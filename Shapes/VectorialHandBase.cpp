// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#include "VectorialHandBase.h"

namespace ClockNet {
    namespace Shapes {

        VectorialHandBase::VectorialHandBase()
            : VectorialHandBase(Gdiplus::Color(), Gdiplus::Color::Black, DefaultOutlineWidth, DefaultLength) {
        }

        VectorialHandBase::VectorialHandBase(const Gdiplus::Color& outlineColor,
                                           const Gdiplus::Color& fillColor,
                                           float outlineWidth,
                                           float length)
            : m_outlineColor(outlineColor)
            , m_fillColor(fillColor)
            , m_outlineWidth(outlineWidth) {
            m_length = length;
        }

        VectorialHandBase::~VectorialHandBase() {
            DisposeDrawingTools();
        }

        void VectorialHandBase::SetOutlineColor(const Gdiplus::Color& color) {
            m_outlineColor = color;
            DisposeDrawingTools();
            if (Changed)
                Changed();
        }

        void VectorialHandBase::SetFillColor(const Gdiplus::Color& color) {
            m_fillColor = color;
            DisposeDrawingTools();
            if (Changed)
                Changed();
        }

        void VectorialHandBase::SetOutlineWidth(float width) {
            m_outlineWidth = width;
            if (m_pen) {
                m_pen->SetWidth(width);
            }
            if (Changed)
                Changed();
        }

        Gdiplus::Pen* VectorialHandBase::CreatePen() {
            return new Gdiplus::Pen(m_outlineColor, m_outlineWidth);
        }

        Gdiplus::Brush* VectorialHandBase::CreateBrush() {
            return new Gdiplus::SolidBrush(m_fillColor);
        }

        Gdiplus::Pen* VectorialHandBase::GetPen() {
            if (!m_pen) {
                m_pen.reset(CreatePen());
            }
            return m_pen.get();
        }

        Gdiplus::Brush* VectorialHandBase::GetBrush() {
            if (!m_brush) {
                m_brush.reset(CreateBrush());
            }
            return m_brush.get();
        }

        bool VectorialHandBase::OnBeforeDraw(ClockDrawingContext& context) {
            // Check if at least one color is set
            if (m_fillColor.GetValue() == 0 && m_outlineColor.GetValue() == 0)
                return false;

            return HandBase::OnBeforeDraw(context);
        }

        void VectorialHandBase::DisposeDrawingTools() {
            m_pen.reset();
            m_brush.reset();
        }

    } // namespace Shapes
} // namespace ClockNet
