include(FetchContent)

message(STATUS "Fetching imgui-sfml...")




message(STATUS "Fetching imgui-sfml... IMGUI_DIR = ${IMGUI_DIR}")

set(IMGUI_SFML_FIND_SFML OFF)
FetchContent_Declare(
        imgui-sfml
        GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
        GIT_TAG v2.6.1
)
FetchContent_MakeAvailable(imgui-sfml)


set(IMGUI_SFML_INCLUDE_DIR ${imgui-sfml_SOURCE_DIR} CACHE PATH "Path to ImGui-SFML" FORCE)

message(STATUS "IMGUI-SFML_DIR = ${IMGUI_SFML_INCLUDE_DIR}")

add_library(imgui-sfml STATIC
        ${imgui-sfml_SOURCE_DIR}/imgui-SFML.cpp
)

target_include_directories(imgui-sfml PUBLIC
        ${imgui-sfml_SOURCE_DIR}
        ${IMGUI_DIR}
        ${SFML_INCLUDE_DIR}
)

target_link_libraries(imgui-sfml PRIVATE
        imgui
        sfml-graphics
        sfml-window
        sfml-system
)
