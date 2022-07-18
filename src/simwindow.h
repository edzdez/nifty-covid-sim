#ifndef NIFTY_COVID_SIM_SIMWINDOW_H
#define NIFTY_COVID_SIM_SIMWINDOW_H

#include <algorithm>

static auto personStatusToColor(const Person::Status &status) -> ImColor
{
    switch (status)
    {
    case Person::Status::Healthy:
    case Person::Status::Recovered:
        return {ImVec4(113.0 / 255.0, 151.0 / 255.0, 76.0 / 255.0, 1.00)};
    case Person::Status::Infected:
        return {ImVec4(169.0 / 255.0, 52.0 / 255.0, 58.0 / 255.0, 1.00)};
    case Person::Status::Deceased:
        return {ImVec4(0.00, 0.00, 0.00, 1.00)};
    }

    fmt::print("Unreachable!\n");
    std::abort();
}

namespace gui
{

auto showSim(sim::State &state) -> void
{
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.13, 0.13, 0.13, 1.00));
    ImGui::Begin("Simulation", nullptr,
                 ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

    ImDrawList *drawList = ImGui::GetWindowDrawList();

    for (int y = 0; y < sim::ROWS; ++y)
    {
        for (int x = 0; x < sim::COLS; ++x)
        {
            auto lx = static_cast<float>(sim::WINDOW_PADDING + x * (sim::CELL_WIDTH));
            auto ly = static_cast<float>(sim::WINDOW_PADDING + y * (sim::CELL_HEIGHT));

            auto person = state.grid()[y * sim::ROWS + x];
            auto fillColor = personStatusToColor(person.status());
            drawList->AddRectFilled(ImVec2(lx, ly), ImVec2(lx + sim::CELL_WIDTH - 1, ly + sim::CELL_HEIGHT - 1),
                                    fillColor);

            if (!person.isCompliant())
                drawList->AddRect(ImVec2(lx, ly), ImVec2(lx + sim::CELL_WIDTH - 1, ly + sim::CELL_HEIGHT - 1),
                                  ImColor(ImVec4(249.0 / 255.0, 161.0 / 255.0, 27.0 / 255.0, 1.00)));
        }
    }

    ImGui::End();
    ImGui::PopStyleColor();
}

} // namespace gui

#endif // NIFTY_COVID_SIM_SIMWINDOW_H
