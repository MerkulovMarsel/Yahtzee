project(yahtzee-lib LANGUAGES CXX)



# Setup a library target
file(GLOB_RECURSE YAHTZEE_SOURCES CONFIGURE_DEPENDS *.cpp)
add_library(${PROJECT_NAME} ${YAHTZEE_SOURCES}
        Application.cpp
        Application.hpp

        GameController.cpp
        GameController.hpp



        core/game.hpp

        core/modes/classic/ClassicGame.cpp
        core/modes/classic/ClassicGame.hpp

        core/modes/speed/SpeedGame.cpp
        core/modes/speed/SpeedGame.hpp

        core/modes/coundown/CountDownGame.cpp
        core/modes/coundown/CountDownGame.hpp

        core/modes/race/RaceGame.cpp
        core/modes/race/RaceGame.hpp

        core/modes/test/TestGame.cpp
        core/modes/test/TestGame.hpp



        UIManger/UIManager.hpp
        UIManger/UIManager.cpp

        UIManger/GameConfig/GameConfig.hpp

        UIManger/ElementsTypes/ElementsTypes.hpp
        UIManger/ElementsTypes/Constant.hpp
        UIManger/ElementsTypes/Data.hpp

        UIManger/TextureManager/TextureManager.cpp
        UIManger/TextureManager/TextureManager.hpp

        UIManger/PositionManger/PositionManager.cpp
        UIManger/PositionManger/PositionManager.hpp



        exception/YahtzeeException.hpp

        exception/game/GameException.cpp
        exception/game/GameException.hpp

        exception/config/ConfigException.cpp
        exception/config/ConfigException.hpp


        elements/base/interfaces/element/Element.hpp
        elements/base/interfaces/element/Element.cpp

        elements/base/interfaces/element/animator/Animator.cpp
        elements/base/interfaces/element/animator/Animator.hpp

        elements/base/interfaces/element/static/StaticUpdateElement.cpp
        elements/base/interfaces/element/static/StaticUpdateElement.hpp

        elements/base/interfaces/element/dynamic/DynamicUpdateElement.hpp

        elements/base/interfaces/state/StateHandler.hpp

        elements/base/interfaces/Touchable/TouchableElement.hpp


        elements/base/general/StaticTouchable/StaticTouchableElement.hpp

        elements/base/general/DynamicTouchable/DynamicTouchableElement.hpp

        elements/base/general/StaticUntouchable/StaticUntouchableElement.hpp

        elements/base/general/DynamicUntouchable/DynamicUntouchableElement.hpp


        elements/handler/Handler.hpp

        elements/handler/BackGround/BackGround.hpp

        elements/handler/Tracker.hpp

        elements/handler/PageChangerButton/PageChangerButton.hpp

        elements/handler/SetPlayerCountButton/SetPlayerCountButton.hpp

        elements/handler/IntegerSlider/IntegerSlider.hpp

        elements/handler/SetGameModeButton/SetGameModeButton.hpp

        elements/handler/Text/TextElement.hpp

        elements/handler/Screen/ScreenElement.hpp

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