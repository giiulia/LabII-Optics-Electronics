#include "virtual.h"
#include "../clean_data.h"
#include <cmath>
#include <iostream>

void getNGreen(double NGreen[][2]){
    double NMean[3];
    for(int i = 0; i<numeroPunti; i++){
        Med_Var_Dev(NGreenX[i], NMean, numberofMeasures);
        NGreen[i][0] = NMean[0];
        NGreen[i][1] = NMean[2];
        cout<<"NGreen[i]: "<<NGreen[i][0]<<" +/- "<<NGreen[i][1]<<endl;
    }

}

void getNYellow(double NYellow[][2]){
    double NMean[3];
    for(int i = 0; i<numeroPunti; i++){
        Med_Var_Dev(NYellowX[i], NMean, numberofMeasures);
        NYellow[i][0] = NMean[0];
        NYellow[i][1] = NMean[2];
        cout<<"NYellow[i]: "<<NYellow[i][0]<<" +/- "<<NYellow[i][1]<<endl;
    }

}

void getNBlu(double NBlue[][2]){
    double NMean[3];
    for(int i = 0; i<numeroPunti; i++){
        Med_Var_Dev(NBlueX[i], NMean, numberofMeasures);
        NBlue[i][0] = NMean[0];
        NBlue[i][1] = NMean[2];
        cout<<"NBlue[i]: "<<NBlue[i][0]<<" +/- "<<NBlue[i][1]<<endl;
    }

}