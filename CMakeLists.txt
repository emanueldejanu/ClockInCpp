cmake_minimum_required(VERSION 3.15)
project(ClockNetCpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
set(SOURCES
    main.cpp
    ClockControl.cpp
    Shapes/ShapeBase.cpp
    Shapes/VectorialShapeBase.cpp
    Shapes/HandBase.cpp
    Shapes/VectorialHandBase.cpp
    Shapes/RimBase.cpp
    Shapes/VectorialRimBase.cpp
    Shapes/RimDrawingCoordinator.cpp
    Shapes/Default/FlatBackground.cpp
    Shapes/Default/DiamondHand.cpp
    Shapes/Default/Pin.cpp
    Shapes/Default/Ticks.cpp
    Shapes/Default/HourNumerals.cpp
    Shapes/Basic/ImageBackground.cpp
    Shapes/Basic/ImageHand.cpp
    Shapes/Basic/ImageRim.cpp
    Shapes/Basic/LineHand.cpp
    Shapes/Basic/PathHand.cpp
    Shapes/Basic/StringBackground.cpp
    Shapes/Basic/StringRim.cpp
    Shapes/Advanced/CapsuleHand.cpp
    Shapes/Advanced/DigitalHand.cpp
    Shapes/Advanced/DotHand.cpp
    Shapes/Advanced/FancyBackground.cpp
    Shapes/Advanced/FancySweepHand.cpp
    Shapes/Advanced/NibHand.cpp
    Shapes/Advanced/SlotHand.cpp
    Templates/BlackTemplate.cpp
    Templates/FancyTemplate.cpp
)

set(HEADERS
    ClockControl.h
    Shapes/IShape.h
    Shapes/IRim.h
    Shapes/ClockDrawingContext.h
    Shapes/ShapeBase.h
    Shapes/VectorialShapeBase.h
    Shapes/HandBase.h
    Shapes/VectorialHandBase.h
    Shapes/RimBase.h
    Shapes/VectorialRimBase.h
    Shapes/RimDrawingCoordinator.h
    Shapes/RimItemOrientation.h
    Shapes/TimeComponent.h
    Shapes/Default/FlatBackground.h
    Shapes/Default/DiamondHand.h
    Shapes/Default/Pin.h
    Shapes/Default/Ticks.h
    Shapes/Default/HourNumerals.h
    Shapes/Basic/ImageBackground.h
    Shapes/Basic/ImageHand.h
    Shapes/Basic/ImageRim.h
    Shapes/Basic/LineHand.h
    Shapes/Basic/PathHand.h
    Shapes/Basic/StringBackground.h
    Shapes/Basic/StringRim.h
    Shapes/Advanced/CapsuleHand.h
    Shapes/Advanced/DigitalHand.h
    Shapes/Advanced/DotHand.h
    Shapes/Advanced/FancyBackground.h
    Shapes/Advanced/FancySweepHand.h
    Shapes/Advanced/NibHand.h
    Shapes/Advanced/SlotHand.h
    Templates/TemplateBase.h
    Templates/BlackTemplate.h
    Templates/FancyTemplate.h
    Utils/ColorExtensions.h
)

# Create executable
add_executable(ClockNetCpp WIN32 ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(ClockNetCpp
    gdiplus
    comctl32
)

# Set Windows subsystem
if(MSVC)
    set_target_properties(ClockNetCpp PROPERTIES
        LINK_FLAGS "/SUBSYSTEM:WINDOWS"
    )
endif()
