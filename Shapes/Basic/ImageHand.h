// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#pragma once
#include "../HandBase.h"

namespace ClockNet {
    namespace Shapes {
        namespace Basic {

            /// <summary>
            /// Displays an image hand in the analog clock control
            /// </summary>
            class ImageHand : public HandBase {
            private:
                Gdiplus::Image* m_image;
                Gdiplus::PointF m_origin;

            protected:
                bool OnBeforeDraw(ClockDrawingContext& context) override;
                void OnDraw(ClockDrawingContext& context) override;

            public:
                static constexpr const wchar_t* DefaultName = L"Image Hand";

                ImageHand();
                ImageHand(Gdiplus::Image* image, const Gdiplus::PointF& origin, float length);
                virtual ~ImageHand();

                Gdiplus::Image* GetImage() const { return m_image; }
                void SetImage(Gdiplus::Image* image);

                const Gdiplus::PointF& GetOrigin() const { return m_origin; }
                void SetOrigin(const Gdiplus::PointF& origin);

                bool HitTest(const Gdiplus::PointF& point, const SYSTEMTIME& time) override;
            };

        } // namespace Basic
    } // namespace Shapes
} // namespace ClockNet
