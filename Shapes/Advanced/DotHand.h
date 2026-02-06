// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#pragma once
#include "../VectorialHandBase.h"

namespace ClockNet {
    namespace Shapes {
        namespace Advanced {

            /// <summary>
            /// This hand is rendered as a disk at the end
            /// </summary>
            class DotHand : public VectorialHandBase {
            private:
                float m_radius;
                Gdiplus::RectF m_dotRectangle;

            protected:
                bool OnBeforeDraw(ClockDrawingContext& context) override;
                void CalculateCache(ClockDrawingContext& context) override;
                void OnDraw(ClockDrawingContext& context) override;

            public:
                static constexpr float DefaultRadius = 5.0f;
                static constexpr const wchar_t* DefaultName = L"Dot Hand";

                DotHand();
                virtual ~DotHand() = default;

                float GetRadius() const { return m_radius; }
                void SetRadius(float radius);

                bool HitTest(const Gdiplus::PointF& point, const SYSTEMTIME& time) override;
            };

        } // namespace Advanced
    } // namespace Shapes
} // namespace ClockNet
