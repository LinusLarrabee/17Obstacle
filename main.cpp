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
#define π 3.1415926
using namespace std;
int main(int argc, const char * argv[]) {
    ifstream fin("17Obstacle.in");
    ofstream fout("17Obstacle.out");
    
    long double r0,Xita0,VO,VF,Beta,R,fay;
    fin >> r0 >> Xita0 >> VO >> VF >> Beta >>R>>fay;
    long double u, v, p, A,AP,Epxinon,EP;
    long double alpha[3][3];
    
    p = tan(fay/2);
    if (p<0) {
        p = -p;
    }
    u = Beta - Xita0;
    v = VO/VF;
    A = (p*cos(u)+sin(u))/sqrt(p*p+1);
    AP = (p*cos(u)-sin(u))/sqrt(p*p+1);
    Epxinon = asin(p/sqrt(p*p+1));
    EP = π - Epxinon;
    
    if (cos(u)/v >= 1){
        alpha[0][0] = -4;//N1 is null
    }
    else if (cos(u)/v <= -1){
        alpha[0][0] = 4;//0 to 2π
    }
    else {
        alpha[0][1] = acos(cos(u)/v);
        alpha[0][0] = -alpha[0][1];
    }
    
    if (A/v>1)
    {
        alpha[1][0] = -4;/* N21 is null */
    }
    else if ((A/v) >= 0 && (A/v) <= 1)
    {
        alpha[1][0] = asin(A/v) - Epxinon;
        alpha[1][1] = π - asin(A/v) - Epxinon;
    }
    else if ((A/v) >= -1 && (A/v) <= 0)
    {
        alpha[1][0] = asin(A/v) - Epxinon;
        alpha[1][1] = -π - asin(A/v) - Epxinon;
        alpha[1][2] = 1;//外包
    }
    else
    {
        alpha[1][0] = 4;/* 0 to 2π */
    }
    
    if (AP/v>1)
    {
        alpha[2][0] = -4;/* N22 is null */
    }
    else if ((AP/v) >= 0 && (AP/v) <= 1)
    {
        alpha[2][0] = asin(AP/v) - EP;
        alpha[2][1] = π - asin(AP/v) - EP;
    }
    else if ((AP/v) >= -1 && (AP/v) <= 0)
    {
        alpha[2][0] = asin(AP/v) - EP;
        alpha[2][1] = -π - asin(AP/v) - EP;
        alpha[2][2] = 1;//外包
    }
    else
    {
        alpha[2][0] = 4;/* 0 to 2π */
    }
    
    if (A/v >1 || AP/v >1)
    {
        alpha[1][2] = -1;
    }
    long double k = 0.5f *(asin(A/v)+asin(AP/v));
    if (k<0) {
        k = -k;
    }
    if (A/v >-1 && A/v <=1 && AP/v >-1 && AP/v <=1)
    {
        if (v>1 && Epxinon >=k)
        {
            alpha[1][1] = alpha[2][1];
            alpha[0][2] = 1;//只考虑前两行
        }
        if (v<1 && Epxinon <=k)
        {
            double temp = alpha[1][1];
            alpha[1][1] = alpha[2][1];
            alpha[2][1] = temp;
            alpha[0][2] = 2;//全部的三行都要考虑
        }
        else alpha[1][2] = -2;
    }
    if (A/v <=-1 && AP/v >-1 && AP/v<=1)
    {
        alpha[0][2] = 3;//只考虑N22
    }
    if (AP/v <=-1 && A/v >-1 && A/v<=1)
    {
        alpha[0][2] = 4;//只考虑N21
    }
    if (AP/v <=-1 && A/v<=-1)
    {
        alpha[0][2] = 5;
    }
    for (int i = 0; i <3; i++) {
        for (int j = 0; j <3; j++) {
            if (j != 2) {
                alpha[i][j] *= (180/π);
            }
            fout << alpha[i][j]<<" ";
        }
        fout <<endl;
    }
    u*=180/π;
    Epxinon*=180/π;
    fout << u<<endl<< v<<endl<< p<<endl<<Epxinon<<endl<<A<<endl<<180-Epxinon<<endl<<AP;
    return 0;
}
