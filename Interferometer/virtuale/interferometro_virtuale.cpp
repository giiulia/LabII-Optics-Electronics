//c++ -o interferometro_virtuale interferometro_virtuale.cpp `root-config --glibs --cflags`
#include <iostream>
#include <fstream> 
#include <cmath>
#include "dati_virtuale.cc"

#include "TApplication.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TAxis.h"
#include "TF1.h"
#include "TFitResult.h"
#include "TMatrixD.h"
#include "TStyle.h"

using namespace std;
int main(int argc, char* argv[]){

//CALIBRAZIONE
    double calibra[numeroMisureN];
    double calib[3];
    double somma_scarti = 0;

    for(int i = 0; i<numeroMisureN; i++){
        calibra[i] = N[i]*lambda/(2*cos(0.5236)*Deltad[i]); //0.5236rad = 30 gradi
        cout<<"calibra[i]: "<<calibra[i]<<endl;
    }


    Med_Var_Dev(calibra, calib, numeroMisureN);
    cout<<"rapporto di calibrazione: "<<calib[0]<<" +/- "<<calib[2]<<endl;

/*//CALIBRAZIONE
    double calibra[numeroMisureN][2];
    double calib[] = {0, 0};
    double somma_scarti = 0;

    for(int i = 0; i<numeroMisureN; i++){
        calibra[i][0] = N[i]*lambda/(2*cos(0.5236)*Deltad[i]); //0.5236rad = 30 gradi
        calibra[i][1] = 1*lambda/(2*cos(0.5236)*Deltad[i]); //l'errore su N è di 1
        cout<<"calibra[i] "<<calibra[i][0]<<" +/- "<<calibra[i][1]<<endl;

        calib[0] = calib[0] + (calibra[i][0]/pow(calibra[i][1], 2));
        somma_scarti = somma_scarti + (1/pow(calibra[i][1], 2));
    }


    calib[0] = calib[0]/somma_scarti;
    calib[1] = 1/sqrt(somma_scarti);
    cout<<"rapporto di calibrazione: "<<calib[0]<<" +/- "<<calib[1]<<endl;
*/
//VERDE
    TApplication TheApp("theApp", &argc, argv);
    ofstream file_verde;
    TCanvas* c1 = new TCanvas();

    double NVerde[numeroPunti][2];
    getNVerde(NVerde);

    file_verde.open("NVerde_DeltaD.txt", ios::out);
    file_verde<<"#DeltaD \tN  \tsigmaDeltaD \tsigmaN"<<endl;

    for(int i = 0; i<numeroPunti; i++){
        cout<<"calib[2]"<<calib[2]<<endl;
        file_verde<<DeltadVerde[i]*calib[0]<<" \t "<<NVerde[i][0]<<" \t "<<DeltadVerde[i]*calib[2]<<" \t "<<NVerde[i][1]<<endl;
    }

    TGraphErrors *geV = new  TGraphErrors("NVerde_DeltaD.txt" , "%lg %lg %lg %lg"); 
    geV->SetTitle("interpolazione per il verde");
    geV->GetXaxis()->SetTitle("#Delta D");
    geV->GetYaxis()->SetTitle("#Delta N");

    geV->GetXaxis()->SetTitleSize(0.05);
    geV->GetXaxis()->SetTitleOffset(1.0);

    geV->GetYaxis()->SetTitleSize(0.05);
    geV->GetYaxis()->SetTitleOffset(1.0);

    geV->SetMarkerStyle(20);
    geV->Draw("AP");

//calcolo il coefficiente di correlazione lineare
    double rVerde;
    double xMediaV[3];
    double yMediaV[3];
    double NVerdePerCoeff[numeroPunti];
    double DeltadVerdePerCoeff[numeroPunti];
    double num = 0, den1 = 0, den2 = 0;

    for(int i = 0; i<numeroPunti; i++){
        NVerdePerCoeff[i] = NVerde[i][0];
        DeltadVerdePerCoeff[i] = DeltadVerde[i]*calib[0];
    }

    Med_Var_Dev(DeltadVerdePerCoeff, yMediaV, numeroPunti);

    Med_Var_Dev(NVerdePerCoeff, xMediaV, numeroPunti);

    for(int i = 0; i<numeroPunti; i++){
        num = num + (NVerde[i][0] -  xMediaV[0])*(DeltadVerdePerCoeff[i] - yMediaV[0]);
        den1 = den1 + pow((NVerde[i][0] -  xMediaV[0]), 2);
        den2 = den2 + pow((DeltadVerdePerCoeff[i] - yMediaV[0]), 2);
    }
    rVerde = num/sqrt(den1*den2);
    cout<<"coefficiente di linearità verde: "<<rVerde<<endl;

//creo un TF1

    double m1, Errm1;
    double lambdaVerde[2];

    TF1 *f1 = new TF1("retta", "[0]*x"); 
    geV->Fit("retta");
    gStyle->SetOptFit(1);

    c1->Print ("ricerca_verde.png", "png") ;

    m1 = f1->GetParameter(0); 
    Errm1 = f1->GetParError(0);
    lambdaVerde[0] = 2*cos(0.5236)/m1;
    lambdaVerde[1] = 2*cos(0.5236)*Errm1/(m1*m1);

    cout<<"lunghezza d'onda verde: "<<lambdaVerde[0]<<"  +/-  "<<lambdaVerde[1]<<endl;

//GIALLO

    ofstream file_giallo;
    TCanvas* c2 = new TCanvas();

    double NGiallo[numeroPunti][2];
    getNGiallo(NGiallo);

    file_giallo.open("NGiallo_DeltaD.txt", ios::out);
    file_giallo<<"#DeltaD \tN  \tsigmaDeltaD \tsigmaN"<<endl;

    for(int i = 0; i<numeroPunti; i++){
        file_giallo<<DeltadGiallo[i]*calib[0]<<" \t "<<NGiallo[i][0]<<" \t "<<DeltadGiallo[i]*calib[2]<<" \t "<<NGiallo[i][1]<<endl;
    }

    TGraphErrors *geG = new  TGraphErrors("NGiallo_DeltaD.txt" , "%lg %lg %lg %lg"); 
    geG->SetTitle("interpolazione per il giallo");
    geG->GetXaxis()->SetTitle("#Delta D");
    geG->GetYaxis()->SetTitle("#Delta N");

    geG->GetXaxis()->SetTitleSize(0.05);
    geG->GetXaxis()->SetTitleOffset(1.0);

    geG->GetYaxis()->SetTitleSize(0.05);
    geG->GetYaxis()->SetTitleOffset(1.0);

    geG->SetMarkerStyle(20);
    geG->Draw("AP");

//calcolo il coefficiente di correlazione lineare
    double rGiallo;
    double xMediaG[3];
    double yMediaG[3];
    double NGialloPerCoeff[numeroPunti];
    double DeltadGialloPerCoeff[numeroPunti];

    for(int i = 0; i<numeroPunti; i++){
        NGialloPerCoeff[i] = NGiallo[i][0];
        DeltadGialloPerCoeff[i] = DeltadGiallo[i]*calib[0];
    }

    Med_Var_Dev(DeltadGialloPerCoeff, yMediaG, numeroPunti);
    Med_Var_Dev(NGialloPerCoeff, xMediaG, numeroPunti);

    for(int i = 0; i<numeroPunti; i++){
        num = num + (NGiallo[i][0] -  xMediaG[0])*(DeltadGialloPerCoeff[i] - yMediaG[0]);
        den1 = den1 + pow((NGiallo[i][0] -  xMediaG[0]), 2);
        den2 = den2 + pow((DeltadGialloPerCoeff[i] - yMediaG[0]), 2);
    }
    rGiallo = num/sqrt(den1*den2);
    cout<<"coefficiente di linearità giallo: "<<rGiallo<<endl;

//creo un TF1

    double m2, Errm2;
    double lambdaGialla[2];

    TF1 *f2 = new TF1("retta", "[0]*x"); 
    geG->Fit("retta");
    gStyle->SetOptFit(1);

    c2->Print ("ricerca_giallo.png", "png") ;

    m2 = f2->GetParameter(0); 
    Errm2 = f2->GetParError(0);
    lambdaGialla[0] = 2*cos(0.5236)/m2;
    lambdaGialla[1] = 2*cos(0.5236)*Errm2/(m2*m2);

    cout<<"lunghezza d'onda gialla: "<<lambdaGialla[0]<<"  +/-  "<<lambdaGialla[1]<<endl;


//BLU
    ofstream file_blu;
    TCanvas* c3 = new TCanvas();

    double NBlu[numeroPunti][2];
    getNBlu(NBlu);

    file_blu.open("NBlu_DeltaD.txt", ios::out);
    file_blu<<"#DeltaD \tN  \tsigmaDeltaD \tsigmaN"<<endl;

    for(int i = 0; i<numeroPunti; i++){
        file_blu<<DeltadBlu[i]*calib[0]<<" \t "<<NBlu[i][0]<<" \t "<<DeltadBlu[i]*calib[2]<<" \t "<<NBlu[i][1]<<endl;
    }

    TGraphErrors *geB = new  TGraphErrors("NBlu_DeltaD.txt" , "%lg %lg %lg %lg"); 
    geB->SetTitle("interpolazione per il blu");
    geB->GetXaxis()->SetTitle("#Delta D");
    geB->GetYaxis()->SetTitle("#Delta N");

    geB->GetXaxis()->SetTitleSize(0.05);
    geB->GetXaxis()->SetTitleOffset(1.0);

    geB->GetYaxis()->SetTitleSize(0.05);
    geB->GetYaxis()->SetTitleOffset(1.0);

    geB->SetMarkerStyle(20);
    geB->Draw("AP");

//calcolo il coefficiente di correlazione lineare
    double rBlu;
    double xMediaB[3];
    double yMediaB[3];
    double NBluPerCoeff[numeroPunti];
    double DeltadBluperCoeff[numeroPunti];

    for(int i = 0; i<numeroPunti; i++){
        NBluPerCoeff[i] = NBlu[i][0];
        DeltadBluperCoeff[i] = DeltadBlu[i]*calib[0];
    }

    Med_Var_Dev(DeltadBluperCoeff, yMediaB, numeroPunti);
    Med_Var_Dev(NBluPerCoeff, xMediaB, numeroPunti);

    for(int i = 0; i<numeroPunti; i++){
        num = num + (NBlu[i][0] -  xMediaB[0])*(DeltadBluperCoeff[i] - yMediaB[0]);
        den1 = den1 + pow((NBlu[i][0] -  xMediaB[0]), 2);
        den2 = den2 + pow((DeltadBluperCoeff[i] - yMediaB[0]), 2);
    }
    rBlu = num/sqrt(den1*den2);
    cout<<"coefficiente di linearità blu: "<<rBlu<<endl;

//creo un TF1

    double m3, Errm3;
    double lambdaBlu[2];

    TF1 *f3 = new TF1("retta", "[0]*x"); 
    geB->Fit("retta");
    gStyle->SetOptFit(1);

    c3->Print ("ricerca_blu.png", "png") ;

    m3 = f3->GetParameter(0); 
    Errm3 = f3->GetParError(0);
    lambdaBlu[0] = 2*cos(0.5236)/m3;
    lambdaBlu[1] = 2*cos(0.5236)*Errm3/(m3*m3);

    cout<<"lunghezza d'onda blu: "<<lambdaBlu[0]<<"  +/-  "<<lambdaBlu[1]<<endl;
    
    TheApp.Run();
    delete c1;
    delete c2;
    delete c3;

    return 0;
}