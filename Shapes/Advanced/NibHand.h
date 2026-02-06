// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#pragma once
#include "../Basic/PathHand.h"

namespace ClockNet {
    namespace Shapes {
        namespace Advanced {

            /// <summary>
            /// A fancy clock hand that resembles a pen nib
            /// </summary>
            class NibHand : public Basic::PathHand {
            private:
                float m_width;
                bool m_keepProportions;

            protected:
                void CalculateCache(ClockDrawingContext& context) override;
                void OnDraw(ClockDrawingContext& context) override;

            public:
                static constexpr float DefaultWidth = 5.0f;
                static constexpr const wchar_t* DefaultName = L"Nib Hand";

                NibHand();
                virtual ~NibHand() = default;

                float GetWidth() const { return m_width; }
                void SetWidth(float width);

                bool GetKeepProportions() const { return m_keepProportions; }
                void SetKeepProportions(bool keep);

                bool HitTest(const Gdiplus::PointF& point, const SYSTEMTIME& time) override;
            };

        } // namespace Advanced
    } // namespace Shapes
} // namespace ClockNet
