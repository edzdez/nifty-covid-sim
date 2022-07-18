#include "person.h"

auto Person::status() const -> Person::Status
{
    return m_status;
}

auto Person::isCompliant() const -> bool
{
    return m_compliant;
}

auto Person::isContagious() const -> bool
{
    return m_contagiousTimer != 0;
}

auto Person::setStatus(Person::Status status) -> void
{
    m_status = status;
}

auto Person::setCompliance(bool compliance) -> void
{
    m_compliant = compliance;
}

auto Person::tick() -> TickResult
{
    if (status() != Status::Infected)
        return TickResult::Skipped;

    --m_contagiousTimer;

    if (1 + std::rand() % 100 <= sim::DEATH_PROBABILITY)
    {
        die();
        return TickResult::Died;
    }
    else if (!isContagious())
    {
        recover();
        return TickResult::Recovered;
    }

    return TickResult::Ran;
}

auto Person::contact(Person &other) -> void
{
    // TODO
}

auto Person::die() -> void
{
    m_status = Status::Deceased;
}

auto Person::recover() -> void
{
    m_status = Status::Recovered;
}