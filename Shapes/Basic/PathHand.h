// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#pragma once
#include "../VectorialHandBase.h"
#include <memory>

namespace ClockNet {
    namespace Shapes {
        namespace Basic {

            /// <summary>
            /// A hand that draws a complex vectorial path defined by GraphicsPath
            /// </summary>
            class PathHand : public VectorialHandBase {
            protected:
                std::unique_ptr<Gdiplus::GraphicsPath> m_path;

                bool OnBeforeDraw(ClockDrawingContext& context) override;
                void OnDraw(ClockDrawingContext& context) override;

            public:
                static constexpr const wchar_t* DefaultName = L"Path Hand";

                PathHand();
                PathHand(Gdiplus::GraphicsPath* path,
                        const Gdiplus::Color& outlineColor,
                        const Gdiplus::Color& fillColor,
                        float length,
                        float lineWidth);
                virtual ~PathHand();

                bool HitTest(const Gdiplus::PointF& point, const SYSTEMTIME& time) override;

                // Access to path for derived classes
                Gdiplus::GraphicsPath* GetPath() { return m_path.get(); }
            };

        } // namespace Basic
    } // namespace Shapes
} // namespace ClockNet
