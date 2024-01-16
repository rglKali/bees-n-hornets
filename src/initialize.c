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


Base * initialize_base(int x, int y, char team) 
{
    Base * base = (Base*)malloc(sizeof(Base));
    if (base == NULL) {
        fprintf(stderr, "Memory allocation failed for base\n");
        exit(EXIT_FAILURE);
    }

    // Apply attributes
    base->team = team;
    base->x = x; base->y = y;
    base->job = ' '; base->prod = 0;

    base->next = base->prev = NULL;
    base->units = NULL;

    return base;
}


Unit * initialize_unit(int x, int y, char team, char type) 
{
    Unit * unit = (Unit*)malloc(sizeof(Unit));
    if (unit == NULL) 
    {
        fprintf(stderr, "Memory allocation failed for unit\n");
        exit(EXIT_FAILURE);
    }

    // Apply attributes
    unit->team = team; unit->type = type;
    unit->x = x; unit->y = y; unit->move = true;

    switch (type)
    {
        case BEE_QUEEN: unit->force = BEE_QUEEN_FORCE; break;
        case BEE_WORKER: unit->force = BEE_WORKER_FORCE; break;
        case BEE_FIGHTER: unit->force = BEE_FIGHTER_FORCE; break;
        case BEE_SQUADRON: unit->force = BEE_SQUADRON_FORCE; break;
        case HORNET_QUEEN: unit->force = HORNET_QUEEN_FORCE; break;
        case HORNET_HORNET: unit->force = HORNET_HORNET_FORCE; break;
    }

    unit->b_next = unit->b_prev = NULL;
    unit->t_next = unit->t_prev = NULL;
    unit->base = NULL;

    return unit;
}


void destroy_unit(Unit * unit) 
{
    unlink_unit_from_base(unit);
    unlink_unit_from_tile(unit);
    free(unit);
}

void destroy_base(Base * base)
{
    while (base->units != NULL)
    {
        destroy_unit(base->units);
    }
    unlink_base_from_tile(base);
    unlink_base_from_board(base);
    free(base);
}