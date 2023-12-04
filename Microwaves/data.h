#ifndef data_h
#define data_h

/*receiver sensitivity should be adjusted at the beginning of each measurement by appropriately 
choosing the amplification and adjusting the offset so that it is as close as possible to 
the center of the measurement scale.
*/


//stationary waves (same orientation, 30x)
double position_reproducibility = 30.;
double riproducibilita[] = {0.9, 0.9, 0.9};

double position[] = {25, 25.5, 26, 26.5, 27, 27.5, 28, 28.5, 29, 29.5, 30, 30.5, 31, 31.5, 32, 32.5, 33, 33.5, 34,  34.5, 35, 35.5, 36, 36.5, 37, 37.5, 38, 38.5, 39, 39.5, 40, 40.5, 41, 41.5, 42, 42.5, 43, 43.5, 44, 44.5, 45, 45.25, 45.5, 45.75, 46, 46.25, 46.5, 46.75, 47, 47.25, 47.50, 47.75, 48, 48.25, 48.5, 48.75, 49, 49.25, 49.5, 49.75, 50 };//devo partire dalla lettura di 1.0
double intensity[] = {0.90, 1.06, 0.86, 0.90, 1.04, 1.04, 0.90, 1.02, 0.84, 0.84 , 0.90, 0.94,  0.82, 0.88, 0.9, 0.8, 0.88, 0.84, 0.78, 0.86 , 0.80 , 0.78, 0.84, 0.78, 0.76, 0.82, 0.74, 0.78, 0.80, 0.72, 0.76, 0.76, 0.68, 0.74, 0.74, 0.66, 0.72, 0.70, 0.64, 0.70, 0.66, 0.64, 0.64,  0.66, 0.70, 0.70, 0.66, 0.64, 0.64, 0.68, 0.70, 0.68, 0.64, 0.62, 0.62, 0.66, 0.68, 0.66, 0.62, 0.60, 0.62 };//*30 traballava
void amplification(double* intensity, int amplify);
//ATTENTION we changed the offset in the first measures(until position= 30 excluded) because the reading went out of the range therefore the measures read were -0.08

/*
In all subsequent measures to this we will consider that the effect of the stationary wave persists.
(will always keep the same distance)
*/

//reflection on squared metal foil (same orientation)
//this time we used 10x because with the 30x the maximum was uncertain

int number_of_incident_angles = 5;
int number_of_reflected_theta = 3;
double theta_inc[] = {70., 60., 50., 40., 35.};//for certain angles of incidence I will have two, one direct and one reflected
double theta_rifl[][3] = {{67., 68., 68.}, {54., 53., 56. }, {49., 49., 50. }, {41., 40., 41.}, {33., 33., 32.}};
double transmitted_theta_50[] = {85, 84, 85}; //50 stands for the angle of incidence at which we found the second maximum
double transmitted_theta_40[] = {79, 79, 80};

double intensity_reflected_wave_metal[][3] = {{0.64, 0.64, 0.64}, {0.74, 0.72, 0.74}, {0.84, 0.82, 0.82}, {0.66, 0.68, 0.67}, {0.62, 0.64, 0.62}};
double transmitted_wave_intensity_50 = 0.2;
double transmitted_wave_intensity_40 = 0.08;

//refraction polystyrene void (check that the refractive index of polystyrene is 1)
double vertex_angle[2] = {22, 1}; //1 = goniometer sensibility
double max_refracted_theta_void = 2;

//refraction polystyrene filled with styrene pellets
double max_theta_rifratto_styrene[] = {13., 14.};
double refracted_wave_intensity[] = {0.58, 0.56};//*30
double reflected_wave_intensity = 0.22;//*30

//polarization
double emitter_receiver_distances[] = {50, 70, 90};

double polarizer_angle1[] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 85, 90, 95, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200}; 
double intensity_polarized_wave_dist1[] = {0.58, 0.54, 0.50, 0.46, 0.38, 0.28, 0.18, 0.10, 0.02, 0.007, 0.0, 0.005, 0.03, 0.1, 0.2, 0.28, 0.38, 0.46, 0.52, 0.56, 0.58, 0.56, 0.54};//*30
//polarization with horizontal grid and horizontal cones
double intensity_complete_50 = 0.56;//*30 passes only the 97%

double polarizer_angle2[] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 85, 90, 95, 100, 110, 120, 130, 140, 150, 160, 170,180}; 
double intensity_polarized_wave_dist2[] = {0.94, 0.92, 0.86, 0.80, 0.68, 0.52, 0.38, 0.22, 0.06, 0.02, 0., 0.002, 0.04, 0.20, 0.40, 0.52, 0.68, 0.78, 0.86, 0.92, 0.94 };//*10;
//polarization with horizontal grid and horizontal cones

double polarizer_angle3[] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 85, 90, 95, 100, 110, 120, 130, 140, 150, 160, 170, 180}; 
double intensity_polarized_wave_dist3[] = {0.76, 0.74, 0.70, 0.62, 0.54, 0.42, 0.30, 0.16, 0.04, 0.02,  0., 0.002, 0.02, 0.14, 0.28, 0.40, 0.50, 0.60, 0.68, 0.72, 0.74};//*10
//polarizzazione con griglia orizzontale e coni orizzontali
double intensity_complete_90 = 0.18;//*30 passes only the 70%

//polarization with the grid (equal orientation with the wide side horizontal) measurements taken at 90cm
double angolo_griglia[] = {0, 45, 90}; //angoles respect to the orizontal line
double intensity_polarized_wave_grid[] = {0.18 , 0.12 , 0.02 };//*30 orizontal, slanted, vertical 

//polarization with grid + Receiver rotated 90 to the Transmitter
double angolo_griglia2[] = {0, 45, 90};
double intensity_polarized_wave_grid2[] = { 0. , 0.14 , 0.};//*30 -90 angle of wich i rotated the receiver

//Brewster angle with Polyethylene sheet, equal polarization: start with horizontal, than 90 degrees(long side on vertical)
int number_of_incident_angles_Brewster = 9;
double incident_angle_Brewster[] = {25, 28, 30, 35, 40, 50, 52, 55,  60, };
double intensity_reflected_wave_40[] = {0.02, 0., 0.02,  0.04, 0.08, 0.11, 0., 0.08, 0.36 }; //*10 misuro prima questa

//find Brewster only with the horizontal one(0)

//double slit: dsin(theta) = n lambda
int number_of_maximums_slit = 2;
int number_of_measures_slit = 2;
double order_of_maximum_double_slit[] = {1, 2};
double maximum_angle_double_slit[] = {22, 48}; //measured between receiver and optical axis *30 we had taken two for each but they were all the same
double intensity_double_slit[] = {0.46, 0.52, 0.32, 0.18}; //the first is of order 0, not shown above
double d = 7.5; 

//Bragg
double distance_balls = 3; //in cm

/*
double intensity[] = {0.42, 0.52, 0.68, 0.72, 0.68, 0.56, 0.40, 0.42, 0.36 0.42, 0.68, 0.76, 0.72, 0.58, 0.48  }//*10
double angolo_bragg[] = {0, 10, 15, 20, 25, 30, 40, 50, 55, 60, 70, 75, 80, 85, 90} //-90
*/
int number_of_measures_Bragg = 7;
double reflected_wave_intensity_Bragg[] = {0.02, 0.12, 0.12, 0.18, 0.18, 0.12, 0.02};//*10
double incident_angle_Bragg[] = {60, 55, 53, 50, 48, 45, 40};



#endif