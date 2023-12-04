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

//  EXPERIMENT1: TESTER RESISTANCE
    cout<<"EXPERIMENT1: TESTER RESISTANCE"<<endl;
    double i_mean1[4][2];
    int size1 = (int) (sizeof(V_1)/sizeof(V_1[0]));

    double R_eq1[4][2];
    double R_V1[4][2];

    for(int i = 0; i<size1; i++){
        media_stdm(I_1[i], i_mean1[i], number_of_measures1);
        cout<<"i_mean_1: "<<i_mean1[i][0]<<"  "<<i_mean1[i][1]<<endl;
        R_eq1[i][0] = V_1[i][0]/i_mean1[i][0];  
        R_eq1[i][1] = sqrt( pow(0.01/i_mean1[i][0], 2) + pow( V_1[i][0]*0.001/(i_mean1[i][0]*i_mean1[i][0]) , 2) );
        cout<<"R_eq[i]: "<<R_eq1[i][0]<<"  "<<R_eq1[i][1]<<" MOhm."<<endl;
        R_V1[i][0] = 1/(1/R_eq1[i][0] - 1/R_1[i][0]);
        R_V1[i][1] = sqrt(  pow(pow(R_1[i][0]/(R_1[i][0] - R_eq1[i][0]), 2)*R_eq1[i][1], 2) + pow(pow(R_eq1[i][0]/(R_eq1[i][0] - R_1[i][0]), 2)*R_1[i][1], 2) );
        cout<<"R_V1[i]: "<<R_V1[i][0]<<"  "<<R_V1[i][1]<<endl;
    }
    //weighted mean R_V1:
    double R_V1_mean[2] = {0, 0};
    for(int i = 0; i<size1; i++){
        R_V1_mean[0] += R_V1[i][0]/pow(R_V1[i][1], 2);
        R_V1_mean[1] += pow(1/R_V1[i][1], 2);
    }
    R_V1_mean[0] = R_V1_mean[0]/R_V1_mean[1];
    R_V1_mean[1] = 1/R_V1_mean[1];
    cout<<"R_V1_mean: "<<R_V1_mean[0]<<"  "<<R_V1_mean[1]<<"  got with weighted mean."<<endl;

//  EXPERIMENT2: AMPERE METER RESISTANCE
    cout<<"EXPERIMENT2: AMPERE METER RESISTANCE"<<endl;
    double i_mean2[4][2];
    int size2 = (int) (sizeof(V_2)/sizeof(V_2[0]));


    double R_eq2[4][2];
    double R_A2[4][2];

    for(int i = 0; i<size2; i++){
        media_stdm(I_2[i], i_mean2[i], number_of_measures2);
        cout<<"i_mean_2: "<<i_mean2[i][0]<<"  "<<i_mean2[i][1]<<endl;
        R_eq2[i][0] = V_2[i][0]*1000./i_mean2[i][0];  
        R_eq2[i][1] = sqrt( pow(0.01/i_mean2[i][0], 2) + pow( V_2[i][0]*0.001/(i_mean2[i][0]*i_mean2[i][0]) , 2) )*1000.;
        cout<<"R_eq[i]: "<<R_eq2[i][0]<<"  "<<R_eq2[i][1]<<" Ohm.  "<<endl;
        R_A2[i][0] = R_eq2[i][0] - R_2[i][0];
        R_A2[i][1] = sqrt(  pow( R_eq2[i][1], 2) + pow( R_2[i][1] , 2) );
        cout<<"R_A2[i]: "<<R_A2[i][0]<<"  "<<R_A2[i][1]<<endl;
    }
    //weighted mean R_A2:
    double R_A2_mean[2] = {0, 0};
    for(int i = 0; i<size2; i++){
        R_A2_mean[0] += R_A2[i][0]/pow(R_A2[i][1], 2);
        R_A2_mean[1] += pow(1/R_A2[i][1], 2);
    }
    R_A2_mean[0] = R_A2_mean[0]/R_A2_mean[1];
    R_A2_mean[1] = 1/R_A2_mean[1];
    cout<<"R_A2_mean: "<<R_A2_mean[0]<<"  "<<R_A2_mean[1]<<"  got with weighted mean."<<endl;

