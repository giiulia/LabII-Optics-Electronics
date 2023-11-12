//c++ -o righello righello.cpp `root-config --glibs --cflags`
#include <iostream>
#include <fstream> 
#include <cmath>
#include "righello.cc"

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

int main(int argc, char* argv[]){
    
    TApplication TheApp("theApp", &argc, argv);
    ofstream file_dati;
    
    double thetaN[numeroAltezze][2];
    double altezze[numeroAltezze][2];

    double thetaInc[2];
    thetaInc[0] = atan(altezza_sorgente/distanza_tavolo);
    thetaInc[1] = sqrt( pow( altezza_sorgente*0.1/(distanza_tavolo*distanza_tavolo)/( 1+pow(altezza_sorgente/distanza_tavolo, 2) ) , 2)  +pow(   0.1/(distanza_tavolo)/( 1+pow(altezza_sorgente/distanza_tavolo, 2) ) , 2) );
    cout<<"theta inc: "<<thetaInc[0]<<" +/- "<<thetaInc[1]<<endl;

    getAltezze(altezze);
    getTheta(thetaN, altezze);

    double ErrDiffCos;
    file_dati.open("cos(thetaInc)-cos(thetaN)_N.txt", ios::out);
    file_dati<<"#N \t cos(thetaInc)-cos(thetaN) \t errY"<<endl;
    for(int i = 0; i<numeroAltezze; i++){
        ErrDiffCos = sqrt( pow(sin(thetaInc[0])*thetaInc[1], 2)+ pow(sin(thetaN[i][0])*thetaN[i][1], 2) );
        file_dati<<i<<" \t "<<cos(thetaInc[0]) - cos(thetaN[i][0])<<" \t\t\t "<<ErrDiffCos<<endl;
    }

//creo un TGrapherrors
    gStyle->SetOptFit();
    auto c1 = new TCanvas("c1","multigraph",700,500);

    TGraphErrors *ge = new  TGraphErrors("cos(thetaInc)-cos(thetaN)_N.txt" , "%lg %lg %lg"); 
    ge->SetTitle("interpolazione per il passo del righello");
    ge->GetXaxis()->SetTitle("ordine del massimo");
    ge->GetXaxis()->SetNdivisions(8);
    ge->GetYaxis()->SetTitle("cos(#theta_{Inc})-cos(#theta_{N})");

    ge->GetXaxis()->SetTitleSize(0.04);
    ge->GetXaxis()->SetTitleOffset(1.2);

    ge->GetYaxis()->SetTitleSize(0.04);
    ge->GetYaxis()->SetTitleOffset(1.2);

    ge->SetMarkerStyle(20);
    ge->Draw("AP");

//calcolo il coefficiente di correlazione lineare
    double rpasso;
    double num, den1, den2;
    double xMedia[3];
    double yMedia[3];
    double DiffCosPerCoeff[numeroAltezze];
    double KPerCoeff[numeroAltezze];

    for(int i = 0; i<numeroAltezze; i++){
        DiffCosPerCoeff[i] = cos(thetaInc[0]) - cos(thetaN[i][0]);
        KPerCoeff[i] = i;
    }

    Med_Var_Dev(DiffCosPerCoeff, yMedia, numeroAltezze);
    Med_Var_Dev(KPerCoeff, xMedia, numeroAltezze);

    for(int i = 0; i<numeroAltezze; i++){
        num = num + (KPerCoeff[i] -  xMedia[0])*(DiffCosPerCoeff[i] - yMedia[0]);
        den1 = den1 + pow((KPerCoeff[i] -  xMedia[0]), 2);
        den2 = den2 + pow((DiffCosPerCoeff[i] - yMedia[0]), 2);
    }
    rpasso = num/sqrt(den1*den2);
    cout<<"coefficiente di linearità passo: "<<rpasso<<endl;

//creo un TF1

    double m, errm, passo_righello, errPasso;

    TF1 *f = new TF1("retta", "[0]*x+[1]"); //nome dell'oggetto, xmin, xmax
    ge->Fit("retta");
    c1->Update();
    auto stats1 = (TPaveStats*)ge->GetListOfFunctions()->FindObject("stats");
    stats1->SetTextSize(0.02);
    stats1->SetX1NDC(0.12); stats1->SetX2NDC(0.32); stats1->SetY1NDC(0.75);
    c1->Modified();          
    c1->Print ("passo_righello.png", "png") ;

    TFitResult results;
    results.Print();

    m = f->GetParameter(0); 
    errm = f->GetParError(0);
    passo_righello = lambda/m;
    errPasso = lambda*errm/(m*m);
    cout<<"passo del righello: "<<passo_righello<<" \t "<<errPasso<<endl;

    TheApp.Run();
    delete c1;


    return 0;
}