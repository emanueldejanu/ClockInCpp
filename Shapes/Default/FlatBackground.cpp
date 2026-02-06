// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#include "FlatBackground.h"

namespace ClockNet {
    namespace Shapes {
        namespace Default {

            FlatBackground::FlatBackground()
                : FlatBackground(Gdiplus::Color(), Gdiplus::Color::Black, DefaultRadius, 0.3f) {
            }

            FlatBackground::FlatBackground(const Gdiplus::Color& fillColor)
                : FlatBackground(Gdiplus::Color(), fillColor, DefaultRadius, 0.3f) {
            }

            FlatBackground::FlatBackground(const Gdiplus::Color& fillColor, float radius)
                : FlatBackground(Gdiplus::Color(), fillColor, radius, 0.3f) {
            }

            FlatBackground::FlatBackground(const Gdiplus::Color& outlineColor,
                                         const Gdiplus::Color& fillColor,
                                         float radius,
                                         float lineWidth)
                : VectorialShapeBase(outlineColor, fillColor, lineWidth)
                , m_radius(radius) {
                m_name = DefaultName;
            }

            void FlatBackground::SetRadius(float radius) {
                if (radius < 0)
                    return; // Could throw exception

                m_radius = radius;
                InvalidateLayout();
                if (Changed)
                    Changed();
            }

            Gdiplus::Pen* FlatBackground::CreatePen() {
                auto pen = new Gdiplus::Pen(m_outlineColor, m_outlineWidth);
                pen->SetAlignment(Gdiplus::PenAlignmentInset);
                return pen;
            }

            void FlatBackground::CalculateCache(ClockDrawingContext& context) {
                m_rect = Gdiplus::RectF(-m_radius, -m_radius, m_radius * 2, m_radius * 2);
            }

            bool FlatBackground::OnBeforeDraw(ClockDrawingContext& context) {
                if (m_radius <= 0)
                    return false;

                return VectorialShapeBase::OnBeforeDraw(context);
            }

            void FlatBackground::OnDraw(ClockDrawingContext& context) {
                if (m_fillColor.GetValue() != 0) {
                    context.Graphics->FillEllipse(GetBrush(), m_rect);
                }

                if (m_outlineColor.GetValue() != 0) {
                    context.Graphics->DrawEllipse(GetPen(), m_rect);
                }
            }

        } // namespace Default
    } // namespace Shapes
} // namespace ClockNet
