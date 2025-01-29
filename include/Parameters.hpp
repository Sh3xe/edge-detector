#pragma once
#include<math.h>
#include<stdio.h>

struct Parameters{

    long double epsilon=0;
    long double mu=0;
    long double v=0;
    long double lambda_1=0;
    long double lambda_2=0;

};

typedef struct Parameters Grid_Parameters;

long double Heaviside(const Grid_Parameters& Image,const long double x){


    return (0.5+atan(x/Image.epsilon)/M_PIl);

};

long double Dirac(const Grid_Parameters& Image,const long double x){

    return (Image.epsilon/(M_PIl*(Image.epsilon*Image.epsilon+x*x)));

};
