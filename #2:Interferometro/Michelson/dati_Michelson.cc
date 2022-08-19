#include "dati_Michelson.h"
#include "../clean_data.h"
#include <cmath>
#include <iostream>
#include <algorithm>

void getDeltaN(double DeltaN[][2]){
    
    double media[numeroP][3];

    for(int i = 0; i<numeroP; i++){
        Med_Var_Dev(DeltaNP[i], media[i], numeroMisureN2);

        DeltaN[i][0] = media[i][0];
        DeltaN[i][1] = media[i][1];

    }
}