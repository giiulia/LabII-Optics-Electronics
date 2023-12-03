//c++ -o virtual virtual.cpp `root-config --glibs --cflags`
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

//CALIBRATION
    double calibrate[numberofMeasuresN];
    double calib[3];
    double deviations_sum = 0;

    for(int i = 0; i<numberofMeasuresN; i++){
        calibrate[i] = N[i]*lambda/(2*cos(0.5236)*Deltad[i]); //0.5236rad = 30 degrees
        cout<<"calibrate[i]: "<<calibrate[i]<<endl;
    }


    Med_Var_Dev(calibrate, calib, numberofMeasuresN);
    cout<<"rapporto di calibratezione: "<<calib[0]<<" +/- "<<calib[2]<<endl;

//GREEN
    TApplication TheApp("theApp", &argc, argv);
    ofstream file_green;
    TCanvas* c1 = new TCanvas();

    double NGreen[numberofPoints][2];
    getNGreen(NGreen);

    file_green.open("NGreen_DeltaD.txt", ios::out);
    file_green<<"#DeltaD \tN  \tsigmaDeltaD \tsigmaN"<<endl;

    for(int i = 0; i<numberofPoints; i++){
        cout<<"calib[2]"<<calib[2]<<endl;
        file_green<<DeltadGreen[i]*calib[0]<<" \t "<<NGreen[i][0]<<" \t "<<DeltadGreen[i]*calib[2]<<" \t "<<NGreen[i][1]<<endl;
    }

    TGraphErrors *geV = new  TGraphErrors("NGreen_DeltaD.txt" , "%lg %lg %lg %lg"); 
    geV->SetTitle("interpolazione per il green");
    geV->GetXaxis()->SetTitle("#Delta D");
    geV->GetYaxis()->SetTitle("#Delta N");

    geV->GetXaxis()->SetTitleSize(0.05);
    geV->GetXaxis()->SetTitleOffset(1.0);

    geV->GetYaxis()->SetTitleSize(0.05);
    geV->GetYaxis()->SetTitleOffset(1.0);

    geV->SetMarkerStyle(20);
    geV->Draw("AP");

//calculation of the linear correlation coefficient
    double rGreen;
    double xMeanY[3];
    double yMeanY[3];
    double NGreenPerCoeff[numberofPoints];
    double DeltadGreenPerCoeff[numberofPoints];
    double num = 0, den1 = 0, den2 = 0;

    for(int i = 0; i<numberofPoints; i++){
        NGreenPerCoeff[i] = NGreen[i][0];
        DeltadGreenPerCoeff[i] = DeltadGreen[i]*calib[0];
    }

    Med_Var_Dev(DeltadGreenPerCoeff, yMeanY, numberofPoints);

    Med_Var_Dev(NGreenPerCoeff, xMeanY, numberofPoints);

    for(int i = 0; i<numberofPoints; i++){
        num = num + (NGreen[i][0] -  xMeanY[0])*(DeltadGreenPerCoeff[i] - yMeanY[0]);
        den1 = den1 + pow((NGreen[i][0] -  xMeanY[0]), 2);
        den2 = den2 + pow((DeltadGreenPerCoeff[i] - yMeanY[0]), 2);
    }
    rGreen = num/sqrt(den1*den2);
    cout<<"linear coefficient green: "<<rGreen<<endl;

//creation of a TF1

    double m1, Errm1;
    double lambdaGreen[2];

    TF1 *f1 = new TF1("line", "[0]*x"); 
    geV->Fit("line");
    gStyle->SetOptFit(1);

    c1->Print ("research_green.png", "png") ;

    m1 = f1->GetParameter(0); 
    Errm1 = f1->GetParError(0);
    lambdaGreen[0] = 2*cos(0.5236)/m1;
    lambdaGreen[1] = 2*cos(0.5236)*Errm1/(m1*m1);

    cout<<"wavelenght green: "<<lambdaGreen[0]<<"  +/-  "<<lambdaGreen[1]<<endl;

//YELLOW

    ofstream file_yellow;
    TCanvas* c2 = new TCanvas();

    double NYellow[numberofPoints][2];
    getNYellow(NYellow);

    file_yellow.open("NYellow_DeltaD.txt", ios::out);
    file_yellow<<"#DeltaD \tN  \tsigmaDeltaD \tsigmaN"<<endl;

    for(int i = 0; i<numberofPoints; i++){
        file_yellow<<DeltadYellow[i]*calib[0]<<" \t "<<NYellow[i][0]<<" \t "<<DeltadYellow[i]*calib[2]<<" \t "<<NYellow[i][1]<<endl;
    }

    TGraphErrors *geG = new  TGraphErrors("NYellow_DeltaD.txt" , "%lg %lg %lg %lg"); 
    geG->SetTitle("interpolazione per il yellow");
    geG->GetXaxis()->SetTitle("#Delta D");
    geG->GetYaxis()->SetTitle("#Delta N");

    geG->GetXaxis()->SetTitleSize(0.05);
    geG->GetXaxis()->SetTitleOffset(1.0);

    geG->GetYaxis()->SetTitleSize(0.05);
    geG->GetYaxis()->SetTitleOffset(1.0);

    geG->SetMarkerStyle(20);
    geG->Draw("AP");