//  EXPERIMENT3: CHECK OF OHM'S LAW
    ofstream data_file3;
    double i_mean3[2];

    data_file3.open("Data/Ohm's_law.txt", ios::out);
    data_file3<<"#I \t V \t errI \t errV "<<endl;

    double err_y = sqrt(0.01*0.01 + pow(0.0499*0.001, 2)); //all errors projected on y

    int size3 = (int) (sizeof(V_3)/sizeof(V_3[0]));
    for(int i = 0; i<size3; i++){
        media_stdm(I_3[i], i_mean3, number_of_measures3);
        cout<<"i_mean3: "<<i_mean3[0]<<"  "<<i_mean3[1]<<endl;
        data_file3<<i_mean3[0] <<" \t "<<V_3[i]<<" \t "<<err_y<<endl; //Volt _ muA

    }
    gStyle->SetOptFit();

    TCanvas* c3 = new TCanvas("c3","c3",800,800);

    TGraphErrors *ge3 = new  TGraphErrors("Data/Ohm's_law.txt" , "%lg %lg %lg"); 
    data_file3.close();
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


    TF1 *line_Ohm = new TF1("line_Ohm", "[0]*x +[1]", 30., 220.); 

    TFitResultPtr fit_ptr3 = ge3->Fit("line_Ohm", "S");
        
    ge3->Draw("AP");
    c3->SetGrid(1, 1);
    c3->Print ("Graphs/voltage_VS_intensity_fit.pdf", "pdf");
    delete c3;

    err_y = err_y * sqrt(fit_ptr3->Chi2()/fit_ptr3->Ndf());
    cout<<"new errors on y: "<<err_y<<endl; 

//  EXPERIMENT4: PARALLEL AND SERIES RESISTANCES
    cout<<"EXPERIMENT4: PARALLEL AND SERIES RESISTANCES"<<endl;

    double i_mean4[2];
    double R_eq4_parallel[2];

    int size4_parallel = (int) (sizeof(V_4_parallel)/sizeof(V_4_parallel[0]));
    for(int i = 0; i<size4_parallel; i++){
        
        media_stdm(I_4_parallel[i], i_mean4, number_of_measures4);
        cout<<"i_mean4: "<<i_mean4[0]<<"  "<<i_mean4[1]<<endl;
        R_eq4_parallel[0] = V_4_parallel[i]/i_mean4[0]; //in MOhm
        R_eq4_parallel[1] = sqrt( pow(0.01/i_mean4[0], 2) + pow(V_4_parallel[i]*0.001/pow(i_mean4[0], 2), 2) );
        cout<<"R_eq4_parallel: "<<R_eq4_parallel[0]*1000<<"  "<<R_eq4_parallel[1]*1000<<"KOhm; to confront with 74.3KOhm."<<endl;
    }
    //calculate of expected Req 
    double ExpectedR_eq_parallel[2];
    ExpectedR_eq_parallel[0] = 1/((1/R_A) + (1/R_B));
    ExpectedR_eq_parallel[1] = sqrt(  pow( pow(R_A/(R_A + R_B), 2)*0.1, 2) + pow( pow(R_B/(R_A + R_B), 2)*0.1, 2)  );
    cout<<"expected parallel resistency: "<<ExpectedR_eq_parallel[0]<<"  "<<ExpectedR_eq_parallel[1]<<endl;

    double R_eq4_series[2];

    int size4_series = (int) (sizeof(V_4_series)/sizeof(V_4_series[0]));
    for(int i = 0; i<size4_series; i++){
        
        media_stdm(I_4_series[i], i_mean4, number_of_measures4);
        cout<<"i_mean4: "<<i_mean4[0]<<"  "<<i_mean4[1]<<endl;
        R_eq4_series[0] = V_4_series[i]/i_mean4[0]; //espresso in MOhm
        R_eq4_series[1] = sqrt( pow(0.01/i_mean4[0], 2) + pow(V_4_series[i]*0.001/pow(i_mean4[0], 2), 2) );
        cout<<"R_eq4_series: "<<R_eq4_series[0]*1000<<"  "<<R_eq4_series[1]*1000<<"KOhm; to confront with 297.2KOhm."<<endl;
    }
    //calculate of expected Req 
    double ExpectedR_eq_series[2];
    ExpectedR_eq_series[0] = R_A + R_B;
    ExpectedR_eq_series[1] = sqrt(0.1*0.1 + 0.1*0.1);
    cout<<"expected series resistance: "<<ExpectedR_eq_series[0]<<"  "<<ExpectedR_eq_series[1]<<endl;

    //calculate of expected Req
    double ExpectedR_eqCorrected_series[2];
    R_V1_mean[0] = R_V1_mean[0]*1000;//in kOhm
    R_V1_mean[1] = R_V1_mean[1]*1000;//in kOhm

    ExpectedR_eqCorrected_series[0] = 1/( 1/R_V1_mean[0]  + 1/(R_A + R_B) );
    double sigma_res_series = sqrt(0.1*0.1 + 0.1*0.1);
    ExpectedR_eqCorrected_series[1] = sqrt( pow(pow(R_V1_mean[0]/(R_V1_mean[0] + R_A + R_B), 2)*sigma_res_series, 2) + pow(pow((R_A + R_B)/(R_A + R_B + R_V1_mean[0]), 2)*R_V1_mean[1], 2) );
    cout<<"expected seriess resistance corrected : "<<ExpectedR_eqCorrected_series[0]<<"  "<<ExpectedR_eqCorrected_series[1]<<endl;

