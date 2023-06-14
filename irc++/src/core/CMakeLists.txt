set(NAME "Core")

include(${PROJECT_SOURCE_DIR}/cmake/StaticAnalyzers.cmake)

find_package(Boost 1.81 COMPONENTS fiber REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_library(${NAME} STATIC
  Core/Log.cpp Core/Log.hpp Core/Debug/Instrumentor.hpp
  Core/Application.cpp Core/Application.hpp Core/Window.cpp Core/Window.hpp
  Core/Resources.hpp Core/DPIHandler.hpp Core/imgui_stdlib.hpp Core/imgui_stdlib.cpp
  Core/IRC.cpp Core/IRC.hpp Core/Parser.cpp Core/Parser.hpp)

# Define set of OS specific files to include
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
  target_sources(${NAME} PRIVATE
    Platform/Windows/Resources.cpp Platform/Windows/DPIHandler.cpp)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  target_sources(${NAME} PRIVATE
    Platform/Mac/Resources.cpp Platform/Mac/DPIHandler.cpp)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  target_sources(${NAME} PRIVATE
    Platform/Linux/Resources.cpp Platform/Linux/DPIHandler.cpp)
endif ()

target_include_directories(${NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(${NAME} PRIVATE cxx_std_20)
target_link_libraries(${NAME}
  PRIVATE project_warnings
  PUBLIC fmt spdlog SDL2::SDL2 imgui Settings ${Boost_LIBRARIES})

add_subdirectory(Tests)
