// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#pragma once
#include "ShapeBase.h"
#include "IRim.h"
#include "RimItemOrientation.h"

namespace ClockNet {
    namespace Shapes {

        /// <summary>
        /// Base class for rim shapes (shapes repeated around the clock)
        /// </summary>
        class RimBase : public ShapeBase, public IRim {
        protected:
            float m_distanceFromEdge;
            float m_angle;
            float m_offsetAngle;
            int m_skipIndex;
            bool m_repeat;
            RimItemOrientation m_orientation;
            uint32_t m_maxCoverageCount;
            uint32_t m_maxCoverageAngle;

            void OnDraw(ClockDrawingContext& context) override;
            virtual void DrawItem(Gdiplus::Graphics* g, int index) = 0;

        public:
            static constexpr float DefaultDistanceFromEdge = 0.0f;
            static constexpr float DefaultAngle = 6.0f;
            static constexpr float DefaultOffsetAngle = 6.0f;
            static constexpr int DefaultSkipIndex = 0;
            static constexpr bool DefaultRepeat = true;
            static constexpr uint32_t DefaultMaxCoverageCount = 0;
            static constexpr uint32_t DefaultMaxCoverageAngle = 360;

            RimBase();
            RimBase(float angle, bool repeat, float distanceFromEdge);
            virtual ~RimBase() = default;

            // IRim implementation
            float GetDistanceFromEdge() const override { return m_distanceFromEdge; }
            void SetDistanceFromEdge(float distance) override;

            float GetAngle() const override { return m_angle; }
            void SetAngle(float angle) override;

            float GetOffsetAngle() const override { return m_offsetAngle; }
            void SetOffsetAngle(float angle) override;

            int GetSkipIndex() const override { return m_skipIndex; }
            void SetSkipIndex(int skip) override;

            bool GetRepeat() const override { return m_repeat; }
            void SetRepeat(bool repeat) override;

            // Additional properties
            RimItemOrientation GetOrientation() const { return m_orientation; }
            void SetOrientation(RimItemOrientation orientation);

            uint32_t GetMaxCoverageCount() const { return m_maxCoverageCount; }
            void SetMaxCoverageCount(uint32_t count);

            uint32_t GetMaxCoverageAngle() const { return m_maxCoverageAngle; }
            void SetMaxCoverageAngle(uint32_t angle);
        };

    } // namespace Shapes
} // namespace ClockNet
