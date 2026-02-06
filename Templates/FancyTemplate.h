// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#pragma once
#include "TemplateBase.h"

namespace ClockNet {
    namespace Templates {

        /// <summary>
        /// Fancy clock template with elegant design
        /// </summary>
        class FancyTemplate : public TemplateBase {
        protected:
            std::vector<std::shared_ptr<Shapes::IShape>> EnumerateShapes() override;

        public:
            FancyTemplate() = default;
            ~FancyTemplate() = default;
        };

    } // namespace Templates
} // namespace ClockNet
