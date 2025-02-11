#pragma once
#include<math.h>
#include<stdio.h>

const float eps = 0.00001;

struct GridParameters
{
    double epsilon=0;
    double mu=0;
    double v=0;
    double lambda_1=0;
    double lambda_2=0;
    double tolerance=0.1;
};


double Heaviside(const GridParameters& Image,const double x){


    return (0.5+atan(x/Image.epsilon)/M_PIl);

};

double Dirac(const GridParameters& Image,const double x){

    return (Image.epsilon/(M_PIl*(Image.epsilon*Image.epsilon+x*x)));

};
