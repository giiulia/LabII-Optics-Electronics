#include "righello.h"
#include "../clean_data.h"
#include <cmath>
#include <iostream>


void getAltezze(double altezze[][2]){
    double altMedia[3];
    for(int i = 0; i<numeroAltezze; i++){
        Med_Var_Dev(altezzaN[i], altMedia, numeroMisure);
        altezze[i][0] = altMedia[0];
        altezze[i][1] = altMedia[2];
        cout<<"altezze[i]: "<<altezze[i][0]<<" +/- "<<altezze[i][1]<<endl;
        altezze[i][1] = 0.1;//cm cambio perche l'incertezza era troppo bassa
    }
}


void getTheta(double thetaN[][2], double altezze[][2] ){
    double diamMedia[3];
    Med_Var_Dev(diametro, diamMedia, numeroMisure);
    double raggio[] = {diamMedia[0]/2, diamMedia[2]/2};
    cout<<"diametro: "<<diamMedia[0]<<" +/- "<<diamMedia[2]<<endl;
    cout<<"raggio: "<<raggio[0]<<" +/- "<<raggio[1]<<endl;
    raggio[1] = 0.1; //cm cambio perche l'incertezza era troppo bassa
    double altezza, errAltezza;
    for (int i= 0; i<numeroAltezze; i++){

        altezza = raggio[0] + altezze[i][0]; 
        errAltezza = sqrt( pow(altezze[i][1], 2) + pow(raggio[1], 2) );
        cout<<"altezza + raggio: "<<altezza<<" +/- "<<errAltezza<<endl;
        thetaN[i][0] = atan(altezza/distanza_muro);
        thetaN[i][1] = sqrt(  pow( (altezza*0.1/(distanza_muro*distanza_muro))/(1+pow(altezza/distanza_muro, 2)), 2 )+  pow( (errAltezza/distanza_muro)/(1+pow(altezza/distanza_muro, 2)), 2)  );
        cout<<"thetaN[i]: "<<thetaN[i][0]<<" +/- "<<thetaN[i][1]<<endl;

    }

}

