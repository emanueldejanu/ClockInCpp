// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#include "FancySweepHand.h"

namespace ClockNet {
    namespace Shapes {
        namespace Advanced {

            FancySweepHand::FancySweepHand()
                : Basic::PathHand(new Gdiplus::GraphicsPath(),
                                 Gdiplus::Color::Red,          // OutlineColor
                                 Gdiplus::Color::Transparent,  // FillColor (transparent)
                                 100.0f,                       // Default length (100%)
                                 1.0f)
                , m_circleRadius(DefaultCircleRadius)
                , m_circleOffset(DefaultCircleOffset)
                , m_tailLength(DefaultTailLength) {
                m_name = DefaultName;
            }

            void FancySweepHand::SetCircleRadius(float circleRadius) {
                m_circleRadius = circleRadius;
                InvalidateLayout();
                if (Changed)
                    Changed();
            }

            void FancySweepHand::SetCircleOffset(float circleOffset) {
                m_circleOffset = circleOffset;
                InvalidateLayout();
                if (Changed)
                    Changed();
            }

            void FancySweepHand::SetTailLength(float tailLength) {
                m_tailLength = tailLength;
                InvalidateLayout();
                if (Changed)
                    Changed();
            }

            void FancySweepHand::CalculateCache(ClockDrawingContext& context) {
                auto path = GetPath();
                if (!path)
                    return;

                path->Reset();

                float diameter = context.Diameter;
                float radius = diameter / 2.0f;
                float actualLength = radius * (m_length / 100.0f);
                float actualCircleOffset = radius * (m_circleOffset / 100.0f);
                float actualCircleRadius = radius * (m_circleRadius / 100.0f);
                float actualTailLength = radius * (m_tailLength / 100.0f);

                float actualCircleCenterX = -actualLength + actualCircleOffset;

                // Base Line
                Gdiplus::PointF baseLineStartPoint(0.0f, actualTailLength);
                Gdiplus::PointF baseLineEndPoint(0.0f, actualCircleCenterX + actualCircleRadius);
                path->AddLine(baseLineStartPoint, baseLineEndPoint);

                // Circle
                float circleX = -actualCircleRadius;
                float circleY = actualCircleCenterX - actualCircleRadius;
                float actualCircleDiameter = actualCircleRadius * 2.0f;
                path->AddEllipse(circleX, circleY, actualCircleDiameter, actualCircleDiameter);

                // Tip Line
                Gdiplus::PointF tipLineStartPoint(0.0f, actualCircleCenterX - actualCircleRadius);
                Gdiplus::PointF tipLineEndPoint(0.0f, -actualLength);
                path->AddLine(tipLineStartPoint, tipLineEndPoint);
            }

        } // namespace Advanced
    } // namespace Shapes
} // namespace ClockNet
