# cub3D

### Description
cub3D is a project inspired by the historic game Wolfenstein 3D. The goal is to create a realistic 3D first-person graphical representation of a maze using ray-casting principles.

### Objectives
Language: C
Graphics Library: miniLibX
Key Features: Player movement, wall textures display, floor and ceiling color management, window interactions (exit via ESC or the red cross).
#####Requirements
Necessary installations: miniLibX, a compatible C compiler (e.g., gcc).
Allowed libraries: libft, math (-lm), minilibx.

### Usage Instructions

1. Execution
   
`
./cub3D path/to/scene.cub
`

3. Controls:
   

- **W, A, S, D**: Move the viewpoint through the maze.
- **Left/Right arrows**: Rotate the view.
- **ESC**: Exit the program.
- **Click on the red cross**: Close the window.

### .cub File Format
- Wall Textures: Specify paths for north, south, east, and west textures.
- Colors: Use identifiers F (floor) and C (ceiling) followed by RGB values.
- Map: Consists of 1 (wall), 0 (empty space), and N, S, E, W for player starting position and orientation.

Example .cub File

```bash
NO ./textures/north_texture.xpm
SO ./textures/south_texture.xpm
WE ./textures/west_texture.xpm
EA ./textures/east_texture.xpm
F 220,100,0
C 225,30,0

111111
100001
101101
1000N1
111111
```

### Error Handling
The program will return *Error\n* followed by a descriptive message if there is any misconfiguration in the .cub file.

### Possible Bonuses
- Wall collisions
- Minimap system
- Doors that can open and close
- Animated sprites
- Rotate the view with the mouse
