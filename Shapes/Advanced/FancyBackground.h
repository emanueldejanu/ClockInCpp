// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#pragma once
#include "../VectorialShapeBase.h"
#include <memory>

namespace ClockNet {
    namespace Shapes {
        namespace Advanced {

            /// <summary>
            /// Fancy gradient background with multiple rims
            /// </summary>
            class FancyBackground : public VectorialShapeBase {
            private:
                float m_outerRimWidth;
                float m_innerRimWidth;

                Gdiplus::RectF m_outerRimRectangle;
                Gdiplus::RectF m_innerRimRectangle;
                Gdiplus::RectF m_faceRectangle;

                std::unique_ptr<Gdiplus::LinearGradientBrush> m_outerRimBrush;
                std::unique_ptr<Gdiplus::LinearGradientBrush> m_innerRimBrush;

            protected:
                void CalculateCache(ClockDrawingContext& context) override;
                bool OnBeforeDraw(ClockDrawingContext& context) override;
                void OnDraw(ClockDrawingContext& context) override;
                Gdiplus::Pen* CreatePen() override;
                Gdiplus::Brush* CreateBrush() override;
                void DisposeDrawingTools() override;

                Gdiplus::LinearGradientBrush* GetOuterRimBrush();
                Gdiplus::LinearGradientBrush* GetInnerRimBrush();

            public:
                static constexpr float DefaultOuterRimWidth = 10.0f;
                static constexpr float DefaultInnerRimWidth = 2.0f;
                static constexpr const wchar_t* DefaultName = L"Fancy Background";

                FancyBackground();

                float GetOuterRimWidth() const { return m_outerRimWidth; }
                void SetOuterRimWidth(float width);

                float GetInnerRimWidth() const { return m_innerRimWidth; }
                void SetInnerRimWidth(float width);
            };

        } // namespace Advanced
    } // namespace Shapes
} // namespace ClockNet
