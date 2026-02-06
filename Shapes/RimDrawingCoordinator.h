// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#pragma once
#include <windows.h>
#include <gdiplus.h>
#include <cstdint>
#include "RimItemOrientation.h"

namespace ClockNet {
    namespace Shapes {

        /// <summary>
        /// Coordinates the drawing of rim items around the clock
        /// </summary>
        class RimDrawingCoordinator {
        private:
            Gdiplus::Graphics* m_graphics;
            Gdiplus::Matrix m_originalMatrix;
            float m_diameter;
            float m_angle;
            float m_offsetAngle;
            uint32_t m_maxCoverageCount;
            uint32_t m_maxCoverageAngle;
            bool m_repeat;
            int m_skipIndex;
            float m_distanceFromEdge;
            RimItemOrientation m_orientation;

            int m_currentIndex;
            float m_currentAngle;
            bool m_isFirst;

        public:
            RimDrawingCoordinator(Gdiplus::Graphics* graphics);
            ~RimDrawingCoordinator();

            // Properties
            float Diameter;
            float Angle;
            float OffsetAngle;
            uint32_t MaxCoverageCount;
            uint32_t MaxCoverageAngle;
            bool Repeat;
            int SkipIndex;
            float DistanceFromEdge;
            RimItemOrientation Orientation;

            // Iterator methods
            bool MoveNext();
            void Reset();

            // Current state
            Gdiplus::Graphics* Graphics;
            int Index;
        };

    } // namespace Shapes
} // namespace ClockNet
