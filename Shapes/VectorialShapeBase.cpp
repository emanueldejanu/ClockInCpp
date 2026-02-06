// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#include "VectorialShapeBase.h"

namespace ClockNet {
    namespace Shapes {

        VectorialShapeBase::VectorialShapeBase()
            : VectorialShapeBase(Gdiplus::Color(), Gdiplus::Color(65, 105, 225), 0.3f) {  // RoyalBlue default
        }

        VectorialShapeBase::VectorialShapeBase(const Gdiplus::Color& outlineColor,
                                               const Gdiplus::Color& fillColor,
                                               float outlineWidth)
            : m_outlineColor(outlineColor)
            , m_fillColor(fillColor)
            , m_outlineWidth(outlineWidth) {
        }

        VectorialShapeBase::~VectorialShapeBase() {
            DisposeDrawingTools();
        }

        void VectorialShapeBase::SetOutlineColor(const Gdiplus::Color& color) {
            m_outlineColor = color;
            DisposeDrawingTools();
            if (Changed)
                Changed();
        }

        void VectorialShapeBase::SetFillColor(const Gdiplus::Color& color) {
            m_fillColor = color;
            DisposeDrawingTools();
            if (Changed)
                Changed();
        }

        void VectorialShapeBase::SetOutlineWidth(float width) {
            m_outlineWidth = width;
            if (m_pen) {
                m_pen->SetWidth(width);
            }
            if (Changed)
                Changed();
        }

        Gdiplus::Pen* VectorialShapeBase::CreatePen() {
            return new Gdiplus::Pen(m_outlineColor, m_outlineWidth);
        }

        Gdiplus::Brush* VectorialShapeBase::CreateBrush() {
            return new Gdiplus::SolidBrush(m_fillColor);
        }

        Gdiplus::Pen* VectorialShapeBase::GetPen() {
            if (!m_pen) {
                m_pen.reset(CreatePen());
            }
            return m_pen.get();
        }

        Gdiplus::Brush* VectorialShapeBase::GetBrush() {
            if (!m_brush) {
                m_brush.reset(CreateBrush());
            }
            return m_brush.get();
        }

        void VectorialShapeBase::DisposeDrawingTools() {
            m_pen.reset();
            m_brush.reset();
        }

    } // namespace Shapes
} // namespace ClockNet
