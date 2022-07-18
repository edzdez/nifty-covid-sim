cmake_minimum_required(VERSION 3.22)
project(nifty_covid_sim)

set(CMAKE_CXX_STANDARD 20)

if (EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else ()
    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif ()

set(IMGUI_BINDINGS src/bindings/imgui_impl_glfw.h src/bindings/imgui_impl_glfw.cpp src/bindings/imgui_impl_opengl3.h src/bindings/imgui_impl_opengl3.cpp src/bindings/imgui_impl_opengl3_loader.h)

set(SOURCE_FILES src/main.cpp src/constants.h src/app.h src/app.cpp src/state.cpp src/state.h src/menuwindow.h src/simwindow.h src/person.cpp src/person.h src/randp.cpp src/randp.h)
add_executable(nifty_covid_sim ${IMGUI_BINDINGS} ${SOURCE_FILES})
target_link_libraries(nifty_covid_sim ${CONAN_LIBS})
