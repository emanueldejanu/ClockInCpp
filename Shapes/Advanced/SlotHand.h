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
            /// A clock's hand that is actually a big disk with a rectangle slot carved in it
            /// through which the user can see whatever is under the disk
            /// </summary>
            class SlotHand : public Basic::PathHand {
            private:
                float m_width;
                float m_radius;
                float m_tailLength;

            protected:
                void CalculateCache(ClockDrawingContext& context) override;

            public:
                static constexpr float DefaultWidth = 10.0f;
                static constexpr float DefaultRadius = 100.0f;
                static constexpr float DefaultTailLength = 12.0f;
                static constexpr const wchar_t* DefaultName = L"Slot Hand";

                SlotHand();
                virtual ~SlotHand() = default;

                float GetWidth() const { return m_width; }
                void SetWidth(float width);

                float GetRadius() const { return m_radius; }
                void SetRadius(float radius);

                float GetTailLength() const { return m_tailLength; }
                void SetTailLength(float tailLength);
            };

        } // namespace Advanced
    } // namespace Shapes
} // namespace ClockNet
