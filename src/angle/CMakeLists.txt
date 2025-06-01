# Angle module library
add_library(angle_lib STATIC
    degree.cpp
    radian.cpp
)

target_include_directories(angle_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Set target properties
set_target_properties(angle_lib PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)