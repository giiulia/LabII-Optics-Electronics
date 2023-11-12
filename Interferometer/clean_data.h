#ifndef clean_data
#define clean_data

#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;
void NormalForm( int e[][3], double* u, int N ){ //vettore in entrata, vettore in uscita, dimensione del vettore di uscita
    double somma;
    for(int i = 0; i<N; i++){
        somma = e[i][0] + e[i][1]/60. + e[i][2]/3600.;
        u[i] = somma;
    }

}

void DegreeToRadiant( double* e, int N){
    double rad;
    for(int i = 0; i<N; i++){
        rad = e[i]*M_PI/180.;
        e[i] = rad;
    }  
}

void Med_Var_Dev(double* const campione, double* risultati, int N){
  double media, varianza, dev;
  media = 0;
  varianza = 0;
  dev = 0;
  
  for(int i = 0; i < N; i++){
    media = media + campione[i];
  }
  media = media/N;
  risultati[0] = media;
  for(int i = 0; i < N; i++){
    varianza = varianza + pow(campione[i]-media, 2.);
  }

  varianza = varianza/(N-1.);
  risultati[1] = varianza;
  dev = sqrt(varianza/N);

  risultati[2] = dev;
}
void Diff(int deltaC[][3], int deltaX[][3], ofstream& file_angoli, int size, int sizeR){
  double deltaCNormal[5];
  double mediaC[3];

  double deltaXNormal[5];
  double mediaX[3];

  NormalForm( deltaC, deltaCNormal, size);
  DegreeToRadiant( deltaCNormal, size );
  Med_Var_Dev(deltaCNormal, mediaC, size);

  NormalForm( deltaX, deltaXNormal, sizeR);
  DegreeToRadiant( deltaXNormal, sizeR );
  Med_Var_Dev(deltaXNormal, mediaX, sizeR);


  double sigma_delta=sqrt(mediaX[2]*mediaX[2] + mediaC[2]*mediaC[2]);

  file_angoli<<mediaX[0]-mediaC[0]<<"\t"<<sigma_delta<<endl;
  //cout<<"Media: "<<mediaX[0]-media0[0]<<"\tDeviazione sulla Media: "<<sigma_delta<<"\n"<<std::endl;
}

void DiffPunti(int deltaC[][3], int puntoX[][3], ofstream& file_punti, int size, int X){
  double deltaCNormal[5];
  double mediaC[3];
  
  double deltaXNormal[5];
  double mediaX[3];

  NormalForm( deltaC, deltaCNormal, size);
  DegreeToRadiant( deltaCNormal, size );
  Med_Var_Dev(deltaCNormal, mediaC, size);


  NormalForm( puntoX, deltaXNormal, size);
  DegreeToRadiant( deltaXNormal, size );
  Med_Var_Dev(deltaXNormal, mediaX, size); 

  double sigma_delta=sqrt(mediaX[2]*mediaX[2] + mediaC[2]*mediaC[2]);
  file_punti<<X<<"\t\t"<<mediaX[0]-mediaC[0]<<"\t"<<sigma_delta<<endl;
  //std::cout<<"Media: "<<mediaX[0]-media0[0]<<"\tDeviazione sulla Media: "<<sigma_delta<<"\n"<<std::endl;

}

#endif 
