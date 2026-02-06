// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#pragma once
#include "../VectorialShapeBase.h"
#include <string>

namespace ClockNet {
    namespace Shapes {
        namespace Basic {

            /// <summary>
            /// Draws text on the background of the clock
            /// </summary>
            class StringBackground : public VectorialShapeBase {
            private:
                std::wstring m_text;
                Gdiplus::Font* m_font;
                float m_maxWidth;
                Gdiplus::PointF m_location;
                Gdiplus::StringFormat* m_stringFormat;
                bool m_recalculateNeeded;
                Gdiplus::RectF m_textRectangle;

                void CalculateDimensions(Gdiplus::Graphics* graphics);

            protected:
                bool OnBeforeDraw(ClockDrawingContext& context) override;
                void OnDraw(ClockDrawingContext& context) override;

            public:
                static constexpr const wchar_t* DefaultName = L"String Background";
                static constexpr const wchar_t* DefaultText = L"Dust in the Wind";
                static constexpr float DefaultMaxWidth = 100.0f;

                StringBackground();
                virtual ~StringBackground();

                const std::wstring& GetText() const { return m_text; }
                void SetText(const std::wstring& text);

                const Gdiplus::Font* GetFont() const { return m_font; }
                void SetFont(Gdiplus::Font* font);

                float GetMaxWidth() const { return m_maxWidth; }
                void SetMaxWidth(float maxWidth);

                const Gdiplus::PointF& GetLocation() const { return m_location; }
                void SetLocation(const Gdiplus::PointF& location);
            };

        } // namespace Basic
    } // namespace Shapes
} // namespace ClockNet
