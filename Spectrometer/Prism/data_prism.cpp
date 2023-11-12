#include <iostream>
#include <cmath>
#include <fstream>

#include "../clean_data.h"

int main(int argc, char*argv[]){
    ofstream Hg_file;
    ofstream IgnoteGas_file;

    ofstream points_file; //for parable

    Hg_file.open ("min_delta.txt", ios::out);
    double size;

    double lines[] = {579.0663, 576.9598,  546.0735, 435.8328,  404.6563}; //yellow dx, yellow sx, green, blue, lilliac
    Hg_file<<lines[0]<<"\t"<<lines[1]<<"\t"<<lines[2]<<"\t"<<lines[3]<<"\t"<<lines[4]<<endl; //prints the lambda on file

    int alpha1[][3] = {{128, 35, 30}, {128, 41, 00}, {128, 51, 00}, {128, 38, 00}, {128, 34, 30}};
    int alpha2[][3] = {{8, 05, 00}, {8, 10, 00}, {8, 18, 00}, {8, 8, 00}, {8, 12, 30} };
    size = sizeof(alpha1)/sizeof(alpha1[0]);
    Diff(alpha2, alpha1, Hg_file, size, size); //prints angle of rotation on file

    Hg_file<<0.048<<"\t"<<0.000577<<endl;

    //zero point
    int delta0[][3] = {{283,05,00}, {283, 02, 30}, {283, 02, 00}, {283, 01, 00}, {283, 03, 00}};

//DIRECT METHOD

    //yellow right
    Hg_file<<"\n#yellow dx:"<<endl;
    int deltaG1[][3] = {{331, 33, 00}, {331, 35, 30}, {331, 34, 30}, {331, 35, 30}, {331, 29, 30}};
    Diff(delta0, deltaG1, Hg_file, size, size);

    //yellow left
    Hg_file<<"\n#yellow sx:"<<endl;;
    int deltaG2[][3] = {{331, 44, 30}, {331, 34, 30}, {331, 29, 00}, {331, 42, 30}, {331, 41, 00}}; 
    Diff(delta0, deltaG2, Hg_file, size, size);

    //line green
    Hg_file<<"\n#green:"<<endl;
    int deltaV[][3] = {{331, 40, 30}, {331, 43, 30}, {331, 41, 00}, {331, 40, 30}, {331, 45, 30}};
    Diff(delta0, deltaV, Hg_file, size, size);

    //line blue
    Hg_file<<"\n#blue:"<<endl;
    int deltaB[][3] = {{333, 25, 30}, {333, 29, 30}, {333, 40, 30}, {333, 30, 30}, {333, 30, 00}};
    Diff(delta0, deltaB, Hg_file, size, size);

    //line lilliac
    Hg_file<<"#\nlilliac:"<<endl;
    int deltaL[][3] = {{333, 42, 30}, {333, 42, 30}, {333, 41, 00}, {333, 40, 30}, {333, 43, 30}};
    Diff(delta0, deltaL, Hg_file, size, size);

    Hg_file.close();

//PARABLE METHOD (green)
    points_file.open ("points.txt", ios::out);
    points_file<<"#index\t\tangle\tdev_media"<<endl;

    int point1[][3] = {{332, 04, 30}, {331, 50, 0}, {331, 50, 30}, {331, 54, 30}, {332, 04, 00}};
    DiffPoints(delta0, point1, points_file, size, 1);

    int point2[][3] = {{331, 50, 30}, {331, 52, 00}, {331, 40, 30}, {331, 38, 00}, {331, 47, 30}};
    DiffPoints(delta0, point2, points_file, size, 2);

    int point3[][3] = {{332, 00, 30}, {331, 55, 00}, {331, 52, 00}, {331, 52, 00}, {331, 45, 30}};
    DiffPoints(delta0, point3, points_file, size, 3);

    int point4[][3] = {{332, 00, 30}, {332, 00, 30}, {332, 9, 30}, {332, 5, 30}, {331, 40, 30}};
    DiffPoints(delta0, point4, points_file, size, 4);
    
    points_file.close();


//IGNOTE GAS
    IgnoteGas_file.open ("ignote_gas.txt", ios::out);

    IgnoteGas_file<<"#angles ignote gas:"<<endl;
    int line1[][3] = {{235, 22, 00}, {235, 20, 00}, {235, 27, 30}}; //rosso
    double sizeLines = sizeof(line1)/sizeof(line1[0]);

    Diff(line1, delta0, IgnoteGas_file, sizeLines, size);

    int line2[][3] = {{235, 02, 00}, {235, 47, 00}, {235, 01, 00}}; //giallo
    Diff(line2, delta0, IgnoteGas_file,sizeLines, size);

    int line3[][3] = {{234, 00, 30}, {233, 41, 00}, {233, 43, 00}}; //green
    Diff(line3, delta0, IgnoteGas_file, sizeLines, size);

    int line4[][3] = {{233, 44, 00}, {233, 40, 00}, {233, 46, 00}}; //ciano
    Diff(line4, delta0, IgnoteGas_file, sizeLines, size);

    int line5[][3] = {{233, 20, 30}, {233, 20, 00}, {233, 22, 00}}; //blue
    Diff(line5, delta0, IgnoteGas_file, sizeLines, size);

    int line6[][3] = {{233, 01, 30}, {232, 52, 00}, {232, 46, 00}}; //viola
    Diff(line6, delta0, IgnoteGas_file, sizeLines, size);


    IgnoteGas_file.close();

}
 