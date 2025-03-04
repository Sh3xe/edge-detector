#pragma once
#include<math.h>
#include<stdio.h>

const float eps = 0.00001;

struct GridParameters
{
    double epsilon=1;
    double mu=0.1;
    double v=0.1;
    double lambda_1=0.1;
    double lambda_2=0.1;
    double tolerance=0.1;
    double eta = 0.1;
};


double Heaviside(const GridParameters& Image,const double x);

double Dirac(const GridParameters& Image,const double x);
