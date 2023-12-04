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
    cout<<"INTENSITY AS THE DISTANCE VARIES"<<endl;
    ofstream oscillations_file;

    double dimension = (sizeof(intensity)/sizeof(intensity[0]));
    cout<<dimension<<endl;

    amplification(intensity, 30, dimension);

    oscillations_file.open("Data/oscillations.txt", ios::out);
    oscillations_file<<"#distance \t intensity"<<endl;

    for(int i = 0; i<dimension; i++){
        oscillations_file<<position[i]<<" \t "<<intensity[i]<<endl;
    }

    TCanvas* c1 = new TCanvas();

    TGraph *gr = new  TGraph("Data/oscillations.txt" , "%lg %lg"); 
    gr->SetTitle(" ");
    gr->GetXaxis()->SetTitle("distanza[cm]");
    gr->GetYaxis()->SetTitle("intensita[mA]");

    gr->GetXaxis()->SetTitleSize(0.055);
    gr->GetXaxis()->SetTitleOffset(0.8);

    gr->GetYaxis()->SetTitleSize(0.055);
    gr->GetYaxis()->SetTitleOffset(0.6);

    gr->SetMarkerStyle(20);
    gr->Draw("APL");
    c1->Print("Graphs/oscillations.png", "png");


//REFLECTION WITH METAL FOIL
    cout<<"REFLECTION WITH METAL FOIL"<<endl;

    double reflected_theta_mean[number_of_incident_angles][3];
    double transmitted_theta_40_mean[3];
    double transmitted_theta_50_mean[3];

    for(int i = 0; i<number_of_incident_angles; i++){
        Med_Var_Dev(theta_rifl[i], reflected_theta_mean[i], number_of_reflected_theta);

        cout<<"theta_inc[i]"<<theta_inc[i]<<" theta_rifl[i]: "<<reflected_theta_mean[i][0]<<" "<<reflected_theta_mean[i][2]<<endl;
    }

    Med_Var_Dev(transmitted_theta_40, transmitted_theta_40_mean, number_of_reflected_theta);
    cout<<"theta_trasmesso40: "<<transmitted_theta_40_mean[0]<<" "<<transmitted_theta_40_mean[2]<<endl;

    Med_Var_Dev(transmitted_theta_50, transmitted_theta_50_mean, number_of_reflected_theta);
    cout<<"theta_trasmesso50: "<<transmitted_theta_50_mean[0]<<" "<<transmitted_theta_50_mean[2]<<endl;

    double intensity_reflected_wave_metal_medie[number_of_incident_angles][3];
    for(int i = 0; i<number_of_incident_angles; i++){
        amplification(intensity_reflected_wave_metal[i], 10, number_of_reflected_theta);
    }
    
    for(int i = 0; i<number_of_incident_angles; i++){
        Med_Var_Dev(intensity_reflected_wave_metal[i], intensity_reflected_wave_metal_medie[i], number_of_reflected_theta);

        cout<<"theta_inc[i]"<<theta_inc[i]<<" intensity riflessa[i]: "<<intensity_reflected_wave_metal_medie[i][0]<<" "<<intensity_reflected_wave_metal_medie[i][2]<<endl;
    }

    cout<<"intensity transmitted40: "<<transmitted_wave_intensity_40*10<<endl;
    cout<<"intensity transmitted50: "<<transmitted_wave_intensity_50*10<<endl;

//REFRACTION POLYSTYRENE AND STYRENE
    cout<<"REFRACTION POLYSTYRENE"<<endl;
    double refraction_index_styrene[2];
    double refracted_wave_mean_intensity[3];

    double refraction_mean_theta_max_styrene[2];

    refraction_mean_theta_max_styrene[0] = mean(refraction_mean_theta_max_styrene, 2);
    refraction_mean_theta_max_styrene[1] =  st_deviation(refraction_mean_theta_max_styrene, 2);

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

    cout<<"refraction index styrene: (expected: 1.546) -> "<<refraction_index_styrene[0]<<" "<<refraction_index_styrene[1]<<endl;

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
    gr3->SetName("40 cm");
    gr3->SetTitle("40 cm");
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
    mg->GetXaxis()->SetTitleOffset(0.4);

    mg->GetYaxis()->SetTitleSize(0.05);
    mg->GetYaxis()->SetTitleOffset(0.4);

    
