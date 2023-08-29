Sparky

Sparky is a game engine I'm writing while watching The Cherno's game engine video
series on YouTube.

How To Build

You will need CMake and Emscripten to build/run the project.

    CMake - https://cmake.org/download/
    Emscripten - https://emscripten.org/docs/getting_started/downloads.html

Building for the first time:

Clone the repository:

    git clone git@github.com:profeclipse/sparky.git

Change to the project directory:

    cd sparky

Create build directories for native application and web (emscripten) application:

    mkdir build
    mkdir embuild

Configure the native application build:

    cd build
    cmake ..
    cd ..

Configure the web application build:

    cd embuild
    emcmake cmake ..
    cd ..

To build the native application:

    cd build
    cmake --build .
    cd ..

To build the web application:

    cd embuild
    cmake --build . --target demo
    cd ..

To run the native application:

    cd build/bin
    ./demo

To run the web application:

    cd embuild/bin
    emrun demo.html

    - or -
    
    cd embuild/bin
    python -m http.server # python 3
        -- or --
    python -m SimpleHTTPServer # python 2

    Open a web browser and point to http://localhost:8000/

