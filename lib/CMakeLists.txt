project(yahtzee-lib LANGUAGES CXX)



# Setup a library target
file(GLOB_RECURSE YAHTZEE_SOURCES CONFIGURE_DEPENDS *.cpp)
add_library(${PROJECT_NAME} ${YAHTZEE_SOURCES}
        core/game.h
        Application.cpp
        Application.h
        UIManger/UIManager.h
        UIManger/UIManager.cpp
        UIManger/GameConfig/GameConfig.h
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
        element/base/Element.h
        core/modes/test/TestGame.cpp
        core/modes/test/TestGame.h
        element/handler/Handler.h
        UIManger/TextureManager/TextureManager.cpp
        UIManger/TextureManager/TextureManager.h
        UIManger/ElementsTypes/ElementsTypes.h
        UIManger/PositionManger/PositionManager.cpp
        UIManger/PositionManger/PositionManager.h
        element/base/animator/Animator.cpp
        element/base/animator/Animator.h
        element/base/Element.cpp
        element/base/StaticUpdate/StaticUpdateElement.cpp
        element/base/StaticUpdate/StaticUpdateElement.h
        element/base/StateHandler/StateHandler.h
        element/base/Touchable/TouchableElement.h
        element/base/StaticTouchable/StaticTouchableElement.h
        element/base/DynamicTouchable/DynamicTouchableElement.h
        element/base/StaticUntouchable/StaticUntouchableElement.h
        element/handler/BackGround/BackGround.h
        element/handler/Tracker.h
        element/handler/PageChangerButton/PageChangerButton.h
        element/handler/SetPlayerCountButton/SetPlayerCountButton.h
        element/handler/IntegerSlider/IntegerSlider.h
        element/handler/SetGameModeButton/SetGameModeButton.h
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