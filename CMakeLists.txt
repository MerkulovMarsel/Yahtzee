cmake_minimum_required(VERSION 3.25...3.31)

project(yahtzee LANGUAGES CXX)


include(cmake/CompilerOptions.cmake)
include(cmake/CompilerWarnings.cmake)

add_subdirectory(third-party)
add_subdirectory(lib)
add_subdirectory(app)
add_subdirectory(tests)
