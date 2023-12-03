#ifndef Fabry_Perot_data_h
#define Fabry_Perot_data_h

int numberofMeasures = 5;
int numberofFringes = 5;
double lambda = 0.6328; //micrometers
double L = 173.9 - 0.003 - 0.018; //cm from the base of the lens: -3mm = - 0.003cm
double errL = 0.1;

//check

void diameter_into_theta(double* diameter, double* theta);
int k[] = {5, 4, 3, 2, 1};
double diameter1[] = {2.8, 2.3, 2.4, 2.6, 2.5 }; // cm intern circle: k = 5
double diameter2[] = {4.7, 4.4, 4.3, 4.6, 4.5}; // k = 4
double diameter3[] = {6.0, 5.9, 5.7, 5.8, 5.8}; // k = 3
double diameter4[] = {7.0, 6.9, 6.9, 6.9, 6.9}; // k = 2
double diameter5[] = {7.9, 7.8, 7.9, 7.8, 7.8}; // k = 1

//calibration
int numberofMeasuresN = 8;
double Deltad[] = {7, 7, 8, 9, 10, 10, 8, 9}; 
int N[] = {21, 22, 25, 28, 29, 30, 24, 26};


#endif