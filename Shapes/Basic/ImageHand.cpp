// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#include "ImageHand.h"

namespace ClockNet {
    namespace Shapes {
        namespace Basic {

            ImageHand::ImageHand()
                : ImageHand(nullptr, Gdiplus::PointF(), DefaultLength) {
            }

            ImageHand::ImageHand(Gdiplus::Image* image, const Gdiplus::PointF& origin, float length)
                : HandBase()
                , m_image(image)
                , m_origin(origin) {
                m_name = DefaultName;
            }

            ImageHand::~ImageHand() {
                // Note: Image is not owned by this class, don't delete it
            }

            void ImageHand::SetImage(Gdiplus::Image* image) {
                m_image = image;
                if (Changed)
                    Changed();
            }

            void ImageHand::SetOrigin(const Gdiplus::PointF& origin) {
                m_origin = origin;
                if (Changed)
                    Changed();
            }

            bool ImageHand::OnBeforeDraw(ClockDrawingContext& context) {
                if (!m_image)
                    return false;

                return HandBase::OnBeforeDraw(context);
            }

            void ImageHand::OnDraw(ClockDrawingContext& context) {
                if (m_origin.Y != 0 && m_length > 0) {
                    float scaleFactor = m_length / m_origin.Y;
                    context.Graphics->ScaleTransform(scaleFactor, scaleFactor);
                }

                context.Graphics->DrawImage(m_image,
                    -m_origin.X,
                    -m_origin.Y,
                    (Gdiplus::REAL)m_image->GetWidth(),
                    (Gdiplus::REAL)m_image->GetHeight());
            }

            bool ImageHand::HitTest(const Gdiplus::PointF& point, const SYSTEMTIME& time) {
                return false;
            }

        } // namespace Basic
    } // namespace Shapes
} // namespace ClockNet
