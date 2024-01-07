# Raylib-Slo-Jam2023: Asteroids Redux

My enty for the Raylib Slo Jam

## Keyboard Controls
- W: Speed Up
- S: Slow Down
- A: Rotate Left
- D: Rotate Right
- Space Bar: Shoot
- Arrow Key Down: Zoom Out
- Arrow Key Up: Zoom Up
- P: Pause

## Gamepad Controls
- Left Stick Forward: Speed Up
- Left Stick Backward: Slow Down
- Right Stick Right: Rotate Left
- Right Stick Left: Rotate Right
- Right Trigger: Shoot
- Left Bumper: Zoom Out
- Right Bumper: Zoom Up
- Start Button: Pause

## Goal of the Game
Destroy as many asteroids and npc ships before the time runs out. Asteroids are worth 1 point while ships are worth 5 points. Be careful, as sometimes the ships will attack back!

## Build Instructions
### Executable
```
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
make
./main
```

### Web Build With Emscripten
```
mkdir web_build
cd web_build
emcmake cmake .. -DPLATFORM=Web -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXE_LINKER_FLAGS="-s USE_GLFW=3" -DCMAKE_EXECUTABLE_SUFFIX=".html" -G "MinGW Makefiles"
emmake make
emrun main.html
```

## Source Code
https://github.com/RyanDeivert555/Raylib-Slo-Jam2023