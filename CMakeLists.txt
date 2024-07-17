cmake_minimum_required(VERSION 3.21)
project(Game)

# SETUP VARIABLES:

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directories should be defined after the project() call
set(OUTPUT_DIR "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIR}")

# FIND SDL2 AND SDL2_IMAGE

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Ensure SDL2 and SDL2_image were found
if(NOT SDL2_FOUND)
    message(FATAL_ERROR "SDL2 not found!")
endif()

if(NOT SDL2_image_FOUND)
    message(FATAL_ERROR "SDL2_image not found!")
endif()

# SETUP INCLUDE AND LINK DIRS:

include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${SDL2IMAGE_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/include
)

# INCLUDE FILES THAT SHOULD BE COMPILED:

file(GLOB_RECURSE SRC "src/*.cpp")

message(STATUS "Add source files:")
foreach(SRC_FILE IN LISTS SRC)
    message(STATUS "${SRC_FILE}")
endforeach()
message(STATUS "")

add_executable(${PROJECT_NAME} ${SRC})

# LINK PROGRAM

target_link_libraries(
    ${PROJECT_NAME}
    SDL2::SDL2
    SDL2::SDL2main
    SDL2_image::SDL2_image
)

# COPY OVER STATIC FILES

message(STATUS "Copying all assets to destination folder...")
file(
    COPY ${CMAKE_SOURCE_DIR}/assets
    DESTINATION ${OUTPUT_DIR}
)
