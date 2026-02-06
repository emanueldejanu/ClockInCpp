// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#include "StringRim.h"
#include <stdexcept>

namespace ClockNet {
    namespace Shapes {
        namespace Basic {

            StringRim::StringRim()
                : StringRim(Gdiplus::Color::Black, nullptr, DefaultPositionOffset) {
            }

            StringRim::StringRim(const Gdiplus::Color& color, Gdiplus::Font* font, float distanceFromEdge)
                : VectorialRimBase(Gdiplus::Color::Transparent,
                                  color,
                                  DefaultOutlineWidth,
                                  DefaultAngle,
                                  DefaultRepeat,
                                  distanceFromEdge)
                , m_font(nullptr)
                , m_stringFormat(nullptr) {

                m_name = DefaultName;
                m_texts.push_back(L"•");

                if (font) {
                    m_font = font->Clone();
                } else {
                    // Create default font (Arial, 7pt)
                    Gdiplus::FontFamily fontFamily(L"Arial");
                    m_font = new Gdiplus::Font(&fontFamily, 7.0f, Gdiplus::FontStyleRegular, Gdiplus::UnitPoint);
                }

                // Create string format
                m_stringFormat = new Gdiplus::StringFormat(Gdiplus::StringFormatFlagsNoWrap);
                m_stringFormat->SetAlignment(Gdiplus::StringAlignmentCenter);
                m_stringFormat->SetLineAlignment(Gdiplus::StringAlignmentCenter);
            }

            StringRim::~StringRim() {
                if (m_font) {
                    delete m_font;
                    m_font = nullptr;
                }
                if (m_stringFormat) {
                    delete m_stringFormat;
                    m_stringFormat = nullptr;
                }
            }

            void StringRim::SetTexts(const std::vector<std::wstring>& texts) {
                if (texts.empty())
                    throw std::invalid_argument("Texts array cannot be empty");

                m_texts = texts;
                if (Changed)
                    Changed();
            }

            void StringRim::SetFont(Gdiplus::Font* font) {
                if (m_font && m_font != font) {
                    delete m_font;
                }
                m_font = font;
                if (Changed)
                    Changed();
            }

            bool StringRim::OnBeforeDraw(ClockDrawingContext& context) {
                if (!m_font)
                    return false;

                if (m_texts.empty())
                    return false;

                if (m_fillColor.GetValue() == 0)
                    return false;

                return VectorialRimBase::OnBeforeDraw(context);
            }

            void StringRim::DrawItem(Gdiplus::Graphics* graphics, int index) {
                int actualIndex = index % m_texts.size();
                const std::wstring& text = m_texts[actualIndex];

                if (!text.empty()) {
                    Gdiplus::RectF boundingBox;
                    Gdiplus::RectF layoutRect(0, 0, 10000, 10000);

                    graphics->MeasureString(text.c_str(), -1, m_font, layoutRect, m_stringFormat, &boundingBox);

                    float textX = -boundingBox.Width / 2.0f;
                    float textY = -boundingBox.Height / 2.0f;
                    Gdiplus::PointF textPosition(textX, textY);

                    try {
                        Gdiplus::RectF layoutRectangle(textPosition, Gdiplus::SizeF(boundingBox.Width, boundingBox.Height));
                        graphics->DrawString(text.c_str(), -1, m_font, layoutRectangle, m_stringFormat, GetBrush());
                    }
                    catch (...) {
                        // When the dimension of the clock is less than 0, an exception might be raised.
                        // We just ignore it - the text won't be displayed, but at very small sizes it's not visible anyway.
                    }
                }
            }

        } // namespace Basic
    } // namespace Shapes
} // namespace ClockNet
