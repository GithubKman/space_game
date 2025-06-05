# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(space_gameTests LANGUAGES CXX)

# ---- Tests ----

add_executable(space_game_test source/space_game_test.cpp)
target_link_libraries(space_game_test PRIVATE space_game_lib)
target_compile_features(space_game_test PRIVATE cxx_std_20)

add_test(NAME space_game_test COMMAND space_game_test)

# ---- End-of-file commands ----

add_folders(Test)
