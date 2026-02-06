// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#include "ImageRim.h"

namespace ClockNet {
    namespace Shapes {
        namespace Basic {

            ImageRim::ImageRim()
                : ImageRim(nullptr, Gdiplus::PointF(), DefaultAngle, DefaultRepeat, DefaultDistanceFromEdge) {
            }

            ImageRim::ImageRim(Gdiplus::Image* image)
                : ImageRim(image, Gdiplus::PointF(), DefaultAngle, DefaultRepeat, DefaultDistanceFromEdge) {
            }

            ImageRim::ImageRim(Gdiplus::Image* image, const Gdiplus::PointF& location, float angle, bool repeat, float distanceFromEdge)
                : RimBase(angle, repeat, distanceFromEdge)
                , m_image(image)
                , m_location(location) {
                m_name = DefaultName;
            }

            ImageRim::~ImageRim() {
                // Note: Image is not owned by this class, don't delete it
            }

            void ImageRim::SetImage(Gdiplus::Image* image) {
                m_image = image;
                if (Changed)
                    Changed();
            }

            void ImageRim::SetLocation(const Gdiplus::PointF& location) {
                m_location = location;
                if (Changed)
                    Changed();
            }

            bool ImageRim::OnBeforeDraw(ClockDrawingContext& context) {
                if (!m_image)
                    return false;

                return RimBase::OnBeforeDraw(context);
            }

            void ImageRim::DrawItem(Gdiplus::Graphics* graphics, int index) {
                graphics->DrawImage(m_image,
                    m_location.X,
                    m_location.Y,
                    (Gdiplus::REAL)m_image->GetWidth(),
                    (Gdiplus::REAL)m_image->GetHeight());
            }

        } // namespace Basic
    } // namespace Shapes
} // namespace ClockNet
