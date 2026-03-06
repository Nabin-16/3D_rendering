# 3D Rendering Engine

A lightweight 3D software renderer built from scratch in C++ using SDL2. No OpenGL or graphics APIs — just pure math. Supports loading and interactively viewing `.obj` 3D models with back-face culling, perspective projection, flat shading, and depth sorting.


---

## Features

- Load and render `.obj` 3D models
- Real-time rotation and translation controls
- Flat shading with lighting
- Built from scratch — no external graphics APIs

---

## Project Structure

```
main/
|__ Demo                   # Demo including mountains.obj and VideoShip.obj
| 
├── main.cpp               # Entry point, scene management, input handling
├── headers/
│   ├── triangle.h         # Triangle class, projection, rendering pipeline
│   ├── matrix.h           # Matrix math + rotation matrices (X, Y, Z)
│   └── vector.h           # 3D vector math (cross product, dot product, normalize)
├── src/
│   ├── include/SDL2/      # SDL2 headers
│   └── lib/               # SDL2 libraries
├── teapot.obj             # Utah teapot model
├── mountains.obj          # Mountain terrain model
└── VideoShip.obj          # Spaceship model
```

---

## Setup & Build (Windows)

### Prerequisites

**1. MinGW-w64 (C++ Compiler)**

Download the latest **x86_64** release from [winlibs.com](https://winlibs.com) — grab the `GCC x86_64-w64-mingw32 UCRT` zip.

Extract to `C:\mingw64`, then add `C:\mingw64\bin` to your system PATH:
- Search **Environment Variables** in Start Menu
- Under System Variables → **Path** → Edit → New → `C:\mingw64\bin`
- Open a new terminal and verify: `g++ --version`

**2. SDL2 Development Libraries**

Download `SDL2-devel-2.x.x-mingw.tar.gz` from the [SDL2 releases page](https://github.com/libsdl-org/SDL/releases).

Extract and copy the **x86_64-w64-mingw32** folder contents:
- `include/SDL2/` → `main/src/include/SDL2/`
- `lib/` → `main/src/lib/`
- `bin/SDL2.dll` → `main/SDL2.dll`

### Build

```bat
cd main
g++ -g -I src/include -L src/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2
```

### Run

```bat
.\main.exe
```

---

## Controls

| Key | Action |
|-----|--------|
| `↑ / ↓` | Rotate X axis |
| `← / →` | Rotate Y axis |
| `8 / 2` | Rotate Z axis |
| `W / S` | Move forward / backward |
| `A / D` | Move left / right |

---

## Loading a Different Model

In `main.cpp`, find the `render()` function and change:

```cpp
scene.load_object_from_file("teapot.obj");
```

to any `.obj` file in the same directory, e.g.:

```cpp
scene.load_object_from_file("mountains.obj");
```

Then rebuild and run.

---

## Exporting .obj Files from Blender

1. Open [blender.org](https://www.blender.org) and download Blender (free)
2. Create or open a 3D model
3. Go to **File → Export → Wavefront (.obj)**
4. In the export options:
   - Make sure **Triangulate Faces** is checked (important!)
   - Uncheck **Write Normals** and **Write UVs** to keep the file simple
5. Save the `.obj` file into the `main/` folder
6. Update `load_object_from_file()` in `main.cpp` with the new filename

> **Note:** This engine only supports simple `v` (vertex) and `f` (face) lines. Face indices must be plain integers — no `f v/vt/vn` slash format.

---

## Dependencies

- [SDL2](https://www.libsdl.org/) — windowing and rendering (included in repo)
- C++17 or later
- MinGW-w64 (Windows)

---

## License

MIT License — free to use and modify.