#ifndef dati_Fabry_h
#define dati_Fabry_h

double lambda = 0.6328; //micrometri

//calibrazione
int numeroMisureN = 3;

double Deltad[] = {6, 7, 6};
int N[] = {21, 22, 21};


//indice di rifrazione aria
int numeroP = 3;
const int numeroMisureN2 = 4;
double l = 3*pow(10, 4); //larghezza della cella in micrometri (3cm)
double Patm = 101325.0*pow(10, -3); //in kPa

double DeltaNP[][numeroMisureN2] = {{7, 6, 7, 7}, {10, 9,  9, 8}, {15, 15, 15, 16}}; //uno per ogni tentativo, la 10 era 9 
void getDeltaN(double* DeltaN[]);

double Pf[] = {30, 40, 70}; //pressione finale di ogni tentativo (Pi = 0) KPa

//indice di rifrazione vetro
int numeroMisureNVetro = 5;
double t = 6*pow(10, 3); //larghezza piastra di vetro in micrometri

double thetai[] = {0, 0, 0,  0, 0};
double thetaf[] = {2.6, 2.8, 2.7, 2.6, 3.2}; //dovevano essere almeno 10
int NVetro = 10;

double thetaf10 = 10.; //dovevano essere almeno 10
double NVetro10[] = {31., 33., 30., 32., 30.};

#endif