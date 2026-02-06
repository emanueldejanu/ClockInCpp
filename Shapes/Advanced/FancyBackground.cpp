// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#include "FancyBackground.h"
#include "../../Utils/ColorExtensions.h"

namespace ClockNet {
    namespace Shapes {
        namespace Advanced {

            FancyBackground::FancyBackground()
                : VectorialShapeBase()
                , m_outerRimWidth(DefaultOuterRimWidth)
                , m_innerRimWidth(DefaultInnerRimWidth) {
                m_name = DefaultName;
            }

            void FancyBackground::SetOuterRimWidth(float width) {
                m_outerRimWidth = width;
                InvalidateLayout();
                if (Changed)
                    Changed();
            }

            void FancyBackground::SetInnerRimWidth(float width) {
                m_innerRimWidth = width;
                InvalidateLayout();
                if (Changed)
                    Changed();
            }

            Gdiplus::Pen* FancyBackground::CreatePen() {
                auto pen = new Gdiplus::Pen(m_outlineColor, m_outlineWidth);
                pen->SetAlignment(Gdiplus::PenAlignmentInset);
                return pen;
            }

            Gdiplus::Brush* FancyBackground::CreateBrush() {
                using namespace Utils;
                Gdiplus::Color faceColor = ColorExtensions::ShiftSaturation(m_fillColor, 50.0f);
                Gdiplus::Color faceColor1 = ColorExtensions::ShiftBrightness(faceColor, 100.0f);
                Gdiplus::Color faceColor2 = ColorExtensions::ShiftBrightness(faceColor, -150.0f);
                return new Gdiplus::LinearGradientBrush(m_faceRectangle, faceColor1, faceColor2, 45.0f);
            }

            Gdiplus::LinearGradientBrush* FancyBackground::GetOuterRimBrush() {
                if (!m_outerRimBrush) {
                    using namespace Utils;
                    Gdiplus::Color color1 = ColorExtensions::ShiftBrightness(m_fillColor, 100.0f);
                    Gdiplus::Color color2 = ColorExtensions::ShiftBrightness(m_fillColor, -100.0f);
                    m_outerRimBrush.reset(new Gdiplus::LinearGradientBrush(
                        m_outerRimRectangle, color1, color2, 45.0f));
                }
                return m_outerRimBrush.get();
            }

            Gdiplus::LinearGradientBrush* FancyBackground::GetInnerRimBrush() {
                if (!m_innerRimBrush) {
                    using namespace Utils;
                    Gdiplus::Color color1 = ColorExtensions::ShiftBrightness(m_fillColor, -100.0f);
                    Gdiplus::Color color2 = ColorExtensions::ShiftBrightness(m_fillColor, 100.0f);
                    m_innerRimBrush.reset(new Gdiplus::LinearGradientBrush(
                        m_innerRimRectangle, color1, color2, 45.0f));
                }
                return m_innerRimBrush.get();
            }

            void FancyBackground::CalculateCache(ClockDrawingContext& context) {
                float diameter = context.Diameter;
                float radius = diameter / 2.0f;

                m_outerRimRectangle = Gdiplus::RectF(-radius, -radius, diameter, diameter);
                m_innerRimRectangle = Gdiplus::RectF(
                    m_outerRimRectangle.X + m_outerRimWidth,
                    m_outerRimRectangle.Y + m_outerRimWidth,
                    m_outerRimRectangle.Width - 2 * m_outerRimWidth,
                    m_outerRimRectangle.Height - 2 * m_outerRimWidth);
                m_faceRectangle = Gdiplus::RectF(
                    m_innerRimRectangle.X + m_innerRimWidth,
                    m_innerRimRectangle.Y + m_innerRimWidth,
                    m_innerRimRectangle.Width - 2 * m_innerRimWidth,
                    m_innerRimRectangle.Height - 2 * m_innerRimWidth);

                // Reset brushes so they're recreated with new rectangles
                m_outerRimBrush.reset();
                m_innerRimBrush.reset();
            }

            bool FancyBackground::OnBeforeDraw(ClockDrawingContext& context) {
                if (m_fillColor.GetValue() == 0)
                    return false;
                return VectorialShapeBase::OnBeforeDraw(context);
            }

            void FancyBackground::OnDraw(ClockDrawingContext& context) {
                context.Graphics->FillEllipse(GetOuterRimBrush(), m_outerRimRectangle);
                context.Graphics->FillEllipse(GetInnerRimBrush(), m_innerRimRectangle);
                context.Graphics->FillEllipse(GetBrush(), m_faceRectangle);
            }

            void FancyBackground::DisposeDrawingTools() {
                m_outerRimBrush.reset();
                m_innerRimBrush.reset();
                VectorialShapeBase::DisposeDrawingTools();
            }

        } // namespace Advanced
    } // namespace Shapes
} // namespace ClockNet
