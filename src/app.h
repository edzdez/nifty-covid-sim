#ifndef NIFTY_COVID_SIM_APP_H
#define NIFTY_COVID_SIM_APP_H

#include "bindings/imgui_impl_glfw.h"
#include "bindings/imgui_impl_opengl3.h"
#include <imgui.h>
#include <imgui_internal.h>

#include <GLFW/glfw3.h>
#include <fmt/core.h>
#include <thread>

#include "constants.h"
#include "state.h"

class App
{
  public:
    App(const char *title, int width, int height);
    ~App();

    App(App &) = delete;
    App(App &&) = delete;
    auto operator=(App &) = delete;
    auto operator=(App &&) = delete;

    auto run() -> void;
    auto update() -> void;

  private:
    const char *glslVersion;
    ImVec4 clearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    GLFWwindow *m_window;
    sim::State m_state;

    std::thread m_simulationThread;

  private:
    auto setup() -> void;

  private:
    static auto glfwErrorCallback(int error, const char *description) -> void;
    static auto simulation(sim::State &state) -> void;
};

#endif // NIFTY_COVID_SIM_APP_H
