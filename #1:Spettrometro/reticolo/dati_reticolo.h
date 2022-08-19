#ifndef dati_reticolo_h
#define dati_reticolo_h


//####################
//costanti
//####################

double lambda = 589.5924;


//####################
//misurazioni giorno 1
//####################

int numeroMisure = 3;

//a sinistra
int dati_rossoSx[][3] = {{272, 00, 00},{272, 30, 00}, {272, 15, 00}}; //m = 1 rosso -46 
void getRossoSx(double rosso[]);

int dati_gialloSx[][3] = {{274, 30, 00}, {274, 30, 00}, {274, 42, 00}}; // m = 1 -44 
void getGialloSx(double giallo[]);

//int thetaGdx[][3] = {{276, 12},{276, 15}, {276, 13}}; //m = 2 -42 

//al centro
int dati_centro[][3] = {{318, 01, 00},{318, 30, 00}, {318, 16, 00}}; //m = 0
void getGiallo1(double giallo[]);
void getRosso1(double rosso[]);

//a destra
int dati_blu1[][3] = {{352, 3, 00},{352, 5, 00}, {352, 4, 00}}; //m=1
int dati_verde1[][3] = {{355, 39, 00}, {355, 40, 00}, {355, 38, 00}}; //m=1

// thetaGsx[][3] = {{2, 10},{2, 12}, {2, 8}}; //m = 2  -316
int dati_gialloDx[][3] = {{4, 5, 00},{4, 19, 00}, {4, 6, 00}}; //m = 1 -314
void getGialloDx(double giallo[]);

int dati_rossoDx[][3] = {{7, 3, 00}, {6, 9, 00}, {6, 8, 00}}; // m = 1 rosso -311
void getRossoDx(double rosso[]);




//####################
// miurazioni giorno 2
//####################

int numeroMisure2 = 4;

//centro
int dati_centro2[][3] = {{283, 00, 00}, {282, 58, 00}, {283, 2, 00}, {283, 00, 00}};

//a destra
int dati_blu2[][3] = {{246, 44, 30},{245, 00, 00}, {246, 46, 00}, {246, 44, 30}}; //m=1
int dati_verde2[][3] = {{245, 25, 00}, {245, 22, 30}, {245, 21, 30}, {245, 21, 30}}; //m=1

int dati_giallo2[][3] = {{239, 00, 00}, {238, 46, 30}, {238, 41, 00}, {238, 42, 00}}; //589.5924 nm
void getGiallo2(double giallo[]);

int dati_rosso2[][3] = {{237, 26, 00},{236, 20, 00}, {236, 20, 30}, {236, 1, 00}, {236, 20, 30}}; //616.0747nm
void getRosso2(double rosso[]);

#endif