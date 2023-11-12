//c++ -o spettrometro_reticolo spettrometro_reticolo.cpp
#include <iostream>
#include <fstream> 
#include <cmath>
#include "dati_reticolo.cc"

using namespace std;
int main(int argc, char* argv[]){

//trova il passo
    double giallo1[2];
    double giallo2[2];
    double passo1[2];
    double passo2[2];
    double mediaPasso[2];


    getGiallo1(giallo1);    
    getGiallo2(giallo2);

    passo1[0] = lambda*1/sin(giallo1[0]);
    passo1[1] = giallo1[1]*lambda*cos(giallo1[0])/pow(sin(giallo1[0]), 2);
    cout<<"passo1 "<<passo1[0]<< " "<<passo1[1]<<endl;

    passo2[0] = lambda*1/sin(giallo2[0]);
    passo2[1] = giallo2[1]*lambda*cos(giallo2[0])/pow(sin(giallo2[0]), 2);
    cout<<"passo2 non corretto"<<passo2[0]<<" "<<passo2[1]<<endl;

    double somma_scarti = (pow(1/passo1[1], 2) + pow(1/passo2[1], 2));
    mediaPasso[0] = (passo1[0]/pow(passo1[1], 2) + passo2[0]/pow(passo2[1], 2)) / somma_scarti;
    mediaPasso[1] = 1/sqrt( somma_scarti );
    cout<<"passo: "<<mediaPasso[0]<<" "<<mediaPasso[1]<<endl;

//corregge il passo
    double alpha[2];
    double beta_meno = (239-283)*M_PI/180;
    double beta_piu = (328-283)*M_PI/180;
    double sigma_beta_meno = 0.0002;
    double sigma_beta_piu = 0.0002;

    alpha[0] = atan((sin(beta_meno)+sin(beta_piu))/(2-cos(beta_meno)-cos(beta_piu)));
    double derivata_beta_meno = (cos(beta_meno) - sin(beta_meno))/pow(2-cos(beta_meno)-cos(beta_piu), 2);
    double derivata_beta_piu = (cos(beta_piu) - sin(beta_piu))/pow(2-cos(beta_meno)-cos(beta_piu), 2);

    cout<<"beta_meno: "<<beta_meno<<endl;
    cout<<"sigma_beta_meno: "<<sigma_beta_meno<<endl;
    cout<<"beta_piu: "<<beta_piu<<endl;
    cout<<"sigma_beta_piu: "<<sigma_beta_piu<<endl;
    alpha[1] = (1/(1 + pow((sin(beta_meno)+sin(beta_piu))/(2-cos(beta_meno)-cos(beta_piu)), 2)) ) * sqrt(pow(derivata_beta_meno*sigma_beta_meno, 2) + pow(derivata_beta_piu*sigma_beta_piu, 2));
    cout<<"alpha: "<<alpha[0]<<"  +/-  "<<alpha[1]<<endl; 
    double passo2Corretto[2];
    double mediaPassoCorretta[2];

    cout<<"giallo2[0]: "<<giallo2[0]<<endl;
    double theta[2];
    theta[0] = giallo2[0]-alpha[0];
    cout<<"theta[0]: "<<theta[0]<<endl;
    theta[1] = sqrt(alpha[1]*alpha[1] + giallo2[1]*giallo2[1]);
    cout<<"sigma theta: "<<theta[1]<<endl;
    passo2Corretto[0] = lambda*1/( sin(theta[0]) + sin(alpha[0]) );
    passo2Corretto[1] = sqrt( pow(  theta[1]*lambda*cos(theta[0])/pow(sin(theta[0]+sin(alpha[0])), 2) , 2 ) + pow(  alpha[1]*lambda*cos(alpha[0])/pow(sin(theta[0]+sin(alpha[0])), 2) , 2  )   );
    cout<<"passo2 corretto "<<passo2Corretto[0]<<" "<<passo2Corretto[1]<<endl;


    somma_scarti = (pow(1/passo1[1], 2) + pow(1/passo2Corretto[1], 2));
    mediaPassoCorretta[0] = (passo1[0]/pow(passo1[1], 2) + passo2Corretto[0]/pow(passo2Corretto[1], 2)) / somma_scarti;
    mediaPassoCorretta[1] = 1/sqrt( somma_scarti );
    cout<<"passo corretto: "<<mediaPassoCorretta[0]<<" "<<mediaPassoCorretta[1]<<endl;
//trova il rosso
    double rosso1[2];
    double rosso2[2];
    double mediaRosso[2];
    double lambdaRosso[2];

    getRosso1(rosso1);    
    getRosso2(rosso2);

    somma_scarti = (pow(1/rosso1[1], 2) + pow(1/rosso2[1], 2));
    mediaRosso[0] = (rosso1[0]/pow(rosso1[1], 2) + rosso2[0]/pow(rosso2[1], 2)) / somma_scarti;
    mediaRosso[1] = 1/sqrt( somma_scarti );
    cout<<"mediaRosso: "<<mediaRosso[0]<<" "<<mediaRosso[1]<<endl;

    lambdaRosso[0] = mediaPassoCorretta[0]*sin(mediaRosso[0])/1;
    lambdaRosso[1] = sqrt( pow( sin(mediaRosso[0])*mediaPassoCorretta[1] , 2) + pow( mediaPassoCorretta[0]*cos(mediaRosso[0])*mediaRosso[1] , 2) );
    cout<<"lambdaRosso: "<<lambdaRosso[0]<<" "<<lambdaRosso[1]<<endl;

//trova il blu
    double blu1[2];
    double blu2[2];
    double mediaBlu[2];
    double lambdaBlu[2];

    getBlu1(blu1);    
    getBlu2(blu2);

    somma_scarti = (pow(1/blu1[1], 2) + pow(1/blu2[1], 2));
    mediaBlu[0] = (blu1[0]/pow(blu1[1], 2) + blu2[0]/pow(blu2[1], 2)) / somma_scarti;
    mediaBlu[1] = 1/sqrt( somma_scarti );
    cout<<"mediaBlu: "<<mediaBlu[0]<<" "<<mediaBlu[1]<<endl;

    lambdaBlu[0] = mediaPassoCorretta[0]*sin(mediaBlu[0])/1;
    lambdaBlu[1] = sqrt( pow( sin(mediaBlu[0])*mediaPassoCorretta[1] , 2) + pow( mediaPassoCorretta[0]*cos(mediaBlu[0])*mediaBlu[1] , 2) );
    cout<<"lambdaBlu: "<<lambdaBlu[0]<<" "<<lambdaBlu[1]<<endl;

//trova il verde
    double verde1[2];
    double verde2[2];
    double mediaVerde[2];
    double lambdaVerde[2];

    getVerde1(verde1);    
    getVerde2(verde2);

    somma_scarti = (pow(1/verde1[1], 2) + pow(1/verde2[1], 2));
    mediaVerde[0] = (verde1[0]/pow(verde1[1], 2) + verde2[0]/pow(verde2[1], 2)) / somma_scarti;
    mediaVerde[1] = 1/sqrt( somma_scarti );
    cout<<"mediaVerde: "<<mediaVerde[0]<<" "<<mediaVerde[1]<<endl;

    lambdaVerde[0] = mediaPassoCorretta[0]*sin(mediaVerde[0])/1;
    lambdaVerde[1] = sqrt( pow( sin(mediaVerde[0])*mediaPassoCorretta[1] , 2) + pow( mediaPassoCorretta[0]*cos(mediaVerde[0])*mediaVerde[1], 2) );
    cout<<"lambdaVerde: "<<lambdaVerde[0]<<" "<<lambdaVerde[1]<<endl;

    return 0;
    
}

