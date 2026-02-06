// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#include "DotHand.h"
#include <cmath>
#include <stdexcept>

namespace ClockNet {
    namespace Shapes {
        namespace Advanced {

            DotHand::DotHand()
                : VectorialHandBase(Gdiplus::Color::Transparent,
                                   Gdiplus::Color::Black,
                                   DefaultOutlineWidth,
                                   DefaultLength)
                , m_radius(DefaultRadius)
                , m_dotRectangle() {
                m_name = DefaultName;
            }

            void DotHand::SetRadius(float radius) {
                if (radius < 0)
                    throw std::out_of_range("The radius cannot be a negative value.");

                m_radius = radius;
                InvalidateLayout();
                if (Changed)
                    Changed();
            }

            bool DotHand::OnBeforeDraw(ClockDrawingContext& context) {
                if (m_radius <= 0 || m_length <= 0)
                    return false;

                return VectorialHandBase::OnBeforeDraw(context);
            }

            void DotHand::CalculateCache(ClockDrawingContext& context) {
                float x = -m_radius;
                float y = -m_length - m_radius;
                float width = m_radius * 2.0f;
                float height = m_radius * 2.0f;

                m_dotRectangle = Gdiplus::RectF(x, y, width, height);
            }

            void DotHand::OnDraw(ClockDrawingContext& context) {
                if (m_fillColor.GetValue() != 0)
                    context.Graphics->FillEllipse(GetBrush(), m_dotRectangle);

                if (m_outlineColor.GetValue() != 0)
                    context.Graphics->DrawEllipse(GetPen(), m_dotRectangle);
            }

            bool DotHand::HitTest(const Gdiplus::PointF& point, const SYSTEMTIME& time) {
                Gdiplus::PointF dotCenter(
                    m_dotRectangle.X + m_radius,
                    m_dotRectangle.Y + m_radius
                );

                Gdiplus::Matrix matrix;
                float angle = GetRotationDegrees(time);
                matrix.Rotate(angle);

                Gdiplus::PointF points[1] = { dotCenter };
                matrix.TransformPoints(points, 1);

                float centerX = points[0].X;
                float centerY = points[0].Y;

                float alphaX = point.X - centerX;
                float alphaY = point.Y - centerY;

                float dist = std::sqrt(alphaX * alphaX + alphaY * alphaY);

                return dist <= m_radius;
            }

        } // namespace Advanced
    } // namespace Shapes
} // namespace ClockNet
