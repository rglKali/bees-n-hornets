#include <stdlib.h>
#include <stdio.h>
#include "structs.h"
#include "consts.h"
#include "links.h"
#include "initialize.h"
#include "game.h"

Board board;


void produce_in_hive(Base * hive, char type)
{
    switch (type)
    {
        case BEE_QUEEN: if (board.bees > BEE_QUEEN_PRICE)
            {
                board.bees -= BEE_QUEEN_PRICE;
                hive->job = BEE_QUEEN;
                hive->prod = BEE_QUEEN_TIME;
            } break;
        case BEE_WORKER: if (board.bees > BEE_WORKER_PRICE)
            {
                board.bees -= BEE_WORKER_PRICE;
                hive->job = BEE_WORKER;
                hive->prod = BEE_WORKER_TIME;
            } break;
        case BEE_FIGHTER: if (board.bees > BEE_FIGHTER_PRICE)
            {
                board.bees -= BEE_FIGHTER_PRICE;
                hive->job = BEE_FIGHTER;
                hive->prod = BEE_FIGHTER_TIME;
            } break;
        case BEE_SQUADRON: if (board.bees > BEE_SQUADRON_PRICE)
            {
                board.bees -= BEE_SQUADRON_PRICE;
                hive->job = BEE_SQUADRON;
                hive->prod = BEE_SQUADRON_TIME;
            } break;
    }
}


void produce_in_nid(Base * nid, char type)
{
    switch (type)
    {
        case HORNET_QUEEN: if (board.hornets > HORNET_QUEEN_PRICE)
            {
                board.hornets -= HORNET_QUEEN_PRICE;
                nid->job = HORNET_QUEEN;
                nid->prod = HORNET_QUEEN_TIME;
            } break;
        case HORNET_HORNET: if (board.hornets > HORNET_HORNET_PRICE)
            {
                board.hornets -= HORNET_HORNET_PRICE;
                nid->job = HORNET_HORNET;
                nid->prod = HORNET_HORNET_TIME;
            } break;
    }
}


void start_production(Base * base, char type)
{
    if (base->job != ' ') { return; }
    switch (base->team) {
        case BEE: produce_in_hive(base, type); break;
        case HORNET: produce_in_nid(base, type); break;
    }
}


void start_harvest(Unit * worker)
{
    if (!worker->move) { return; }
    worker->move = false;
    worker->job = 'R';
    worker->prod = HARVEST_TIME;
}


void move(Unit * unit, int x, int y)
{
    if (!unit->move) { return; }
    unlink_unit_from_tile(unit);
    unit->x = x; unit->y = y;
    link_unit_to_tile(unit);
    unit->move = false;
}


void build_a_hive(Unit * queen)
{
    if (board.bees > BEE_HIVE_PRICE) 
    {
        Base * hive = initialize_base(queen->x, queen->y, BEE);
        board.bees -= BEE_HIVE_PRICE;
        queen->move = false;
        unlink_unit_from_base(queen);
        link_base_to_board(hive);
        link_unit_to_base(queen, hive);
        link_base_to_tile(hive);
    }
}


void build(Unit * queen) 
{
    if (!queen->move) { return; }
    Base * base = NULL;
    switch (queen->team) 
    {
        case BEE: if (board.bees >= BEE_HIVE_PRICE) 
            {
                board.bees -= BEE_HIVE_PRICE;
                base = initialize_base(queen->x, queen->y, BEE);
            }
        case HORNET: if (board.hornets >= HORNET_NID_PRICE) 
            {
                board.hornets -= HORNET_NID_PRICE;
                base = initialize_base(queen->x, queen->y, HORNET);
            }
    }
    if (base != NULL)
    {
        queen->move = false;
        unlink_unit_from_base(queen);
        link_base_to_board(base);
        link_unit_to_base(queen, base);
        link_base_to_tile(base);
    }
}


void finish_production(Base * base)
{
    Unit * unit = initialize_unit(base->x, base->y, base->team, base->job);
    link_unit_to_base(unit, base);
    link_unit_to_tile(unit);

    base->job = ' '; base->prod = 0;
}


void finish_harvest(Unit * worker)
{
    unlink_unit_from_base(worker);
    unlink_unit_from_tile(worker);
    destroy_unit(worker);
}