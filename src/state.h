#ifndef NIFTY_COVID_SIM_STATE_H
#define NIFTY_COVID_SIM_STATE_H

#include <cmath>
#include <mutex>
#include <vector>
#include <unordered_set>

#include "constants.h"
#include "person.h"
#include "randp.h"

namespace sim
{

class State
{
  public:
    State();

    auto reset() -> void;
    auto step() -> void;

    [[nodiscard]] auto dead() const -> bool;
    [[nodiscard]] auto deceased() const -> int;
    [[nodiscard]] auto totalInfected() const -> int;
    [[nodiscard]] auto currInfected() const -> int;
    [[nodiscard]] auto newInfected() const -> int;
    [[nodiscard]] auto nonCompliant() const -> int;
    [[nodiscard]] auto grid() -> std::vector<Person> &; // Can't wait for 'deducing this'
    [[nodiscard]] auto grid() const -> const std::vector<Person> &;

    auto setDead() -> void;

    [[nodiscard]] auto percentSocialDistancing() -> int *;

  public:
    std::mutex m_mutex;

  private:
    bool m_dead = false;

    int m_percentSocialDistancing = sim::INITIAL_PERCENT_SOCIAL_DISTANCING;
    int m_deceased = 0;
    int m_totalInfected = 0;
    int m_currInfected = 0;
    int m_newInfected = 0;
    int m_noncompliant = 0;

    std::vector<Person> m_grid = std::vector<Person>(sim::ROWS * sim::COLS);

  private:
    auto pickNoncompliant() -> void;
    auto pickInfected() -> void;
};

} // namespace sim

#endif // NIFTY_COVID_SIM_STATE_H
