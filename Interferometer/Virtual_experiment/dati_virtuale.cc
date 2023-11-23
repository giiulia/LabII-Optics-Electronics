#include "dati_virtuale.h"
#include "../clean_data.h"
#include <cmath>
#include <iostream>

void getNVerde(double NVerde[][2]){
    double NMedia[3];
    for(int i = 0; i<numeroPunti; i++){
        Med_Var_Dev(NVerdeX[i], NMedia, numeroMisure);
        NVerde[i][0] = NMedia[0];
        NVerde[i][1] = NMedia[2];
        cout<<"NVerde[i]: "<<NVerde[i][0]<<" +/- "<<NVerde[i][1]<<endl;
    }

}

void getNGiallo(double NGiallo[][2]){
    double NMedia[3];
    for(int i = 0; i<numeroPunti; i++){
        Med_Var_Dev(NGialloX[i], NMedia, numeroMisure);
        NGiallo[i][0] = NMedia[0];
        NGiallo[i][1] = NMedia[2];
        cout<<"NGiallo[i]: "<<NGiallo[i][0]<<" +/- "<<NGiallo[i][1]<<endl;
    }

}

void getNBlu(double NBlu[][2]){
    double NMedia[3];
    for(int i = 0; i<numeroPunti; i++){
        Med_Var_Dev(NBluX[i], NMedia, numeroMisure);
        NBlu[i][0] = NMedia[0];
        NBlu[i][1] = NMedia[2];
        cout<<"NBlu[i]: "<<NBlu[i][0]<<" +/- "<<NBlu[i][1]<<endl;
    }

}