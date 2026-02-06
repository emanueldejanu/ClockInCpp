// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#include "RimBase.h"
#include "RimDrawingCoordinator.h"

namespace ClockNet {
    namespace Shapes {

        RimBase::RimBase()
            : RimBase(DefaultAngle, DefaultRepeat, DefaultDistanceFromEdge) {
        }

        RimBase::RimBase(float angle, bool repeat, float distanceFromEdge)
            : m_angle(angle)
            , m_repeat(repeat)
            , m_distanceFromEdge(distanceFromEdge)
            , m_offsetAngle(DefaultOffsetAngle)
            , m_skipIndex(DefaultSkipIndex)
            , m_orientation(RimItemOrientation::FaceIn)
            , m_maxCoverageCount(DefaultMaxCoverageCount)
            , m_maxCoverageAngle(DefaultMaxCoverageAngle) {
        }

        void RimBase::SetDistanceFromEdge(float distance) {
            m_distanceFromEdge = distance;
            InvalidateLayout();
            if (Changed)
                Changed();
        }

        void RimBase::SetAngle(float angle) {
            if (angle <= 0)
                return;
            m_angle = angle;
            if (Changed)
                Changed();
        }

        void RimBase::SetOffsetAngle(float angle) {
            if (angle < 0)
                return;
            m_offsetAngle = angle;
            if (Changed)
                Changed();
        }

        void RimBase::SetSkipIndex(int skip) {
            m_skipIndex = skip;
            if (Changed)
                Changed();
        }

        void RimBase::SetRepeat(bool repeat) {
            m_repeat = repeat;
            if (Changed)
                Changed();
        }

        void RimBase::SetOrientation(RimItemOrientation orientation) {
            m_orientation = orientation;
            if (Changed)
                Changed();
        }

        void RimBase::SetMaxCoverageCount(uint32_t count) {
            m_maxCoverageCount = count;
            if (Changed)
                Changed();
        }

        void RimBase::SetMaxCoverageAngle(uint32_t angle) {
            m_maxCoverageAngle = angle;
            if (Changed)
                Changed();
        }

        void RimBase::OnDraw(ClockDrawingContext& context) {
            RimDrawingCoordinator coordinator(context.Graphics);
            coordinator.Diameter = context.Diameter;
            coordinator.Angle = m_angle;
            coordinator.OffsetAngle = m_offsetAngle;
            coordinator.MaxCoverageCount = m_maxCoverageCount;
            coordinator.MaxCoverageAngle = m_maxCoverageAngle;
            coordinator.Repeat = m_repeat;
            coordinator.SkipIndex = m_skipIndex;
            coordinator.DistanceFromEdge = m_distanceFromEdge;
            coordinator.Orientation = m_orientation;

            while (coordinator.MoveNext()) {
                DrawItem(coordinator.Graphics, coordinator.Index);
            }
        }

    } // namespace Shapes
} // namespace ClockNet
