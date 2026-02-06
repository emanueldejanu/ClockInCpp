// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#pragma once
#include <windows.h>
#include <gdiplus.h>
#include <algorithm>

namespace ClockNet {
    namespace Utils {

        /// <summary>
        /// Color manipulation utilities
        /// </summary>
        class ColorExtensions {
        public:
            /// <summary>
            /// Shifts the brightness of a color
            /// </summary>
            static Gdiplus::Color ShiftBrightness(const Gdiplus::Color& color, float shift) {
                int r = std::min(255, std::max(0, (int)(color.GetR() + shift)));
                int g = std::min(255, std::max(0, (int)(color.GetG() + shift)));
                int b = std::min(255, std::max(0, (int)(color.GetB() + shift)));
                return Gdiplus::Color(color.GetA(), r, g, b);
            }

            /// <summary>
            /// Shifts the saturation of a color
            /// </summary>
            static Gdiplus::Color ShiftSaturation(const Gdiplus::Color& color, float shift) {
                // Simplified version - full HSB conversion would be more accurate
                float factor = 1.0f + (shift / 100.0f);
                int r = std::min(255, std::max(0, (int)(color.GetR() * factor)));
                int g = std::min(255, std::max(0, (int)(color.GetG() * factor)));
                int b = std::min(255, std::max(0, (int)(color.GetB() * factor)));
                return Gdiplus::Color(color.GetA(), r, g, b);
            }
        };

    } // namespace Utils
} // namespace ClockNet
