// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#pragma once
#include "../VectorialHandBase.h"
#include <string>

namespace ClockNet {
    namespace Shapes {
        namespace Advanced {

            /// <summary>
            /// Represents a digital clock hand that displays the current time as text
            /// </summary>
            class DigitalHand : public VectorialHandBase {
            private:
                Gdiplus::Font* m_font;
                Gdiplus::StringFormat* m_stringFormat;
                float m_verticalLocation;
                std::wstring m_format;

            protected:
                bool OnBeforeDraw(ClockDrawingContext& context) override;
                void OnDraw(ClockDrawingContext& context) override;

            public:
                static constexpr float DefaultVerticalLocation = 12.0f;
                static constexpr const wchar_t* DefaultFormat = L"HH:mm:ss";
                static constexpr const wchar_t* DefaultName = L"Digital Hand";

                DigitalHand();
                DigitalHand(const Gdiplus::Color& color, Gdiplus::Font* font);
                virtual ~DigitalHand();

                const Gdiplus::Font* GetFont() const { return m_font; }
                void SetFont(Gdiplus::Font* font);

                float GetVerticalLocation() const { return m_verticalLocation; }
                void SetVerticalLocation(float verticalLocation);

                const std::wstring& GetFormat() const { return m_format; }
                void SetFormat(const std::wstring& format);

                bool HitTest(const Gdiplus::PointF& point, const SYSTEMTIME& time) override;
            };

        } // namespace Advanced
    } // namespace Shapes
} // namespace ClockNet
