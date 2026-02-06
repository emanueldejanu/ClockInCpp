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
            /// Draws a sweep hand as a line with a circle near its top
            /// </summary>
            class FancySweepHand : public Basic::PathHand {
            private:
                float m_circleRadius;
                float m_circleOffset;
                float m_tailLength;

            protected:
                void CalculateCache(ClockDrawingContext& context) override;

            public:
                static constexpr float DefaultCircleRadius = 7.0f;
                static constexpr float DefaultCircleOffset = 24.0f;
                static constexpr float DefaultTailLength = 14.0f;
                static constexpr const wchar_t* DefaultName = L"Fancy Sweep Hand";

                FancySweepHand();
                virtual ~FancySweepHand() = default;

                float GetCircleRadius() const { return m_circleRadius; }
                void SetCircleRadius(float circleRadius);

                float GetCircleOffset() const { return m_circleOffset; }
                void SetCircleOffset(float circleOffset);

                float GetTailLength() const { return m_tailLength; }
                void SetTailLength(float tailLength);
            };

        } // namespace Advanced
    } // namespace Shapes
} // namespace ClockNet
