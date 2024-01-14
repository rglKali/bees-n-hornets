#ifndef GAME_STRUCTS_H
#define GAME_STRUCTS_H

#include <stdbool.h>
#include "game.h"

typedef struct unit {
    // Common attributes
    char team, type;                // Unit's team & type
    int x, y;                       // Unit's position
    bool move;                      // Unit's destination
    int force;                      // If unit can move (can move by default by the begginig of the turn except busy workers)
    struct unit *t_next, *t_prev;   // Links to another units in the same tile (if any)
    struct unit *b_next, *b_prev;   // Links to another units in the same base (if any)

    // worker-spesific attrs
    char job;                       // The current unit, that is produced, if any (for wokrer should be "R")
    int prod;                       // Amount of turns left till production is finished
} Unit;


typedef struct base {
    char team;
    int x, y;
    char job;                       // The current unit, that is produced, if any (for wokrer should be "R")
    int prod;                       // Amount of turns left till production is finished

    struct base *next, *prev;       // Links to other bases
    struct unit *units;             // Links to related units
} Base;


typedef struct tile {
    int x, y;                       // tile position in the grid
    struct base *base;              // Link to the base in the tile (if any)
    struct unit *units;             // link to the units in the tile (if any)
} Tile;


typedef struct board {
    struct tile tiles               // The 2d array of tiles
    [BOARD_ROWS][BOARD_COLS];
    int turn;                       // The current turn
    int bees, hornets;              // Resources of bees and hornets
    struct base *hive, *nid;        // Links to the Bees and Hornets starter bases
} Board;

extern Board board;

#endif