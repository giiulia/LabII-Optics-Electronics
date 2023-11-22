#ifndef graticule_data_h
#define graticule_data_h


//####################
//constants
//####################

double lambda = 589.5924;


//####################
//measures day 1
//####################

int numberofMeasures = 3;

//a sinistra
int data_redLeft[][3] = {{272, 00, 00},{272, 30, 00}, {272, 15, 00}}; //m = 1 red -46 
void getRedLeft(double red[]);

int data_yellowLeft[][3] = {{274, 30, 00}, {274, 30, 00}, {274, 42, 00}}; // m = 1 -44 
void getYellowLeft(double yellow[]);

//int thetaGdx[][3] = {{276, 12},{276, 15}, {276, 13}}; //m = 2 -42 

//al center
int data_center[][3] = {{318, 01, 00},{318, 30, 00}, {318, 16, 00}}; //m = 0
void getYellow1(double yellow[]);
void getRed1(double red[]);

//a destra
int data_blue1[][3] = {{352, 3, 00},{352, 5, 00}, {352, 4, 00}}; //m=1
int data_green1[][3] = {{355, 39, 00}, {355, 40, 00}, {355, 38, 00}}; //m=1

// thetaGsx[][3] = {{2, 10},{2, 12}, {2, 8}}; //m = 2  -316
int data_yellowRight[][3] = {{4, 5, 00},{4, 19, 00}, {4, 6, 00}}; //m = 1 -314
void getYellowRight(double yellow[]);

int data_redRight[][3] = {{7, 3, 00}, {6, 9, 00}, {6, 8, 00}}; // m = 1 red -311
void getRedRight(double red[]);




//####################
// measures day 2
//####################

int numberofMeasures2 = 4;

//center
int data_center2[][3] = {{283, 00, 00}, {282, 58, 00}, {283, 2, 00}, {283, 00, 00}};

//a destra
int data_blue2[][3] = {{246, 44, 30},{245, 00, 00}, {246, 46, 00}, {246, 44, 30}}; //m=1
int data_green2[][3] = {{245, 25, 00}, {245, 22, 30}, {245, 21, 30}, {245, 21, 30}}; //m=1

int data_yellow2[][3] = {{239, 00, 00}, {238, 46, 30}, {238, 41, 00}, {238, 42, 00}}; //589.5924 nm
void getYellow2(double yellow[]);

int data_red2[][3] = {{237, 26, 00},{236, 20, 00}, {236, 20, 30}, {236, 1, 00}, {236, 20, 30}}; //616.0747nm
void getRed2(double red[]);

#endif