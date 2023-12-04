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

#include "dati_circuiti3.h"
//#include "stats.h"

using namespace std;
int main(int argc, char *argv[]){

//ESPERIMENTO1: RC
  TApplication TheApp("TheApp", &argc, argv);
  cout<<"ESPERIMENTO1: RC"<<endl;
  ofstream file_dati1;
  ofstream file_dati2;

  int size1 = (int) (sizeof(freq1)/sizeof(freq1[0]));

  file_dati1.open("RC-capoC-modulo.txt", ios::out);
  file_dati1<<"#f \t VAB/VA \t errV "<<endl;

  cout<<"ai capi di C - modulo:"<<endl;
  double err;
  double err_VAB;
  double err_VA;
  for(int i = 0; i<size1; i++){
    err_VAB = V1_AB[i]/100;
    err_VA = V1_A[i]/100;
    err = sqrt( pow(err_VA*V1_AB[i]/pow(V1_A[i], 2), 2) + pow(err_VAB/V1_A[i], 2) );
    file_dati1<<freq1[i]<<" \t "<<V1_AB[i]/V1_A[i]<<" \t "<<err<<endl;
    cout<<freq1[i]<<" \t& "<<V1_A[i]<<" "<<err_VA<<" \t& "<<V1_AB[i]<<"$   $"<<err_VAB<<" \t& "<<V1_AB[i]/V1_A[i]<<" $ $ "<<err<<"\\"<<endl;
  }

  gStyle->SetOptFit();

  TCanvas* c1 = new TCanvas("c1","c1", 800, 800);
  c1->SetLogx();

  TGraphErrors *ge1 = new  TGraphErrors("RC-capoC-modulo.txt" , "%lg %lg %lg"); 
  file_dati1.close();
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
  
  TF1 *RC_C_modulo = new TF1("RC-C-modulo", " 1/(sqrt(( 2*3.1415*x)^2*[0]^2*[1]^2 +1) )", 0., 2*pow(10, 3)); 
  RC_C_modulo->SetParNames("R", "C");
  RC_C_modulo->SetParameter(0, 6103);
  RC_C_modulo->SetParameter(1, 1.99*pow(10, -8));


  TFitResultPtr fit_ptr1 = ge1->Fit("RC-C-modulo", "S");
      
  ge1->Draw("AP");
  c1->SetGrid(1, 1);
  //TheApp.Run();
  c1->Print ("RC-C-modulo.png", "png");

  double C_modulo = RC_C_modulo->GetParameter(1);
  double C_modulo_err = RC_C_modulo->GetParError(1);
  cout<<"stima di C ottenuta col modulo: "<<C_modulo <<" pm "<<C_modulo_err<<endl;
  
  delete c1;

  file_dati2.open("RC-capoC-fase.txt", ios::out);
  file_dati2<<"#f \t PhiAB \t errPhi "<<endl;


  cout<<"ai capi di C - fase:"<<endl;
  double err_fase_VAB;
  for(int i = 0; i<size1; i++){
    if(fase1_AB[i] > -10){
      err_fase_VAB = sqrt(pow(fase1_AB[i]*2/100, 2))*sqrt(2); //2 %
    }
    else err_fase_VAB = sqrt(pow(fase1_AB[i]/100, 2))*sqrt(2); // 1%
    file_dati2<<freq1[i]<<" \t "<<fase1_AB[i]<<" \t "<<err_fase_VAB<<endl;
    cout<<" \t&"<<fase1_AB[i]<<" $ $ "<<err_fase_VAB<<endl;

  }

  gStyle->SetOptFit();

  TCanvas* c2 = new TCanvas("c2","c2", 800, 800);
  c2->SetLogx();

  TGraphErrors *ge2 = new  TGraphErrors("RC-capoC-fase.txt" , "%lg %lg %lg"); 
  file_dati2.close();
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
  
  TF1 *RC_C_fase = new TF1("RC-C-fase", " -atan( 2*3.1415*x*[0]*[1])*180/3.1415 ", 0., 2*pow(10, 3)); 
  RC_C_fase->SetParNames("R", "C");
  RC_C_fase->SetParameter(0, 4103);
  RC_C_fase->SetParameter(1, 1.99*pow(10, -8));

  TFitResultPtr fit_ptr2 = ge2->Fit("RC-C-fase", "S");
      
  ge2->Draw("AP");
  c2->SetGrid(1, 1);
 // TheApp.Run();
  c2->Print ("RC-C-fase.png", "png");

  double C_fase = RC_C_fase ->GetParameter(1);
  double C_fase_err = RC_C_fase ->GetParError(1);
  cout<<"stima di C ottenuta con la fase: "<<C_fase<<" pm "<<C_fase_err<<endl;
  delete c2;

  ofstream file_dati9;
  ofstream file_dati10;

  file_dati9.open("RC-capoR-modulo.txt", ios::out);
  file_dati9<<"#f \t VB/VA \t errV "<<endl;

  cout<<"ai capi di R - modulo:"<<endl;
  double err_VB;
  for(int i = 0; i<size1; i++){
    err_VB = V1_B[i]/100;
    err_VA = V1_A[i]/100;
    err = sqrt( pow(err_VA*V1_B[i]/pow(V1_A[i], 2), 2) + pow(err_VB/V1_A[i], 2) );
    file_dati9<<freq1[i]<<" \t "<<V1_B[i]/V1_A[i]<<" \t "<<err<<endl;
    cout<<freq1[i]<<" \t& "<<V1_A[i]<<" $ $ "<<err_VA<<" \t& "<<V1_B[i]<<" $ $ "<<err_VB<<" \t& "<<V1_B[i]/V1_A[i]<<" $ $ "<<err<<"\\"<<endl;
  }

  gStyle->SetOptFit();

  TCanvas* c9 = new TCanvas("c9","c9", 800, 800);
  c9->SetLogx();

  TGraphErrors *ge9 = new  TGraphErrors("RC-capoR-modulo.txt" , "%lg %lg %lg"); 
  file_dati9.close();
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
  
  TF1 *RC_R_modulo = new TF1("RC-R-modulo", " [0]*[1]* 2*3.1415*x/sqrt(1 + [0]^2*[1]^2*( 2*3.1415*x)^2) ", 0., 2*pow(10, 3)); 
  RC_R_modulo->SetParNames("R", "C");
  RC_R_modulo->SetParameter(0, 4103);
  RC_R_modulo->SetParameter(1, 1.99*pow(10, -8));

  TFitResultPtr fit_ptr9 = ge9->Fit("RC-R-modulo", "S");
      
  ge9->Draw("AP");
  c9->SetGrid(1, 1);
  //TheApp.Run();
  c9->Print ("RC-R-modulo.png", "png");

  C_modulo = RC_R_modulo->GetParameter(1);
  C_modulo_err = RC_R_modulo->GetParError(1);
  cout<<"stima di C ottenuta col modulo ai capi di R: "<<C_modulo <<" pm "<<C_modulo_err<<endl;

  delete c9;

  file_dati10.open("RC-capoR-fase.txt", ios::out);
  file_dati10<<"#f \t PhiB \t errPhi "<<endl;


  cout<<"ai capi di R - fase:"<<endl;
  double err_fase_B;
  for(int i = 0; i<size1; i++){
    if(fase1_B[i] < 10){
      err_fase_B = sqrt(2)*(fase1_B[i]*2/100);
    }
    else err_fase_B = (fase1_B[i]/100)*sqrt(2);

    file_dati10<<freq1[i]<<" \t "<<fase1_B[i]<<" \t "<<err_fase_B<<endl;
    cout<<" \t& "<<fase1_B[i]<<" $ $ "<<err_fase_B<<" \t ";

  }

  gStyle->SetOptFit();

  TCanvas* c10 = new TCanvas("c10","c10", 800, 800);
  c10->SetLogx();

  TGraphErrors *ge10 = new  TGraphErrors("RC-capoR-fase.txt" , "%lg %lg %lg"); 
  file_dati10.close();
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
  
  TF1 *RC_R_fase = new TF1("RC-R-fase", " ( (3.1415/2) - atan( 2*3.1415*x*[0]*[1]) )*180/3.1415 ", 0., 2*pow(10, 3)); 
  RC_R_fase->SetParNames("R", "C");
  RC_R_fase->SetParameter(0, 4103);
  RC_R_fase->SetParameter(1, 1.99*pow(10, -8));

  TFitResultPtr fit_ptr10 = ge10->Fit("RC-R-fase", "S");
      
  ge10->Draw("AP");
  c10->SetGrid(1, 1);
  //TheApp.Run();
  c10->Print ("RC-R-fase.png", "png");
  C_fase = RC_R_fase->GetParameter(1);
  C_fase_err = RC_R_fase->GetParError(1);
  cout<<"stima di C ottenuta col modulo ai capi di R: "<<C_fase<<" pm "<<C_fase_err<<endl;


  delete c10;

//ESPERIMENTO2: RL
  cout<<"ESPERIMENTO2: RL"<<endl;
  ofstream file_dati11;
  ofstream file_dati12;

  int size2 = (int) (sizeof(freq2)/sizeof(freq2[0]));

  file_dati11.open("RL-capoL-modulo.txt", ios::out);
  file_dati11<<"#f \t VAB/VA \t errV "<<endl;

  cout<<"ai capi di L - modulo:"<<endl;

  for(int i = 0; i<size2-6; i++){
    err_VAB = V2_AB[i]/100;
    err = sqrt( pow(0.1*V2_AB[i]/pow(V2_A[i], 2), 2) + pow(err_VAB/V2_A[i], 2) );
    file_dati11<<freq2[i]<<" \t "<<V2_AB[i]/V2_A[i]<<" \t "<<err<<endl;
    cout<<freq2[i]<<" \t & "<<V2_A[i]<<" $ $ "<<err_VA<<" \t& "<<V2_AB[i]<<" $ $ "<<err_VAB<<" \t & "<<V2_AB[i]/V2_A[i]<<" $pm$ "<<err<<"\\"<<endl;
  }

  gStyle->SetOptFit();

  TCanvas* c11 = new TCanvas("c11","c11", 800, 800);
  c11->SetLogx();

  TGraphErrors *ge11 = new  TGraphErrors("RL-capoL-modulo.txt" , "%lg %lg %lg"); 
  file_dati11.close();
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
  
  
  TF1 *RL_L_modulo = new TF1("RL-L-modulo", "  2*3.1415*x*[1]/sqrt([0]^2 + ( 2*3.1415*x)^2*[1]^2 )  ", 0., 160*pow(10, 3)); 
  RL_L_modulo->SetParNames("R", "L");
  RL_L_modulo->SetParameter(0, 6103);
  RL_L_modulo->SetParameter(1, 0.564);
  TFitResultPtr fit_ptr11 = ge11->Fit("RL-L-modulo", "S");
      
  ge11->Draw("AP");
  c11->SetGrid(1, 1);
  //TheApp.Run();
  c11->Print ("RL-L-modulo.png", "png");
  double L_modulo = RC_R_fase->GetParameter(1);
  double L_modulo_err = RC_R_fase->GetParError(1);
  cout<<"stima di L ottenuta col modulo: "<<L_modulo<<" pm "<<L_modulo_err<<endl;


  
  delete c11;

  file_dati12.open("RL-capoL-fase.txt", ios::out);
  file_dati12<<"#f \t PhiAB \t errPhi "<<endl;

  int size2f = (int) (sizeof(freq2fasi)/sizeof(freq2fasi[0]));

  cout<<"ai capi di L - fase:"<<endl;
  for(int i = 0; i<size2f-6; i++){
    if(fase2_AB[i] <10){
      err_fase_VAB = fase2_AB[i]*2*sqrt(2)/100; //2%
    }
    err_fase_VAB = fase2_AB[i]*sqrt(2)/100;//1%

    file_dati12<<freq2fasi[i]<<" \t "<<fase2_AB[i]<<" \t "<<err_fase_VAB<<endl;
    cout<<freq2fasi[i]<<" \t& "<<fase2_AB[i]<<" $ $ "<<err_fase_VAB<<" \t ";

  }

  gStyle->SetOptFit();

  TCanvas* c12 = new TCanvas("c12","c12", 800, 800);
  c12->SetLogx();

  TGraphErrors *ge12 = new  TGraphErrors("RL-capoL-fase.txt" , "%lg %lg %lg"); 
  file_dati12.close();
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

  TF1 *RL_L_fase = new TF1("RL-L-fase", " ( (3.1415/2) - atan( 2*3.1415*x*[1]/[0]) )*180/3.1415 ", 0., 160*pow(10, 3)); 
  RL_L_fase->SetParNames("R", "L");
  RL_L_fase->SetParameter(0, 6103);
  RL_L_fase->SetParameter(1, 0.564);


  TFitResultPtr fit_ptr12 = ge12->Fit("RL-L-fase", "S");
      
  ge12->Draw("AP");
  c12->SetGrid(1, 1);
 // TheApp.Run();
  c12->Print ("RL-L-fase.png", "png");
  delete c12;
  double L_fase = RL_L_fase->GetParameter(1);
  double L_fase_err = RL_L_fase->GetParError(1);
  cout<<"stima di L ottenuta con la fase: "<<L_fase<<" pm "<<L_fase_err<<endl;


  ofstream file_dati13;
  ofstream file_dati14;

  file_dati13.open("RL-capoR-modulo.txt", ios::out);
  file_dati13<<"#f \t VB/VA \t errV "<<endl;

  cout<<"ai capi di R - modulo:"<<endl;

  for(int i = 0; i<size2-6; i++){
    err_VB = V2_B[i]/100;
    err_VA = V2_A[i]/100;
    err = sqrt( pow(err_VA*V2_B[i]/pow(V2_A[i], 2), 2) + pow(err_VB/V2_A[i], 2) );
    file_dati13<<freq2[i]<<" \t "<<V2_B[i]/V2_A[i]<<" \t "<<err<<endl;
    cout<<freq2[i]<<" \t& "<<V2_A[i]<<" $ $ "<<err_VA<<" \t& "<<V2_B[i]<<" $ $ "<<err_VB<<" \t& "<<V2_B[i]/V2_A[i]<<" $ $ "<<err<<"\\"<<endl;
  }

  gStyle->SetOptFit();

  TCanvas* c13 = new TCanvas("c13","c13", 800, 800);
  c13->SetLogx();

  TGraphErrors *ge13 = new  TGraphErrors("RL-capoR-modulo.txt" , "%lg %lg %lg"); 
  file_dati13.close();
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
  
  TF1 *RL_R_modulo = new TF1("RL_R_modulo", "[0]/sqrt([0]^2 + ( 2*3.1415*x*[1])^2)", 0., 160*pow(10, 3)); 
  RL_R_modulo->SetParNames("R", "L");
  RL_R_modulo->SetParameter(0, 6426);
  RL_R_modulo->SetParameter(1, 2.613);


  TFitResultPtr fit_ptr13 = ge13->Fit("RL_R_modulo", "S");
      
  ge13->Draw("AP");
  c13->SetGrid(1, 1);
  TheApp.Run();
  c13->Print ("RL-R-modulo.png", "png");

  L_modulo = RL_R_modulo->GetParameter(1);
  L_fase_err = RL_R_modulo->GetParError(1);
  cout<<"stima di L ottenuta: "<<L_modulo<<" pm "<<L_modulo_err<<endl;

  delete c13;  

  file_dati14.open("RL-capoR-fase.txt", ios::out);
  file_dati14<<"#f \t PhiB \t errPhi "<<endl;


  cout<<"ai capi di R - fase:"<<endl;

  for(int i = 0; i<size2f-6; i++){
    if(fase2_B[i] > -10){
      err_fase_B = sqrt(pow(fase2_B[i]*2*sqrt(2)/100, 2));
    }
    err_fase_B = sqrt(pow(fase2_B[i]*sqrt(2)/100, 2));

    file_dati14<<freq2fasi[i]<<" \t "<<fase2_B[i]<<" \t "<<err_fase_B<<endl;
    cout<<" \t& "<<fase2_B[i]<<" $pm$ "<<err_fase_B<<" \t ";

  }

  gStyle->SetOptFit();

  TCanvas* c14 = new TCanvas("c14","c14", 800, 800);
  c14->SetLogx();

  TGraphErrors *ge14 = new  TGraphErrors("RL-capoR-fase.txt" , "%lg %lg %lg"); 
  file_dati14.close();
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
  
  TF1 *RL_R_fase = new TF1("RL_R_fase", "-atan( 2*3.1415*x*[1]/[0])*180/3.1415", 0., 160*pow(10, 3)); 
  RL_R_fase->SetParNames("R", "L");
  RL_R_fase->SetParameter(0, 4103);
  RL_R_fase->SetParameter(1, 2.164);

  TFitResultPtr fit_ptr14 = ge14->Fit("RL_R_fase", "S");
      
  ge14->Draw("AP");
  c14->SetGrid(1, 1);
  TheApp.Run();
  c14->Print ("RL-R-fase.png", "png");
  delete c14;

  L_fase = RL_R_fase->GetParameter(1);
  L_fase_err = RL_R_fase->GetParError(1);
  cout<<"stima di L ottenuta ai capi di R: "<<L_fase<<" pm "<<L_fase_err<<endl;

  TMatrixD cov = fit_ptr14->GetCovarianceMatrix();
  cov.Print();

//ESPERIMENTO3: RLC ai capi di R
  cout<<"ESPERIMENTO3:    RLC-CADUTA AI CAPI DI R"<<endl;
  ofstream file_dati3;
  ofstream file_dati4;

  int size3 = (int) (sizeof(freq3)/sizeof(freq3[0]));

  file_dati3.open("RLC-capoR-modulo.txt", ios::out);
  file_dati3<<"#f \t V \t errV "<<endl;


  cout<<"ai capi di R - modulo:"<<endl;

  for(int i = 0; i<size3; i++){
    err_VA = V3_A[i]/100;
    err_VB = V3_B[i]/100;
    err = sqrt( pow(err_VA*V3_B[i]/pow(V3_A[i], 2), 2) + pow(err_VB/V3_A[i], 2) );
    file_dati3<<freq3[i]<<" \t "<<V3_B[i]/V3_A[i]<<" \t "<<err<<endl;
    cout<<freq3[i]<<" \t& "<<V3_A[i]<<" $ $ "<<err_VA<<" \t& "<<V3_B[i]<<" $ $ "<<err_VB<<" \t& "<<V3_B[i]/V3_A[i]<<" $ $ "<<err<<"\\"<<endl;

  }


  TCanvas* c3 = new TCanvas("c3","c3", 800, 800);
  c3->SetLogx();

  TGraphErrors *ge3 = new  TGraphErrors("RLC-capoR-modulo.txt" , "%lg %lg %lg"); 
  file_dati3.close();
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

  TF1 *RLC_R_modulo = new TF1("RLC_R_modulo", " 2*3.1415*x*[0]*[1]/sqrt( ( 2*3.1415*x)^2*[1]^2*[0]^2 + (( 2*3.1415*x)^2*[2]*[1] - 1)^2  )", 0., 160*pow(10, 3)); 
  RLC_R_modulo->SetParNames("R", "C", "L");
  RLC_R_modulo->SetParameter(0, 6103);
  RLC_R_modulo->SetParameter(1, 1.99*pow(10, -8));
  RLC_R_modulo->SetParameter(2, 0.514);

  TFitResultPtr fit_ptr3 = ge3->Fit("RLC_R_modulo", "S");
      
  ge3->Draw("AP");
  c3->SetGrid(1, 1);
  //TheApp.Run();
  c3->Print ("RLC-R-modulo.png", "png");

  C_modulo = RLC_R_modulo->GetParameter(1);
  C_modulo_err = RLC_R_modulo->GetParError(1);
  cout<<"stima di C ottenuta ai capi di R: "<<C_modulo<<" pm "<<C_modulo_err<<endl;
  

  L_modulo = RLC_R_modulo->GetParameter(2);
  L_modulo_err = RLC_R_modulo->GetParError(2);
  cout<<"stima di L ottenuta ai capi di R: "<<L_modulo<<" pm "<<L_modulo_err<<endl;

  delete c3;


  file_dati4.open("RLC-capoR-fase.txt", ios::out);
  file_dati4<<"#f \t fase \t errFase "<<endl;


  cout<<"ai capi di R - fase:"<<endl;

  for(int i = 0; i<size3; i++){
    err_fase_B =sqrt(pow(fase3_B[i]*sqrt(2)/100, 2));

    file_dati4<<freq3[i]<<" \t "<<fase3_B[i]<<" \t "<<err_fase_B<<endl;
    cout<<" \t& "<<fase3_B[i]<<" $pm$ "<<err_fase_B<<" \t ";

  }

  gStyle->SetOptFit();

  TCanvas* c4 = new TCanvas("c4","c4", 800, 800);
  c4->SetLogx();

  TGraphErrors *ge4 = new  TGraphErrors("RLC-capoR-fase.txt" , "%lg %lg %lg"); 
  file_dati4.close();
  ge4->SetTitle(" ");
  ge4->GetXaxis()->SetTitle("freq[Hz]");
  ge4->GetYaxis()->SetTitle("fase[rad]");

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


  TF1 *RLC_R_fase = new TF1("RLC_R_fase", "-atan((  2*3.1415*x*[2] - 1/( 2*3.1415*x*[1]) ) / [0])*180/3.1415", 0., 160*pow(10, 3)); 
  RLC_R_fase->SetParNames("R", "C", "L");
  RLC_R_fase->SetParameter(0, 6780);
  RLC_R_fase->SetParameter(1, 1.99*pow(10, -8));
  RLC_R_fase->SetParameter(2, 0.564);


  TFitResultPtr fit_ptr4 = ge4->Fit("RLC_R_fase", "S");
      
  ge4->Draw("AP");
  c4->SetGrid(1, 1);
 // TheApp.Run();
  c4->Print ("RLC-R-fase.png", "png");
  
  C_fase = RLC_R_fase->GetParameter(1);
  C_fase_err = RLC_R_fase->GetParError(1);
  cout<<"stima di C ottenuta ai capi di R con la fase: "<<C_fase<<" $pm$ "<<C_fase_err<<endl;

  L_fase = RLC_R_fase->GetParameter(2);
  L_fase_err = RLC_R_fase->GetParError(2);
  cout<<"stima di L ottenuta ai capi di R con la fase: "<<L_fase<<" $pm$ "<<L_fase_err<<endl;
  cout<<"Ndf: "<<fit_ptr4->Ndf()<<endl;


  delete c4;
 

 //ESPERIMENTO4: RLC ai capi di C
  cout<<"ESPERIMENTO4:    RLC-CADUTA AI CAPI DI C"<<endl;
  ofstream file_dati5;
  ofstream file_dati6;

  int size4 = (int) (sizeof(freq4)/sizeof(freq4[0]));

  file_dati5.open("RLC-capoC-modulo.txt", ios::out);
  file_dati5<<"#f \t V \t errV "<<endl;


  gStyle->SetOptFit();

  cout<<"ai capi di C - modulo:"<<endl;

  for(int i = 0; i<size4; i++){
    err_VA = V4_A[i]/100;
    err_VB = V4_B[i]/100;
    err = sqrt( pow(err_VA*V4_B[i]/pow(V4_A[i], 2), 2) + pow(err_VB/V4_A[i], 2) );

    file_dati5<<freq4[i]<<" \t "<<V4_B[i]/V4_A[i]<<" \t "<<err<<endl;
    cout<<freq4[i]<<" \t "<<V4_A[i]<<" $ $ "<<err_VA<<" \t& "<<V4_B[i]<<" $ $ "<<err_VB<<" \t& "<<V4_B[i]/V4_A[i]<<" $pm$ "<<err<<"\\"<<endl;

  }

  TCanvas* c5 = new TCanvas("c5","c5", 800, 800);
  c5->SetLogx();

  TGraphErrors *ge5 = new  TGraphErrors("RLC-capoC-modulo.txt" , "%lg %lg %lg"); 
  file_dati5.close();
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
  
  TF1 *RLC_C_modulo = new TF1("RLC_C_modulo", "  1/(   2*3.1415*x*[1]*sqrt([0]^2 + ( 2*3.1415*x*[2] - 1/( 2*3.1415*x*[1]))^2)  )  ", 0., 160*pow(10, 3)); 
  RLC_C_modulo->SetParNames("R", "C", "L");
  RLC_C_modulo->SetParameter(0, 3803);
  RLC_C_modulo->SetParameter(1, 2*pow(10, -7));
  RLC_C_modulo->SetParameter(2, 2);

  TFitResultPtr fit_ptr5 = ge5->Fit("RLC_C_modulo", "S");
      
  ge5->Draw("AP");
  c5->SetGrid(1, 1);
  //TheApp.Run();
  c5->Print ("RLC-C-modulo.png", "png");

  C_modulo = RLC_C_modulo->GetParameter(1);
  C_modulo_err = RLC_C_modulo->GetParError(1);
  cout<<"stima di C ottenuta ai capi di C: "<<C_modulo<<" pm "<<C_modulo_err<<endl;

  L_modulo = RLC_C_modulo->GetParameter(2);
  L_modulo_err = RLC_R_modulo->GetParError(2);
  cout<<"stima di L ottenuta ai capi di C: "<<L_modulo<<" pm "<<L_modulo_err<<endl;


  file_dati6.open("RLC-capoC-fase.txt", ios::out);
  file_dati6<<"#f \t fase \t errFase "<<endl;

  cout<<"ai capi di C - fase:"<<endl;

  for(int i = 0; i<size4; i++){
    if(fase4_B[i] > -10){
      err_fase_B = sqrt(pow(fase4_B[i]*2*sqrt(2)/100, 2));
    }
    else err_fase_B = sqrt(pow(fase4_B[i]*sqrt(2)/100, 2));

    file_dati6<<freq4[i]<<" \t "<<fase4_B[i]<<" \t "<<err_fase_B<<endl;
    cout<<" \t& "<<fase4_B[i]<<" $pm$ "<<err_fase_B<<" \t "<<endl;

  }

  gStyle->SetOptFit();

  TCanvas* c6 = new TCanvas("c6","c6", 800, 800);
  c6->SetLogx();

  TGraphErrors *ge6 = new  TGraphErrors("RLC-capoC-fase.txt" , "%lg %lg %lg"); 
  file_dati6.close();
  ge6->SetTitle(" ");
  ge6->GetXaxis()->SetTitle("freq[Hz]");
  ge6->GetYaxis()->SetTitle("fase[rad]");

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

  TF1 *RLC_C_fase = new TF1("RLC_C_fase", "( -3.1415/2 - atan((  2*3.1415*x*[2] - 1/( 2*3.1415*x*[1]) ) / [0]) )*180/3.1415", 0., 40*pow(10, 3)); 
  RLC_C_fase->SetParNames("R", "C", "L");
  RLC_C_fase->SetParameter(0, 6*pow(10, 3));
  RLC_C_fase->SetParameter(1, 2*pow(10, -8));
  RLC_C_fase->SetParameter(2, 0.5);

  TFitResultPtr fit_ptr6 = ge6->Fit("RLC_C_fase", "S");
      
  ge6->Draw("AP");
  c6->SetGrid(1, 1);
  //TheApp.Run();
  c6->Print ("RLC-fase-capoC.png", "png");
  
  C_fase = RLC_C_fase->GetParameter(1);
  C_fase_err = RLC_C_fase->GetParError(1);
  cout<<"stima di C ottenuta ai capi di C con la fase: "<<C_fase<<" $pm$ "<<C_fase_err<<endl;

  L_fase = RLC_C_fase->GetParameter(2);
  L_fase_err = RLC_C_fase->GetParError(2);
  cout<<"stima di L ottenuta ai capi di C con la fase: "<<L_fase<<" $pm$ "<<L_fase_err<<endl;
  cout<<"Ndf: "<<fit_ptr6->Ndf()<<endl;
  delete c6;



//ESPERIMENTO5: RLC ai capi di L
  cout<<"ESPERIMENTO5:    RLC-CADUTA AI CAPI DI L"<<endl;
  ofstream file_dati7;
  ofstream file_dati8;

  int size5 = (int) (sizeof(freq5)/sizeof(freq5[0]));

  file_dati7.open("RLC-capoL-modulo.txt", ios::out);
  file_dati7<<"#f \t V \t errV "<<endl;

  cout<<"ai capi di L - modulo:"<<endl;

  for(int i = 0; i<size5; i++){
    err_VA = V5_A[i]/100;
    err_VB = V5_B[i]/100;
    err = sqrt( pow(err_VA*V5_B[i]/pow(V5_A[i], 2), 2) + pow(err_VB/V5_A[i], 2) );

    file_dati7<<freq5[i]<<" \t "<<V5_B[i]/V5_A[i]<<" \t "<<err<<endl;
    cout<<freq5[i]<<" \t "<<V5_A[i]<<" $ $ "<<err_VA<<" \t& "<<V5_B[i]<<" $ $ "<<err_VB<<" \t& "<<V5_B[i]/V5_A[i]<<" $pm$ "<<err<<"\\"<<endl;

  }

  gStyle->SetOptFit();

  TCanvas* c7 = new TCanvas("c7","c7", 800, 800);
  c7->SetLogx();

  TGraphErrors *ge7 = new  TGraphErrors("RLC-capoL-modulo.txt" , "%lg %lg %lg"); 
  file_dati7.close();
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
  

  TF1 *RLC_L_modulo = new TF1("RLC_L_modulo", " 2*3.1415*x*[2]/sqrt(  [0]^2 + ( 2*3.1415*x*[2] - 1/( 2*3.1415*x*[1]))^2 ) ", 0., 160*pow(10, 3)); 
  RLC_L_modulo->SetParNames("R", "C", "L");
  RLC_L_modulo->SetParameter(0, 6603);
  RLC_L_modulo->SetParameter(1, 2.764*pow(10, -8));
  RLC_L_modulo->SetParameter(2, 0.5036);

  TFitResultPtr fit_ptr7 = ge7->Fit("RLC_L_modulo", "S");
      
  ge7->Draw("AP");
  c7->SetGrid(1, 1);
  TheApp.Run();
  c7->Print ("RLC-L-modulo.png", "png");

  C_modulo = RLC_L_modulo->GetParameter(1);
  C_modulo_err = RLC_L_modulo->GetParError(1);
  cout<<"stima di C ottenuta ai capi di L: "<<C_modulo<<" pm "<<C_modulo_err<<endl;

  L_modulo = RLC_L_modulo->GetParameter(2);
  L_modulo_err = RLC_L_modulo->GetParError(2);
  cout<<"stima di L ottenuta ai capi di L: "<<L_modulo<<" pm "<<L_modulo_err<<endl;


  file_dati8.open("RLC-fase-capoL.txt", ios::out);
  file_dati8<<"#f \t fase \t errFase "<<endl;

  cout<<"ai capi di L - fase:"<<endl;

  for(int i = 0; i<size5; i++){
    if(fase5_B[i] < 10){
      err_fase_B = fase5_B[i]*2*sqrt(2)/100;
    }
    else err_fase_B = fase5_B[i]*sqrt(2)/100;
    file_dati8<<freq5[i]<<" \t "<<fase5_B[i]<<" \t "<<err_fase_B<<endl;
    cout<<" \t& "<<fase5_B[i]<<" $pm$ "<<err_fase_B<<" \t ";

  }


  gStyle->SetOptFit();

  TCanvas* c8 = new TCanvas("c8","c8", 800, 800);
  c8->SetLogx();

  TGraphErrors *ge8 = new  TGraphErrors("RLC-fase-capoL.txt" , "%lg %lg %lg"); 
  file_dati8.close();
  ge8->SetTitle(" ");
  ge8->GetXaxis()->SetTitle("freq[Hz]");
  ge8->GetYaxis()->SetTitle("fase[rad]");

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


  TF1 *RLC_L_fase = new TF1("RLC_L_fase", "( 3.1415/2 - atan(( 2*3.1415*x*[2] - 1/(2*3.1415*x*[1]) ) / [0]) )*180/3.1415", 0., 160*pow(10, 3)); 
  RLC_L_fase->SetParNames("R", "C", "L");
  RLC_L_fase->SetParameter(0, 3863);
  RLC_L_fase->SetParameter(1, 1.701*pow(10, -7));
  RLC_L_fase->SetParameter(2, 2.218);


  TFitResultPtr fit_ptr8 = ge8->Fit("RLC_L_fase", "S");
      
  ge8->Draw("AP");
  c8->SetGrid(1, 1);
  TheApp.Run();
  c8->Print ("RLC-L-fase.png", "png");
  
  C_fase = RLC_L_fase->GetParameter(1);
  C_fase_err = RLC_L_fase->GetParError(1);
  cout<<"stima di C ottenuta ai capi di L con la fase: "<<C_fase<<" $pm$ "<<C_fase_err<<endl;

  L_fase = RLC_R_fase->GetParameter(2);
  L_fase_err = RLC_R_fase->GetParError(2);
  cout<<"stima di L ottenuta ai capi di L con la fase: "<<L_fase<<" $pm$ "<<L_fase_err<<endl;


  delete c8;


  return 0;
}