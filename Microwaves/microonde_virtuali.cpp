#include <iostream>
#include <fstream> 
#include <cmath>

#include "TApplication.h"
#include "TCanvas.h"
#include "TPaveStats.h"
#include "TGraphErrors.h"
#include "TAxis.h"
#include "TF1.h"
#include "TFitResult.h"
#include "TMultiGraph.h"
#include "TStyle.h"

using namespace std;
int main(int argc, char *argv[]){
    TApplication TheApp("theApp", &argc, argv);
    ifstream file_dati;
    file_dati.open("dati_virtuali.txt", ios::in );

    gStyle->SetOptFit();

    cout<<"FIT OPZIONE 1"<<endl;
    TCanvas* c1 = new TCanvas();     

    TGraphErrors *ge1 = new  TGraphErrors("dati_virtuali.txt" , "%lg %lg 0. 0.2"); 
    ge1->SetTitle("interpolazione con A#left| cos(#theta) #right|");
    ge1->GetXaxis()->SetTitle("angolo[gradi]");
    ge1->GetYaxis()->SetTitle("lettura[mA]");

    ge1->GetXaxis()->SetTitleSize(0.05);
    ge1->GetXaxis()->SetTitleOffset(1.0);

    ge1->GetYaxis()->SetTitleSize(0.05);
    ge1->GetYaxis()->SetTitleOffset(1.0);

    ge1->SetMarkerStyle(20);
    ge1->Draw("AP");

    TF1 *f1 = new TF1("opzione1", "[0]* sqrt( pow(cos(x*3.1415/180), 2) ) "); 

    ge1->Fit("opzione1");
    c1->Print ("interpolazione_1.png", "png");
    TFitResult results1;
    results1.Print();

    delete c1;

    cout<<"FIT OPZIONE 2"<<endl;
    TCanvas* c2 = new TCanvas();     

    TGraph *ge2 = new  TGraph("dati_virtuali.txt" , "%lg %lg 0. 0.2"); 
    ge2->SetTitle("interpolazione con B cos(#theta)^{2}");
    ge2->GetXaxis()->SetTitle("angolo[gradi]");
    ge2->GetYaxis()->SetTitle("lettura[mA]");

    ge2->GetXaxis()->SetTitleSize(0.05);
    ge2->GetXaxis()->SetTitleOffset(1.0);

    ge2->GetYaxis()->SetTitleSize(0.05);
    ge2->GetYaxis()->SetTitleOffset(1.0);

    ge2->SetMarkerStyle(20);
    ge2->Draw("AP");

    TF1 *f2 = new TF1("opzione2", "[0]*pow( cos(x*3.1415/180) , 2)"); 

    ge2->Fit("opzione2");
    c2->Print ("interpolazione_2.png", "png");
    TFitResult results2;
    results2.Print();

    delete c2;

    cout<<"FIT OPZIONE 3"<<endl;
    TCanvas* c3 = new TCanvas();     
    
    TGraph *ge3 = new  TGraph("dati_virtuali.txt" , "%lg %lg 0. 0.2"); 
    ge3->SetTitle("interpolazione con A #left| cos(#theta) #right| + B cos(#theta)^{2}");
    ge3->GetXaxis()->SetTitle("angolo[gradi]");
    ge3->GetYaxis()->SetTitle("lettura[mA]");

    ge3->GetXaxis()->SetTitleSize(0.05);
    ge3->GetXaxis()->SetTitleOffset(1.0);

    ge3->GetYaxis()->SetTitleSize(0.05);
    ge3->GetYaxis()->SetTitleOffset(1.0);

    ge3->SetMarkerStyle(20);
    ge3->Draw("AP");

    TF1 *f3 = new TF1("opzione3", "[0]*pow( cos(x*3.1415/180) , 2) + [1]*sqrt( pow( cos(x*3.1415/180), 2) )"); 

    ge3->Fit("opzione3");
    c3->Print ("interpolazione_3.png", "png");
    TFitResult results3;
    results3.Print();

    delete c3;
  
    TheApp.Run();
    return 0;
}