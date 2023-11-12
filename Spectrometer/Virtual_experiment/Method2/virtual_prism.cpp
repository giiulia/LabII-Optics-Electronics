//c++ -o virual_prism virual_prism.cpp `root-config --glibs --cflags`

#include <iostream>
#include <fstream> 
#include <sstream> 
#include <string> 
#include <cmath>
#include <math.h>
#include <typeinfo>

#include "TF1.h"
#include "TFitResult.h"
#include "TMatrixD.h"
#include "TStyle.h"
#include "TGraphErrors.h"
#include "TAxis.h"
#include "TApplication.h"
#include "TGraph.h"
#include "TCanvas.h"

using namespace std;
    
void draw_parable(const char* data_file, const char* file_png, double* y0, const char* titolo){
    TCanvas *c2 = new TCanvas();
    gStyle->SetCanvasDefH(400);
    gStyle->SetCanvasDefW(700);
    TGraphErrors *pt = new  TGraphErrors( data_file, "%lg %lg %lg"); // P=numero di punti
    pt->SetTitle(titolo);
    pt->GetXaxis()->SetTitle("theta [rad]");
    pt->GetYaxis()->SetTitle("delta [rad]");
    pt->SetMarkerStyle(20);
    pt->Draw("AP");

    TF1 *p = new TF1("parable", "[0]*x^{2} + [1]*x + [2]", 0.8, 0.85); //nome dell'oggetto, xmin, xmax y = yV+a*(x-xV)^2
    c2->cd();
    pt->Draw("AP");
    pt->Fit("parable");   
    c2->Modified();
    c2->Update();
    double a =  p->GetParameter(0);
    double b =  p->GetParameter(1);
    double c =  p->GetParameter(2);
    double aErr = p->GetParError(0);
    double bErr = p->GetParError(1);
    double cErr = p->GetParError(2);

    y0[0] = c-( pow(b, 2)/ (4*a) );
    y0[1] = sqrt( pow(cErr, 2) + pow(b*bErr/(2*a), 2) + pow(b*aErr/(4*a*a), 2) );
    cout<<"ordinata vertice ed errore: "<<y0[0]<<"p.m."<<y0[1]<<endl;

    c2->Print (file_png, "png") ;
    delete c2;

}



