#include <stdlib.h>
#include <stdio.h>
#include "initialize.h"
#include "structs.h"
#include "links.h"
#include "game.h"


void initialize_board() 
{
    // Initialize the turn and resources
    board.turn = 0;
    board.bees = 10;
    board.hornets = 10;

    // Initialize each tile in the board
    for (int i = 0; i < BOARD_ROWS; i++) 
    {
        for (int j = 0; j < BOARD_COLS; j++) 
        {
            board.tiles[i][j].x = i;
            board.tiles[i][j].y = j;
            board.tiles[i][j].units = NULL;
            board.tiles[i][j].base = NULL;
        }
    }
}


void initialize_hive(int x, int y)
{
    // Allocate memory
    Base * hive = (Base*)malloc(sizeof(Base));
    if (hive == NULL) {
        fprintf(stderr, "Memory allocation failed for Hive\n");
        exit(EXIT_FAILURE);
    }

    // Apply attributes
    hive->team = BEE;
    hive->x = x; hive->y = y;
    hive->job = ' ';
    hive->prod = 0;
}

void initialize_nid(int x, int y)
{
    // Allocate memory
    Base * nid = (Base*)malloc(sizeof(Base));
    if (nid == NULL) {
        fprintf(stderr, "Memory allocation failed for nid\n");
        exit(EXIT_FAILURE);
    }

    // Apply attributes
    nid->team = HORNET;
    nid->x = x; nid->y = y;
    nid->job = ' ';
    nid->prod = 0;
}