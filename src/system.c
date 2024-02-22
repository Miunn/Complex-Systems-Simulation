/**
 * @file system.c
 * @author Caulier Rémi (remi@remicaulier.fr)
 * @brief System functions implementation
 * @version 0.1
 * @date 2024-02-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include "../includes/system.h"
#include "../includes/norm_random.h"

SYSTEM* init_new_system()
{
    SYSTEM* system = (SYSTEM*) malloc(sizeof(SYSTEM));

    system->t = 0;
    system->t_max = 20;
    system->t_arr = 0;
    system->t_att_cum = 0;
    system->t_cum = 0;
    system->t_occ = 0;
    system->delta = 0;
    system->t_dep = DBL_MAX;
    system->long_file = 0;

    system->state = 0;

    system->nb_arr = 0;
    system->nb_servis = 0;

    system->t_moy_sej = 0;
    system->n_moy_sej = 0;
    system->t_moy_att = 0;
    system->taux_att_obs = 0;
    system->taux_occ = 0;
    system->productivity = 0;
    system->mu_obs = 0;

    return system;
}

SYSTEM* init_new_system_max(int t_max)
{
    SYSTEM* system = init_new_system();

    system->t_max = t_max;

    return system;
}

void run_simulation(SYSTEM* system)
{
    while (system->t < system->t_max && ((system->t_dep < system->t_max) || (system->t_arr < system->t_max)))
    {
        if (system->t_arr < system->t_dep)
        {
            system->nb_arr++;
            system->delta = system->t_arr - system->t;
            system->t = system->t_arr;
            system->t_arr = system->t + generate_inter_time();
            system->t_cum = system->t_cum + system->delta*(system->long_file + system->state);  // Temps de séjour
            system->t_att_cum = system->t_att_cum + system->delta * system->long_file;  // Temps attente en file
            system->t_occ = system->t_occ + system->delta * system->state;

            if (system->state == 0)
            {
                system->state = 1;
                system->t_dep = system->t + generate_service_time();
            }
            else
            {
                system->long_file++;
            }

            system->t_arr = system->t + generate_arrival_time();
        }
        else
        {
            system->nb_servis++;
            system->delta = system->t_dep - system->t;
            system->t = system->t_dep;
            system->t_cum = system->t_cum + system->delta * (system->long_file + system->state);
            system->t_att_cum = system->t_att_cum + system->delta * system->long_file;
            system->t_occ = system->t_occ + system->delta;

            if (system->long_file > 0)
            {
                system->long_file--;
                system->t_dep = system->t + generate_service_time();
            }
            else
            {
                system->state = 0;
                system->t_dep = DBL_MAX;
            }
        }

    }

    system->delta = system->t_max - system->t;
    system->t = system->t_max;
    system->t_cum = system->t_cum + system->delta * (system->long_file + system->state);
    system->t_occ = system->t_occ + system->delta * system->state;
    system->t_att_cum = system->t_att_cum + system->delta * system->long_file;

    system->t_moy_sej = system->t_cum / (double)system->nb_arr;
    system->n_moy_sej = system->t_cum / system->t;
    system->t_moy_att = system->t_att_cum / (double)system->nb_arr;

    system->taux_att_obs = system->nb_arr / system->t;
    system->taux_occ = system->t_occ / system->t;

    system->productivity = system->nb_servis / system->t_max;
    system->mu_obs = system->nb_servis / system->t_occ;
}

int generate_service_time()
{
    return normalRand(5, 3);
}

int generate_inter_time()
{
    return normalRand(5, 3);
}

int generate_arrival_time()
{
    return normalRand(5, 3);
}