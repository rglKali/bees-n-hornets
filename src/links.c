#include <stdlib.h>
#include <stdio.h>
#include "links.h"
#include "structs.h"


// Functions used to link files
void link_hive_to_board(Base * hive) 
{
    // Link to NULLs by default
    hive->prev = hive->next = NULL;

    // Check if the board has no hive yet
    if (board.hive == NULL) {
        board.hive = hive;
        return;
    }

    // Find the latest Hive
    Base *current = board.hive;
    while (current->next != NULL) {
        current = current->next;
    }

    // Link the hive to the end of the list
    current->next = hive;
    hive->prev = current;
}


void link_nid_to_board(Base * nid) 
{
    // Link to NULLs by default
    nid->prev = nid->next = NULL;

    // Check if the board has no nid yet
    if (board.nid == NULL) {
        board.nid = nid;
        return;
    }

    // Find the latest Nid
    Base *current = board.nid;
    while (current->next != NULL) {
        current = current->next;
    }

    // Link the nid to the end of the file
    current->next = nid;
    nid->prev = current;
    nid->next = NULL;
}


void link_base_to_tile(Base * base) 
{
    // Get the tile
    Tile *tile = &board.tiles[base->x][base->y];

    // Link the base to the tile
    tile->base = base;
}


void link_unit_to_tile(Unit * unit)
{
    // Link to NULLs by default
    unit->t_prev = unit->t_next = NULL;

    // Get the tile
    Tile * tile = &board.tiles[unit->x][unit->y];

    // Check if the tile has no unit yet
    if (tile->units == NULL) 
    {
        tile->units = unit;
        return;
    }

    // Find the latest Unit per tile
    Unit *current = tile->units;
    while (current->t_next != NULL) 
    {
        current = current->t_next;
    }

    // Link the unit to the end of the list
    current->t_next = unit;
    unit->t_prev = current;
}


void link_unit_to_base(Unit * unit, Base * base)
{
    // Link to NULLs by default
    unit->b_prev = unit->b_next = NULL;

    // Check if the base has no units yet
    if (base->units == NULL) {
        base->units = unit;
        return;
    }

    // Find the latest unit
    Unit *current = base->units;
    while (current->b_next != NULL) {
        current = current->b_next;
    }

    // Link the base to the end of the list
    current->b_next = unit;
    unit->b_prev = current;
}


void unlink_hive_from_board(Base * hive) 
{
    // Update the next hive's prev pointer
    if (hive->next != NULL) {
        hive->next->prev = hive->prev;
    } 
    
    // Update the prev hive's next pointer
    if (hive->prev != NULL) {
        hive->prev->next = hive->next;
    }

    // Update the board's pointers
    if (board.hive == hive) 
    { 
        board.hive = (hive->next != NULL) ? hive->next : hive->prev;
    }
}


void unlink_nid_from_board(Base * nid) 
{
    // Update the next nid's prev pointer
    if (nid->next != NULL) {
        nid->next->prev = nid->prev;
    } 
    
    // Update the prev nid's next pointer
    if (nid->prev != NULL) {
        nid->prev->next = nid->next;
    }

    // Update the board's pointers
    if (board.nid == nid) 
    { 
        board.nid = (nid->next != NULL) ? nid->next : nid->prev;
    }
}


void unlink_base_from_tile(Base * base) 
{
    // Get the tile
    Tile *tile = &board.tiles[base->x][base->y];

    // Link the base to the tile
    tile->base = NULL;
}


void unlink_unit_from_tile(Unit * unit) 
{
    // Get the tile
    Tile * tile = &board.tiles[unit->x][unit->y];

    // Update the next unit's prev pointer
    if (unit->t_next != NULL) {
        unit->t_next->t_prev = unit->t_prev;
    } 
    
    // Update the prev unit's next pointer
    if (unit->t_prev != NULL) {
        unit->t_prev->t_next = unit->t_next;
    }

    // Update the tile's pointers
    if (tile->units == unit) 
    { 
        tile->units = (unit->t_next != NULL) ? unit->t_next : unit->t_prev;
    }
}


void unlink_unit_from_base(Unit * unit, Base * base) 
{
    // Update the next unit's prev pointer
    if (unit->b_next != NULL) {
        unit->b_next->b_prev = unit->b_prev;
    } 
    
    // Update the prev unit's next pointer
    if (unit->b_prev != NULL) {
        unit->b_prev->b_next = unit->b_next;
    }

    // Update the tile's pointers
    if (base->units == unit) 
    { 
        base->units = (unit->b_next != NULL) ? unit->b_next : unit->b_prev;
    }
}