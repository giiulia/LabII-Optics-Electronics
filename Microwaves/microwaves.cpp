#include <iostream>
#include <fstream> 
#include <cmath>
#include "data.cc"

#include "TApplication.h"
#include "TCanvas.h"
#include "TPaveStats.h"
#include "TGraphErrors.h"
#include "TAxis.h"
#include "TMarker.h"
#include "TF1.h"
#include "TFitResult.h"
#include "TMultiGraph.h"
#include "TStyle.h"

int main(int argc, char *argv[]){
    TApplication TheApp("theApp", &argc, argv);

//OSCILLATIONS
    cout<<"OSCILLATIONS OF INTENSITY RESPECT TO DISTANCE"<<endl;
    ofstream oscillations_file;

    double dimension = (sizeof(intensity)/sizeof(intensity[0]));
    cout<<dimension<<endl;

    amplification(intensity, 30, dimension);

    oscillations_file.open("oscillations.txt", ios::out);
    oscillations_file<<"#distanza\t intensity"<<endl;

    for(int i = 0; i<dimension; i++){
        oscillations_file<<posiztion[i]<<" \t "<<intensity[i]<<endl;
    }

    TCanvas* c1 = new TCanvas();

    TGraph *gr = new  TGraph("oscillations.txt" , "%lg %lg"); 
    gr->SetTitle(" ");
    gr->GetXaxis()->SetTitle("distanza[cm]");
    gr->GetYaxis()->SetTitle("intensity[mA]");

    gr->GetXaxis()->SetTitleSize(0.055);
    gr->GetXaxis()->SetTitleOffset(0.8);

    gr->GetYaxis()->SetTitleSize(0.055);
    gr->GetYaxis()->SetTitleOffset(0.6);

    gr->SetMarkerStyle(20);
    gr->Draw("APL");
    c1->Print("oscillazioni.png", "png");


//REFLECTION WITH METAL FOIL
    cout<<"RIFLESSIONE CON IL METALLO"<<endl;

    double theta_rifl_medie[number_of_incident_angles][3];
    double theta_trasmesso_40_media[3];
    double theta_trasmesso_50_media[3];

    for(int i = 0; i<number_of_incident_angles; i++){
        Med_Var_Dev(theta_rifl[i], theta_rifl_medie[i], numero_misure_angoli_rifl);

        cout<<"theta_inc[i]"<<theta_inc[i]<<" theta_rifl[i]: "<<theta_rifl_medie[i][0]<<" "<<theta_rifl_medie[i][2]<<endl;
    }

    Med_Var_Dev(theta_trasmesso_40, theta_trasmesso_40_media, numero_misure_angoli_rifl);
    cout<<"theta_trasmesso40: "<<theta_trasmesso_40_media[0]<<" "<<theta_trasmesso_40_media[2]<<endl;

    Med_Var_Dev(theta_trasmesso_50, theta_trasmesso_50_media, numero_misure_angoli_rifl);
    cout<<"theta_trasmesso50: "<<theta_trasmesso_50_media[0]<<" "<<theta_trasmesso_50_media[2]<<endl;

    double intensity_reflected_wave_metallo_medie[number_of_incident_angles][3];
    for(int i = 0; i<number_of_incident_angles; i++){
        amplification(intensity_reflected_wave_metallo[i], 10, numero_misure_angoli_rifl);
    }
    
    for(int i = 0; i<number_of_incident_angles; i++){
        Med_Var_Dev(intensity_reflected_wave_metallo[i], intensity_reflected_wave_metallo_medie[i], numero_misure_angoli_rifl);

        cout<<"theta_inc[i]"<<theta_inc[i]<<" intensity riflessa[i]: "<<intensity_reflected_wave_metallo_medie[i][0]<<" "<<intensity_reflected_wave_metallo_medie[i][2]<<endl;
    }

    cout<<"intensity transmitted40: "<<transmitted_wave_intensity_40*10<<endl;
    cout<<"intensity transmitted50: "<<transmitted_wave_intensity_50*10<<endl;

//REFRACTION POLYSTYRENE AND STYRENE
    cout<<"REFRACTION POLYSTYRENE"<<endl;
    double refraction_index_styrene[2];
    double refracted_wave_mean_intensity[3];

    double refraction_mean_theta_max_styrene[2];

    refraction_mean_theta_max_styrene[0] = media(refraction_mean_theta_max_styrene, 2);
    refraction_mean_theta_max_styrene[1] =  deviazione_st(refraction_mean_theta_max_styrene, 2);

    cout<<"refracted theta: (22 degrees to add)"<<refraction_mean_theta_max_styrene[0]<<" "<<refraction_mean_theta_max_styrene[1]<<endl;
    refraction_mean_theta_max_styrene[0] = (refraction_mean_theta_max_styrene[0]+22)*M_PI/180;
    refraction_mean_theta_max_styrene[1] = sqrt( pow(refraction_mean_theta_max_styrene[1], 2)+1)*M_PI/180 ;

    vertex_angle[0] = vertex_angle[0]*M_PI/180;
    vertex_angle[1] = vertex_angle[1]*M_PI/180;

    refraction_index_styrene[0] = 1*sin(refraction_mean_theta_max_styrene[0])/sin(vertex_angle[0]);
    refraction_index_styrene[1] = sqrt( pow( 1*cos(refraction_mean_theta_max_styrene[0])*refraction_mean_theta_max_styrene[1]/sin(vertex_angle[0]) , 2) + pow(  sin(refraction_mean_theta_max_styrene[0])*cos(vertex_angle[0])*vertex_angle[1]/pow(sin(vertex_angle[0]), 2)  , 2  ) );
   
    amplification(refracted_wave_intensity, 30, 2);

    Med_Var_Dev(refracted_wave_intensity, refracted_wave_mean_intensity, 2);
    cout<<"refrcted wave intensity: "<<refracted_wave_mean_intensity<<endl;
    cout<<"reflected wave intensity: "<<reflected_wave_intensity*30<<endl;

    cout<<"refraction index styrene: (expected: 1.546)"<<refraction_index_styrene[0]<<" "<<refraction_index_styrene[1]<<endl;

//POLARIZATION  

    //polarization without grid
    ofstream polarization_file_dist1;
    ofstream polarization_file_dist2;
    ofstream polarization_file_dist3;

    double dimension1 = (sizeof(intensity_polarized_wave_dist1)/sizeof(intensity_polarized_wave_dist1[0]));
    double dimension2 = (sizeof(intensity_polarized_wave_dist2)/sizeof(intensity_polarized_wave_dist2[0]));

    amplification(intensity_polarized_wave_dist1, 30, dimension1);
    amplification(intensity_polarized_wave_dist2, 10, dimension2);
    amplification(intensity_polarized_wave_dist3, 10, dimension2);

    polarization_file_dist1.open("polarization_dist1.txt", ios::out);
    polarization_file_dist1<<"#angle\t intensity"<<endl;

    for(int i = 0; i<dimension1; i++){
        polarization_file_dist1<<polarizer_angle1[i]<<" \t "<<intensity_polarized_wave_dist1[i]<<endl;
    }

    polarization_file_dist2.open("polarization_dist2.txt", ios::out);
    polarization_file_dist2<<"#angle\t intensity"<<endl;

    for(int i = 0; i<dimension2; i++){
        polarization_file_dist2<<polarizer_angle2[i]<<" \t "<<intensity_polarized_wave_dist2[i]<<endl;
    }

    polarization_file_dist3.open("polarization_dist3.txt", ios::out);
    polarization_file_dist3<<"#angle\t intensity"<<endl;

    for(int i = 0; i<dimension2; i++){
        polarization_file_dist3<<polarizer_angle3[i]<<" \t "<<intensity_polarized_wave_dist3[i]<<endl;
    }

    auto c2 = new TCanvas("c2","c2",1000, 800);
    
    auto mg = new TMultiGraph("verifica della legge di Malus","verifica della legge di Malus");
    
    auto gr1 = new TGraph("polarization_dist1.txt" , "%lg %lg");
    gr1->SetName("50 cm");
    gr1->SetTitle("50 cm");
    gr1->SetMarkerStyle(20);
    gr1->SetMarkerColor(2);
    gr1->SetLineColor(2);
    gr1->SetLineWidth(2);
    gr1->SetFillStyle(0);
    
    auto gr2 = new TGraph("polarization_dist2.txt" , "%lg %lg");
    gr2->SetName("70 cm");
    gr2->SetTitle("70 cm");
    gr2->SetMarkerStyle(20);
    gr2->SetMarkerColor(3);
    gr2->SetDrawOption("P");
    gr2->SetLineColor(3);
    gr2->SetLineWidth(2);
    gr2->SetFillStyle(0);
    
    auto gr3 = new TGraph("polarization_dist3.txt" , "%lg %lg");
    gr3->SetName("90 cm");
    gr3->SetTitle("90 cm");
    gr3->SetMarkerStyle(20);
    gr3->SetMarkerColor(4);
    gr3->SetLineColor(4);
    gr3->SetLineWidth(2);
    gr3->SetFillStyle(0);

    mg->Add( gr1 );
    mg->Add( gr2 );
    mg->Add( gr3 );

    mg->Draw("APL");

    mg->GetXaxis()->SetTitle("angoli[gradi]");
    mg->GetYaxis()->SetTitle("intensità[mA]");

    mg->GetXaxis()->SetTitleSize(0.05);
    mg->GetXaxis()->SetTitleOffset(0.9);

    mg->GetYaxis()->SetTitleSize(0.05);
    mg->GetYaxis()->SetTitleOffset(0.9);

    
// Change the axis limits
    gPad->Modified();
    mg->GetXaxis()->SetLimits(0,200);
    mg->SetMinimum(0.);
    mg->SetMaximum(20.);

    c2->BuildLegend();

    c2->Print("polarization.png", "png");

    oscillations_file.close();
    polarization_file_dist1.close();
    polarization_file_dist2.close();
    polarization_file_dist3.close();

    delete c2;
    
    TCanvas* c8 = new TCanvas();
    TF1* opz1 = new TF1("option", "[0]*cos(x*3.1415/180)", 0, 200);
    opz1->SetParameter(0, 17.4);

    opz1->SetTitle("");
    opz1->GetXaxis()->SetTitle("#theta[gradi]");
    opz1->GetYaxis()->SetTitle("Meter reading");

    opz1->GetXaxis()->SetTitleSize(0.05);
    opz1->GetXaxis()->SetTitleOffset(0.8);

    opz1->GetYaxis()->SetTitleSize(0.05);
    opz1->GetYaxis()->SetTitleOffset(0.6);

    TMarker punto1(polarizer_angle1[0], intensity_polarized_wave_dist1[0], 20);
    TMarker punto2(polarizer_angle1[1], intensity_polarized_wave_dist1[1], 20);
    TMarker punto3(polarizer_angle1[2], intensity_polarized_wave_dist1[2], 20);
    TMarker punto4(polarizer_angle1[3], intensity_polarized_wave_dist1[3], 20);
    TMarker punto5(polarizer_angle1[4], intensity_polarized_wave_dist1[4], 20);
    TMarker punto6(polarizer_angle1[5], intensity_polarized_wave_dist1[5], 20);
    TMarker punto7(polarizer_angle1[6], intensity_polarized_wave_dist1[6], 20);
    TMarker punto8(polarizer_angle1[7], intensity_polarized_wave_dist1[7], 20);
    TMarker punto9(polarizer_angle1[8], intensity_polarized_wave_dist1[8], 20);
    TMarker punto10(polarizer_angle1[9], intensity_polarized_wave_dist1[9], 20);
    TMarker punto11(polarizer_angle1[10], intensity_polarized_wave_dist1[10], 20);
    TMarker punto12(polarizer_angle1[11], intensity_polarized_wave_dist1[11], 20);
    TMarker punto13(polarizer_angle1[12], intensity_polarized_wave_dist1[12], 20);
    TMarker punto14(polarizer_angle1[13], intensity_polarized_wave_dist1[13], 20);
    TMarker punto15(polarizer_angle1[14], intensity_polarized_wave_dist1[14], 20);
    TMarker punto16(polarizer_angle1[15], intensity_polarized_wave_dist1[15], 20);
    TMarker punto17(polarizer_angle1[16], intensity_polarized_wave_dist1[16], 20);
    TMarker punto18(polarizer_angle1[17], intensity_polarized_wave_dist1[17], 20);
    TMarker punto19(polarizer_angle1[18], intensity_polarized_wave_dist1[18], 20);
    TMarker punto20(polarizer_angle1[19], intensity_polarized_wave_dist1[19], 20);
    TMarker punto21(polarizer_angle1[20], intensity_polarized_wave_dist1[20], 20);
    TMarker punto22(polarizer_angle1[21], intensity_polarized_wave_dist1[21], 20);
    TMarker punto23(polarizer_angle1[22], intensity_polarized_wave_dist1[22], 20);

    opz1->Draw();
    punto1.Draw();
    punto2.Draw();
    punto3.Draw("P");
    punto4.Draw("P");
    punto5.Draw("P");
    punto6.Draw("P");
    punto7.Draw("P");
    punto8.Draw("P");
    punto9.Draw("P");
    punto10.Draw("P");
    punto11.Draw("P");
    punto12.Draw("P");
    punto13.Draw("P");
    punto14.Draw("P");
    punto15.Draw("P");
    punto16.Draw("P");
    punto17.Draw("P");
    punto18.Draw("P");
    punto19.Draw("P");
    punto20.Draw("P");
    punto21.Draw("P");
    punto22.Draw("P");
    punto23.Draw("P");

    c8->Print("Meter reading and Malus law_opt1.png", "png");

    delete c8;


    TCanvas* c9 = new TCanvas();
    TF1* opz2 = new TF1("option2", "[0]*cos(x*3.1415/180)^{2}", 0, 200);
    opz2->SetParameter(0, 17.4);


    opz2->SetTitle("");
    opz2->GetXaxis()->SetTitle("#theta[gradi]");
    opz2->GetYaxis()->SetTitle("Meter reading");

    opz2->GetXaxis()->SetTitleSize(0.05);
    opz2->GetXaxis()->SetTitleOffset(0.8);

    opz2->GetYaxis()->SetTitleSize(0.05);
    opz2->GetYaxis()->SetTitleOffset(0.6);

    opz2->Draw();
    punto1.Draw("P");
    punto2.Draw("P");
    punto3.Draw("P");
    punto4.Draw("P");
    punto5.Draw("P");
    punto6.Draw("P");
    punto7.Draw("P");
    punto8.Draw("P");
    punto9.Draw("P");
    punto10.Draw("P");
    punto11.Draw("P");
    punto12.Draw("P");
    punto13.Draw("P");
    punto14.Draw("P");
    punto15.Draw("P");
    punto16.Draw("P");
    punto17.Draw("P");
    punto18.Draw("P");
    punto19.Draw("P");
    punto20.Draw("P");
    punto21.Draw("P");
    punto22.Draw("P");
    punto23.Draw("P");

    c9->Print("Meter reading and Malus law_opt2.png", "png");

    delete c9;



//BREWSTER ANGLE
    ofstream file_Brewster_0;

    amplification(intensity_reflected_wave_90, 10, number_of_incident_angles_Brewster);

    file_Brewster_0.open("Brewster.txt", ios::out);
    file_Brewster_0<<"#angle\t intensity"<<endl;

    for(int i = 0; i<number_of_incident_angles_Brewster; i++){
        file_Brewster_0<<incidence_angle_Brewster[i]<<" \t "<<intensity_reflected_wave_90[i]<<endl;
    }

    TCanvas* c4 = new TCanvas();

    TGraph *gr_0 = new  TGraph("Brewster.txt" , "%lg %lg"); 
    gr_0->SetTitle("research  of Brewster angle");
    gr_0->GetXaxis()->SetTitle("angolo rispetto alla normale[gradi]");
    gr_0->GetYaxis()->SetTitle("intensità[mA]");

    gr_0->GetXaxis()->SetTitleSize(0.05);
    gr_0->GetXaxis()->SetTitleOffset(0.8);

    gr_0->GetYaxis()->SetTitleSize(0.05);
    gr_0->GetYaxis()->SetTitleOffset(0.6);

    gr_0->SetMarkerStyle(20);
    gr_0->Draw("APL");
    c4->Print("Brewster angle.png", "png");    
    

    file_Brewster_0.close();

    delete c4;




//DOUBLE SLIT
    cout<<"DOUBLE SLIT INTERFERENCE"<<endl;
    ofstream double_slit_file;

    for(int i = 0; i <number_of_maximus; i++){
        max_angle_double_slit[i] = (max_angle_double_slit[i])*M_PI/180.;
    }

    double_slit_file.open("double_slit_interference", ios::out);
    double_slit_file<<"#max order \t sin(angle)  \t errSinAngle"<<endl;

    for(int i = 0; i<number_of_maximus; i++){
        cout<<ordine_massimo_doppia_fenditura[i]<<" \t "<<sin(max_angle_double_slit[i])<<" \t "<<cos(max_angle_double_slit[i])*M_PI/180<<endl; 
        double_slit_file<<ordine_massimo_doppia_fenditura[i]<<" \t\t\t "<<sin(max_angle_double_slit[i])<<" \t "<<cos(max_angle_double_slit[i])*M_PI/180<<endl;
    }

    gStyle->SetOptFit();
    auto c6 = new TCanvas("c6","multigraph",700,500);

    TGraphErrors *ge2 = new  TGraphErrors("double_slit_interference" , "%lg %lg %lg"); 
    ge2->SetTitle(" interpolazione per trovare la lunghezza d'onda ");
    ge2->GetXaxis()->SetTitle("ordine massimo[intero]");
    ge2->GetYaxis()->SetTitle("sin(#theta)");

    ge2->GetXaxis()->SetTitleSize(0.05);
    ge2->GetXaxis()->SetTitleOffset(1.0);

    ge2->GetYaxis()->SetTitleSize(0.05);
    ge2->GetYaxis()->SetTitleOffset(1.0);

    ge2->SetMarkerStyle(20);
    ge2->Draw("AP");

    double m2, Errm2;
    double lambdaDF[2];

    TF1 *f2 = new TF1("line", "[0]*x"); 
    ge2->Fit("line");
    c6->Update();
    auto stats2 = (TPaveStats*)ge2->GetListOfFunctions()->FindObject("stats");
    stats2->SetX1NDC(0.12); stats2->SetX2NDC(0.32); stats2->SetY1NDC(0.75);
    c6->Modified();           

    c6->Print ("interpolation_dpuble_slit.png", "png");

    m2 = f2->GetParameter(0); 
    Errm2 = f2->GetParError(0);

    lambdaDF[0] = d*m2;
    lambdaDF[1] = Errm2*d;
    cout<<"wavelenght with double slit in cm: "<<lambdaDF[0]<<"  "<<lambdaDF[1]<<endl;
    delete c6;

    TheApp.Run();


    return 0;
}