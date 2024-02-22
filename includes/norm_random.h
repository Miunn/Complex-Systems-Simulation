/**
 * @file norm_random.h
 * @author Caulier Rémi (remi@remicaulier.fr)
 * @brief Random normal distribution functions definition
 * @version 0.1
 * @date 2024-02-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef NORM_RANDOM_H
#define NORM_RANDOM_H

double uniformRand(double min, double max);
double boxMullerTransform();
double normalRand(double mean, double sd);

#endif