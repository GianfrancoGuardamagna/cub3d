*This project has been created as part of the 42 curriculum by carmegon, gguardam.*


# cub3D

> A first-person 3D maze explorer built with ray casting, inspired by *Wolfenstein 3D*.

## Description

**cub3D** is a graphical project of the 42 curriculum. Its goal is to build a "realistic" 3D view of the inside of a maze, seen from a first-person perspective, using the **ray-casting** technique made famous by *Wolfenstein 3D* (1992), the first true FPS in video game history.

The program takes a scene description file (`.cub`) as its only argument. That file defines the wall textures, the floor and ceiling colors and the map of the maze. The program parses and validates the file, then opens a window where the player can walk around the maze and look left and right.

The project is written in **C**, follows the **42 Norm**, and uses **MLX42** (the graphics library) and our own **libft**.

### Features

- Parsing of `.cub` files: any order of elements, free number of blank lines and spaces between them.
- A different texture for each wall orientation (North, South, East, West).
- Configurable floor and ceiling colors, read from the `.cub` file.
- Strict map validation: allowed characters, exactly one player and a map closed by walls.
- Maps of any size and with rows of different length (spaces are valid map characters).
- Clean error handling: `Error` followed by an explicit message, with no crashes and no leaks.
- Smooth movement and rotation, with **wall collisions**.
- A **minimap** in the top-left corner showing the maze and the player.
- Clean exit with `ESC` or by clicking the red cross of the window.

### How it works

1. **Parsing** – The file is read line by line with `get_next_line`. The texture paths and the colors are stored first; when the map starts, its rows are stored in a `char **` array that grows one row at a time.
2. **Validation** – The colors must be `R,G,B` values in `[0, 255]`. The map may only contain `0 1 N S E W` and spaces, must contain exactly one player, and every walkable cell must be surrounded by walls (no walkable cell may touch a space or the edge of the map).
3. **Ray casting** – For every vertical column of the window, one ray is cast from the player. The **DDA** (*Digital Differential Analyzer*) algorithm moves the ray from grid cell to grid cell until it hits a wall, and gives the exact distance to it.
4. **Projection** – The height of the wall column is inversely proportional to that distance. The distance is corrected with the cosine of the ray angle to avoid the *fisheye* effect.
5. **Texturing** – The side of the wall that was hit (N, S, E, W) selects the texture, and the exact hit position selects the texture column. Floor and ceiling are painted with the colors of the `.cub` file.
6. **Events** – Keys are read every frame to move and rotate the player. Before each move, the four corners of the player's hitbox are checked against the map to prevent walking through walls.

## Instructions

### Requirements

- Linux
- `cc`, `make` and `cmake`
- GLFW (`libglfw3-dev`) and the usual X11 development packages
- The `libft/` and `MLX42/` folders at the root of the repository

### Compilation

From the root of the repository:

```bash
make
```

This builds `libft`, `MLX42` (only if it is not built yet) and the executable `cub3D`.

If anything fails, or after changing a macro, clean everything and rebuild:

```bash
make re
```

> `make re` also rebuilds MLX42 from scratch, so it takes longer than a normal `make`.

Other rules: `make clean`, `make fclean`, `make bonus`.

### Execution

Run the executable followed by a map file with the `.cub` extension:

```bash
./cub3D maps/map1.cub
```

Textures are loaded using the paths written in the `.cub` file, relative to the folder **from which you run the program**.

### Controls

| Key | Action |
|---|---|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Move (strafe) left |
| `D` | Move (strafe) right |
| `←` | Look left |
| `→` | Look right |
| `ESC` | Quit the program |
| Window close button (red cross) | Quit the program |

> **Mouse:** looking around is meant to be done with the arrow keys. The mouse look is optional and **off by default**: it can be toggled with the `C` key (the arrow keys are disabled while it is on; press `C` again to go back).

### Changing the window size

The size of the window is defined by two macros at the top of `cub3d.h`:

```c
# ifndef WIDTH
#  define WIDTH 900
# endif
# ifndef HEIGHT
#  define HEIGHT 600
# endif
```

Edit the two numbers and run `make` again (all the objects depend on `cub3d.h`, so everything is recompiled). Examples to try:

| Resolution | `WIDTH` | `HEIGHT` |
|---|---|---|
| Small | `640` | `480` |
| Classic | `800` | `600` |
| **Default** | `900` | `600` |
| HD | `1280` | `720` |
| HD+ | `1600` | `900` |
| Full HD | `1920` | `1080` |

Notes:

- One ray is cast per pixel column, so very large windows need more computation.
- The minimap automatically scales with the window (it uses a quarter of its width and height).
- If something looks odd after the change, run `make re`.

Other macros in `cub3d.h` that can be played with:

| Macro | Default | Meaning |
|---|---|---|
| `PLAYER_FOV` | `60` | Field of view, in degrees |
| `PLAYER_RADIUS` | `15` | Size of the player's hitbox (collisions) |
| `ROT_SPEED` | `0.0523…` | Rotation speed of the arrow keys, in radians per frame (3°) |
| `MOUSE_SENS` | `0.001` | Mouse look sensitivity |

### The `.cub` file

A scene file has two parts: the **elements** (textures and colors) and the **map**, which must always be the last thing in the file.

```
NO ./textures/wall_N.png
SO ./textures/wall_S.png
WE ./textures/wall_W.png
EA ./textures/wall_E.png

F 220,100,0
C 135,206,235

111111111111
100000000001
1000111000011111111
10001 10N0000000001
1000111000011111111
111111111111
```

