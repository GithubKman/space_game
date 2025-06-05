install(
    TARGETS space_game_exe
    RUNTIME COMPONENT space_game_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
