#include "state.h"

sim::State::State()
{
    reset();
}

auto sim::State::reset() -> void
{
    m_deceased = 0;
    m_totalInfected = 0;
    m_currInfected = 0;
    m_newInfected = 0;
    m_noncompliant = 0;
    m_grid = std::vector<Person>(sim::ROWS * sim::COLS);

    pickNoncompliant();
    pickInfected();
}

auto sim::State::step() -> void
{
    pickNoncompliant();

    std::unordered_set<size_t> newInfections;
    for (int i = 0; i < sim::ROWS * sim::COLS; ++i)
    {
        auto &p1 = m_grid[i];
        if (p1.status() == Person::Status::Infected && p1.isContagious())
        {
            for (int dy = -1; dy <= 1; ++dy)
            {
                for (int dx = -1; dx <= 1; ++dx)
                {
                    if (dy == 0 && dx == 0)
                        continue;

                    int p2Idx = i + dx + (sim::COLS * dy);
                    if (p2Idx < 0 || p2Idx >= sim::COLS * sim::ROWS)
                        continue;

                    auto &p2 = m_grid[p2Idx];

                    if (p2.status() == Person::Status::Healthy && !(p1.isCompliant() && p2.isCompliant()))
                    {
                        if (1 + rand() % 100 <= INFECTION_PROBABILITY)
                            newInfections.insert(p2Idx);
                    }
                }
            }
        }
    }

    for (const auto &idx : newInfections)
    {
        m_grid[idx].setStatus(Person::Status::Infected);
        ++m_currInfected;
        ++m_totalInfected;
    }

    m_newInfected = static_cast<int>(newInfections.size());
    for (int idx = 0; idx < sim::COLS * sim::ROWS; ++idx)
    {
        if (!newInfections.contains(idx))
        {
            auto &p = m_grid[idx];
            switch (p.tick())
            {
            case Person::TickResult::Died:
                ++m_deceased;
            case Person::TickResult::Recovered:
                --m_currInfected;
                --m_newInfected;
                break;

            default:
                break;
            }
        }
    }
}

auto sim::State::dead() const -> bool
{
    return m_dead;
}

auto sim::State::deceased() const -> int
{
    return m_deceased;
}

auto sim::State::totalInfected() const -> int
{
    return m_totalInfected;
}

auto sim::State::currInfected() const -> int
{
    return m_currInfected;
}

auto sim::State::newInfected() const -> int
{
    return m_newInfected;
}

auto sim::State::nonCompliant() const -> int
{
    return m_noncompliant;
}

auto sim::State::grid() const -> const std::vector<Person> &
{
    return m_grid;
}

auto sim::State::grid() -> std::vector<Person> &
{
    return m_grid;
}

auto sim::State::setDead() -> void
{
    m_dead = true;
}

auto sim::State::percentSocialDistancing() -> int *
{
    return &m_percentSocialDistancing;
}

auto sim::State::pickNoncompliant() -> void
{
    for (auto &p : m_grid)
        p.setCompliance(true);

    auto expectedNoncompliant =
        static_cast<int>(std::round((ROWS * COLS) * static_cast<float>(100 - m_percentSocialDistancing) / 100));

    RandP randp(ROWS * COLS);

    int i;
    for (i = expectedNoncompliant - 1; i >= 0; --i)
    {
        auto n = randp.nextInt();
        if (n.has_value())
        {
            auto &person = m_grid[n.value()];

            if (person.status() != Person::Status::Deceased)
                person.setCompliance(false);
            else
                ++i;
        }
        else
            break;
    }

    m_noncompliant = expectedNoncompliant - i - 1;
}

auto sim::State::pickInfected() -> void
{
    m_currInfected = static_cast<int>(
        std::round((ROWS * COLS) * static_cast<float>(sim::INITIAL_INFECTED_POPULATION_PERCENT) / 100));
    m_totalInfected = m_currInfected;

    RandP randp(ROWS * COLS);
    for (int i = 0; i < m_totalInfected; ++i)
    {
        auto n = randp.nextInt();
        if (n.has_value())
        {
            auto &person = m_grid[n.value()];
            person.setStatus(Person::Status::Infected);
        }
    }
}
