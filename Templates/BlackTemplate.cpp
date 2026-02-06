// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#include "BlackTemplate.h"
#include "../Shapes/Advanced/FancyBackground.h"
#include "../Shapes/Default/Ticks.h"
#include "../Shapes/Default/HourNumerals.h"
#include "../Shapes/Default/DiamondHand.h"
#include "../Shapes/Basic/LineHand.h"
#include "../Shapes/Default/Pin.h"

namespace ClockNet {
    namespace Templates {

        std::vector<std::shared_ptr<Shapes::IShape>> BlackTemplate::EnumerateShapes() {
            std::vector<std::shared_ptr<Shapes::IShape>> shapes;

            // Fancy Background
            auto background = std::make_shared<Shapes::Advanced::FancyBackground>();
            background->SetName(L"Fancy Background");
            background->SetFillColor(Gdiplus::Color::Black);
            shapes.push_back(background);

            // Minute Ticks
            auto minuteTicks = std::make_shared<Shapes::Default::Ticks>();
            minuteTicks->SetName(L"Minute Ticks");
            minuteTicks->SetDistanceFromEdge(16.5f);
            minuteTicks->SetAngle(6.0f);
            minuteTicks->SetOffsetAngle(6.0f);
            minuteTicks->SetSkipIndex(5);
            minuteTicks->SetOutlineColor(Gdiplus::Color::White);
            minuteTicks->SetOutlineWidth(0.3f);
            shapes.push_back(minuteTicks);

            // Hour Ticks
            auto hourTicks = std::make_shared<Shapes::Default::Ticks>();
            hourTicks->SetName(L"Hour Ticks");
            hourTicks->SetDistanceFromEdge(16.5f);
            hourTicks->SetAngle(30.0f);
            hourTicks->SetOffsetAngle(30.0f);
            hourTicks->SetOutlineColor(Gdiplus::Color::White);
            hourTicks->SetOutlineWidth(1.0f);
            shapes.push_back(hourTicks);

            // Hour Numerals
            auto numerals = std::make_shared<Shapes::Default::HourNumerals>();
            numerals->SetName(L"Hour Numerals");
            numerals->SetDistanceFromEdge(32.0f);
            numerals->SetFillColor(Gdiplus::Color::LightGray);
            shapes.push_back(numerals);

            // Hour Hand
            auto hourHand = std::make_shared<Shapes::Default::DiamondHand>();
            hourHand->SetName(L"Hour Hand");
            hourHand->SetComponentToDisplay(Shapes::TimeComponent::Hour);
            hourHand->SetFillColor(Gdiplus::Color(65, 105, 225)); // RoyalBlue
            hourHand->SetLength(50.0f);
            hourHand->SetWidth(10.0f);
            hourHand->SetTailLength(8.0f);
            shapes.push_back(hourHand);

            // Minute Hand
            auto minuteHand = std::make_shared<Shapes::Default::DiamondHand>();
            minuteHand->SetName(L"Minute Hand");
            minuteHand->SetComponentToDisplay(Shapes::TimeComponent::Minute);
            minuteHand->SetFillColor(Gdiplus::Color::LimeGreen);
            minuteHand->SetLength(76.0f);
            minuteHand->SetWidth(8.0f);
            minuteHand->SetTailLength(8.0f);
            shapes.push_back(minuteHand);

            // Second Hand
            auto secondHand = std::make_shared<Shapes::Basic::LineHand>();
            secondHand->SetName(L"Second Hand");
            secondHand->SetComponentToDisplay(Shapes::TimeComponent::Second);
            secondHand->SetLength(86.0f);
            secondHand->SetOutlineColor(Gdiplus::Color::Red);
            shapes.push_back(secondHand);

            // Pin
            auto pin = std::make_shared<Shapes::Default::Pin>();
            pin->SetName(L"Pin");
            pin->SetFillColor(Gdiplus::Color::Red);
            shapes.push_back(pin);

            return shapes;
        }

    } // namespace Templates
} // namespace ClockNet
