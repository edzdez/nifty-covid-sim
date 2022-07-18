#include <GLFW/glfw3.h>
#include <fmt/core.h>

#include "app.h"
#include "constants.h"

auto main() -> int
{
    std::srand(time(nullptr));

    App app(sim::WINDOW_TITLE, sim::WINDOW_WIDTH, sim::WINDOW_HEIGHT);
    app.run();
}