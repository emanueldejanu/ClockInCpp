// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#include "HandBase.h"
#include <cmath>

namespace ClockNet {
    namespace Shapes {

        HandBase::HandBase()
            : m_length(DefaultLength)
            , m_componentToDisplay(TimeComponent::None)
            , m_integralValue(DefaultIntegralValue) {
        }

        void HandBase::SetLength(float length) {
            if (m_length == length)
                return;

            m_length = length;
            InvalidateLayout();
            if (Changed)
                Changed();
        }

        void HandBase::SetComponentToDisplay(TimeComponent component) {
            if (m_componentToDisplay == component)
                return;

            m_componentToDisplay = component;
            if (Changed)
                Changed();
        }

        void HandBase::SetIntegralValue(bool value) {
            if (m_integralValue == value)
                return;

            m_integralValue = value;
            if (Changed)
                Changed();
        }

        float HandBase::GetRotationDegrees(const SYSTEMTIME& time) const {
            switch (m_componentToDisplay) {
                case TimeComponent::Hour:
                    if (m_integralValue)
                        return (float)((time.wHour % 12) * 30);
                    else
                        return (float)((time.wHour % 12 + time.wMinute / 60.0f) * 30);

                case TimeComponent::Minute:
                    if (m_integralValue)
                        return (float)(time.wMinute * 6);
                    else
                        return (float)((time.wMinute + time.wSecond / 60.0f) * 6);

                case TimeComponent::Second:
                    if (m_integralValue)
                        return (float)(time.wSecond * 6);
                    else
                        return (float)((time.wSecond + time.wMilliseconds / 1000.0f) * 6);

                default:
                    return 0;
            }
        }

        bool HandBase::OnBeforeDraw(ClockDrawingContext& context) {
            bool allowToDraw = ShapeBase::OnBeforeDraw(context);
            if (!allowToDraw)
                return false;

            float degrees = GetRotationDegrees(context.Time);
            if (degrees != 0) {
                context.Graphics->RotateTransform(degrees);
            }

            return true;
        }

    } // namespace Shapes
} // namespace ClockNet
