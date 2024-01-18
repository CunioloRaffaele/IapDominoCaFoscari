cmake_minimum_required(VERSION 3.10)
project(iap C)

set(CMAKE_C_STANDARD 99)

# Add optimization level
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 --pedantic")

# Add all the source files
file(GLOB_RECURSE SOURCE_FILES main.c ./fragments/*.c ./functions/*.c)

# Include directories
include_directories(./fragments ./functions)

# Create the executable
add_executable(iap ${SOURCE_FILES})

# Custom target to run the executable with arguments
add_custom_target(test
        COMMAND ${CMAKE_BINARY_DIR}/iap --debugging
        DEPENDS iap
        WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
        COMMENT "debugging"
)