**Elements** (in any order, separated by any number of empty lines; the identifier and its value can be separated by any number of spaces):

| Identifier | Meaning | Value |
|---|---|---|
| `NO` | North wall texture | Path to a `.png` file |
| `SO` | South wall texture | Path to a `.png` file |
| `WE` | West wall texture | Path to a `.png` file |
| `EA` | East wall texture | Path to a `.png` file |
| `F` | Floor color | `R,G,B`, each from `0` to `255` |
| `C` | Ceiling color | `R,G,B`, each from `0` to `255` |

**Map rules:**

- Only these characters are allowed: `0` (empty space), `1` (wall), `N`, `S`, `E`, `W` (player start position and initial orientation) and the space character.
- There must be **exactly one** player.
- The map must be **closed**: every `0` and the player must be surrounded by `1`s (never touching a space or the border of the map). Spaces inside the map are fine as long as they are surrounded by walls.
- Rows can have different lengths.

#### Color examples to try

Change the `F` (floor) and `C` (ceiling) lines of any `.cub` file:

| Mood | Ceiling `C` | Floor `F` |
|---|---|---|
| Sunny day | `C 135,206,235` | `F 34,139,34` |
| Sunset | `C 255,140,60` | `F 60,30,20` |
| Night | `C 10,10,40` | `F 20,20,20` |
| Dungeon | `C 40,40,40` | `F 90,60,30` |
| Desert | `C 250,220,160` | `F 210,170,100` |
| Underwater | `C 0,60,120` | `F 0,30,60` |
| Candy | `C 255,182,193` | `F 186,85,211` |

### Error handling

If the file or the arguments are wrong, the program prints `Error` on the first line and an explicit message on the second one (on the standard error output), frees everything and exits with status `1`. The program detects, among others:

| Situation | Message |
|---|---|
| Wrong number of arguments | `Usage: ./cub3D map.cub` |
| File without the `.cub` extension | `Invalid file extension. Have to be .cub` |
| File that cannot be opened | `Cannot open file` |
| Missing texture or color | `Missing textures` / `Missing floor or ceiling color` |
| Texture file that cannot be loaded | `Cannot load texture: <path>` |
| Color with a wrong format or out of range | `Invalid color. Use R, G, B from 0 to 255` |
| No map in the file | `No map found in file` |
| Forbidden character in the map | `Invalid character in map` |
| No player, or more than one | `Map needs exactly one player` |
| Map not closed by walls | `Map is not closed by walls` |

### Project structure

```
.
├── Makefile
├── cub3d.h              # structures, macros and prototypes
├── main.c
├── libft/               # our libft (with ft_fprintf and get_next_line)
├── MLX42/               # graphics library
└── src/
    ├── parsing/         # .cub reading, colors, map storage and validation
    ├── init/            # window, textures, player, keyboard/mouse events
    ├── utils/           # error handling and memory cleanup
    ├── dda.c            # DDA ray casting algorithm
    ├── render.c         # drawing of the walls, floor and ceiling
    ├── textures.c       # texture selection and pixel reading
    ├── collision.c      # wall collisions
    ├── moves.c          # player movement
    └── minimap.c        # minimap
```

## Resources

### References

- Lode Vandevenne – *Raycasting* (the DDA algorithm explained step by step): <https://lodev.org/cgtutor/raycasting.html>
- Lode Vandevenne – *Raycasting II: textured walls*: <https://lodev.org/cgtutor/raycasting2.html>
- MLX42 – official repository and documentation: <https://github.com/codam-coding-college/MLX42> and <https://github.com/codam-coding-college/MLX42/wiki>
- Ray casting – Wikipedia: <https://en.wikipedia.org/wiki/Ray_casting>
- J. Amanatides and A. Woo – *A Fast Voxel Traversal Algorithm for Ray Tracing* (Eurographics, 1987), the grid traversal on which DDA ray casting is based.
- Fabien Sanglard – *Game Engine Black Book: Wolfenstein 3D*.
- Original *Wolfenstein 3D*, playable online (link given in the subject): <http://users.atw.hu/wolf3d/>
- The 42 *Norm* and the *cub3D* subject.

### Use of AI

AI tools (Claude) were used as a learning and productivity aid, **not** as a replacement for understanding the code. Specifically:

- **Understanding the theory:** to understand how ray casting works (rays, the DDA algorithm, wall projection, the fisheye correction and texture mapping) and how MLX42 works (images, textures, hooks and the main loop).
- **Parsing and map storage:** to understand and design the file reading flow, how the map is stored in a dynamically growing `char **` array, and how the map validation (allowed characters, one player, closed map) works, using step-by-step explanations and diagrams.
- **Integration:** to help join the two halves of the project (the parser and the rendering engine), adapting the engine, which originally worked with a hard-coded map, to maps loaded from `.cub` files of any size.
- **Robustness and testing:** to review the code for crashes and memory problems (for example, the parsing of malformed colors and the cleanup on errors) and to build test `.cub` files with invalid inputs.
- **Code quality:** to fix Norm issues (splitting functions, removing dead code) and to review the Makefile.
- **Documentation:** to write this README (in English and Spanish).

In addition, **peer-to-peer learning** at 42 was key: discussing the project with other students and studying how they approached ray casting helped us understand the project much better.

Everything produced with the help of AI was reviewed, tested and kept only after being understood by the authors.

## Authors

- **carmegon**
- **gguardam**
