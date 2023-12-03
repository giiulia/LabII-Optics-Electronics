#ifndef virtual_h
#define virtual_h

//calibration
int numberofMeasures = 6;
double lambda = 0.632; 

double Deltad[] = {10., 9.46, 9.15, 10.41, 8.98, 10.5}; 
int N[] = {32, 31, 30, 34, 29, 33};

//measures green
int numberofPoints = 3;
const int numberofMeasures = 4;
double DeltadGreen[] = {9.70, 10., 10.30};
double NGreenX[][numberofMeasures] = {{42, 41, 42, 42}, {43, 44, 44, 45}, {45, 44, 45, 46}};

//measures blue
double DeltadBlue[] = {9.70, 10., 10.30};
double NBlueX[][numberofMeasures] = {{37, 37, 39, 37}, {38, 38, 40, 38}, {39, 40, 39, 41}};

//measures yellow
double DeltadYellow[] = {9.70, 10., 10.30};
double NYellowX[][numberofMeasures] = {{34, 33, 34, 34}, {36, 36, 35, 35}, {37, 37, 36, 36}};


#endif