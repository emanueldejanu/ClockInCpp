// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#include "ImageBackground.h"

namespace ClockNet {
    namespace Shapes {
        namespace Basic {

            ImageBackground::ImageBackground()
                : ImageBackground(nullptr, Gdiplus::PointF()) {
            }

            ImageBackground::ImageBackground(Gdiplus::Image* image, const Gdiplus::PointF& pinLocation)
                : ShapeBase()
                , m_image(image)
                , m_pinLocation(pinLocation) {
                m_name = DefaultName;
            }

            ImageBackground::~ImageBackground() {
                // Note: Image is not owned by this class, don't delete it
            }

            void ImageBackground::SetImage(Gdiplus::Image* image) {
                if (m_image == image)
                    return;

                m_image = image;
                if (Changed)
                    Changed();
            }

            void ImageBackground::SetPinLocation(const Gdiplus::PointF& pinLocation) {
                if (m_pinLocation.X == pinLocation.X && m_pinLocation.Y == pinLocation.Y)
                    return;

                m_pinLocation = pinLocation;
                if (Changed)
                    Changed();
            }

            bool ImageBackground::OnBeforeDraw(ClockDrawingContext& context) {
                if (!m_image)
                    return false;

                return ShapeBase::OnBeforeDraw(context);
            }

            void ImageBackground::OnDraw(ClockDrawingContext& context) {
                float height = 100.0f;

                if (m_pinLocation.Y != 0 && height > 0) {
                    float scaleFactor = height / m_pinLocation.Y;
                    context.Graphics->ScaleTransform(scaleFactor, scaleFactor);
                }

                context.Graphics->DrawImage(m_image,
                    -m_pinLocation.X,
                    -m_pinLocation.Y,
                    (Gdiplus::REAL)m_image->GetWidth(),
                    (Gdiplus::REAL)m_image->GetHeight());
            }

        } // namespace Basic
    } // namespace Shapes
} // namespace ClockNet
