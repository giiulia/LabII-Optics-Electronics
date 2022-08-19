//c++ -o prisma_virtuale prisma_virtuale.cpp `root-config --glibs --cflags`
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

void leggo_file_Hg(ifstream& file_angoli, double* alpha, double* base, double* lambda, double delta[][2]){


    double angolo, dev_media;

    int i = 0;
    string line;

    getline(file_angoli, line);
    istringstream issL(line);
    if (issL>>lambda[0]>>lambda[1]>>lambda[2]>>lambda[3]>>lambda[4]){ //se va bene lo legge altrimenti no
        //cout << "Ho letto: " <<lambda[0]<<", "<<lambda[1]<<", "<<lambda[2]<<", "<<lambda[3]<<", "<<lambda[4]<<endl;
    }

    getline(file_angoli, line);
    istringstream issA(line);
    if (issA>>*alpha){ //se va bene lo legge altrimenti no
        //cout << "Ho letto: "<<*alpha<<endl;

    }

    getline(file_angoli, line);
    istringstream issB(line);
    if (issB>>*base){ //se va bene lo legge altrimenti no
        //cout << "Ho letto: "<<*base<<endl;

    }

    while(getline(file_angoli, line) && i<5) {
        istringstream issD(line);
        if (issD >> angolo >> dev_media) { //se va bene lo legge altrimenti no

            //cout << "Ho letto " << angolo << ", " << dev_media << endl;

            delta[i][0] = angolo;
            delta[i][1] = dev_media;
            ++i;
        }
    }
    

}
    
void disegna_parabola(const char* file_dati, const char* file_immagine, double* y0, const char* titolo){
    TCanvas *c2 = new TCanvas();
    gStyle->SetCanvasDefH(400);
    gStyle->SetCanvasDefW(700);
    TGraphErrors *pt = new  TGraphErrors( file_dati, "%lg %lg %lg"); // P=numero di punti
    pt->SetTitle(titolo);
    pt->GetXaxis()->SetTitle("theta [rad]");
    pt->GetYaxis()->SetTitle("delta [rad]");
    pt->SetMarkerStyle(20);
    pt->Draw("AP");

    TF1 *p = new TF1("parabola", "[0]*x^{2} + [1]*x + [2]", 0.8, 0.85); //nome dell'oggetto, xmin, xmax y = yV+a*(x-xV)^2
    c2->cd();
    pt->Draw("AP");
    pt->Fit("parabola");   
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

    c2->Print (file_immagine, "png") ;
    delete c2;

}



