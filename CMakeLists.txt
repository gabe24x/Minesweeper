cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Project3)

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
set(SFML_DIR "<C:/Users/gabedebrito/Documents/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)
add_executable(Project3 main.cpp Board.cpp Board.h Tile.h TextureManager.cpp TextureManager.h WelcomeWindow.h WelcomeWindow.cpp Tile.cpp Textbox.cpp Textbox.h GameWindow.cpp GameWindow.h Button.cpp Button.h Timer.cpp Timer.h LeaderboardWindow.cpp LeaderboardWindow.h)
target_link_libraries(Project3 sfml-system sfml-window sfml-graphics sfml-audio)