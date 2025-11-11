# WhiteJack
You play as a dirty blackjack dealer

Core 
  Language: C++

  Graphics & Audio: Raylib (C-API)

  Build System: CMake

  Deployment: WebAssembly (WASM) / Native Executable

Key Architectural Patterns :

  State Design Pattern: 
  The entire application flow is managed by the IGameState interface.
  the game transition between (StateMainMenu not yet implemented) ,StateGuide, StateGameplay, and StateGameOver
  
  State Machines :
  To manage transitions between major screens and encapsulate the behavior of each screen.
  
  Non-Blocking Timer System :
  to control all delayed actions

  











sources I used :
https://www.raylib.com/cheatsheet/cheatsheet.html
https://gameprogrammingpatterns.com/state.html
https://en.cppreference.com/
https://emscripten.org/docs/compiling/index.html
https://cmake.org/cmake/help/latest/guide/tutorial/index.html
Game Assets:
https://deanlofiplays.itch.io/heart-life-pack-1
https://kerenel.itch.io/pixelart-cards
Background Music:
https://pixabay.com/music/search/casino%20background/
Sound Effects:
https://kenney.nl/assets/category:Audio?sort=update
