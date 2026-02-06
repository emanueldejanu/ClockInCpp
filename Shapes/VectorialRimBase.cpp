// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#include "VectorialRimBase.h"

namespace ClockNet {
    namespace Shapes {

        VectorialRimBase::VectorialRimBase()
            : VectorialRimBase(Gdiplus::Color(), Gdiplus::Color::Black,
                             DefaultOutlineWidth, DefaultAngle, DefaultRepeat, DefaultDistanceFromEdge) {
        }

        VectorialRimBase::VectorialRimBase(const Gdiplus::Color& outlineColor,
                                         const Gdiplus::Color& fillColor,
                                         float outlineWidth,
                                         float angle,
                                         bool repeat,
                                         float distanceFromEdge)
            : RimBase(angle, repeat, distanceFromEdge)
            , m_outlineColor(outlineColor)
            , m_fillColor(fillColor)
            , m_outlineWidth(outlineWidth) {
        }

        VectorialRimBase::~VectorialRimBase() {
            DisposeDrawingTools();
        }

        void VectorialRimBase::SetOutlineColor(const Gdiplus::Color& color) {
            m_outlineColor = color;
            DisposeDrawingTools();
            if (Changed)
                Changed();
        }

        void VectorialRimBase::SetFillColor(const Gdiplus::Color& color) {
            m_fillColor = color;
            DisposeDrawingTools();
            if (Changed)
                Changed();
        }

        void VectorialRimBase::SetOutlineWidth(float width) {
            m_outlineWidth = width;
            if (m_pen) {
                m_pen->SetWidth(width);
            }
            if (Changed)
                Changed();
        }

        Gdiplus::Pen* VectorialRimBase::CreatePen() {
            return new Gdiplus::Pen(m_outlineColor, m_outlineWidth);
        }

        Gdiplus::Brush* VectorialRimBase::CreateBrush() {
            return new Gdiplus::SolidBrush(m_fillColor);
        }

        Gdiplus::Pen* VectorialRimBase::GetPen() {
            if (!m_pen) {
                m_pen.reset(CreatePen());
            }
            return m_pen.get();
        }

        Gdiplus::Brush* VectorialRimBase::GetBrush() {
            if (!m_brush) {
                m_brush.reset(CreateBrush());
            }
            return m_brush.get();
        }

        void VectorialRimBase::DisposeDrawingTools() {
            m_pen.reset();
            m_brush.reset();
        }

    } // namespace Shapes
} // namespace ClockNet
