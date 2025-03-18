#include<math.h>
#include<stdio.h>
#include "Parameters.hpp"

double Heaviside(const GridParameters& params,const double x)
{
    return (0.5+atan(x/params.epsilon)/M_PIl);
}

double Dirac(const GridParameters& params,const double x)
{
    return (params.epsilon/(M_PIl*(params.epsilon*params.epsilon+x*x)));
}