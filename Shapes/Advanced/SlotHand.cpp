// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#include "SlotHand.h"

namespace ClockNet {
    namespace Shapes {
        namespace Advanced {

            SlotHand::SlotHand()
                : Basic::PathHand(new Gdiplus::GraphicsPath(),
                                 Gdiplus::Color::Black,    // OutlineColor
                                 Gdiplus::Color::Black,    // FillColor
                                 100.0f,                   // Default length (100%)
                                 1.0f)
                , m_width(DefaultWidth)
                , m_radius(DefaultRadius)
                , m_tailLength(DefaultTailLength) {
                m_name = DefaultName;
            }

            void SlotHand::SetWidth(float width) {
                if (m_width == width)
                    return;

                m_width = width;
                InvalidateLayout();
                if (Changed)
                    Changed();
            }

            void SlotHand::SetRadius(float radius) {
                if (m_radius == radius)
                    return;

                m_radius = radius;
                InvalidateLayout();
                if (Changed)
                    Changed();
            }

            void SlotHand::SetTailLength(float tailLength) {
                m_tailLength = tailLength;
                InvalidateLayout();
                if (Changed)
                    Changed();
            }

            void SlotHand::CalculateCache(ClockDrawingContext& context) {
                auto path = GetPath();
                if (!path)
                    return;

                path->Reset();

                float diameter = context.Diameter;
                float radius = diameter / 2.0f;
                float actualLength = radius * (m_length / 100.0f);
                float actualTailLength = radius * (m_tailLength / 100.0f);
                float actualWidth = radius * (m_width / 100.0f);
                float actualHandRadius = radius * (m_radius / 100.0f);

                // The circular disk
                float ellipseX = -actualHandRadius;
                float ellipseY = -actualHandRadius;
                float ellipseWidth = actualHandRadius * 2.0f;
                float ellipseHeight = actualHandRadius * 2.0f;

                path->AddEllipse(ellipseX, ellipseY, ellipseWidth, ellipseHeight);

                // The rectangle slot
                float rectangleX = -actualWidth / 2.0f;
                float rectangleY = -actualLength;
                float rectangleWidth = actualWidth;
                float rectangleHeight = actualLength + actualTailLength;

                Gdiplus::RectF rect(rectangleX, rectangleY, rectangleWidth, rectangleHeight);
                path->AddRectangle(rect);
            }

        } // namespace Advanced
    } // namespace Shapes
} // namespace ClockNet
