include(FetchContent)

message(STATUS "Fetching sfml...")

FetchContent_Declare(
        sfml
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x
)

set(SFML_BUILD_WINDOW ON)
set(SFML_BUILD_GRAPHICS ON)
set(SFML_BUILD_NETWORK OFF)
set(SFML_BUILD_AUDIO OFF)

FetchContent_MakeAvailable(sfml)

set(SFML_INCLUDE_DIR ${sfml_SOURCE_DIR} CACHE PATH "Path to SFML" FORCE)

message(STATUS "Fetching sfml... SFML_DIR = ${SFML_INCLUDE_DIR}")