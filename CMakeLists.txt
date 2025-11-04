cmake_minimum_required(VERSION 3.10)
project(WhiteJack VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# -----------------------------------------------------------
# --- WEB BUILD FIX: PART 1 (Configure Raylib) ---
#
if(EMSCRIPTEN)
 set(PLATFORM "Web" CACHE STRING "Raylib platform" FORCE)
endif()
# --- END FIX PART 1 ---
# -----------------------------------------------------------

add_subdirectory(raylib EXCLUDE_FROM_ALL)

# We will manually list our files.
set(SOURCE_FILES
  src/core/main.cpp
  src/core/Game.cpp
  src/core/IGameState.cpp
  src/core/Utils.cpp

  src/game/Card.cpp
  src/game/Deck.cpp
  src/game/Hand.cpp
  src/game/Player.cpp
  src/game/Client.cpp

  src/states/StateGameplay.cpp
  src/states/StateMainMenu.cpp


  src/managers/ResourceManager.cpp
 
)

# -----------------------------------------------------------
# --- CREATE THE TARGET ---
add_executable(WhiteJack ${SOURCE_FILES})
# -----------------------------------------------------------


target_include_directories(WhiteJack PUBLIC 
  ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(WhiteJack PRIVATE raylib)

# -----------------------------------------------------------
# --- WEB BUILD FIX: PART 2 (Force Global Linker Flags) ---
#
#
if(EMSCRIPTEN)
  set_target_properties(WhiteJack PROPERTIES SUFFIX ".html")
  
  set(CMAKE_EXE_LINKER_FLAGS
 "-s ASYNCIFY \
  -s ALLOW_MEMORY_GROWTH \
 --preload-file ${CMAKE_SOURCE_DIR}/assets@assets"
  CACHE STRING "Emscripten Linker Flags" FORCE)
endif()
# -----------------------------------------------------------