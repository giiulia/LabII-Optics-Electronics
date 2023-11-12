#include "../../clean_data.h"
#include <iostream>
#include <fstream>

using namespace std;
int main(int argc, char*argv[]){
    ofstream Hg_file;

    int number_of_measures = 5;

//DIRECT METHOD
    Hg_file.open ("min_delta.txt", ios::out);
    Hg_file<<"434.8064"<<"\t"<<"460.9567"<<"\t"<<"487.9864"<<"\t"<<"696.5431"<<"\t"<<"738.398"<<endl; //prints lambda on file
    Hg_file<<"1.0475"<<endl; //vertex angle [rad]
    Hg_file<<"0.0531"<<endl; //prism base


    double lambda1Dec[number_of_measures];
    double mean1[3];
    int lambda1[][3] = {{35, 5, 00}, {35, 22, 00}, {35, 18, 00}, {35, 17, 00}, {35, 18, 00}};
    NormalForm( lambda1, lambda1Dec, number_of_measures);
    Med_Var_Dev(lambda1Dec, mean1, number_of_measures);
    cout<<"lambda1: "<<mean1[0]<<" "<<mean1[2]<<endl;

    DegreeToRadiant( lambda1Dec, number_of_measures );
    Med_Var_Dev(lambda1Dec, mean1, number_of_measures);
    cout<<"lambda1: "<<mean1[0]<<" "<<mean1[2]<<endl;
    //mean1[2] = 0.0002909;
    Hg_file<<mean1[0]<<" "<<mean1[2]<<endl;


    double lambda2Dec[number_of_measures];
    double mean2[3];    
    int lambda2[][3] = {{35, 2, 00}, {35, 2, 00}, {35, 25, 00}, {35, 14, 00}, {35, 5, 00}}; 
    NormalForm( lambda2, lambda2Dec, number_of_measures);
    Med_Var_Dev(lambda2Dec, mean2, number_of_measures);
    cout<<"lambda2: "<<mean2[0]<<" "<<mean2[2]<<endl;

    DegreeToRadiant( lambda2Dec, number_of_measures );
    Med_Var_Dev(lambda2Dec, mean2, number_of_measures);
    cout<<"lambda2: "<<mean2[0]<<" "<<mean2[2]<<endl;
    //mean2[2] = 0.0002909;
    Hg_file<<mean2[0]<<" "<<mean2[2]<<endl;


    double lambda3Dec[number_of_measures];
    double mean3[3];    
    int lambda3[][3] = {{34, 50, 00}, {34, 56, 00}, {34, 55, 00}, {35, 00, 00}, {34, 48, 00}};
    NormalForm( lambda3, lambda3Dec, number_of_measures);
    Med_Var_Dev(lambda3Dec, mean3, number_of_measures);
    cout<<"lambda3: "<<mean3[0]<<" "<<mean3[2]<<endl;


    DegreeToRadiant( lambda3Dec, number_of_measures );
    Med_Var_Dev(lambda3Dec, mean3, number_of_measures);
    cout<<"lambda3: "<<mean3[0]<<" "<<mean3[2]<<endl;
    //mean3[2] = 0.0002909;
    Hg_file<<mean3[0]<<" "<<mean3[2]<<endl;


    double lambda4Dec[number_of_measures];
    double mean4[3];    
    int lambda4[][3] = {{34, 22, 00}, {34, 25, 00}, {34, 26, 00}, {34, 17, 00}, {34, 26, 00}};
    NormalForm( lambda4, lambda4Dec, number_of_measures);
    Med_Var_Dev(lambda4Dec, mean4, number_of_measures);
    cout<<"lambda4: "<<mean4[0]<<" "<<mean4[2]<<endl;

    DegreeToRadiant( lambda4Dec, number_of_measures );
    Med_Var_Dev(lambda4Dec, mean4, number_of_measures);
    cout<<"lambda4: "<<mean4[0]<<" "<<mean4[2]<<endl;
    //mean4[2] = 0.0002909;
    Hg_file<<mean4[0]<<" "<<mean4[2]<<endl;


    double lambda5Dec[number_of_measures];
    double mean5[3];   
    int lambda5[][3] = {{34, 11, 00}, {34, 9, 00}, {34, 21, 00}, {34, 12, 00}, {34, 11, 00}};
    NormalForm( lambda5, lambda5Dec, number_of_measures);
    Med_Var_Dev(lambda5Dec, mean5, number_of_measures);
    cout<<"lambda5: "<<mean5[0]<<" "<<mean5[2]<<endl;

    DegreeToRadiant( lambda5Dec, number_of_measures );
    Med_Var_Dev(lambda5Dec, mean5, number_of_measures);
    cout<<"lambda5: "<<mean5[0]<<" "<<mean5[2]<<endl;
    //mean5[2] = 0.0002909;
    Hg_file<<mean5[0]<<" "<<mean5[2]<<endl;

    Hg_file.close();

    return 0;
}
