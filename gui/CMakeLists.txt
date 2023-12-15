##
## CMakeLists: zappy_gui / zappy_gui
##

cmake_minimum_required(VERSION 3.16)

# standard version cpp
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

# project name
project(zappy_gui)

# change library prefix to none
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/..)

# option to build tests
option(ZAPPY_BUILD_TESTS "Build the tests" OFF)

# include directories
include_directories(Core/include/)

# Warning flags
set(GCC_WARNING_FLAGS
    -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches
    -Wlogical-op -Wnull-dereference -Wuseless-cast -fno-gnu-unique -Wno-pragmas)

set(CLANG_WARNING_FLAGS
    -Weverything
    -Wno-c++20-compat
    -Wno-c++98-c++11-compat-binary-literal
    -Wno-c++98-compat
    -Wno-c++98-compat-pedantic
    -Wno-c99-extensions
    -Wno-disabled-macro-expansion
    -Wno-documentation-unknown-command
    -Wno-exit-time-destructors
    -Wno-missing-prototypes
    -Wno-global-constructors
    -Wno-implicit-int-float-conversion
    -Wno-return-std-move
    -Wno-return-type-c-linkage
    -Wno-signed-enum-bitfield
    -Wno-weak-vtables)

if(${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS 13.0.0)
    set(CLANG_WARNING_FLAGS ${CLANG_WARNING_FLAGS} -Wno-return-std-move-in-c++11)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always")

set(WARNING_FLAGS
    -Wall
    -Wextra
    -Wshadow
    -Wnon-virtual-dtor
    -pedantic
    -Wold-style-cast
    -Wcast-align
    -Wunused
    -Wno-covered-switch-default
    -Woverloaded-virtual
    -Wpedantic
    -Wconversion
    -Wsign-conversion
    -Wdouble-promotion
    -Wformat=2
    -Weffc++
    -Wno-padded
    -Wno-ctad-maybe-unsupported)

# set colors for the messages because why not ?
if(NOT WIN32)
  string(ASCII 27 Esc)
  set(ColourReset "${Esc}[m")
  set(ColourBold  "${Esc}[1m")
  set(Red         "${Esc}[31m")
  set(Green       "${Esc}[32m")
  set(Yellow      "${Esc}[33m")
  set(Blue        "${Esc}[34m")
  set(Magenta     "${Esc}[35m")
  set(Cyan        "${Esc}[36m")
  set(White       "${Esc}[37m")
  set(BoldRed     "${Esc}[1;31m")
  set(BoldGreen   "${Esc}[1;32m")
  set(BoldYellow  "${Esc}[1;33m")
  set(BoldBlue    "${Esc}[1;34m")
  set(BoldMagenta "${Esc}[1;35m")
  set(BoldCyan    "${Esc}[1;36m")
  set(BoldWhite   "${Esc}[1;37m")
endif()

# set different flags
set(CMAKE_BUILD_TYPE
    ${CMAKE_BUILD_TYPE}
    CACHE
      STRING
      "Choose the type of build, options are: None Debug"
      FORCE)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb3")
endif()

# Clang-tidy
if(USE_CLANG_TIDY)
  find_program(
    CLANG_TIDY_EXE
    NAMES "clang-tidy"
    DOC "Path to clang-tidy executable")
  if(CLANG_TIDY_EXE)
    if(DEFINED zappy_gui_CLANG_TIDY_FLAGS)
      set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}"
                               "${zappy_gui_CLANG_TIDY_FLAGS}")
    else()
      set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
    endif()
    message("-- Found clang-tidy: ${CLANG_TIDY_EXE}")
  else()
    message("-- Failed to find clang-tidy")
  endif()
endif()

# set warning flags
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(WARNING_FLAGS ${WARNING_FLAGS} ${CLANG_WARNING_FLAGS})
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  set(WARNING_FLAGS ${WARNING_FLAGS} ${GCC_WARNING_FLAGS})
else()
  error("${CMAKE_CXX_COMPILER_ID}: Unsupported compiler.")
endif()

message("Warning flags: ${Cyan} ${WARNING_FLAGS}${ColourReset}")

add_library(zappy_gui-interface INTERFACE)

# link shared libraries and compile them
set_property(TARGET zappy_gui-interface PROPERTY CXX_STANDARD 20)
set_property(TARGET zappy_gui-interface PROPERTY CXX_STANDARD_REQUIRED ON)

message("Loading zappy_gui-core")

add_library(
    zappy_gui-core
    SHARED
    # temporary file to just be able to compile the lib, can delete it when no longer needed
    src/launch.cpp
    )
target_compile_options(zappy_gui-core PRIVATE ${WARNING_FLAGS})
target_include_directories(zappy_gui-core PUBLIC include)
set_property(TARGET zappy_gui-core PROPERTY CXX_STANDARD 20)
set_property(TARGET zappy_gui-core PROPERTY CXX_STANDARD_REQUIRED ON)
target_link_libraries(
    zappy_gui-core PRIVATE
    )

message("${BoldWhite}Finished loading zappy_gui-core${ColourReset}")

# adding executables
add_executable(
    zappy_gui
    src/main.cpp
    src/zappyError.cpp
    src/GUI/GUI.cpp
    src/GuiClient/GuiClient.cpp
    src/RingBuffer.cpp
    src/Camera.cpp
    src/Map/Map.cpp
    src/HUD/HUD.cpp
    src/Scenes/Game.cpp
    src/Player/Player.cpp
    src/Player/PlayerManager.cpp
    src/GuiClient/GuiClient.cpp
    src/RingBuffer.cpp
    src/MusicManager/MusicManager.cpp
    src/ParticleEngine/AParticle.cpp
    src/ParticleEngine/RainParticle.cpp
    src/ParticleEngine/FogParticle.cpp
    src/ParticleEngine/ParticleEngine.cpp
    src/Weather/WeatherManager.cpp
    src/Egg/EggManager.cpp
    src/Scenes/Victory.cpp
    src/Scenes/SceneManager.cpp
    src/HUD/FrequencyPanel.cpp
    src/HUD/TextButton.cpp
    src/DisconnectPanel/DisconnectPanel.cpp
    src/HUD/SelectionPanel.cpp
    )

# rules for zappy_gui project
target_link_libraries(
    zappy_gui PRIVATE
    zappy_gui-interface
    zappy_gui-core
    sfml-window
    sfml-graphics
    sfml-system
    sfml-audio
    sfml-network
    )
target_link_options(zappy_gui PRIVATE -rdynamic)
target_compile_options(zappy_gui PRIVATE ${WARNING_FLAGS})
set_property(TARGET zappy_gui PROPERTY CXX_STANDARD 20)
set_property(TARGET zappy_gui PROPERTY CXX_STANDARD_REQUIRED ON)

# execute tests if needed
if (ZAPPY_BUILD_TESTS)
    add_subdirectory(tests)
endif()
