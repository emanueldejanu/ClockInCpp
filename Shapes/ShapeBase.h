// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#pragma once
#include "IShape.h"
#include "ClockDrawingContext.h"
#include <string>

namespace ClockNet {
    namespace Shapes {

        /// <summary>
        /// Provides common functionality for all shapes
        /// </summary>
        class ShapeBase : public IShape {
        protected:
            std::wstring m_name;
            bool m_visible;
            bool m_isCacheValid;

            // Virtual methods for derived classes
            virtual bool OnBeforeDraw(ClockDrawingContext& context);
            virtual void CalculateCache(ClockDrawingContext& context);
            virtual void OnDraw(ClockDrawingContext& context) = 0;
            virtual void OnAfterDraw(ClockDrawingContext& context);
            virtual void DisposeDrawingTools();

            void InvalidateLayout();

        public:
            ShapeBase();
            virtual ~ShapeBase() = default;

            // IShape implementation
            std::wstring GetName() const override { return m_name; }
            void SetName(const std::wstring& name) override;

            bool IsVisible() const override { return m_visible; }
            void SetVisible(bool visible) override;

            void Draw(ClockDrawingContext& context) override;
        };

    } // namespace Shapes
} // namespace ClockNet
