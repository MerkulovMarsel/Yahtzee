project(yahtzee-app LANGUAGES CXX)

# Setup an executable target
add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
ct_set_compiler_warnings(${PROJECT_NAME})

# Link with yahtzee-lib
target_link_libraries(${PROJECT_NAME} PRIVATE yahtzee-lib)

# Игнорировать предупреждения из SFML (для GCC/Clang/MSVC)
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE
        "${CMAKE_BINARY_DIR}/_deps/sfml-src/include"
)

# Копирование всех необходимых DLL SFML
set(SFML_DLLS
        "sfml-graphics-d-2.dll"
        "sfml-window-d-2.dll"
        "sfml-system-d-2.dll"
        # Добавьте другие, если нужны (audio, network)
)

foreach(DLL ${SFML_DLLS})
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_BINARY_DIR}/_deps/sfml-build/lib/${DLL}"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endforeach()