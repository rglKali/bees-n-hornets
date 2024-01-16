#include <stdio.h>
#include "MLV/MLV_all.h"
#include "game.h"

#define CELL_SIZE 60


int main()
{
    MLV_create_window("Bees and Hornets", "BaH", 800, 450);
    MLV_actualise_window();
    MLV_wait_seconds( 15 );
    MLV_free_window();
    return 0;
}
