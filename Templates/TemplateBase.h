// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#pragma once
#include "../Shapes/IShape.h"
#include <vector>
#include <memory>

namespace ClockNet {

    /// <summary>
    /// Base class for clock templates
    /// </summary>
    class TemplateBase {
    protected:
        virtual std::vector<std::shared_ptr<Shapes::IShape>> EnumerateShapes() = 0;

    public:
        virtual ~TemplateBase() = default;

        std::vector<std::shared_ptr<Shapes::IShape>> GetShapes() {
            return EnumerateShapes();
        }
    };

} // namespace ClockNet
