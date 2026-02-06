// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#include "Ticks.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace ClockNet {
    namespace Shapes {
        namespace Default {

            Ticks::Ticks()
                : m_length(DefaultLength)
                , m_distanceFromEdge(DefaultDistanceFromEdge)
                , m_angle(6.0f)
                , m_offsetAngle(0.0f)
                , m_skipIndex(0) {
                m_name = DefaultName;
                m_outlineColor = Gdiplus::Color::Black;
                m_outlineWidth = 0.3f;
            }

            void Ticks::SetLength(float length) {
                m_length = length;
                InvalidateLayout();
                if (Changed)
                    Changed();
            }

            void Ticks::SetDistanceFromEdge(float distance) {
                m_distanceFromEdge = distance;
                InvalidateLayout();
                if (Changed)
                    Changed();
            }

            void Ticks::SetAngle(float angle) {
                m_angle = angle;
                if (Changed)
                    Changed();
            }

            void Ticks::SetOffsetAngle(float angle) {
                m_offsetAngle = angle;
                if (Changed)
                    Changed();
            }

            void Ticks::SetSkipIndex(int skip) {
                m_skipIndex = skip;
                if (Changed)
                    Changed();
            }

            bool Ticks::OnBeforeDraw(ClockDrawingContext& context) {
                if (m_outlineColor.GetValue() == 0 || m_length <= 0)
                    return false;
                return VectorialShapeBase::OnBeforeDraw(context);
            }

            void Ticks::CalculateCache(ClockDrawingContext& context) {
                float diameter = context.Diameter;
                float radius = diameter / 2.0f;
                float actualLength = radius * (m_length / 100.0f);

                m_startPoint = Gdiplus::PointF(0, -actualLength / 2.0f);
                m_endPoint = Gdiplus::PointF(0, actualLength / 2.0f);
            }

            void Ticks::OnDraw(ClockDrawingContext& context) {
                Gdiplus::Matrix originalMatrix;
                context.Graphics->GetTransform(&originalMatrix);

                float diameter = context.Diameter;
                float radius = diameter / 2.0f;
                float distance = radius * (m_distanceFromEdge / 100.0f);

                int count = (int)(360.0f / m_angle);
                for (int i = 0; i < count; i++) {
                    if (m_skipIndex > 0 && i % m_skipIndex == 0)
                        continue;

                    context.Graphics->SetTransform(&originalMatrix);
                    context.Graphics->TranslateTransform(0, -radius + distance);
                    context.Graphics->RotateTransform(m_offsetAngle + i * m_angle);

                    context.Graphics->DrawLine(GetPen(), m_startPoint, m_endPoint);
                }

                context.Graphics->SetTransform(&originalMatrix);
            }

        } // namespace Default
    } // namespace Shapes
} // namespace ClockNet
