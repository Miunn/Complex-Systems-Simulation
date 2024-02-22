/**
 * @file main.c
 * @author Caulier Rémi (remi@remicaulier.fr)
 * @brief Main file to run simulation
 * @version 0.1
 * @date 2024-02-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */


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