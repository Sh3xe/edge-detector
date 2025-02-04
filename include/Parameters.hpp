#pragma once
#include<math.h>
#include<stdio.h>

const float eps = 0.00001;

struct GridParameters
{
    long double epsilon=0;
    long double mu=0;
    long double v=0;
    long double lambda_1=0;
    long double lambda_2=0;
};


long double Heaviside(const GridParameters& Image,const long double x){


    return (0.5+atan(x/Image.epsilon)/M_PIl);

};

long double Dirac(const GridParameters& Image,const long double x){

    return (Image.epsilon/(M_PIl*(Image.epsilon*Image.epsilon+x*x)));

};
