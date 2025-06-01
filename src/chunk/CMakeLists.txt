# Chunk module library
add_library(chunk_lib STATIC
    chunk_map.cpp
)

target_include_directories(chunk_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ../vector
    ..
)

target_link_libraries(chunk_lib PUBLIC
    vector_lib
    raylib
    raylib_cpp
)

# Set target properties
set_target_properties(chunk_lib PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)