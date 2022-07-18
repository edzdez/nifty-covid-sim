# Nifty Covid Sim

A virus simulator based on [this](http://nifty.stanford.edu/2021/bitner-covid-sim/#) nifty.
Written in C++20 with [imgui](https://github.com/ocornut/imgui).

![](demo/demo.gif)

## Dependencies

Dependencies are managed with [conan](https://conan.io/) and can be found in the [conanfile](./conanfile.txt).

- libfmt
- glfw
- imgui

## Build

Ths project is built in C++20 using [CMake](https://cmake.org/) and [Ninja](https://ninja-build.org/).
I've only tested this on Fedora 36 with g++12.

```shell
# clone the repo
$ git clone "https://github.com/edzdez/nifty-covid-simulation"
$ cd nifty-covid-simulation

# Installing dependencies
$ conan install . -s build_type=Release --install-folder=cmake-build-release --build missing

# Generate build files
$ cmake -S . -B cmake-build-release -G Ninja -DCMAKE_BUILD_TYPE=Release

# Build
$ cd cmake-build-release
$ ninja
$ cd ..

# In the root directory of the repo
$ ./cmake-build-release/bin/nifty_covid_sim
```