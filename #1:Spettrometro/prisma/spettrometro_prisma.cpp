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

void leggo_file_Hg(ifstream& file_angoli, double *alpha, double*base, double* lambda, double delta[][2], double ignoto[][2]){


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
    if (issA>>alpha[0]>>alpha[1]){ //se va bene lo legge altrimenti no
        cout << "Ho letto: "<<alpha[0]<<", "<<alpha[1]<<endl;
        alpha[0] = 3.14159 - alpha[0]; //angolo al vertice
        cout<<alpha[0]<<endl;

    }

    getline(file_angoli, line);
    istringstream issB(line);
    if (issB>>base[0]>>base[1]){ //se va bene lo legge altrimenti no
        //cout << "Ho letto: "<<base[0]<<", "<<base[1]<<endl;

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
    
void leggo_file_gasIgnoto(ifstream& file_angoli, double ignoto[][2]){
    int i = 0;
    double angolo, dev_media;

    string line;
    while(getline(file_angoli, line) && i<6) {
        istringstream issD(line);
        if (issD >> angolo >> dev_media) { //se va bene lo legge altrimenti no

            cout << "Ho letto " << angolo << ", " << dev_media << endl;

            ignoto[i][0] = angolo;
            ignoto[i][1] = dev_media;
            ++i;
        }
    }
}

int main(int argc, char* argv[]){
    TApplication TheApp("theApp", &argc, argv);
    ifstream file_Hg;
    ifstream file_gasIgnoto;

    ofstream file_dati;

    int P = 5;

    double alpha[2];
    double base[2];
    double lambda[P];
    double delta[P][2];
    double ignoto[6][2];

    double n[P][2];
    double lambdaIgnota[6][2];

    file_Hg.open("delta_min.txt", ios::in);
    file_gasIgnoto.open("gas_ignoto.txt", ios::in);

    file_dati.open("lambda_indici.txt", ios::out);

    
    leggo_file_Hg(file_Hg, alpha, base, lambda, delta, ignoto);
    cout<<base[0]<<"\t"<<base[1]<<endl;
    file_Hg.close();
    leggo_file_gasIgnoto(file_gasIgnoto, ignoto);
    file_Hg.close();



//inizializzo n e riempio il file_dati
    file_dati<<"#lambdaHg\t\tindice n\tdev_n"<<endl;

    double derivata_alpha, derivata_delta;
    for(int i = 0; i<P; i++){
        n[i][0] = sin((delta[i][0]+alpha[0])/2.)/sin(alpha[0]/2.);
        derivata_alpha = pow( ( cos( (alpha[0]+delta[i][0] )/2. ) - ( cos(alpha[0]/2.)/sin(alpha[0]/2.) )*sin( (alpha[0]+delta[i][0] )/2.) )/sin(alpha[0]/2.)*2., 2.);
        derivata_delta = pow( cos((delta[i][0]+alpha[0])/2.)/(2.*sin(alpha[0]/2.)), 2. );
        n[i][1] = sqrt( derivata_alpha* alpha[1]*alpha[1] + derivata_delta*delta[i][1]*delta[i][1]);
        file_dati<<lambda[i]<<"\t\t"<<n[i][0]<<"\t\t"<<n[i][1]<<endl;
    }

//creo un TGrapherrors
    TCanvas* c1 = new TCanvas();

    TGraphErrors *ge = new  TGraphErrors("lambda_indici.txt" , "%lg %lg %lg"); // P=numero di punti
    ge->SetTitle("n in funzione di lambda ottenuto con il Metodo 1");
    ge->GetXaxis()->SetTitle("lunghezza d'onda [nm]");
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
    B[0] = f->GetParameter(1);
    cout<<"A:"<<A[0]<<endl;
    cout<<"B:"<<B[0]<<endl;

    A[1] = 0.005473;
    B[1] = 1274;

    cov.Print();

    delete c1;

//aggiungo le lunghezze d'onda ipotizzate
    file_dati<<"#GAS IGNOTO"<<endl;
    file_dati<<"#indice n\tdev_n\t\tipotesi di lambda"<<endl;
    
    double derivata_alpha2, derivata_delta2;
    double derivata_B, derivata_A, derivata_n, covarianza;
    for(int i = 0; i<6; i++){

        n[i][0] = sin((ignoto[i][0]+alpha[0])/2.)/sin(alpha[0]/2.);
        derivata_alpha2 = pow( ( cos( (alpha[0]+ignoto[i][0] )/2. ) - ( cos(alpha[0]/2.)/sin(alpha[0]/2.) )*sin( (alpha[0]+ignoto[i][0] )/2.) )/sin(alpha[0]/2.)*2., 2.);
        derivata_delta2 = pow( cos((ignoto[i][0]+alpha[0])/2.)/(2.*sin(alpha[0]/2.)), 2. );
        n[i][1] = sqrt( derivata_alpha2* alpha[1]*alpha[1] + derivata_delta2*ignoto[i][1]*ignoto[i][1]);
        cout<<"n:"<<n[i][0]<<n[i][1]<<endl;

        lambdaIgnota[i][0] = sqrt( B[0]/( n[i][0]-A[0]) );
        derivata_n = -pow( -B[0]/(A[0]-n[i][0]), 3/2)/( 2*B[0] );
        //cout<<derivata_n<<endl;
        derivata_A = B[0]/( 2*pow(n[i][0]-A[0], 2)*sqrt(B[0]/( n[i][0]-A[0] )) );
        //cout<<derivata_A<<endl;
        derivata_B = sqrt(-B[0]/(A[0]-n[i][0]))/( 2*B[0] );
        //cout<<derivata_B<<endl;

        covarianza = -6.655;
        lambdaIgnota[i][1] = sqrt( derivata_n*derivata_n*n[i][1]*n[i][1] + derivata_A*derivata_A*A[1]*A[1]  + derivata_B*derivata_B*B[1]*B[1] + derivata_A*derivata_B*2*covarianza);
    }
    for(int i = 0; i<6; i++){
        file_dati<<n[i][0]<<"\t\t"<<n[i][1]<<"\t"<<lambdaIgnota[i][0]<<"\t\t"<<lambdaIgnota[i][1]<<endl;
    }

//METODO DELLA PARABOLA
    
    TCanvas *c2 = new TCanvas();
    double y0;
    double Errory0;

    TGraphErrors *pt = new  TGraphErrors("metodo2/punti.txt" , "%lg %lg %lg"); // P=numero di punti
    pt->SetTitle("campionamento intorno all'angolo minimo");
    pt->GetXaxis()->SetTitle("punti");
    pt->GetYaxis()->SetTitle("theta[rad]");
    pt->SetMarkerStyle(20);
    pt->Draw("AP");

    TF1 *p = new TF1("parabola", "[0]+[1]*(x-[2])^2", 0.8, 0.5); //nome dell'oggetto, xmin, xmax y = yV+a*(x-xV)^2
    gStyle->SetOptFit(1);
    pt->Fit("parabola");
    pt->Draw("AP");

    y0 = p->GetParameter(0);   
    Errory0 = p->GetParError(0);
    cout<<"ordinata vertice ed errore: "<<y0<<"p.m."<<Errory0<<endl;

    c2->Print ("metodo2/campionamento.png", "png") ;


//POTERE RISOLUTIVO
    TCanvas *c3 = new TCanvas();

    double R[P][2];
    double mediaR = 0;
    double sommaPesi= 0;
    double errMedia = 0;
    cout<<"base[0]"<<base[0]<<endl;
    cout<<"lambda[0]"<<lambda[0]<<endl;

    for(int i = 0; i<P; i++){
        R[i][0] = B[0]*2*base[0]*pow(10, 9)/pow(lambda[i], 3);
        R[i][1] = (2*base[0]*pow(10, 9)/pow(lambda[i], 3))*B[1];
        cout<<"potere risolutivo: "<<R[i][0]<<" "<<R[i][1]<<endl;
        mediaR = mediaR + ( R[i][0]/pow(R[i][1], 2) );
        sommaPesi = sommaPesi + (1/pow(R[i][1], 2));
    }
    mediaR = mediaR/sommaPesi;
    errMedia = sqrt(1/sommaPesi);
    cout<<"mediaR: "<<mediaR<<" "<<errMedia<<endl;

    TF1 *r = new TF1("potere risolutivo","0.048*10^(9)*2*7547/x^3", 100., 700.);
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
    c3->Print("potere_risolutivo.png", "png");

    TheApp.Run();

    delete c1;
    delete c2;
    return 0;
}