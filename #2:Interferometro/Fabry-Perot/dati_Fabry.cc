#include "dati_Fabry.h"
#include "../clean_data.h"
#include <cmath>
#include <iostream>
#include <algorithm>

void diam_into_theta(double* diametro, double* theta){
    
    double mediaDiametro[3];
    double raggio[2];
    Med_Var_Dev(diametro, mediaDiametro, numeroMisure);
    cout<<"media Diametro "<<mediaDiametro[0]<<" +/- "<<mediaDiametro[2]<<endl;
    raggio[0] = mediaDiametro[0]/2; //raggio
    raggio[1] = 0.1/2;
    cout<<"raggio "<<raggio[0]<<" +/- "<<raggio[1]<<endl;


    theta[0] = atan(raggio[0]/L);
    theta[1] = sqrt( pow(raggio[1]/ ( L*(1 + pow(raggio[0]/L, 2)) ), 2) + pow(raggio[0]*errL/( (L*L)*(1 + pow(raggio[0]/L, 2)) ), 2)  );
    cout<<"theta: "<<theta[0]<<" +/ - "<<theta[1]<<endl;

}
