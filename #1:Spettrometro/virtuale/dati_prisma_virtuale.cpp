#include "../clean_data.h"
#include <iostream>
#include <fstream>

void riempie_file_punti(ofstream &file_punti, int theta1[][3], int delta1[][3],int theta2[][3], int delta2[][3],int theta3[][3], int delta3[][3],int theta4[][3], int delta4[][3],int theta5[][3], int delta5[][3], int theta6[][3], int delta6[][3], int theta7[][3], int delta7[][3]){
    int numeroMisure = 5;

    file_punti<<"#theta\t\tdelta\t\tdev_delta"<<endl;

    double theta1Dec[1];
    double delta1Dec[numeroMisure];
    double mediaDelta[3];

    NormalForm( theta1, theta1Dec, 1);
    DegreeToRadiant( theta1Dec, 1 );

    NormalForm( delta1, delta1Dec, numeroMisure);
    DegreeToRadiant( delta1Dec, numeroMisure );
    Med_Var_Dev(delta1Dec, mediaDelta, numeroMisure);

    file_punti<<theta1Dec[0]<<"\t"<<mediaDelta[0]<<"\t"<<mediaDelta[2]<<endl;

    NormalForm( theta2, theta1Dec, 1);
    DegreeToRadiant( theta1Dec, 1 );

    NormalForm( delta2, delta1Dec, numeroMisure );
    DegreeToRadiant( delta1Dec, numeroMisure );
    Med_Var_Dev(delta1Dec, mediaDelta, numeroMisure );
    
    file_punti<<theta1Dec[0]<<"\t"<<mediaDelta[0]<<"\t"<<mediaDelta[2]<<endl;


    NormalForm( theta3, theta1Dec, 1);
    DegreeToRadiant( theta1Dec, 1 );

    NormalForm( delta3, delta1Dec, numeroMisure );
    DegreeToRadiant( delta1Dec, numeroMisure );
    Med_Var_Dev(delta1Dec, mediaDelta, numeroMisure );

    file_punti<<theta1Dec[0]<<"\t"<<mediaDelta[0]<<"\t"<<mediaDelta[2]<<endl;

    NormalForm( theta4, theta1Dec, 1);
    DegreeToRadiant( theta1Dec, 1 );

    NormalForm( delta4, delta1Dec, numeroMisure );
    DegreeToRadiant( delta1Dec, numeroMisure );
    Med_Var_Dev(delta1Dec, mediaDelta, numeroMisure );

    file_punti<<theta1Dec[0]<<"\t"<<mediaDelta[0]<<"\t"<<mediaDelta[2]<<endl;


    NormalForm( theta5, theta1Dec, 1);
    DegreeToRadiant( theta1Dec, 1 );

    NormalForm( delta5, delta1Dec, numeroMisure);
    DegreeToRadiant( delta1Dec, numeroMisure );
    Med_Var_Dev(delta1Dec, mediaDelta, numeroMisure);

    file_punti<<theta1Dec[0]<<"\t"<<mediaDelta[0]<<"\t"<<mediaDelta[2]<<endl;

    NormalForm( theta6, theta1Dec, 1);
    DegreeToRadiant( theta1Dec, 1 );

    NormalForm( delta6, delta1Dec, numeroMisure);
    DegreeToRadiant( delta1Dec, numeroMisure );
    Med_Var_Dev(delta1Dec, mediaDelta, numeroMisure);

    file_punti<<theta1Dec[0]<<"\t"<<mediaDelta[0]<<"\t"<<mediaDelta[2]<<endl;

    NormalForm( theta7, theta1Dec, 1);
    DegreeToRadiant( theta1Dec, 1 );

    NormalForm( delta7, delta1Dec, numeroMisure);
    DegreeToRadiant( delta1Dec, numeroMisure );
    Med_Var_Dev(delta1Dec, mediaDelta, numeroMisure);

    file_punti<<theta1Dec[0]<<"\t"<<mediaDelta[0]<<"\t"<<mediaDelta[2]<<endl;
/*
    NormalForm( theta8, theta1Dec, 1);
    DegreeToRadiant( theta1Dec, 1 );

    NormalForm( delta8, delta1Dec, numeroMisure);
    DegreeToRadiant( delta1Dec, numeroMisure );
    Med_Var_Dev(delta1Dec, mediaDelta, numeroMisure);

    file_punti<<theta1Dec[0]<<"\t"<<mediaDelta[0]<<"\t"<<mediaDelta[2]<<endl;

    NormalForm( theta9, theta1Dec, 1);
    DegreeToRadiant( theta1Dec, 1 );

    NormalForm( delta9, delta1Dec, numeroMisure);
    DegreeToRadiant( delta1Dec, numeroMisure );
    Med_Var_Dev(delta1Dec, mediaDelta, numeroMisure);

    file_punti<<theta1Dec[0]<<"\t"<<mediaDelta[0]<<"\t"<<mediaDelta[2]<<endl;
*/
}

