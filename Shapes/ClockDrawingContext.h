// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#pragma once
#include <windows.h>
#include <gdiplus.h>

namespace ClockNet {
    namespace Shapes {

        /// <summary>
        /// Contains the drawing context for rendering clock shapes
        /// </summary>
        class ClockDrawingContext {
        public:
            Gdiplus::Graphics* Graphics;
            SYSTEMTIME Time;
            float Diameter;

            ClockDrawingContext(Gdiplus::Graphics* graphics, const SYSTEMTIME& time, float diameter)
                : Graphics(graphics), Time(time), Diameter(diameter) {
            }

            // Helper to get time as fractional hours/minutes/seconds
            float GetHours() const {
                return Time.wHour + Time.wMinute / 60.0f;
            }

            float GetMinutes() const {
                return Time.wMinute + Time.wSecond / 60.0f;
            }

            float GetSeconds() const {
                return Time.wSecond + Time.wMilliseconds / 1000.0f;
            }
        };

    } // namespace Shapes
} // namespace ClockNet
