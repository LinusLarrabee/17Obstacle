//
//  main.cpp
//  17Obstacle
//
//  Created by 孙浩 on 2018/3/3.
//  Copyright © 2018年 BUAA F632. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cmath>
#define π 3.141592653589793
using namespace std;
int main(int argc, const char * argv[]) {
    ifstream fin("17Obstacle.in");
    ofstream fout("17Obstacle.out");
    
    long double r0,Xita0,VO,VF,Beta,R,Alpha;
    fin >> r0 >> Xita0 >> VO >> VF >> Beta >>R>>Alpha;
    long double u, v, p, A,AP,Epxinon,EP,Yita;
    long double S[3][3]={0};
    
    long double VOsqrt[4],VO1,VO2;
    Xita0 *= (π/180);
    Beta *= (π/180);
    Alpha *= (π/180);
    p = R/sqrt(r0*r0-R*R);
    if (p<0) {
        p = -p;
    }
    
    u = Beta - Xita0;
    v = VO/VF;
    A = (p*cos(u)+sin(u))/sqrt(p*p+1);
    AP = (p*cos(u)-sin(u))/sqrt(p*p+1);
    Epxinon = asin(p/sqrt(p*p+1));
    EP = π - Epxinon;
    Yita = Alpha - Xita0;

    VOsqrt[0] = 0.5f * VF * (p*cos(u)+sin(u)) * sqrt(p*p + 1) /p;
    VOsqrt[1] = 0.5f * VF * (p*cos(u)-sin(u)) * sqrt(p*p + 1) /p;
    VOsqrt[2] = - VOsqrt[0];
    VOsqrt[3] = - VOsqrt[1];
    VO1 = VF * (p*cos(u)+sin(u))/(p*cos(Yita)+sin(Yita));
    VO2 = VF * (p*cos(u)-sin(u))/(p*cos(Yita)-sin(Yita));

    double k =tan(Yita)*tan(Yita) - p*p;
    if (Alpha - Beta > 0 && Alpha - Beta < π)
    {
        S[1][0] = VO1;
        S[1][1] = VO2;//>VO1,<VO2
        if (tan(Yita)*tan(Yita) - p*p > 0)
            S[1][2] = 1;//开区间
        else S[1][2] = 0;
    }
    if ((Alpha - Beta > π && Alpha - Beta < 2*π)||(Alpha - Beta > -π && Alpha - Beta < 0))
    {
        S[1][0] = VO2;
        S[1][1] = VO1;//>VO2,<VO1
        if (tan(Yita)*tan(Yita) - p*p > 0)
            S[1][2] = 1;
        else S[1][2] = 0;
    }
    //暂时忽略想等情况，因为浮点数下相等问题无法解决
    S[2][0] = VF*cos(u)/cos(Yita);
    if (cos(Yita)>0)
    {
        S[2][2] = 1;///<
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            fout << S[i][j] <<" ";
        }
        fout <<endl;
    }
    fout << k<<endl<< VO1<<endl<< VO2;//<<endl<<Epxinon<<endl<<A<<endl<<180-Epxinon<<endl<<AP;
    return 0;
}
