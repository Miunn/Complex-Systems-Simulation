/**
 * @file system.h
 * @author Caulier Rémi (remi@remicaulier.fr)
 * @brief System functions definition with statistics accumulators
 * @version 0.1
 * @date 2024-02-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef SYSTEM_H
#define SYSTEM_H

typedef struct SYSTEM
{
    double t;
    double t_max;
    double t_arr;
    double t_dep;
    double t_att_cum;
    double t_cum;
    double t_occ;
    double delta;
    int state;
    int nb_arr;
    int nb_servis;
    int long_file;

    // Mean values
    double t_moy_sej;       // bar{T}
    double n_moy_sej;       // bar{N}
    double t_moy_att;       // bar{T_att}
    double taux_att_obs;    // lambda observe
    double taux_occ;        // % occupation
    double productivity;
    double mu_obs;

} SYSTEM;

SYSTEM* init_new_system();
SYSTEM* init_new_system_max(int t_max);
void run_simulation(SYSTEM* system);
int generate_service_time();
int generate_inter_time();
int generate_arrival_time();

#endif