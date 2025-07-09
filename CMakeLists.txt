cmake_minimum_required(VERSION 3.31.4)
project(DotsAndBoxes)


#C++ Standard

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#include sourcefiles and raylib
add_subdirectory("external/raylib")
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")

#Add executable
add_executable(${PROJECT_NAME} ${SOURCES})


target_link_libraries(${PROJECT_NAME} raylib)

if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} m pthread dl rt X11)
endif()


set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

# Only relevant for multi-config generators like Visual Studio
target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:DEBUG>:DEBUG_BUILD>
    $<$<CONFIG:RELEASE>:NDEBUG>
)

# Example: Set different output folders by config
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/Debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/Release"
)