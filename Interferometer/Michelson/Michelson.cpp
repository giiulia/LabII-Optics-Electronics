//c++ -o Michelson Michelson.cpp `root-config --glibs --cflags`
#include <iostream>
#include <fstream> 
#include <cmath>
#include "Michelson_data.cc"

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


//CHECK CALIBRATION
    double calibrate[numeroMisureN][2];
    double errCaliber = 1;
    double deviations_sum = 0;
    double calib[] = {0, 0};

    for(int i = 0; i<numeroMisureN; i++){
        calibrate[i][0] = N[i]*lambda/(2*Deltad[i]);
        calibrate[i][1] = N[i]*lambda*errCaliber/(2*Deltad[i]*Deltad[i]);
        cout<<"calibrate[i]"<<calibrate[i][0]<<" +/- "<<calibrate[i][1]<<endl;
        calib[0] = calib[0] + (calibrate[i][0]/pow(calibrate[i][1], 2));
        deviations_sum = deviations_sum + (1/pow(calibrate[i][1], 2));
    }
    calib[0] = calib[0]/deviations_sum;
    calib[1] = 1/sqrt(deviations_sum);

    cout<<"calibration division: "<<calib[0]<<"+/-"<<calib[1]<<endl;

//AIR REFRACTION INDEX
    TApplication TheApp("theApp", &argc, argv);
    ofstream data_file;

    double DeltaN[numberP][2];
    getDeltaN(DeltaN);


    data_file.open("DeltaN_DeltaP.txt", ios::out);
    data_file<<"#DeltaP DeltaN \t errDeltaP \t errDeltaN"<<endl;

    for(int i = 0; i<numberP; i++){
        cout<<Pf[i]<<" \t "<<DeltaN[i][0]<<" \t "<<"4"<<" \t "<<DeltaN[i][1]<<endl; //errore di 2kPa sulla pompa

        data_file<<Pf[i]<<" \t "<<DeltaN[i][0]<<" \t "<<"4"<<" \t\t "<<DeltaN[i][1]<<endl;
    }

//creation of a TGrapherrors
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

//creation of a TF1

    double m, Errm;
    double n[2];

    TF1 *f = new TF1("line", "[0]*x"); 
    ge->Fit("line");
    c1->Update();
    auto stats1 = (TPaveStats*)ge->GetListOfFunctions()->FindObject("stats");
    stats1->SetX1NDC(0.12); stats1->SetX2NDC(0.32); stats1->SetY1NDC(0.75);
    c1->Modified();           

    c1->Print ("air_refraction_index.png", "png");

    TFitResult results;
    results.Print();

    m = f->GetParameter(0); 
    Errm = f->GetParError(0);
    m = lambda*m/(2*l);
    Errm = lambda*Errm/(2*l);

    cout<<"m: "<<m<<" +/- "<<Errm<<endl;
    n[0] = 1 + Patm*m;
    n[1] = Errm*Patm;
    cout<<"air refraction index: "<<n[0]<<"  +/-  "<<n[1]<<endl;
    delete c1;

//GLASS REFRACTION INDEX

    double nVetro[2];
    double ThetaMean[3];
    double den, fatt1, fatt2, num;

    for(int i = 0; i<numberofMeasuresNGlass; i++){
        cout<<"thetaf[i]"<<thetaf[i]<<endl;
        thetaf[i] = thetaf[i]*M_PI/180;
    }

    Med_Var_Dev(thetaf, ThetaMean, numberofMeasuresNGlass);
    cout<<"media Theta: "<<ThetaMean[0]<< " $pm$ "<<ThetaMean[2]<<endl;
    nVetro[0] = (2*t - NGlass*lambda )*( 1 - cos(ThetaMean[0]) )/(2*t* ( 1 - cos(ThetaMean[0]) ) - NGlass*lambda );

    den = pow(2*t*( 1 - cos(ThetaMean[0]) ) - NGlass*lambda , 2);

    fatt1 = (2*t - NGlass*lambda )*sin(ThetaMean[0])*( 2*t* ( 1 - cos(ThetaMean[0]) ) - NGlass*lambda );
    fatt2 = (2*t - NGlass*lambda )*( 1 - cos(ThetaMean[0]) )*2*t*sin(ThetaMean[0]);
    num = ThetaMean[2]*(-fatt1 + fatt2);  
    nVetro[1] = num/den;

    cout<<"media indice di rifrazione vetro: "<<nVetro[0]<<" "<<nVetro[1]<<endl;

