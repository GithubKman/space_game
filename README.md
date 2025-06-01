# Space mining simulator game using Raylib

Work in progress game for me to improve coding skills and have fun.

#### TODO:
  -Add objects like asteroids <br>
  -Add polygon collisions to asteroids


## Usage

To compile, use one of the following dependending on your build target...

### Desktop

#### Dependencies:
All raylib build dependencies <br>
GLFW (optional)
#### To compile:
Use the following to build for desktop:

``` bash
cmake -B build
cmake --build build
```

### Web

Compiling for the web requires the [Emscripten SDK](https://emscripten.org/docs/getting_started/downloads.html):

``` bash
mkdir build
cd build
emcmake cmake .. -DPLATFORM=Web -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXECUTABLE_SUFFIX=".html"
emmake make
```
