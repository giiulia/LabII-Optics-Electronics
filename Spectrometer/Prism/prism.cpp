//c++ -o spettrometro_prisma spettrometro_prisma.cpp `root-config --glibs --cflags`

#include <iostream>
#include <fstream> 
#include <sstream> 
#include <string> 
#include <cmath>
#include <math.h>

#include <TROOT.h>
#include "TStyle.h"

#include "TF1.h"
#include "TFitResult.h"
#include "TMatrixD.h"
#include "TGraphErrors.h"
#include "TAxis.h"
#include "TApplication.h"
#include "TGraph.h"
#include "TCanvas.h"

using namespace std;

void read_file_Hg(ifstream& angles_file, double *alpha, double*base, double* lambda, double delta[][2], double ignote[][2]){


    double angle, dev_mean;

    int i = 0;
    string line;

    getline(angles_file, line);
    istringstream issL(line);
    if (issL>>lambda[0]>>lambda[1]>>lambda[2]>>lambda[3]>>lambda[4]){ //if its ok read, otherwise not
        //cout << "Read: " <<lambda[0]<<", "<<lambda[1]<<", "<<lambda[2]<<", "<<lambda[3]<<", "<<lambda[4]<<endl;
    }

    getline(angles_file, line);
    istringstream issA(line);
    if (issA>>alpha[0]>>alpha[1]){ //if its ok read, otherwise not
        cout << "Read: "<<alpha[0]<<", "<<alpha[1]<<endl;
        alpha[0] = 3.14159 - alpha[0]; //angle al vertice
        cout<<alpha[0]<<endl;

    }

    getline(angles_file, line);
    istringstream issB(line);
    if (issB>>base[0]>>base[1]){ //if its ok read, otherwise not
        //cout << "Read: "<<base[0]<<", "<<base[1]<<endl;

    }

    while(getline(angles_file, line) && i<5) {
        istringstream issD(line);
        if (issD >> angle >> dev_mean) { //if its ok read, otherwise not

            //cout << "Read " << angle << ", " << dev_mean << endl;

            delta[i][0] = angle;
            delta[i][1] = dev_mean;
            ++i;
        }
    }
    

}
    
void read_IgnoteGas_file(ifstream& angles_file, double ignote[][2]){
    int i = 0;
    double angle, dev_mean;

    string line;
    while(getline(angles_file, line) && i<6) {
        istringstream issD(line);
        if (issD >> angle >> dev_mean) { //se va bene lo legge altrimenti no

            cout << "Read " << angle << ", " << dev_mean << endl;

            ignote[i][0] = angle;
            ignote[i][1] = dev_mean;
            ++i;
        }
    }
}