int main(int argc, char* argv[]){
    gStyle->SetOptFit(1112);

    TApplication TheApp("theApp", &argc, argv);

    int P = 5;

    double alpha = 1.0475;
    double base = 0.0531;
    double lambda[5] = {434.8064, 460.9567, 487.9864, 696.5431, 738.398};

    double y0[P][2]; 
    draw_parable("Data/parable1.txt", "Graphs/sampling1.png", y0[0], "ricerca delta minimo for lambda1");
    draw_parable("Data/parable2.txt", "Graphs/sampling2.png", y0[1], "ricerca delta minimo for lambda2");
    draw_parable("Data/parable3.txt", "Graphs/sampling3.png", y0[2], "ricerca delta minimo for lambda3");
    draw_parable("Data/parable4.txt", "Graphs/sampling4.png", y0[3], "ricerca delta minimo for lambda4");
    draw_parable("Data/parable5.txt", "Graphs/sampling5.png", y0[4], "ricerca delta minimo for lambda5");
    cout<<"VERTEX first parable"<<y0[0][0]<<y0[0][1]<<endl;

    ofstream data_file_method2;//su cui scrivo

    double n2[P][2];
    
    data_file_method2.open("Data/lambda_indexes2.txt", ios::out);


//inizialization of n and filling the data_file
    data_file_method2<<"#lambdaAr\t\t index n\t dev_n"<<endl;
    double derivative_delta;

    for(int i = 0; i<P; i++){
        n2[i][0] = sin((y0[i][0]+alpha)/2.)/sin(alpha/2.);
        derivative_delta = cos((y0[i][0]+alpha)/2.)/(2.*sin(alpha/2.));
        n2[i][1] = derivative_delta*y0[i][1];
        cout<<"lambda[i]: "<<lambda[i]<<endl;
        data_file_method2<<lambda[i]<<"\t\t\t"<<n2[i][0]<<"\t\t"<<n2[i][1]<<endl;
    }

//creation of a TGrapherrors
    TCanvas* c3 = new TCanvas();

    TGraphErrors *ge2 = new  TGraphErrors("Data/lambda_indexes2.txt" , "%lg %lg %lg"); // P = number of points
    ge2->SetTitle("n in funzione di lambda con Metodo2");
    ge2->GetXaxis()->SetTitle("lambda[nm]");
    ge2->GetYaxis()->SetTitle("indice n");
    ge2->SetMarkerStyle(20);
    ge2->Draw("AP");

//creation of a TF1
    double A2[2];
    double B2[2];
    TF1 *f2 = new TF1("hyperbole", "[0]+[1]*(1/x)^{2}");
    ge2->Fit("hyperbole");
    gStyle->SetOptFit(1);

    ge2->Draw("AP");
    c3->Print ("Graphs/Cauchy_coeff_method2.png", "png") ;

 
    TFitResult results2;
    results2.Print();
    TFitResultPtr point2 = ge2->Fit("hyperbole", "S");
    TMatrixD cov2 = point2->GetCovarianceMatrix();
    A2[0] = f2->GetParameter(0);  
    A2[1] = f2->GetParError(0);  
    cout<<"A2:"<<A2[0]<<"+/-"<<A2[1]<<endl;
    B2[0] = f2->GetParameter(1)/1000000;
    B2[1] = f2->GetParError(1)/1000000;  
    cout<<"B2:"<<B2[0]<<"+/-"<<B2[1]<<"mu m"<<endl;

    cov2.Print();
    double covariance2 = -0.7058*pow(10, -6);
    double lambdaUV = 0.1;//in micrometri
    double lambdaVerde = 0.5600;//in micrometri
    double lambdaIR = pow(10, 2);//in micrometri

//CALCULATION of refraction index n for UV
    double nUV[2];
    cout<<lambdaUV<<endl;
    nUV[0] = A2[0] + B2[0]/(lambdaUV*lambdaUV);
    nUV[1] = sqrt( pow(A2[1], 2) + pow( B2[1]/(pow(lambdaUV, 2)) , 2) + 2*covariance2/(lambdaUV*lambdaUV) ) ;
    cout<<"refraction idex for UV: "<<nUV[0]<<"+/-"<<nUV[1]<<endl;

//CALCULATION of refraction index n for V

    double nV[2];
    cout<<lambdaVerde<<endl;
    nV[0] = A2[0] + B2[0]/(lambdaVerde*lambdaVerde);
    cout<<"pow(A2[1], 2): "<<pow(A2[1], 2)<<endl;
    cout<<"pow( B2[1]/(pow(lambdaVerde, 2)) , 2): "<<pow( B2[1]/(pow(lambdaVerde, 2)) , 2)<<endl;
    cout<<"2*covariance2/(lambdaVerde*lambdaVerde): "<<2*covariance2/(lambdaVerde*lambdaVerde)<<endl;
    nV[1] = sqrt( pow(A2[1], 2) + pow( B2[1]/(pow(lambdaVerde, 2)) , 2) + 2*covariance2/(lambdaVerde*lambdaVerde) ) ;
    cout<<"refraction idex for Verde: "<<nV[0]<<"+/-"<<nV[1]<<endl;


//CALCULATION of refraction index n for IR

    double nIR[2];
    cout<<lambdaIR<<endl;
    nIR[0] = A2[0] + B2[0]/(lambdaIR*lambdaIR);
    cout<<"pow(A2[1], 2) : "<<pow(A2[1], 2) <<endl;
    cout<<"pow( B2[1]/(pow(lambdaIR, 2)) , 2): "<<pow( B2[1]/(pow(lambdaIR, 2)) , 2)<<endl;
    cout<<"2*covariance2/(lambdaIR*lambdaIR) : "<<2*covariance2/(lambdaIR*lambdaIR) <<endl;
    nIR[1] = sqrt( pow(A2[1], 2) + pow( B2[1]/(pow(lambdaIR, 2)) , 2) + 2*covariance2/(lambdaIR*lambdaIR) ) ;
    cout<<"refraction idex for IR: "<<nIR[0]<<"+/-"<<nIR[1]<<endl;

    //TheApp.Run();

    return 0;
}