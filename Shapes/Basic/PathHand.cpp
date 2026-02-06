// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#include "PathHand.h"

namespace ClockNet {
    namespace Shapes {
        namespace Basic {

            PathHand::PathHand()
                : PathHand(new Gdiplus::GraphicsPath(), Gdiplus::Color(), Gdiplus::Color::Black, DefaultLength, DefaultOutlineWidth) {
            }

            PathHand::PathHand(Gdiplus::GraphicsPath* path,
                             const Gdiplus::Color& outlineColor,
                             const Gdiplus::Color& fillColor,
                             float length,
                             float lineWidth)
                : VectorialHandBase(outlineColor, fillColor, lineWidth, length)
                , m_path(path) {
                m_name = DefaultName;
            }

            PathHand::~PathHand() {
                // m_path will be automatically deleted by unique_ptr
            }

            bool PathHand::OnBeforeDraw(ClockDrawingContext& context) {
                if (!m_path)
                    return false;

                return VectorialHandBase::OnBeforeDraw(context);
            }

            void PathHand::OnDraw(ClockDrawingContext& context) {
                if (!m_path)
                    return;

                if (m_fillColor.GetValue() != 0) {
                    context.Graphics->FillPath(GetBrush(), m_path.get());
                }

                if (m_outlineColor.GetValue() != 0) {
                    context.Graphics->DrawPath(GetPen(), m_path.get());
                }
            }

            bool PathHand::HitTest(const Gdiplus::PointF& point, const SYSTEMTIME& time) {
                if (!m_path)
                    return false;

                Gdiplus::Matrix matrix;
                float angle = GetRotationDegrees(time);
                matrix.Rotate(-angle);

                Gdiplus::PointF points[1] = { point };
                matrix.TransformPoints(points, 1);

                return m_path->IsVisible(points[0]);
            }

        } // namespace Basic
    } // namespace Shapes
} // namespace ClockNet
