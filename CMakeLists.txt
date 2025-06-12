cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
    space_game
    VERSION 0.1.0
    DESCRIPTION "Cool space game where you mine asteroids (WIP)"
    HOMEPAGE_URL "https://github.com/GithubKman/space_game"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)
include(FetchContent)

# ---- Declare library ----

add_library(
    space_game_lib OBJECT
    source/angle/degree.cpp
    source/angle/radian.cpp
    source/chunk/chunk_map.cpp
    source/player/player.cpp
    source/world/world.cpp
    source/object/entity.cpp
)


target_compile_features(space_game_lib PUBLIC cxx_std_20)

# raylib
find_package(raylib QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG c1ab645
        GIT_SHALLOW 1
    )
    FetchContent_MakeAvailable(raylib)
endif()

# raylib-cpp
find_package(raylib_cpp QUIET)
if (NOT raylib_cpp_FOUND)
    if (NOT DEFINED RAYLIB_CPP_VERSION)
        set(RAYLIB_CPP_VERSION v5.5.0)
    endif()
    include(FetchContent)
    FetchContent_Declare(
        raylib_cpp
        GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
        GIT_TAG ${RAYLIB_CPP_VERSION}
    )
    FetchContent_MakeAvailable(raylib_cpp)
endif()

target_include_directories(
    space_game_lib ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_link_libraries(space_game_lib PUBLIC raylib raylib_cpp)
# ---- Declare executable ----

add_executable(space_game_exe source/main.cpp)
add_executable(space_game::exe ALIAS space_game_exe)

set_property(TARGET space_game_exe PROPERTY OUTPUT_NAME space_game)

target_compile_features(space_game_exe PRIVATE cxx_std_20)

target_link_libraries(space_game_exe PRIVATE space_game_lib raylib raylib_cpp)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT space_game_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of space_game"
  )
endif()

add_custom_command(TARGET MyApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:MyApp>/resources
)

include(cmake/dev-mode.cmake)
