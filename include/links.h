#ifndef GAME_LINKS_H
#define GAME_LINKS_H

#include "structs.h"

void link_hive_to_board(Base * hive);

void link_nid_to_board(Base * nid);

void link_base_to_tile(Base *base);

void link_unit_to_tile(Unit * unit);

void link_unit_to_base(Unit * unit, Base * base);

void unlink_hive_from_board(Base * hive);

void unlink_nid_from_board(Base * nid);

void unlink_base_from_tile(Base * base);

void unlink_unit_from_tile(Unit * unit);

void unlink_unit_from_base(Unit * unit, Base * base);

#endif