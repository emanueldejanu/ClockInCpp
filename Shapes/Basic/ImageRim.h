// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#pragma once
#include "../RimBase.h"

namespace ClockNet {
    namespace Shapes {
        namespace Basic {

            /// <summary>
            /// A rim shape class that draws bitmap images for items
            /// </summary>
            class ImageRim : public RimBase {
            private:
                Gdiplus::Image* m_image;
                Gdiplus::PointF m_location;

            protected:
                bool OnBeforeDraw(ClockDrawingContext& context) override;
                void DrawItem(Gdiplus::Graphics* graphics, int index) override;

            public:
                static constexpr const wchar_t* DefaultName = L"Image Rim";

                ImageRim();
                ImageRim(Gdiplus::Image* image);
                ImageRim(Gdiplus::Image* image, const Gdiplus::PointF& location, float angle, bool repeat, float distanceFromEdge);
                virtual ~ImageRim();

                Gdiplus::Image* GetImage() const { return m_image; }
                void SetImage(Gdiplus::Image* image);

                const Gdiplus::PointF& GetLocation() const { return m_location; }
                void SetLocation(const Gdiplus::PointF& location);
            };

        } // namespace Basic
    } // namespace Shapes
} // namespace ClockNet
