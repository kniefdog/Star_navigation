#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#define pi2arc 3.1415926/180.0
using namespace std;
struct star
{
    int num;
    double xd;
    double cj;
    double cw;
}ll[510],l;

int main()
{
    FILE*res;  FILE*des;
    double x1,y1,z1,X1,Y1,Z1,X_1,Y_1;
    double x2,y2,z2,X2,Y2,Z2,X_2,Y_2;
    double x3,y3,z3,X3,Y3,Z3,X_3,Y_3;
    double f = 35.0;
    double A[3][3] = { 0 };
	double B[3][3] = { 0 };
	double C[3][3] = { 0 };
	double D[3][3] = { 0 };
	double E[3][3] = { 0 };
	A[0][0] = -cos(qj*PI); A[0][1] = sin(qj*PI); A[1][0] = sin(qj*PI); A[1][1] = cos(qj*PI); A[2][2] = 1;
	B[0][0] = 1; B[1][1] = sin(Cb0*PI); B[1][2] = cos(Cb0*PI); B[2][1] = cos(Cb0*PI); B[2][2] = -sin(Cb0*PI);
	C[0][0] = -sin(Ca0*PI); C[0][1] = cos(Ca0*PI); C[1][0] = -cos(Ca0*PI); C[1][1] = -sin(Ca0*PI); C[2][2] = 1;
	for (i = 0; i<3; i++)
	for (j = 0; j<3; j++)
	for (n = 0; n<3; n++)
	{
		D[i][j] = D[i][j] + A[i][n] * B[n][j];
	}
	for (i = 0; i<3; i++)
	for (j = 0; j<3; j++)
	for (n = 0; n<3; n++)
	{
		M[i][j] = M[i][j] + D[i][n] * C[n][j];
	}
    res = fopen("G://ะวนโ//star_navigate//star//star_database.txt","r");
	if(res == nullptr){
        printf("111can not open file.\n");
		exit(0);
	}
	for(int k=0;k<510;k++){
        fscanf(res, "%d, %lf, %lf, %lf", &l.num, &l.xd, &l.cj, &l.cw);
        ll[k].num = l.num;
        ll[k].xd = l.xd;
        ll[k].cj = l.cj;
        ll[k].cw = l.cw;
    }
    for(int i=0;i<510;i++){
        x1 = cos(ll[i].cj*pi2arc)*cos(ll[i].cw*pi2arc);
        y1 = sin(ll[i].cj*pi2arc)*cos(ll[i].cw*pi2arc);
        z1 = sin(ll[i].cw*pi2arc);
        X1 = M[0][0] * x1 + M[0][1] * y1 + M[0][2] * z1;
        Y1 = M[1][0] * x1 + M[1][1] * y1 + M[1][2] * z1;
        Z1 = M[2][0] * x1 + M[2][1] * y1 + M[2][2] * z1;
        X_1 = -f * X1 / Z1;
        Y_1 = -f * Y1 / Z1;
        for(int j=i+1;j<510;j++){
            x2 = cos(ll[j].cj*pi2arc)*cos(ll[j].cw*pi2arc);
            y2 = sin(ll[j].cj*pi2arc)*cos(ll[j].cw*pi2arc);
            z2 = sin(ll[j].cw*pi2arc);
            X2 = M[0][0] * x2 + M[0][1] * y2 + M[0][2] * z2;
            Y2 = M[1][0] * x2 + M[1][1] * y2 + M[1][2] * z2;
            Z2 = M[2][0] * x2 + M[2][1] * y2 + M[2][2] * z2;
            X_2 = -f * X2 / Z2;
            Y_2 = -f * Y2 / Z2;
            for(int k=j+1;k<510;k++){
                x3 = cos(ll[k].cj*pi2arc)*cos(ll[k].cw*pi2arc);
                y3 = sin(ll[k].cj*pi2arc)*cos(ll[k].cw*pi2arc);
                z3 = sin(ll[k].cw*pi2arc);
                X3 = M[0][0] * x3 + M[0][1] * y3 + M[0][2] * z3;
                Y3 = M[1][0] * x3 + M[1][1] * y3 + M[1][2] * z3;
                Z3 = M[2][0] * x3 + M[2][1] * y3 + M[2][2] * z3;
                X_3 = -f * X3 / Z3;
                Y_3 = -f * Y3 / Z3;
                jj12 = acos((x1*x2 + y1*y2 + z1*z2) / (sqrt(x1*x1 + y1*y1 + z1*z1) * sqrt(x2*x2 + y2*y2 + z2*z2))) / 3.1415926*180.0;
                jj13 = acos((x1*x3 + y1*y3 + z1*z3) / (sqrt(x1*x1 + y1*y1 + z1*z1) * sqrt(x3*x3 + y3*y3 + z3*z3))) / 3.1415926*180.0;
                jj23 = acos((x2*x3 + y2*y3 + z2*z3) / (sqrt(x2*x2 + y2*y2 + z2*z2) * sqrt(x3*x3 + y3*y3 + z3*z3))) / 3.1415926*180.0;
                if(jj12 < 24.0 && jj13 <24.0 && jj23 < 24.0){
                    cout<<ll[i].num<<" "<<ll[j].num<<" "<<ll[k].num<<" "<<endl;
                }
            }
        }
    }
    return 0;

}
