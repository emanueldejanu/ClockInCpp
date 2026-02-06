// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#include "LineHand.h"

namespace ClockNet {
    namespace Shapes {
        namespace Basic {

            LineHand::LineHand() {
                m_name = DefaultName;
                m_outlineColor = Gdiplus::Color::Red;
            }

            void LineHand::CalculateCache(ClockDrawingContext& context) {
                float diameter = context.Diameter;
                float radius = diameter / 2.0f;
                float actualLength = radius * (m_length / 100.0f);

                m_startPoint = Gdiplus::PointF(0, 0);
                m_endPoint = Gdiplus::PointF(0, -actualLength);
            }

            void LineHand::OnDraw(ClockDrawingContext& context) {
                if (m_outlineColor.GetValue() != 0) {
                    context.Graphics->DrawLine(GetPen(), m_startPoint, m_endPoint);
                }
            }

            bool LineHand::HitTest(const Gdiplus::PointF& point, const SYSTEMTIME& time) {
                // Simple hit testing - could be improved
                return false;
            }

        } // namespace Basic
    } // namespace Shapes
} // namespace ClockNet
