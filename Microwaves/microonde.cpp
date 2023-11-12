#include <iostream>
#include <fstream> 
#include <cmath>
#include "dati_microonde.cc"

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

//OSCILLAZIONI
    cout<<"OSCILLAZIONI DELL'INTENSITA RISPETTO ALLA DISTANZA"<<endl;
    ofstream file_oscillazioni;

    double dimension = (sizeof(intensita)/sizeof(intensita[0]));
    cout<<dimension<<endl;

    amplification(intensita, 30, dimension);

    file_oscillazioni.open("oscillazioni.txt", ios::out);
    file_oscillazioni<<"#distanza\t intensita"<<endl;

    for(int i = 0; i<dimension; i++){
        file_oscillazioni<<posizione[i]<<" \t "<<intensita[i]<<endl;
    }

    TCanvas* c1 = new TCanvas();

    TGraph *gr = new  TGraph("oscillazioni.txt" , "%lg %lg"); 
    gr->SetTitle(" ");
    gr->GetXaxis()->SetTitle("distanza[cm]");
    gr->GetYaxis()->SetTitle("intensita[mA]");

    gr->GetXaxis()->SetTitleSize(0.055);
    gr->GetXaxis()->SetTitleOffset(0.8);

    gr->GetYaxis()->SetTitleSize(0.055);
    gr->GetYaxis()->SetTitleOffset(0.6);

    gr->SetMarkerStyle(20);
    gr->Draw("APL");
    c1->Print("oscillazioni.png", "png");


//RIFLESSIONE CON LAMINA DI METALLO
    cout<<"RIFLESSIONE CON IL METALLO"<<endl;

    double theta_rifl_medie[numero_angoli_inc][3];
    double theta_trasmesso_40_media[3];
    double theta_trasmesso_50_media[3];

    for(int i = 0; i<numero_angoli_inc; i++){
        Med_Var_Dev(theta_rifl[i], theta_rifl_medie[i], numero_misure_angoli_rifl);

        cout<<"theta_inc[i]"<<theta_inc[i]<<" theta_rifl[i]: "<<theta_rifl_medie[i][0]<<" "<<theta_rifl_medie[i][2]<<endl;
    }

    Med_Var_Dev(theta_trasmesso_40, theta_trasmesso_40_media, numero_misure_angoli_rifl);
    cout<<"theta_trasmesso40: "<<theta_trasmesso_40_media[0]<<" "<<theta_trasmesso_40_media[2]<<endl;

    Med_Var_Dev(theta_trasmesso_50, theta_trasmesso_50_media, numero_misure_angoli_rifl);
    cout<<"theta_trasmesso50: "<<theta_trasmesso_50_media[0]<<" "<<theta_trasmesso_50_media[2]<<endl;

    double intensita_onda_riflessa_metallo_medie[numero_angoli_inc][3];
    for(int i = 0; i<numero_angoli_inc; i++){
        amplification(intensita_onda_riflessa_metallo[i], 10, numero_misure_angoli_rifl);
    }
    
    for(int i = 0; i<numero_angoli_inc; i++){
        Med_Var_Dev(intensita_onda_riflessa_metallo[i], intensita_onda_riflessa_metallo_medie[i], numero_misure_angoli_rifl);

        cout<<"theta_inc[i]"<<theta_inc[i]<<" intensita riflessa[i]: "<<intensita_onda_riflessa_metallo_medie[i][0]<<" "<<intensita_onda_riflessa_metallo_medie[i][2]<<endl;
    }

    cout<<"intensita trasmessa40: "<<intensita_onda_trasmessa_40*10<<endl;
    cout<<"intensita trasmessa50: "<<intensita_onda_trasmessa_50*10<<endl;

