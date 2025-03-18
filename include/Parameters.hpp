#pragma once
#include<math.h>
#include<stdio.h>

struct GridParameters
{
    double epsilon=0.2;

    // weight associated with border length cost
    double mu=0.1;

    // Weight
    double v=0.0;

    // Interior area cost
    double lambda_1=1.2;

    // Exterior area cost
    double lambda_2=1.2;

    // Minimum loss function value allowed for an image to be considered solution
    double tolerance=10.0;

    double delta_t = 0.7;

    double eta = 0.1;

    size_t max_iterations = 100;

    bool log_iterations = false;

    bool save_iter = false;
};

/**
 * @brief Mathematical heavyside function calculated with an estimation of parameters.epsilon
 * 
 * @param parameters 
 * @param x 
 * @return double 
 */
double Heaviside(const GridParameters& parameters ,const double x);

/**
 * @brief Mathematical Dirac function calculated with an estimation of parameters.epsilon
 * 
 * @param parameters 
 * @param x 
 * @return double 
 */
double Dirac(const GridParameters& parameters ,const double x);
