// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#pragma once
#include "../VectorialShapeBase.h"

namespace ClockNet {
    namespace Shapes {
        namespace Default {

            /// <summary>
            /// Ticks around the clock rim
            /// </summary>
            class Ticks : public VectorialShapeBase {
            private:
                float m_length;
                float m_distanceFromEdge;
                float m_angle;
                float m_offsetAngle;
                int m_skipIndex;

                Gdiplus::PointF m_startPoint;
                Gdiplus::PointF m_endPoint;

            protected:
                void CalculateCache(ClockDrawingContext& context) override;
                bool OnBeforeDraw(ClockDrawingContext& context) override;
                void OnDraw(ClockDrawingContext& context) override;

            public:
                static constexpr float DefaultLength = 5.0f;
                static constexpr float DefaultDistanceFromEdge = 8.0f;
                static constexpr const wchar_t* DefaultName = L"Ticks";

                Ticks();

                float GetLength() const { return m_length; }
                void SetLength(float length);

                float GetDistanceFromEdge() const { return m_distanceFromEdge; }
                void SetDistanceFromEdge(float distance);

                float GetAngle() const { return m_angle; }
                void SetAngle(float angle);

                float GetOffsetAngle() const { return m_offsetAngle; }
                void SetOffsetAngle(float angle);

                int GetSkipIndex() const { return m_skipIndex; }
                void SetSkipIndex(int skip);
            };

        } // namespace Default
    } // namespace Shapes
} // namespace ClockNet
