#include "graticule_data.h"
#include "../clean_data.h"
#include <cmath>
#include <iostream>
#include <algorithm>


//####################
// functions yellow
//####################

// fills yellowLeft[] using dataYellowLeft[]
void getYellowLeft(double yellow[]){

  double yellowDec[numberofMeasures];
  double meanYellow[3];

  double centerDec[numberofMeasures];
  double meanCenter[3];


  NormalForm( data_center, centerDec, numberofMeasures);
  DegreeToRadiant( centerDec, numberofMeasures );
  Mean_Var_Dev(centerDec, meanCenter, numberofMeasures);


  NormalForm( data_yellowLeft, yellowDec, numberofMeasures);
  DegreeToRadiant( yellowDec, numberofMeasures );
  Mean_Var_Dev(yellowDec, meanYellow, numberofMeasures);
  cout<<"meanYellow1sx: "<<meanYellow[0]<<" "<<meanYellow[2]<<endl;


  yellow[0] =  -(meanYellow[0]-meanCenter[0]); 
  yellow[1] = sqrt(meanYellow[2]*meanYellow[2] + meanCenter[2]*meanCenter[2]);

  
}

// fills yellowRight[] using dataYellowRight[]
void getYellowRight(double yellow[]){

  double yellowDec[numberofMeasures];
  double meanYellow[3];

  double centerDec[numberofMeasures];
  double meanCenter[3];


  NormalForm( data_center, centerDec, numberofMeasures);
  DegreeToRadiant( centerDec, numberofMeasures );
  Mean_Var_Dev(centerDec, meanCenter, numberofMeasures);


  NormalForm( data_yellowRight, yellowDec, numberofMeasures);
  DegreeToRadiant( yellowDec, numberofMeasures );
  Mean_Var_Dev(yellowDec, meanYellow, numberofMeasures);



  yellow[0] = meanYellow[0]-meanCenter[0]+( 2*M_PI ); 
  yellow[1] = sqrt(meanYellow[2]*meanYellow[2] + meanCenter[2]*meanCenter[2]);

  
  
}

void getYellow1(double yellow[]){
    double X[2];
    double Y[2];

    getYellowLeft(X);
    getYellowRight(Y);

    double deviations_sum = pow((1/X[1]), 2) + pow((1/Y[1]), 2);
    yellow[0] = ( (X[0]/pow(X[1], 2))+(Y[0]/pow(Y[1], 2)) )/deviations_sum;
    yellow[1] = sqrt(1/deviations_sum);
}

// fills yellow2[] using data_yellow2[]
void getYellow2(double yellow[]){

  double yellowDec[numberofMeasures2];
  double meanYellow[3];

  double centerDec[numberofMeasures2];
  double meanCenter[3];


  NormalForm( data_center2, centerDec, numberofMeasures2);
  DegreeToRadiant( centerDec, numberofMeasures2 );
  Mean_Var_Dev(centerDec, meanCenter, numberofMeasures);



  NormalForm( data_yellow2, yellowDec, numberofMeasures2);
  DegreeToRadiant( yellowDec, numberofMeasures2 );
  Mean_Var_Dev(yellowDec, meanYellow, numberofMeasures);



  yellow[0] = -(meanYellow[0]-meanCenter[0]); 
  yellow[1] = sqrt(meanYellow[2]*meanYellow[2] + meanCenter[2]*meanCenter[2]);
}


//####################
// functions red
//####################

void getRedLeft(double red[]){

  double redDec[numberofMeasures];
  double meanRed[3];

  double centerDec[numberofMeasures];
  double meanCenter[3];


  NormalForm( data_center, centerDec, numberofMeasures);
  DegreeToRadiant( centerDec, numberofMeasures );
  Mean_Var_Dev(centerDec, meanCenter, numberofMeasures);

  NormalForm( data_redLeft, redDec, numberofMeasures);
  DegreeToRadiant( redDec, numberofMeasures );
  Mean_Var_Dev(redDec, meanRed, numberofMeasures);


  red[0] = -(meanRed[0]-meanCenter[0]); 
  red[1] = sqrt(meanRed[2]*meanRed[2] + meanCenter[2]*meanCenter[2]);


  
}

// fills redRight[] using dataRedRight[]
void getRedRight(double red[]){

  double redDec[numberofMeasures];
  double meanRed[3];

  double centerDec[numberofMeasures];
  double meanCenter[3];

  NormalForm( data_center, centerDec, numberofMeasures);
  DegreeToRadiant( centerDec, numberofMeasures );
  Mean_Var_Dev(centerDec, meanCenter, numberofMeasures);


  NormalForm( data_redRight, redDec, numberofMeasures);
  DegreeToRadiant( redDec, numberofMeasures );
  Mean_Var_Dev(redDec, meanRed, numberofMeasures);


  red[0] = meanRed[0]-meanCenter[0] + (2*M_PI);
  red[1] = sqrt(meanRed[2]*meanRed[2] + meanCenter[2]*meanCenter[2]);

}

