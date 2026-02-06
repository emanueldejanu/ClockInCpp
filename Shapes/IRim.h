// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#pragma once
#include "IShape.h"

namespace ClockNet {
    namespace Shapes {

        /// <summary>
        /// Interface for rim shapes (shapes repeated around the clock)
        /// </summary>
        class IRim {
        public:
            virtual ~IRim() = default;

            virtual float GetDistanceFromEdge() const = 0;
            virtual void SetDistanceFromEdge(float distance) = 0;

            virtual float GetAngle() const = 0;
            virtual void SetAngle(float angle) = 0;

            virtual float GetOffsetAngle() const = 0;
            virtual void SetOffsetAngle(float angle) = 0;

            virtual int GetSkipIndex() const = 0;
            virtual void SetSkipIndex(int skip) = 0;

            virtual bool GetRepeat() const = 0;
            virtual void SetRepeat(bool repeat) = 0;
        };

    } // namespace Shapes
} // namespace ClockNet
