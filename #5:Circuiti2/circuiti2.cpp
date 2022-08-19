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
#include "TMatrixD.h"

#include "dati_circuiti2.h"
#include "stats.h"

using namespace std;
int main(int argc, char *argv[]){

//ESPERIMENTO1: carica, Vc
    TApplication TheApp("TheApp", &argc, argv);
    cout<<"ESPERIMENTO1:    RC-CADUTA AI CAPI DI C"<<endl;
    ofstream file_dati1;

    double v_media1[2];
    int size1 = (int) (sizeof(T_1)/sizeof(T_1[0]));


    file_dati1.open("RC_caduta_su_c.txt", ios::out);
    file_dati1<<"#t \t V \t errV "<<endl;


    for(int i = 0; i<size1; i++){
        media_stdm(V_1[i], v_media1, numeroMisure);
        if(v_media1[1] == 0){
            v_media1[1] = 2;
        }
        cout<<"v_media1: "<<v_media1[0]/1000<<"  "<<v_media1[1]*1.4/1000<<";     valore in V"<<endl;
        file_dati1<<T_1[i]<<" \t "<<v_media1[0]/1000<<" \t "<<v_media1[1]*1.4/1000<<endl; //Volt _ muA

    }
    gStyle->SetOptFit();

    TCanvas* c1 = new TCanvas("c1","c1", 800, 800);

    TGraphErrors *ge1 = new  TGraphErrors("RC_caduta_su_c.txt" , "%lg %lg %lg"); 
    file_dati1.close();
    ge1->SetTitle("RC in carica - andamento caduta di potenziale su C nel tempo");
    ge1->GetXaxis()->SetTitle("tempo[ms]");
    ge1->GetYaxis()->SetTitle("Voltaggio[V]");

    ge1->GetXaxis()->SetTitleSize(0.035);
    ge1->GetXaxis()->SetTitleOffset(1.3);
    ge1->GetXaxis()->SetLabelSize(0.028);

    ge1->GetYaxis()->SetTitleSize(0.034);
    ge1->GetYaxis()->SetTitleOffset(1.39);
    ge1->GetYaxis()->SetLabelSize(0.026);


    ge1->SetMarkerStyle(20);
    ge1->SetMarkerSize(0.5);

    ge1->GetYaxis()->SetNdivisions(5, 5, 0);
    ge1->GetXaxis()->SetNdivisions(16, 5, 0);   


    TF1 *crescitaRC = new TF1("crescitaRC", "[0]*( 1 - 2*exp(-x/[1]) ) ", 0., 12.); 
    crescitaRC->SetParameter(0, 1.);
    crescitaRC->SetParameter(1, 2.39); //tau in ms

    TFitResultPtr fit_ptr1 = ge1->Fit("crescitaRC", "S");
        
    ge1->Draw("AP");
    c1->SetGrid(1, 1);
//    TheApp.Run();
    c1->Print ("crescitaRC.pdf", "pdf");
    double Vg_1 = crescitaRC->GetParameter(0);
    double Vg_1_err = crescitaRC->GetParError(0);
    cout<<"Vg_1 stima: "<<Vg_1<<" pm "<<Vg_1_err<<" V"<<";  da confrontare con 1.00 pm 0.01 V"<<endl;

    double tau_RC = crescitaRC->GetParameter(1);
    double tau_RC_err = crescitaRC->GetParError(1);
    cout<<"tau_RC: "<<tau_RC<<" pm "<<tau_RC_err<<endl;

    double C_1 = tau_RC/R_1;
    double C_1_err = sqrt(pow(tau_RC_err/(R_1), 2) + pow(0.001*tau_RC/(R_1*R_1), 2));
    cout<<"C_1 stima: "<<C_1<<" pm "<<C_1_err<<"mu F"<<";  da confrontare con 2.42 pm 0.01 mu F"<<endl;
    
    delete c1;

//ESPERIMENTO2: carica, Vr
    cout<<"ESPERIMENTO2:    RC-CADUTA AI CAPI DI R"<<endl;
    ofstream file_dati2;

    double v_media2[2];
    int size2 = (int) (sizeof(T_2)/sizeof(T_2[0]));
    cout<<size2<<endl;

    file_dati2.open("RC_caduta_su_r.txt", ios::out);
    file_dati2<<"#t \t V \t errV "<<endl;


    for(int i = 0; i<size2; i++){
        media_stdm(V_2[i], v_media2, numeroMisure);
        if(v_media2[1] == 0){
            v_media2[1] = 2;
        }
        cout<<"v_media2: "<<v_media2[0]/1000<<"  "<<v_media2[1]*3/1000<<";     valore in V"<<endl;
        file_dati2<<T_2[i]<<" \t "<<v_media2[0]/1000<<" \t "<<v_media2[1]*3/1000<<endl; 

    }
    gStyle->SetOptFit();

    TCanvas* c2 = new TCanvas("c2","c2", 800, 800);

    TGraphErrors *ge2 = new  TGraphErrors("RC_caduta_su_r.txt" , "%lg %lg %lg"); 
    file_dati2.close();
    ge2->SetTitle("RC in carica - andamento caduta di potenziale su R nel tempo");
    ge2->GetXaxis()->SetTitle("tempo[ms]");
    ge2->GetYaxis()->SetTitle("Voltaggio[V]");

    ge2->GetXaxis()->SetTitleSize(0.035);
    ge2->GetXaxis()->SetTitleOffset(1.3);
    ge2->GetXaxis()->SetLabelSize(0.028);

    ge2->GetYaxis()->SetTitleSize(0.034);
    ge2->GetYaxis()->SetTitleOffset(1.39);
    ge2->GetYaxis()->SetLabelSize(0.026);


    ge2->SetMarkerStyle(20);
    ge2->SetMarkerSize(0.5);

    ge2->GetYaxis()->SetNdivisions(5, 5, 0);
    ge2->GetXaxis()->SetNdivisions(15, 5, 0);


    TF1 *decrescitaRC = new TF1("decrescitaRC", "2*[0]*exp(-x/[1]) ", 0., 30.); 
    decrescitaRC->SetParameter(0, 1.);
    decrescitaRC->SetParameter(1, 2.39);

    TFitResultPtr fit_ptr2 = ge2->Fit("decrescitaRC", "S");
        
    ge2->Draw("AP");
    c2->SetGrid(1, 1);
  //  TheApp.Run();
    c2->Print ("decrescitaRC.pdf", "pdf");
    double Vg_2 = decrescitaRC->GetParameter(0);
    double Vg_2_err = decrescitaRC->GetParError(0);
    cout<<"Vg_2 stima: "<<Vg_2<<" pm "<<Vg_2_err<<" V"<<";  da confrontare con 1.00 pm 0.01 V"<<endl;

    double tau_RC2 = decrescitaRC->GetParameter(1);
    double tau_RC2_err = decrescitaRC->GetParError(1);
    cout<<"tau_RC2: "<<tau_RC2<<" pm "<<tau_RC2_err<<endl;

    double C_2 = tau_RC2/R_1;
    double C_2_err = sqrt(pow(tau_RC2_err/(R_1), 2) + pow(0.001*tau_RC2/(R_1*R_1), 2));
    cout<<"C_2 stima: "<<C_2<<" pm "<<C_2_err<<"mu F"<<";  da confrontare con 2.42 pm 0.01 mu F"<<endl;

    delete c2;

//ESPERIMENTO3: carica, Vl
    cout<<"ESPERIMENTO3:    RL-CADUTA AI CAPI DI L"<<endl;
    ofstream file_dati3;

    double v_media3[2];
    int size3 = (int) (sizeof(T_3)/sizeof(T_3[0]));


    file_dati3.open("RL_caduta_su_l.txt", ios::out);
    file_dati3<<"#t \t V \t errV "<<endl;


    for(int i = 0; i<size3; i++){
        media_stdm(V_3[i], v_media3, numeroMisure);
        if(v_media3[1] == 0){
            v_media3[1] = 2;
        }
        cout<<"v_media3: "<<v_media3[0]/1000<<"  "<<v_media3[1]*1.28/1000<<";     valore in V"<<endl;
        file_dati3<<T_3[i]<<" \t "<<v_media3[0]/1000<<" \t "<<v_media3[1]*1.28/1000<<endl; 

    }
    gStyle->SetOptFit();

    TCanvas* c3 = new TCanvas("c3","c3", 800, 800);

    TGraphErrors *ge3 = new  TGraphErrors("RL_caduta_su_l.txt" , "%lg %lg %lg"); 
    file_dati3.close();
    ge3->SetTitle("RL in carica - andamento caduta di potenziale su L nel tempo");
    gStyle->SetTitleFontSize(0.1);

    ge3->GetXaxis()->SetTitle("tempo[#mu s]");
    ge3->GetYaxis()->SetTitle("Voltaggio[V]");

    ge3->GetXaxis()->SetTitleSize(0.035);
    ge3->GetXaxis()->SetTitleOffset(1.3);
    ge3->GetXaxis()->SetLabelSize(0.028);

    ge3->GetYaxis()->SetTitleSize(0.034);
    ge3->GetYaxis()->SetTitleOffset(1.39);
    ge3->GetYaxis()->SetLabelSize(0.026);


    ge3->SetMarkerStyle(20);
    ge3->SetMarkerSize(0.5);

    ge3->GetYaxis()->SetNdivisions(5, 5, 0);
    ge3->GetXaxis()->SetNdivisions(15, 5, 0);


    TF1 *decrescitaRL = new TF1("decrescitaRL", "2*[0]*exp(-x/[1]) ", 0., 115.); //Resistenza in MOhm e induttanza in H
    decrescitaRL->SetParameter(0, 1.);
    decrescitaRL->SetParameter(1, 46.98); //tau RL in mu s

    TFitResultPtr fit_ptr3 = ge3->Fit("decrescitaRL", "S");
        
    ge3->Draw("AP");
    c3->SetGrid(1, 1);

//    TheApp.Run();
    c3->Print ("decrescitaRL.pdf", "pdf");
    double tau_RL = decrescitaRL->GetParameter(1);
    double tau_RL_err = decrescitaRL->GetParError(1);
    double L_3 = tau_RL*R_1/1000; //uso R_1 in MOhm
    double L_3_err = sqrt(pow(tau_RL_err*R_1/1000, 2) + pow(0.000001*tau_RL, 2)); //incertezza sui MOhm = 0.001/1000
    cout<< "L_3 stima: "<<L_3<<" pm "<<L_3_err<<" H;    da confrontare con la prossima"<<endl;

    delete c3;
//ESPERIMENTO4: carica, Vr
    cout<<"ESPERIMENTO4:    RL-CADUTA AI CAPI DI R"<<endl;
    ofstream file_dati4;

    double v_media4[2];
    int size4 = (int) (sizeof(T_4)/sizeof(T_4[0]));


    file_dati4.open("RL_caduta_su_r.txt", ios::out);
    file_dati4<<"#t \t V \t errV "<<endl;


    for(int i = 0; i<size4; i++){
        media_stdm(V_4[i], v_media4, numeroMisure);
        cout<<"v_media4: "<<v_media4[0]/1000<<"  "<<v_media4[1]*4/1000<<";     valore in V"<<endl;
        file_dati4<<T_4[i]<<" \t "<<v_media4[0]/1000<<" \t "<<v_media4[1]*4/1000<<endl; 

    }
    gStyle->SetOptFit();

    TCanvas* c4 = new TCanvas("c4","c4", 800, 800);

    TGraphErrors *ge4 = new  TGraphErrors("RL_caduta_su_r.txt" , "%lg %lg %lg"); 
    file_dati4.close();
    ge4->SetTitle("RL in carica - andamento caduta di potenziale su R nel tempo");
    ge4->GetXaxis()->SetTitle("tempo[#mu s]");
    ge4->GetYaxis()->SetTitle("Voltaggio[V]");

    ge4->GetXaxis()->SetTitleSize(0.035);
    ge4->GetXaxis()->SetTitleOffset(1.3);
    ge4->GetXaxis()->SetLabelSize(0.028);

    ge4->GetYaxis()->SetTitleSize(0.034);
    ge4->GetYaxis()->SetTitleOffset(1.39);
    ge4->GetYaxis()->SetLabelSize(0.026);


    ge4->SetMarkerStyle(20);
    ge4->SetMarkerSize(0.5);

    ge4->GetYaxis()->SetNdivisions(5, 5, 0);
    ge4->GetXaxis()->SetNdivisions(20, 5, 0);


    TF1 *crescitaRL = new TF1("crescitaRL", "[0]*( 1 - 2*exp(-x/[1])) ", 0., 406.); 
    crescitaRL->SetParameter(0, 0.883);
    crescitaRL->SetParameter(1, 39.4);

    TFitResultPtr fit_ptr4 = ge4->Fit("crescitaRL", "S");
        
    ge4->Draw("AP");
    c4->SetGrid(1, 1);

  //  TheApp.Run();

    c4->Print ("crescitaRL.pdf", "pdf");
    double tau_RL2 = crescitaRL->GetParameter(1);
    double tau_RL2_err = crescitaRL->GetParError(1);
    double L_4 = tau_RL2*(R_1 + 0.1273)/1000; //correzione R eq; uso i MOhm
    double L_4_err = sqrt(pow(tau_RL2_err*(R_1 + 0.1273)/1000, 2) + pow(0.00003*tau_RL2, 2)); //incertezza sui MOhm = 0.03/1000
    cout<< "L_4 stima: "<<L_4<<" pm "<<L_4_err<<" H;    da confrontare con la precedente"<<endl;

    delete c4;


//ESPERIMENTO5: sottosmorzamento
    cout<<"ESPERIMENTO5:    RLC-SOTTOSMORZAMENTO"<<endl;
    ofstream file_dati5;

    double v_media5[2];
    int size5 = (int) (sizeof(T_5)/sizeof(T_5[0]));


    file_dati5.open("RLC_sottosmorzamento.txt", ios::out);
    file_dati5<<"#t \t V \t errV "<<endl;


    for(int i = 0; i<size5; i++){
        media_stdm(V_5[i], v_media5, numeroMisure);
        cout<<"v_media5: "<<v_media5[0]/1000<<"  "<<v_media5[1]*5/1000<<";     valore in V"<<endl;
        file_dati5<<T_5[i]/1000<<" \t "<<v_media5[0]/1000<<" \t "<<v_media5[1]*5/1000<<endl; 

    }
    gStyle->SetOptFit();

    TCanvas* c5 = new TCanvas("c5","c5", 800, 800);

    TGraphErrors *ge5 = new  TGraphErrors("RLC_sottosmorzamento.txt" , "%lg %lg %lg"); 
    file_dati5.close();
    ge5->SetTitle("RLC in carica - sottosmorzamento");
    ge5->GetXaxis()->SetTitle("tempo[m s]");
    ge5->GetYaxis()->SetTitle("Voltaggio[V]");

    ge5->GetXaxis()->SetTitleSize(0.035);
    ge5->GetXaxis()->SetTitleOffset(1.3);
    ge5->GetXaxis()->SetLabelSize(0.028);

    ge5->GetYaxis()->SetTitleSize(0.034);
    ge5->GetYaxis()->SetTitleOffset(1.39);
    ge5->GetYaxis()->SetLabelSize(0.026);


    ge5->SetMarkerStyle(20);
    ge5->SetMarkerSize(0.5);

    ge5->GetYaxis()->SetNdivisions(5, 5, 0);
    ge5->GetXaxis()->SetNdivisions(10, 5, 0);


    TF1 *sottosmorzamento = new TF1("sottosmorzamento", "[0]*exp(-x*[1])*sin(x*[2]) ", 0., 1.5); //[x] = ms 
    sottosmorzamento->SetParameter(0, 0.25);

    double L_approx = 0.04519; //H
    cout<<"L/R stima: "<<L_approx/(R_5*pow(10, -3))<<" ms"<<endl;

    sottosmorzamento->SetParameter( 1, (R_5*pow(10, -3))/(2*L_approx) ); //H/kOhm = ms

    cout<<"L_approx: "<<L_approx<<" H"<<"; C_5*pow(10, -3): "<<C_5*pow(10, -3)<<" mu F"<<endl;
    cout<<"R_5: "<<R_5<<" Ohm"<<"; L_approx*pow(10, 3) "<<L_approx*pow(10, 3)<<" mH"<<endl;

    double beta = sqrt(1/(L_approx*C_5*pow(10, -3)) - R_5*R_5/(4*L_approx*pow(10, 3)*L_approx*pow(10, 3))); //[LC] = ms^2; [L/R] = ms^2
    cout<<"beta stima: "<<beta<<endl;
    sottosmorzamento->SetParameter(2, beta);

    TFitResultPtr fit_ptr5 = ge5->Fit("sottosmorzamento", "S");
        
    ge5->Draw("AP");
    c5->SetGrid(1, 1);

    //TheApp.Run();

    c5->Print ("sottosmorzamento.pdf", "pdf");
    double V0_5 = sottosmorzamento->GetParameter(0);
    double V0_5_err = sottosmorzamento->GetParError(0);
    cout<<"V0_5 - sottosmorzamento: "<<V0_5<<" pm "<<V0_5_err<<" A"<<endl;

    double I0_5 = V0_5/R_5;
    double I0_5_err = sqrt(  pow(V0_5_err/R_5, 2) + pow(V0_5*0.1/(R_5*R_5), 2) );
    cout<<"I0_5 - sottosmorzamento: "<<I0_5<<" pm "<<I0_5_err<<" A"<<endl;

    double gamma1 = sottosmorzamento->GetParameter(1);
    double gamma1_err = sottosmorzamento->GetParError(1);
    cout<<"gamma - sottosmorzamento: "<<gamma1<<" "<<gamma1_err<<endl;
    double tau_sottosm = 0.5/gamma1;
    double tau_sottosm_err = gamma1_err/(2*gamma1*gamma1); 
    double L_5 = tau_sottosm*(R_5 + 127.3)*pow(10, -3);
    double L_5_err = sqrt(pow(tau_sottosm_err*(R_5 + 127.3)*pow(10, -3), 2) + pow(0.030*tau_sottosm, 2)); // err R_5 = 30 Ohm = 0.030 kOhm
    cout<<"L_5 - sottosmorzamento: "<<L_5<<" pm "<<L_5_err<<" H ?"<<endl;

    beta = sottosmorzamento->GetParameter(2);
    double beta_err = sottosmorzamento->GetParError(2);
    cout<<"beta: "<<beta<<" "<<beta_err<<endl;

    TMatrixD cov = fit_ptr5->GetCovarianceMatrix();
    cov.Print();

    double omega_sq = pow( beta, 2 ) + pow( gamma1, 2 );
    double omega_sq_err = sqrt(  pow(2*beta*beta_err, 2) + pow(2*gamma1*gamma1_err, 2) + 2*4*beta*gamma1*(-9.122 *pow(10, -4))  );
    cout<<"omega_sq: "<<omega_sq<<" pm "<<omega_sq_err<<" ms"<<endl;

    double C_5 = 1/(L_5*omega_sq);
    double C_5_err = sqrt(  pow(L_5_err/(pow(L_5, 2)*omega_sq), 2) + pow(omega_sq_err/(pow(omega_sq, 2)*L_5), 2)  );
    cout<<"C_5: "<<C_5<<" pm "<<C_5_err<<" mu F?"<<endl;
    delete c5;

//ESPERIMENTO6: smorzamento critico
    cout<<"ESPERIMENTO6:    RLC-SMORZAMENTO CRITICO"<<endl;
    ofstream file_dati6;
    int size6 = (int) (sizeof(T_6)/sizeof(T_6[0]));

    file_dati6.open("RLC_smorzamento_critico.txt", ios::out);
    file_dati6<<"#t \t V \t errV "<<endl;


    for(int i = 0; i<size6; i++){
        file_dati6<<T_6[i]/1000<<" \t "<<V_6[i]/1000<<" \t "<<"0.002"<<endl; 
    }
    gStyle->SetOptFit();

    TCanvas* c6 = new TCanvas("c6","c6", 800, 800);

    TGraphErrors *ge6 = new  TGraphErrors("RLC_smorzamento_critico.txt" , "%lg %lg %lg"); 
    file_dati6.close();
    ge6->SetTitle("RLC in carica - smorzamento_critico");
    ge6->GetXaxis()->SetTitle("tempo[m s]");
    ge6->GetYaxis()->SetTitle("Voltaggio[V]");

    ge6->GetXaxis()->SetTitleSize(0.035);
    ge6->GetXaxis()->SetTitleOffset(1.3);
    ge6->GetXaxis()->SetLabelSize(0.028);

    ge6->GetYaxis()->SetTitleSize(0.034);
    ge6->GetYaxis()->SetTitleOffset(1.39);
    ge6->GetYaxis()->SetLabelSize(0.026);


    ge6->SetMarkerStyle(20);
    ge6->SetMarkerSize(0.5);

    ge6->GetYaxis()->SetNdivisions(5, 5, 0);
    ge6->GetXaxis()->SetNdivisions(10, 5, 0);


    TF1 *smorzamento_critico = new TF1("smorzamento_critico", "[0]*x*exp(-[1]*x) ", 0., 0.54); //[x] = ms 
    sottosmorzamento->SetParameter(0, 1.3);
    cout<<"L/R stima: "<<L_approx/(R_6*pow(10, -3))<<" ms"<<endl;
    smorzamento_critico->SetParameter( 1, (R_6*pow(10, -3))/(2*L_approx) ); //kOhm/H = 1/ms
    cout<<"L_approx: "<<L_approx<<" H"<<endl;
    cout<<"R_6: "<<R_6<<" Ohm"<<endl;

    TFitResultPtr fit_ptr6 = ge6->Fit("smorzamento_critico", "S");

    ge6->Draw("AP");
    c6->SetGrid(1, 1);

    //TheApp.Run();

    c6->Print ("smorzamento_critico.pdf", "pdf");
    double V0_6 = smorzamento_critico->GetParameter(0);
    double V0_6_err = smorzamento_critico->GetParError(0);
   // double I0_6 = V0_6/(R_6*pow(10, -3));
   // double I0_6_err = sqrt(  pow(V0_6_err/R_6*pow(10, -3), 2) + pow(V0_6*0.1/(R_6*pow(10, -3)*R_6*pow(10, -3)), 2) );
    cout<<"V0_6 - smorzamento_critico: "<<V0_6<<" pm "<<V0_6_err<<" V"<<endl;

    double gamma2 = smorzamento_critico->GetParameter(1);
    double gamma2_err = smorzamento_critico->GetParError(1);
    double tau_critico = 1/(2*gamma2);
    double tau_critico_err = gamma2_err/(2*gamma2*gamma2); 
    double L_6 = tau_critico*R_6*pow(10, -3);
    double L_6_err = sqrt(pow(tau_critico_err*R_6*pow(10, -3), 2) + pow(0.0001*tau_critico, 2)); // err R_6 = 0.1 Ohm = 0.0001 kOhm 
    cout<<"L_6 - smorzamento_critico: "<<L_6<<" pm "<<L_6_err<<" H ?"<<endl;


    delete c6;
    TCanvas* c6b = new TCanvas("c6","c6", 800, 800);

    TFitResultPtr fit_ptr6b = ge6->Fit("sottosmorzamento", "S");

    ge6->Draw("AP");
    c6b->SetGrid(1, 1);

   // TheApp.Run();
    c6b->Print ("smorzamento_sottocritico.pdf", "pdf");
   


    delete c6b;
   
//ESPERIMENTO7: sovrasmorzamento
    cout<<"ESPERIMENTO7:    RLC-SOVRASMORZAMENTO"<<endl;
    ofstream file_dati7;

    int size7 = (int) (sizeof(T_7)/sizeof(T_7[0]));


    file_dati7.open("RLC_sovrasmorzamento.txt", ios::out);
    file_dati7<<"#t \t V \t errV "<<endl;


    for(int i = 0; i<size7; i++){
        file_dati7<<T_7[i]/1000<<" \t "<<V_7[i]/1000<<" \t "<<"0.004"<<endl; 

    }
    gStyle->SetOptFit();

    TCanvas* c7 = new TCanvas("c7","c7", 800, 800);

    TGraphErrors *ge7 = new  TGraphErrors("RLC_sovrasmorzamento.txt" , "%lg %lg %lg"); 
    file_dati7.close();
    ge7->SetTitle("RLC in carica - sovrasmorzamento");
    ge7->GetXaxis()->SetTitle("tempo[m s]");
    ge7->GetYaxis()->SetTitle("Voltaggio[V]");

    ge7->GetXaxis()->SetTitleSize(0.035);
    ge7->GetXaxis()->SetTitleOffset(1.3);
    ge7->GetXaxis()->SetLabelSize(0.028);

    ge7->GetYaxis()->SetTitleSize(0.034);
    ge7->GetYaxis()->SetTitleOffset(1.39);
    ge7->GetYaxis()->SetLabelSize(0.026);


    ge7->SetMarkerStyle(20);
    ge7->SetMarkerSize(0.5);

    ge7->GetYaxis()->SetNdivisions(5, 5, 0);
    ge7->GetXaxis()->SetNdivisions(10, 5, 0);


    TF1 *sovrasmorzamento = new TF1("sovrasmorzamento", "[0]*exp(-x*[1])*sinh(x*[2]) ", 0., 0.72); //[x] = ms 
    sovrasmorzamento->SetParameter(0, 1.4);

    cout<<"L/R stima: "<<L_approx/(R_7*pow(10, -3))<<" ms"<<endl;

    sovrasmorzamento->SetParameter( 1, (R_7*pow(10, -3))/(2*L_approx) ); //H/kOhm = ms

    cout<<"L_approx: "<<L_approx<<" H"<<"; C_5*pow(10, -3): "<<C_5*pow(10, -3)<<" mu F"<<endl;
    cout<<"R_7: "<<R_7<<" Ohm"<<"; L_approx*pow(10, 3) "<<L_approx*pow(10, 3)<<" mH"<<endl;

    double beta2 = sqrt(1/(L_approx*C_5*pow(10, -3)) - R_7*R_7/(4*L_approx*pow(10, 3)*L_approx*pow(10, 3))); //[LC] = ms^2; [L/R] = ms^2
    cout<<"beta2 stima: "<<beta2<<endl;
    sovrasmorzamento->SetParameter(2, beta);

    TFitResultPtr fit_ptr7 = ge7->Fit("sovrasmorzamento", "S");
        
    ge7->Draw("AP");
    c7->SetGrid(1, 1);

   // TheApp.Run();

    c7->Print ("sovrasmorzamento.pdf", "pdf");
    double V0_7 = sovrasmorzamento->GetParameter(0);
    double V0_7_err = sovrasmorzamento->GetParError(0);
    double I0_7 = V0_7/R_7;
    double I0_7_err = sqrt(  pow(V0_7_err/R_7, 2) + pow(V0_7*0.1/(R_7*R_7), 2) );
    cout<<"I0_7 - sovramorzamento: "<<I0_7<<" pm "<<I0_7_err<<" A"<<endl;

    double gamma3 = sovrasmorzamento->GetParameter(1);
    double gamma3_err = sovrasmorzamento->GetParError(1);
    double tau_sovrasm = 1/(gamma3*2);
    double tau_sovrasm_err = gamma3_err/(2*gamma3*gamma3); 
    cout<<"tau - svorasmorzamento: "<<tau_sovrasm<<" pm "<<tau_sovrasm_err<<" ms"<<endl;

    double L_7 = tau_sovrasm*R_7*pow(10, -3);
    double L_7_err = sqrt(pow(tau_sovrasm_err*R_7*pow(10, -3), 2) + pow(0.0001*tau_sovrasm, 2)); // err R_5 = 0.1 Ohm = 0.0001 kOhm
    cout<<"L_7 - svorasmorzamento: "<<L_7<<" pm "<<L_7_err<<" H ?"<<endl;

    beta2 = sovrasmorzamento->GetParameter(2);
    double beta2_err = sovrasmorzamento->GetParError(2);
    cout<<"beta2: "<<beta2<<" "<<beta2_err<<endl;

    TMatrixD cov2 = fit_ptr7->GetCovarianceMatrix();
    cov2.Print();

    double omega_sq2 = pow( beta2, 2 ) + pow( gamma3, 2 );
    double omega_sq2_err = sqrt(  pow(2*beta2*beta2_err, 2) + pow(2*gamma3*gamma3_err, 2) + 4*beta2*gamma3*0.003826 );
    cout<<"omega_sq: "<<omega_sq2<<" pm "<<omega_sq2_err<<" ms"<<endl;

    double C_7 = 1/(L_7*omega_sq2);
    double C_7_err = sqrt(  pow(L_7_err/(pow(L_7, 2)*omega_sq2), 2) + pow(omega_sq2_err/(pow(omega_sq2, 2)*L_7), 2)  );
    cout<<"C_7: "<<C_7<<" pm "<<C_7_err<<" mu F?"<<endl;
    delete c7;
    return 0;
}