#pragma once
#include<math.h>
#include<stdio.h>

const float eps = 0.00001;

struct GridParameters
{
<<<<<<< Updated upstream
    double epsilon=0;
    double mu=0;
    double v=0;
    double lambda_1=0;
    double lambda_2=0;
    double tolerance=0.1;
=======
    double epsilon=0.2;

    // Larger values of mu will detect less noise
    double mu=0.1;
    double v=0;

    double lambda_1=1.5;
    double lambda_2=1.5;

    // Minimum loss function value allowed for an image to be considered solution
    double tolerance=0.01;

    double delta_t = 0.02;

    // 
    double eta = 0.1;
>>>>>>> Stashed changes
};


double Heaviside(const GridParameters& Image,const double x){


    return (0.5+atan(x/Image.epsilon)/M_PIl);

};

double Dirac(const GridParameters& Image,const double x){

    return (Image.epsilon/(M_PIl*(Image.epsilon*Image.epsilon+x*x)));

};
