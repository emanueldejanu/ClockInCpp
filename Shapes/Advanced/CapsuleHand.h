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
            /// A clock hand shaped like a capsule/pill
            /// </summary>
            class CapsuleHand : public Basic::PathHand {
            private:
                float m_width;
                float m_tailLength;

            protected:
                void CalculateCache(ClockDrawingContext& context) override;

            public:
                static constexpr float DefaultWidth = 4.0f;
                static constexpr float DefaultTailLength = 2.0f;
                static constexpr float DefaultLength = 43.0f;
                static constexpr const wchar_t* DefaultName = L"Capsule Hand";

                CapsuleHand();
                virtual ~CapsuleHand() = default;

                float GetWidth() const { return m_width; }
                void SetWidth(float width);

                float GetTailLength() const { return m_tailLength; }
                void SetTailLength(float tailLength);
            };

        } // namespace Advanced
    } // namespace Shapes
} // namespace ClockNet
