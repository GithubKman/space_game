# Add subdirectories
add_subdirectory(angle)
add_subdirectory(chunk)
add_subdirectory(player)
add_subdirectory(vector)

# Main executable
add_executable(${PROJECT_NAME} main.cpp)

# Link with all module libraries
target_link_libraries(${PROJECT_NAME} PRIVATE 
    angle_lib
    chunk_lib
    player_lib
    vector_lib
    raylib 
    raylib_cpp
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    angle
    chunk
    player
    vector
)