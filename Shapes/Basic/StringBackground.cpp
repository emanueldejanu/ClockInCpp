// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#include "StringBackground.h"

namespace ClockNet {
    namespace Shapes {
        namespace Basic {

            StringBackground::StringBackground()
                : VectorialShapeBase(Gdiplus::Color::Transparent, Gdiplus::Color::Black, 1.0f)
                , m_text(DefaultText)
                , m_font(nullptr)
                , m_maxWidth(DefaultMaxWidth)
                , m_location(0.0f, 0.0f)
                , m_stringFormat(nullptr)
                , m_recalculateNeeded(true)
                , m_textRectangle() {

                m_name = DefaultName;

                // Create default font (Arial, 2.25pt)
                Gdiplus::FontFamily fontFamily(L"Arial");
                m_font = new Gdiplus::Font(&fontFamily, 2.25f, Gdiplus::FontStyleRegular, Gdiplus::UnitPoint);

                // Create string format
                m_stringFormat = new Gdiplus::StringFormat();
                m_stringFormat->SetAlignment(Gdiplus::StringAlignmentCenter);
                m_stringFormat->SetLineAlignment(Gdiplus::StringAlignmentCenter);
                m_stringFormat->SetTrimming(Gdiplus::StringTrimmingNone);
            }

            StringBackground::~StringBackground() {
                if (m_font) {
                    delete m_font;
                    m_font = nullptr;
                }
                if (m_stringFormat) {
                    delete m_stringFormat;
                    m_stringFormat = nullptr;
                }
            }

            void StringBackground::SetText(const std::wstring& text) {
                m_text = text;
                m_recalculateNeeded = true;
                if (Changed)
                    Changed();
            }

            void StringBackground::SetFont(Gdiplus::Font* font) {
                if (m_font && m_font != font) {
                    delete m_font;
                }
                m_font = font;
                m_recalculateNeeded = true;
                if (Changed)
                    Changed();
            }

            void StringBackground::SetMaxWidth(float maxWidth) {
                m_maxWidth = maxWidth;
                m_recalculateNeeded = true;
                if (Changed)
                    Changed();
            }

            void StringBackground::SetLocation(const Gdiplus::PointF& location) {
                m_location = location;
                m_recalculateNeeded = true;
                if (Changed)
                    Changed();
            }

            void StringBackground::CalculateDimensions(Gdiplus::Graphics* graphics) {
                if (!m_font || m_text.empty())
                    return;

                Gdiplus::RectF layoutRect(0, 0, m_maxWidth, 1000);
                Gdiplus::RectF boundingBox;

                graphics->MeasureString(m_text.c_str(), -1, m_font, layoutRect, m_stringFormat, &boundingBox);

                float textX = m_location.X - boundingBox.Width / 2.0f;
                float textY = m_location.Y - boundingBox.Height / 2.0f;

                m_textRectangle = Gdiplus::RectF(textX, textY, boundingBox.Width, boundingBox.Height);
                m_recalculateNeeded = false;
            }

            bool StringBackground::OnBeforeDraw(ClockDrawingContext& context) {
                if (!m_font)
                    return false;

                if (m_text.empty())
                    return false;

                if (m_fillColor.GetValue() == 0)
                    return false;

                return VectorialShapeBase::OnBeforeDraw(context);
            }

            void StringBackground::OnDraw(ClockDrawingContext& context) {
                if (m_recalculateNeeded)
                    CalculateDimensions(context.Graphics);

                context.Graphics->DrawString(m_text.c_str(), -1, m_font, m_textRectangle, m_stringFormat, GetBrush());
            }

        } // namespace Basic
    } // namespace Shapes
} // namespace ClockNet
