project(yahtzee-lib LANGUAGES CXX)



# Setup a library target
file(GLOB_RECURSE YAHTZEE_SOURCES CONFIGURE_DEPENDS *.cpp)
add_library(${PROJECT_NAME} ${YAHTZEE_SOURCES}
        core/game.h
        Application.cpp
        Application.h
        objects/board/Board.cpp
        objects/board/Board.h
        objects/dices/Dice.cpp
        objects/dices/Dice.h
        objects/combination_field/CombinationField.cpp
        objects/combination_field/CombinationField.h
        config/Config.cpp
        config/Config.h
        objects/info/Info.cpp
        objects/info/Info.h
        config/handler/EventHandler.cpp
        config/handler/EventHandler.h
        objects/GameObject.h
        config/GameConfig/GameConfig.h
        GameController.cpp
        GameController.h
        exception/YahtzeeException.h
        exception/game/GameException.cpp
        exception/game/GameException.h
        core/modes/classic/ClassicGame.cpp
        core/modes/classic/ClassicGame.h
        exception/config/ConfigException.cpp
        exception/config/ConfigException.h
        core/modes/speed/SpeedGame.cpp
        core/modes/speed/SpeedGame.h
        core/modes/coundown/CountDownGame.cpp
        core/modes/coundown/CountDownGame.h
        core/modes/race/RaceGame.cpp
        core/modes/race/RaceGame.h
        objects/setting/SettingObjects.cpp
        objects/setting/SettingObjects.h
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE:${PROJECT_NAME}>"
        "$<TARGET_FILE_DIR:yahtzee-app>"
)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(${PROJECT_NAME} PUBLIC
        ${IMGUI_INCLUDE_DIR}
        ${SFML_INCLUDE_DIR}
        ${IMGUI_SFML_INCLUDE_DIR}
)
ct_set_compiler_warnings(${PROJECT_NAME})

# Link with third-party dependencies
target_link_libraries(${PROJECT_NAME} PUBLIC
        imgui
        imgui-sfml
        sfml-graphics
        sfml-window
        sfml-system
        opengl32
        gdi32
)

message(STATUS "IMGUI_DIR: ${IMGUI_DIR}")
message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
message(STATUS "IMGUI_SFML_INCLUDE_DIR: ${IMGUI_SFML_INCLUDE_DIR}")