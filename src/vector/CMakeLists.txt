# Vector module library (header-only)
add_library(vector_lib INTERFACE)

target_include_directories(vector_lib INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Set target properties for interface library
set_target_properties(vector_lib PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)