//c++ -o interferometro_Fabry interferometro_Fabry.cpp `root-config --glibs --cflags`

#include <iostream>
#include <fstream> 
#include <cmath>
#include "dati_Fabry.cc"

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

    double theta[numeroFrange][2];

    diam_into_theta(diametro1, theta[0]);
    diam_into_theta(diametro2, theta[1]);
    diam_into_theta(diametro3, theta[2]);
    diam_into_theta(diametro4, theta[3]);
    diam_into_theta(diametro5, theta[4]);
    
    file_dati.open("k_theta.txt", ios::out);
    file_dati<<"#cos(theta) \tk  \tsigmaCosTheta \tsigmaK"<<endl;

    for(int i = 0; i<numeroFrange; i++){
        file_dati<<cos(theta[i][0])<<" \t "<<k[i]<<" \t "<<sin(theta[i][0])*theta[i][1]<<" \t "<<"0"<<endl;
    }

//creo un TGrapherrors
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

//calcolo il coefficiente di correlazione lineare

    double rVerifica;
    double xMedia[3];
    double yMedia = 3.;
    double CosTheta[numeroFrange];
    double num = 0, den1 = 0, den2 = 0;

    for(int i = 0; i<numeroFrange; i++){
        CosTheta[i] = cos(theta[i][0]);
    }

    Med_Var_Dev(CosTheta, xMedia, numeroFrange);

    for(int i = 0; i<numeroFrange; i++){
        num = num + (CosTheta[i] -  xMedia[0])*(k[i] - yMedia);
        den1 = den1 + pow((CosTheta[i] -  xMedia[0]), 2);
        den2 = den2 + pow(((i+1) - yMedia), 2);
    }
    rVerifica = num/sqrt(den1*den2);
    cout<<"coefficiente di linearità: "<<rVerifica<<endl;

//creo un TF1

    double m, Errm, c, Errc;
    double d[2];
    double deltaR[2];

    TF1 *f = new TF1("retta", "[0]*x+[1]", 0, 1); //nome dell'oggetto, xmin, xmax
    
    ge->Fit(f, "WQRN"); // "initial pre-fit"
    ge->Fit(f, "RM+"); // "final fit"
    //ge->Fit("retta");

    gStyle->SetOptFit(1);

    c1->Print ("verifica.png", "png") ;

    TFitResult results;
    results.Print();

    m = f->GetParameter(0); 
    Errm = f->GetParError(0);
    c = f->GetParameter(1);
    Errc = f->GetParError(1); 


    d[0] = (lambda*m)/2;
    d[1] = lambda*Errm/2;
    cout<<"larghezza cavità di Fabry-Perot: "<<d[0]<<" \t "<<d[1]<<endl;

    deltaR[0] = c*2*M_PI;
    deltaR[1] = 2*M_PI*Errc;
    cout<<"delta R: "<<deltaR[0]<<" \t "<<deltaR[1]<<endl;

    delete c1;

//CALIBRAZIONE
    
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

    TheApp.Run();

    return 0;
}