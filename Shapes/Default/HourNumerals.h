// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#pragma once
#include "../VectorialShapeBase.h"
#include <string>
#include <memory>

namespace ClockNet {
    namespace Shapes {
        namespace Default {

            /// <summary>
            /// Hour numerals around the clock face
            /// </summary>
            class HourNumerals : public VectorialShapeBase {
            private:
                float m_distanceFromEdge;
                std::unique_ptr<Gdiplus::Font> m_font;
                std::unique_ptr<Gdiplus::StringFormat> m_stringFormat;

            protected:
                void OnDraw(ClockDrawingContext& context) override;

            public:
                static constexpr float DefaultDistanceFromEdge = 26.0f;
                static constexpr const wchar_t* DefaultName = L"Hour Numerals";

                HourNumerals();
                ~HourNumerals();

                float GetDistanceFromEdge() const { return m_distanceFromEdge; }
                void SetDistanceFromEdge(float distance);
            };

        } // namespace Default
    } // namespace Shapes
} // namespace ClockNet
