//c++ -o Fabry_Perot Fabry_Perot.cpp `root-config --glibs --cflags`

#include <iostream>
#include <fstream> 
#include <cmath>
#include "Fabry_Perot_data.cc"

#include "TApplication.h"
#include "TCanvas.h"
#include "TPaveStats.h"
#include "TGraphErrors.h"
#include "TAxis.h"
#include "TF1.h"
#include "TFitResult.h"
#include "TMatrixD.h"
#include "TStyle.h"

using namespace std;
int main(int argc, char* argv[]){
    TApplication TheApp("theApp", &argc, argv);
    ofstream file_dati;

    double theta[interferencesFringes][2];

    diameter_into_theta(diameter, theta[0]);
    diameter_into_theta(diameter2, theta[1]);
    diameter_into_theta(diameter3, theta[2]);
    diameter_into_theta(diameter4, theta[3]);
    diameter_into_theta(diameter5, theta[4]);
    
    file_dati.open("k_theta.txt", ios::out);
    file_dati<<"#cos(theta) \tk  \tsigmaCosTheta \tsigmaK"<<endl;

    for(int i = 0; i<interferencesFringes; i++){
        file_dati<<cos(theta[i][0])<<" \t "<<k[i]<<" \t "<<sin(theta[i][0])*theta[i][1]<<" \t "<<"0"<<endl;
    }

//creation of a TGrapherrors
    TCanvas* c1 = new TCanvas();

    TGraphErrors *ge = new  TGraphErrors("k_theta.txt" , "%lg %lg %lg %lg"); 
    ge->SetTitle("verifica della legge dei massimi di interferenza");

    ge->SetMarkerStyle(20);

    ge->GetXaxis()->SetTitle("cos(#theta)");
    ge->GetYaxis()->SetTitle("ordine K");

    ge->GetXaxis()->SetTitleSize(0.04);
    ge->GetXaxis()->SetTitleOffset(1.2);

    ge->GetYaxis()->SetNdivisions(5);
    ge->GetYaxis()->SetTitleSize(0.04);
    ge->GetYaxis()->SetTitleOffset(1.2);

    ge->Draw("AP");

    double errorX = ge->GetErrorX(0);
    cout<<"errorX "<<errorX<<endl;

    double errorY = ge->GetErrorY(0);
    cout<<"errorY "<<errorY<<endl;

//calculation of the coefficient of linear correlation

    double rCheck;
    double xMean[3];
    double yMedia = 3.;
    double CosTheta[interferencesFringes];
    double num = 0, den1 = 0, den2 = 0;

    for(int i = 0; i<interferencesFringes; i++){
        CosTheta[i] = cos(theta[i][0]);
    }

    Med_Var_Dev(CosTheta, xMean, interferencesFringes);

    for(int i = 0; i<interferencesFringes; i++){
        num = num + (CosTheta[i] -  xMean[0])*(k[i] - yMedia);
        den1 = den1 + pow((CosTheta[i] -  xMean[0]), 2);
        den2 = den2 + pow(((i+1) - yMedia), 2);
    }
    rCheck = num/sqrt(den1*den2);
    cout<<"linearity coefficient: "<<rCheck<<endl;

//creation of a TF1

    double m, Errm, c, Errc;
    double d[2];
    double deltaR[2];

    TF1 *f = new TF1("line", "[0]*x+[1]", 0, 1); 
    
    ge->Fit(f, "WQRN"); 
    ge->Fit(f, "RM+"); 

    gStyle->SetOptFit(1);

    c1->Print ("check.png", "png") ;

    TFitResult results;
    results.Print();

    m = f->GetParameter(0); 
    Errm = f->GetParError(0);
    c = f->GetParameter(1);
    Errc = f->GetParError(1); 


    d[0] = (lambda*m)/2;
    d[1] = lambda*Errm/2;
    cout<<"width of Fabry-Perot cavity: "<<d[0]<<" \t "<<d[1]<<endl;

    deltaR[0] = c*2*M_PI;
    deltaR[1] = 2*M_PI*Errc;
    cout<<"delta R: "<<deltaR[0]<<" \t "<<deltaR[1]<<endl;

    delete c1;

//CALIBRATION
    
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

    cout<<"division of calibration: "<<calib[0]<<"+/-"<<calib[1]<<endl;

    TheApp.Run();

    return 0;
}