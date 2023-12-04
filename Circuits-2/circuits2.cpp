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

#include "data.h"
#include "stats.h"

using namespace std;
int main(int argc, char *argv[]){

//EXPERIMENT1: charge, Vc
    TApplication TheApp("TheApp", &argc, argv);
    cout<<"EXPERIMENT1:    RC-FALL ON C"<<endl;
    ofstream data_file1;

    double v_mean1[2];
    int size1 = (int) (sizeof(T_1)/sizeof(T_1[0]));


    data_file1.open("RC_fall_on_c.txt", ios::out);
    data_file1<<"#t \t V \t errV "<<endl;


    for(int i = 0; i<size1; i++){
        media_stdm(V_1[i], v_mean1, numeroMisure);
        if(v_mean1[1] == 0){
            v_mean1[1] = 2;
        }
        cout<<"v_mean1: "<<v_mean1[0]/1000<<"  "<<v_mean1[1]*1.4/1000<<";     valore in V"<<endl;
        data_file1<<T_1[i]<<" \t "<<v_mean1[0]/1000<<" \t "<<v_mean1[1]*1.4/1000<<endl; //Volt _ muA

    }
    gStyle->SetOptFit();

    TCanvas* c1 = new TCanvas("c1","c1", 800, 800);

    TGraphErrors *ge1 = new  TGraphErrors("RC_fall_on_c.txt" , "%lg %lg %lg"); 
    data_file1.close();
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


    TF1 *increaseRC = new TF1("increaseRC", "[0]*( 1 - 2*exp(-x/[1]) ) ", 0., 12.); 
    increaseRC->SetParameter(0, 1.);
    increaseRC->SetParameter(1, 2.39); //tau in ms

    TFitResultPtr fit_ptr1 = ge1->Fit("increaseRC", "S");
        
    ge1->Draw("AP");
    c1->SetGrid(1, 1);

    c1->Print ("increaseRC.pdf", "pdf");
    double Vg_1 = increaseRC->GetParameter(0);
    double Vg_1_err = increaseRC->GetParError(0);
    cout<<"Vg_1 estimate: "<<Vg_1<<" pm "<<Vg_1_err<<" V"<<";  to compare to 1.00 pm 0.01 V"<<endl;

    double tau_RC = increaseRC->GetParameter(1);
    double tau_RC_err = increaseRC->GetParError(1);
    cout<<"tau_RC: "<<tau_RC<<" pm "<<tau_RC_err<<endl;

    double C_1 = tau_RC/R_1;
    double C_1_err = sqrt(pow(tau_RC_err/(R_1), 2) + pow(0.001*tau_RC/(R_1*R_1), 2));
    cout<<"C_1 estimate: "<<C_1<<" pm "<<C_1_err<<"mu F"<<";  to compare to 2.42 pm 0.01 mu F"<<endl;
    
    delete c1;

//EXPERIMENT2: charge, Vr
    cout<<"EXPERIMENT2:    RC- FALL ON R"<<endl;
    ofstream data_file2;

    double v_mean2[2];
    int size2 = (int) (sizeof(T_2)/sizeof(T_2[0]));
    cout<<size2<<endl;

    data_file2.open("RC_fall_on_r.txt", ios::out);
    data_file2<<"#t \t V \t errV "<<endl;


    for(int i = 0; i<size2; i++){
        media_stdm(V_2[i], v_mean2, numeroMisure);
        if(v_mean2[1] == 0){
            v_mean2[1] = 2;
        }
        cout<<"v_mean2: "<<v_mean2[0]/1000<<"  "<<v_mean2[1]*3/1000<<";     valore in V"<<endl;
        data_file2<<T_2[i]<<" \t "<<v_mean2[0]/1000<<" \t "<<v_mean2[1]*3/1000<<endl; 

    }
    gStyle->SetOptFit();

    TCanvas* c2 = new TCanvas("c2","c2", 800, 800);

    TGraphErrors *ge2 = new  TGraphErrors("RC_fall_on_r.txt" , "%lg %lg %lg"); 
    data_file2.close();
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


    TF1 *decreaseRC = new TF1("decreaseRC", "2*[0]*exp(-x/[1]) ", 0., 30.); 
    decreaseRC->SetParameter(0, 1.);
    decreaseRC->SetParameter(1, 2.39);

    TFitResultPtr fit_ptr2 = ge2->Fit("decreaseRC", "S");
        
    ge2->Draw("AP");
    c2->SetGrid(1, 1);
  //  TheApp.Run();
    c2->Print ("decreaseRC.pdf", "pdf");
    double Vg_2 = decreaseRC->GetParameter(0);
    double Vg_2_err = decreaseRC->GetParError(0);
    cout<<"Vg_2 estimate: "<<Vg_2<<" pm "<<Vg_2_err<<" V"<<";  to compare to 1.00 pm 0.01 V"<<endl;

    double tau_RC2 = decreaseRC->GetParameter(1);
    double tau_RC2_err = decreaseRC->GetParError(1);
    cout<<"tau_RC2: "<<tau_RC2<<" pm "<<tau_RC2_err<<endl;

    double C_2 = tau_RC2/R_1;
    double C_2_err = sqrt(pow(tau_RC2_err/(R_1), 2) + pow(0.001*tau_RC2/(R_1*R_1), 2));
    cout<<"C_2 estimate: "<<C_2<<" pm "<<C_2_err<<"mu F"<<";  to compare to 2.42 pm 0.01 mu F"<<endl;

    delete c2;

//EXPERIMENT3: carica, Vl
    cout<<"EXPERIMENT3:    RL-CADUTA AI CAPI DI L"<<endl;
    ofstream data_file3;

    double v_mean3[2];
    int size3 = (int) (sizeof(T_3)/sizeof(T_3[0]));


    data_file3.open("RL_fall_on_l.txt", ios::out);
    data_file3<<"#t \t V \t errV "<<endl;


    for(int i = 0; i<size3; i++){
        media_stdm(V_3[i], v_mean3, numeroMisure);
        if(v_mean3[1] == 0){
            v_mean3[1] = 2;
        }
        cout<<"v_mean3: "<<v_mean3[0]/1000<<"  "<<v_mean3[1]*1.28/1000<<";     in V"<<endl;
        data_file3<<T_3[i]<<" \t "<<v_mean3[0]/1000<<" \t "<<v_mean3[1]*1.28/1000<<endl; 

    }
    gStyle->SetOptFit();

    TCanvas* c3 = new TCanvas("c3","c3", 800, 800);

    TGraphErrors *ge3 = new  TGraphErrors("RL_fall_on_l.txt" , "%lg %lg %lg"); 
    data_file3.close();
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


    TF1 *decreaseRL = new TF1("decreaseRL", "2*[0]*exp(-x/[1]) ", 0., 115.); //Resistence in MOhm and inductance in H
    decreaseRL->SetParameter(0, 1.);
    decreaseRL->SetParameter(1, 46.98); //tau RL in mu s

    TFitResultPtr fit_ptr3 = ge3->Fit("decreaseRL", "S");
        
    ge3->Draw("AP");
    c3->SetGrid(1, 1);

    c3->Print ("Graphs/decreaseRL.pdf", "pdf");
    double tau_RL = decreaseRL->GetParameter(1);
    double tau_RL_err = decreaseRL->GetParError(1);
    double L_3 = tau_RL*R_1/1000; //R_1 in MOhm
    double L_3_err = sqrt(pow(tau_RL_err*R_1/1000, 2) + pow(0.000001*tau_RL, 2)); //error on MOhm = 0.001/1000
    cout<< "L_3 estimate: "<<L_3<<" pm "<<L_3_err<<" H;    to compare to the next"<<endl;

    delete c3;

//EXPERIMENT4: carica, Vr
    cout<<"EXPERIMENT4:    RL-FALL ON R"<<endl;
    ofstream data_file4;

    double v_mean4[2];
    int size4 = (int) (sizeof(T_4)/sizeof(T_4[0]));


    data_file4.open("RL_fall_on_r.txt", ios::out);
    data_file4<<"#t \t V \t errV "<<endl;


    for(int i = 0; i<size4; i++){
        media_stdm(V_4[i], v_mean4, numeroMisure);
        cout<<"v_mean4: "<<v_mean4[0]/1000<<"  "<<v_mean4[1]*4/1000<<";     in V"<<endl;
        data_file4<<T_4[i]<<" \t "<<v_mean4[0]/1000<<" \t "<<v_mean4[1]*4/1000<<endl; 

    }
    gStyle->SetOptFit();

    TCanvas* c4 = new TCanvas("c4","c4", 800, 800);

    TGraphErrors *ge4 = new  TGraphErrors("RL_fall_on_r.txt" , "%lg %lg %lg"); 
    data_file4.close();
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


    TF1 *increaseRL = new TF1("increasingRL", "[0]*( 1 - 2*exp(-x/[1])) ", 0., 406.); 
    increaseRL->SetParameter(0, 0.883);
    increaseRL->SetParameter(1, 39.4);

    TFitResultPtr fit_ptr4 = ge4->Fit("increasingRL", "S");
        
    ge4->Draw("AP");
    c4->SetGrid(1, 1);


    c4->Print ("increasingRL.pdf", "pdf");
    double tau_RL2 = increaseRL->GetParameter(1);
    double tau_RL2_err = increaseRL->GetParError(1);
    double L_4 = tau_RL2*(R_1 + 0.1273)/1000; //correction R eq; MOhm
    double L_4_err = sqrt(pow(tau_RL2_err*(R_1 + 0.1273)/1000, 2) + pow(0.00003*tau_RL2, 2)); //error on MOhm = 0.03/1000
    cout<< "L_4 estimatete: "<<L_4<<" pm "<<L_4_err<<" H;    to compare to the previous"<<endl;

    delete c4;


//EXPERIMENT5: underdumping
    cout<<"EXPERIMENT5:    RLC-UNDERDUMPING"<<endl;
    ofstream data_file5;

    double v_mean5[2];
    int size5 = (int) (sizeof(T_5)/sizeof(T_5[0]));


    data_file5.open("RLC_underdumping.txt", ios::out);
    data_file5<<"#t \t V \t errV "<<endl;


    for(int i = 0; i<size5; i++){
        media_stdm(V_5[i], v_mean5, numeroMisure);
        cout<<"v_mean5: "<<v_mean5[0]/1000<<"  "<<v_mean5[1]*5/1000<<";     in V"<<endl;
        data_file5<<T_5[i]/1000<<" \t "<<v_mean5[0]/1000<<" \t "<<v_mean5[1]*5/1000<<endl; 

    }
    gStyle->SetOptFit();

    TCanvas* c5 = new TCanvas("c5","c5", 800, 800);

    TGraphErrors *ge5 = new  TGraphErrors("RLC_underdumping.txt" , "%lg %lg %lg"); 
    data_file5.close();
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


    TF1 *underdumping = new TF1("underdumping", "[0]*exp(-x*[1])*sin(x*[2]) ", 0., 1.5); //[x] = ms 
    underdumping->SetParameter(0, 0.25);

    double L_approx = 0.04519; //H
    cout<<"L/R estimate: "<<L_approx/(R_5*pow(10, -3))<<" ms"<<endl;

    underdumping->SetParameter( 1, (R_5*pow(10, -3))/(2*L_approx) ); //H/kOhm = ms

    cout<<"L_approx: "<<L_approx<<" H"<<"; C_5*pow(10, -3): "<<C_5*pow(10, -3)<<" mu F"<<endl;
    cout<<"R_5: "<<R_5<<" Ohm"<<"; L_approx*pow(10, 3) "<<L_approx*pow(10, 3)<<" mH"<<endl;

    double beta = sqrt(1/(L_approx*C_5*pow(10, -3)) - R_5*R_5/(4*L_approx*pow(10, 3)*L_approx*pow(10, 3))); //[LC] = ms^2; [L/R] = ms^2
    cout<<"beta estimate: "<<beta<<endl;
    underdumping->SetParameter(2, beta);

    TFitResultPtr fit_ptr5 = ge5->Fit("underdumping", "S");
        
    ge5->Draw("AP");
    c5->SetGrid(1, 1);

    c5->Print ("underdumping.pdf", "pdf");
    double V0_5 = underdumping->GetParameter(0);
    double V0_5_err = underdumping->GetParError(0);
    cout<<"V0_5 - underdumping: "<<V0_5<<" pm "<<V0_5_err<<" A"<<endl;

    double I0_5 = V0_5/R_5;
    double I0_5_err = sqrt(  pow(V0_5_err/R_5, 2) + pow(V0_5*0.1/(R_5*R_5), 2) );
    cout<<"I0_5 - underdumping: "<<I0_5<<" pm "<<I0_5_err<<" A"<<endl;

    double gamma1 = underdumping->GetParameter(1);
    double gamma1_err = underdumping->GetParError(1);
    cout<<"gamma - underdumping: "<<gamma1<<" "<<gamma1_err<<endl;
    double tau_underdumping = 0.5/gamma1;
    double tau_underdumping_err = gamma1_err/(2*gamma1*gamma1); 
    double L_5 = tau_underdumping*(R_5 + 127.3)*pow(10, -3);
    double L_5_err = sqrt(pow(tau_underdumping_err*(R_5 + 127.3)*pow(10, -3), 2) + pow(0.030*tau_underdumping, 2)); // err R_5 = 30 Ohm = 0.030 kOhm
    cout<<"L_5 - underdumping: "<<L_5<<" pm "<<L_5_err<<" H ?"<<endl;

    beta = underdumping->GetParameter(2);
    double beta_err = underdumping->GetParError(2);
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

//EXPERIMENT6: critical dumping
    cout<<"EXPERIMENT6:    RLC-CRITICAL DUMPING"<<endl;
    ofstream data_file6;
    int size6 = (int) (sizeof(T_6)/sizeof(T_6[0]));

    data_file6.open("RLC_critical_dumping.txt", ios::out);
    data_file6<<"#t \t V \t errV "<<endl;


    for(int i = 0; i<size6; i++){
        data_file6<<T_6[i]/1000<<" \t "<<V_6[i]/1000<<" \t "<<"0.002"<<endl; 
    }
    gStyle->SetOptFit();

    TCanvas* c6 = new TCanvas("c6","c6", 800, 800);

    TGraphErrors *ge6 = new  TGraphErrors("RLC_critical_dumping.txt" , "%lg %lg %lg"); 
    data_file6.close();
    ge6->SetTitle("RLC in carica - smorzamento critico");
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


    TF1 *critical_dumping = new TF1("critical_dumping", "[0]*x*exp(-[1]*x) ", 0., 0.54); //[x] = ms 
    underdumping->SetParameter(0, 1.3);
    cout<<"L/R estimate: "<<L_approx/(R_6*pow(10, -3))<<" ms"<<endl;
    critical_dumping->SetParameter( 1, (R_6*pow(10, -3))/(2*L_approx) ); //kOhm/H = 1/ms
    cout<<"L_approx: "<<L_approx<<" H"<<endl;
    cout<<"R_6: "<<R_6<<" Ohm"<<endl;

    TFitResultPtr fit_ptr6 = ge6->Fit("critical_dumping", "S");

    ge6->Draw("AP");
    c6->SetGrid(1, 1);

    c6->Print ("critical_dumping.pdf", "pdf");
    double V0_6 = critical_dumping->GetParameter(0);
    double V0_6_err = critical_dumping->GetParError(0);
    cout<<"V0_6 - critical_dumping: "<<V0_6<<" pm "<<V0_6_err<<" V"<<endl;

    double gamma2 = critical_dumping->GetParameter(1);
    double gamma2_err = critical_dumping->GetParError(1);
    double tau_critico = 1/(2*gamma2);
    double tau_critico_err = gamma2_err/(2*gamma2*gamma2); 
    double L_6 = tau_critico*R_6*pow(10, -3);
    double L_6_err = sqrt(pow(tau_critico_err*R_6*pow(10, -3), 2) + pow(0.0001*tau_critico, 2)); // err R_6 = 0.1 Ohm = 0.0001 kOhm 
    cout<<"L_6 - critical_dumping: "<<L_6<<" pm "<<L_6_err<<" H ?"<<endl;


    delete c6;
    TCanvas* c6b = new TCanvas("c6","c6", 800, 800);

    TFitResultPtr fit_ptr6b = ge6->Fit("underdumping", "S");

    ge6->Draw("AP");
    c6b->SetGrid(1, 1);

    c6b->Print ("smorzamento_sottocritico.pdf", "pdf");

    delete c6b;
   
//EXPERIMENT7: overdumping
    cout<<"EXPERIMENT7:    RLC-OVERDUMPING"<<endl;
    ofstream data_file7;

    int size7 = (int) (sizeof(T_7)/sizeof(T_7[0]));


    data_file7.open("RLC_overdumping.txt", ios::out);
    data_file7<<"#t \t V \t errV "<<endl;


    for(int i = 0; i<size7; i++){
        data_file7<<T_7[i]/1000<<" \t "<<V_7[i]/1000<<" \t "<<"0.004"<<endl; 

    }
    gStyle->SetOptFit();

    TCanvas* c7 = new TCanvas("c7","c7", 800, 800);

    TGraphErrors *ge7 = new  TGraphErrors("RLC_overdumping.txt" , "%lg %lg %lg"); 
    data_file7.close();
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


    TF1 *overdumping = new TF1("overdumping", "[0]*exp(-x*[1])*sinh(x*[2]) ", 0., 0.72); //[x] = ms 
    overdumping->SetParameter(0, 1.4);

    cout<<"L/R estimate: "<<L_approx/(R_7*pow(10, -3))<<" ms"<<endl;

    overdumping->SetParameter( 1, (R_7*pow(10, -3))/(2*L_approx) ); //H/kOhm = ms

    cout<<"L_approx: "<<L_approx<<" H"<<"; C_5*pow(10, -3): "<<C_5*pow(10, -3)<<" mu F"<<endl;
    cout<<"R_7: "<<R_7<<" Ohm"<<"; L_approx*pow(10, 3) "<<L_approx*pow(10, 3)<<" mH"<<endl;

    double beta2 = sqrt(1/(L_approx*C_5*pow(10, -3)) - R_7*R_7/(4*L_approx*pow(10, 3)*L_approx*pow(10, 3))); //[LC] = ms^2; [L/R] = ms^2
    cout<<"beta2 estimate: "<<beta2<<endl;
    overdumping->SetParameter(2, beta);

    TFitResultPtr fit_ptr7 = ge7->Fit("overdumping", "S");
        
    ge7->Draw("AP");
    c7->SetGrid(1, 1);

    c7->Print ("overdumping.pdf", "pdf");
    double V0_7 = overdumping->GetParameter(0);
    double V0_7_err = overdumping->GetParError(0);
    double I0_7 = V0_7/R_7;
    double I0_7_err = sqrt(  pow(V0_7_err/R_7, 2) + pow(V0_7*0.1/(R_7*R_7), 2) );
    cout<<"I0_7 - overdumping: "<<I0_7<<" pm "<<I0_7_err<<" A"<<endl;

    double gamma3 = overdumping->GetParameter(1);
    double gamma3_err = overdumping->GetParError(1);
    double tau_sovrasm = 1/(gamma3*2);
    double tau_sovrasm_err = gamma3_err/(2*gamma3*gamma3); 
    cout<<"tau - svorasmorzamento: "<<tau_sovrasm<<" pm "<<tau_sovrasm_err<<" ms"<<endl;

    double L_7 = tau_sovrasm*R_7*pow(10, -3);
    double L_7_err = sqrt(pow(tau_sovrasm_err*R_7*pow(10, -3), 2) + pow(0.0001*tau_sovrasm, 2)); // err R_5 = 0.1 Ohm = 0.0001 kOhm
    cout<<"L_7 - svorasmorzamento: "<<L_7<<" pm "<<L_7_err<<" H ?"<<endl;

    beta2 = overdumping->GetParameter(2);
    double beta2_err = overdumping->GetParError(2);
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