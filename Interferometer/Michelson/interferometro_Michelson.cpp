//c++ -o interferometro_Michelson interferometro_Michelson.cpp `root-config --glibs --cflags`
#include <iostream>
#include <fstream> 
#include <cmath>
#include "dati_Michelson.cc"

#include "TApplication.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TAxis.h"
#include "TPaveStats.h"
#include "TLatex.h"
#include "TF1.h"
#include "TFitResult.h"
#include "TMatrixD.h"
#include "TStyle.h"

using namespace std;
int main(int argc, char* argv[]){


//CHECK CALIBRAZIONE
    double calibra[numeroMisureN][2];
    double errCalibro = 1;
    double somma_scarti = 0;
    double calib[] = {0, 0};

    for(int i = 0; i<numeroMisureN; i++){
        calibra[i][0] = N[i]*lambda/(2*Deltad[i]);
        calibra[i][1] = N[i]*lambda*errCalibro/(2*Deltad[i]*Deltad[i]);
        cout<<"calibra[i]"<<calibra[i][0]<<" +/- "<<calibra[i][1]<<endl;
        calib[0] = calib[0] + (calibra[i][0]/pow(calibra[i][1], 2));
        somma_scarti = somma_scarti + (1/pow(calibra[i][1], 2));
    }
    calib[0] = calib[0]/somma_scarti;
    calib[1] = 1/sqrt(somma_scarti);

    cout<<"rapporto di calibrazione: "<<calib[0]<<"+/-"<<calib[1]<<endl;

//INDICE DI RIFRAZIONE DELL'ARIA
    TApplication TheApp("theApp", &argc, argv);
    ofstream file_dati;

    double DeltaN[numeroP][2];
    getDeltaN(DeltaN);


    file_dati.open("DeltaN_DeltaP.txt", ios::out);
    file_dati<<"#DeltaP DeltaN \t errDeltaP \t errDeltaN"<<endl;

    for(int i = 0; i<numeroP; i++){
        cout<<Pf[i]<<" \t "<<DeltaN[i][0]<<" \t "<<"4"<<" \t "<<DeltaN[i][1]<<endl; //errore di 2kPa sulla pompa

        file_dati<<Pf[i]<<" \t "<<DeltaN[i][0]<<" \t "<<"4"<<" \t\t "<<DeltaN[i][1]<<endl;
    }

//creo un TGrapherrors
    gStyle->SetOptFit();
    auto c1 = new TCanvas("c1","multigraph",700,500);

    TGraphErrors *ge = new  TGraphErrors("DeltaN_DeltaP.txt" , "%lg %lg %lg %lg"); 
    ge->SetTitle("interpolazione per l'indice di rifrazione dell'aria");
    ge->GetXaxis()->SetTitle("#Delta P[kPa]");
    ge->GetYaxis()->SetTitle("#Delta N");

    ge->GetXaxis()->SetTitleSize(0.05);
    ge->GetXaxis()->SetTitleOffset(1.0);

    ge->GetYaxis()->SetTitleSize(0.05);
    ge->GetYaxis()->SetTitleOffset(1.0);

    ge->SetMarkerStyle(20);
    ge->Draw("AP");

//creo un TF1

    double m, Errm;
    double n[2];

    TF1 *f = new TF1("retta", "[0]*x"); 
    ge->Fit("retta");
    c1->Update();
    auto stats1 = (TPaveStats*)ge->GetListOfFunctions()->FindObject("stats");
    stats1->SetX1NDC(0.12); stats1->SetX2NDC(0.32); stats1->SetY1NDC(0.75);
    c1->Modified();           

    c1->Print ("indice_rifrazione_aria.png", "png");

    TFitResult results;
    results.Print();

    m = f->GetParameter(0); 
    Errm = f->GetParError(0);
    m = lambda*m/(2*l);
    Errm = lambda*Errm/(2*l);

    cout<<"m: "<<m<<" +/- "<<Errm<<endl;
    n[0] = 1 + Patm*m;
    n[1] = Errm*Patm;
    cout<<"indice di rifrazione dell'aria: "<<n[0]<<"  +/-  "<<n[1]<<endl;
    delete c1;
//INDICE DI RIFRAZIONE DEL VETRO

    double nVetro[2];
    double MediaTheta[3];
    double den, fatt1, fatt2, num;

    for(int i = 0; i<numeroMisureNVetro; i++){
        cout<<"thetaf[i]"<<thetaf[i]<<endl;
        thetaf[i] = thetaf[i]*M_PI/180;
    }

    Med_Var_Dev(thetaf, MediaTheta, numeroMisureNVetro);
    cout<<"media Theta: "<<MediaTheta[0]<< " $pm$ "<<MediaTheta[2]<<endl;
    nVetro[0] = (2*t - NVetro*lambda )*( 1 - cos(MediaTheta[0]) )/(2*t* ( 1 - cos(MediaTheta[0]) ) - NVetro*lambda );

    den = pow(2*t*( 1 - cos(MediaTheta[0]) ) - NVetro*lambda , 2);

    fatt1 = (2*t - NVetro*lambda )*sin(MediaTheta[0])*( 2*t* ( 1 - cos(MediaTheta[0]) ) - NVetro*lambda );
    fatt2 = (2*t - NVetro*lambda )*( 1 - cos(MediaTheta[0]) )*2*t*sin(MediaTheta[0]);
    num = MediaTheta[2]*(-fatt1 + fatt2);  //non uso l'incertezza dello strumento 
    nVetro[1] = num/den;

    cout<<"media indice di rifrazione vetro: "<<nVetro[0]<<" "<<nVetro[1]<<endl;

//INDICE DI RIFRAZIONE DEL VETRO METODO MEDIA PESATA

    double nVetro2[numeroMisureNVetro][2];
    double MedianVetro[] = {0, 0};
    double somma_scarti2 = 0;

    for(int i = 0; i<numeroMisureNVetro; i++){
        //thetaf[i] = thetaf[i]*M_PI/180; gia sistemato
        nVetro2[i][0] = (2*t - NVetro*lambda )*( 1 - cos(thetaf[i]) )/(2*t* ( 1 - cos(thetaf[i]) ) - NVetro*lambda );

        den = pow(2*t*( 1 - cos(thetaf[i]) ) - NVetro*lambda , 2);

        fatt1 = (2*t - NVetro*lambda )*sin(thetaf[i])*( 2*t* ( 1 - cos(thetaf[i]) ) - NVetro*lambda );
        fatt2 = (2*t - NVetro*lambda )*( 1 - cos(thetaf[i]) )*2*t*sin(thetaf[i]);
        num = (M_PI/180)*(-fatt1 + fatt2);  //uso l'incertezza dello strumento
        nVetro2[i][1] = num/den;
        cout<<"nVetro2[i]: "<<nVetro2[i][0]<<" pm "<<nVetro2[i][1]<<endl;
        MedianVetro[0] = MedianVetro[0] + (nVetro2[i][0]/pow(nVetro2[i][1], 2));
        somma_scarti2 = somma_scarti2 + (1/pow(nVetro2[i][1], 2));
    }

    MedianVetro[0] = MedianVetro[0]/somma_scarti2;
    MedianVetro[1] = sqrt(1/somma_scarti2);

    cout<<"media pesata indice di rifrazione vetro: "<<MedianVetro[0]<<" "<<MedianVetro[1]<<endl;

//INDICE DI RIFRAZIONE DEL VETRO CON 10

    double nVetro10[2];
    double MediaN[3];
    double derivata_N, derivata_theta;

    thetaf10 = thetaf10*M_PI/180;

    Med_Var_Dev(NVetro10, MediaN, numeroMisureNVetro);
    cout<<"media N: "<<MediaN[0]<< " $pm$ "<<MediaN[2]<<endl;
    nVetro10[0] = (2*t - MediaN[0]*lambda )*( 1 - cos(thetaf10) )/(2*t* ( 1 - cos(thetaf10) ) - MediaN[0]*lambda );

    den = pow(2*t*( 1 - cos(thetaf10) ) - MediaN[0]*lambda , 2);
    num = MediaN[2]*2*t*(1-cos(thetaf10))*lambda*cos(thetaf10);
    derivata_N = num/den;

    den = pow(2*t*( 1 - cos(thetaf10) ) - MediaN[0]*lambda , 2);
    num = (M_PI/180)*(lambda*MediaN[0]-2*t)*lambda*MediaN[0]*sin(thetaf10);  //uso l'incertezza dello strumento 
    derivata_theta = num/den;

    nVetro10[1] = sqrt( pow(derivata_N, 2) + pow(derivata_theta, 2) );

    cout<<"media indice di rifrazione vetro10: "<<nVetro10[0]<<" "<<nVetro10[1]<<endl;


//INDICE DI RIFRAZIONE DEL VETRO CON 10 METODO MEDIA PESATA

    double nVetro10_2[numeroMisureNVetro][2];
    double MedianVetro2[] = {0, 0};
    double somma_scarti3 = 0;

    //thetaf10 = thetaf10*M_PI/180; gia sistemato
    cout<<"theta finale 10_2: "<<thetaf10<<endl;

    for(int i = 0; i<numeroMisureNVetro; i++){
        nVetro10_2[i][0] = (2*t - NVetro10[i]*lambda )*( 1 - cos(thetaf10) )/(2*t* ( 1 - cos(thetaf10) ) - NVetro10[i]*lambda );
        den = pow(2*t*( 1 - cos(thetaf10) ) - NVetro10[i]*lambda , 2);
        num = (M_PI/180)*(lambda*NVetro10[i]-2*t)*lambda*NVetro10[i]*sin(thetaf10);  //uso l'incertezza dello strumento 
        
        nVetro10_2[i][1] = num/den;

        somma_scarti3 = somma_scarti3 + (1/pow(nVetro10_2[i][1], 2));
        MedianVetro2[0] = MedianVetro2[0] + (nVetro10_2[i][0]/pow(nVetro10_2[i][1], 2));
    }

    MedianVetro2[0] = MedianVetro2[0]/somma_scarti3;
    MedianVetro2[1] = 1/sqrt(somma_scarti3);
    cout<<"media pesata indice di rifrazione vetro10: "<<MedianVetro2[0]<<" "<<MedianVetro2[1]<<endl;

    TheApp.Run();
    delete c1;
    return 0;
//i 10 gradi sono meno accurati ma più precisi

}