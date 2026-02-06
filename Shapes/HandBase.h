// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#pragma once
#include "ShapeBase.h"
#include "TimeComponent.h"

namespace ClockNet {
    namespace Shapes {

        /// <summary>
        /// Base class for clock hands
        /// </summary>
        class HandBase : public ShapeBase {
        protected:
            float m_length;
            TimeComponent m_componentToDisplay;
            bool m_integralValue;

            float GetRotationDegrees(const SYSTEMTIME& time) const;
            bool OnBeforeDraw(ClockDrawingContext& context) override;

        public:
            static constexpr float DefaultLength = 90.0f;
            static constexpr bool DefaultIntegralValue = false;

            HandBase();
            virtual ~HandBase() = default;

            // Properties
            float GetLength() const { return m_length; }
            void SetLength(float length);

            TimeComponent GetComponentToDisplay() const { return m_componentToDisplay; }
            void SetComponentToDisplay(TimeComponent component);

            bool GetIntegralValue() const { return m_integralValue; }
            void SetIntegralValue(bool value);

            // Hit testing
            virtual bool HitTest(const Gdiplus::PointF& point, const SYSTEMTIME& time) = 0;
        };

    } // namespace Shapes
} // namespace ClockNet