int main(int argc, char* argv[]){
    TApplication TheApp("theApp", &argc, argv);
    ifstream Hg_file;
    ifstream IgnoteGas_file;

    ofstream file_data;

    int P = 5;

    double alpha[2];
    double base[2];
    double lambda[P];
    double delta[P][2];
    double ignote[6][2];

    double n[P][2];
    double lambdaIgnote[6][2];

    Hg_file.open("min_delta.txt", ios::in);
    IgnoteGas_file.open("ignote_gas.txt", ios::in);

    file_data.open("lambda_indexes.txt", ios::out);

    
    read_file_Hg(Hg_file, alpha, base, lambda, delta, ignote);
    cout<<base[0]<<"\t"<<base[1]<<endl;
    Hg_file.close();
    read_IgnoteGas_file(IgnoteGas_file, ignote);
    Hg_file.close();



//inizializzo n e riempio il file_data
    file_data<<"#lambdaHg\t\t index n \t dev_n"<<endl;

    double derivative_alpha, derivative_delta;
    for(int i = 0; i<P; i++){
        n[i][0] = sin((delta[i][0]+alpha[0])/2.)/sin(alpha[0]/2.);
        derivative_alpha = pow( ( cos( (alpha[0]+delta[i][0] )/2. ) - ( cos(alpha[0]/2.)/sin(alpha[0]/2.) )*sin( (alpha[0]+delta[i][0] )/2.) )/sin(alpha[0]/2.)*2., 2.);
        derivative_delta = pow( cos((delta[i][0]+alpha[0])/2.)/(2.*sin(alpha[0]/2.)), 2. );
        n[i][1] = sqrt( derivative_alpha* alpha[1]*alpha[1] + derivative_delta*delta[i][1]*delta[i][1]);
        file_data<<lambda[i]<<"\t\t"<<n[i][0]<<"\t\t"<<n[i][1]<<endl;
    }

//creo un TGrapherrors
    TCanvas* c1 = new TCanvas();

    TGraphErrors *ge = new  TGraphErrors("lambda_indexes.txt" , "%lg %lg %lg"); // P=numero di punti
    ge->SetTitle("n in funzione di lambda ottenuto con il Metodo 1");
    ge->GetXaxis()->SetTitle("lunghezza d'onda [nm]");
    ge->GetYaxis()->SetTitle("indice n");
    ge->SetMarkerStyle(20);
    ge->Draw("AP");

//creo un TF1
    double A[2];
    double B[2];
    TF1 *f = new TF1("hyperbole", "[0]+[1]*(1/x)^{2}", 400, 700); //nome dell'oggetto, xmin, xmax
    ge->Fit("hyperbole");
    gStyle->SetOptFit(1);

    ge->Draw("AP");
    c1->Print ("Graphs/Cauchy_coefficients.png", "png") ;

 
    TFitResult results;
    results.Print();
    TFitResultPtr point = ge->Fit("hyperbole", "S");
    TMatrixD cov = point->GetCovarianceMatrix();
    A[0] = f->GetParameter(0);  
    B[0] = f->GetParameter(1);
    cout<<"A:"<<A[0]<<endl;
    cout<<"B:"<<B[0]<<endl;

    A[1] = 0.005473;
    B[1] = 1274;

    cov.Print();

    delete c1;

//aggiungo le lunghezze d'onda ipotizzate
    file_data<<"#GAS IGNOTE"<<endl;
    file_data<<"#index n\tdev_n\t\thypotesis of lambda"<<endl;
    
    double derivative_alpha2, derivative_delta2;
    double derivative_B, derivative_A, derivative_n, covarianza;
    for(int i = 0; i<6; i++){

        n[i][0] = sin((ignote[i][0]+alpha[0])/2.)/sin(alpha[0]/2.);
        derivative_alpha2 = pow( ( cos( (alpha[0]+ignote[i][0] )/2. ) - ( cos(alpha[0]/2.)/sin(alpha[0]/2.) )*sin( (alpha[0]+ignote[i][0] )/2.) )/sin(alpha[0]/2.)*2., 2.);
        derivative_delta2 = pow( cos((ignote[i][0]+alpha[0])/2.)/(2.*sin(alpha[0]/2.)), 2. );
        n[i][1] = sqrt( derivative_alpha2* alpha[1]*alpha[1] + derivative_delta2*ignote[i][1]*ignote[i][1]);
        cout<<"n:"<<n[i][0]<<n[i][1]<<endl;

        lambdaIgnote[i][0] = sqrt( B[0]/( n[i][0]-A[0]) );
        derivative_n = -pow( -B[0]/(A[0]-n[i][0]), 3/2)/( 2*B[0] );
        //cout<<derivative_n<<endl;
        derivative_A = B[0]/( 2*pow(n[i][0]-A[0], 2)*sqrt(B[0]/( n[i][0]-A[0] )) );
        //cout<<derivative_A<<endl;
        derivative_B = sqrt(-B[0]/(A[0]-n[i][0]))/( 2*B[0] );
        //cout<<derivative_B<<endl;

        covarianza = -6.655;
        lambdaIgnote[i][1] = sqrt( derivative_n*derivative_n*n[i][1]*n[i][1] + derivative_A*derivative_A*A[1]*A[1]  + derivative_B*derivative_B*B[1]*B[1] + derivative_A*derivative_B*2*covarianza);
    }
    for(int i = 0; i<6; i++){
        file_data<<n[i][0]<<"\t\t"<<n[i][1]<<"\t"<<lambdaIgnote[i][0]<<"\t\t"<<lambdaIgnote[i][1]<<endl;
    }

//PARABOLE METHOD (green)
    
    TCanvas *c2 = new TCanvas();
    double y0;
    double Errory0;

    TGraphErrors *pt = new  TGraphErrors("points.txt" , "%lg %lg %lg"); // P=numero di punti
    pt->SetTitle("campionamento intorno all'angolo minimo");
    pt->GetXaxis()->SetTitle("punti");
    pt->GetYaxis()->SetTitle("theta[rad]");
    pt->SetMarkerStyle(20);
    pt->Draw("AP");

    TF1 *p = new TF1("parabole", "[0]+[1]*(x-[2])^2", 0.8, 0.5); //nome dell'oggetto, xmin, xmax y = yV+a*(x-xV)^2
    gStyle->SetOptFit(1);
    pt->Fit("parabole");
    pt->Draw("AP");

    y0 = p->GetParameter(0);   
    Errory0 = p->GetParError(0);
    cout<<"vertex ordinate and error: "<<y0<<"p.m."<<Errory0<<endl;

    c2->Print ("Graphs/parabole.png", "png") ;


//RESOLUTIVE POWER
    TCanvas *c3 = new TCanvas();

    double R[P][2];
    double meanR = 0;
    double sumWeights= 0;
    double errMean = 0;
    cout<<"base[0]"<<base[0]<<endl;
    cout<<"lambda[0]"<<lambda[0]<<endl;

    for(int i = 0; i<P; i++){
        R[i][0] = B[0]*2*base[0]*pow(10, 9)/pow(lambda[i], 3);
        R[i][1] = (2*base[0]*pow(10, 9)/pow(lambda[i], 3))*B[1];
        cout<<"potere risolutivo: "<<R[i][0]<<" "<<R[i][1]<<endl;
        meanR = meanR + ( R[i][0]/pow(R[i][1], 2) );
        sumWeights = sumWeights + (1/pow(R[i][1], 2));
    }
    meanR = meanR/sumWeights;
    errMean = sqrt(1/sumWeights);
    cout<<"meanR: "<<meanR<<" "<<errMean<<endl;

    TF1 *r = new TF1("resolutive_power","0.048*10^(9)*2*7547/x^3", 100., 700.);
    TGraphErrors *re = new TGraphErrors(P);

    for(int i = 0; i<P; i++){
        re->SetPoint(i, lambda[i], R[i][0]);
        re->SetPointError(i, 0., R[i][1]);
    }
    r->SetTitle("R(x) = LB/x^{3}");


    r->GetXaxis()->SetTitle("lambda[nm]");
    r->GetYaxis()->SetTitle("potere risolutivo");


    //gROOT->SetStyle("Plain");
    c3->UseCurrentStyle();
    gROOT->ForceStyle();

    gStyle->SetOptStat(0);
    gStyle->SetTitleBorderSize(0);
    gStyle->SetTitleSize(0.035);
    gStyle->SetTitleFont(50, "hxy");      // for histogram and axis titles
    gStyle->SetLabelFont(50, "xyz");      // for axis labels (values)
    gStyle->SetLabelSize(0.97);      // for axis labels (values)

    gROOT->ForceStyle();


    ///re->Draw("AP");
    r->Draw();
    gPad->Modified();
    gPad->Update();

    c3->SetGrid(1, 1);
    c3->Print("Graphs/resolutive_power.png", "png");

    TheApp.Run();

    delete c1;
    delete c2;
    return 0;
}