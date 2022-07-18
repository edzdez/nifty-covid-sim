#ifndef NIFTY_COVID_SIM_CONSTANTS_H
#define NIFTY_COVID_SIM_CONSTANTS_H

#include <chrono>

namespace sim
{

constexpr static auto WINDOW_TITLE = "Nifty Covid Simulator";
constexpr static auto WINDOW_WIDTH = 1800;
constexpr static auto WINDOW_HEIGHT = 800;
constexpr static auto WINDOW_PADDING = 25;

constexpr static auto TIME_STEP = std::chrono::milliseconds(1000);
constexpr static auto ROWS = 107;
constexpr static auto COLS = 207;

constexpr static auto CELL_WIDTH = 7;
constexpr static auto CELL_HEIGHT = 7;

constexpr static auto INITIAL_PERCENT_SOCIAL_DISTANCING = 90;
constexpr static auto INFECTION_PROBABILITY = 75;
constexpr static auto DEATH_PROBABILITY = 3;
constexpr static auto INITIAL_INFECTED_POPULATION_PERCENT = 5;

}

#endif // NIFTY_COVID_SIM_CONSTANTS_H
