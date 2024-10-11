cmake_minimum_required(VERSION 3.10)
project(FixedMinesweeper)

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files (all .cpp files in the directory)
file(GLOB SOURCES "src/*.cpp")

# Find and link SFML libraries
find_package(SFML 2.6 REQUIRED COMPONENTS graphics window system audio)

# Create the Minesweeper executable
add_executable(Minesweeper ${SOURCES})

# Link the SFML libraries
target_link_libraries(Minesweeper sfml-graphics sfml-window sfml-system sfml-audio)

# Specify the directory where your game resources are stored
set(RESOURCE_DIR "${CMAKE_SOURCE_DIR}/resources")

# Custom command to copy resources to the build directory after the build
add_custom_command(TARGET Minesweeper POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${RESOURCE_DIR}"              # Source directory with resources
    "$<TARGET_FILE_DIR:Minesweeper>/resources"  # Destination directory near the executable
)
