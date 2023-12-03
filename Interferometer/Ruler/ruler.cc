#include "ruler.h"
#include "../clean_data.h"
#include <cmath>
#include <iostream>


void getHeights(double heights[][2]){
    double meanHeight[3];
    for(int i = 0; i<numberofHeights; i++){
        Med_Var_Dev(heightN[i], meanHeight, numberofMeasures);
        heights[i][0] = meanHeight[0];
        heights[i][1] = meanHeight[2];
        cout<<"heights[i]: "<<heights[i][0]<<" +/- "<<heights[i][1]<<endl;
        heights[i][1] = 0.1;
    }
}


void getTheta(double thetaN[][2], double heights[][2] ){
    double meanDiameter[3];
    Med_Var_Dev(diameter, meanDiameter, numberofMeasures);
    double radius[] = {meanDiameter[0]/2, meanDiameter[2]/2};
    cout<<"diameter: "<<meanDiameter[0]<<" +/- "<<meanDiameter[2]<<endl;
    cout<<"radius: "<<radius[0]<<" +/- "<<radius[1]<<endl;
    radius[1] = 0.1; 
    double height, errHeights;
    for (int i= 0; i<numberofHeights; i++){

        height = radius[0] + heights[i][0]; 
        errHeights = sqrt( pow(heights[i][1], 2) + pow(radius[1], 2) );
        cout<<"height + radius: "<<height<<" +/- "<<errHeights<<endl;
        thetaN[i][0] = atan(height/wall_distance);
        thetaN[i][1] = sqrt(  pow( (height*0.1/(wall_distance*wall_distance))/(1+pow(height/wall_distance, 2)), 2 )+  pow( (errHeights/wall_distance)/(1+pow(height/wall_distance, 2)), 2)  );
        cout<<"thetaN[i]: "<<thetaN[i][0]<<" +/- "<<thetaN[i][1]<<endl;

    }

}

