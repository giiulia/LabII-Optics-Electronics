#ifndef dati_virtuale_h
#define dati_virtuale_h

//calibrazione
int numeroMisureN = 6;
double lambda = 0.632; //micrometri

double Deltad[] = {10., 9.46, 9.15, 10.41, 8.98, 10.5}; //partivo dall'8 sempre
int N[] = {32, 31, 30, 34, 29, 33};

//misure verde
int numeroPunti = 3;
const int numeroMisure = 4;
double DeltadVerde[] = {9.70, 10., 10.30};
//double NVerdeX[][numeroMisure] = {{43, 43, 44, 44}, {45, 45, 45, 46}, {46, 46, 47, 47}};
double NVerdeX[][numeroMisure] = {{42, 41, 42, 42}, {43, 44, 44, 45}, {45, 44, 45, 46}};

//misure blu
double DeltadBlu[] = {9.70, 10., 10.30};
double NBluX[][numeroMisure] = {{37, 37, 39, 37}, {38, 38, 40, 38}, {39, 40, 39, 41}};

//misure giallo
double DeltadGiallo[] = {9.70, 10., 10.30};
double NGialloX[][numeroMisure] = {{34, 33, 34, 34}, {36, 36, 35, 35}, {37, 37, 36, 36}};


#endif