#include "dati_reticolo.h"
#include "../clean_data.h"
#include <cmath>
#include <iostream>
#include <algorithm>


//####################
// funzioni giallo
//####################

// riempie gialloSx[] usando datiGialloSx[]
void getGialloSx(double giallo[]){

  double gialloDec[numeroMisure];
  double mediaG[3];

  double centroDec[numeroMisure];
  double mediaC[3];


  NormalForm( dati_centro, centroDec, numeroMisure);
  DegreeToRadiant( centroDec, numeroMisure );
  Med_Var_Dev(centroDec, mediaC, numeroMisure);


  NormalForm( dati_gialloSx, gialloDec, numeroMisure);
  DegreeToRadiant( gialloDec, numeroMisure );
  Med_Var_Dev(gialloDec, mediaG, numeroMisure);
  cout<<"mediaGiallo1sx: "<<mediaG[0]<<" "<<mediaG[2]<<endl;


  giallo[0] =  -(mediaG[0]-mediaC[0]); //positivo
  giallo[1] = sqrt(mediaG[2]*mediaG[2] + mediaC[2]*mediaC[2]);

  
}

// riempie gialloDx[] usando datiGialloDx[]
void getGialloDx(double giallo[]){

  double gialloDec[numeroMisure];
  double mediaG[3];

  double centroDec[numeroMisure];
  double mediaC[3];


  NormalForm( dati_centro, centroDec, numeroMisure);
  DegreeToRadiant( centroDec, numeroMisure );
  Med_Var_Dev(centroDec, mediaC, numeroMisure);


  NormalForm( dati_gialloDx, gialloDec, numeroMisure);
  DegreeToRadiant( gialloDec, numeroMisure );
  Med_Var_Dev(gialloDec, mediaG, numeroMisure);



  giallo[0] = mediaG[0]-mediaC[0]+( 2*M_PI ); //positivo
  giallo[1] = sqrt(mediaG[2]*mediaG[2] + mediaC[2]*mediaC[2]);

  
  
}

void getGiallo1(double giallo[]){
    double X[2];
    double Y[2];

    getGialloSx(X);
    getGialloDx(Y);

    double somma_scarti = pow((1/X[1]), 2) + pow((1/Y[1]), 2);
    giallo[0] = ( (X[0]/pow(X[1], 2))+(Y[0]/pow(Y[1], 2)) )/somma_scarti;
    giallo[1] = sqrt(1/somma_scarti);
}

// riempie giallo2[] usando dati_giallo2[]
void getGiallo2(double giallo[]){

  double gialloDec[numeroMisure2];
  double mediaG[3];

  double centroDec[numeroMisure2];
  double mediaC[3];


  NormalForm( dati_centro2, centroDec, numeroMisure2);
  DegreeToRadiant( centroDec, numeroMisure2 );
  Med_Var_Dev(centroDec, mediaC, numeroMisure);



  NormalForm( dati_giallo2, gialloDec, numeroMisure2);
  DegreeToRadiant( gialloDec, numeroMisure2 );
  Med_Var_Dev(gialloDec, mediaG, numeroMisure);



  giallo[0] = -(mediaG[0]-mediaC[0]); //positivo
  giallo[1] = sqrt(mediaG[2]*mediaG[2] + mediaC[2]*mediaC[2]);
}


//####################
// funzioni rosso
//####################

void getRossoSx(double rosso[]){

  double rossoDec[numeroMisure];
  double mediaR[3];

  double centroDec[numeroMisure];
  double mediaC[3];


  NormalForm( dati_centro, centroDec, numeroMisure);
  DegreeToRadiant( centroDec, numeroMisure );
  Med_Var_Dev(centroDec, mediaC, numeroMisure);

  NormalForm( dati_rossoSx, rossoDec, numeroMisure);
  DegreeToRadiant( rossoDec, numeroMisure );
  Med_Var_Dev(rossoDec, mediaR, numeroMisure);


  rosso[0] = -(mediaR[0]-mediaC[0]); //positivo
  rosso[1] = sqrt(mediaR[2]*mediaR[2] + mediaC[2]*mediaC[2]);


  
}

// riempie rossooDx[] usando datiRossoDx[]
void getRossoDx(double rosso[]){

  double rossoDec[numeroMisure];
  double mediaR[3];

  double centroDec[numeroMisure];
  double mediaC[3];

  NormalForm( dati_centro, centroDec, numeroMisure);
  DegreeToRadiant( centroDec, numeroMisure );
  Med_Var_Dev(centroDec, mediaC, numeroMisure);


  NormalForm( dati_rossoDx, rossoDec, numeroMisure);
  DegreeToRadiant( rossoDec, numeroMisure );
  Med_Var_Dev(rossoDec, mediaR, numeroMisure);


  rosso[0] = mediaR[0]-mediaC[0] + (2*M_PI); //positivo
  rosso[1] = sqrt(mediaR[2]*mediaR[2] + mediaC[2]*mediaC[2]);

}

