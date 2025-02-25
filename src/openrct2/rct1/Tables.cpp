/*****************************************************************************
 * Copyright (c) 2014-2020 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#include "Tables.h"

#include "../common.h"
#include "../core/Guard.hpp"
#include "../interface/Colour.h"
#include "../object/ObjectManager.h"
#include "../ride/Ride.h"
#include "../ride/RideData.h"
#include "../world/Surface.h"
#include "RCT1.h"

#include <iterator>

// clang-format off
namespace RCT1
{
    colour_t GetColour(colour_t colour)
    {
        static constexpr const uint8_t map[] =
        {
            COLOUR_BLACK,
            COLOUR_GREY,
            COLOUR_WHITE,
            COLOUR_LIGHT_PURPLE,
            COLOUR_BRIGHT_PURPLE,
            COLOUR_DARK_BLUE,
            COLOUR_LIGHT_BLUE,
            COLOUR_TEAL,
            COLOUR_SATURATED_GREEN,
            COLOUR_DARK_GREEN,
            COLOUR_MOSS_GREEN,
            COLOUR_BRIGHT_GREEN,
            COLOUR_OLIVE_GREEN,
            COLOUR_DARK_OLIVE_GREEN,
            COLOUR_YELLOW,
            COLOUR_DARK_YELLOW,
            COLOUR_LIGHT_ORANGE,
            COLOUR_DARK_ORANGE,
            COLOUR_LIGHT_BROWN,
            COLOUR_SATURATED_BROWN,
            COLOUR_DARK_BROWN,
            COLOUR_SALMON_PINK,
            COLOUR_BORDEAUX_RED,
            COLOUR_SATURATED_RED,
            COLOUR_BRIGHT_RED,
            COLOUR_BRIGHT_PINK,
            COLOUR_LIGHT_PINK,
            COLOUR_DARK_PINK,
            COLOUR_DARK_PURPLE,
            COLOUR_AQUAMARINE,
            COLOUR_BRIGHT_YELLOW,
            COLOUR_ICY_BLUE
        };
        if (colour >= std::size(map))
        {
            log_warning("Unsupported RCT1 colour.");
            return COLOUR_BLACK;
        }
        return map[colour];
    }

    PeepSpriteType GetPeepSpriteType(uint8_t rct1SpriteType)
    {
        static constexpr const PeepSpriteType map[] =
        {
            PeepSpriteType::Normal, // 0x00
            PeepSpriteType::Handyman, // 0x01
            PeepSpriteType::Mechanic, // 0x02
            PeepSpriteType::Security, // 0x03
            PeepSpriteType::EntertainerPanda, // 0x04
            PeepSpriteType::EntertainerTiger, // 0x05
            PeepSpriteType::EntertainerElephant, // 0x06
            PeepSpriteType::EntertainerRoman, // 0x07
            PeepSpriteType::EntertainerGorilla, // 0x08
            PeepSpriteType::EntertainerSnowman, // 0x09
            PeepSpriteType::EntertainerKnight, // 0x0A
            PeepSpriteType::EntertainerAstronaut, // 0x0B
            PeepSpriteType::IceCream, // 0x0C
            PeepSpriteType::Chips, // 0x0D
            PeepSpriteType::Burger, // 0x0E
            PeepSpriteType::Drink, // 0x0F
            PeepSpriteType::Balloon, // 0x10
            PeepSpriteType::Candyfloss, // 0x11
            PeepSpriteType::Umbrella, // 0x12
            PeepSpriteType::Pizza, // 0x13
            PeepSpriteType::SecurityAlt, // 0x14
            PeepSpriteType::Popcorn, // 0x15
            PeepSpriteType::ArmsCrossed, // 0x16
            PeepSpriteType::HeadDown, // 0x17
            PeepSpriteType::Nauseous, // 0x18
            PeepSpriteType::VeryNauseous, // 0x19
            PeepSpriteType::RequireToilet, // 0x1A
            PeepSpriteType::Hat, // 0x1B
            PeepSpriteType::HotDog, // 0x1C
            PeepSpriteType::Tentacle, // 0x1D
            PeepSpriteType::ToffeeApple, // 0x1E
            PeepSpriteType::Doughnut, // 0x1F
            PeepSpriteType::Coffee, // 0x20
            PeepSpriteType::Chicken, // 0x21
            PeepSpriteType::Lemonade, // 0x22
        };
        if (rct1SpriteType >= std::size(map))
        {
            log_warning("Unsupported RCT1 peep sprite type: %d.", rct1SpriteType);
            return PeepSpriteType::Normal;
        }
        return map[rct1SpriteType];
    }

    ObjectEntryIndex GetTerrain(uint8_t terrainSurface)
    {
        static constexpr std::string_view map[RCT1_NUM_TERRAIN_SURFACES] =
        {
            "rct2.surface.grass",
            "rct2.surface.sand",
            "rct2.surface.dirt",
            "rct2.surface.rock",
            "rct2.surface.martian",
            "rct2.surface.chequerboard",
            "rct2.surface.grassclumps",
            "rct1.aa.surface.roofred",
            "rct2.surface.ice",
            "rct1.ll.surface.wood",
            "rct1.ll.surface.rust",
            "rct1.ll.surface.roofgrey",
            "rct2.surface.gridred",
            "rct2.surface.gridyellow",
            "rct2.surface.gridpurple",
            "rct2.surface.gridgreen",
        };
        std::string selectedSurface = "rct2.surface.grass";
        if (terrainSurface < std::size(map))
        {
            selectedSurface = map[terrainSurface];
        }

        return object_manager_get_loaded_object_entry_index(ObjectEntryDescriptor(selectedSurface));
    }

    ObjectEntryIndex GetTerrainEdge(uint8_t terrainEdge)
    {
        static constexpr std::string_view map[RCT1_NUM_TERRAIN_EDGES] =
        {
            "rct2.edge.rock",
            "rct1.edge.brick",
            "rct1.edge.iron",
            "rct2.edge.woodred",
            "rct1.aa.edge.grey",
            "rct1.aa.edge.yellow",
            "rct2.edge.woodblack",
            "rct1.aa.edge.red",
            "rct2.edge.ice",
            "rct1.ll.edge.purple",
            "rct1.ll.edge.green",
            "rct1.ll.edge.stonebrown",
            "rct1.ll.edge.stonegrey",
            "rct1.ll.edge.skyscrapera",
            "rct1.ll.edge.skyscraperb",
        };
        std::string selectedEdge = "rct2.edge.rock";
        if (terrainEdge < std::size(map))
        {
            selectedEdge = map[terrainEdge];
        }

        return object_manager_get_loaded_object_entry_index(ObjectEntryDescriptor(selectedEdge));
    }

    uint8_t GetRideType(RideType rideType, uint8_t vehicleType)
    {
        if (rideType == RideType::SteelTwisterRollerCoaster && vehicleType == RCT1_VEHICLE_TYPE_NON_LOOPING_STEEL_TWISTER_ROLLER_COASTER_TRAIN)
            return RIDE_TYPE_HYPER_TWISTER;
        if (rideType == RideType::SteelCorkscrewRollerCoaster && vehicleType == RCT1_VEHICLE_TYPE_HYPERCOASTER_TRAIN)
            return RIDE_TYPE_HYPERCOASTER;

        static uint8_t map[] =
        {
            RIDE_TYPE_WOODEN_ROLLER_COASTER,        // RCT1_RIDE_TYPE_WOODEN_ROLLER_COASTER
            RIDE_TYPE_STAND_UP_ROLLER_COASTER,      // RCT1_RIDE_TYPE_STAND_UP_STEEL_ROLLER_COASTER
            RIDE_TYPE_SUSPENDED_SWINGING_COASTER,   // RCT1_RIDE_TYPE_SUSPENDED_ROLLER_COASTER
            RIDE_TYPE_INVERTED_ROLLER_COASTER,      // RCT1_RIDE_TYPE_INVERTED_ROLLER_COASTER
            RIDE_TYPE_CLASSIC_MINI_ROLLER_COASTER,  // RCT1_RIDE_TYPE_STEEL_MINI_ROLLER_COASTER
            RIDE_TYPE_MINIATURE_RAILWAY,            // RCT1_RIDE_TYPE_MINIATURE_RAILWAY
            RIDE_TYPE_MONORAIL,                     // RCT1_RIDE_TYPE_MONORAIL
            RIDE_TYPE_MINI_SUSPENDED_COASTER,       // RCT1_RIDE_TYPE_SUSPENDED_SINGLE_RAIL_ROLLER_COASTER
            RIDE_TYPE_BOAT_HIRE,                    // RCT1_RIDE_TYPE_BOAT_HIRE
            RIDE_TYPE_WOODEN_WILD_MOUSE,            // RCT1_RIDE_TYPE_WOODEN_CRAZY_RODENT_ROLLER_COASTER
            RIDE_TYPE_STEEPLECHASE,                 // RCT1_RIDE_TYPE_SINGLE_RAIL_ROLLER_COASTER
            RIDE_TYPE_CAR_RIDE,                     // RCT1_RIDE_TYPE_CAR_RIDE
            RIDE_TYPE_LAUNCHED_FREEFALL,            // RCT1_RIDE_TYPE_LAUNCHED_FREEFALL
            RIDE_TYPE_BOBSLEIGH_COASTER,            // RCT1_RIDE_TYPE_BOBSLED_ROLLER_COASTER
            RIDE_TYPE_OBSERVATION_TOWER,            // RCT1_RIDE_TYPE_OBSERVATION_TOWER
            RIDE_TYPE_LOOPING_ROLLER_COASTER,       // RCT1_RIDE_TYPE_STEEL_ROLLER_COASTER
            RIDE_TYPE_DINGHY_SLIDE,                 // RCT1_RIDE_TYPE_WATER_SLIDE
            RIDE_TYPE_MINE_TRAIN_COASTER,           // RCT1_RIDE_TYPE_MINE_TRAIN_ROLLER_COASTER
            RIDE_TYPE_CHAIRLIFT,                    // RCT1_RIDE_TYPE_CHAIRLIFT
            RIDE_TYPE_CORKSCREW_ROLLER_COASTER,     // RCT1_RIDE_TYPE_STEEL_CORKSCREW_ROLLER_COASTER
            RIDE_TYPE_MAZE,                         // RCT1_RIDE_TYPE_HEDGE_MAZE
            RIDE_TYPE_SPIRAL_SLIDE,                 // RCT1_RIDE_TYPE_SPIRAL_SLIDE
            RIDE_TYPE_GO_KARTS,                     // RCT1_RIDE_TYPE_GO_KARTS
            RIDE_TYPE_LOG_FLUME,                    // RCT1_RIDE_TYPE_LOG_FLUME
            RIDE_TYPE_RIVER_RAPIDS,                 // RCT1_RIDE_TYPE_RIVER_RAPIDS
            RIDE_TYPE_DODGEMS,                      // RCT1_RIDE_TYPE_DODGEMS
            RIDE_TYPE_SWINGING_SHIP,                // RCT1_RIDE_TYPE_SWINGING_SHIP
            RIDE_TYPE_SWINGING_INVERTER_SHIP,       // RCT1_RIDE_TYPE_SWINGING_INVERTER_SHIP
            RIDE_TYPE_FOOD_STALL,                   // RCT1_RIDE_TYPE_ICE_CREAM_STALL
            RIDE_TYPE_FOOD_STALL,                   // RCT1_RIDE_TYPE_CHIPS_STALL
            RIDE_TYPE_DRINK_STALL,                  // RCT1_RIDE_TYPE_DRINK_STALL
            RIDE_TYPE_FOOD_STALL,                   // RCT1_RIDE_TYPE_CANDYFLOSS_STALL
            RIDE_TYPE_SHOP,                         // RCT1_RIDE_TYPE_BURGER_BAR
            RIDE_TYPE_MERRY_GO_ROUND,               // RCT1_RIDE_TYPE_MERRY_GO_ROUND
            RIDE_TYPE_SHOP,                         // RCT1_RIDE_TYPE_BALLOON_STALL
            RIDE_TYPE_INFORMATION_KIOSK,            // RCT1_RIDE_TYPE_INFORMATION_KIOSK
            RIDE_TYPE_TOILETS,                      // RCT1_RIDE_TYPE_TOILETS
            RIDE_TYPE_FERRIS_WHEEL,                 // RCT1_RIDE_TYPE_FERRIS_WHEEL
            RIDE_TYPE_MOTION_SIMULATOR,             // RCT1_RIDE_TYPE_MOTION_SIMULATOR
            RIDE_TYPE_3D_CINEMA,                    // RCT1_RIDE_TYPE_3D_CINEMA
            RIDE_TYPE_TOP_SPIN,                     // RCT1_RIDE_TYPE_TOP_SPIN
            RIDE_TYPE_SPACE_RINGS,                  // RCT1_RIDE_TYPE_SPACE_RINGS
            RIDE_TYPE_REVERSE_FREEFALL_COASTER,     // RCT1_RIDE_TYPE_REVERSE_FREEFALL_ROLLER_COASTER
            RIDE_TYPE_SHOP,                         // RCT1_RIDE_TYPE_SOUVENIR_STALL
            RIDE_TYPE_VERTICAL_DROP_ROLLER_COASTER, // RCT1_RIDE_TYPE_VERTICAL_ROLLER_COASTER
            RIDE_TYPE_FOOD_STALL,                   // RCT1_RIDE_TYPE_PIZZA_STALL
            RIDE_TYPE_TWIST,                        // RCT1_RIDE_TYPE_TWIST
            RIDE_TYPE_HAUNTED_HOUSE,                // RCT1_RIDE_TYPE_HAUNTED_HOUSE
            RIDE_TYPE_FOOD_STALL,                   // RCT1_RIDE_TYPE_POPCORN_STALL
            RIDE_TYPE_CIRCUS,                       // RCT1_RIDE_TYPE_CIRCUS
            RIDE_TYPE_GHOST_TRAIN,                  // RCT1_RIDE_TYPE_GHOST_TRAIN
            RIDE_TYPE_TWISTER_ROLLER_COASTER,       // RCT1_RIDE_TYPE_STEEL_TWISTER_ROLLER_COASTER
            RIDE_TYPE_WOODEN_ROLLER_COASTER,        // RCT1_RIDE_TYPE_WOODEN_TWISTER_ROLLER_COASTER
            RIDE_TYPE_SIDE_FRICTION_ROLLER_COASTER, // RCT1_RIDE_TYPE_WOODEN_SIDE_FRICTION_ROLLER_COASTER
            RIDE_TYPE_STEEL_WILD_MOUSE,             // RCT1_RIDE_TYPE_STEEL_WILD_MOUSE_ROLLER_COASTER
            RIDE_TYPE_FOOD_STALL,                   // RCT1_RIDE_TYPE_HOT_DOG_STALL
            RIDE_TYPE_FOOD_STALL,                   // RCT1_RIDE_TYPE_EXOTIC_SEA_FOOD_STALL
            RIDE_TYPE_SHOP,                         // RCT1_RIDE_TYPE_HAT_STALL
            RIDE_TYPE_FOOD_STALL,                   // RCT1_RIDE_TYPE_TOFFEE_APPLE_STALL
            RIDE_TYPE_VIRGINIA_REEL,                // RCT1_RIDE_TYPE_VIRGINIA_REEL
            RIDE_TYPE_SPLASH_BOATS,                 // RCT1_RIDE_TYPE_RIVER_RIDE
            RIDE_TYPE_MINI_HELICOPTERS,             // RCT1_RIDE_TYPE_CYCLE_MONORAIL
            RIDE_TYPE_LAY_DOWN_ROLLER_COASTER,      // RCT1_RIDE_TYPE_FLYING_ROLLER_COASTER
            RIDE_TYPE_SUSPENDED_MONORAIL,           // RCT1_RIDE_TYPE_SUSPENDED_MONORAIL
            RIDE_TYPE_NULL,                         // RCT1_RIDE_TYPE_40
            RIDE_TYPE_REVERSER_ROLLER_COASTER,      // RCT1_RIDE_TYPE_WOODEN_REVERSER_ROLLER_COASTER
            RIDE_TYPE_HEARTLINE_TWISTER_COASTER,    // RCT1_RIDE_TYPE_HEARTLINE_TWISTER_ROLLER_COASTER
            RIDE_TYPE_MINI_GOLF,                    // RCT1_RIDE_TYPE_MINIATURE_GOLF
            RIDE_TYPE_NULL,                         // RCT1_RIDE_TYPE_44
            RIDE_TYPE_ROTO_DROP,                    // RCT1_RIDE_TYPE_ROTO_DROP
            RIDE_TYPE_FLYING_SAUCERS,               // RCT1_RIDE_TYPE_FLYING_SAUCERS
            RIDE_TYPE_CROOKED_HOUSE,                // RCT1_RIDE_TYPE_CROOKED_HOUSE
            RIDE_TYPE_MONORAIL_CYCLES,              // RCT1_RIDE_TYPE_CYCLE_RAILWAY
            RIDE_TYPE_COMPACT_INVERTED_COASTER,     // RCT1_RIDE_TYPE_SUSPENDED_LOOPING_ROLLER_COASTER
            RIDE_TYPE_WATER_COASTER,                // RCT1_RIDE_TYPE_WATER_COASTER
            RIDE_TYPE_AIR_POWERED_VERTICAL_COASTER, // RCT1_RIDE_TYPE_AIR_POWERED_VERTICAL_COASTER
            RIDE_TYPE_INVERTED_HAIRPIN_COASTER,     // RCT1_RIDE_TYPE_INVERTED_WILD_MOUSE_COASTER
            RIDE_TYPE_BOAT_HIRE,                    // RCT1_RIDE_TYPE_JET_SKIS
            RIDE_TYPE_SHOP,                         // RCT1_RIDE_TYPE_T_SHIRT_STALL
            RIDE_TYPE_RIVER_RAFTS,                  // RCT1_RIDE_TYPE_RAFT_RIDE
            RIDE_TYPE_FOOD_STALL,                   // RCT1_RIDE_TYPE_DOUGHNUT_SHOP
            RIDE_TYPE_ENTERPRISE,                   // RCT1_RIDE_TYPE_ENTERPRISE
            RIDE_TYPE_DRINK_STALL,                  // RCT1_RIDE_TYPE_COFFEE_SHOP
            RIDE_TYPE_FOOD_STALL,                   // RCT1_RIDE_TYPE_FRIED_CHICKEN_STALL
            RIDE_TYPE_DRINK_STALL,                  // RCT1_RIDE_TYPE_LEMONADE_STALL
        };

        const auto index = EnumValue(rideType);
        Guard::ArgumentInRange<size_t>(index, 0, std::size(map), "Unsupported RCT1 ride type.");

        return map[index];
    }

    VehicleColourSchemeCopyDescriptor GetColourSchemeCopyDescriptor(uint8_t vehicleType)
    {
        static VehicleColourSchemeCopyDescriptor map[89] =
        {
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_STEEL_ROLLER_COASTER_TRAIN = 0,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_STEEL_ROLLER_COASTER_TRAIN_BACKWARDS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_WOODEN_ROLLER_COASTER_TRAIN,
            { COPY_COLOUR_1, COPY_COLOUR_2, COPY_COLOUR_2 }, // RCT1_VEHICLE_TYPE_INVERTED_COASTER_TRAIN, // Not in RCT2
            { COPY_COLOUR_1, COPY_COLOUR_2, COPY_COLOUR_2 }, // RCT1_VEHICLE_TYPE_SUSPENDED_SWINGING_CARS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_LADYBIRD_CARS,
            { COPY_COLOUR_1, COPY_COLOUR_1, COPY_COLOUR_2 }, // RCT1_VEHICLE_TYPE_STANDUP_ROLLER_COASTER_CARS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_SPINNING_CARS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_SINGLE_PERSON_SWINGING_CHAIRS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_SWANS_PEDAL_BOATS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_DARK_BLUE }, // RCT1_VEHICLE_TYPE_LARGE_MONORAIL_TRAIN,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_CANOES,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_ROWING_BOATS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_STEAM_TRAIN,
            { COPY_COLOUR_1, COPY_COLOUR_2, COPY_COLOUR_2 }, // RCT1_VEHICLE_TYPE_WOODEN_MOUSE_CARS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_BUMPER_BOATS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_WOODEN_ROLLER_COASTER_TRAIN_BACKWARDS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_ROCKET_CARS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_HORSES, // Steeplechase
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_SPORTSCARS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_LYING_DOWN_SWINGING_CARS, // Inverted single-rail
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_WOODEN_MINE_CARS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_SUSPENDED_SWINGING_AIRPLANE_CARS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_SMALL_MONORAIL_CARS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_WATER_TRICYCLES,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_LAUNCHED_FREEFALL_CAR,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_BOBSLEIGH_CARS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_DINGHIES,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_ROTATING_CABIN,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_MINE_TRAIN,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_CHAIRLIFT_CARS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_CORKSCREW_ROLLER_COASTER_TRAIN,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_MOTORBIKES,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_RACING_CARS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_TRUCKS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_GO_KARTS,
            { COPY_COLOUR_1, COLOUR_BLACK, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_RAPIDS_BOATS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_LOG_FLUME_BOATS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_DODGEMS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_SWINGING_SHIP,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_SWINGING_INVERTER_SHIP,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_MERRY_GO_ROUND,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_FERRIS_WHEEL,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_SIMULATOR_POD,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_CINEMA_BUILDING,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_TOPSPIN_CAR,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_SPACE_RINGS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_REVERSE_FREEFALL_ROLLER_COASTER_CAR,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_VERTICAL_ROLLER_COASTER_CARS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_CAT_CARS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_TWIST_ARMS_AND_CARS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_HAUNTED_HOUSE_BUILDING,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_LOG_CARS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_CIRCUS_TENT,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_GHOST_TRAIN_CARS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_STEEL_TWISTER_ROLLER_COASTER_TRAIN,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_WOODEN_TWISTER_ROLLER_COASTER_TRAIN,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_WOODEN_SIDE_FRICTION_CARS,
            { COPY_COLOUR_1, COPY_COLOUR_1, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_VINTAGE_CARS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_STEAM_TRAIN_COVERED_CARS,
            { COPY_COLOUR_1, COLOUR_BLACK, COPY_COLOUR_2 }, // RCT1_VEHICLE_TYPE_STAND_UP_STEEL_TWISTER_ROLLER_COASTER_TRAIN,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_FLOORLESS_STEEL_TWISTER_ROLLER_COASTER_TRAIN,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_STEEL_MOUSE_CARS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_CHAIRLIFT_CARS_ALTERNATIVE,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_SUSPENDED_MONORAIL_TRAIN,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_HELICOPTER_CARS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_VIRGINIA_REEL_TUBS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_REVERSER_CARS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_GOLFERS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_RIVER_RIDE_BOATS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_FLYING_ROLLER_COASTER_TRAIN,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_NON_LOOPING_STEEL_TWISTER_ROLLER_COASTER_TRAIN,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_HEARTLINE_TWISTER_CARS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_HEARTLINE_TWISTER_CARS_REVERSED,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_RESERVED,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_ROTODROP_CAR,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_FLYING_SAUCERS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_CROOKED_HOUSE_BUILDING,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_BICYCLES,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_HYPERCOASTER_TRAIN,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_4_ACROSS_INVERTED_COASTER_TRAIN,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_WATER_COASTER_BOATS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_FACEOFF_CARS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_JET_SKIS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_RAFT_BOATS,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_YELLOW }, // RCT1_VEHICLE_TYPE_AMERICAN_STYLE_STEAM_TRAIN,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_AIR_POWERED_COASTER_TRAIN,
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_SUSPENDED_WILD_MOUSE_CARS, // Inverted Hairpin in RCT2
            { COPY_COLOUR_1, COPY_COLOUR_2, COLOUR_BLACK }, // RCT1_VEHICLE_TYPE_ENTERPRISE_WHEEL
        };

        Guard::ArgumentInRange<size_t>(vehicleType, 0, std::size(map), "Unsupported RCT1 vehicle type.");
        return map[vehicleType];
    }

    bool RideTypeUsesVehicles(RideType rideType)
    {
        switch (rideType) {
        case RideType::HedgeMaze:
        case RideType::SpiralSlide:
        case RideType::IceCreamStall:
        case RideType::ChipsStall:
        case RideType::DrinkStall:
        case RideType::CandyflossStall:
        case RideType::BurgerBar:
        case RideType::BalloonStall:
        case RideType::InformationKiosk:
        case RideType::Toilets:
        case RideType::SouvenirStall:
        case RideType::PizzaStall:
        case RideType::PopcornStall:
        case RideType::HotDogStall:
        case RideType::ExoticSeaFoodStall:
        case RideType::HatStall:
        case RideType::ToffeeAppleStall:
        case RideType::_40:
        case RideType::_44:
        case RideType::TShirtStall:
        case RideType::DoughnutShop:
        case RideType::CoffeeShop:
        case RideType::FriedChickenStall:
        case RideType::LemonadeStall:
            return false;
        default:
            return true;
        }
    }

    bool PathIsQueue(uint8_t pathType)
    {
        switch (pathType) {
        case RCT1_FOOTPATH_TYPE_QUEUE_BLUE:
        case RCT1_FOOTPATH_TYPE_QUEUE_RED:
        case RCT1_FOOTPATH_TYPE_QUEUE_YELLOW:
        case RCT1_FOOTPATH_TYPE_QUEUE_GREEN:
            return true;
        }
        return false;
    }

    uint8_t NormalisePathAddition(uint8_t pathAdditionType)
    {
        switch (pathAdditionType) {
        case RCT1_PATH_ADDITION_BROKEN_LAMP_1: return RCT1_PATH_ADDITION_LAMP_1;
        case RCT1_PATH_ADDITION_BROKEN_LAMP_2: return RCT1_PATH_ADDITION_LAMP_2;
        case RCT1_PATH_ADDITION_BROKEN_BIN:    return RCT1_PATH_ADDITION_BIN;
        case RCT1_PATH_ADDITION_BROKEN_BENCH:  return RCT1_PATH_ADDITION_BENCH;
        case RCT1_PATH_ADDITION_BROKEN_LAMP_3: return RCT1_PATH_ADDITION_LAMP_3;
        case RCT1_PATH_ADDITION_BROKEN_LAMP_4: return RCT1_PATH_ADDITION_LAMP_4;
        }
        return pathAdditionType;
    }

    uint8_t GetVehicleSubEntryIndex(uint8_t vehicleSubEntry)
    {
        static constexpr const uint8_t map[] =
        {
            0, // STEEL_RC_FRONT
            1, // STEEL_RC_CARRIAGE
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0, // MONORAIL_CARRIAGE
            1, // MONORAIL_FRONT
            2, // MONORAIL_BACK
            0,
            0,
            1, // MINIATURE_RAILWAY_TENDER
            0, // MINIATURE_RAILWAY_LOCOMOTIVE
            2, // MINIATURE_RAILWAY_CARRIAGE
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0, // MINE_TRAIN_FRONT
            1, // MINE_TRAIN_CARRIAGE
            0,
            0, // CORKSCREW_RC_FRONT
            1, // CORKSCREW_RC_CARRIAGE
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0, // GHOST_TRAIN_CAR
            1, // TWISTER_RC_SPOILER
            0, // TWISTER_RC_CARRIAGE
            1, // GHOST_TRAIN_INVISIBLE
            0, // ARTICULATED_RC_FRONT
            1, // ARTICULATED_RC_CARRIAGE
            0,
            0,
            2, // MINIATURE_RAILWAY_CARRIAGE_COVERED
            0, // STANDUP_TWISTER_RC_CARRIAGE
            0,
            0,
            0,
            0,
            0,
            0,
            0, // REVERSER_RC_CAR
            2, // REVERSER_RC_BOGIE
            1, // MINIGOLF_PLAYER
            0, // MINIGOLF_BALL
            0, // SPLASH_BOAT
            1, // SPLASH_BOAT_INVISIBLE
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0, // HYPERCOASTER_FRONT
            1, // HYPERCOASTER_CARRIAGE
            0, // INVERTED_4_ACROSS_CARRIAGE
            0, // WATER_COASTER_BOAT
            0,
            1, // WATER_COASTER_INVISIBLE
            0,
            0, // RIVER_RAFT
            1, // MINIATURE_RAILWAY_AMERICAN_TENDER
            0, // MINIATURE_RAILWAY_AMERICAN_LOCOMOTIVE
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
        };
        return map[vehicleSubEntry];
    }

    const char * GetRideTypeObject(RideType rideType)
    {
        static constexpr const char * map[] =
        {
            "PTCT1   ",  // RCT1_RIDE_TYPE_WOODEN_ROLLER_COASTER
            "TOGST   ",  // RCT1_RIDE_TYPE_STAND_UP_STEEL_ROLLER_COASTER
            "ARRSW1  ",  // RCT1_RIDE_TYPE_SUSPENDED_ROLLER_COASTER
            "NEMT    ",  // RCT1_RIDE_TYPE_INVERTED_ROLLER_COASTER
            "ZLDB    ",  // RCT1_RIDE_TYPE_STEEL_MINI_ROLLER_COASTER
            "NRL     ",  // RCT1_RIDE_TYPE_MINIATURE_RAILWAY
            "MONO2   ",  // RCT1_RIDE_TYPE_MONORAIL
            "BATFL   ",  // RCT1_RIDE_TYPE_SUSPENDED_SINGLE_RAIL_ROLLER_COASTER
            "RBOAT   ",  // RCT1_RIDE_TYPE_BOAT_HIRE
            "WMOUSE  ",  // RCT1_RIDE_TYPE_WOODEN_CRAZY_RODENT_ROLLER_COASTER
            "STEEP1  ",  // RCT1_RIDE_TYPE_SINGLE_RAIL_ROLLER_COASTER
            "SPCAR   ",  // RCT1_RIDE_TYPE_CAR_RIDE
            "SSC1    ",  // RCT1_RIDE_TYPE_LAUNCHED_FREEFALL
            "BOB1    ",  // RCT1_RIDE_TYPE_BOBSLED_ROLLER_COASTER
            "OBS1    ",  // RCT1_RIDE_TYPE_OBSERVATION_TOWER
            "SCHT1   ",  // RCT1_RIDE_TYPE_STEEL_ROLLER_COASTER
            "DING1   ",  // RCT1_RIDE_TYPE_WATER_SLIDE
            "AMT1    ",  // RCT1_RIDE_TYPE_MINE_TRAIN_ROLLER_COASTER
            "CLIFT1  ",  // RCT1_RIDE_TYPE_CHAIRLIFT
            "ARRT1   ",  // RCT1_RIDE_TYPE_STEEL_CORKSCREW_ROLLER_COASTER
            "HMAZE   ",  // RCT1_RIDE_TYPE_HEDGE_MAZE
            "HSKELT  ",  // RCT1_RIDE_TYPE_SPIRAL_SLIDE
            "KART1   ",  // RCT1_RIDE_TYPE_GO_KARTS
            "LFB1    ",  // RCT1_RIDE_TYPE_LOG_FLUME
            "RAPBOAT ",  // RCT1_RIDE_TYPE_RIVER_RAPIDS
            "DODG1   ",  // RCT1_RIDE_TYPE_DODGEMS
            "SWSH1   ",  // RCT1_RIDE_TYPE_SWINGING_SHIP
            "SWSH2   ",  // RCT1_RIDE_TYPE_SWINGING_INVERTER_SHIP
            "ICECR1  ",  // RCT1_RIDE_TYPE_ICE_CREAM_STALL
            "CHPSH   ",  // RCT1_RIDE_TYPE_CHIPS_STALL
            "DRNKS   ",  // RCT1_RIDE_TYPE_DRINK_STALL
            "CNDYF   ",  // RCT1_RIDE_TYPE_CANDYFLOSS_STALL
            "BURGB   ",  // RCT1_RIDE_TYPE_BURGER_BAR
            "MGR1    ",  // RCT1_RIDE_TYPE_MERRY_GO_ROUND
            "BALLN   ",  // RCT1_RIDE_TYPE_BALLOON_STALL
            "INFOK   ",  // RCT1_RIDE_TYPE_INFORMATION_KIOSK
            "TLT1    ",  // RCT1_RIDE_TYPE_TOILETS
            "FWH1    ",  // RCT1_RIDE_TYPE_FERRIS_WHEEL
            "SIMPOD  ",  // RCT1_RIDE_TYPE_MOTION_SIMULATOR
            "C3D     ",  // RCT1_RIDE_TYPE_3D_CINEMA
            "TOPSP1  ",  // RCT1_RIDE_TYPE_TOP_SPIN
            "SRINGS  ",  // RCT1_RIDE_TYPE_SPACE_RINGS
            "REVF1   ",  // RCT1_RIDE_TYPE_REVERSE_FREEFALL_ROLLER_COASTER
            "SOUVS   ",  // RCT1_RIDE_TYPE_SOUVENIR_STALL
            "BMVD    ",  // RCT1_RIDE_TYPE_VERTICAL_ROLLER_COASTER
            "PIZZS   ",  // RCT1_RIDE_TYPE_PIZZA_STALL
            "TWIST1  ",  // RCT1_RIDE_TYPE_TWIST
            "HHBUILD ",  // RCT1_RIDE_TYPE_HAUNTED_HOUSE
            "POPCS   ",  // RCT1_RIDE_TYPE_POPCORN_STALL
            "CIRCUS1 ",  // RCT1_RIDE_TYPE_CIRCUS
            "GTC     ",  // RCT1_RIDE_TYPE_GHOST_TRAIN
            "BMSD    ",  // RCT1_RIDE_TYPE_STEEL_TWISTER_ROLLER_COASTER
            "MFT     ",  // RCT1_RIDE_TYPE_WOODEN_TWISTER_ROLLER_COASTER
            "SFRIC1  ",  // RCT1_RIDE_TYPE_WOODEN_SIDE_FRICTION_ROLLER_COASTER
            "SMC1    ",  // RCT1_RIDE_TYPE_STEEL_WILD_MOUSE_ROLLER_COASTER
            "HOTDS   ",  // RCT1_RIDE_TYPE_HOT_DOG_STALL
            "SQDST   ",  // RCT1_RIDE_TYPE_EXOTIC_SEA_FOOD_STALL
            "HATST   ",  // RCT1_RIDE_TYPE_HAT_STALL
            "TOFFS   ",  // RCT1_RIDE_TYPE_TOFFEE_APPLE_STALL
            "VREEL   ",  // RCT1_RIDE_TYPE_VIRGINIA_REEL
            "SPBOAT  ",  // RCT1_RIDE_TYPE_RIVER_RIDE
            "MONBK   ",  // RCT1_RIDE_TYPE_CYCLE_MONORAIL
            "VEKST   ",  // RCT1_RIDE_TYPE_FLYING_ROLLER_COASTER
            "SMONO   ",  // RCT1_RIDE_TYPE_SUSPENDED_MONORAIL
            "        ",  // RCT1_RIDE_TYPE_40
            "REVCAR  ",  // RCT1_RIDE_TYPE_WOODEN_REVERSER_ROLLER_COASTER
            "UTCAR   ",  // RCT1_RIDE_TYPE_HEARTLINE_TWISTER_ROLLER_COASTER
            "GOLF1   ",  // RCT1_RIDE_TYPE_MINIATURE_GOLF
            "        ",  // RCT1_RIDE_TYPE_44
            "GDROP1  ",  // RCT1_RIDE_TYPE_ROTO_DROP
            "FSAUC   ",  // RCT1_RIDE_TYPE_FLYING_SAUCERS
            "CHBUILD ",  // RCT1_RIDE_TYPE_CROOKED_HOUSE
            "HELICAR ",  // RCT1_RIDE_TYPE_CYCLE_RAILWAY
            "SLCT    ",  // RCT1_RIDE_TYPE_SUSPENDED_LOOPING_ROLLER_COASTER
            "CSTBOAT ",  // RCT1_RIDE_TYPE_WATER_COASTER
            "THCAR   ",  // RCT1_RIDE_TYPE_AIR_POWERED_VERTICAL_COASTER
            "IVMC1   ",  // RCT1_RIDE_TYPE_INVERTED_WILD_MOUSE_COASTER
            "JSKI    ",  // RCT1_RIDE_TYPE_JET_SKIS
            "TSHRT   ",  // RCT1_RIDE_TYPE_T_SHIRT_STALL
            "RFTBOAT ",  // RCT1_RIDE_TYPE_RAFT_RIDE
            "DOUGH   ",  // RCT1_RIDE_TYPE_DOUGHNUT_SHOP
            "ENTERP  ",  // RCT1_RIDE_TYPE_ENTERPRISE
            "COFFS   ",  // RCT1_RIDE_TYPE_COFFEE_SHOP
            "CHCKS   ",  // RCT1_RIDE_TYPE_FRIED_CHICKEN_STALL
            "LEMST   ",  // RCT1_RIDE_TYPE_LEMONADE_STALL
        };

        const auto index = EnumValue(rideType);
        Guard::ArgumentInRange<size_t>(index, 0, std::size(map), "Unsupported RCT1 ride type.");

        return map[index];
    }

    const char * GetVehicleObject(uint8_t vehicleType)
    {
        static constexpr const char * map[] =
        {
            "SCHT1   ",  // RCT1_VEHICLE_TYPE_STEEL_ROLLER_COASTER_TRAIN
            "SCHT1   ",  // RCT1_VEHICLE_TYPE_STEEL_ROLLER_COASTER_TRAIN_BACKWARDS
            "PTCT1   ",  // RCT1_VEHICLE_TYPE_WOODEN_ROLLER_COASTER_TRAIN
            "SLCT    ",  // RCT1_VEHICLE_TYPE_INVERTED_COASTER_TRAIN (Not in RCT2)
            "ARRSW1  ",  // RCT1_VEHICLE_TYPE_SUSPENDED_SWINGING_CARS
            "ZLDB    ",  // RCT1_VEHICLE_TYPE_LADYBIRD_CARS
            "TOGST   ",  // RCT1_VEHICLE_TYPE_STANDUP_ROLLER_COASTER_CARS
            "WMSPIN  ",  // RCT1_VEHICLE_TYPE_SPINNING_CARS
            "BATFL   ",  // RCT1_VEHICLE_TYPE_SINGLE_PERSON_SWINGING_CHAIRS
            "SWANS   ",  // RCT1_VEHICLE_TYPE_SWANS_PEDAL_BOATS
            "MONO1   ",  // RCT1_VEHICLE_TYPE_LARGE_MONORAIL_TRAIN
            "CBOAT   ",  // RCT1_VEHICLE_TYPE_CANOES
            "RBOAT   ",  // RCT1_VEHICLE_TYPE_ROWING_BOATS
            "NRL     ",  // RCT1_VEHICLE_TYPE_STEAM_TRAIN
            "WMOUSE  ",  // RCT1_VEHICLE_TYPE_WOODEN_MOUSE_CARS
            "BBOAT   ",  // RCT1_VEHICLE_TYPE_BUMPER_BOATS
            "PTCT1   ",  // RCT1_VEHICLE_TYPE_WOODEN_ROLLER_COASTER_TRAIN_BACKWARDS
            "RCKC    ",  // RCT1_VEHICLE_TYPE_ROCKET_CARS
            "STEEP1  ",  // RCT1_VEHICLE_TYPE_HORSES // Steeplechase
            "SPCAR   ",  // RCT1_VEHICLE_TYPE_SPORTSCARS
            "SKYTR   ",  // RCT1_VEHICLE_TYPE_LYING_DOWN_SWINGING_CARS (Inverted single-rail)
            "WMMINE  ",  // RCT1_VEHICLE_TYPE_WOODEN_MINE_CARS
            "ARRSW2  ",  // RCT1_VEHICLE_TYPE_SUSPENDED_SWINGING_AIRPLANE_CARS
            "MONO2   ",  // RCT1_VEHICLE_TYPE_SMALL_MONORAIL_CARS
            "TRIKE   ",  // RCT1_VEHICLE_TYPE_WATER_TRICYCLES
            "SSC1    ",  // RCT1_VEHICLE_TYPE_LAUNCHED_FREEFALL_CAR
            "BOB1    ",  // RCT1_VEHICLE_TYPE_BOBSLEIGH_CARS
            "DING1   ",  // RCT1_VEHICLE_TYPE_DINGHIES
            "OBS1    ",  // RCT1_VEHICLE_TYPE_ROTATING_CABIN
            "AMT1    ",  // RCT1_VEHICLE_TYPE_MINE_TRAIN
            "CLIFT1  ",  // RCT1_VEHICLE_TYPE_CHAIRLIFT_CARS
            "ARRT1   ",  // RCT1_VEHICLE_TYPE_CORKSCREW_ROLLER_COASTER_TRAIN
            "STEEP2  ",  // RCT1_VEHICLE_TYPE_MOTORBIKES
            "RCR     ",  // RCT1_VEHICLE_TYPE_RACING_CARS
            "TRUCK1  ",  // RCT1_VEHICLE_TYPE_TRUCKS
            "KART1   ",  // RCT1_VEHICLE_TYPE_GO_KARTS
            "RAPBOAT ",  // RCT1_VEHICLE_TYPE_RAPIDS_BOATS
            "LFB1    ",  // RCT1_VEHICLE_TYPE_LOG_FLUME_BOATS
            "DODG1   ",  // RCT1_VEHICLE_TYPE_DODGEMS
            "SWSH1   ",  // RCT1_VEHICLE_TYPE_SWINGING_SHIP
            "SWSH2   ",  // RCT1_VEHICLE_TYPE_SWINGING_INVERTER_SHIP
            "MGR1    ",  // RCT1_VEHICLE_TYPE_MERRY_GO_ROUND
            "FWH1    ",  // RCT1_VEHICLE_TYPE_FERRIS_WHEEL
            "SIMPOD  ",  // RCT1_VEHICLE_TYPE_SIMULATOR_POD
            "C3D     ",  // RCT1_VEHICLE_TYPE_CINEMA_BUILDING
            "TOPSP1  ",  // RCT1_VEHICLE_TYPE_TOPSPIN_CAR
            "SRINGS  ",  // RCT1_VEHICLE_TYPE_SPACE_RINGS
            "REVF1   ",  // RCT1_VEHICLE_TYPE_REVERSE_FREEFALL_ROLLER_COASTER_CAR
            "BMVD    ",  // RCT1_VEHICLE_TYPE_VERTICAL_ROLLER_COASTER_CARS
            "CTCAR   ",  // RCT1_VEHICLE_TYPE_CAT_CARS
            "TWIST1  ",  // RCT1_VEHICLE_TYPE_TWIST_ARMS_AND_CARS
            "HHBUILD ",  // RCT1_VEHICLE_TYPE_HAUNTED_HOUSE_BUILDING
            "ZLOG    ",  // RCT1_VEHICLE_TYPE_LOG_CARS
            "CIRCUS1 ",  // RCT1_VEHICLE_TYPE_CIRCUS_TENT
            "GTC     ",  // RCT1_VEHICLE_TYPE_GHOST_TRAIN_CARS
            "BMSD    ",  // RCT1_VEHICLE_TYPE_STEEL_TWISTER_ROLLER_COASTER_TRAIN
            "MFT     ",  // RCT1_VEHICLE_TYPE_WOODEN_TWISTER_ROLLER_COASTER_TRAIN
            "SFRIC1  ",  // RCT1_VEHICLE_TYPE_WOODEN_SIDE_FRICTION_CARS
            "VCR     ",  // RCT1_VEHICLE_TYPE_VINTAGE_CARS
            "NRL2    ",  // RCT1_VEHICLE_TYPE_STEAM_TRAIN_COVERED_CARS
            "BMSU    ",  // RCT1_VEHICLE_TYPE_STAND_UP_STEEL_TWISTER_ROLLER_COASTER_TRAIN
            "BMFL    ",  // RCT1_VEHICLE_TYPE_FLOORLESS_STEEL_TWISTER_ROLLER_COASTER_TRAIN
            "SMC1    ",  // RCT1_VEHICLE_TYPE_STEEL_MOUSE_CARS
            "CLIFT2  ",  // RCT1_VEHICLE_TYPE_CHAIRLIFT_CARS_ALTERNATIVE
            "SMONO   ",  // RCT1_VEHICLE_TYPE_SUSPENDED_MONORAIL_TRAIN
            "HELICAR ",  // RCT1_VEHICLE_TYPE_HELICOPTER_CARS
            "VREEL   ",  // RCT1_VEHICLE_TYPE_VIRGINIA_REEL_TUBS
            "REVCAR  ",  // RCT1_VEHICLE_TYPE_REVERSER_CARS
            "GOLF1   ",  // RCT1_VEHICLE_TYPE_GOLFERS
            "SPBOAT  ",  // RCT1_VEHICLE_TYPE_RIVER_RIDE_BOATS
            "VEKST   ",  // RCT1_VEHICLE_TYPE_FLYING_ROLLER_COASTER_TRAIN
            "BMRB    ",  // RCT1_VEHICLE_TYPE_NON_LOOPING_STEEL_TWISTER_ROLLER_COASTER_TRAIN
            "UTCAR   ",  // RCT1_VEHICLE_TYPE_HEARTLINE_TWISTER_CARS
            "UTCARR  ",  // RCT1_VEHICLE_TYPE_HEARTLINE_TWISTER_CARS_REVERSED
            "        ",  // RCT1_VEHICLE_TYPE_RESERVED
            "GDROP1  ",  // RCT1_VEHICLE_TYPE_ROTODROP_CAR
            "FSAUC   ",  // RCT1_VEHICLE_TYPE_FLYING_SAUCERS
            "CHBUILD ",  // RCT1_VEHICLE_TYPE_CROOKED_HOUSE_BUILDING
            "MONBK   ",  // RCT1_VEHICLE_TYPE_BICYCLES
            "ARRT2   ",  // RCT1_VEHICLE_TYPE_HYPERCOASTER_TRAIN
            "NEMT    ",  // RCT1_VEHICLE_TYPE_4_ACROSS_INVERTED_COASTER_TRAIN
            "CSTBOAT ",  // RCT1_VEHICLE_TYPE_WATER_COASTER_BOATS
            "SLCFO   ",  // RCT1_VEHICLE_TYPE_FACEOFF_CARS
            "JSKI    ",  // RCT1_VEHICLE_TYPE_JET_SKIS
            "RFTBOAT ",  // RCT1_VEHICLE_TYPE_RAFT_BOATS
            "AML1    ",  // RCT1_VEHICLE_TYPE_AMERICAN_STYLE_STEAM_TRAIN
            "THCAR   ",  // RCT1_VEHICLE_TYPE_AIR_POWERED_COASTER_TRAIN
            "IVMC1   ",  // RCT1_VEHICLE_TYPE_SUSPENDED_WILD_MOUSE_CARS (Inverted Hairpin in RCT2)
            "ENTERP  ",  // RCT1_VEHICLE_TYPE_ENTERPRISE_WHEEL
        };

        Guard::ArgumentInRange<size_t>(vehicleType, 0, std::size(map), "Unsupported RCT1 vehicle type.");
        return map[vehicleType];
    }

    const char * GetSmallSceneryObject(uint8_t smallSceneryType)
    {
        static constexpr const char * map[] =
        {
            "TL0     ",
            "TL1     ",
            "TL2     ",
            "TL3     ",
            "TM0     ",
            "TM1     ",
            "TM2     ",
            "TM3     ",
            "TS0     ",
            "TS1     ",
            "TS2     ",
            "TS3     ",
            "TS4     ",
            "TS5     ",
            "TS6     ",
            "TIC     ",
            "TLC     ",
            "TMC     ",
            "TMP     ",
            "TITC    ",
            "TGHC    ",
            "TAC     ",
            "TGHC2   ",
            "TCJ     ",
            "TMBJ    ",
            "TCF     ",
            "TCL     ",
            "TRF     ",
            "TRF2    ",
            "TEL     ",
            "TAP     ",
            "TSP     ",
            "TMZP    ",
            "TCRP    ",
            "TBP     ",
            "TLP     ",
            "TWP     ",
            "TAS     ",
            "TMG     ",
            "TWW     ",
            "TSB     ",
            "TVL     ",
            "TCT     ",
            "TEF     ",
            "TAL     ",
            "TSQ     ",
            "THT     ",
            "TCB     ",
            "TDM     ",
            "TSD     ",
            "TGS     ",
            "TUS     ",
            "TH1     ",
            "TBC     ",
            "TH2     ",
            "TPM     ",
            "TSC     ",
            "TG1     ",
            "TWF     ",
            "TSH0    ",
            "TSH1    ",
            "TSH2    ",
            "TSH3    ",
            "TSH4    ",
            "TSH5    ",
            "TG2     ",
            "TG3     ",
            "TG4     ",
            "TG5     ",
            "TG6     ",
            "TG7     ",
            "TG8     ",
            "TG9     ",
            "TG10    ",
            "TG11    ",
            "TG12    ",
            "TG13    ",
            "TG14    ",
            "TT1     ",
            "TDF     ",
            "TSH     ",
            "THRS    ",
            "TSTD    ",
            "TRMS    ",
            "TRWS    ",
            "TRC     ",
            "TQF     ",
            "TES1    ",
            "TEN     ",
            "TERS    ",
            "TERB    ",
            "TEP     ",
            "TST1    ",
            "TST2    ",
            "TMS1    ",
            "TAS1    ",
            "TAS2    ",
            "TAS3    ",
            "TST3    ",
            "TST4    ",
            "TST5    ",
            "TAS4    ",
            "TCY     ",
            "TBW     ",
            "TBR1    ",
            "TBR2    ",
            "TML     ",
            "TMW     ",
            "TBR3    ",
            "TBR4    ",
            "TMJ     ",
            "TBR     ",
            "TMO1    ",
            "TMO2    ",
            "TMO3    ",
            "TMO4    ",
            "TMO5    ",
            "TWH1    ",
            "TWH2    ",
            "TNS     ",
            "TP1     ",
            "TP2     ",
            "TK1     ",
            "TK2     ",
            "TR1     ",
            "TR2     ",
            "TQ1     ",
            "TQ2     ",
            "TWN     ",
            "TCE     ",
            "TCO     ",
            "THL     ",
            "TCC     ",
            "TB1     ",
            "TB2     ",
            "TK3     ",
            "TK4     ",
            "TBN     ",
            "TBN1    ",
            "TDT1    ",
            "TDT2    ",
            "TDT3    ",
            "TMM1    ",
            "TMM2    ",
            "TMM3    ",
            "TGS1    ",
            "TGS2    ",
            "TGS3    ",
            "TGS4    ",
            "TDN4    ",
            "TDN5    ",
            "TJT1    ",
            "TJT2    ",
            "TJB1    ",
            "TTF     ",
            "TF1     ",
            "TF2     ",
            "TGE1    ",
            "TJT3    ",
            "TJT4    ",
            "TJP1    ",
            "TJB2    ",
            "TGE2    ",
            "TJT5    ",
            "TJB3    ",
            "TJB4    ",
            "TJT6    ",
            "TJP2    ",
            "TGE3    ",
            "TCK     ",
            "TGE4    ",
            "TGE5    ",
            "TG15    ",
            "TG16    ",
            "TG17    ",
            "TG18    ",
            "TG19    ",
            "TG20    ",
            "TG21    ",
            "TSM     ",
            "TIG     ",
            "TCFS    ",
            "TRFS    ",
            "TRF3    ",
            "TNSS    ",
            "TCT1    ",
            "TCT2    ",
            "TSF1    ",
            "TSF2    ",
            "TSF3    ",
            "TCN     ",
            "TTG     ",
            "TSNC    ",
            "TSNB    ",
            "TSCP    ",
            "TCD     ",
            "TSG     ",
            "TSK     ",
            "TGH1    ",
            "TGH2    ",
            "TSMP    ",
            "TJF     ",
            "TLY     ",
            "TGC1    ",
            "TGC2    ",
            "TGG     ",
            "TSPH    ",
            "TOH1    ",
            "TOH2    ",
            "TOT1    ",
            "TOT2    ",
            "TOS     ",
            "TOT3    ",
            "TOT4    ",
            "TSC2    ",
            "TSP1    ",
            "TOH3    ",
            "TSP2    ",
            "ROMROOF1",
            "GEOROOF1",
            "TNTROOF1",
            "JNGROOF1",
            "MINROOF1",
            "ROMROOF2",
            "GEOROOF2",
            "PAGROOF1",
            "SPCROOF1",
            "ROOF1   ",
            "ROOF2   ",
            "ROOF3   ",
            "ROOF4   ",
            "ROOF5   ",
            "ROOF6   ",
            "ROOF7   ",
            "ROOF8   ",
            "ROOF9   ",
            "ROOF10  ",
            "ROOF11  ",
            "ROOF12  ",
            "ROOF13  ",
            "ROOF14  ",
            "IGROOF  ",
            "CORROOF ",
            "CORROOF2",
        };
        return map[smallSceneryType];
    }

    const char * GetLargeSceneryObject(uint8_t largeSceneryType)
    {
        static constexpr const char * map[] =
        {
            "SCOL    ",
            "SHS1    ",
            "SSPX    ",
            "SHS2    ",
            "SCLN    ",
            "SMH1    ",
            "SMH2    ",
            "SVLC    ",
            "SPYR    ",
            "SMN1    ",
            "SMB     ",
            "SSK1    ",
            "SDN1    ",
            "SDN2    ",
            "SDN3    ",
            "SIP     ",
            "STB1    ",
            "STB2    ",
            "STG1    ",
            "STG2    ",
            "SCT     ",
            "SOH1    ",
            "SOH2    ",
            "SOH3    ",
            "SGP     ",
            "SSR     ",
            "STH     ",
            "SAH     ",
            "SPS     ",
            "SPG     ",
            "SOB     ",
            "SAH2    ",
            "SST     ",
            "SSH     ",
            "SAH3    ",
            "SSIG1   ",
            "SSIG2   ",
            "SSIG3   ",
            "SSIG4   ",
        };
        return map[largeSceneryType];
    }

    const char * GetWallObject(uint8_t wallType)
    {
        static constexpr const char * map[] =
        {
            "WMF     ", // RCT1_WALL_TYPE_MESH_FENCE         
            "WMFG    ", // RCT1_WALL_TYPE_MESH_FENCE_WITH_GATE         
            "WRW     ", // RCT1_WALL_TYPE_ROMAN         
            "WEW     ", // RCT1_WALL_TYPE_EGYPTIAN         
            "WHG     ", // RCT1_WALL_TYPE_HEDGE         
            "WHGG    ", // RCT1_WALL_TYPE_HEDGE_WITH_GATE         
            "WCW1    ", // RCT1_WALL_TYPE_BLUE_PLAYING_CARDS         
            "WCW2    ", // RCT1_WALL_TYPE_RED_PLAYING_CARDS         
            "WSW     ", // RCT1_WALL_TYPE_WHITE_RAILING         
            "WSWG    ", // RCT1_WALL_TYPE_WHITE_RAILING_WITH_GATE         
            "WMW     ", // RCT1_WALL_TYPE_MARTIAN         
            "WALLGL16", // RCT1_WALL_TYPE_GLASS_SMOOTH         
            "WFW1    ", // RCT1_WALL_TYPE_WOODEN_PANEL_FENCE         
            "WFWG    ", // RCT1_WALL_TYPE_WOODEN_PANEL_FENCE_WITH_GATE         
            "WPW1    ", // RCT1_WALL_TYPE_WOODEN_POST_FENCE         
            "WPW2    ", // RCT1_WALL_TYPE_RED_WOODEN_POST_FENCE         
            "WPF     ", // RCT1_WALL_TYPE_BARBED_WIRE         
            "WPFG    ", // RCT1_WALL_TYPE_BARBED_WIRE_WITH_GATE         
            "WWTW    ", // RCT1_WALL_TYPE_PRIMITIVE_TALL_WOOD_FENCE         
            "WMWW    ", // RCT1_WALL_TYPE_PRIMITIVE_SHORT_WOOD_FENCE         
            "WSW1    ", // RCT1_WALL_TYPE_IRON_RAILING         
            "WSW2    ", // RCT1_WALL_TYPE_IRON_RAILING_WITH_GATE         
            "WGW2    ", // RCT1_WALL_TYPE_GLASS_PANELS         
            "WBW     ", // RCT1_WALL_TYPE_BONE_FENCE         
            "WBR1    ", // RCT1_WALL_TYPE_BRICK         
            "WBRG    ", // RCT1_WALL_TYPE_BRICK_WITH_GATE         
            "WFW1    ", // RCT1_WALL_TYPE_WHITE_WOODEN_PANEL_FENCE         
            "WFW1    ", // RCT1_WALL_TYPE_RED_WOODEN_PANEL_FENCE         
            "WBR2    ", // RCT1_WALL_TYPE_STONE         
            "WBR3    ", // RCT1_WALL_TYPE_STONE_WITH_GATE         
            "WPW3    ", // RCT1_WALL_TYPE_WOODEN_FENCE         
            "WJF     ", // RCT1_WALL_TYPE_JUNGLE         
            "WCH     ", // RCT1_WALL_TYPE_CONIFER_HEDGE         
            "WCHG    ", // RCT1_WALL_TYPE_CONIFER_HEDGE_WITH_GATE         
            "WC1     ", // RCT1_WALL_TYPE_SMALL_BROWN_CASTLE         
            "WC2     ", // RCT1_WALL_TYPE_SMALL_GREY_CASTLE         
            "WC3     ", // RCT1_WALL_TYPE_ROMAN_COLUMN         
            "WC4     ", // RCT1_WALL_TYPE_LARGE_BROWN_CASTLE         
            "WC5     ", // RCT1_WALL_TYPE_LARGE_BROWN_CASTLE_CROSS         
            "WC6     ", // RCT1_WALL_TYPE_LARGE_BROWN_CASTLE_GATE         
            "WC7     ", // RCT1_WALL_TYPE_LARGE_BROWN_CASTLE_WINDOW         
            "WC8     ", // RCT1_WALL_TYPE_MEDIUM_BROWN_CASTLE         
            "WC9     ", // RCT1_WALL_TYPE_LARGE_GREY_CASTLE         
            "WC10    ", // RCT1_WALL_TYPE_LARGE_GREY_CASTLE_CROSS         
            "WC11    ", // RCT1_WALL_TYPE_LARGE_GREY_CASTLE_GATE         
            "WC12    ", // RCT1_WALL_TYPE_LARGE_GREY_CASTLE_WINDOW         
            "WC13    ", // RCT1_WALL_TYPE_MEDIUM_GREY_CASTLE         
            "WC14    ", // RCT1_WALL_TYPE_CREEPY         
            "WC15    ", // RCT1_WALL_TYPE_CREEPY_GATE         
            "WC16    ", // RCT1_WALL_TYPE_BARBED_WIRE_WITH_SNOW         
            "WC17    ", // RCT1_WALL_TYPE_WOODEN_PANEL_FENCE_WITH_SNOW         
            "WC18    ", // RCT1_WALL_TYPE_WOODEN_POST_FENCE_WITH_SNOW
        };
        if (wallType < std::size(map))
            return map[wallType];

        return map[0];
    }

    const char * GetPathObject(uint8_t pathType)
    {
        static constexpr const char * map[] =
        {
            "TARMAC  ",  // RCT1_FOOTPATH_TYPE_QUEUE_BLUE
            "PATHSPCE",  // RCT1_FOOTPATH_TYPE_QUEUE_RED
            "PATHDIRT",  // RCT1_FOOTPATH_TYPE_QUEUE_YELLOW
            "TARMACG ",  // RCT1_FOOTPATH_TYPE_QUEUE_GREEN

            "TARMAC  ",  // RCT1_FOOTPATH_TYPE_TARMAC_GRAY
            "PATHSPCE",  // RCT1_FOOTPATH_TYPE_TARMAC_RED
            "TARMACB ",  // RCT1_FOOTPATH_TYPE_TARMAC_BROWN
            "TARMACG ",  // RCT1_FOOTPATH_TYPE_TARMAC_GREEN

            "PATHDIRT",  // RCT1_FOOTPATH_TYPE_DIRT_RED
            "PATHASH ",  // RCT1_FOOTPATH_TYPE_DIRT_BLACK
            "        ",
            "        ",

            "PATHCRZY",  // RCT1_FOOTPATH_TYPE_CRAZY_PAVING
            "        ",
            "        ",
            "        ",

            "ROAD    ",  // RCT1_FOOTPATH_TYPE_ROADS
            "        ",
            "        ",
            "        ",

            "PATHCRZY",  // RCT1_FOOTPATH_TYPE_TILE_PINK
            "PATHCRZY",  // RCT1_FOOTPATH_TYPE_TILE_GRAY
            "PATHCRZY",  // RCT1_FOOTPATH_TYPE_TILE_RED
            "PATHCRZY",  // RCT1_FOOTPATH_TYPE_TILE_GREEN
        };
        return map[pathType];
    }

    const char * GetPathAddtionObject(uint8_t pathAdditionType)
    {
        static constexpr const char * map[] =
        {
            "        ",  // RCT1_PATH_ADDITION_NONE
            "LAMP1   ",  // RCT1_PATH_ADDITION_LAMP_1
            "LAMP2   ",  // RCT1_PATH_ADDITION_LAMP_2
            "LITTER1 ",  // RCT1_PATH_ADDITION_BIN
            "BENCH1  ",  // RCT1_PATH_ADDITION_BENCH
            "JUMPFNT1",  // RCT1_PATH_ADDITION_JUMPING_FOUNTAIN
            "LAMP3   ",  // RCT1_PATH_ADDITION_LAMP_3
            "LAMP4   ",  // RCT1_PATH_ADDITION_LAMP_4
            "LAMP1   ",  // RCT1_PATH_ADDITION_BROKEN_LAMP_1
            "LAMP2   ",  // RCT1_PATH_ADDITION_BROKEN_LAMP_2
            "LITTER1 ",  // RCT1_PATH_ADDITION_BROKEN_BIN
            "BENCH1  ",  // RCT1_PATH_ADDITION_BROKEN_BENCH
            "LAMP3   ",  // RCT1_PATH_ADDITION_BROKEN_LAMP_3
            "LAMP4   ",  // RCT1_PATH_ADDITION_BROKEN_LAMP_4
            "JUMPSNW1",  // RCT1_PATH_ADDITION_JUMPING_SNOW
        };
        return map[pathAdditionType];
    }

    const char * GetSceneryGroupObject(uint8_t sceneryGroupType)
    {
        static constexpr const char * map[] =
        {
            "        ", // RCT1_SCENERY_THEME_GENERAL
            "SCGMINE ", // RCT1_SCENERY_THEME_MINE
            "SCGCLASS", // RCT1_SCENERY_THEME_CLASSICAL_ROMAN
            "SCGEGYPT", // RCT1_SCENERY_THEME_EGYPTIAN
            "SCGMART ", // RCT1_SCENERY_THEME_MARTIAN
            "        ", // RCT1_SCENERY_THEME_JUMPING_FOUNTAINS
            "SCGWOND ", // RCT1_SCENERY_THEME_WONDERLAND
            "SCGJURAS", // RCT1_SCENERY_THEME_JURASSIC
            "SCGSPOOK", // RCT1_SCENERY_THEME_SPOOKY
            "SCGJUNGL", // RCT1_SCENERY_THEME_JUNGLE
            "SCGABSTR", // RCT1_SCENERY_THEME_ABSTRACT
            "        ", // RCT1_SCENERY_THEME_GARDEN_CLOCK
            "SCGSNOW ", // RCT1_SCENERY_THEME_SNOW_ICE
            "SCGMEDIE", // RCT1_SCENERY_THEME_MEDIEVAL
            "SCGSPACE", // RCT1_SCENERY_THEME_SPACE
            "SCGHALLO", // RCT1_SCENERY_THEME_CREEPY
            "SCGURBAN", // RCT1_SCENERY_THEME_URBAN
            "SCGORIEN", // RCT1_SCENERY_THEME_PAGODA
        };
        return map[sceneryGroupType];
    }

    const char * GetWaterObject(uint8_t waterType)
    {
        static constexpr const char * map[] =
        {
            "WTRCYAN ",
            "WTRORNG ",
        };
        return map[waterType];
    }

    const std::vector<const char *> GetSceneryObjects(uint8_t sceneryType)
    {
        static const std::vector<const char *> map[] =
        {
            // RCT1_SCENERY_THEME_GENERAL (trees, shrubs, garden, walls, fence, path accessories)
            { "TIC     ", "TLC     ", "TMC     ", "TMP     ", "TITC    ", "TGHC    ", "TAC     ", "TGHC2   ", "TCJ     ", "TMBJ    ", "TCF     ", "TCL     ", "TRF     ", "TRF2    ", "TEL     ", "TAP     ", "TSP     ", "TMZP    ", "TCRP    ", "TBP     ", "TLP     ", "TWP     ", "TAS     ", "TMG     ", "TWW     ", "TSB     ", "TVL     ", "TCY     ", "TNS     ", "TWN     ", "TCE     ", "TCO     ", "THL     ", "TCC     ", "TF1     ", "TF2     ", "TCT     ", "TH1     ", "TH2     ", "TPM     ", "TROPT1  ",
              "TS0     ", "TS1     ", "TS2     ", "TS3     ", "TS4     ", "TS5     ", "TS6     ", "TEF     ", "TAL     ", "TSQ     ", "THT     ", "TCB     ", "TDM     ", "TSD     ", "TORN1   ", "TORN2   ", "TGS     ", "TUS     ", "TBC     ", "TSC     ", "TWF     ", "TSH0    ", "TSH1    ", "TSH2    ", "TSH3    ", "TSH4    ", "TSH5    ", "TDF     ", "TSH     ", "THRS    ", "TSTD    ", "TBR     ", "TTF     ", "WHG     ", "WHGG    ", "WCH     ", "WCHG    ",
              "TG1     ", "TG2     ", "TG3     ", "TG4     ", "TG5     ", "TG6     ", "TG7     ", "TG8     ", "TG9     ", "TG10    ", "TG11    ", "TG12    ", "TG13    ", "TG14    ", "TG15    ", "TG16    ", "TG17    ", "TG18    ", "TG19    ", "TG20    ", "TG21    ",
              "WBR1A   ", "WBR2A   ", "WALLBB34", "WALLTN32", "TNTROOF1", "WALLBB33", "WALLBB32", "WALLBB16", "WALLBB8 ", "ROOF5   ", "ROOF7   ", "WALLRS32", "WALLRS16", "WALLRS8 ", "WALLBR32", "WALLBR16", "WALLBR8 ", "WALLBRDR", "WALLBRWN", "BRBASE  ", "ROOF1   ", "ROOF2   ", "ROOF3   ", "ROOF4   ", "WALLCB32", "WALLCB16", "WALLCB8 ", "WALLCBDR", "WALLCBWN", "BRBASE2 ", "CWBCRV33", "CWBCRV32", "BRCRRF1 ", "ROOF6   ", "ROOF8   ", "WALLCF32", "WALLCF16", "WALLCF8 ", "WALLCFDR", "WALLCFWN", "WALLCFAR", "BRBASE3 ", "CWFCRV33", "CWFCRV32", "BRCRRF2 ", "ROOF9   ", "ROOF11  ", "ROOF10  ", "ROOF12  ", "CORROOF2", "WALLCO16", "CORROOF ", "WALLLT32", "WALLSK16", "WALLSK32", "SKTDW2  ", "SKTDW   ", "SKTBASE ", "SKTBASET", "SUPPW2  ", "SUPPW1  ", "SUPPW3  ", "SUPPLEG1", "SUPPLEG2", "SUMRF   ", "WALLRH32",
              "WMF     ", "WMFG    ", "WSW     ", "WSWG    ", "WFW1    ", "WFWG    ", "WPF     ", "WPFG    ", "WSW1    ", "WSW2    ", "WBR1    ", "WBRG    ", "WBR2    ", "WBR3    ", "WALLMM16", "WALLMM17",
              "LAMP1   ", "LAMP2   ", "LITTER1 ", "BENCH1  ", "QTV1    ", "BN1     ", "WALLPOST", "WALLSIGN", "SSIG1   ", "SSIG2   ", "SSIG3   ", "SSIG4   " },
            // RCT1_SCENERY_THEME_MINE
            { "SMH1    ", "SMH2    ", "SMN1    ", "TBW     ", "TBR1    ", "TBR2    ", "TML     ", "TMW     ", "TBR3    ", "TBR4    ", "TMJ     ", "BN5     ", "WALLWD8 ", "WALLWD16", "WALLWD32", "WALLWD33", "WALLMN32", "WDBASE  ", "MINROOF1", "ROOF13  ", "LITTERMN" },
            // RCT1_SCENERY_THEME_CLASSICAL_ROMAN
            { "SCOL    ", "TT1     ", "TRMS    ", "TRWS    ", "TRC     ", "TQF     ", "WRW     ", "WRWA    ", "ROMROOF2", "WC3     ", "ROMROOF1", "BN3     " },
            // RCT1_SCENERY_THEME_EGYPTIAN
            { "SSPX    ", "SCLN    ", "SPYR    ", "TES1    ", "TEN     ", "TERS    ", "TERB    ", "TEP     ", "WEW     ", "LAMP3   ", "BN4     ", "BENCHSTN" },
            // RCT1_SCENERY_THEME_MARTIAN
            { "SMB     ", "TMO1    ", "TMO2    ", "TMO3    ", "TMO4    ", "TMO5    ", "SVLC    ", "WMW     ", "LAMP4   " },
            // RCT1_SCENERY_THEME_JUMPING_FOUNTAINS (Single researchable scenery item)
            { "JUMPFNT1" },
            // RCT1_SCENERY_THEME_WONDERLAND
            { "TWH1    ", "TWH2    ", "TST1    ", "TST2    ", "TMS1    ", "TST3    ", "TST4    ", "TST5    ", "TAS1    ", "TAS2    ", "TAS3    ", "TAS4    ", "CHBBASE ", "TP1     ", "TP2     ", "TK1     ", "TK2     ", "TR1     ", "TR2     ", "TQ1     ", "TQ2     ", "TB1     ", "TB2     ", "TK3     ", "TK4     ", "WCW1    ", "WCW2    " },
            // RCT1_SCENERY_THEME_JURASSIC
            { "TBN     ", "TBN1    ", "TDN4    ", "TDN5    ", "SDN1    ", "SDN2    ", "SDN3    ", "WWTW    ", "WMWW    ", "WWTWA   ", "WBW     ", "BN6     " },
            // RCT1_SCENERY_THEME_SPOOKY,
            { "SSK1    ", "TDT1    ", "TDT2    ", "TDT3    ", "TMM1    ", "TMM2    ", "TMM3    ", "TGS1    ", "TGS2    ", "TGS3    ", "TGS4    ", "SMSKULL ", "WALLRK32" },
            // RCT1_SCENERY_THEME_JUNGLE
            { "TJT1    ", "TJT2    ", "TJB1    ", "TJT3    ", "TJT4    ", "TJP1    ", "TJB2    ", "TJT5    ", "TJB3    ", "TJB4    ", "TJT6    ", "TJP2    ", "TJF     ", "WPW1    ", "WPW2    ", "WJF     ", "BN2     ", "WALLJN32", "JNGROOF1", "ROOF14  ", "BENCHLOG" },
            // RCT1_SCENERY_THEME_ABSTRACT
            { "TGE1    ", "TGE2    ", "TGE3    ", "TGE4    ", "TGE5    ", "TGC1    ", "TGC2    ", "WALLGL8 ", "WALLGL16", "WALLGL32", "GEOROOF1", "WGW2    ", "GEOROOF2" },
            // RCT1_SCENERY_THEME_GARDEN_CLOCK (Single researchable scenery item)
            { "TCK     " },
            // RCT1_SCENERY_THEME_SNOW_ICE
            { "SIP     ", "TSM     ", "TIG     ", "TSF1    ", "TSF2    ", "TSF3    ", "TSNC    ", "TSNB    ", "WC16    ", "WC17    ", "WC18    ", "JUMPSNW1", "TCFS    ", "TRFS    ", "TRF3    ", "TNSS    ", "BN8     ", "WALLIG16", "WALLIG24", "IGROOF  " },
            // RCT1_SCENERY_THEME_MEDIEVAL
            { "TCT1    ", "STB1    ", "STB2    ", "WC1     ", "WC4     ", "WC5     ", "WC6     ", "WC7     ", "WC8     ", "WALLCZ32", "WALLCY32", "TCT2    ", "STG1    ", "STG2    ", "WC2     ", "WC9     ", "WC10    ", "WC11    ", "WC12    ", "WC13    ", "WALLCW32", "WALLCX32", "TCN     ", "TTG     ", "SCT     ", "SOH1    ", "SOH2    ", "SOH3    ", "WPW3    ", "WALLCFPC", "WALLCBPC" },
            // RCT1_SCENERY_THEME_SPACE
            { "SSR     ", "SST     ", "SSH     ", "TSCP    ", "TSPH    ", "TSC2    ", "TSP1    ", "TSP2    ", "WALLSP32", "SPCROOF1", "BN9     ", "BENCHSPC", "LITTERSP" },
            // RCT1_SCENERY_THEME_CREEPY
            { "TCD     ", "TSG     ", "TSK     ", "TGH1    ", "TGH2    ", "TSMP    ", "SGP     ", "WC14    ", "WC15    ", "TL0     ", "TL1     ", "TL2     ", "TL3     ", "TM0     ", "TM1     ", "TM2     ", "TM3     " },
            // RCT1_SCENERY_THEME_URBAN
            { "SHS1    ", "SHS2    ", "STH     ", "SAH     ", "SPS     ", "SAH2    ", "SAH3    ", "SOB     ", "WALLU132", "WALLU232" },
            // RCT1_SCENERY_THEME_PAGODA
            { "SPG     ", "TLY     ", "TGG     ", "TOH1    ", "TOH2    ", "TOT1    ", "TOT2    ", "TOS     ", "TOT3    ", "TOT4    ", "TOH3    ", "WALLPG32", "PAGROOF1", "BN7     " }
        };
        return map[sceneryType];
    }
    // clang-format on

    track_type_t RCT1TrackTypeToOpenRCT2(RCT12TrackType origTrackType, uint8_t rideType)
    {
        if (GetRideTypeDescriptor(rideType).HasFlag(RIDE_TYPE_FLAG_FLAT_RIDE))
            return RCT12FlatTrackTypeToOpenRCT2(origTrackType);

        return origTrackType;
    }
} // namespace RCT1
