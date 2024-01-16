#ifndef GAME_INIT_H
#define GAME_INIT_H

#include "structs.h"

void initialize_board();

Base * initialize_base(int x, int y, char team);

Unit * initialize_unit(int x, int y, char team, char type);

void destroy_unit(Unit * unit);

void destroy_base(Base * base);

#endif