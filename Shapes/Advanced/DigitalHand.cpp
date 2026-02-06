// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#include "DigitalHand.h"
#include <sstream>
#include <iomanip>

namespace ClockNet {
    namespace Shapes {
        namespace Advanced {

            DigitalHand::DigitalHand()
                : DigitalHand(Gdiplus::Color::Black, nullptr) {
            }

            DigitalHand::DigitalHand(const Gdiplus::Color& color, Gdiplus::Font* font)
                : VectorialHandBase(Gdiplus::Color::Transparent, color)
                , m_font(nullptr)
                , m_stringFormat(nullptr)
                , m_verticalLocation(DefaultVerticalLocation)
                , m_format(DefaultFormat) {

                m_name = DefaultName;

                if (font) {
                    m_font = font->Clone();
                } else {
                    // Create default font (Arial, 3pt)
                    Gdiplus::FontFamily fontFamily(L"Arial");
                    m_font = new Gdiplus::Font(&fontFamily, 3.0f, Gdiplus::FontStyleRegular, Gdiplus::UnitPoint);
                }

                m_stringFormat = new Gdiplus::StringFormat();
                m_stringFormat->SetAlignment(Gdiplus::StringAlignmentCenter);
                m_stringFormat->SetLineAlignment(Gdiplus::StringAlignmentCenter);
                m_stringFormat->SetTrimming(Gdiplus::StringTrimmingNone);
            }

            DigitalHand::~DigitalHand() {
                if (m_font) {
                    delete m_font;
                    m_font = nullptr;
                }
                if (m_stringFormat) {
                    delete m_stringFormat;
                    m_stringFormat = nullptr;
                }
            }

            void DigitalHand::SetFont(Gdiplus::Font* font) {
                if (m_font && m_font != font) {
                    delete m_font;
                }
                m_font = font;
                if (Changed)
                    Changed();
            }

            void DigitalHand::SetVerticalLocation(float verticalLocation) {
                if (m_verticalLocation == verticalLocation)
                    return;

                m_verticalLocation = verticalLocation;
                if (Changed)
                    Changed();
            }

            void DigitalHand::SetFormat(const std::wstring& format) {
                m_format = format;
                if (Changed)
                    Changed();
            }

            bool DigitalHand::OnBeforeDraw(ClockDrawingContext& context) {
                if (!m_font)
                    return false;

                if (m_fillColor.GetValue() == 0)
                    return false;

                return VectorialHandBase::OnBeforeDraw(context);
            }

            void DigitalHand::OnDraw(ClockDrawingContext& context) {
                // Format time string
                std::wstringstream ss;
                ss << std::setfill(L'0') << std::setw(2) << context.Time.wHour << L":"
                   << std::setw(2) << context.Time.wMinute << L":"
                   << std::setw(2) << context.Time.wSecond;
                std::wstring text = ss.str();

                if (!text.empty()) {
                    Gdiplus::RectF boundingBox;
                    context.Graphics->MeasureString(text.c_str(), -1, m_font, Gdiplus::PointF(0, 0), m_stringFormat, &boundingBox);

                    float textX = -boundingBox.Width / 2.0f;
                    float textY = m_verticalLocation;
                    Gdiplus::RectF textRectangle(textX, textY, boundingBox.Width, boundingBox.Height);

                    context.Graphics->DrawString(text.c_str(), -1, m_font, textRectangle, m_stringFormat, GetBrush());
                }
            }

            bool DigitalHand::HitTest(const Gdiplus::PointF& point, const SYSTEMTIME& time) {
                return false;
            }

        } // namespace Advanced
    } // namespace Shapes
} // namespace ClockNet