/*

//trova il verde
    double verde1[2];
    double verde2[2];
    double lambdaVerde1[2];
    double lambdaVerde2[2];
    double medialambdaVerde[2];

    getVerde1(verde1);    
    getVerde2(verde2);

    lambdaVerde1[0] = mediaPassoCorretta[0]*sin(verde1[0])/1;
    lambdaVerde1[1] = sqrt( pow( sin(verde1[0])*mediaPassoCorretta[1] , 2) + pow( mediaPassoCorretta[0]*cos(verde1[0])*verde1[1], 2) );
    cout<<"lambdaVerde: "<<lambdaVerde1[0]<<" "<<lambdaVerde1[1]<<endl;

    lambdaVerde2[0] = mediaPassoCorretta[0]*(sin(verde2[0])+sin(alpha[0]))/1;
    lambdaVerde2[1] = sqrt( pow( sin(verde2[0])*mediaPassoCorretta[1] , 2) + pow( mediaPassoCorretta[0]*cos(verde2[0])*verde2[1], 2) + pow( mediaPassoCorretta[0]*cos(alpha[0])*alpha[1], 2) );
    cout<<"lambdaVerde: "<<lambdaVerde2[0]<<" "<<lambdaVerde2[1]<<endl;


    somma_scarti = (pow(1/lambdaVerde1[1], 2) + pow(1/lambdaVerde2[1], 2));
    medialambdaVerde[0] = (lambdaVerde1[0]/pow(lambdaVerde1[1], 2) + lambdaVerde2[0]/pow(lambdaVerde2[1], 2)) / somma_scarti;
    medialambdaVerde[1] = 1/sqrt( somma_scarti );
    cout<<"mediaVerde: "<<medialambdaVerde[0]<<" "<<medialambdaVerde[1]<<endl;
*/