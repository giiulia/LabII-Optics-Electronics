#include "Michelson_data.h"
#include "../clean_data.h"
#include <cmath>
#include <iostream>
#include <algorithm>

void getDeltaN(double DeltaN[][2]){
    
    double mean[numberP][3];

    for(int i = 0; i<numberP; i++){
        Med_Var_Dev(DeltaNP[i], mean[i], numberMeasuresN2);

        DeltaN[i][0] = mean[i][0];
        DeltaN[i][1] = mean[i][1];

    }
}