// Change the axis limits
    gPad->Modified();
    mg->GetXaxis()->SetLimits(0,200);
    mg->SetMinimum(0.);
    mg->SetMaximum(20.);

    c2->BuildLegend();

    c2->Print("Graphs/polarization.png", "png");

    oscillations_file.close();
    polarization_file_dist1.close();
    polarization_file_dist2.close();
    polarization_file_dist3.close();

    delete c2;
    
    TCanvas* c3 = new TCanvas();
    TF1* opz1 = new TF1("option", "[0]*cos(x*3.1415/180)", 0, 200);
    opz1->SetParameter(0, 17.4);

    opz1->SetTitle("");
    opz1->GetXaxis()->SetTitle("#theta[gradi]");
    opz1->GetYaxis()->SetTitle("Meter reading");

    opz1->GetXaxis()->SetTitleSize(0.05);
    opz1->GetXaxis()->SetTitleOffset(0.8);

    opz1->GetYaxis()->SetTitleSize(0.05);
    opz1->GetYaxis()->SetTitleOffset(0.6);

    TMarker points[sizeof(polarizer_angle1)];
  
    opz1->Draw();

    for(int i = 0; i<sizeof(polarizer_angle1); i++){
        TMarker * punto = new TMarker(polarizer_angle1[i], intensity_polarized_wave_dist1[i], 20);
        points[i] = *punto;
        points[i].Draw();
        delete punto;

    }


//    c3->Print("Graphs/Meter_reading_and_Malus_law_opt1.png", "png");

    delete c3;

    TCanvas* c4 = new TCanvas();
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
    for(int i = 0; i<sizeof(polarizer_angle1); i++){
        TMarker * punto = new TMarker(polarizer_angle1[i], intensity_polarized_wave_dist1[i], 20);
        points[i] = *punto;
        points[i].Draw();
        delete punto;

    }


 //   c4->Print("Graphs/Meter_reading_and_Malus_law_opt2.png", "png");

    delete c4;


//BREWSTER ANGLE
    ofstream file_Brewster_0;

    amplification(intensity_reflected_wave_40, 10, number_of_incident_angles_Brewster);

    file_Brewster_0.open("Brewster.txt", ios::out);
    file_Brewster_0<<"#angle\t intensity"<<endl;

    for(int i = 0; i<number_of_incident_angles_Brewster; i++){
        file_Brewster_0<<incident_angle_Brewster[i]<<" \t "<<intensity_reflected_wave_40[i]<<endl;
    }

    TCanvas* c5 = new TCanvas();

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
    c5->Print("Graphs/Brewster_angle.png", "png");    
    

    file_Brewster_0.close();

    delete c5;


//DOUBLE SLIT
    cout<<"DOUBLE SLIT INTERFERENCE"<<endl;
    ofstream double_slit_file;

    for(int i = 0; i <number_of_maximums_slit; i++){
        maximum_angle_double_slit[i] = (maximum_angle_double_slit[i])*M_PI/180.;
    }

    double_slit_file.open("double_slit_interference", ios::out);
    double_slit_file<<"#max order \t sin(angle)  \t errSinAngle"<<endl;

    for(int i = 0; i<number_of_maximums_slit; i++){
        cout<<order_of_maximum_double_slit[i]<<" \t "<<sin(maximum_angle_double_slit[i])<<" \t "<<cos(maximum_angle_double_slit[i])*M_PI/180<<endl; 
        double_slit_file<<order_of_maximum_double_slit[i]<<" \t\t\t "<<sin(maximum_angle_double_slit[i])<<" \t "<<cos(maximum_angle_double_slit[i])*M_PI/180<<endl;
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

    c6->Print ("Graphs/interpolation_dpuble_slit.png", "png");

    m2 = f2->GetParameter(0); 
    Errm2 = f2->GetParError(0);

    lambdaDF[0] = d*m2;
    lambdaDF[1] = Errm2*d;
    cout<<"wavelenght with double slit in cm: "<<lambdaDF[0]<<"  "<<lambdaDF[1]<<endl;
    delete c6;

//BRAGG'S CUBE
    ofstream Bragg_file;

    amplification(reflected_wave_intensity_Bragg, 10, number_of_measures_Bragg);

    Bragg_file.open("Bragg.txt", ios::out);
    Bragg_file<<"#angle \t intensity"<<endl;

    for(int i = 0; i<number_of_measures_Bragg; i++){
        Bragg_file<<incident_angle_Bragg[i]<<" \t "<<reflected_wave_intensity_Bragg[i]<<endl;
    }

    TCanvas* c7 = new TCanvas();

    TGraph *grb = new  TGraph("Bragg.txt" , "%lg %lg"); 
    grb->SetTitle("ricerca del massimo");
    grb->GetXaxis()->SetTitle("angolo rispetto ai piani[gradi]");
    grb->GetYaxis()->SetTitle("intensita[mA]");

    grb->GetXaxis()->SetTitleSize(0.05);
    grb->GetXaxis()->SetTitleOffset(0.8);

    grb->GetYaxis()->SetTitleSize(0.05);
    grb->GetYaxis()->SetTitleOffset(0.6);

    grb->SetMarkerStyle(20);
    grb->Draw("APL");
    c7->Print("Graphs/Bragg's_cube.png", "png");    
    

    Bragg_file.close();

    delete c7;



    TheApp.Run();


    return 0;
}