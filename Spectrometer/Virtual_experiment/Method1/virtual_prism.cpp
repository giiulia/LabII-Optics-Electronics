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

void read_Ar_file(ifstream& file_angles, double* alpha, double* base, double* lambda, double delta[][2]){


    double angle, dev_media;

    int i = 0;
    string line;

    getline(file_angles, line);
    istringstream issL(line);
    if (issL>>lambda[0]>>lambda[1]>>lambda[2]>>lambda[3]>>lambda[4]){ //if its ok reads otherwise not
        //cout << "Read: " <<lambda[0]<<", "<<lambda[1]<<", "<<lambda[2]<<", "<<lambda[3]<<", "<<lambda[4]<<endl;
    }

    getline(file_angles, line);
    istringstream issA(line);
    if (issA>>*alpha){ //se va bene lo legge altrimenti no
        //cout << "Read: "<<*alpha<<endl;

    }

    getline(file_angles, line);
    istringstream issB(line);
    if (issB>>*base){ //se va bene lo legge altrimenti no
        //cout << "Read: "<<*base<<endl;

    }

    while(getline(file_angles, line) && i<5) {
        istringstream issD(line);
        if (issD >> angle >> dev_media) { //se va bene lo legge altrimenti no

            //cout << "Read " << angle << ", " << dev_media << endl;

            delta[i][0] = angle;
            delta[i][1] = dev_media;
            ++i;
        }
    }
    

}


int main(int argc, char* argv[]){
    gStyle->SetOptFit(1112);

    TApplication TheApp("theApp", &argc, argv);

    ifstream file_Ar;
    ofstream data_file;

    int P = 5;

    double alpha;
    double base;
    double lambda[5];
    double delta[P][2];

    double n[P][2];

    file_Ar.open("min_delta.txt", ios::in);

    data_file.open("lambda_indexes.txt", ios::out);

    read_Ar_file(file_Ar, &alpha, &base, lambda, delta);
    file_Ar.close();

//inizialize n and fill the data_file
    data_file<<"#lambdaAr\t\t index n\tdev_n"<<endl;
    cout<<"alpha"<<alpha<<endl;
    double derivata_delta;
    for(int i = 0; i<P; i++){
        n[i][0] = sin((delta[i][0]+alpha)/2.)/sin(alpha/2.);
        derivata_delta = cos((delta[i][0]+alpha)/2.)/(2.*sin(alpha/2.));
        n[i][1] = derivata_delta*delta[i][1];
        data_file<<lambda[i]<<"\t\t\t"<<n[i][0]<<"\t\t"<<n[i][1]<<endl;
    }

//create a TGrapherrors
    TCanvas* c1 = new TCanvas();

    TGraphErrors *ge = new  TGraphErrors("lambda_indexes.txt" , "%lg %lg %lg"); // P=numero di punti
    ge->SetTitle("n in funzione di lambda da lambda_indici.txt");
    ge->GetXaxis()->SetTitle("lambda");
    ge->GetYaxis()->SetTitle("indice n");
    ge->SetMarkerStyle(20);
    ge->Draw("AP");

//create a TF1
    double A[2];
    double B[2];
    TF1 *f = new TF1("hyperbole", "[0]+[1]*(1/x)^{2}", 400, 700); //nome dell'oggetto, xmin, xmax
    ge->Fit("hyperbole");
    gStyle->SetOptFit(1);

    ge->Draw("AP");
    c1->Print ("Cauchy_coeff_method1.png", "png") ;

 
    TFitResult results;
    results.Print();
    TFitResultPtr point = ge->Fit("hyperbole", "S");
    TMatrixD cov = point->GetCovarianceMatrix();
    A[0] = f->GetParameter(0);  
    cout<<"B:"<<B[0]<<endl;
    B[0] = f->GetParameter(1);
    cout<<"A:"<<A[0]<<endl;
   

    cov.Print();

    delete c1;

    return 0;
}