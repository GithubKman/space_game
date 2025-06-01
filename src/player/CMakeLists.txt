# Player module library
add_library(player_lib STATIC
    player.cpp
)

target_include_directories(player_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ../angle
)

target_link_libraries(player_lib PUBLIC
    angle_lib
    raylib
    raylib_cpp
)

# Set target properties
set_target_properties(player_lib PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)