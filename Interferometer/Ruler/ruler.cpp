//c++ -o ruler ruler.cpp `root-config --glibs --cflags`
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
    
    double thetaN[numberofHeights][2];
    double heights[numberofHeights][2];

    double incidentTheta[2];
    incidentTheta[0] = atan(source_height/table_distance);
    incidentTheta[1] = sqrt( pow( source_height*0.1/(table_distance*table_distance)/( 1+pow(source_height/table_distance, 2) ) , 2)  +pow(   0.1/(table_distance)/( 1+pow(source_height/table_distance, 2) ) , 2) );
    cout<<"theta inc: "<<incidentTheta[0]<<" +/- "<<incidentTheta[1]<<endl;

    getAltezze(heights);
    getTheta(thetaN, heights);

    double ErrDiffCos;
    file_dati.open("cos(incidentTheta)-cos(thetaN)_N.txt", ios::out);
    file_dati<<"#N \t cos(incidentTheta)-cos(thetaN) \t errY"<<endl;
    for(int i = 0; i<numberofHeights; i++){
        ErrDiffCos = sqrt( pow(sin(incidentTheta[0])*incidentTheta[1], 2)+ pow(sin(thetaN[i][0])*thetaN[i][1], 2) );
        file_dati<<i<<" \t "<<cos(incidentTheta[0]) - cos(thetaN[i][0])<<" \t\t\t "<<ErrDiffCos<<endl;
    }

//creation of a TGrapherrors
    gStyle->SetOptFit();
    auto c1 = new TCanvas("c1","multigraph",700,500);

    TGraphErrors *ge = new  TGraphErrors("cos(incidentTheta)-cos(thetaN)_N.txt" , "%lg %lg %lg"); 
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

//calculation of the linear correlation coefficient
    double rPitch;
    double num, den1, den2;
    double xMean[3];
    double yMean[3];
    double DiffCosPerCoeff[numberofHeights];
    double KPerCoeff[numberofHeights];

    for(int i = 0; i<numberofHeights; i++){
        DiffCosPerCoeff[i] = cos(incidentTheta[0]) - cos(thetaN[i][0]);
        KPerCoeff[i] = i;
    }

    Mean_Var_Dev(DiffCosPerCoeff, yMean, numberofHeights);
    Mean_Var_Dev(KPerCoeff, xMean, numberofHeights);

    for(int i = 0; i<numberofHeights; i++){
        num = num + (KPerCoeff[i] -  xMean[0])*(DiffCosPerCoeff[i] - yMean[0]);
        den1 = den1 + pow((KPerCoeff[i] -  xMean[0]), 2);
        den2 = den2 + pow((DiffCosPerCoeff[i] - yMean[0]), 2);
    }
    rPitch = num/sqrt(den1*den2);
    cout<<"linear coefficient - pitch: "<<rPitch<<endl;

//creation of a TF1

    double m, errm, ruler_pitch, errPitch;

    TF1 *f = new TF1("line", "[0]*x+[1]");
    ge->Fit("line");
    c1->Update();
    auto stats1 = (TPaveStats*)ge->GetListOfFunctions()->FindObject("stats");
    stats1->SetTextSize(0.02);
    stats1->SetX1NDC(0.12); stats1->SetX2NDC(0.32); stats1->SetY1NDC(0.75);
    c1->Modified();          
    c1->Print ("ruler_pitch.png", "png") ;

    TFitResult results;
    results.Print();

    m = f->GetParameter(0); 
    errm = f->GetParError(0);
    ruler_pitch = lambda/m;
    errPitch = lambda*errm/(m*m);
    cout<<"ruler pitch: "<<ruler_pitch<<" \t "<<errPitch<<endl;

    TheApp.Run();
    delete c1;


    return 0;
}