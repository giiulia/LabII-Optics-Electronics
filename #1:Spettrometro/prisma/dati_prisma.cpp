#include <iostream>
#include <cmath>
#include <fstream>

#include "../clean_data.h"

int main(int argc, char*argv[]){
    ofstream file_Hg;
    ofstream file_gasIgnoto;

    ofstream file_punti; //per parabola

    file_Hg.open ("delta_min.txt", ios::out);
    double size;

    double righe[] = {579.0663, 576.9598,  546.0735, 435.8328,  404.6563}; //gialla dx, gialla sx, verde, blu, lilla
    //file_Hg<<"#lunghezze d'onda(nm):"<<endl;
    file_Hg<<righe[0]<<"\t"<<righe[1]<<"\t"<<righe[2]<<"\t"<<righe[3]<<"\t"<<righe[4]<<endl; //stampa le lambda su file

    int alpha1[][3] = {{128, 35, 30}, {128, 41, 00}, {128, 51, 00}, {128, 38, 00}, {128, 34, 30}};
    int alpha2[][3] = {{8, 05, 00}, {8, 10, 00}, {8, 18, 00}, {8, 8, 00}, {8, 12, 30} };
    size = sizeof(alpha1)/sizeof(alpha1[0]);
    Diff(alpha2, alpha1, file_Hg, size, size); //stampa l'angolo di rotazione su file

    file_Hg<<0.048<<"\t"<<0.000577<<endl;

    //punto zero
    int delta0[][3] = {{283,05,00}, {283, 02, 30}, {283, 02, 00}, {283, 01, 00}, {283, 03, 00}};

//METODO DIRETTO

    //gialla di destra
    file_Hg<<"\n#gialla dx:"<<endl;
    int deltaG1[][3] = {{331, 33, 00}, {331, 35, 30}, {331, 34, 30}, {331, 35, 30}, {331, 29, 30}};
    Diff(delta0, deltaG1, file_Hg, size, size);

    //gialla di sinistra
    file_Hg<<"\n#gialla sx:"<<endl;;
    int deltaG2[][3] = {{331, 44, 30}, {331, 34, 30}, {331, 29, 00}, {331, 42, 30}, {331, 41, 00}}; 
    Diff(delta0, deltaG2, file_Hg, size, size);

    //int deltaG[][3] = {{331,25,0}, {331, 22, 30}, {331, 24, 30}, {331, 22, 30}, {331, 21, 30}}; non usare

    //riga verde
    file_Hg<<"\n#verde:"<<endl;
    int deltaV[][3] = {{331, 40, 30}, {331, 43, 30}, {331, 41, 00}, {331, 40, 30}, {331, 45, 30}};
    Diff(delta0, deltaV, file_Hg, size, size);

    //riga blu
    file_Hg<<"\n#blu:"<<endl;
    int deltaB[][3] = {{333, 25, 30}, {333, 29, 30}, {333, 40, 30}, {333, 30, 30}, {333, 30, 00}};
    Diff(delta0, deltaB, file_Hg, size, size);

    //riga lilla
    file_Hg<<"#\nlilla:"<<endl;
    int deltaL[][3] = {{333, 42, 30}, {333, 42, 30}, {333, 41, 00}, {333, 40, 30}, {333, 43, 30}};
    Diff(delta0, deltaL, file_Hg, size, size);

    file_Hg.close();

    file_punti.open ("metodo2/punti.txt", ios::out);
    file_punti<<"#indice\t\tangolo\tdev_media"<<endl;

//METODO DELLA PARABOLA (verde)

    int punto1[][3] = {{332, 04, 30}, {331, 50, 0}, {331, 50, 30}, {331, 54, 30}, {332, 04, 00}};
    DiffPunti(delta0, punto1, file_punti, size, 1);

    //int punto2[][3] = {{331, 50, 30}, {331, 52, 00}, {331, 49, 30}, {331, 48, 00}, {331, 52, 30}};

    int punto2[][3] = {{331, 50, 30}, {331, 52, 00}, {331, 40, 30}, {331, 38, 00}, {331, 47, 30}};
    DiffPunti(delta0, punto2, file_punti, size, 2);

    int punto3[][3] = {{332, 00, 30}, {331, 55, 00}, {331, 52, 00}, {331, 52, 00}, {331, 45, 30}};
    DiffPunti(delta0, punto3, file_punti, size, 3);

    int punto4[][3] = {{332, 00, 30}, {332, 00, 30}, {332, 9, 30}, {332, 5, 30}, {331, 40, 30}};
    DiffPunti(delta0, punto4, file_punti, size, 4);
    
    file_punti.close();


//GAS IGNOTO
    file_gasIgnoto.open ("gas_ignoto.txt", ios::out);

    file_gasIgnoto<<"#angoli gas ignoto:"<<endl;
    int riga1[][3] = {{235, 22, 00}, {235, 20, 00}, {235, 27, 30}}; //rosso
    double sizeRighe = sizeof(riga1)/sizeof(riga1[0]);

    Diff(riga1, delta0, file_gasIgnoto, sizeRighe, size);

    int riga2[][3] = {{235, 02, 00}, {235, 47, 00}, {235, 01, 00}}; //giallo
    Diff(riga2, delta0, file_gasIgnoto,sizeRighe, size);

    int riga3[][3] = {{234, 00, 30}, {233, 41, 00}, {233, 43, 00}}; //verde
    Diff(riga3, delta0, file_gasIgnoto, sizeRighe, size);

    int riga4[][3] = {{233, 44, 00}, {233, 40, 00}, {233, 46, 00}}; //ciano
    Diff(riga4, delta0, file_gasIgnoto, sizeRighe, size);

    int riga5[][3] = {{233, 20, 30}, {233, 20, 00}, {233, 22, 00}}; //blu
    Diff(riga5, delta0, file_gasIgnoto, sizeRighe, size);

    int riga6[][3] = {{233, 01, 30}, {232, 52, 00}, {232, 46, 00}}; //viola
    Diff(riga6, delta0, file_gasIgnoto, sizeRighe, size);


    file_gasIgnoto.close();

}
