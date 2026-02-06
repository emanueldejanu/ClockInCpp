// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#pragma once
#include "../VectorialHandBase.h"

namespace ClockNet {
    namespace Shapes {
        namespace Basic {

            /// <summary>
            /// Simple line hand for the clock
            /// </summary>
            class LineHand : public VectorialHandBase {
            private:
                Gdiplus::PointF m_startPoint;
                Gdiplus::PointF m_endPoint;

            protected:
                void CalculateCache(ClockDrawingContext& context) override;
                void OnDraw(ClockDrawingContext& context) override;

            public:
                static constexpr const wchar_t* DefaultName = L"Line Hand";

                LineHand();

                bool HitTest(const Gdiplus::PointF& point, const SYSTEMTIME& time) override;
            };

        } // namespace Basic
    } // namespace Shapes
} // namespace ClockNet
