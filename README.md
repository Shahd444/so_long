# so_long

A simple 2D game developed in C using the MiniLibX graphics library. The player moves around a tile-based map, collects all collectibles, and reaches the exit to win. The project focuses on event handling, image rendering, and basic game logic.

Features:
- Map parsing from a .ber file.
- Keyboard input to move the player (WASD).
- Collectibles must be gathered before the exit is usable.
- Step counter displayed on screen or in terminal.
- Basic collision detection (walls, closed exit).
- Error handling for invalid maps.

Game Rules:
- You control a character that must collect all items (C)
- After collecting everything, you must reach the exit (E)

The map contains walls (1), floor (0), player (P), collectibles (C), and an exit (E)

Map Requirements:
- Rectangular shape
- Surrounded by walls
- Contains exactly one player and at least one collectible and one exit

Controls:
- W – move up
- A – move left
- S – move down
- D – move right
- ESC – quit the game

How to Build:
`make`

How to Play:
`./so_long maps/example.ber`
