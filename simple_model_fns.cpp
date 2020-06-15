#include <iostream>
#include "simple_model.hpp"

const double Gh = 1;
const double Gdt = .2;

const double GM = 1;
const double GW = 1;
const double GT = 0.8;
const double Geps2 = 1;

double Gphi [XSIZE][YSIZE]; 

//Checks whether we're at the boundary and loops back to the other side if we are for periodic boundary
int checkbc(int i, int lambda){

    if (i > (lambda - 1)){
        return i-lambda;
    }
    else if (i < 0){
        return i+lambda;
    }
    else {
        return i;
    }
}

//Calculates derivative of f wrt phi
double dfdphi(int i, int j){
    double term1, term2;
    double p = Gphi[i][j];

    term1 = 30.0 * (1.0-GT) * p*p *((p*p)-2.0*p +1.0);
    term2= 2.0*GW*p*(2.0*(p*p)-3.0*p+1.0);

    return term1+term2;
}

//Calculates laplacian 
double laplac(int i, int j){
    double xderiv, yderiv;
    xderiv = (Gphi[checkbc(i+1,XSIZE)][j] - (2*Gphi[i][j]) + Gphi[checkbc(i-1,XSIZE)][j]);
    yderiv = (Gphi[i][checkbc(j+1,YSIZE)] - (2*Gphi[i][j]) + Gphi[i][checkbc(j-1,YSIZE)]);
    return (xderiv + yderiv)/(Gh*Gh);
}

