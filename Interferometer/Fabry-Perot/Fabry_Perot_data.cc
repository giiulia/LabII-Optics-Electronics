#include "Fabry_Perot_data.h"
#include "../clean_data.h"
#include <cmath>
#include <iostream>
#include <algorithm>

void diameter_into_theta(double* diametro, double* theta){
    
    double diameterMean[3];
    double radius[2];
    Med_Var_Dev(diametro, diameterMean, numberofMeasures);
    cout<<"Diametrer mean: "<<diameterMean[0]<<" +/- "<<diameterMean[2]<<endl;
    radius[0] = diameterMean[0]/2; //radius
    radius[1] = 0.1/2;
    cout<<"radius "<<radius[0]<<" +/- "<<radius[1]<<endl;


    theta[0] = atan(radius[0]/L);
    theta[1] = sqrt( pow(radius[1]/ ( L*(1 + pow(radius[0]/L, 2)) ), 2) + pow(radius[0]*errL/( (L*L)*(1 + pow(radius[0]/L, 2)) ), 2)  );
    cout<<"theta: "<<theta[0]<<" +/ - "<<theta[1]<<endl;

}
