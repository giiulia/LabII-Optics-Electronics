#ifndef clean_data
#define clean_data

#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;
void NormalForm( int e[][3], double* u, int N ){ //vettore in entrata, vettore in uscita, dimensione del vettore di uscita
    double sum;
    for(int i = 0; i<N; i++){
        sum = e[i][0] + e[i][1]/60. + e[i][2]/3600.;
        u[i] = sum;
    }

}

void DegreeToRadiant( double* e, int N){
    double rad;
    for(int i = 0; i<N; i++){
        rad = e[i]*M_PI/180.;
        e[i] = rad;
    }  
}

void Mean_Var_Dev(double* const sample, double* results, int N){
  double mean, variance, dev;
  mean = 0;
  variance = 0;
  dev = 0;
  
  for(int i = 0; i < N; i++){
    mean = mean + sample[i];
  }
  mean = mean/N;
  results[0] = mean;
  for(int i = 0; i < N; i++){
    variance = variance + pow(sample[i]-mean, 2.);
  }

  variance = variance/(N-1.);
  results[1] = variance;
  dev = sqrt(variance/N);

  results[2] = dev;
}
void Diff(int deltaC[][3], int deltaX[][3], ofstream& angles_file, int size, int sizeR){
  double deltaCNormal[5];
  double meanC[3];

  double deltaXNormal[5];
  double meanX[3];

  NormalForm( deltaC, deltaCNormal, size);
  DegreeToRadiant( deltaCNormal, size );
  Mean_Var_Dev(deltaCNormal, meanC, size);

  NormalForm( deltaX, deltaXNormal, sizeR);
  DegreeToRadiant( deltaXNormal, sizeR );
  Mean_Var_Dev(deltaXNormal, meanX, sizeR);


  double sigma_delta=sqrt(meanX[2]*meanX[2] + meanC[2]*meanC[2]);

  angles_file<<meanX[0]-meanC[0]<<"\t"<<sigma_delta<<endl;
  //cout<<"Mean: "<<meanX[0]-mean0[0]<<"\t Deviation on Mean: "<<sigma_delta<<"\n"<<std::endl;
}

void DiffPoints(int deltaC[][3], int pointX[][3], ofstream& file_points, int size, int X){
  double deltaCNormal[5];
  double meanC[3];
  
  double deltaXNormal[5];
  double meanX[3];

  NormalForm( deltaC, deltaCNormal, size);
  DegreeToRadiant( deltaCNormal, size );
  Mean_Var_Dev(deltaCNormal, meanC, size);


  NormalForm( pointX, deltaXNormal, size);
  DegreeToRadiant( deltaXNormal, size );
  Mean_Var_Dev(deltaXNormal, meanX, size); 

  double sigma_delta=sqrt(meanX[2]*meanX[2] + meanC[2]*meanC[2]);
  file_points<<X<<"\t\t"<<meanX[0]-meanC[0]<<"\t"<<sigma_delta<<endl;
  //std::cout<<"Mean: "<<meanX[0]-mean0[0]<<"\t deviation on Mean: "<<sigma_delta<<"\n"<<std::endl;

}

#endif 
