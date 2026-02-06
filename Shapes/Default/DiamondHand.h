// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#pragma once
#include "../VectorialHandBase.h"
#include <vector>

namespace ClockNet {
    namespace Shapes {
        namespace Default {

            /// <summary>
            /// A clock hand shaped like a diamond
            /// </summary>
            class DiamondHand : public VectorialHandBase {
            private:
                float m_tailLength;
                float m_width;
                std::vector<Gdiplus::PointF> m_points;

                bool IsPointInsidePolygon(const Gdiplus::PointF& point,
                                        const std::vector<Gdiplus::PointF>& polygon) const;

            protected:
                void CalculateCache(ClockDrawingContext& context) override;
                void OnDraw(ClockDrawingContext& context) override;

            public:
                static constexpr float DefaultTailLength = 12.0f;
                static constexpr float DefaultWidth = 10.0f;
                static constexpr const wchar_t* DefaultName = L"Diamond Hand";

                DiamondHand();

                float GetTailLength() const { return m_tailLength; }
                void SetTailLength(float length);

                float GetWidth() const { return m_width; }
                void SetWidth(float width);

                bool HitTest(const Gdiplus::PointF& point, const SYSTEMTIME& time) override;
            };

        } // namespace Default
    } // namespace Shapes
} // namespace ClockNet
