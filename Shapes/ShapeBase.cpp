// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#include "ShapeBase.h"

namespace ClockNet {
    namespace Shapes {

        ShapeBase::ShapeBase()
            : m_visible(true), m_isCacheValid(false) {
        }

        void ShapeBase::SetName(const std::wstring& name) {
            if (m_name == name)
                return;

            m_name = name;
            if (NameChanged)
                NameChanged();
        }

        void ShapeBase::SetVisible(bool visible) {
            m_visible = visible;
            if (Changed)
                Changed();
        }

        void ShapeBase::InvalidateLayout() {
            m_isCacheValid = false;
        }

        bool ShapeBase::OnBeforeDraw(ClockDrawingContext& context) {
            return true;
        }

        void ShapeBase::CalculateCache(ClockDrawingContext& context) {
            // Base implementation - override in derived classes
        }

        void ShapeBase::OnAfterDraw(ClockDrawingContext& context) {
            // Base implementation - override in derived classes
        }

        void ShapeBase::DisposeDrawingTools() {
            // Base implementation - override in derived classes
        }

        void ShapeBase::Draw(ClockDrawingContext& context) {
            if (!m_visible)
                return;

            bool allowToDraw = OnBeforeDraw(context);
            if (!allowToDraw)
                return;

            if (!m_isCacheValid) {
                CalculateCache(context);
                m_isCacheValid = true;
            }

            OnDraw(context);
            OnAfterDraw(context);
        }

    } // namespace Shapes
} // namespace ClockNet
