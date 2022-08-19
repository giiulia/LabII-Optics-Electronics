#include <iostream>
#include <cmath>
#include <fstream>

#include "TCanvas.h"
#include "TH1F.h"
#include "TApplication.h"
#include "TF1.h"
#include "TGraphErrors.h"
#include "TFitResult.h"
#include "TPaveStats.h"
#include "TStyle.h"

#include "dati_circuiti1.h"
#include "stats.h"

using namespace std;
int main(int argc, char*argv[]){
//  ESPERIMENTO1: RESISTENZA VOLTMETRO
    cout<<"ESPERIMENTO1: RESISTENZA VOLTMETRO"<<endl;
    double i_media1[4][2];
    int size1 = (int) (sizeof(V_1)/sizeof(V_1[0]));

    double R_eq1[4][2];
    double R_V1[4][2];

    for(int i = 0; i<size1; i++){
        media_stdm(I_1[i], i_media1[i], numeroMisure1);
        cout<<"i_media_1: "<<i_media1[i][0]<<"  "<<i_media1[i][1]<<endl;
        R_eq1[i][0] = V_1[i][0]/i_media1[i][0];  
        R_eq1[i][1] = sqrt( pow(0.01/i_media1[i][0], 2) + pow( V_1[i][0]*0.001/(i_media1[i][0]*i_media1[i][0]) , 2) );
        cout<<"R_eq[i]: "<<R_eq1[i][0]<<"  "<<R_eq1[i][1]<<"  ho usato le incertezze degli strumenti, valore in MOhm.  "<<endl;
        R_V1[i][0] = 1/(1/R_eq1[i][0] - 1/R_1[i][0]);
        R_V1[i][1] = sqrt(  pow(pow(R_1[i][0]/(R_1[i][0] - R_eq1[i][0]), 2)*R_eq1[i][1], 2) + pow(pow(R_eq1[i][0]/(R_eq1[i][0] - R_1[i][0]), 2)*R_1[i][1], 2) );
        cout<<"R_V1[i]: "<<R_V1[i][0]<<"  "<<R_V1[i][1]<<endl;
    }
    //media pesata R_V1:
    double R_V1_medio[2] = {0, 0};
    for(int i = 0; i<size1; i++){
        R_V1_medio[0] += R_V1[i][0]/pow(R_V1[i][1], 2);
        R_V1_medio[1] += pow(1/R_V1[i][1], 2);
    }
    R_V1_medio[0] = R_V1_medio[0]/R_V1_medio[1];
    R_V1_medio[1] = 1/R_V1_medio[1];
    cout<<"R_V1_medio: "<<R_V1_medio[0]<<"  "<<R_V1_medio[1]<<"  ottenuto con una media pesata."<<endl;

//  ESPERIMENTO2: RESISTENZA AMPEROMETRO
    cout<<"ESPERIMENTO2: RESISTENZA AMPEROMETRO"<<endl;
    double i_media2[4][2];
    int size2 = (int) (sizeof(V_2)/sizeof(V_2[0]));


    double R_eq2[4][2];
    double R_A2[4][2];

    for(int i = 0; i<size2; i++){
        media_stdm(I_2[i], i_media2[i], numeroMisure2);
        cout<<"i_media_2: "<<i_media2[i][0]<<"  "<<i_media2[i][1]<<endl;
        R_eq2[i][0] = V_2[i][0]*1000./i_media2[i][0];  
        R_eq2[i][1] = sqrt( pow(0.01/i_media2[i][0], 2) + pow( V_2[i][0]*0.001/(i_media2[i][0]*i_media2[i][0]) , 2) )*1000.;
        cout<<"R_eq[i]: "<<R_eq2[i][0]<<"  "<<R_eq2[i][1]<<"  ho usato le incertezze degli strumenti, valore in Ohm.  "<<endl;
        R_A2[i][0] = R_eq2[i][0] - R_2[i][0];
        R_A2[i][1] = sqrt(  pow( R_eq2[i][1], 2) + pow( R_2[i][1] , 2) );
        cout<<"R_A2[i]: "<<R_A2[i][0]<<"  "<<R_A2[i][1]<<endl;
    }
    //media pesata R_A2:
    double R_A2_medio[2] = {0, 0};
    for(int i = 0; i<size2; i++){
        R_A2_medio[0] += R_A2[i][0]/pow(R_A2[i][1], 2);
        R_A2_medio[1] += pow(1/R_A2[i][1], 2);
    }
    R_A2_medio[0] = R_A2_medio[0]/R_A2_medio[1];
    R_A2_medio[1] = 1/R_A2_medio[1];
    cout<<"R_A2_medio: "<<R_A2_medio[0]<<"  "<<R_A2_medio[1]<<"  ottenuto con una media pesata."<<endl;

//  ESPERIMENTO3: VERIFICA DELLA LEGGE DI OHM
    //TApplication TheApp("TheApp", &argc, argv);
    ofstream file_dati3;
    double i_media3[2];

    file_dati3.open("verifica_legge_di_ohm.txt", ios::out);
    file_dati3<<"#I \t V \t errI \t errV "<<endl;

    double err_y = sqrt(0.01*0.01 + pow(0.0499*0.001, 2)); //proietto tutti gli errori sulle y

    int size3 = (int) (sizeof(V_3)/sizeof(V_3[0]));
    for(int i = 0; i<size3; i++){
        media_stdm(I_3[i], i_media3, numeroMisure3);
        cout<<"i_media3: "<<i_media3[0]<<"  "<<i_media3[1]<<endl;
        file_dati3<<i_media3[0] <<" \t "<<V_3[i]<<" \t "<<err_y<<endl; //Volt _ muA

    }
    gStyle->SetOptFit();

    TCanvas* c3 = new TCanvas("c3","c3",800,800);

    TGraphErrors *ge3 = new  TGraphErrors("verifica_legge_di_ohm.txt" , "%lg %lg %lg"); 
    file_dati3.close();
    ge3->SetTitle("verifica della legge di Ohm");
    ge3->GetXaxis()->SetTitle("Intensita'[#mu A]");
    ge3->GetYaxis()->SetTitle("Voltaggio[V]");

    ge3->GetXaxis()->SetTitleSize(0.035);
    ge3->GetXaxis()->SetTitleOffset(1.3);
    ge3->GetXaxis()->SetLabelSize(0.028);

    ge3->GetYaxis()->SetTitleSize(0.034);
    ge3->GetYaxis()->SetTitleOffset(1.39);
    ge3->GetYaxis()->SetLabelSize(0.026);


    ge3->SetMarkerStyle(20);
    ge3->SetMarkerSize(0.5);

    ge3->GetXaxis()->SetNdivisions(20, 5, 0);
    ge3->GetYaxis()->SetNdivisions(12,5, 0);


    TF1 *retta_Ohm = new TF1("retta_Ohm", "[0]*x +[1]", 30., 220.); 

    TFitResultPtr fit_ptr3 = ge3->Fit("retta_Ohm", "S");
        
    ge3->Draw("AP");
    c3->SetGrid(1, 1);
    c3->Print ("voltaggio_intensita_fit.pdf", "pdf");
    delete c3;

    err_y = err_y * sqrt(fit_ptr3->Chi2()/fit_ptr3->Ndf());
    cout<<"nuove incertezze sulle y: "<<err_y<<endl; 
//  ESPERIMENTO4: RESISTENZE IN PRALLELO E IN SERIE
    cout<<"ESPERIMENTO4: RESISTENZE IN PRALLELO E IN SERIE"<<endl;

    double i_media4[2];
    double R_eq4_parallelo[2];

    int size4_parallelo = (int) (sizeof(V_4_parallelo)/sizeof(V_4_parallelo[0]));
    for(int i = 0; i<size4_parallelo; i++){
        
        media_stdm(I_4_parallelo[i], i_media4, numeroMisure4);
        cout<<"i_media4: "<<i_media4[0]<<"  "<<i_media4[1]<<endl;
        R_eq4_parallelo[0] = V_4_parallelo[i]/i_media4[0]; //espresso in MOhm
        R_eq4_parallelo[1] = sqrt( pow(0.01/i_media4[0], 2) + pow(V_4_parallelo[i]*0.001/pow(i_media4[0], 2), 2) );
        cout<<"R_eq4_parallelo: "<<R_eq4_parallelo[0]*1000<<"  "<<R_eq4_parallelo[1]*1000<<"KOhm;  da confrontare con 74.3KOhm."<<endl;
    }
    //calcolo della Reqattesa
    double R_eqAttesa_parallelo[2];
    R_eqAttesa_parallelo[0] = 1/((1/R_A) + (1/R_B));
    R_eqAttesa_parallelo[1] = sqrt(  pow( pow(R_A/(R_A + R_B), 2)*0.1, 2) + pow( pow(R_B/(R_A + R_B), 2)*0.1, 2)  );
    cout<<"resistenza attesa parallelo: "<<R_eqAttesa_parallelo[0]<<"  "<<R_eqAttesa_parallelo[1]<<endl;

    double R_eq4_serie[2];

    int size4_serie = (int) (sizeof(V_4_serie)/sizeof(V_4_serie[0]));
    for(int i = 0; i<size4_serie; i++){
        
        media_stdm(I_4_serie[i], i_media4, numeroMisure4);
        cout<<"i_media4: "<<i_media4[0]<<"  "<<i_media4[1]<<endl;
        R_eq4_serie[0] = V_4_serie[i]/i_media4[0]; //espresso in MOhm
        R_eq4_serie[1] = sqrt( pow(0.01/i_media4[0], 2) + pow(V_4_serie[i]*0.001/pow(i_media4[0], 2), 2) );
        cout<<"R_eq4_serie: "<<R_eq4_serie[0]*1000<<"  "<<R_eq4_serie[1]*1000<<"KOhm;  da confrontare con 297.2KOhm."<<endl;
    }
    //calcolo della Reqattesa
    double R_eqAttesa_serie[2];
    R_eqAttesa_serie[0] = R_A + R_B;
    R_eqAttesa_serie[1] = sqrt(0.1*0.1 + 0.1*0.1);
    cout<<"resistenza attesa serie: "<<R_eqAttesa_serie[0]<<"  "<<R_eqAttesa_serie[1]<<endl;

    //calcolo della Reqattesa
    double R_eqAttesaCorretta_serie[2];
    R_V1_medio[0] = R_V1_medio[0]*1000;//in kOhm
    R_V1_medio[1] = R_V1_medio[1]*1000;//in kOhm

    R_eqAttesaCorretta_serie[0] = 1/( 1/R_V1_medio[0]  + 1/(R_A + R_B) );
    double sigma_res_serie = sqrt(0.1*0.1 + 0.1*0.1);
    R_eqAttesaCorretta_serie[1] = sqrt( pow(pow(R_V1_medio[0]/(R_V1_medio[0] + R_A + R_B), 2)*sigma_res_serie, 2) + pow(pow((R_A + R_B)/(R_A + R_B + R_V1_medio[0]), 2)*R_V1_medio[1], 2) );
    cout<<"resistenza attesa serie corretta: "<<R_eqAttesaCorretta_serie[0]<<"  "<<R_eqAttesaCorretta_serie[1]<<endl;

//  ESPERIMENTO7: DIODO
    TApplication app("app", &argc, argv);

    cout<<"ESPERIMENTO7: DIODO"<<endl;

    ofstream file_dati7;


    file_dati7.open("intensita_voltaggio.txt", ios::out);
    file_dati7<<"#V \t I \t errV \t errI "<<endl;

    double i_media7[2];
    int size7 = (int) (sizeof(V_7)/sizeof(V_7[0]));
    //cout<<"size7: "<<size7<<endl;
    for(int i = 0; i<size7; i++){
        media_stdm(I_7[i], i_media7, numeroMisure7);
        file_dati7<<V_7[i] <<" \t "<< i_media7[0]<<" \t "<<" 0.001 "<<" \t "<<i_media7[1]<<endl; //muA _ Volt

    }

    gStyle->SetOptFit();
    auto c7 = new TCanvas("c1","multigraph",800,800);

    TGraphErrors *ge7 = new  TGraphErrors("intensita_voltaggio.txt" , "%lg %lg %lg %lg"); 
    file_dati7.close();
    ge7->SetTitle("andamento dell'intensita' su voltaggio per il diodo");
    ge7->GetXaxis()->SetTitle("Voltaggio[V]");
    ge7->GetYaxis()->SetTitle("Intensita[#mu A]");

    ge7->GetXaxis()->SetTitleSize(0.035);
    ge7->GetXaxis()->SetTitleOffset(1.3);
    ge7->GetXaxis()->SetLabelSize(0.028);

    ge7->GetYaxis()->SetTitleSize(0.034);
    ge7->GetYaxis()->SetTitleOffset(1.39);
    ge7->GetYaxis()->SetLabelSize(0.026);


    ge7->SetMarkerStyle(20);
    ge7->SetMarkerSize(0.5);
    
    gPad->Modified();
    ge7->GetXaxis()->SetLimits(0., 1.2);
    ge7->SetMinimum(-100.);

    ge7->GetXaxis()->SetNdivisions(12,5, 2);
    ge7->GetYaxis()->SetNdivisions(24,5, 0);


    TF1 *exp = new TF1("exp_crescente", "[0]*(exp([1]*x/[2]) -1)", 0., 1.2); 
    double * I0 = new double(2);
    media_stdm(I_7[0], I0, numeroMisure7);
    cout<<"I0 media: "<<I0[0]<<" "<<I0[1]<<endl;
    exp->SetParameter(0, I0[0]);
    delete I0;

    exp->SetParameter(1, 38.6);
    exp->SetParameter(2, 1.45); //costante del diodo??
    TFitResultPtr fit_result_exp = ge7->Fit("exp_crescente", "S", "", 0., 0.900);

    ge7->Draw("AP");
    c7->SetGrid(1, 1);
    c7->Print ("intensita_voltaggio_fitexp.png", "png");
    //app.Run();

    TF1 *retta = new TF1("retta", "[0]*x + [1]", 0., 1.2); 
    retta->SetParameter(0, 1566667);
    retta->SetParameter(1, 613100);


    TFitResultPtr fit_result_retta = ge7->Fit("retta", "S", " ", 0.900, 1.2);
    double m_7 = retta->GetParameter(0);
    double a_7 = retta->GetParameter(1);

    double m_7_err = retta->GetParError(0);
    double a_7_err = retta->GetParError(1);
    cout<<"coefficiente angolare: "<<m_7<<endl;
    cout<<"intercetta : "<<a_7<<endl;
    double zero_err = sqrt(pow(a_7_err/m_7, 2) + pow(m_7_err*a_7/(m_7*m_7), 2));
    cout<<"lo zero è: "<<-a_7/m_7<<"  "<<zero_err<<endl;


    ge7->SetTitle("interpolazione regione sopra ai 0.900V");
    ge7->Draw("AP");
    c7->SetGrid(1, 1);
    c7->Print ("intensita_voltaggio_fitsoloretta.png", "png");


    delete c7;

}