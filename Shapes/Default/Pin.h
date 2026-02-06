// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#pragma once
#include "../VectorialHandBase.h"

namespace ClockNet {
    namespace Shapes {
        namespace Default {

            /// <summary>
            /// Center pin shape for the clock
            /// </summary>
            class Pin : public VectorialHandBase {
            private:
                float m_diameter;
                float m_centerX;
                float m_centerY;

            protected:
                void CalculateCache(ClockDrawingContext& context) override;
                bool OnBeforeDraw(ClockDrawingContext& context) override;
                void OnDraw(ClockDrawingContext& context) override;

            public:
                static constexpr float DefaultDiameter = 1.33f;
                static constexpr const wchar_t* DefaultName = L"Pin";

                Pin();

                float GetDiameter() const { return m_diameter; }
                void SetDiameter(float diameter);

                bool HitTest(const Gdiplus::PointF& point, const SYSTEMTIME& time) override;
            };

        } // namespace Default
    } // namespace Shapes
} // namespace ClockNet
