// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#include "DiamondHand.h"
#include <cmath>

namespace ClockNet {
    namespace Shapes {
        namespace Default {

            DiamondHand::DiamondHand()
                : m_tailLength(DefaultTailLength)
                , m_width(DefaultWidth) {
                m_name = DefaultName;
                m_fillColor = Gdiplus::Color(65, 105, 225); // RoyalBlue
            }

            void DiamondHand::SetTailLength(float length) {
                m_tailLength = length;
                InvalidateLayout();
                if (Changed)
                    Changed();
            }

            void DiamondHand::SetWidth(float width) {
                m_width = width;
                InvalidateLayout();
                if (Changed)
                    Changed();
            }

            void DiamondHand::CalculateCache(ClockDrawingContext& context) {
                float diameter = context.Diameter;
                float radius = diameter / 2.0f;
                float actualLength = radius * (m_length / 100.0f);
                float actualTailLength = radius * (m_tailLength / 100.0f);
                float actualWidth = radius * (m_width / 100.0f);
                float actualHalfWidth = actualWidth / 2.0f;

                m_points.clear();
                m_points.push_back(Gdiplus::PointF(0.0f, actualTailLength));
                m_points.push_back(Gdiplus::PointF(-actualHalfWidth, 0.0f));
                m_points.push_back(Gdiplus::PointF(0.0f, -actualLength));
                m_points.push_back(Gdiplus::PointF(actualHalfWidth, 0.0f));
            }

            void DiamondHand::OnDraw(ClockDrawingContext& context) {
                if (m_points.size() < 2)
                    return;

                if (m_fillColor.GetValue() != 0) {
                    context.Graphics->FillPolygon(GetBrush(), m_points.data(), (INT)m_points.size());
                }

                if (m_outlineColor.GetValue() != 0) {
                    context.Graphics->DrawPolygon(GetPen(), m_points.data(), (INT)m_points.size());
                }
            }

            bool DiamondHand::HitTest(const Gdiplus::PointF& point, const SYSTEMTIME& time) {
                Gdiplus::Matrix matrix;
                float angle = GetRotationDegrees(time);
                matrix.Rotate(-angle);

                Gdiplus::PointF points[1] = { point };
                matrix.TransformPoints(points, 1);

                return IsPointInsidePolygon(points[0], m_points);
            }

            bool DiamondHand::IsPointInsidePolygon(const Gdiplus::PointF& point,
                                                  const std::vector<Gdiplus::PointF>& polygon) const {
                int j = (int)polygon.size() - 1;
                bool oddNodes = false;

                for (size_t i = 0; i < polygon.size(); i++) {
                    if ((polygon[i].Y < point.Y && polygon[j].Y >= point.Y) ||
                        (polygon[j].Y < point.Y && polygon[i].Y >= point.Y)) {
                        if (polygon[i].X + (point.Y - polygon[i].Y) / (polygon[j].Y - polygon[i].Y) *
                            (polygon[j].X - polygon[i].X) < point.X) {
                            oddNodes = !oddNodes;
                        }
                    }
                    j = (int)i;
                }

                return oddNodes;
            }

        } // namespace Default
    } // namespace Shapes
} // namespace ClockNet