using namespace std;
int main(int argc, char*argv[]){
    ofstream file_Hg;

    int numeroMisure = 5;
//METODO DIRETTO
    file_Hg.open ("delta_min.txt", ios::out);
    file_Hg<<"434.8064"<<"\t"<<"460.9567"<<"\t"<<"487.9864"<<"\t"<<"696.5431"<<"\t"<<"738.398"<<endl; //stampa le lambda su file
    file_Hg<<"1.0475"<<endl; //angolo al vertice in rad
    file_Hg<<"0.0531"<<endl; //base prisma


    double lambda1Dec[numeroMisure];
    double media1[3];
    int lambda1[][3] = {{35, 5, 00}, {35, 22, 00}, {35, 18, 00}, {35, 17, 00}, {35, 18, 00}};
    NormalForm( lambda1, lambda1Dec, numeroMisure);
    Med_Var_Dev(lambda1Dec, media1, numeroMisure);
    cout<<"lambda1: "<<media1[0]<<" "<<media1[2]<<endl;

    DegreeToRadiant( lambda1Dec, numeroMisure );
    Med_Var_Dev(lambda1Dec, media1, numeroMisure);
    cout<<"lambda1: "<<media1[0]<<" "<<media1[2]<<endl;
    //media1[2] = 0.0002909;
    file_Hg<<media1[0]<<" "<<media1[2]<<endl;


    double lambda2Dec[numeroMisure];
    double media2[3];    
    int lambda2[][3] = {{35, 2, 00}, {35, 2, 00}, {35, 25, 00}, {35, 14, 00}, {35, 5, 00}}; 
    NormalForm( lambda2, lambda2Dec, numeroMisure);
    Med_Var_Dev(lambda2Dec, media2, numeroMisure);
    cout<<"lambda2: "<<media2[0]<<" "<<media2[2]<<endl;

    DegreeToRadiant( lambda2Dec, numeroMisure );
    Med_Var_Dev(lambda2Dec, media2, numeroMisure);
    cout<<"lambda2: "<<media2[0]<<" "<<media2[2]<<endl;
    //media2[2] = 0.0002909;
    file_Hg<<media2[0]<<" "<<media2[2]<<endl;


    double lambda3Dec[numeroMisure];
    double media3[3];    
    int lambda3[][3] = {{34, 50, 00}, {34, 56, 00}, {34, 55, 00}, {35, 00, 00}, {34, 48, 00}};
    NormalForm( lambda3, lambda3Dec, numeroMisure);
    Med_Var_Dev(lambda3Dec, media3, numeroMisure);
    cout<<"lambda3: "<<media3[0]<<" "<<media3[2]<<endl;


    DegreeToRadiant( lambda3Dec, numeroMisure );
    Med_Var_Dev(lambda3Dec, media3, numeroMisure);
    cout<<"lambda3: "<<media3[0]<<" "<<media3[2]<<endl;
    //media3[2] = 0.0002909;
    file_Hg<<media3[0]<<" "<<media3[2]<<endl;


    double lambda4Dec[numeroMisure];
    double media4[3];    
    int lambda4[][3] = {{34, 22, 00}, {34, 25, 00}, {34, 26, 00}, {34, 17, 00}, {34, 26, 00}};
    NormalForm( lambda4, lambda4Dec, numeroMisure);
    Med_Var_Dev(lambda4Dec, media4, numeroMisure);
    cout<<"lambda4: "<<media4[0]<<" "<<media4[2]<<endl;

    DegreeToRadiant( lambda4Dec, numeroMisure );
    Med_Var_Dev(lambda4Dec, media4, numeroMisure);
    cout<<"lambda4: "<<media4[0]<<" "<<media4[2]<<endl;
    //media4[2] = 0.0002909;
    file_Hg<<media4[0]<<" "<<media4[2]<<endl;


    double lambda5Dec[numeroMisure];
    double media5[3];   
    int lambda5[][3] = {{34, 11, 00}, {34, 9, 00}, {34, 21, 00}, {34, 12, 00}, {34, 11, 00}};
    NormalForm( lambda5, lambda5Dec, numeroMisure);
    Med_Var_Dev(lambda5Dec, media5, numeroMisure);
    cout<<"lambda5: "<<media5[0]<<" "<<media5[2]<<endl;

    DegreeToRadiant( lambda5Dec, numeroMisure );
    Med_Var_Dev(lambda5Dec, media5, numeroMisure);
    cout<<"lambda5: "<<media5[0]<<" "<<media5[2]<<endl;
    //media5[2] = 0.0002909;
    file_Hg<<media5[0]<<" "<<media5[2]<<endl;

    file_Hg.close();

//METODO DELLA PARABOLA lambda1
 /*   ofstream file_punti1;

    file_punti1.open ("metodo2/parabola1.txt", ios::out);

    int theta11[][3] = {{48,6,0}};  
    int delta11[][3] = {{35,16,0},{35,18,0},{35,24,0},{35,23,0},{35,26,0}};
    
    int theta21[][3] ={{47,47,0}} ;
    int delta21[][3] = {{35,13,0},{35,19,0},{35,19,0},{35,15,0},{35,14,0}};   

    int theta31[][3] ={{47,38,0}} ;
    int delta31[][3] = {{35,12,0},{35,9,0},{35,12,0},{35,20,0},{35,16,0}};

    int theta41[][3] ={{47,33,0}} ;
    int delta41[][3] = {{35,14,0},{35,15,0},{35,17,0},{35,11,0},{35,13,0}};   

    int theta51[][3] ={{47,28,0}} ;
    int delta51[][3] = {{35,13,0},{35,11,0},{35,15,0},{35,12,0},{35,12,0}};     

    int theta61[][3] ={{47,19,0}} ;
    int delta61[][3] = {{35,20,0},{35,15,0},{35,11,0},{35,19,0},{35,14,0}};

    int theta71[][3] = {{47,10,0}} ;
    int delta71[][3] = {{35,21,0},{35,28,0},{35,13,0},{35,14,0},{35,14,0}};

    int theta81[][3] ={{47,1,0}};
    int delta81[][3] =  {{35,14,0},{35,19,0},{35,26,0},{35,22,0},{35,14,0}};

    int theta91[][3] = {{46,51,0}} ;
    int delta91[][3] = {{35,25,0},{35,25,0},{35,24,0},{35,24,0},{35,36,0}};

    riempie_file_punti(file_punti1, theta11, delta11, theta21, delta21,theta31, delta31,theta41, delta41,theta51, delta51,  theta61, delta61,  theta71, delta71, theta81, delta81, theta91, delta91);
    file_punti1.close();
*/
//METODO DELLA PARABOLA lambda2
/*    ofstream file_punti2;

    file_punti2.open ("metodo2/parabola2.txt", ios::out);
//35 8 minimo

    int theta12[][3] = {{46,44,00}} ;
    int delta12[][3] = {{35,11,00},{35,14,00},{35,11,00},{35,11,00},{35,12,00}};

    int theta22[][3] = {{47,6,00}} ;
    int delta22[][3] = {{35,12,00},{35,11,00},{35,13,00},{35,16,00},{35,5,00}};

    int theta32[][3] = {{48,6,00}} ;
    int delta32[][3] = {{35,8,00},{35,9,00},{35,10,00},{35,10,00},{35,7,00}};

    int theta42[][3] = {{48,34,00}} ;
    int delta42[][3] = {{35,14,00},{35,11,00},{35,11,00},{35,9,00},{35,7,00}};

    int theta52[][3] = {{49,1,00}} ;
    int delta52[][3] = {{35,11,00},{35,14,00},{35,15,00},{35,15,00},{35,12,00}};

    int theta62[][3] = {{49,47,00}} ;
    int delta62[][3] = {{35,23,00},{35,13,00},{35,13,00},{35,15,00},{35,16,00}};

    

    riempie_file_punti(file_punti2, theta12, delta12, theta22, delta22,theta32, delta32,theta42, delta42,theta52, delta52, theta62, delta62);

    file_punti2.close();
*/
//METODO DELLA PARABOLA lambda3
    ofstream file_punti3;

    file_punti3.open ("metodo2/parabola3.txt", ios::out);
    int theta13[][3] = {{48,1,00}};  
    int delta13[][3] = {{35,3,00},{35,5,00},{35,3,00},{35,2,00},{35,2,00}};

    int theta23[][3] = {{47,57,00}};  
    int delta23[][3] = {{34,56,00},{35,0,00},{34,55,00},{34,55,00},{35,2,00}};
   
    int theta33[][3] ={{47,45,00} } ;
    int delta33[][3] = {{34,55,00},{34,53,00},{34,51,00},{34,58,00},{34,58,00}};

    int theta43[][3] = {{47,32,00} } ;
    int delta43[][3] = {{34,56,00},{34,56,00},{34,57,00},{34,58,00},{34,59,00}};

    int theta53[][3] ={{47,21,00} };
    int delta53[][3] =  {{35,6,00},{34,55,00},{34,56,00},{34,58,00},{35,0,00}};

    int theta63[][3] = {  {47,2,00} } ;
    int delta63[][3] = {{35,9,00},{35,7,00},{35,3,00},{35,2,00},{35,3,00}};

    int theta73[][3] = {{46,51,00}} ;
    int delta73[][3] = {{35,6,00},{34,58,00},{35,2,00},{35,0,00},{35,0,00}};

    riempie_file_punti(file_punti3, theta13, delta13, theta23, delta23,theta33, delta33,theta43, delta43,theta53, delta53, theta63, delta63,  theta73, delta73);

    file_punti3.close();

//METODO DELLA PARABOLA lambda4
  /*  ofstream file_punti4;

    file_punti4.open ("metodo2/parabola4.txt", ios::out);

    int theta14[][3] = {{48,33,00}};  
    int delta14[][3] = {{34,31,00},{34,23,00},{34,33,00},{34,31,00},{34,35,00}};
   
    int theta24[][3] ={{48,16,00}} ;
    int delta24[][3] = {{34,29,00},{34,23,00},{34,26,00},{34,21,00},{34,30,00}};

    int theta34[][3] = { {48,3,00} } ;
    int delta34[][3] = {{34,22,00},{34,20,00},{34,19,00},{34,23,00},{34,21,00}};

    int theta44[][3] ={{47,46,00}};
    int delta44[][3] =  {{34,21,00},{34,22,00},{34,24,00},{34,21,00},{34,21,00}};

    int theta54[][3] = { {47,13,00}} ;
    int delta54[][3] = {{34,21,00},{34,23,00},{34,23,00},{34,24,00},{34,25,00}};

    int theta64[][3] = {{46,28,00}} ;
    int delta64[][3] = {{34,20,00},{34,26,00},{34,33,00},{34,21,00},{34,27,00}};
    riempie_file_punti(file_punti4, theta14, delta14, theta24, delta24,theta34, delta34,theta44, delta44,theta54, delta54, theta64, delta64);

    file_punti4.close();
*/
//METODO DELLA PARABOLA lambda5
    ofstream file_punti5;

    file_punti5.open ("metodo2/parabola5.txt", ios::out);

    int theta15[][3] = {{45,45,00}};  
    int delta15[][3] = {{34,23,00},{34,25,00},{34,21,00},{34,20,00},{34,23,00}};
   
    int theta25[][3] ={{46,0,00}} ;
    int delta25[][3] = {{34,22,00},{34,19,00},{34,20,00},{34,18,00},{34,22,00}};

    int theta35[][3] = {{47,8,00}} ;
    int delta35[][3] = {{34,16,00},{34,15,00},{34,18,00},{34,12,00},{34,18,00}};

    int theta45[][3] ={ {47,19,00} };
    int delta45[][3] =  {{34,14,00},{34,13,00},{34,17,00},{34,16,00},{34,15,00}};

    int theta55[][3] ={ {47,35,00} };
    int delta55[][3] =  {{34,17,00},{34,18,00},{34,16,00},{34,15,00},{34,15,00}};

    int theta65[][3] = {{48,1}} ;
    int delta65[][3] = {{34,21,00},{34,21,00},{34,17,00},{34,19,00},{34,18,00}};

    int theta75[][3] = {{48,20,00}} ;
    int delta75[][3] = {{34,19,00},{34,20,00},{34,23,00},{34,17,00},{34,18,00}};
    riempie_file_punti(file_punti5, theta15, delta15, theta25, delta25,theta35, delta35,theta45, delta45,theta55, delta55, theta65, delta65, theta75, delta75);

    file_punti5.close();


    return 0;
}
