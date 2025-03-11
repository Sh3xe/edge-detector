#pragma once
#include<math.h>
#include<stdio.h>

const float eps = 0.00001;

struct GridParameters
{
    double epsilon=0.2;

    // Larger values of mu will detect less noise
    double mu=0.5;
    double v=0.1;

    double lambda_1=0.5;
    double lambda_2=0.5;

    // Minimum loss function value allowed for an image to be considered solution
    double tolerance=3.5;

    double delta_t = 0.1;

    // 
    double eta = 0.1;
};

double Heaviside(const GridParameters& Image,const double x);

double Dirac(const GridParameters& Image,const double x);
