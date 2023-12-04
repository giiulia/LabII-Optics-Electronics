#include <iostream>
#include <cmath>
#include <fstream>

#include "TCanvas.h"
#include "TH1F.h"
#include "TApplication.h"
#include "TF1.h"
#include "TGraphErrors.h"
#include "TFitResult.h"
#include "TPad.h"
#include "TPaveStats.h"
#include "TStyle.h"
#include "TMatrixD.h"

#include "data.h"

using namespace std;
int main(int argc, char *argv[]){

//EXPERIMENT1: RC
  TApplication TheApp("TheApp", &argc, argv);
  cout<<"EXPERIMENT1: RC"<<endl;
  ofstream data_file1;
  ofstream data_file2;

  int size1 = (int) (sizeof(freq1)/sizeof(freq1[0]));

  data_file1.open("Data/RC-endsofC-sheer_value.txt", ios::out);
  data_file1<<"#f \t VAB/VA \t errV "<<endl;

  cout<<"at ends of C - sheer_value:"<<endl;
  double err;
  double err_VAB;
  double err_VA;
  for(int i = 0; i<size1; i++){
    err_VAB = V1_AB[i]/100;
    err_VA = V1_A[i]/100;
    err = sqrt( pow(err_VA*V1_AB[i]/pow(V1_A[i], 2), 2) + pow(err_VAB/V1_A[i], 2) );
    data_file1<<freq1[i]<<" \t "<<V1_AB[i]/V1_A[i]<<" \t "<<err<<endl;
    cout<<freq1[i]<<" \t& "<<V1_A[i]<<" "<<err_VA<<" \t& "<<V1_AB[i]<<"$   $"<<err_VAB<<" \t& "<<V1_AB[i]/V1_A[i]<<" $ $ "<<err<<"\\"<<endl;
  }

  gStyle->SetOptFit();

  TCanvas* c1 = new TCanvas("c1","c1", 800, 800);
  c1->SetLogx();

  TGraphErrors *ge1 = new  TGraphErrors("Data/RC-endsofC-sheer_value.txt" , "%lg %lg %lg"); 
  data_file1.close();
  ge1->SetTitle(" ");
  ge1->GetXaxis()->SetTitle("freq[Hz]");
  ge1->GetYaxis()->SetTitle("Voltaggio[V]");

  ge1->GetXaxis()->SetTitleSize(0.035);
  ge1->GetXaxis()->SetTitleOffset(1.3);
  ge1->GetXaxis()->SetLabelSize(0.040);

  ge1->GetYaxis()->SetTitleSize(0.034);
  ge1->GetYaxis()->SetTitleOffset(1.39);
  ge1->GetYaxis()->SetLabelSize(0.040);


  ge1->SetMarkerStyle(20);
  ge1->SetMarkerSize(0.5);

  ge1->GetYaxis()->SetNdivisions(5, 5, 0);
  ge1->GetXaxis()->SetNdivisions(10, 5, 0);   
  
  TF1 *RC_C_sheer_value = new TF1("RC-C-sheer_value", " 1/(sqrt(( 2*3.1415*x)^2*[0]^2*[1]^2 +1) )", 0., 2*pow(10, 3)); 
  RC_C_sheer_value->SetParNames("R", "C");
  RC_C_sheer_value->SetParameter(0, 6103);
  RC_C_sheer_value->SetParameter(1, 1.99*pow(10, -8));


  TFitResultPtr fit_ptr1 = ge1->Fit("RC-C-sheer_value", "S");
      
  ge1->Draw("AP");
  c1->SetGrid(1, 1);
  c1->Print ("Graphs/RC-C_sheer_value.png", "png");

  double C_sheer_value = RC_C_sheer_value->GetParameter(1);
  double C_sheer_value_err = RC_C_sheer_value->GetParError(1);
  cout<<"estimate of C got with sheer_value: "<<C_sheer_value <<" pm "<<C_sheer_value_err<<endl;
  
  delete c1;

  data_file2.open("Data/RC-endsofC_phase.txt", ios::out);
  data_file2<<"#f \t PhiAB \t errPhi "<<endl;


  cout<<"a ends of C - phase:"<<endl;
  double err_phase_VAB;
  for(int i = 0; i<size1; i++){
    if(phase1_AB[i] > -10){
      err_phase_VAB = sqrt(pow(phase1_AB[i]*2/100, 2))*sqrt(2); //2 %
    }
    else err_phase_VAB = sqrt(pow(phase1_AB[i]/100, 2))*sqrt(2); // 1%
    data_file2<<freq1[i]<<" \t "<<phase1_AB[i]<<" \t "<<err_phase_VAB<<endl;
    cout<<" \t&"<<phase1_AB[i]<<" $ $ "<<err_phase_VAB<<endl;

  }

  gStyle->SetOptFit();

  TCanvas* c2 = new TCanvas("c2","c2", 800, 800);
  c2->SetLogx();

  TGraphErrors *ge2 = new  TGraphErrors("Data/RC-endsofC_phase.txt" , "%lg %lg %lg"); 
  data_file2.close();
  ge2->SetTitle(" ");
  ge2->GetXaxis()->SetTitle("freq[Hz]");
  ge2->GetYaxis()->SetTitle("Voltaggio[V]");

  ge2->GetXaxis()->SetTitleSize(0.035);
  ge2->GetXaxis()->SetTitleOffset(1.3);
  ge2->GetXaxis()->SetLabelSize(0.040);

  ge2->GetYaxis()->SetTitleSize(0.034);
  ge2->GetYaxis()->SetTitleOffset(1.39);
  ge2->GetYaxis()->SetLabelSize(0.040);


  ge2->SetMarkerStyle(20);
  ge2->SetMarkerSize(0.5);

  ge2->GetYaxis()->SetNdivisions(5, 5, 0);
  ge2->GetXaxis()->SetNdivisions(10, 5, 0);   
  
  TF1 *RC_C_phase = new TF1("RC-C-phase", " -atan( 2*3.1415*x*[0]*[1])*180/3.1415 ", 0., 2*pow(10, 3)); 
  RC_C_phase->SetParNames("R", "C");
  RC_C_phase->SetParameter(0, 4103);
  RC_C_phase->SetParameter(1, 1.99*pow(10, -8));

  TFitResultPtr fit_ptr2 = ge2->Fit("RC-C-phase", "S");
      
  ge2->Draw("AP");
  c2->SetGrid(1, 1);
  c2->Print ("Graphs/RC-C-phase.png", "png");

  double C_phase = RC_C_phase ->GetParameter(1);
  double C_phase_err = RC_C_phase ->GetParError(1);
  cout<<"estimate of C got with the phase: "<<C_phase<<" pm "<<C_phase_err<<endl;
  delete c2;

  ofstream data_file9;
  ofstream data_file10;

  data_file9.open("Data/RC-endsofR-sheer_value.txt", ios::out);
  data_file9<<"#f \t VB/VA \t errV "<<endl;

  cout<<"at ends of R - sheer_value:"<<endl;
  double err_VB;
  for(int i = 0; i<size1; i++){
    err_VB = V1_B[i]/100;
    err_VA = V1_A[i]/100;
    err = sqrt( pow(err_VA*V1_B[i]/pow(V1_A[i], 2), 2) + pow(err_VB/V1_A[i], 2) );
    data_file9<<freq1[i]<<" \t "<<V1_B[i]/V1_A[i]<<" \t "<<err<<endl;
    cout<<freq1[i]<<" \t& "<<V1_A[i]<<" $ $ "<<err_VA<<" \t& "<<V1_B[i]<<" $ $ "<<err_VB<<" \t& "<<V1_B[i]/V1_A[i]<<" $ $ "<<err<<"\\"<<endl;
  }

  gStyle->SetOptFit();

  TCanvas* c9 = new TCanvas("c9","c9", 800, 800);
  c9->SetLogx();

  TGraphErrors *ge9 = new  TGraphErrors("Data/RC-endsofR-sheer_value.txt" , "%lg %lg %lg"); 
  data_file9.close();
  ge9->SetTitle(" ");
  ge9->GetXaxis()->SetTitle("freq[Hz]");
  ge9->GetYaxis()->SetTitle("Voltaggio[V]");

  ge9->GetXaxis()->SetTitleSize(0.035);
  ge9->GetXaxis()->SetTitleOffset(1.3);
  ge9->GetXaxis()->SetLabelSize(0.040);

  ge9->GetYaxis()->SetTitleSize(0.034);
  ge9->GetYaxis()->SetTitleOffset(1.39);
  ge9->GetYaxis()->SetLabelSize(0.040);


  ge9->SetMarkerStyle(20);
  ge9->SetMarkerSize(0.5);

  ge9->GetYaxis()->SetNdivisions(5, 5, 0);
  ge9->GetXaxis()->SetNdivisions(10, 5, 0);   
  
  TF1 *RC_R_sheer_value = new TF1("RC-R-sheer_value", " [0]*[1]* 2*3.1415*x/sqrt(1 + [0]^2*[1]^2*( 2*3.1415*x)^2) ", 0., 2*pow(10, 3)); 
  RC_R_sheer_value->SetParNames("R", "C");
  RC_R_sheer_value->SetParameter(0, 4103);
  RC_R_sheer_value->SetParameter(1, 1.99*pow(10, -8));

  TFitResultPtr fit_ptr9 = ge9->Fit("RC-R-sheer_value", "S");
      
  ge9->Draw("AP");
  c9->SetGrid(1, 1);
  c9->Print ("Graphs/RC-R-sheer_value.png", "png");

  C_sheer_value = RC_R_sheer_value->GetParameter(1);
  C_sheer_value_err = RC_R_sheer_value->GetParError(1);
  cout<<"estimate of C got with sheer_value at ends of R: "<<C_sheer_value <<" pm "<<C_sheer_value_err<<endl;

  delete c9;

  data_file10.open("Data/RC-endsofR-phase.txt", ios::out);
  data_file10<<"#f \t PhiB \t errPhi "<<endl;


  cout<<"at ends of R - phase:"<<endl;
  double err_phase_B;
  for(int i = 0; i<size1; i++){
    if(phase1_B[i] < 10){
      err_phase_B = sqrt(2)*(phase1_B[i]*2/100);
    }
    else err_phase_B = (phase1_B[i]/100)*sqrt(2);

    data_file10<<freq1[i]<<" \t "<<phase1_B[i]<<" \t "<<err_phase_B<<endl;
    cout<<" \t& "<<phase1_B[i]<<" $ $ "<<err_phase_B<<" \t ";

  }

  gStyle->SetOptFit();

  TCanvas* c10 = new TCanvas("c10","c10", 800, 800);
  c10->SetLogx();

  TGraphErrors *ge10 = new  TGraphErrors("Data/RC-endsofR-phase.txt" , "%lg %lg %lg"); 
  data_file10.close();
  ge10->SetTitle(" ");
  ge10->GetXaxis()->SetTitle("freq[Hz]");
  ge10->GetYaxis()->SetTitle("Voltaggio[V]");

  ge10->GetXaxis()->SetTitleSize(0.035);
  ge10->GetXaxis()->SetTitleOffset(1.3);
  ge10->GetXaxis()->SetLabelSize(0.040);

  ge10->GetYaxis()->SetTitleSize(0.034);
  ge10->GetYaxis()->SetTitleOffset(1.39);
  ge10->GetYaxis()->SetLabelSize(0.040);


  ge10->SetMarkerStyle(20);
  ge10->SetMarkerSize(0.5);

  ge10->GetYaxis()->SetNdivisions(5, 5, 0);
  ge10->GetXaxis()->SetNdivisions(10, 5, 0);   
  
  TF1 *RC_R_phase = new TF1("RC-R-phase", " ( (3.1415/2) - atan( 2*3.1415*x*[0]*[1]) )*180/3.1415 ", 0., 2*pow(10, 3)); 
  RC_R_phase->SetParNames("R", "C");
  RC_R_phase->SetParameter(0, 4103);
  RC_R_phase->SetParameter(1, 1.99*pow(10, -8));

  TFitResultPtr fit_ptr10 = ge10->Fit("RC-R-phase", "S");
      
  ge10->Draw("AP");
  c10->SetGrid(1, 1);
  c10->Print ("Graphs/RC-R-phase.png", "png");
  C_phase = RC_R_phase->GetParameter(1);
  C_phase_err = RC_R_phase->GetParError(1);
  cout<<"estimate of C got with sheer_value at ends of R: "<<C_phase<<" pm "<<C_phase_err<<endl;


  delete c10;

//EXPERIMENT2: RL
  cout<<"EXPERIMENT2: RL"<<endl;
  ofstream data_file11;
  ofstream data_file12;

  int size2 = (int) (sizeof(freq2)/sizeof(freq2[0]));

  data_file11.open("Data/RL-endsofL-sheer_value.txt", ios::out);
  data_file11<<"#f \t VAB/VA \t errV "<<endl;

  cout<<"at ends of L - sheer_value:"<<endl;

  for(int i = 0; i<size2-6; i++){
    err_VAB = V2_AB[i]/100;
    err = sqrt( pow(0.1*V2_AB[i]/pow(V2_A[i], 2), 2) + pow(err_VAB/V2_A[i], 2) );
    data_file11<<freq2[i]<<" \t "<<V2_AB[i]/V2_A[i]<<" \t "<<err<<endl;
    cout<<freq2[i]<<" \t & "<<V2_A[i]<<" $ $ "<<err_VA<<" \t& "<<V2_AB[i]<<" $ $ "<<err_VAB<<" \t & "<<V2_AB[i]/V2_A[i]<<" $pm$ "<<err<<"\\"<<endl;
  }

  gStyle->SetOptFit();

  TCanvas* c11 = new TCanvas("c11","c11", 800, 800);
  c11->SetLogx();

  TGraphErrors *ge11 = new  TGraphErrors("Data/RL-endsofL-sheer_value.txt" , "%lg %lg %lg"); 
  data_file11.close();
  ge11->SetTitle(" ");
  ge11->GetXaxis()->SetTitle("freq[Hz]");
  ge11->GetYaxis()->SetTitle("Voltaggio[V]");

  ge11->GetXaxis()->SetTitleSize(0.035);
  ge11->GetXaxis()->SetTitleOffset(1.3);
  ge11->GetXaxis()->SetLabelSize(0.040);

  ge11->GetYaxis()->SetTitleSize(0.034);
  ge11->GetYaxis()->SetTitleOffset(1.39);
  ge11->GetYaxis()->SetLabelSize(0.040);


  ge11->SetMarkerStyle(20);
  ge11->SetMarkerSize(0.5);

  ge11->GetYaxis()->SetNdivisions(5, 5, 0);
  ge11->GetXaxis()->SetNdivisions(10, 5, 0);   
  
  
  TF1 *RL_L_sheer_value = new TF1("RL-L-sheer_value", "  2*3.1415*x*[1]/sqrt([0]^2 + ( 2*3.1415*x)^2*[1]^2 )  ", 0., 160*pow(10, 3)); 
  RL_L_sheer_value->SetParNames("R", "L");
  RL_L_sheer_value->SetParameter(0, 6103);
  RL_L_sheer_value->SetParameter(1, 0.564);
  TFitResultPtr fit_ptr11 = ge11->Fit("RL-L-sheer_value", "S");
      
  ge11->Draw("AP");
  c11->SetGrid(1, 1);
  c11->Print ("Graphs/RL-L-sheer_value.png", "png");
  double L_sheer_value = RC_R_phase->GetParameter(1);
  double L_sheer_value_err = RC_R_phase->GetParError(1);
  cout<<"estimate of L got with sheer_value: "<<L_sheer_value<<" pm "<<L_sheer_value_err<<endl;


  
  delete c11;

  data_file12.open("Data/RL-endsofL-phase.txt", ios::out);
  data_file12<<"#f \t PhiAB \t errPhi "<<endl;

  int size2f = (int) (sizeof(freq2fasi)/sizeof(freq2fasi[0]));

  cout<<"at ends of L - phase:"<<endl;
  for(int i = 0; i<size2f-6; i++){
    if(phase2_AB[i] <10){
      err_phase_VAB = phase2_AB[i]*2*sqrt(2)/100; //2%
    }
    err_phase_VAB = phase2_AB[i]*sqrt(2)/100;//1%

    data_file12<<freq2fasi[i]<<" \t "<<phase2_AB[i]<<" \t "<<err_phase_VAB<<endl;
    cout<<freq2fasi[i]<<" \t& "<<phase2_AB[i]<<" $ $ "<<err_phase_VAB<<" \t ";

  }

  gStyle->SetOptFit();

  TCanvas* c12 = new TCanvas("c12","c12", 800, 800);
  c12->SetLogx();

  TGraphErrors *ge12 = new  TGraphErrors("Data/RL-endsofL-phase.txt" , "%lg %lg %lg"); 
  data_file12.close();
  ge12->SetTitle(" ");
  ge12->GetXaxis()->SetTitle("freq[Hz]");
  ge12->GetYaxis()->SetTitle("Voltaggio[V]");

  ge12->GetXaxis()->SetTitleSize(0.035);
  ge12->GetXaxis()->SetTitleOffset(1.3);
  ge12->GetXaxis()->SetLabelSize(0.040);

  ge12->GetYaxis()->SetTitleSize(0.034);
  ge12->GetYaxis()->SetTitleOffset(1.39);
  ge12->GetYaxis()->SetLabelSize(0.040);


  ge12->SetMarkerStyle(20);
  ge12->SetMarkerSize(0.5);

  ge12->GetYaxis()->SetNdivisions(5, 5, 0);
  ge12->GetXaxis()->SetNdivisions(10, 5, 0);   

  TF1 *RL_L_phase = new TF1("RL-L-phase", " ( (3.1415/2) - atan( 2*3.1415*x*[1]/[0]) )*180/3.1415 ", 0., 160*pow(10, 3)); 
  RL_L_phase->SetParNames("R", "L");
  RL_L_phase->SetParameter(0, 6103);
  RL_L_phase->SetParameter(1, 0.564);


  TFitResultPtr fit_ptr12 = ge12->Fit("RL-L-phase", "S");
      
  ge12->Draw("AP");
  c12->SetGrid(1, 1);
  c12->Print ("Graphs/RL-L-phase.png", "png");
  delete c12;
  double L_phase = RL_L_phase->GetParameter(1);
  double L_phase_err = RL_L_phase->GetParError(1);
  cout<<"estimate of L got with the phase: "<<L_phase<<" pm "<<L_phase_err<<endl;


  ofstream data_file13;
  ofstream data_file14;

  data_file13.open("Data/RL-endsofR-sheer_value.txt", ios::out);
  data_file13<<"#f \t VB/VA \t errV "<<endl;

  cout<<"at ends of R - sheer_value:"<<endl;

  for(int i = 0; i<size2-6; i++){
    err_VB = V2_B[i]/100;
    err_VA = V2_A[i]/100;
    err = sqrt( pow(err_VA*V2_B[i]/pow(V2_A[i], 2), 2) + pow(err_VB/V2_A[i], 2) );
    data_file13<<freq2[i]<<" \t "<<V2_B[i]/V2_A[i]<<" \t "<<err<<endl;
    cout<<freq2[i]<<" \t& "<<V2_A[i]<<" $ $ "<<err_VA<<" \t& "<<V2_B[i]<<" $ $ "<<err_VB<<" \t& "<<V2_B[i]/V2_A[i]<<" $ $ "<<err<<"\\"<<endl;
  }

  gStyle->SetOptFit();

  TCanvas* c13 = new TCanvas("c13","c13", 800, 800);
  c13->SetLogx();

  TGraphErrors *ge13 = new  TGraphErrors("Data/RL-endsofR-sheer_value.txt" , "%lg %lg %lg"); 
  data_file13.close();
  ge13->SetTitle(" ");
  ge13->GetXaxis()->SetTitle("freq[Hz]");
  ge13->GetYaxis()->SetTitle("Voltaggio[V]");

  ge13->GetXaxis()->SetTitleSize(0.035);
  ge13->GetXaxis()->SetTitleOffset(1.3);
  ge13->GetXaxis()->SetLabelSize(0.040);

  ge13->GetYaxis()->SetTitleSize(0.034);
  ge13->GetYaxis()->SetTitleOffset(1.39);
  ge13->GetYaxis()->SetLabelSize(0.040);


  ge13->SetMarkerStyle(20);
  ge13->SetMarkerSize(0.5);

  ge13->GetYaxis()->SetNdivisions(5, 5, 0);
  ge13->GetXaxis()->SetNdivisions(10, 5, 0);   
  
  TF1 *RL_R_sheer_value = new TF1("RL_R_sheer_value", "[0]/sqrt([0]^2 + ( 2*3.1415*x*[1])^2)", 0., 160*pow(10, 3)); 
  RL_R_sheer_value->SetParNames("R", "L");
  RL_R_sheer_value->SetParameter(0, 6426);
  RL_R_sheer_value->SetParameter(1, 2.613);


  TFitResultPtr fit_ptr13 = ge13->Fit("RL_R_sheer_value", "S");
      
  ge13->Draw("AP");
  c13->SetGrid(1, 1);
  TheApp.Run();
  c13->Print ("RL-R-sheer_value.png", "png");

  L_sheer_value = RL_R_sheer_value->GetParameter(1);
  L_phase_err = RL_R_sheer_value->GetParError(1);
  cout<<"estimate of L ottenuta: "<<L_sheer_value<<" pm "<<L_sheer_value_err<<endl;

  delete c13;  

  data_file14.open("Data/RL-endsofR-phase.txt", ios::out);
  data_file14<<"#f \t PhiB \t errPhi "<<endl;


  cout<<"at ends of R - phase:"<<endl;

  for(int i = 0; i<size2f-6; i++){
    if(phase2_B[i] > -10){
      err_phase_B = sqrt(pow(phase2_B[i]*2*sqrt(2)/100, 2));
    }
    err_phase_B = sqrt(pow(phase2_B[i]*sqrt(2)/100, 2));

    data_file14<<freq2fasi[i]<<" \t "<<phase2_B[i]<<" \t "<<err_phase_B<<endl;
    cout<<" \t& "<<phase2_B[i]<<" $pm$ "<<err_phase_B<<" \t ";

  }

  gStyle->SetOptFit();

  TCanvas* c14 = new TCanvas("c14","c14", 800, 800);
  c14->SetLogx();

  TGraphErrors *ge14 = new  TGraphErrors("Data/RL-endsofR-phase.txt" , "%lg %lg %lg"); 
  data_file14.close();
  ge14->SetTitle(" ");
  ge14->GetXaxis()->SetTitle("freq[Hz]");
  ge14->GetYaxis()->SetTitle("Voltaggio[V]");

  ge14->GetXaxis()->SetTitleSize(0.035);
  ge14->GetXaxis()->SetTitleOffset(1.3);
  ge14->GetXaxis()->SetLabelSize(0.040);

  ge14->GetYaxis()->SetTitleSize(0.034);
  ge14->GetYaxis()->SetTitleOffset(1.39);
  ge14->GetYaxis()->SetLabelSize(0.040);


  ge14->SetMarkerStyle(20);
  ge14->SetMarkerSize(0.5);

  ge14->GetYaxis()->SetNdivisions(5, 5, 0);
  ge14->GetXaxis()->SetNdivisions(10, 5, 0);   
  
  TF1 *RL_R_phase = new TF1("RL_R_phase", "-atan( 2*3.1415*x*[1]/[0])*180/3.1415", 0., 160*pow(10, 3)); 
  RL_R_phase->SetParNames("R", "L");
  RL_R_phase->SetParameter(0, 4103);
  RL_R_phase->SetParameter(1, 2.164);

  TFitResultPtr fit_ptr14 = ge14->Fit("RL_R_phase", "S");
      
  ge14->Draw("AP");
  c14->SetGrid(1, 1);
  TheApp.Run();
  c14->Print ("Graphs/RL-R-phase.png", "png");
  delete c14;

  L_phase = RL_R_phase->GetParameter(1);
  L_phase_err = RL_R_phase->GetParError(1);
  cout<<"estimate of L ottenuta at ends of R: "<<L_phase<<" pm "<<L_phase_err<<endl;

  TMatrixD cov = fit_ptr14->GetCovarianceMatrix();
  cov.Print();

//EXPERIMENT3: RLC at ends of R
  cout<<"EXPERIMENT3:    RLC-CADUTA AI CAPI DI R"<<endl;
  ofstream data_file3;
  ofstream data_file4;

  int size3 = (int) (sizeof(freq3)/sizeof(freq3[0]));

  data_file3.open("Data/RLC-endsofR-sheer_value.txt", ios::out);
  data_file3<<"#f \t V \t errV "<<endl;


  cout<<"at ends of R - sheer_value:"<<endl;

  for(int i = 0; i<size3; i++){
    err_VA = V3_A[i]/100;
    err_VB = V3_B[i]/100;
    err = sqrt( pow(err_VA*V3_B[i]/pow(V3_A[i], 2), 2) + pow(err_VB/V3_A[i], 2) );
    data_file3<<freq3[i]<<" \t "<<V3_B[i]/V3_A[i]<<" \t "<<err<<endl;
    cout<<freq3[i]<<" \t& "<<V3_A[i]<<" $ $ "<<err_VA<<" \t& "<<V3_B[i]<<" $ $ "<<err_VB<<" \t& "<<V3_B[i]/V3_A[i]<<" $ $ "<<err<<"\\"<<endl;

  }


  TCanvas* c3 = new TCanvas("c3","c3", 800, 800);
  c3->SetLogx();

  TGraphErrors *ge3 = new  TGraphErrors("Data/RLC-endsofR-sheer_value.txt" , "%lg %lg %lg"); 
  data_file3.close();
  ge3->SetTitle(" ");
  ge3->GetXaxis()->SetTitle("freq[Hz]");
  ge3->GetYaxis()->SetTitle("Voltaggio[V]");

  ge3->GetXaxis()->SetTitleSize(0.035);
  ge3->GetXaxis()->SetTitleOffset(1.3);
  ge3->GetXaxis()->SetLabelSize(0.040);

  ge3->GetYaxis()->SetTitleSize(0.034);
  ge3->GetYaxis()->SetTitleOffset(1.39);
  ge3->GetYaxis()->SetLabelSize(0.040);

  ge3->SetMarkerStyle(20);
  ge3->SetMarkerSize(0.5);

  ge3->GetYaxis()->SetNdivisions(5, 5, 0);
  ge3->GetXaxis()->SetNdivisions(10, 5, 0);   

  TF1 *RLC_R_sheer_value = new TF1("RLC_R_sheer_value", " 2*3.1415*x*[0]*[1]/sqrt( ( 2*3.1415*x)^2*[1]^2*[0]^2 + (( 2*3.1415*x)^2*[2]*[1] - 1)^2  )", 0., 160*pow(10, 3)); 
  RLC_R_sheer_value->SetParNames("R", "C", "L");
  RLC_R_sheer_value->SetParameter(0, 6103);
  RLC_R_sheer_value->SetParameter(1, 1.99*pow(10, -8));
  RLC_R_sheer_value->SetParameter(2, 0.514);

  TFitResultPtr fit_ptr3 = ge3->Fit("RLC_R_sheer_value", "S");
      
  ge3->Draw("AP");
  c3->SetGrid(1, 1);
  c3->Print ("Graphs/RLC-R-sheer_value.png", "png");

  C_sheer_value = RLC_R_sheer_value->GetParameter(1);
  C_sheer_value_err = RLC_R_sheer_value->GetParError(1);
  cout<<"estimate of C ottenuta at ends of R: "<<C_sheer_value<<" pm "<<C_sheer_value_err<<endl;
  

  L_sheer_value = RLC_R_sheer_value->GetParameter(2);
  L_sheer_value_err = RLC_R_sheer_value->GetParError(2);
  cout<<"estimate of L ottenuta at ends of R: "<<L_sheer_value<<" pm "<<L_sheer_value_err<<endl;

  delete c3;


  data_file4.open("Data/RLC-endsofR-phase.txt", ios::out);
  data_file4<<"#f \t phase \t errFase "<<endl;


  cout<<"at ends of R - phase:"<<endl;

  for(int i = 0; i<size3; i++){
    err_phase_B =sqrt(pow(phase3_B[i]*sqrt(2)/100, 2));

    data_file4<<freq3[i]<<" \t "<<phase3_B[i]<<" \t "<<err_phase_B<<endl;
    cout<<" \t& "<<phase3_B[i]<<" $pm$ "<<err_phase_B<<" \t ";

  }

  gStyle->SetOptFit();

  TCanvas* c4 = new TCanvas("c4","c4", 800, 800);
  c4->SetLogx();

  TGraphErrors *ge4 = new  TGraphErrors("Data/RLC-endsofR-phase.txt" , "%lg %lg %lg"); 
  data_file4.close();
  ge4->SetTitle(" ");
  ge4->GetXaxis()->SetTitle("freq[Hz]");
  ge4->GetYaxis()->SetTitle("phase[rad]");

  ge4->GetXaxis()->SetTitleSize(0.035);
  ge4->GetXaxis()->SetTitleOffset(1.3);
  ge4->GetXaxis()->SetLabelSize(0.040);

  ge4->GetYaxis()->SetTitleSize(0.034);
  ge4->GetYaxis()->SetTitleOffset(1.39);
  ge4->GetYaxis()->SetLabelSize(0.040);


  ge4->SetMarkerStyle(20);
  ge4->SetMarkerSize(0.5);

  ge4->GetYaxis()->SetNdivisions(5, 5, 0);
  ge4->GetXaxis()->SetNdivisions(16, 5, 0);     


  TF1 *RLC_R_phase = new TF1("RLC_R_phase", "-atan((  2*3.1415*x*[2] - 1/( 2*3.1415*x*[1]) ) / [0])*180/3.1415", 0., 160*pow(10, 3)); 
  RLC_R_phase->SetParNames("R", "C", "L");
  RLC_R_phase->SetParameter(0, 6780);
  RLC_R_phase->SetParameter(1, 1.99*pow(10, -8));
  RLC_R_phase->SetParameter(2, 0.564);


  TFitResultPtr fit_ptr4 = ge4->Fit("RLC_R_phase", "S");
      
  ge4->Draw("AP");
  c4->SetGrid(1, 1);
 // TheApp.Run();
  c4->Print ("Graphs/RLC-R-phase.png", "png");
  
  C_phase = RLC_R_phase->GetParameter(1);
  C_phase_err = RLC_R_phase->GetParError(1);
  cout<<"estimate of C ottenuta at ends of R con la phase: "<<C_phase<<" $pm$ "<<C_phase_err<<endl;

  L_phase = RLC_R_phase->GetParameter(2);
  L_phase_err = RLC_R_phase->GetParError(2);
  cout<<"estimate of L ottenuta at ends of R con la phase: "<<L_phase<<" $pm$ "<<L_phase_err<<endl;
  cout<<"Ndf: "<<fit_ptr4->Ndf()<<endl;


  delete c4;
 

 //EXPERIMENT4: RLC at ends of C
  cout<<"EXPERIMENT4:    RLC-CADUTA AI CAPI DI C"<<endl;
  ofstream data_file5;
  ofstream data_file6;

  int size4 = (int) (sizeof(freq4)/sizeof(freq4[0]));

  data_file5.open("Data/RLC-endsofC-sheer_value.txt", ios::out);
  data_file5<<"#f \t V \t errV "<<endl;


  gStyle->SetOptFit();

  cout<<"at ends of C - sheer_value:"<<endl;

  for(int i = 0; i<size4; i++){
    err_VA = V4_A[i]/100;
    err_VB = V4_B[i]/100;
    err = sqrt( pow(err_VA*V4_B[i]/pow(V4_A[i], 2), 2) + pow(err_VB/V4_A[i], 2) );

    data_file5<<freq4[i]<<" \t "<<V4_B[i]/V4_A[i]<<" \t "<<err<<endl;
    cout<<freq4[i]<<" \t "<<V4_A[i]<<" $ $ "<<err_VA<<" \t& "<<V4_B[i]<<" $ $ "<<err_VB<<" \t& "<<V4_B[i]/V4_A[i]<<" $pm$ "<<err<<"\\"<<endl;

  }

  TCanvas* c5 = new TCanvas("c5","c5", 800, 800);
  c5->SetLogx();

  TGraphErrors *ge5 = new  TGraphErrors("Data/RLC-endsofC-sheer_value.txt" , "%lg %lg %lg"); 
  data_file5.close();
  ge5->SetTitle(" ");
  ge5->GetXaxis()->SetTitle("freq[Hz]");
  ge5->GetYaxis()->SetTitle("Voltaggio[V]");

  ge5->GetXaxis()->SetTitleSize(0.035);
  ge5->GetXaxis()->SetTitleOffset(1.3);
  ge5->GetXaxis()->SetLabelSize(0.040);

  ge5->GetYaxis()->SetTitleSize(0.034);
  ge5->GetYaxis()->SetTitleOffset(1.39);
  ge5->GetYaxis()->SetLabelSize(0.040);


  ge5->SetMarkerStyle(20);
  ge5->SetMarkerSize(0.5);

  ge5->GetYaxis()->SetNdivisions(5, 5, 0);
  ge5->GetXaxis()->SetNdivisions(10, 5, 0);   
  
  TF1 *RLC_C_sheer_value = new TF1("RLC_C_sheer_value", "  1/(   2*3.1415*x*[1]*sqrt([0]^2 + ( 2*3.1415*x*[2] - 1/( 2*3.1415*x*[1]))^2)  )  ", 0., 160*pow(10, 3)); 
  RLC_C_sheer_value->SetParNames("R", "C", "L");
  RLC_C_sheer_value->SetParameter(0, 3803);
  RLC_C_sheer_value->SetParameter(1, 2*pow(10, -7));
  RLC_C_sheer_value->SetParameter(2, 2);

  TFitResultPtr fit_ptr5 = ge5->Fit("RLC_C_sheer_value", "S");
      
  ge5->Draw("AP");
  c5->SetGrid(1, 1);
  //TheApp.Run();
  c5->Print ("Graphs/RLC-C-sheer_value.png", "png");

  C_sheer_value = RLC_C_sheer_value->GetParameter(1);
  C_sheer_value_err = RLC_C_sheer_value->GetParError(1);
  cout<<"estimate of C ottenuta at ends of C: "<<C_sheer_value<<" pm "<<C_sheer_value_err<<endl;

  L_sheer_value = RLC_C_sheer_value->GetParameter(2);
  L_sheer_value_err = RLC_R_sheer_value->GetParError(2);
  cout<<"estimate of L ottenuta at ends of C: "<<L_sheer_value<<" pm "<<L_sheer_value_err<<endl;


  data_file6.open("Data/RLC-endsofC-phase.txt", ios::out);
  data_file6<<"#f \t phase \t errFase "<<endl;

  cout<<"at ends of C - phase:"<<endl;

  for(int i = 0; i<size4; i++){
    if(phase4_B[i] > -10){
      err_phase_B = sqrt(pow(phase4_B[i]*2*sqrt(2)/100, 2));
    }
    else err_phase_B = sqrt(pow(phase4_B[i]*sqrt(2)/100, 2));

    data_file6<<freq4[i]<<" \t "<<phase4_B[i]<<" \t "<<err_phase_B<<endl;
    cout<<" \t& "<<phase4_B[i]<<" $pm$ "<<err_phase_B<<" \t "<<endl;

  }

  gStyle->SetOptFit();

  TCanvas* c6 = new TCanvas("c6","c6", 800, 800);
  c6->SetLogx();

  TGraphErrors *ge6 = new  TGraphErrors("Data/RLC-endsofC-phase.txt" , "%lg %lg %lg"); 
  data_file6.close();
  ge6->SetTitle(" ");
  ge6->GetXaxis()->SetTitle("freq[Hz]");
  ge6->GetYaxis()->SetTitle("phase[rad]");

  ge6->GetXaxis()->SetTitleSize(0.035);
  ge6->GetXaxis()->SetTitleOffset(1.3);
  ge6->GetXaxis()->SetLabelSize(0.040);

  ge6->GetYaxis()->SetTitleSize(0.034);
  ge6->GetYaxis()->SetTitleOffset(1.39);
  ge6->GetYaxis()->SetLabelSize(0.040);


  ge6->SetMarkerStyle(20);
  ge6->SetMarkerSize(0.5);

  ge6->GetYaxis()->SetNdivisions(5, 5, 0);
  ge6->GetXaxis()->SetNdivisions(16, 5, 0);     

  TF1 *RLC_C_phase = new TF1("RLC_C_phase", "( -3.1415/2 - atan((  2*3.1415*x*[2] - 1/( 2*3.1415*x*[1]) ) / [0]) )*180/3.1415", 0., 40*pow(10, 3)); 
  RLC_C_phase->SetParNames("R", "C", "L");
  RLC_C_phase->SetParameter(0, 6*pow(10, 3));
  RLC_C_phase->SetParameter(1, 2*pow(10, -8));
  RLC_C_phase->SetParameter(2, 0.5);

  TFitResultPtr fit_ptr6 = ge6->Fit("RLC_C_phase", "S");
      
  ge6->Draw("AP");
  c6->SetGrid(1, 1);
  //TheApp.Run();
  c6->Print ("Graphs/RLC-phase-endsofC.png", "png");
  
  C_phase = RLC_C_phase->GetParameter(1);
  C_phase_err = RLC_C_phase->GetParError(1);
  cout<<"estimate of C ottenuta at ends of C con la phase: "<<C_phase<<" $pm$ "<<C_phase_err<<endl;

  L_phase = RLC_C_phase->GetParameter(2);
  L_phase_err = RLC_C_phase->GetParError(2);
  cout<<"estimate of L ottenuta at ends of C con la phase: "<<L_phase<<" $pm$ "<<L_phase_err<<endl;
  cout<<"Ndf: "<<fit_ptr6->Ndf()<<endl;
  delete c6;



//EXPERIMENT5: RLC at ends of L
  cout<<"EXPERIMENT5:    RLC-CADUTA AI CAPI DI L"<<endl;
  ofstream data_file7;
  ofstream data_file8;

  int size5 = (int) (sizeof(freq5)/sizeof(freq5[0]));

  data_file7.open("Data/RLC-endsofL-sheer_value.txt", ios::out);
  data_file7<<"#f \t V \t errV "<<endl;

  cout<<"at ends of L - sheer_value:"<<endl;

  for(int i = 0; i<size5; i++){
    err_VA = V5_A[i]/100;
    err_VB = V5_B[i]/100;
    err = sqrt( pow(err_VA*V5_B[i]/pow(V5_A[i], 2), 2) + pow(err_VB/V5_A[i], 2) );

    data_file7<<freq5[i]<<" \t "<<V5_B[i]/V5_A[i]<<" \t "<<err<<endl;
    cout<<freq5[i]<<" \t "<<V5_A[i]<<" $ $ "<<err_VA<<" \t& "<<V5_B[i]<<" $ $ "<<err_VB<<" \t& "<<V5_B[i]/V5_A[i]<<" $pm$ "<<err<<"\\"<<endl;

  }

  gStyle->SetOptFit();

  TCanvas* c7 = new TCanvas("c7","c7", 800, 800);
  c7->SetLogx();

  TGraphErrors *ge7 = new  TGraphErrors("Data/RLC-endsofL-sheer_value.txt" , "%lg %lg %lg"); 
  data_file7.close();
  ge7->SetTitle(" ");
  ge7->GetXaxis()->SetTitle("freq[Hz]");
  ge7->GetYaxis()->SetTitle("Voltaggio[V]");

  ge7->GetXaxis()->SetTitleSize(0.035);
  ge7->GetXaxis()->SetTitleOffset(1.3);
  ge7->GetXaxis()->SetLabelSize(0.040);

  ge7->GetYaxis()->SetTitleSize(0.034);
  ge7->GetYaxis()->SetTitleOffset(1.39);
  ge7->GetYaxis()->SetLabelSize(0.040);


  ge7->SetMarkerStyle(20);
  ge7->SetMarkerSize(0.5);

  ge7->GetYaxis()->SetNdivisions(5, 5, 0);
  ge7->GetXaxis()->SetNdivisions(10, 5, 0);   
  

  TF1 *RLC_L_sheer_value = new TF1("RLC_L_sheer_value", " 2*3.1415*x*[2]/sqrt(  [0]^2 + ( 2*3.1415*x*[2] - 1/( 2*3.1415*x*[1]))^2 ) ", 0., 160*pow(10, 3)); 
  RLC_L_sheer_value->SetParNames("R", "C", "L");
  RLC_L_sheer_value->SetParameter(0, 6603);
  RLC_L_sheer_value->SetParameter(1, 2.764*pow(10, -8));
  RLC_L_sheer_value->SetParameter(2, 0.5036);

  TFitResultPtr fit_ptr7 = ge7->Fit("RLC_L_sheer_value", "S");
      
  ge7->Draw("AP");
  c7->SetGrid(1, 1);
  TheApp.Run();
  c7->Print ("Graphs/RLC-L-sheer_value.png", "png");

  C_sheer_value = RLC_L_sheer_value->GetParameter(1);
  C_sheer_value_err = RLC_L_sheer_value->GetParError(1);
  cout<<"estimate of C ottenuta at ends of L: "<<C_sheer_value<<" pm "<<C_sheer_value_err<<endl;

  L_sheer_value = RLC_L_sheer_value->GetParameter(2);
  L_sheer_value_err = RLC_L_sheer_value->GetParError(2);
  cout<<"estimate of L ottenuta at ends of L: "<<L_sheer_value<<" pm "<<L_sheer_value_err<<endl;


  data_file8.open("Data/RLC-phase-endsofL.txt", ios::out);
  data_file8<<"#f \t phase \t errFase "<<endl;

  cout<<"at ends of L - phase:"<<endl;

  for(int i = 0; i<size5; i++){
    if(phase5_B[i] < 10){
      err_phase_B = phase5_B[i]*2*sqrt(2)/100;
    }
    else err_phase_B = phase5_B[i]*sqrt(2)/100;
    data_file8<<freq5[i]<<" \t "<<phase5_B[i]<<" \t "<<err_phase_B<<endl;
    cout<<" \t& "<<phase5_B[i]<<" $pm$ "<<err_phase_B<<" \t ";

  }


  gStyle->SetOptFit();

  TCanvas* c8 = new TCanvas("c8","c8", 800, 800);
  c8->SetLogx();

  TGraphErrors *ge8 = new  TGraphErrors("Data/RLC-phase-endsofL.txt" , "%lg %lg %lg"); 
  data_file8.close();
  ge8->SetTitle(" ");
  ge8->GetXaxis()->SetTitle("freq[Hz]");
  ge8->GetYaxis()->SetTitle("phase[rad]");

  ge8->GetXaxis()->SetTitleSize(0.035);
  ge8->GetXaxis()->SetTitleOffset(1.3);
  ge8->GetXaxis()->SetLabelSize(0.040);

  ge8->GetYaxis()->SetTitleSize(0.034);
  ge8->GetYaxis()->SetTitleOffset(1.39);
  ge8->GetYaxis()->SetLabelSize(0.040);


  ge8->SetMarkerStyle(20);
  ge8->SetMarkerSize(0.5);

  ge8->GetYaxis()->SetNdivisions(5, 5, 0);
  ge8->GetXaxis()->SetNdivisions(16, 5, 0);     


  TF1 *RLC_L_phase = new TF1("RLC_L_phase", "( 3.1415/2 - atan(( 2*3.1415*x*[2] - 1/(2*3.1415*x*[1]) ) / [0]) )*180/3.1415", 0., 160*pow(10, 3)); 
  RLC_L_phase->SetParNames("R", "C", "L");
  RLC_L_phase->SetParameter(0, 3863);
  RLC_L_phase->SetParameter(1, 1.701*pow(10, -7));
  RLC_L_phase->SetParameter(2, 2.218);


  TFitResultPtr fit_ptr8 = ge8->Fit("RLC_L_phase", "S");
      
  ge8->Draw("AP");
  c8->SetGrid(1, 1);
  TheApp.Run();
  c8->Print ("Graphs/RLC-L-phase.png", "png");
  
  C_phase = RLC_L_phase->GetParameter(1);
  C_phase_err = RLC_L_phase->GetParError(1);
  cout<<"estimate of C ottenuta at ends of L con la phase: "<<C_phase<<" $pm$ "<<C_phase_err<<endl;

  L_phase = RLC_R_phase->GetParameter(2);
  L_phase_err = RLC_R_phase->GetParError(2);
  cout<<"estimate of L ottenuta at ends of L con la phase: "<<L_phase<<" $pm$ "<<L_phase_err<<endl;


  delete c8;


  return 0;
}