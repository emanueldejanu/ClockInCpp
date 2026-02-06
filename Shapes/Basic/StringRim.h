// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#pragma once
#include "../VectorialRimBase.h"
#include <string>
#include <vector>

namespace ClockNet {
    namespace Shapes {
        namespace Basic {

            /// <summary>
            /// Draws text items around the rim of the clock
            /// </summary>
            class StringRim : public VectorialRimBase {
            private:
                std::vector<std::wstring> m_texts;
                Gdiplus::Font* m_font;
                Gdiplus::StringFormat* m_stringFormat;

            protected:
                bool OnBeforeDraw(ClockDrawingContext& context) override;
                void DrawItem(Gdiplus::Graphics* graphics, int index) override;

            public:
                static constexpr const wchar_t* DefaultName = L"String Rim";
                static constexpr float DefaultPositionOffset = 7.0f;

                StringRim();
                StringRim(const Gdiplus::Color& color, Gdiplus::Font* font, float distanceFromEdge);
                virtual ~StringRim();

                const std::vector<std::wstring>& GetTexts() const { return m_texts; }
                void SetTexts(const std::vector<std::wstring>& texts);

                const Gdiplus::Font* GetFont() const { return m_font; }
                void SetFont(Gdiplus::Font* font);
            };

        } // namespace Basic
    } // namespace Shapes
} // namespace ClockNet
