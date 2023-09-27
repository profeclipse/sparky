Sparky

Sparky is a game engine I'm writing while watching The Cherno's game engine video
series on YouTube.

https://youtube.com/playlist?list=PLlrATfBNZ98fqE45g3jZA_hLGUrD4bo6_&si=_PbAR4AgU0UG696Z

How To Build

You will need Premake 5 or greater and Emscripten to build/run the project.

    Premake - https://premake.github.io
    Emscripten - https://emscripten.org/docs/getting_started/downloads.html

Building for the first time:

Clone the repository:

    git clone git@github.com:profeclipse/sparky.git

Change to the project directory:

    cd sparky

Configure the build system (assumes gmake as the build system):

    premake5 gmake2

To build the native application:

    cd build
    make -j4 config=release_mac
        -- or --
    make -j4 config=debug_mac

To build the web application:

    cd build
    emmake make -j4 config=release_web
        -- or --
    emmake make -j4 config=debug_web

To run the native application:

    cd build/bin/release-mac
        -- or --
    cd build/bin/debug-mac

    ./sparky-demo

To run the web application:

    cd build/bin/release-web
        -- or --
    cd build/bin/debug-web

    emrun sparky-demo.html

    - or -
    
    cd build/bin/release-web
        -- or --
    cd build/bin/debug-web

    python -m http.server # python 3
        -- or --
    python -m SimpleHTTPServer # python 2

    Open a web browser and point to http://localhost:8000/sparky-demo.html