void getRed1(double red[]){
    double X[2];
    double Y[2];
    
    getRedLeft(X);
    getRedRight(Y);
    
    double deviations_sum = pow((1/X[1]), 2) + pow((1/Y[1]), 2);
    red[0] = ( (X[0]/pow(X[1], 2))+(Y[0]/pow(Y[1], 2)) )/deviations_sum;
    red[1] = sqrt(1/deviations_sum);

 
}

// fills red2[] using data_red2[]
void getRed2(double red[]){

  double redDec[numberofMeasures2];
  double meanRed[3];

  double centerDec[numberofMeasures2];
  double meanCenter[3];

  NormalForm( data_center2, centerDec, numberofMeasures2);
  DegreeToRadiant( centerDec, numberofMeasures2 );
  Mean_Var_Dev(centerDec, meanCenter, numberofMeasures);


  NormalForm( data_red2, redDec, numberofMeasures2);
  DegreeToRadiant( redDec, numberofMeasures2 );
  Mean_Var_Dev(redDec, meanRed, numberofMeasures);


  red[0] = -(meanRed[0]-meanCenter[0]); 
  red[1] = sqrt(meanRed[2]*meanRed[2] + meanCenter[2]*meanCenter[2]);

}

//####################
// functions blue
//####################

void getBlue1(double blue[]){

  double blueDec[numberofMeasures];
  double meanBlue[3];

  double centerDec[numberofMeasures];
  double meanCenter[3];


  NormalForm( data_center, centerDec, numberofMeasures);
  DegreeToRadiant( centerDec, numberofMeasures );
  Mean_Var_Dev(centerDec, meanCenter, numberofMeasures);


  NormalForm( data_blue1, blueDec, numberofMeasures);
  DegreeToRadiant( blueDec, numberofMeasures );
  Mean_Var_Dev(blueDec, meanBlue, numberofMeasures);

  blue[0] = meanBlue[0]-meanCenter[0]; //positivo=34
  blue[1] = sqrt(meanBlue[2]*meanBlue[2] + meanCenter[2]*meanCenter[2]);


}

void getBlue2(double blue[]){

  double blueDec[numberofMeasures2];
  double meanBlue[3];

  double centerDec[numberofMeasures2];
  double meanCenter[3];


  NormalForm( data_center2, centerDec, numberofMeasures2);
  DegreeToRadiant( centerDec, numberofMeasures2 );
  Mean_Var_Dev(centerDec, meanCenter, numberofMeasures);


  NormalForm( data_blue2, blueDec, numberofMeasures2);
  DegreeToRadiant( blueDec, numberofMeasures2 );
  Mean_Var_Dev(blueDec, meanBlue, numberofMeasures);


  blue[0] = -(meanBlue[0]-meanCenter[0]);
  blue[1] = sqrt(meanBlue[2]*meanBlue[2] + meanCenter[2]*meanCenter[2]);


}

//####################
// functions green
//####################

void getGreen1(double green[]){

  double greenDec[numberofMeasures];
  double meanGreen[3];

  double centerDec[numberofMeasures];
  double meanCenter[3];


  NormalForm( data_center, centerDec, numberofMeasures);
  DegreeToRadiant( centerDec, numberofMeasures );
  Mean_Var_Dev(centerDec, meanCenter, numberofMeasures);


  NormalForm( data_green1, greenDec, numberofMeasures);
  DegreeToRadiant( greenDec, numberofMeasures );
  Mean_Var_Dev(greenDec, meanGreen, numberofMeasures);



  green[0] = meanGreen[0]-meanCenter[0]; 
  green[1] = sqrt(meanGreen[2]*meanGreen[2] + meanCenter[2]*meanCenter[2]);

}

void getGreen2(double green[]){

  double greenDec[numberofMeasures2];
  double meanGreen[3];


  double centerDec[numberofMeasures2];
  double meanCenter[3];


  NormalForm( data_center2, centerDec, numberofMeasures2);
  DegreeToRadiant( centerDec, numberofMeasures2 );
  Mean_Var_Dev(centerDec, meanCenter, numberofMeasures);


  NormalForm( data_green2, greenDec, numberofMeasures2);
  DegreeToRadiant( greenDec, numberofMeasures2 );
  Mean_Var_Dev(greenDec, meanGreen, numberofMeasures);


  green[0] = -(meanGreen[0]-meanCenter[0]); //positivo
  green[1] = sqrt(meanGreen[2]*meanGreen[2] + meanCenter[2]*meanCenter[2]);

}







