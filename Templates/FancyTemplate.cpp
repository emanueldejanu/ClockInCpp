// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#include "FancyTemplate.h"
#include "../Shapes/Default/FlatBackground.h"
#include "../Shapes/Default/Ticks.h"
#include "../Shapes/Default/HourNumerals.h"
#include "../Shapes/Default/DiamondHand.h"
#include "../Shapes/Advanced/NibHand.h"
#include "../Shapes/Basic/LineHand.h"
#include "../Shapes/Default/Pin.h"

namespace ClockNet {
    namespace Templates {

        std::vector<std::shared_ptr<Shapes::IShape>> FancyTemplate::EnumerateShapes() {
            std::vector<std::shared_ptr<Shapes::IShape>> shapes;

            // Flat Background
            auto background = std::make_shared<Shapes::Default::FlatBackground>();
            background->SetName(L"Background");
            background->SetFillColor(Gdiplus::Color::White);
            shapes.push_back(background);

            // Minute Ticks
            auto minuteTicks = std::make_shared<Shapes::Default::Ticks>();
            minuteTicks->SetName(L"Minute Ticks");
            minuteTicks->SetOutlineColor(Gdiplus::Color::Black);
            minuteTicks->SetLength(6.0f);
            minuteTicks->SetOutlineWidth(0.3f);
            minuteTicks->SetDistanceFromEdge(8.0f);
            minuteTicks->SetAngle(6.0f);
            minuteTicks->SetOffsetAngle(6.0f);
            minuteTicks->SetSkipIndex(5);
            shapes.push_back(minuteTicks);

            // Hour Ticks
            auto hourTicks = std::make_shared<Shapes::Default::Ticks>();
            hourTicks->SetName(L"Hour Ticks");
            hourTicks->SetOutlineColor(Gdiplus::Color::Black);
            hourTicks->SetLength(6.0f);
            hourTicks->SetOutlineWidth(1.0f);
            hourTicks->SetAngle(30.0f);
            hourTicks->SetOffsetAngle(30.0f);
            shapes.push_back(hourTicks);

            // Hour Numerals
            auto numerals = std::make_shared<Shapes::Default::HourNumerals>();
            numerals->SetName(L"Hour Numerals");
            numerals->SetDistanceFromEdge(26.0f);
            shapes.push_back(numerals);

            // Hour Hand
            auto hourHand = std::make_shared<Shapes::Advanced::NibHand>();
            hourHand->SetName(L"Hour Hand");
            hourHand->SetFillColor(Gdiplus::Color::Black);
            hourHand->SetLength(60.0f);
            hourHand->SetComponentToDisplay(Shapes::TimeComponent::Hour);
            hourHand->SetWidth(10.0f);
            hourHand->SetOutlineColor(Gdiplus::Color(0x60, 0x60, 0x60));
            hourHand->SetOutlineWidth(1.5f);
            shapes.push_back(hourHand);

            // Minute Hand
            auto minuteHand = std::make_shared<Shapes::Advanced::NibHand>();
            minuteHand->SetName(L"Minute Hand");
            minuteHand->SetComponentToDisplay(Shapes::TimeComponent::Minute);
            minuteHand->SetOutlineColor(Gdiplus::Color(0x60, 0x60, 0x60));
            minuteHand->SetOutlineWidth(1.5f);
            minuteHand->SetLength(86.0f);
            minuteHand->SetFillColor(Gdiplus::Color::Black);
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
            pin->SetFillColor(Gdiplus::Color(100, 100, 100));
            shapes.push_back(pin);

            return shapes;
        }

    } // namespace Templates
} // namespace ClockNet
