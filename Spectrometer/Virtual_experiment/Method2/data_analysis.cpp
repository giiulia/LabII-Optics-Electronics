#include "../../clean_data.h"
#include <iostream>
#include <fstream>

void fills_parable_fil(ofstream &parable_file, int theta1[][3], int delta1[][3],int theta2[][3], int delta2[][3],int theta3[][3], int delta3[][3],int theta4[][3], int delta4[][3],int theta5[][3], int delta5[][3], int theta6[][3], int delta6[][3]){
    int number_of_measures = 5;

    parable_file<<"#theta\t\tdelta\t\tdev_delta"<<endl;

    double theta1Dec[1];
    double delta1Dec[number_of_measures];
    double mediaDelta[3];

    NormalForm( theta1, theta1Dec, 1);
    DegreeToRadiant( theta1Dec, 1 );

    NormalForm( delta1, delta1Dec, number_of_measures);
    DegreeToRadiant( delta1Dec, number_of_measures );
    Med_Var_Dev(delta1Dec, mediaDelta, number_of_measures);

    parable_file<<theta1Dec[0]<<"\t"<<mediaDelta[0]<<"\t"<<mediaDelta[2]<<endl;

    NormalForm( theta2, theta1Dec, 1);
    DegreeToRadiant( theta1Dec, 1 );

    NormalForm( delta2, delta1Dec, number_of_measures );
    DegreeToRadiant( delta1Dec, number_of_measures );
    Med_Var_Dev(delta1Dec, mediaDelta, number_of_measures );
    
    parable_file<<theta1Dec[0]<<"\t"<<mediaDelta[0]<<"\t"<<mediaDelta[2]<<endl;


    NormalForm( theta3, theta1Dec, 1);
    DegreeToRadiant( theta1Dec, 1 );

    NormalForm( delta3, delta1Dec, number_of_measures );
    DegreeToRadiant( delta1Dec, number_of_measures );
    Med_Var_Dev(delta1Dec, mediaDelta, number_of_measures );

    parable_file<<theta1Dec[0]<<"\t"<<mediaDelta[0]<<"\t"<<mediaDelta[2]<<endl;

    NormalForm( theta4, theta1Dec, 1);
    DegreeToRadiant( theta1Dec, 1 );

    NormalForm( delta4, delta1Dec, number_of_measures );
    DegreeToRadiant( delta1Dec, number_of_measures );
    Med_Var_Dev(delta1Dec, mediaDelta, number_of_measures );

    parable_file<<theta1Dec[0]<<"\t"<<mediaDelta[0]<<"\t"<<mediaDelta[2]<<endl;


    NormalForm( theta5, theta1Dec, 1);
    DegreeToRadiant( theta1Dec, 1 );

    NormalForm( delta5, delta1Dec, number_of_measures);
    DegreeToRadiant( delta1Dec, number_of_measures );
    Med_Var_Dev(delta1Dec, mediaDelta, number_of_measures);

    parable_file<<theta1Dec[0]<<"\t"<<mediaDelta[0]<<"\t"<<mediaDelta[2]<<endl;

    NormalForm( theta6, theta1Dec, 1);
    DegreeToRadiant( theta1Dec, 1 );

    NormalForm( delta6, delta1Dec, number_of_measures);
    DegreeToRadiant( delta1Dec, number_of_measures );
    Med_Var_Dev(delta1Dec, mediaDelta, number_of_measures);

    parable_file<<theta1Dec[0]<<"\t"<<mediaDelta[0]<<"\t"<<mediaDelta[2]<<endl;
/*
    NormalForm( theta7, theta1Dec, 1);
    DegreeToRadiant( theta1Dec, 1 );

    NormalForm( delta7, delta1Dec, number_of_measures);
    DegreeToRadiant( delta1Dec, number_of_measures );
    Med_Var_Dev(delta1Dec, mediaDelta, number_of_measures);

    parable_file<<theta1Dec[0]<<"\t"<<mediaDelta[0]<<"\t"<<mediaDelta[2]<<endl;

    NormalForm( theta8, theta1Dec, 1);
    DegreeToRadiant( theta1Dec, 1 );

    NormalForm( delta8, delta1Dec, number_of_measures);
    DegreeToRadiant( delta1Dec, number_of_measures );
    Med_Var_Dev(delta1Dec, mediaDelta, number_of_measures);

    parable_file<<theta1Dec[0]<<"\t"<<mediaDelta[0]<<"\t"<<mediaDelta[2]<<endl;

    NormalForm( theta9, theta1Dec, 1);
    DegreeToRadiant( theta1Dec, 1 );

    NormalForm( delta9, delta1Dec, number_of_measures);
    DegreeToRadiant( delta1Dec, number_of_measures );
    Med_Var_Dev(delta1Dec, mediaDelta, number_of_measures);

    parable_file<<theta1Dec[0]<<"\t"<<mediaDelta[0]<<"\t"<<mediaDelta[2]<<endl;
*/
}

using namespace std;
int main(int argc, char*argv[]){

    int number_of_measures = 5;

/*
//PARABLE METHOD lambda1
    ofstream parable_file1;

    parable_file1.open ("parable1.txt", ios::out);

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

    fills_parable_file(parable_file1, theta11, delta11, theta21, delta21,theta31, delta31,theta41, delta41,theta51, delta51,  theta61, delta61,  theta71, delta71, theta81, delta81, theta91, delta91);
    parable_file1.close();
*/
//PARABLE METHOD lambda2
    ofstream parable_file2;

    parable_file2.open ("parable2.txt", ios::out);

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

    

    fills_parable_file(parable_file2, theta12, delta12, theta22, delta22,theta32, delta32,theta42, delta42,theta52, delta52, theta62, delta62);

    parable_file2.close();
/*
//PARABLE METHOD lambda3
    ofstream parable_file3;

    parable_file3.open ("parable3.txt", ios::out);
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

    fills_parable_file(parable_file3, theta13, delta13, theta23, delta23,theta33, delta33,theta43, delta43,theta53, delta53, theta63, delta63,  theta73, delta73);

    parable_file3.close();
*/
//PARABLE METHOD lambda4
    ofstream parable_file4;

    parable_file4.open ("parable4.txt", ios::out);

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
    fills_parable_file(parable_file4, theta14, delta14, theta24, delta24,theta34, delta34,theta44, delta44,theta54, delta54, theta64, delta64);

    parable_file4.close();
/*
//PARABLE METHOD lambda5
    ofstream parable_file5;

    parable_file5.open ("parable5.txt", ios::out);

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
    fills_parable_file(parable_file5, theta15, delta15, theta25, delta25,theta35, delta35,theta45, delta45,theta55, delta55, theta65, delta65, theta75, delta75);

    parable_file5.close();
*/

    return 0;
}
