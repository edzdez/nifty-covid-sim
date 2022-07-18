#include "randp.h"

RandP::RandP(int p_n) : m_nums(std::vector<int>(p_n)), m_nums_left(p_n)
{
    std::iota(m_nums.begin(), m_nums.end(), 0);
}

auto RandP::nextInt() -> std::optional<int>
{
    if (m_nums_left == 0)
        return {};

    int idx = std::rand() % m_nums_left--;

    int res = m_nums[idx];
    m_nums[idx] = m_nums[m_nums_left];

    return res;
}
