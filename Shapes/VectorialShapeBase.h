// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#pragma once
#include "ShapeBase.h"
#include <windows.h>
#include <gdiplus.h>
#include <memory>

namespace ClockNet {
    namespace Shapes {

        /// <summary>
        /// Base class for vectorial shapes
        /// </summary>
        class VectorialShapeBase : public ShapeBase {
        protected:
            Gdiplus::Color m_outlineColor;
            Gdiplus::Color m_fillColor;
            float m_outlineWidth;

            std::unique_ptr<Gdiplus::Pen> m_pen;
            std::unique_ptr<Gdiplus::Brush> m_brush;

            virtual Gdiplus::Pen* CreatePen();
            virtual Gdiplus::Brush* CreateBrush();

            void DisposeDrawingTools() override;

        public:
            VectorialShapeBase();
            VectorialShapeBase(const Gdiplus::Color& outlineColor, const Gdiplus::Color& fillColor, float outlineWidth);
            virtual ~VectorialShapeBase();

            // Properties
            Gdiplus::Color GetOutlineColor() const { return m_outlineColor; }
            void SetOutlineColor(const Gdiplus::Color& color);

            Gdiplus::Color GetFillColor() const { return m_fillColor; }
            void SetFillColor(const Gdiplus::Color& color);

            float GetOutlineWidth() const { return m_outlineWidth; }
            void SetOutlineWidth(float width);

            // Protected accessors for derived classes
            Gdiplus::Pen* GetPen();
            Gdiplus::Brush* GetBrush();
        };

    } // namespace Shapes
} // namespace ClockNet