//GLASS REFRACTION INDEX WITH WEIGHTED MEAN

    double NGlass2[numberofMeasuresNGlass][2];
    double NGlassMean[] = {0, 0};
    double deviations_sum2 = 0;

    for(int i = 0; i<numberofMeasuresNGlass; i++){

        NGlass2[i][0] = (2*t - NGlass*lambda )*( 1 - cos(thetaf[i]) )/(2*t* ( 1 - cos(thetaf[i]) ) - NGlass*lambda );

        den = pow(2*t*( 1 - cos(thetaf[i]) ) - NGlass*lambda , 2);

        fatt1 = (2*t - NGlass*lambda )*sin(thetaf[i])*( 2*t* ( 1 - cos(thetaf[i]) ) - NGlass*lambda );
        fatt2 = (2*t - NGlass*lambda )*( 1 - cos(thetaf[i]) )*2*t*sin(thetaf[i]);
        num = (M_PI/180)*(-fatt1 + fatt2); 
        NGlass2[i][1] = num/den;
        cout<<"NGlass2[i]: "<<NGlass2[i][0]<<" pm "<<NGlass2[i][1]<<endl;
        NGlassMean[0] = NGlassMean[0] + (NGlass2[i][0]/pow(NGlass2[i][1], 2));
        deviations_sum2 = deviations_sum2 + (1/pow(NGlass2[i][1], 2));
    }

    NGlassMean[0] = NGlassMean[0]/deviations_sum2;
    NGlassMean[1] = sqrt(1/deviations_sum2);

    cout<<"weighted mean glass refraction index: "<<NGlassMean[0]<<" "<<NGlassMean[1]<<endl;

//GLASS REFRACTION INDEX WITH 10

    double NGlass10[2];
    double MeanN[3];
    double derivative_N, derivative_theta;

    thetaf10 = thetaf10*M_PI/180;

    Med_Var_Dev(NGlass10, MeanN, numberofMeasuresNGlass);
    cout<<"media N: "<<MeanN[0]<< " $pm$ "<<MeanN[2]<<endl;
    NGlass10[0] = (2*t - MeanN[0]*lambda )*( 1 - cos(thetaf10) )/(2*t* ( 1 - cos(thetaf10) ) - MeanN[0]*lambda );

    den = pow(2*t*( 1 - cos(thetaf10) ) - MeanN[0]*lambda , 2);
    num = MeanN[2]*2*t*(1-cos(thetaf10))*lambda*cos(thetaf10);
    derivative_N = num/den;

    den = pow(2*t*( 1 - cos(thetaf10) ) - MeanN[0]*lambda , 2);
    num = (M_PI/180)*(lambda*MeanN[0]-2*t)*lambda*MeanN[0]*sin(thetaf10);  
    derivative_theta = num/den;

    NGlass10[1] = sqrt( pow(derivative_N, 2) + pow(derivative_theta, 2) );

    cout<<"media indice di rifrazione vetro10: "<<NGlass10[0]<<" "<<NGlass10[1]<<endl;


//GLASS REFRACTION INDEX WITH 10, WEIGHTED MEAN

    double NGlass10_2[numberofMeasuresNGlass][2];
    double MeanNGlass2[] = {0, 0};
    double deviations_sum3 = 0;

    cout<<"final theta 10_2: "<<thetaf10<<endl;

    for(int i = 0; i<numberofMeasuresNGlass; i++){
        NGlass10_2[i][0] = (2*t - NGlass10[i]*lambda )*( 1 - cos(thetaf10) )/(2*t* ( 1 - cos(thetaf10) ) - NGlass10[i]*lambda );
        den = pow(2*t*( 1 - cos(thetaf10) ) - NGlass10[i]*lambda , 2);
        num = (M_PI/180)*(lambda*NGlass10[i]-2*t)*lambda*NGlass10[i]*sin(thetaf10);  
        
        NGlass10_2[i][1] = num/den;

        deviations_sum3 = deviations_sum3 + (1/pow(NGlass10_2[i][1], 2));
        MeanNGlass2[0] = MeanNGlass2[0] + (NGlass10_2[i][0]/pow(NGlass10_2[i][1], 2));
    }

    MeanNGlass2[0] = MeanNGlass2[0]/deviations_sum3;
    MeanNGlass2[1] = 1/sqrt(deviations_sum3);
    cout<<"media pesata indice di rifrazione vetro10: "<<MeanNGlass2[0]<<" "<<MeanNGlass2[1]<<endl;

    TheApp.Run();
    delete c1;
    return 0;
//10 degrees are less accurate but more precise

}