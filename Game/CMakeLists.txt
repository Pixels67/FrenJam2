project(Game)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out/bin/${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}-${CMAKE_BUILD_TYPE})

set(PROJECT_SOURCES
        src/main.cpp
        src/Tile.hpp
        src/Using.hpp
        src/Player.hpp
        src/DialogueUi.hpp
        src/Dialogue.hpp
        src/Interactable.hpp
        src/Item.hpp
        src/ItemUi.hpp
        src/Player.cpp
        src/Map.hpp
        src/Fren.hpp
        src/Door.hpp
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE FlockCore)

add_custom_command(
        TARGET Game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/assets
        ${PROJECT_SOURCE_DIR}/out/bin/${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}-$<CONFIG>/assets
)