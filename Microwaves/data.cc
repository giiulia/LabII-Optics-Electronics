#include "data.h"
#include "clean_data.h"
#include <cmath>
#include <iostream>

using namespace std;
void amplification(double* intensity, int amplify, int dimension){

    for(int i = 0; i<dimension; i++){
        intensity[i] = intensity[i]*amplify;
    }

}

double mean(double * v, int size){
    double sum = 0;
    for(int i = 0; i<size; i++){
        sum += + v[i];
    }
    return sum/static_cast<float>(size);
}

double st_deviation(double * v, int size){
    double sum_sq = 0;
    for(int i = 0; i<size; i++){
        sum_sq += + pow(v[i] - mean(v, size), 2);
    }
    return sqrt(sum_sq/(static_cast<float>(size)-1))/sqrt(size);
}