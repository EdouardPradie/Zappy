##
## CMakeLists: zappy / tests
##

cmake_minimum_required(VERSION 3.6)

message("Loading catch2 lib")

include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        605a34765aa5d5ecbf476b4598a862ada971b0cc # v3.0.1
)
# After the following call, the CMake targets defined by Catch2 will be available to the rest of the build
FetchContent_MakeAvailable(Catch2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-writable-strings")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/)

# Source files
set(
    SRCS
    src/main.cpp
)

# binary
add_executable(tests-zappy ${SRCS})
target_include_directories(tests-zappy PRIVATE ${PROJECT_SOURCE_DIR}/Core/include)
target_link_libraries(tests-zappy zappy_gui-core Catch2)
set_property(TARGET tests-zappy PROPERTY CXX_STANDARD 20)
set_property(TARGET tests-zappy PROPERTY CXX_STANDARD_REQUIRED ON)

#[[ execute_process(COMMAND "./tests-zappy"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    ) ]]