//calculation of the linear correlation coefficient
    double rYellow;
    double xMeanY[3];
    double yMeanY[3];
    double NYellowPerCoeff[numberofPoints];
    double DeltadYellowPerCoeff[numberofPoints];

    for(int i = 0; i<numberofPoints; i++){
        NYellowPerCoeff[i] = NYellow[i][0];
        DeltadYellowPerCoeff[i] = DeltadYellow[i]*calib[0];
    }

    Med_Var_Dev(DeltadYellowPerCoeff, yMeanY, numberofPoints);
    Med_Var_Dev(NYellowPerCoeff, xMeanY, numberofPoints);

    for(int i = 0; i<numberofPoints; i++){
        num = num + (NYellow[i][0] -  xMeanY[0])*(DeltadYellowPerCoeff[i] - yMeanY[0]);
        den1 = den1 + pow((NYellow[i][0] -  xMeanY[0]), 2);
        den2 = den2 + pow((DeltadYellowPerCoeff[i] - yMeanY[0]), 2);
    }
    rYellow = num/sqrt(den1*den2);
    cout<<"linear coefficient yellow: "<<rYellow<<endl;

//creation of a TF1

    double m2, Errm2;
    double lambdaYellow[2];

    TF1 *f2 = new TF1("line", "[0]*x"); 
    geG->Fit("line");
    gStyle->SetOptFit(1);

    c2->Print ("research_yellow.png", "png") ;

    m2 = f2->GetParameter(0); 
    Errm2 = f2->GetParError(0);
    lambdaYellow[0] = 2*cos(0.5236)/m2;
    lambdaYellow[1] = 2*cos(0.5236)*Errm2/(m2*m2);

    cout<<"wavelenght yellow: "<<lambdaYellow[0]<<"  +/-  "<<lambdaYellow[1]<<endl;


//BLUE
    ofstream file_blue;
    TCanvas* c3 = new TCanvas();

    double NBlue[numberofPoints][2];
    getNBlue(NBlue);

    file_blue.open("NBlue_DeltaD.txt", ios::out);
    file_blue<<"#DeltaD \tN  \tsigmaDeltaD \tsigmaN"<<endl;

    for(int i = 0; i<numberofPoints; i++){
        file_blue<<DeltadBlue[i]*calib[0]<<" \t "<<NBlue[i][0]<<" \t "<<DeltadBlue[i]*calib[2]<<" \t "<<NBlue[i][1]<<endl;
    }

    TGraphErrors *geB = new  TGraphErrors("NBlue_DeltaD.txt" , "%lg %lg %lg %lg"); 
    geB->SetTitle("interpolazione per il blue");
    geB->GetXaxis()->SetTitle("#Delta D");
    geB->GetYaxis()->SetTitle("#Delta N");

    geB->GetXaxis()->SetTitleSize(0.05);
    geB->GetXaxis()->SetTitleOffset(1.0);

    geB->GetYaxis()->SetTitleSize(0.05);
    geB->GetYaxis()->SetTitleOffset(1.0);

    geB->SetMarkerStyle(20);
    geB->Draw("AP");

//calculation of the linear correlation coefficient
    double rBlue;
    double xMeanB[3];
    double yMeanB[3];
    double NBluePerCoeff[numberofPoints];
    double DeltadBlueperCoeff[numberofPoints];

    for(int i = 0; i<numberofPoints; i++){
        NBluePerCoeff[i] = NBlue[i][0];
        DeltadBlueperCoeff[i] = DeltadBlue[i]*calib[0];
    }

    Med_Var_Dev(DeltadBlueperCoeff, yMeanB, numberofPoints);
    Med_Var_Dev(NBluePerCoeff, xMeanB, numberofPoints);

    for(int i = 0; i<numberofPoints; i++){
        num = num + (NBlue[i][0] -  xMeanB[0])*(DeltadBlueperCoeff[i] - yMeanB[0]);
        den1 = den1 + pow((NBlue[i][0] -  xMeanB[0]), 2);
        den2 = den2 + pow((DeltadBlueperCoeff[i] - yMeanB[0]), 2);
    }
    rBlue = num/sqrt(den1*den2);
    cout<<"linear coefficient blue: "<<rBlue<<endl;

//creation of a TF1

    double m3, Errm3;
    double lambdaBlue[2];

    TF1 *f3 = new TF1("line", "[0]*x"); 
    geB->Fit("line");
    gStyle->SetOptFit(1);

    c3->Print ("research_blue.png", "png") ;

    m3 = f3->GetParameter(0); 
    Errm3 = f3->GetParError(0);
    lambdaBlue[0] = 2*cos(0.5236)/m3;
    lambdaBlue[1] = 2*cos(0.5236)*Errm3/(m3*m3);

    cout<<"wavelenght blue: "<<lambdaBlue[0]<<"  +/-  "<<lambdaBlue[1]<<endl;
    
    TheApp.Run();
    delete c1;
    delete c2;
    delete c3;

    return 0;
}