#include "stats.h"

#include <cmath>
#include <iostream>

void mean_stdm(double * v_in, double * v_out, int size){
    double sum = 0;
    double var;
    double sum_sq = 0;
    for(int i = 0 ; i<size; i++){
        sum += v_in[i];
        sum_sq += pow(v_in[i], 2);
    }
    v_out[0] = sum / static_cast<float>(size);
    var = (sum_sq/static_cast<float>(size) - pow(sum/static_cast<float>(size), 2))*(static_cast<float>(size) / static_cast<float>(size - 1));
    v_out[1] = sqrt(var/static_cast<float>(size));

}