void getRosso1(double rosso[]){
    double X[2];
    double Y[2];
    
    getRossoSx(X);
    getRossoDx(Y);
    
    double somma_scarti = pow((1/X[1]), 2) + pow((1/Y[1]), 2);
    rosso[0] = ( (X[0]/pow(X[1], 2))+(Y[0]/pow(Y[1], 2)) )/somma_scarti;
    rosso[1] = sqrt(1/somma_scarti);

 
}

// riempie rosso2[] usando dati_rosso2[]
void getRosso2(double rosso[]){

  double rossoDec[numeroMisure2];
  double mediaR[3];

  double centroDec[numeroMisure2];
  double mediaC[3];

  NormalForm( dati_centro2, centroDec, numeroMisure2);
  DegreeToRadiant( centroDec, numeroMisure2 );
  Med_Var_Dev(centroDec, mediaC, numeroMisure);


  NormalForm( dati_rosso2, rossoDec, numeroMisure2);
  DegreeToRadiant( rossoDec, numeroMisure2 );
  Med_Var_Dev(rossoDec, mediaR, numeroMisure);


  rosso[0] = -(mediaR[0]-mediaC[0]); //positivo
  rosso[1] = sqrt(mediaR[2]*mediaR[2] + mediaC[2]*mediaC[2]);

}

//####################
// funzioni blu
//####################

void getBlu1(double blu[]){

  double bluDec[numeroMisure];
  double mediaB[3];

  double centroDec[numeroMisure];
  double mediaC[3];


  NormalForm( dati_centro, centroDec, numeroMisure);
  DegreeToRadiant( centroDec, numeroMisure );
  Med_Var_Dev(centroDec, mediaC, numeroMisure);


  NormalForm( dati_blu1, bluDec, numeroMisure);
  DegreeToRadiant( bluDec, numeroMisure );
  Med_Var_Dev(bluDec, mediaB, numeroMisure);

  blu[0] = mediaB[0]-mediaC[0]; //positivo=34
  blu[1] = sqrt(mediaB[2]*mediaB[2] + mediaC[2]*mediaC[2]);


}

void getBlu2(double blu[]){

  double bluDec[numeroMisure2];
  double mediaB[3];

  double centroDec[numeroMisure2];
  double mediaC[3];


  NormalForm( dati_centro2, centroDec, numeroMisure2);
  DegreeToRadiant( centroDec, numeroMisure2 );
  Med_Var_Dev(centroDec, mediaC, numeroMisure);


  NormalForm( dati_blu2, bluDec, numeroMisure2);
  DegreeToRadiant( bluDec, numeroMisure2 );
  Med_Var_Dev(bluDec, mediaB, numeroMisure);


  blu[0] = -(mediaB[0]-mediaC[0]); //positivo=37
  blu[1] = sqrt(mediaB[2]*mediaB[2] + mediaC[2]*mediaC[2]);


}

//####################
// funzioni verde
//####################

void getVerde1(double verde[]){

  double verdeDec[numeroMisure];
  double mediaV[3];

  double centroDec[numeroMisure];
  double mediaC[3];


  NormalForm( dati_centro, centroDec, numeroMisure);
  DegreeToRadiant( centroDec, numeroMisure );
  Med_Var_Dev(centroDec, mediaC, numeroMisure);


  NormalForm( dati_verde1, verdeDec, numeroMisure);
  DegreeToRadiant( verdeDec, numeroMisure );
  Med_Var_Dev(verdeDec, mediaV, numeroMisure);



  verde[0] = mediaV[0]-mediaC[0]; //positivo
  verde[1] = sqrt(mediaV[2]*mediaV[2] + mediaC[2]*mediaC[2]);

}

void getVerde2(double verde[]){

  double verdeDec[numeroMisure2];
  double mediaV[3];


  double centroDec[numeroMisure2];
  double mediaC[3];


  NormalForm( dati_centro2, centroDec, numeroMisure2);
  DegreeToRadiant( centroDec, numeroMisure2 );
  Med_Var_Dev(centroDec, mediaC, numeroMisure);


  NormalForm( dati_verde2, verdeDec, numeroMisure2);
  DegreeToRadiant( verdeDec, numeroMisure2 );
  Med_Var_Dev(verdeDec, mediaV, numeroMisure);


  verde[0] = -(mediaV[0]-mediaC[0]); //positivo
  verde[1] = sqrt(mediaV[2]*mediaV[2] + mediaC[2]*mediaC[2]);

}







