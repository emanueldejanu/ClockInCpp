// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#include "CapsuleHand.h"

namespace ClockNet {
    namespace Shapes {
        namespace Advanced {

            CapsuleHand::CapsuleHand()
                : Basic::PathHand(new Gdiplus::GraphicsPath(),
                                 Gdiplus::Color(224, 224, 224),  // OutlineColor
                                 Gdiplus::Color::DimGray,        // FillColor
                                 DefaultLength,
                                 1.0f)
                , m_width(DefaultWidth)
                , m_tailLength(DefaultTailLength) {
                m_name = DefaultName;
            }

            void CapsuleHand::SetWidth(float width) {
                m_width = width;
                InvalidateLayout();
                if (Changed)
                    Changed();
            }

            void CapsuleHand::SetTailLength(float tailLength) {
                m_tailLength = tailLength;
                InvalidateLayout();
                if (Changed)
                    Changed();
            }

            void CapsuleHand::CalculateCache(ClockDrawingContext& context) {
                auto path = GetPath();
                if (!path)
                    return;

                path->Reset();

                float halfWidth = m_width / 2.0f;
                float topY = -m_length + halfWidth;
                float bottomY = m_tailLength - halfWidth;

                // Top semicircle (pointing upward)
                path->AddArc(-halfWidth, -m_length, m_width, m_width, 180.0f, 180.0f);

                // Right side of the rectangle
                path->AddLine(halfWidth, topY, halfWidth, bottomY);

                // Bottom semicircle (pointing downward)
                path->AddArc(-halfWidth, m_tailLength - m_width, m_width, m_width, 0.0f, 180.0f);

                // Left side of the rectangle
                path->AddLine(-halfWidth, bottomY, -halfWidth, topY);

                path->CloseFigure();
            }

        } // namespace Advanced
    } // namespace Shapes
} // namespace ClockNet
