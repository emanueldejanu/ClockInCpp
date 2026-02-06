// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#include "NibHand.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace ClockNet {
    namespace Shapes {
        namespace Advanced {

            NibHand::NibHand()
                : Basic::PathHand(new Gdiplus::GraphicsPath(), Gdiplus::Color(), Gdiplus::Color::Black, DefaultLength, DefaultOutlineWidth)
                , m_width(DefaultWidth)
                , m_keepProportions(true) {
                m_name = DefaultName;
            }

            void NibHand::SetWidth(float width) {
                m_width = width;
                InvalidateLayout();
                if (Changed)
                    Changed();
            }

            void NibHand::SetKeepProportions(bool keep) {
                m_keepProportions = keep;
                InvalidateLayout();
                if (Changed)
                    Changed();
            }

            void NibHand::CalculateCache(ClockDrawingContext& context) {
                auto path = GetPath();
                if (!path)
                    return;

                path->Reset();

                // Create the nib shape - exact coordinates from C# version
                path->AddArc(Gdiplus::RectF(-12.0f, 43.0f, 24.0f, 24.0f), -60.0f, 300.0f);

                // First curve
                Gdiplus::PointF curve1[] = {
                    Gdiplus::PointF(-4.0f, 39.0f),
                    Gdiplus::PointF(-8.0f, 35.0f)
                };
                path->AddCurve(curve1, 2);

                // Second curve
                Gdiplus::PointF curve2[] = {
                    Gdiplus::PointF(-8.0f, 35.0f),
                    Gdiplus::PointF(-4.0f, 29.0f),
                    Gdiplus::PointF(-2.0f, 11.0f)
                };
                path->AddCurve(curve2, 3);

                // Arc
                path->AddArc(Gdiplus::RectF(-12.0f, -13.0f, 24.0f, 24.0f), 90.0f, 90.0f);

                // Curve to tip
                Gdiplus::PointF curve3[] = {
                    Gdiplus::PointF(-12.0f, -7.0f),
                    Gdiplus::PointF(-2.0f, -59.0f),
                    Gdiplus::PointF(-10.0f, -119.0f)
                };
                path->AddCurve(curve3, 3);

                // Tip curve
                Gdiplus::PointF curve4[] = {
                    Gdiplus::PointF(-10.0f, -119.0f),
                    Gdiplus::PointF(-5.0f, -124.0f),
                    Gdiplus::PointF(-3.0f, -129.0f)
                };
                path->AddCurve(curve4, 3);

                // Top arc
                path->AddArc(Gdiplus::RectF(-15.0f, -159.0f, 30.0f, 30.0f), 90.0f, 90.0f);

                // Top curve
                Gdiplus::PointF curve5[] = {
                    Gdiplus::PointF(-14.0f, -151.0f),
                    Gdiplus::PointF(-3.0f, -199.0f),
                    Gdiplus::PointF(-1.0f, -249.0f)
                };
                path->AddCurve(curve5, 3);

                // Left line to center
                path->AddLine(Gdiplus::PointF(-1.0f, -249.0f), Gdiplus::PointF(-1.0f, -280.0f));

                // Center line
                path->AddLine(Gdiplus::PointF(1.0f, -280.0f), Gdiplus::PointF(1.0f, -249.0f));

                // Mirror side - top curve
                Gdiplus::PointF curve6[] = {
                    Gdiplus::PointF(1.0f, -249.0f),
                    Gdiplus::PointF(3.0f, -199.0f),
                    Gdiplus::PointF(14.0f, -151.0f)
                };
                path->AddCurve(curve6, 3);

                // Mirror arc
                path->AddArc(Gdiplus::RectF(-15.0f, -159.0f, 30.0f, 30.0f), 0.0f, 90.0f);

                // Mirror tip curve
                Gdiplus::PointF curve7[] = {
                    Gdiplus::PointF(3.0f, -129.0f),
                    Gdiplus::PointF(5.0f, -124.0f),
                    Gdiplus::PointF(10.0f, -119.0f)
                };
                path->AddCurve(curve7, 3);

                // Mirror curve to bottom
                Gdiplus::PointF curve8[] = {
                    Gdiplus::PointF(10.0f, -119.0f),
                    Gdiplus::PointF(2.0f, -59.0f),
                    Gdiplus::PointF(12.0f, -7.0f)
                };
                path->AddCurve(curve8, 3);

                // Mirror arc
                path->AddArc(Gdiplus::RectF(-12.0f, -13.0f, 24.0f, 24.0f), 0.0f, 90.0f);

                // Mirror curves at bottom
                Gdiplus::PointF curve9[] = {
                    Gdiplus::PointF(2.0f, 11.0f),
                    Gdiplus::PointF(4.0f, 29.0f),
                    Gdiplus::PointF(8.0f, 35.0f)
                };
                path->AddCurve(curve9, 3);

                Gdiplus::PointF curve10[] = {
                    Gdiplus::PointF(8.0f, 35.0f),
                    Gdiplus::PointF(4.0f, 39.0f),
                    Gdiplus::PointF(10.0f * (float)cos(M_PI / 3.0), 41.0f * (float)sin(M_PI / 3.0))
                };
                path->AddCurve(curve10, 3);
            }

            void NibHand::OnDraw(ClockDrawingContext& context) {
                // Apply scaling
                if (m_keepProportions && m_length > 0) {
                    float scaleFactor = m_length / 280.0f;
                    context.Graphics->ScaleTransform(scaleFactor, scaleFactor);
                } else {
                    float scaleFactorY = m_length > 0 ? m_length / 280.0f : 1.0f;
                    float scaleFactorX = m_width > 0 ? m_width / 30.0f : 1.0f;
                    context.Graphics->ScaleTransform(scaleFactorX, scaleFactorY);
                }

                // Draw the path using base class
                Basic::PathHand::OnDraw(context);
            }

            bool NibHand::HitTest(const Gdiplus::PointF& point, const SYSTEMTIME& time) {
                Gdiplus::Matrix matrix;

                // Inverse of the scaling applied in OnDraw
                if (m_keepProportions && m_length > 0) {
                    float scaleFactor = m_length / 280.0f;
                    matrix.Scale(1.0f / scaleFactor, 1.0f / scaleFactor);
                } else {
                    float scaleFactorY = m_length > 0 ? m_length / 280.0f : 1.0f;
                    float scaleFactorX = m_width > 0 ? m_width / 30.0f : 1.0f;
                    matrix.Scale(1.0f / scaleFactorX, 1.0f / scaleFactorY);
                }

                Gdiplus::PointF points[1] = { point };
                matrix.TransformPoints(points, 1);

                return Basic::PathHand::HitTest(points[0], time);
            }

        } // namespace Advanced
    } // namespace Shapes
} // namespace ClockNet
