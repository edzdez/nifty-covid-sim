#ifndef NIFTY_COVID_SIM_MENUWINDOW_H
#define NIFTY_COVID_SIM_MENUWINDOW_H

#include "imgui.h"

namespace gui
{

auto showKey() -> void
{
    ImGuiStyle *style = &ImGui::GetStyle();
    ImGui::TextWrapped("Key:");
    {
        auto oldColorBackground = style->Colors[ImGuiCol_ChildBg];
        style->Colors[ImGuiCol_ChildBg] = ImVec4(113.0 / 255.0, 151.0 / 255.0, 76.0 / 255.0, 1.00);
        ImGui::BeginChild("Healthy/Recovered", ImVec2(15, 15));
        ImGui::EndChild();
        ImGui::SameLine();
        ImGui::TextWrapped("Healthy/Recovered");
        style->Colors[ImGuiCol_ChildBg] = oldColorBackground;
    }

    {
        auto oldColorBackground = style->Colors[ImGuiCol_ChildBg];
        style->Colors[ImGuiCol_ChildBg] = ImVec4(169.0 / 255.0, 52.0 / 255.0, 58.0 / 255.0, 1.00);
        ImGui::BeginChild("Infected", ImVec2(15, 15));
        ImGui::EndChild();
        ImGui::SameLine();
        ImGui::TextWrapped("Infected");
        style->Colors[ImGuiCol_ChildBg] = oldColorBackground;
    }

    {
        auto oldColorBackground = style->Colors[ImGuiCol_ChildBg];
        style->Colors[ImGuiCol_ChildBg] = ImVec4(0.00, 0.00, 0.00, 1.00);
        ImGui::BeginChild("Deceased", ImVec2(15, 15));
        ImGui::EndChild();
        ImGui::SameLine();
        ImGui::TextWrapped("Deceased");
        style->Colors[ImGuiCol_ChildBg] = oldColorBackground;
    }

    {
        auto oldColorBorder = style->Colors[ImGuiCol_Border];
        style->Colors[ImGuiCol_Border] = ImVec4(249.0 / 255.0, 161.0 / 255.0, 27.0 / 255.0, 1.00);
        ImGui::BeginChild("Noncompliant", ImVec2(15, 15), true);
        ImGui::EndChild();
        ImGui::SameLine();
        ImGui::TextWrapped("Noncompliant");
        style->Colors[ImGuiCol_Border] = oldColorBorder;
    }
}

auto showStatus(sim::State &state) -> void
{
    ImGui::TextWrapped("Total Deceased: %d", state.deceased());
    ImGui::TextWrapped("Total Infections: %d", state.totalInfected());
    ImGui::TextWrapped("Current Infections: %d", state.currInfected());
    ImGui::TextWrapped("New Infections: %d", state.newInfected());
    ImGui::TextWrapped("Noncompliant People: %d", state.nonCompliant());
}

auto showMenu(sim::State &state) -> void
{
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.09, 0.09, 0.09, 1.00));
    ImGui::Begin("Menu", nullptr,
                 ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

    ImGui::Dummy(ImVec2(ImGui::GetWindowContentRegionWidth(), 100));
    ImGui::TextWrapped("Percentage of population complying with social distancing recommendations");

    ImGui::Dummy(ImVec2(ImGui::GetWindowContentRegionWidth(), 10));
    ImGuiStyle *style = &ImGui::GetStyle();
    {
        auto oldColorBackground = style->Colors[ImGuiCol_FrameBg];
        auto oldColorBackgroundHovered = style->Colors[ImGuiCol_FrameBgHovered];
        auto oldColorBackgroundActive = style->Colors[ImGuiCol_FrameBgActive];

        style->Colors[ImGuiCol_FrameBg] = ImVec4(0.18, 0.18, 0.17, 1.00);
        style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.18, 0.18, 0.17, 1.00);
        style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.23, 0.23, 0.22, 1.00);

        ImGui::PushItemWidth(ImGui::GetWindowContentRegionWidth());
        ImGui::SliderInt("##", state.percentSocialDistancing(), 0, 100);

        style->Colors[ImGuiCol_FrameBg] = oldColorBackground;
        style->Colors[ImGuiCol_FrameBgHovered] = oldColorBackgroundHovered;
        style->Colors[ImGuiCol_FrameBgActive] = oldColorBackgroundActive;
    }

    ImGui::Dummy(ImVec2(ImGui::GetWindowContentRegionWidth(), 30));
    if (ImGui::Button("Restart Simulation", ImVec2(ImGui::GetWindowContentRegionWidth(), 100)))
    {
        fmt::print("Restarting Simulation...\n");
        fflush(stdout);
        state.reset();
    }

    ImGui::Dummy(ImVec2(ImGui::GetWindowContentRegionWidth(), 40));
    showStatus(state);

    ImGui::Dummy(ImVec2(ImGui::GetWindowContentRegionWidth(), 40));
    showKey();

    ImGui::End();
    ImGui::PopStyleColor();
}

} // namespace gui

#endif // NIFTY_COVID_SIM_MENUWINDOW_H
