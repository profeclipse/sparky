# Sparky Game Engine

Sparky is a game engine I'm writing while watching The Cherno's game engine video
series on YouTube.

[Sparky Game Engine](https://youtube.com/playlist?list=PLlrATfBNZ98fqE45g3jZA_hLGUrD4bo6_&si=_PbAR4AgU0UG696Z)

The engine currently only spports MacOS and WebGL. Linux and Windows will be added.

## How To Build

You will need CMake version 3.27.6 or greater and Emscripten to build/run the project.

CMake
- [Homepage](https://cmake.org)
- [Download](https://cmake.org/download/)

Emscripten
- [Homepage](https://emscripten.org)
- [Download](https://emscripten.org/docs/getting_started/downloads.html)

### Initial Setup

Clone the repository:

```
git clone git@github.com:profeclipse/sparky.git
```

Change to the project directory:

```
cd sparky
```

Configure the build system:

```
scripts/bootstrap
scripts/setup
```

### Build the Engine and Demo

To build the engine and demo for MacOS:

```
scripts/build -p mac
```

To build the engine and demo for Web:

```
scripts/build -p web
```

To build the enigne and demo for all supported platforms:

```
scripts/build -p all
```

## Running the demo

### Running the Native Demo

```
cd build/sparky-demo
./sparky-demo
```

(The demo depends on the resource directory `res` being in the current directory.)

### Running the Web Application

#### Run with `emrun`

```
cd embuild/sparky-demo
emrun sparky-demo.html
```

#### Using python as a web server

Start the web server:
- Python 2: `python -m SimpleHTTPServer`
- Python 3: `python -m http.server`

Open a web browser and point to `http://localhost:8000` and navigate to `sparky-demo.html`.
