#ifndef NIFTY_COVID_SIM_PERSON_H
#define NIFTY_COVID_SIM_PERSON_H

#include <cassert>
#include <cstdint>
#include <cstdlib>

#include "constants.h"

class Person
{
  public:
    enum class Status : uint8_t
    {
        Healthy = 0,
        Infected,
        Recovered,
        Deceased,
    };

    enum class TickResult : uint8_t
    {
        Ran = 0,
        Skipped,
        Died,
        Recovered,
    };

  public:
    Person() = default;

    [[nodiscard]] auto status() const -> Status;
    [[nodiscard]] auto isCompliant() const -> bool;
    [[nodiscard]] auto isContagious() const -> bool;

    auto setStatus(Status status) -> void;
    auto setCompliance(bool compliance) -> void;

    auto tick() -> TickResult;
    auto contact(Person &other) -> bool;

  private:
    Status m_status = Status::Healthy;
    bool m_compliant = true;
    int m_contagiousTimer = 4;

  private:
    auto die() -> void;
    auto recover() -> void;
};

#endif // NIFTY_COVID_SIM_PERSON_H