//RIFRAZIONE POLISTIROLO E STYRENE
    cout<<"RIFRAZIONE POLISTIROLO"<<endl;
    double indice_rifrazione_styrene[2];
    double intensita_onda_rifratta_media[3];

    double max_theta_rifratto_styrene_media[2];

    max_theta_rifratto_styrene_media[0] = media(max_theta_rifratto_styrene, 2);
    max_theta_rifratto_styrene_media[1] =  deviazione_st(max_theta_rifratto_styrene, 2);

    cout<<"theta rifratto: (da aggiungere il 22 gradi)"<<max_theta_rifratto_styrene_media[0]<<" "<<max_theta_rifratto_styrene_media[1]<<endl;
    max_theta_rifratto_styrene_media[0] = (max_theta_rifratto_styrene_media[0]+22)*M_PI/180;
    max_theta_rifratto_styrene_media[1] = sqrt( pow(max_theta_rifratto_styrene_media[1], 2)+1)*M_PI/180 ;

    angolo_al_vertice[0] = angolo_al_vertice[0]*M_PI/180;
    angolo_al_vertice[1] = angolo_al_vertice[1]*M_PI/180;

    indice_rifrazione_styrene[0] = 1*sin(max_theta_rifratto_styrene_media[0])/sin(angolo_al_vertice[0]);
    indice_rifrazione_styrene[1] = sqrt( pow( 1*cos(max_theta_rifratto_styrene_media[0])*max_theta_rifratto_styrene_media[1]/sin(angolo_al_vertice[0]) , 2) + pow(  sin(max_theta_rifratto_styrene_media[0])*cos(angolo_al_vertice[0])*angolo_al_vertice[1]/pow(sin(angolo_al_vertice[0]), 2)  , 2  ) );
   
    amplification(intensita_onda_rifratta, 30, 2);
    Med_Var_Dev(intensita_onda_rifratta, intensita_onda_rifratta_media, 2);
    cout<<"intensita onda rifratta: "<<intensita_onda_rifratta_media<<endl;
    cout<<"intensita onda riflessa: "<<intensita_onda_riflessa*30<<endl;

    cout<<"indice di rifrazione stirene: (atteso:1.546) "<<indice_rifrazione_styrene[0]<<" "<<indice_rifrazione_styrene[1]<<endl;

