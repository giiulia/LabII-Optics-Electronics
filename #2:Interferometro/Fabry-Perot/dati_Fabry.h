#ifndef dati_Fabry_h
#define dati_Fabry_h

int numeroMisure = 5;
int numeroFrange = 5;
double lambda = 0.6328; //micrometri
double L = 173.9 - 0.003 - 0.018; //cm dalla base delle lente-3mm = - 0.003cm
double errL = 0.1;
//verifica
void diam_into_theta(double* diametro, double* theta);
int k[] = {5, 4, 3, 2, 1};
double diametro1[] = {2.8, 2.3, 2.4, 2.6, 2.5 }; // cm cerchio interno: k = 5
double diametro2[] = {4.7, 4.4, 4.3, 4.6, 4.5}; // k = 4
double diametro3[] = {6.0, 5.9, 5.7, 5.8, 5.8}; // k = 3
double diametro4[] = {7.0, 6.9, 6.9, 6.9, 6.9}; // k = 2
double diametro5[] = {7.9, 7.8, 7.9, 7.8, 7.8}; // k = 1

//calibrazione
int numeroMisureN = 8;
double Deltad[] = {7, 7, 8, 9, 10, 10, 8, 9}; //partivo dal 3 sempre
int N[] = {21, 22, 25, 28, 29, 30, 24, 26};


#endif