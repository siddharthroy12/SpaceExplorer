# Raylib template with CMake and Github Actions

## Idea for the game

Each playthrough will be randomly generated like a roughlike
There will be 4-5 star systems (Together will form a constellation)
In each star system there will be 4-5 planets
You have to protect planets from envasion
You will have limited amount of ammo, health
To get more ammo you'll need to mine astroids
Killing ememies will give you something (there will be boss battles too)
if you die you'll have to start a new game
envasion will spread from planet to planet if not stopped
stopping envasion will give you money and resources to upgrade your ship and get new weapons
once you have enough money you can use the teleporter to go the next star system
the difficulty will increase as you move to the next star system
once you finish all the star system the playthrough will end

## Building to Web

**You need to install Emscripten** [Download Here!](https://emscripten.org/docs/getting_started/downloads.html)

1. Clone the repository using Git. Execute this in a terminal: `git clone https://github.com/siddharthroy12/SpaceExplorer`
1. Cd into SpaceExplorer. `cd SpaceExplorer`
1. Install the raylib git submodule using `git submodule update --init --recursive --depth=1`
1. Make a build folder. Your builds will go here. `mkdir build; cd build`
1. Setup cmake `emcmake cmake -S .. -D CMAKE_BUILD_TYPE=Release`
1. Run `cmake --build build` to compile the project
1. Run a local web server and open the SpaceExplorer.html

## Building (Linux/macOS)

1. Clone the repository using `git clone https://github.com/siddharthroy12/SpaceExplorer`
1. Move to the SpaceExplorer directory
`cd SpaceExplorer`
1. Install the raylib git submodule using `git submodule update --init --recursive --depth=1`
1. Make a build folder and cd to it with `mkdir build && cd build`
1. Setup cmake `cmake .. -DCMAKE_BUILD_TYPE=Release`
1. Run `make` to compile the project
1. Make the binary executable `chmod +x SpaceExplorer`
1. Run the binary with `./SpaceExplorer`

## Building (Windows, MinGW)

**You need to install MinGW. Select make and developer tools in the installer** [Download MinGW here!](https://sourceforge.net/projects/mingw/)

1. Clone the repository using Git. Execute this in a terminal: `git clone https://github.com/siddharthroy12/SpaceExplorer`
1. Cd into SpaceExplorer. `cd SpaceExplorer`
1. Install the raylib git submodule using `git submodule update --init --recursive --depth=1`
1. Make a build folder. Your builds will go here. `mkdir build; cd build`
1. Setup CMake. **Make sure to define MinGW Makefiles if you are using MinGW!** `cmake .. -DCMAKE_BUILD_TYPE=Release -G "MinGW Makefiles"`
1. Make sure you have mingw32-make. If you do, just run it in the build directory and it will start compiling everything. It won't take long, and once it's finished, then
1. Run SpaceExplorer.exe! You have just compiled SpaceExplorer for Windows using MinGW.

## Building (Windows, MSVC)

You need to have Visual Studio 2019 (other versions aren't tested, please tell us if it works for you) with C++ Development selected in the installer.

1. Clone the repository using Git. Execute this in a terminal: `git clone https://github.com/siddharthroy12/SpaceExplorer`
1. Cd into SpaceExplorer. `cd SpaceExplorer`
1. Install the raylib git submodule using `git submodule update --init --recursive --depth=1`
1. Make a build folder. Your builds will go here. `mkdir build; cd build`
1. Setup CMake. `cmake .. -DCMAKE_BUILD_TYPE=Release`
1. Let's build the project! Run `cmake --build .`
1. Go into Debug, your build of SpaceExplorer is there. You have now compiled SpaceExplorer for Windows using MSVC.
