// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#pragma once
#include "TemplateBase.h"

namespace ClockNet {
    namespace Templates {

        /// <summary>
        /// Black-themed clock template
        /// </summary>
        class BlackTemplate : public TemplateBase {
        protected:
            std::vector<std::shared_ptr<Shapes::IShape>> EnumerateShapes() override;

        public:
            BlackTemplate() = default;
            ~BlackTemplate() = default;
        };

    } // namespace Templates
} // namespace ClockNet
