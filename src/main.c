#include <stdio.h>
#include <stdlib.h>
#include "../includes/system.h"

int main(int argc, char* argv[])
{
    SYSTEM* system = init_new_system();

    run_simulation(system);

    free(system);
    return 0;
}