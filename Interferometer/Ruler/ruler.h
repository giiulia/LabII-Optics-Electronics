#ifndef ruler_h
#define ruler_h

double lambda = 0.6328*pow(10, -4); //cm

const int numberofMeasures = 5;
int numberofHeights = 8;
double source_height = 3.8;
double table_distance = 72.5;
double wall_distance = 120+7;
double diametro[] = {7.8, 7.7, 7.7, 7.8, 7.8};//cm
double heightN[][numberofMeasures] = {{0., 0., 0., 0., 0.},{2.5, 2.5, 2.5, 2.4, 2.5}, {4.2, 4.1, 4.1, 4.0, 4.1}, {5.5, 5.5, 5.4, 5.4, 5.5}, {6.6, 6.6, 6.5, 6.5, 6.5}, {7.5, 7.6, 7.5, 7.4, 7.5}, {8.5, 8.5, 8.4, 8.4, 8.5}, {9.3, 9.8, 9.3, 9.2, 9.3}};

#endif