//  EXPERIMENT7: DIODE
    TApplication app("app", &argc, argv);

    cout<<"EXPERIMENT7: DIODE"<<endl;

    ofstream data_file7;

    data_file7.open("Data/intensity_VS_power.txt", ios::out);
    data_file7<<"#V \t I \t errV \t errI "<<endl;

    double i_mean7[2];
    int size7 = (int) (sizeof(V_7)/sizeof(V_7[0]));
    //cout<<"size7: "<<size7<<endl;
    for(int i = 0; i<size7; i++){
        media_stdm(I_7[i], i_mean7, number_of_measures7);
        data_file7<<V_7[i] <<" \t "<< i_mean7[0]<<" \t "<<" 0.001 "<<" \t "<<i_mean7[1]<<endl; //muA _ Volt

    }

    gStyle->SetOptFit();
    auto c7 = new TCanvas("c1","multigraph",800,800);

    TGraphErrors *ge7 = new  TGraphErrors("Data/intensity_VS_power.txt" , "%lg %lg %lg %lg"); 
    data_file7.close();
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


    TF1 *exp = new TF1("exp_increasing", "[0]*(exp([1]*x/[2]) -1)", 0., 1.2); 
    double * I0 = new double(2);
    media_stdm(I_7[0], I0, number_of_measures7);
    cout<<"I0 mean: "<<I0[0]<<" "<<I0[1]<<endl;
    exp->SetParameter(0, I0[0]);
    delete I0;

    exp->SetParameter(1, 38.6);
    exp->SetParameter(2, 1.45); 
    TFitResultPtr fit_result_exp = ge7->Fit("exp_increasing", "S", "", 0., 0.900);

    ge7->Draw("AP");
    c7->SetGrid(1, 1);
    c7->Print ("Graphs/intensity_VS_power_fitexp.png", "png");

    TF1 *line = new TF1("line", "[0]*x + [1]", 0., 1.2); 
    line->SetParameter(0, 1566667);
    line->SetParameter(1, 613100);


    TFitResultPtr fit_result_line = ge7->Fit("line", "S", " ", 0.900, 1.2);
    double m_7 = line->GetParameter(0);
    double a_7 = line->GetParameter(1);

    double m_7_err = line->GetParError(0);
    double a_7_err = line->GetParError(1);
    cout<<"angular coefficient: "<<m_7<<endl;
    cout<<"intecept : "<<a_7<<endl;
    double zero_err = sqrt(pow(a_7_err/m_7, 2) + pow(m_7_err*a_7/(m_7*m_7), 2));
    cout<<"the zero is: "<<-a_7/m_7<<"  "<<zero_err<<endl;


    ge7->SetTitle("interpolazione regione sopra ai 0.900V");
    ge7->Draw("AP");
    c7->SetGrid(1, 1);
    c7->Print ("Graphs/intensity_VS_power_linefit.png", "png");


    delete c7;

}