int main(int argc, char* argv[]){
    gStyle->SetOptFit(1112);

    TApplication TheApp("theApp", &argc, argv);

    ifstream file_Hg;//da cui leggo
    ofstream file_dati;//su cui scrivo

    int P = 5;

    double alpha;
    double base;
    double lambda[5];
    double delta[P][2];

    double n[P][2];

    file_Hg.open("delta_min.txt", ios::in);

    file_dati.open("lambda_indici.txt", ios::out);

    
    leggo_file_Hg(file_Hg, &alpha, &base, lambda, delta);
    file_Hg.close();

//inizializzo n e riempio il file_dati
    file_dati<<"#lambdaHg\t\tindice n\tdev_n"<<endl;
    cout<<"alpha"<<alpha<<endl;
    double derivata_alpha, derivata_delta;
    for(int i = 0; i<P; i++){
        n[i][0] = sin((delta[i][0]+alpha)/2.)/sin(alpha/2.);
        derivata_delta = cos((delta[i][0]+alpha)/2.)/(2.*sin(alpha/2.));
        n[i][1] = derivata_delta*delta[i][1];
        file_dati<<lambda[i]<<"\t\t\t"<<n[i][0]<<"\t\t"<<n[i][1]<<endl;
    }

//creo un TGrapherrors
    TCanvas* c1 = new TCanvas();

    TGraphErrors *ge = new  TGraphErrors("lambda_indici.txt" , "%lg %lg %lg"); // P=numero di punti
    ge->SetTitle("n in funzione di lambda da lambda_indici.txt");
    ge->GetXaxis()->SetTitle("lambda");
    ge->GetYaxis()->SetTitle("indice n");
    ge->SetMarkerStyle(20);
    ge->Draw("AP");

//creo un TF1
    double A[2];
    double B[2];
    TF1 *f = new TF1("iperbole", "[0]+[1]*(1/x)^{2}", 400, 700); //nome dell'oggetto, xmin, xmax
    ge->Fit("iperbole");
    gStyle->SetOptFit(1);

    ge->Draw("AP");
    c1->Print ("grafico1.png", "png") ;

 
    TFitResult results;
    results.Print();
    TFitResultPtr point = ge->Fit("iperbole", "S");
    TMatrixD cov = point->GetCovarianceMatrix();
    A[0] = f->GetParameter(0);  
    cout<<"B:"<<B[0]<<endl;
    B[0] = f->GetParameter(1);
    cout<<"A:"<<A[0]<<endl;
   

    cov.Print();

    delete c1;

//METODO DELLA PARABOLA
    double y0[P][2]; 
    disegna_parabola("metodo2/parabola1.txt", "metodo2/campionamento1.png", y0[0], "ricerca delta minimo per lambda1");
    disegna_parabola("metodo2/parabola2.txt", "metodo2/campionamento2.png", y0[1], "ricerca delta minimo per lambda2");
    disegna_parabola("metodo2/parabola3.txt", "metodo2/campionamento3.png", y0[2], "ricerca delta minimo per lambda3");
    disegna_parabola("metodo2/parabola4.txt", "metodo2/campionamento4.png", y0[3], "ricerca delta minimo per lambda4");
    disegna_parabola("metodo2/parabola5.txt", "metodo2/campionamento5.png", y0[4], "ricerca delta minimo per lambda5");
    cout<<"VERTICE prima parabola"<<y0[0][0]<<y0[0][1]<<endl;

    ofstream file_dati_metodo2;//su cui scrivo

    double n2[P][2];
    
    file_dati_metodo2.open("lambda_indici2.txt", ios::out);


//inizializzo n e riempio il file_dati
    file_dati_metodo2<<"#lambdaAr\t\tindice n\tdev_n"<<endl;
    for(int i = 0; i<P; i++){
        n2[i][0] = sin((y0[i][0]+alpha)/2.)/sin(alpha/2.);
        derivata_delta = cos((y0[i][0]+alpha)/2.)/(2.*sin(alpha/2.));
        n2[i][1] = derivata_delta*y0[i][1];
        cout<<"lambda[i]: "<<lambda[i]<<endl;
        file_dati_metodo2<<lambda[i]<<"\t\t\t"<<n2[i][0]<<"\t\t"<<n2[i][1]<<endl;
    }

//creo un TGrapherrors
    TCanvas* c3 = new TCanvas();

    TGraphErrors *ge2 = new  TGraphErrors("lambda_indici2.txt" , "%lg %lg %lg"); // P=numero di punti
    ge2->SetTitle("n in funzione di lambda con Metodo2");
    ge2->GetXaxis()->SetTitle("lambda[nm]");
    ge2->GetYaxis()->SetTitle("indice n");
    ge2->SetMarkerStyle(20);
    ge2->Draw("AP");

//creo un TF1
    double A2[2];
    double B2[2];
    TF1 *f2 = new TF1("iperbole", "[0]+[1]*(1/x)^{2}"); //nome dell'oggetto, xmin, xmax
    ge2->Fit("iperbole");
    gStyle->SetOptFit(1);

    ge2->Draw("AP");
    c3->Print ("grafico2.png", "png") ;

 
    TFitResult results2;
    results2.Print();
    TFitResultPtr point2 = ge2->Fit("iperbole", "S");
    TMatrixD cov2 = point2->GetCovarianceMatrix();
    A2[0] = f2->GetParameter(0);  
    A2[1] = f2->GetParError(0);  
    cout<<"A2:"<<A2[0]<<"+/-"<<A2[1]<<endl;
    B2[0] = f2->GetParameter(1)/1000000;
    B2[1] = f2->GetParError(1)/1000000;  
    cout<<"B2:"<<B2[0]<<"+/-"<<B2[1]<<"mu m"<<endl;

    cov2.Print();
    double covarianza2 = -0.7058*pow(10, -6);
    double lambdaUV = 0.1;//in micrometri
    double lambdaVerde = 0.5600;//in micrometri
    double lambdaIR = pow(10, 2);//in micrometri

//CALCOLO DI n per UV
    double nUV[2];
    cout<<lambdaUV<<endl;
    nUV[0] = A2[0] + B2[0]/(lambdaUV*lambdaUV);
    nUV[1] = sqrt( pow(A2[1], 2) + pow( B2[1]/(pow(lambdaUV, 2)) , 2) + 2*covarianza2/(lambdaUV*lambdaUV) ) ;
    cout<<"indice di rifrazione per UV: "<<nUV[0]<<"+/-"<<nUV[1]<<endl;

//CALCOLO DI n per V

    double nV[2];
    cout<<lambdaVerde<<endl;
    nV[0] = A2[0] + B2[0]/(lambdaVerde*lambdaVerde);
    cout<<"pow(A2[1], 2): "<<pow(A2[1], 2)<<endl;
    cout<<"pow( B2[1]/(pow(lambdaVerde, 2)) , 2): "<<pow( B2[1]/(pow(lambdaVerde, 2)) , 2)<<endl;
    cout<<"2*covarianza2/(lambdaVerde*lambdaVerde): "<<2*covarianza2/(lambdaVerde*lambdaVerde)<<endl;
    nV[1] = sqrt( pow(A2[1], 2) + pow( B2[1]/(pow(lambdaVerde, 2)) , 2) + 2*covarianza2/(lambdaVerde*lambdaVerde) ) ;
    cout<<"indice di rifrazione per Verde: "<<nV[0]<<"+/-"<<nV[1]<<endl;


//CALCOLO DI n perIR

    double nIR[2];
    cout<<lambdaIR<<endl;
    nIR[0] = A2[0] + B2[0]/(lambdaIR*lambdaIR);
    cout<<"pow(A2[1], 2) : "<<pow(A2[1], 2) <<endl;
    cout<<"pow( B2[1]/(pow(lambdaIR, 2)) , 2): "<<pow( B2[1]/(pow(lambdaIR, 2)) , 2)<<endl;
    cout<<"2*covarianza2/(lambdaIR*lambdaIR) : "<<2*covarianza2/(lambdaIR*lambdaIR) <<endl;
    nIR[1] = sqrt( pow(A2[1], 2) + pow( B2[1]/(pow(lambdaIR, 2)) , 2) + 2*covarianza2/(lambdaIR*lambdaIR) ) ;
    cout<<"indice di rifrazione per IR: "<<nIR[0]<<"+/-"<<nIR[1]<<endl;

    //TheApp.Run();

    return 0;
}