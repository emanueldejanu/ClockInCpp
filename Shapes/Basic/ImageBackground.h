// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#pragma once
#include "../ShapeBase.h"

namespace ClockNet {
    namespace Shapes {
        namespace Basic {

            /// <summary>
            /// A background shape representing a bitmap image
            /// </summary>
            class ImageBackground : public ShapeBase {
            private:
                Gdiplus::Image* m_image;
                Gdiplus::PointF m_pinLocation;

            protected:
                bool OnBeforeDraw(ClockDrawingContext& context) override;
                void OnDraw(ClockDrawingContext& context) override;

            public:
                static constexpr const wchar_t* DefaultName = L"Image Background";

                ImageBackground();
                ImageBackground(Gdiplus::Image* image, const Gdiplus::PointF& pinLocation);
                virtual ~ImageBackground();

                Gdiplus::Image* GetImage() const { return m_image; }
                void SetImage(Gdiplus::Image* image);

                const Gdiplus::PointF& GetPinLocation() const { return m_pinLocation; }
                void SetPinLocation(const Gdiplus::PointF& pinLocation);
            };

        } // namespace Basic
    } // namespace Shapes
} // namespace ClockNet
