// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#include "RimDrawingCoordinator.h"
#include <gdiplus.h>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace ClockNet {
    namespace Shapes {

        RimDrawingCoordinator::RimDrawingCoordinator(Gdiplus::Graphics* graphics)
            : m_graphics(graphics)
            , m_diameter(200.0f)
            , m_angle(6.0f)
            , m_offsetAngle(0.0f)
            , m_maxCoverageCount(0)
            , m_maxCoverageAngle(360)
            , m_repeat(true)
            , m_skipIndex(0)
            , m_distanceFromEdge(0.0f)
            , m_orientation(RimItemOrientation::FaceIn)
            , m_currentIndex(-1)
            , m_currentAngle(0.0f)
            , m_isFirst(true) {

            Graphics = graphics;
            Index = 0;

            // Save original matrix
            graphics->GetTransform(&m_originalMatrix);
        }

        RimDrawingCoordinator::~RimDrawingCoordinator() {
            // Restore original matrix
            if (m_graphics) {
                m_graphics->SetTransform(&m_originalMatrix);
            }
        }

        bool RimDrawingCoordinator::MoveNext() {
            if (m_isFirst) {
                m_isFirst = false;
                m_currentIndex = 0;
                m_currentAngle = OffsetAngle;
            } else {
                m_currentIndex++;
                m_currentAngle += Angle;
            }

            // Check coverage limits
            if (MaxCoverageCount > 0 && m_currentIndex >= (int)MaxCoverageCount) {
                return false;
            }

            if (m_currentAngle >= MaxCoverageAngle) {
                return false;
            }

            if (!Repeat && m_currentAngle >= 360.0f) {
                return false;
            }

            // Skip indices if needed
            if (SkipIndex > 0 && m_currentIndex % SkipIndex == 0) {
                return MoveNext(); // Recursive skip
            }

            // Restore original matrix
            m_graphics->SetTransform(&m_originalMatrix);

            // Calculate position
            float radius = Diameter / 2.0f;
            float distance = radius * (DistanceFromEdge / 100.0f);
            float positionRadius = radius - distance;

            // Translate to position around rim
            float angleRad = (m_currentAngle - 90.0f) * (float)M_PI / 180.0f;
            float x = positionRadius * cos(angleRad);
            float y = positionRadius * sin(angleRad);

            m_graphics->TranslateTransform(x, y);

            // Apply orientation rotation
            switch (Orientation) {
                case RimItemOrientation::FaceIn:
                    m_graphics->RotateTransform(m_currentAngle);
                    break;

                case RimItemOrientation::FaceOut:
                    m_graphics->RotateTransform(m_currentAngle + 180.0f);
                    break;

                case RimItemOrientation::Vertical:
                    // No rotation
                    break;
            }

            Index = m_currentIndex;
            return true;
        }

        void RimDrawingCoordinator::Reset() {
            m_currentIndex = -1;
            m_currentAngle = 0.0f;
            m_isFirst = true;
        }

    } // namespace Shapes
} // namespace ClockNet
