# Cub3D Parser

This is the parsing module for the Cub3D project at 42 School. The parser reads and validates `.cub` configuration files containing texture paths, colors, and map data.

## Features

### ✅ Completed Parsing Components

1. **File Reading and Validation**
   - Validates `.cub` file extension
   - Reads and parses entire file content
   - Handles errors gracefully

2. **Texture Parsing**
   - Parses 4 required textures: NO (North), SO (South), WE (West), EA (East)
   - Validates texture file paths exist
   - Detects duplicate texture definitions

3. **Color Parsing**
   - Parses floor (F) and ceiling (C) colors
   - Validates RGB values (0-255 range)
   - Supports comma-separated RGB format

4. **Map Parsing**
   - Extracts map from file after textures/colors
   - Normalizes map lines to consistent width
   - Supports irregular map shapes

5. **Map Validation**
   - Validates all characters (0, 1, N, S, E, W, spaces)
   - Finds and validates single player position
   - Checks map is enclosed by walls
   - Performs flood-fill connectivity check

## File Structure

```
Cub3d/
├── Makefile
├── inc/
│   └── cub3d.h           # Main header with structures and prototypes
├── src/
│   ├── main.c            # Entry point and initialization
│   ├── parsing/
│   │   ├── parse_file.c      # Main parsing orchestrator
│   │   ├── parse_textures.c  # Texture and color parsing
│   │   ├── parse_map.c       # Map extraction and parsing
│   │   └── validate_map.c    # Map validation algorithms
│   └── utils/
│       ├── utils.c       # String utilities (split, trim, etc.)
│       ├── error.c       # Error handling
│       └── free.c        # Memory management
├── textures/            # Sample texture files
└── test files (.cub)    # Test configuration files
```

## Data Structures

### Main Data Structure (`t_data`)
```c
typedef struct s_data
{
    // Textures
    char        *texture_paths[4];  // NO, SO, WE, EA
    t_color     floor_color;        // RGB floor color
    t_color     ceiling_color;      // RGB ceiling color
    
    // Map
    char        **map;              // 2D map array
    int         map_width;          // Map width
    int         map_height;         // Map height
    
    // Player
    float       player_x;           // Player X position
    float       player_y;           // Player Y position
    char        player_dir;         // Player direction (N,S,E,W)
    
    // Parsing state
    int         textures_parsed;    // Count of parsed textures
    int         colors_parsed;      // Count of parsed colors
    // ... other fields
} t_data;
```

## .cub File Format

```
NO ./textures/north_wall.xpm
SO ./textures/south_wall.xpm
WE ./textures/west_wall.xpm
EA ./textures/east_wall.xpm

F 220,100,0
C 225,30,0

1111111111
1000000001
1000N00001
1000000001
1111111111
```

## Usage

```bash
# Compile
make

# Run parser
./cub3D <map_file.cub>

# Test with provided examples
./cub3D simple_test.cub
./cub3D test.cub
```

## Validation Rules

1. **Textures**: All 4 textures (NO, SO, WE, EA) must be defined and files must exist
2. **Colors**: Floor (F) and Ceiling (C) colors must be defined with valid RGB values (0-255)
3. **Map Characters**: Only '0' (empty), '1' (wall), 'N/S/E/W' (player), and spaces allowed
4. **Player**: Exactly one player must be present
5. **Walls**: Map must be completely enclosed by walls ('1' characters)
6. **Connectivity**: All playable areas must be reachable from player position

## Error Handling

The parser provides detailed error messages for:
- Missing or invalid files
- Wrong file extensions
- Missing textures or colors
- Invalid RGB values
- Map validation failures
- Memory allocation errors

## Next Steps

1. **Install MLX**: Uncomment MLX-related lines in Makefile and header
2. **Rendering**: Implement raycasting engine
3. **Controls**: Add player movement and rotation
4. **Optimization**: Improve performance for larger maps
5. **Enhanced Features**: Add sprites, doors, etc.

## Testing

The project includes several test files:
- `simple_test.cub`: Basic valid map
- `test.cub`: Complex map (has disconnected regions - intentionally fails validation)

Try creating your own `.cub` files to test different scenarios!

---
*This parsing module provides a solid foundation for the Cub3D raycasting engine.*
