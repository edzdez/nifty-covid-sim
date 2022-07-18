#include "app.h"
#include <thread>

#include "menuwindow.h"
#include "simwindow.h"

auto App::glfwErrorCallback(int error, const char *description) -> void
{
    fmt::print("Glfw Error {}: {}\n", error, description);
}

App::App(const char *title, int width, int height)
{
    // Setup m_window
    glfwSetErrorCallback(App::glfwErrorCallback);
    if (glfwInit() == 0)
        std::exit(EXIT_FAILURE);

#if defined(__APPLE__)
    // GL 3.2 + GLSL 150
    glslVersion = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // Required on Mac
#else
    // GL 3.0 + GLSL 130
    glslVersion = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    // Create m_window with graphics context
    m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (m_window == nullptr)
        std::exit(EXIT_FAILURE);

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.Fonts->AddFontFromFileTTF("fonts/JetBrainsMonoNL-Regular.ttf", 18);
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    ImGuiStyle *style = &ImGui::GetStyle();
    style->Colors[ImGuiCol_Button] = ImVec4(0.18f, 0.18f, 0.17f, 1.00f);
    style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    style->Colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 0.85f, 0.40f, 1.00f);
    style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(1.00f, 0.85f, 0.40f, 1.00f);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(sim::WINDOW_PADDING, sim::WINDOW_PADDING));

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init(glslVersion);

    m_simulationThread = std::thread(simulation, std::ref(m_state));
}

App::~App()
{
    m_state.m_mutex.lock();
    m_state.setDead();
    m_state.m_mutex.unlock();

    m_simulationThread.join();

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_window);
    glfwTerminate();
}

auto App::setup() -> void
{
}

auto App::run() -> void
{
    setup();

    while (glfwWindowShouldClose(m_window) == 0)
    {
        // Poll and handle events (inputs, m_window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your
        // inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or
        // clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or
        // clear/overwrite your copy of the keyboard data. Generally you may always pass all inputs to dear imgui, and
        // hide them from your application based on those two flags.
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport(nullptr, ImGuiDockNodeFlags_NoTabBar | ImGuiDockNodeFlags_NoResizeX, nullptr);

        update();

        // Rendering
        ImGui::Render();
        int displayW{}, displayH{};
        glfwGetFramebufferSize(m_window, &displayW, &displayH);
        glViewport(0, 0, displayW, displayH);
        glClearColor(clearColor.x * clearColor.w, clearColor.y * clearColor.w, clearColor.z * clearColor.w,
                     clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_window);
    }
}

auto App::update() -> void
{
    m_state.m_mutex.lock();
    gui::showMenu(m_state);
    gui::showSim(m_state);
    m_state.m_mutex.unlock();
}

auto App::simulation(sim::State &state) -> void
{
    while (true)
    {
        state.m_mutex.lock();
        if (state.dead())
        {
            state.m_mutex.unlock();
            return;
        }

        state.step();

        state.m_mutex.unlock();
        std::this_thread::sleep_for(sim::TIME_STEP);
    }
}
