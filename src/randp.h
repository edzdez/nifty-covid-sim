#ifndef NIFTY_COVID_SIM_RANDP_H
#define NIFTY_COVID_SIM_RANDP_H

#include <cstdlib>
#include <numeric>
#include <optional>
#include <vector>

class RandP
{
  public:
    explicit RandP(int n);
    auto nextInt() -> std::optional<int>;

  private:
    std::vector<int> m_nums;
    int m_nums_left;
};

#endif // NIFTY_COVID_SIM_RANDP_H