//POLARIZZAZIONE

    //polarizzazione senza griglia
    ofstream file_polarizzazione_dist1;
    ofstream file_polarizzazione_dist2;
    ofstream file_polarizzazione_dist3;

    double dimension1 = (sizeof(intensita_onda_polarizzata_dist1)/sizeof(intensita_onda_polarizzata_dist1[0]));
    double dimension2 = (sizeof(intensita_onda_polarizzata_dist2)/sizeof(intensita_onda_polarizzata_dist2[0]));

    amplification(intensita_onda_polarizzata_dist1, 30, dimension1);
    amplification(intensita_onda_polarizzata_dist2, 10, dimension2);
    amplification(intensita_onda_polarizzata_dist3, 10, dimension2);//stessa lunghezza dell'altro array

    file_polarizzazione_dist1.open("polarizzazione_dist1.txt", ios::out);
    file_polarizzazione_dist1<<"#angolo\t intensita"<<endl;

    for(int i = 0; i<dimension1; i++){
        file_polarizzazione_dist1<<angolo_polarizzatore1[i]<<" \t "<<intensita_onda_polarizzata_dist1[i]<<endl;
    }

    file_polarizzazione_dist2.open("polarizzazione_dist2.txt", ios::out);
    file_polarizzazione_dist2<<"#angolo\t intensita"<<endl;

    for(int i = 0; i<dimension2; i++){
        file_polarizzazione_dist2<<angolo_polarizzatore2[i]<<" \t "<<intensita_onda_polarizzata_dist2[i]<<endl;
    }

    file_polarizzazione_dist3.open("polarizzazione_dist3.txt", ios::out);
    file_polarizzazione_dist3<<"#angolo\t intensita"<<endl;

    for(int i = 0; i<dimension2; i++){
        file_polarizzazione_dist3<<angolo_polarizzatore3[i]<<" \t "<<intensita_onda_polarizzata_dist3[i]<<endl;
    }

    auto c2 = new TCanvas("c2","c2",1000, 800);
    
    auto mg = new TMultiGraph("verifica della legge di Malus","verifica della legge di Malus");
    
    auto gr1 = new TGraph("polarizzazione_dist1.txt" , "%lg %lg");
    gr1->SetName("50 cm");
    gr1->SetTitle("50 cm");
    gr1->SetMarkerStyle(20);
    gr1->SetMarkerColor(2);
    gr1->SetLineColor(2);
    gr1->SetLineWidth(2);
    gr1->SetFillStyle(0);
    
    auto gr2 = new TGraph("polarizzazione_dist2.txt" , "%lg %lg");
    gr2->SetName("70 cm");
    gr2->SetTitle("70 cm");
    gr2->SetMarkerStyle(20);
    gr2->SetMarkerColor(3);
    gr2->SetDrawOption("P");
    gr2->SetLineColor(3);
    gr2->SetLineWidth(2);
    gr2->SetFillStyle(0);
    
    auto gr3 = new TGraph("polarizzazione_dist3.txt" , "%lg %lg");
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
    mg->GetYaxis()->SetTitle("intensita[mA]");

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

    c2->Print("polarizzazione.png", "png");

    file_oscillazioni.close();
    file_polarizzazione_dist1.close();
    file_polarizzazione_dist2.close();
    file_polarizzazione_dist3.close();

    delete c2;

    TCanvas* c8 = new TCanvas();
    TF1* opz1 = new TF1("opzione1", "[0]*cos(x*3.1415/180)", 0, 200);
    opz1->SetParameter(0, 17.4);//0.58*30


    opz1->SetTitle("");
    opz1->GetXaxis()->SetTitle("#theta[gradi]");
    opz1->GetYaxis()->SetTitle("Meter reading");

    opz1->GetXaxis()->SetTitleSize(0.05);
    opz1->GetXaxis()->SetTitleOffset(0.8);

    opz1->GetYaxis()->SetTitleSize(0.05);
    opz1->GetYaxis()->SetTitleOffset(0.6);

    TMarker punto1(angolo_polarizzatore1[0], intensita_onda_polarizzata_dist1[0], 20);
    TMarker punto2(angolo_polarizzatore1[1], intensita_onda_polarizzata_dist1[1], 20);
    TMarker punto3(angolo_polarizzatore1[2], intensita_onda_polarizzata_dist1[2], 20);
    TMarker punto4(angolo_polarizzatore1[3], intensita_onda_polarizzata_dist1[3], 20);
    TMarker punto5(angolo_polarizzatore1[4], intensita_onda_polarizzata_dist1[4], 20);
    TMarker punto6(angolo_polarizzatore1[5], intensita_onda_polarizzata_dist1[5], 20);
    TMarker punto7(angolo_polarizzatore1[6], intensita_onda_polarizzata_dist1[6], 20);
    TMarker punto8(angolo_polarizzatore1[7], intensita_onda_polarizzata_dist1[7], 20);
    TMarker punto9(angolo_polarizzatore1[8], intensita_onda_polarizzata_dist1[8], 20);
    TMarker punto10(angolo_polarizzatore1[9], intensita_onda_polarizzata_dist1[9], 20);
    TMarker punto11(angolo_polarizzatore1[10], intensita_onda_polarizzata_dist1[10], 20);
    TMarker punto12(angolo_polarizzatore1[11], intensita_onda_polarizzata_dist1[11], 20);
    TMarker punto13(angolo_polarizzatore1[12], intensita_onda_polarizzata_dist1[12], 20);
    TMarker punto14(angolo_polarizzatore1[13], intensita_onda_polarizzata_dist1[13], 20);
    TMarker punto15(angolo_polarizzatore1[14], intensita_onda_polarizzata_dist1[14], 20);
    TMarker punto16(angolo_polarizzatore1[15], intensita_onda_polarizzata_dist1[15], 20);
    TMarker punto17(angolo_polarizzatore1[16], intensita_onda_polarizzata_dist1[16], 20);
    TMarker punto18(angolo_polarizzatore1[17], intensita_onda_polarizzata_dist1[17], 20);
    TMarker punto19(angolo_polarizzatore1[18], intensita_onda_polarizzata_dist1[18], 20);
    TMarker punto20(angolo_polarizzatore1[19], intensita_onda_polarizzata_dist1[19], 20);
    TMarker punto21(angolo_polarizzatore1[20], intensita_onda_polarizzata_dist1[20], 20);
    TMarker punto22(angolo_polarizzatore1[21], intensita_onda_polarizzata_dist1[21], 20);
    TMarker punto23(angolo_polarizzatore1[22], intensita_onda_polarizzata_dist1[22], 20);

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

    c8->Print("Meter reading e legge di Malus_opz1.png", "png");

    delete c8;



    TCanvas* c9 = new TCanvas();
    TF1* opz2 = new TF1("opzione2", "[0]*cos(x*3.1415/180)^{2}", 0, 200);
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

    c9->Print("Meter reading e legge di Malus_opz2.png", "png");

    delete c9;




