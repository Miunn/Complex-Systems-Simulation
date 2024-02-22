/**
 * @file norm_random.c
 * @author Caulier Rémi (remi@remicaulier.fr)
 * @brief Random normal distribution implementation
 * @version 0.1
 * @date 2024-02-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdlib.h>
#include <math.h>

double uniformRand(double min, double max)
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

double boxMullerTransform()
{
    return sqrtf64(-2*log(uniformRand(0,1)))*cos(23.14*uniformRand(0,1));
}

double normalRand(double mean, double sd)
{
    return boxMullerTransform()*sd + mean;
}