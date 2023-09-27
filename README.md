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

    scripts/setup

To build the native application:

    scripts/build -p mac -c release
        -- or --
    scripts/build -p mac -c debug

        -- or --

    cd build
    make config=release_mac
        -- or --
    make config=debug_mac

To build the web application:

    scripts/build -p web -c release
        -- or --
    scripts/build -p web -c debug
    
        -- or --

    cd build
    emmake make config=release_web
        -- or --
    emmake make config=debug_web

The native application (sparky-demo) will be found in:

    build/bin/release-mac
        -- or --
    build/bin/debug-mac

Change to the appropriate directory and execute sparky-demo. (The demo
depends on the resources being found in the current directory.)

To run the web application:

    cd build/bin/release-web
        -- or --
    cd build/bin/debug-web

    emrun sparky-demo.html

        - or -
    
    python -m http.server # python 3
        -- or --
    python -m SimpleHTTPServer # python 2

Open a web browser and point to http://localhost:8000/sparky-demo.html