//ANGOLO DI BREWSTER
    ofstream file_Brewster_0;

    amplification(intensita_onda_riflessa_90, 10, numero_angoli_inc_Brewster);

    file_Brewster_0.open("Brewster.txt", ios::out);
    file_Brewster_0<<"#angolo\t intensita"<<endl;

    for(int i = 0; i<numero_angoli_inc_Brewster; i++){
        file_Brewster_0<<angolo_incidenza_Brewster[i]<<" \t "<<intensita_onda_riflessa_90[i]<<endl;
    }

    TCanvas* c4 = new TCanvas();

    TGraph *gr_0 = new  TGraph("Brewster.txt" , "%lg %lg"); 
    gr_0->SetTitle("ricerca dell'angolo di Brewster");
    gr_0->GetXaxis()->SetTitle("angolo rispetto alla normale[gradi]");
    gr_0->GetYaxis()->SetTitle("intensita[mA]");

    gr_0->GetXaxis()->SetTitleSize(0.05);
    gr_0->GetXaxis()->SetTitleOffset(0.8);

    gr_0->GetYaxis()->SetTitleSize(0.05);
    gr_0->GetYaxis()->SetTitleOffset(0.6);

    gr_0->SetMarkerStyle(20);
    gr_0->Draw("APL");
    c4->Print("angolo di Brewster.png", "png");    
    

    file_Brewster_0.close();

    delete c4;



//DOPPIA FENDITURA
    cout<<"INTERFERENZA DOPPIA FENDITURA"<<endl;
    ofstream file_doppia_fenditura;

    for(int i = 0; i <numero_massimi_fenditura; i++){
        angolo_massimo_doppia_fenditura[i] = (angolo_massimo_doppia_fenditura[i])*M_PI/180.;
    }

    file_doppia_fenditura.open("interferenza_doppia_fenditura.txt", ios::out);
    file_doppia_fenditura<<"#ordine massimo \tsin(angolo)  \t errSinAngolo"<<endl;

    for(int i = 0; i<numero_massimi_fenditura; i++){
        cout<<ordine_massimo_doppia_fenditura[i]<<" \t "<<sin(angolo_massimo_doppia_fenditura[i])<<" \t "<<cos(angolo_massimo_doppia_fenditura[i])*M_PI/180<<endl; 
        file_doppia_fenditura<<ordine_massimo_doppia_fenditura[i]<<" \t\t\t "<<sin(angolo_massimo_doppia_fenditura[i])<<" \t "<<cos(angolo_massimo_doppia_fenditura[i])*M_PI/180<<endl;
    }

    gStyle->SetOptFit();
    auto c6 = new TCanvas("c6","multigraph",700,500);

    TGraphErrors *ge2 = new  TGraphErrors("interferenza_doppia_fenditura.txt" , "%lg %lg %lg"); 
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

    TF1 *f2 = new TF1("retta", "[0]*x"); 
    ge2->Fit("retta");
    c6->Update();
    auto stats2 = (TPaveStats*)ge2->GetListOfFunctions()->FindObject("stats");
    stats2->SetX1NDC(0.12); stats2->SetX2NDC(0.32); stats2->SetY1NDC(0.75);
    c6->Modified();           

    c6->Print ("interpolazione_doppia_fenditura_corretta.png", "png");

    m2 = f2->GetParameter(0); 
    Errm2 = f2->GetParError(0);

    lambdaDF[0] = d*m2;
    lambdaDF[1] = Errm2*d;
    cout<<"lunghezza d'onda con la doppia fenditura in cm: "<<lambdaDF[0]<<"  "<<lambdaDF[1]<<endl;
    delete c6;

//CUBO DI BRAGG
    ofstream file_Bragg;

    amplification(intensita_onda_riflessa_Bragg, 10, numero_misure_Bragg);

    file_Bragg.open("Bragg.txt", ios::out);
    file_Bragg<<"#angolo\t intensita"<<endl;

    for(int i = 0; i<numero_misure_Bragg; i++){
        file_Bragg<<angolo_incidenza_Bragg[i]<<" \t "<<intensita_onda_riflessa_Bragg[i]<<endl;
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
    c7->Print("cubo di Bragg.png", "png");    
    

    file_Bragg.close();

    delete c7;


    TheApp.Run();


    return 0;
}