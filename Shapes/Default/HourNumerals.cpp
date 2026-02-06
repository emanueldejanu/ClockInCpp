// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#include "HourNumerals.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace ClockNet {
    namespace Shapes {
        namespace Default {

            HourNumerals::HourNumerals()
                : m_distanceFromEdge(DefaultDistanceFromEdge) {
                m_name = DefaultName;
                m_fillColor = Gdiplus::Color::Black;

                m_font.reset(new Gdiplus::Font(L"Arial", 12.0f, Gdiplus::FontStyleRegular, Gdiplus::UnitPoint));
                m_stringFormat.reset(new Gdiplus::StringFormat());
                m_stringFormat->SetAlignment(Gdiplus::StringAlignmentCenter);
                m_stringFormat->SetLineAlignment(Gdiplus::StringAlignmentCenter);
            }

            HourNumerals::~HourNumerals() {
            }

            void HourNumerals::SetDistanceFromEdge(float distance) {
                m_distanceFromEdge = distance;
                if (Changed)
                    Changed();
            }

            void HourNumerals::OnDraw(ClockDrawingContext& context) {
                Gdiplus::Matrix originalMatrix;
                context.Graphics->GetTransform(&originalMatrix);

                float diameter = context.Diameter;
                float radius = diameter / 2.0f;
                float distance = radius * (m_distanceFromEdge / 100.0f);

                for (int i = 1; i <= 12; i++) {
                    float angle = (float)(i * 30.0f - 90.0f); // Convert to radians offset
                    float radians = angle * (float)M_PI / 180.0f;

                    float x = (radius - distance) * cos(radians);
                    float y = (radius - distance) * sin(radians);

                    wchar_t text[3];
                    swprintf_s(text, 3, L"%d", i);

                    context.Graphics->SetTransform(&originalMatrix);
                    context.Graphics->DrawString(
                        text,
                        -1,
                        m_font.get(),
                        Gdiplus::PointF(x, y),
                        m_stringFormat.get(),
                        GetBrush()
                    );
                }

                context.Graphics->SetTransform(&originalMatrix);
            }

        } // namespace Default
    } // namespace Shapes
} // namespace ClockNet
