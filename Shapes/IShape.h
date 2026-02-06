// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#pragma once
#include <windows.h>
#include <gdiplus.h>
#include <string>
#include <functional>

namespace ClockNet {
    namespace Shapes {

        // Forward declaration
        class ClockDrawingContext;

        /// <summary>
        /// Represents a graphic element displayed in the AnalogClock
        /// </summary>
        class IShape {
        public:
            virtual ~IShape() = default;

            // Properties
            virtual std::wstring GetName() const = 0;
            virtual void SetName(const std::wstring& name) = 0;

            virtual bool IsVisible() const = 0;
            virtual void SetVisible(bool visible) = 0;

            // Events
            std::function<void()> NameChanged;
            std::function<void()> Changed;

            // Methods
            virtual void Draw(ClockDrawingContext& context) = 0;
        };

    } // namespace Shapes
} // namespace ClockNet
