//c++ -o graticule graticule.cpp
#include <iostream>
#include <fstream> 
#include <cmath>
#include "graticule_data.cc"

using namespace std;
int main(int argc, char* argv[]){

//finding the pitch
    double yellow1[2];
    double yellow2[2];
    double pitch1[2];
    double pitch2[2];
    double meanPitch[2];


    getYellow1(yellow1);    
    getYellow2(yellow2);

    pitch1[0] = lambda*1/sin(yellow1[0]);
    pitch1[1] = yellow1[1]*lambda*cos(yellow1[0])/pow(sin(yellow1[0]), 2);
    cout<<"pitch1 "<<pitch1[0]<< " "<<pitch1[1]<<endl;

    pitch2[0] = lambda*1/sin(yellow2[0]);
    pitch2[1] = yellow2[1]*lambda*cos(yellow2[0])/pow(sin(yellow2[0]), 2);
    cout<<"pitch2 not corrected"<<pitch2[0]<<" "<<pitch2[1]<<endl;

    double sum_deviations = (pow(1/pitch1[1], 2) + pow(1/pitch2[1], 2));
    meanPitch[0] = (pitch1[0]/pow(pitch1[1], 2) + pitch2[0]/pow(pitch2[1], 2)) / sum_deviations;
    meanPitch[1] = 1/sqrt( sum_deviations );
    cout<<"pitch: "<<meanPitch[0]<<" "<<meanPitch[1]<<endl;

//correcting the pitch
    double alpha[2];
    double beta_minus = (239-283)*M_PI/180;
    double beta_plus = (328-283)*M_PI/180;
    double sigma_beta_minus = 0.0002;
    double sigma_beta_plus = 0.0002;

    alpha[0] = atan((sin(beta_minus)+sin(beta_plus))/(2-cos(beta_minus)-cos(beta_plus)));
    double derivative_beta_minus = (cos(beta_minus) - sin(beta_minus))/pow(2-cos(beta_minus)-cos(beta_plus), 2);
    double derivative_beta_plus = (cos(beta_plus) - sin(beta_plus))/pow(2-cos(beta_minus)-cos(beta_plus), 2);

    cout<<"beta_minus: "<<beta_minus<<endl;
    cout<<"sigma_beta_minus: "<<sigma_beta_minus<<endl;
    cout<<"beta_plus: "<<beta_plus<<endl;
    cout<<"sigma_beta_plus: "<<sigma_beta_plus<<endl;
    alpha[1] = (1/(1 + pow((sin(beta_minus)+sin(beta_plus))/(2-cos(beta_minus)-cos(beta_plus)), 2)) ) * sqrt(pow(derivative_beta_minus*sigma_beta_minus, 2) + pow(derivative_beta_plus*sigma_beta_plus, 2));
    cout<<"alpha: "<<alpha[0]<<"  +/-  "<<alpha[1]<<endl; 
    double pitch2Corrected[2];
    double meanPitchCorrected[2];

    cout<<"yellow2[0]: "<<yellow2[0]<<endl;
    double theta[2];
    theta[0] = yellow2[0]-alpha[0];
    cout<<"theta[0]: "<<theta[0]<<endl;
    theta[1] = sqrt(alpha[1]*alpha[1] + yellow2[1]*yellow2[1]);
    cout<<"sigma theta: "<<theta[1]<<endl;
    pitch2Corrected[0] = lambda*1/( sin(theta[0]) + sin(alpha[0]) );
    pitch2Corrected[1] = sqrt( pow(  theta[1]*lambda*cos(theta[0])/pow(sin(theta[0]+sin(alpha[0])), 2) , 2 ) + pow(  alpha[1]*lambda*cos(alpha[0])/pow(sin(theta[0]+sin(alpha[0])), 2) , 2  )   );
    cout<<"pitch2 corrected "<<pitch2Corrected[0]<<" "<<pitch2Corrected[1]<<endl;


    sum_deviations = (pow(1/pitch1[1], 2) + pow(1/pitch2Corrected[1], 2));
    meanPitchCorrected[0] = (pitch1[0]/pow(pitch1[1], 2) + pitch2Corrected[0]/pow(pitch2Corrected[1], 2)) / sum_deviations;
    meanPitchCorrected[1] = 1/sqrt( sum_deviations );
    cout<<"pitch corrected: "<<meanPitchCorrected[0]<<" "<<meanPitchCorrected[1]<<endl;

//finding the red
    double rosso1[2];
    double rosso2[2];
    double meanRed[2];
    double lambdaRed[2];

    getRed1(rosso1);    
    getRed2(rosso2);

    sum_deviations = (pow(1/rosso1[1], 2) + pow(1/rosso2[1], 2));
    meanRed[0] = (rosso1[0]/pow(rosso1[1], 2) + rosso2[0]/pow(rosso2[1], 2)) / sum_deviations;
    meanRed[1] = 1/sqrt( sum_deviations );
    cout<<"meanRed: "<<meanRed[0]<<" "<<meanRed[1]<<endl;

    lambdaRed[0] = meanPitchCorrected[0]*sin(meanRed[0])/1;
    lambdaRed[1] = sqrt( pow( sin(meanRed[0])*meanPitchCorrected[1] , 2) + pow( meanPitchCorrected[0]*cos(meanRed[0])*meanRed[1] , 2) );
    cout<<"lambdaRed: "<<lambdaRed[0]<<" "<<lambdaRed[1]<<endl;

//finding the blue
    double blue1[2];
    double blue2[2];
    double meanBlue[2];
    double lambdaBlue[2];

    getBlue1(blue1);    
    getBlue2(blue2);

    sum_deviations = (pow(1/blue1[1], 2) + pow(1/blue2[1], 2));
    meanBlue[0] = (blue1[0]/pow(blue1[1], 2) + blue2[0]/pow(blue2[1], 2)) / sum_deviations;
    meanBlue[1] = 1/sqrt( sum_deviations );
    cout<<"meanBlue: "<<meanBlue[0]<<" "<<meanBlue[1]<<endl;

    lambdaBlue[0] = meanPitchCorrected[0]*sin(meanBlue[0])/1;
    lambdaBlue[1] = sqrt( pow( sin(meanBlue[0])*meanPitchCorrected[1] , 2) + pow( meanPitchCorrected[0]*cos(meanBlue[0])*meanBlue[1] , 2) );
    cout<<"lambdaBlue: "<<lambdaBlue[0]<<" "<<lambdaBlue[1]<<endl;

//finding the green
    double green1[2];
    double green2[2];
    double meanGreen[2];
    double lambdaGreen[2];

    getGreen1(green1);    
    getGreen2(green2);

    sum_deviations = (pow(1/green1[1], 2) + pow(1/green2[1], 2));
    meanGreen[0] = (green1[0]/pow(green1[1], 2) + green2[0]/pow(green2[1], 2)) / sum_deviations;
    meanGreen[1] = 1/sqrt( sum_deviations );
    cout<<"meanGreen: "<<meanGreen[0]<<" "<<meanGreen[1]<<endl;

    lambdaGreen[0] = meanPitchCorrected[0]*sin(meanGreen[0])/1;
    lambdaGreen[1] = sqrt( pow( sin(meanGreen[0])*meanPitchCorrected[1] , 2) + pow( meanPitchCorrected[0]*cos(meanGreen[0])*meanGreen[1], 2) );
    cout<<"lambdaGreen: "<<lambdaGreen[0]<<" "<<lambdaGreen[1]<<endl;

    return 0;
    
}

