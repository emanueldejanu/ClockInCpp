// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#pragma once
#include "../VectorialShapeBase.h"

namespace ClockNet {
    namespace Shapes {
        namespace Default {

            /// <summary>
            /// Flat background shape for the clock
            /// </summary>
            class FlatBackground : public VectorialShapeBase {
            private:
                float m_radius;
                Gdiplus::RectF m_rect;

            protected:
                void CalculateCache(ClockDrawingContext& context) override;
                bool OnBeforeDraw(ClockDrawingContext& context) override;
                void OnDraw(ClockDrawingContext& context) override;
                Gdiplus::Pen* CreatePen() override;

            public:
                static constexpr float DefaultRadius = 100.0f;
                static constexpr const wchar_t* DefaultName = L"Flat Background";

                FlatBackground();
                FlatBackground(const Gdiplus::Color& fillColor);
                FlatBackground(const Gdiplus::Color& fillColor, float radius);
                FlatBackground(const Gdiplus::Color& outlineColor,
                             const Gdiplus::Color& fillColor,
                             float radius,
                             float lineWidth);

                float GetRadius() const { return m_radius; }
                void SetRadius(float radius);
            };

        } // namespace Default
    } // namespace Shapes
} // namespace ClockNet
