// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#include "Pin.h"

namespace ClockNet {
    namespace Shapes {
        namespace Default {

            Pin::Pin()
                : VectorialHandBase(Gdiplus::Color(), Gdiplus::Color::Black)
                , m_diameter(DefaultDiameter)
                , m_centerX(0)
                , m_centerY(0) {
                m_name = DefaultName;
            }

            void Pin::SetDiameter(float diameter) {
                if (diameter < 0)
                    return;

                m_diameter = diameter;
                InvalidateLayout();
                if (Changed)
                    Changed();
            }

            bool Pin::OnBeforeDraw(ClockDrawingContext& context) {
                if (m_diameter <= 0)
                    return false;

                // Don't rotate the pin - override base behavior
                return ShapeBase::OnBeforeDraw(context);
            }

            void Pin::CalculateCache(ClockDrawingContext& context) {
                m_centerX = -m_diameter / 2.0f;
                m_centerY = -m_diameter / 2.0f;
            }

            void Pin::OnDraw(ClockDrawingContext& context) {
                if (m_fillColor.GetValue() != 0) {
                    context.Graphics->FillEllipse(GetBrush(), m_centerX, m_centerY, m_diameter, m_diameter);
                }

                if (m_outlineColor.GetValue() != 0) {
                    context.Graphics->DrawEllipse(GetPen(), m_centerX, m_centerY, m_diameter, m_diameter);
                }
            }

            bool Pin::HitTest(const Gdiplus::PointF& point, const SYSTEMTIME& time) {
                return false;
            }

        } // namespace Default
    } // namespace Shapes
} // namespace ClockNet
