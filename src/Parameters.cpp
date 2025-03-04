#include<math.h>
#include<stdio.h>
#include "Parameters.hpp"

double Heaviside(const GridParameters& Image,const double x){


    return (0.5+atan(x/Image.epsilon)/M_PIl);

};

double Dirac(const GridParameters& Image,const double x){

    return (Image.epsilon/(M_PIl*(Image.epsilon*Image.epsilon+x*x)));

};