/*

//finding the green
    double green1[2];
    double green2[2];
    double lambdaGreen1[2];
    double lambdaGreen2[2];
    double meanlambdaGreen[2];

    getGreen1(green1);    
    getGreen2(green2);

    lambdaGreen1[0] = meanPitchCorrected[0]*sin(green1[0])/1;
    lambdaGreen1[1] = sqrt( pow( sin(green1[0])*meanPitchCorrected[1] , 2) + pow( meanPitchCorrected[0]*cos(green1[0])*green1[1], 2) );
    cout<<"lambdaGreen: "<<lambdaGreen1[0]<<" "<<lambdaGreen1[1]<<endl;

    lambdaGreen2[0] = meanPitchCorrected[0]*(sin(green2[0])+sin(alpha[0]))/1;
    lambdaGreen2[1] = sqrt( pow( sin(green2[0])*meanPitchCorrected[1] , 2) + pow( meanPitchCorrected[0]*cos(green2[0])*green2[1], 2) + pow( meanPitchCorrected[0]*cos(alpha[0])*alpha[1], 2) );
    cout<<"lambdaGreen: "<<lambdaGreen2[0]<<" "<<lambdaGreen2[1]<<endl;


    sum_deviations = (pow(1/lambdaGreen1[1], 2) + pow(1/lambdaGreen2[1], 2));
    meanlambdaGreen[0] = (lambdaGreen1[0]/pow(lambdaGreen1[1], 2) + lambdaGreen2[0]/pow(lambdaGreen2[1], 2)) / sum_deviations;
    meanlambdaGreen[1] = 1/sqrt( sum_deviations );
    cout<<"meanGreen: "<<meanlambdaGreen[0]<<" "<<meanlambdaGreen[1]<<endl;
*/