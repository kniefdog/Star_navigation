/**************
 *编写主题:
 *编写时间:
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include<iostream>
using namespace std;
float max_mine(float x,float y,float z);
float mid_mine(float x,float y,float z);
float jj(float x1,float y1,float z1,float x2,float y2,float z2);
float* sort_mine(float x,float y,float z);
struct star1{
    int num;
    float xd;
    float cj;
    float cw;
}l,list[40];

int main()
{
    FILE* fp;
    errno_t err;
    float x1,y1,z1,x2,y2,z2,x3,y3,z3,jj_1_2,jj_1_3,jj_2_3;
    float* res;
    float T;
    fstream fout("D://mycppspace//star_navigate//jiaojuku//10-11_jj.txt");
    if ((err = fopen_s(&fp, "D://mycppspace//star_navigate//jiaojuku//10-11.txt", "rt")) != 0)
		{
			printf("can not open file1.\n");
			exit(0);
		}
    for(int k=0;k<40;k++){
        fscanf(fp,"%d, %f, %f, %f",&list[k].num, &list[k].xd, &list[k].cj, &list[k].cw);
    }
    for(int k=0;k<40;k++){
        //fscanf(fp,"%d, %f,%f,%f",&list[k].num, &list[k].xd, &list[k].cj, &list[k].cw);
        cout<<list[k].num<<" "<<list[k].xd<<" "<<list[k].cj<<" "<<list[k].cw<<endl;
    }
    for(int i=0;i<40;i++){
            x1 = cos(list[i].cj*3.1415926 / 180.0)*cos(list[i].cw*3.1415926 / 180.0);
            y1 = sin(list[i].cj*3.1415926 / 180.0)*cos(list[i].cw*3.1415926 / 180.0);
            z1 = sin(list[i].cw*3.1415926 / 180.0);
        for(int j=i+1;j<40;j++){
                x2 = cos(list[j].cj*3.1415926 / 180.0)*cos(list[j].cw*3.1415926 / 180.0);
                y2 = sin(list[j].cj*3.1415926 / 180.0)*cos(list[j].cw*3.1415926 / 180.0);
                z2 = sin(list[j].cw*3.1415926 / 180.0);
            for(int k=j+1;k<40;k++){
                    x3 = cos(list[k].cj*3.1415926 / 180.0)*cos(list[k].cw*3.1415926 / 180.0);
                    y3 = sin(list[k].cj*3.1415926 / 180.0)*cos(list[k].cw*3.1415926 / 180.0);
                    z3 = sin(list[k].cw*3.1415926 / 180.0);
                    jj_1_2 = jj(x1,y1,z1,x2,y2,z2);
                    jj_1_3 = jj(x1,y1,z1,x3,y3,z3);
                    jj_2_3 = jj(x2,y2,z3,x3,y3,z3);
                    if(jj_1_2 <18 && jj_1_3<18 && jj_2_3<18){
                        res = sort_mine(jj_1_2,jj_1_3,jj_2_3);
                        T = res[1]+log10(res[2]+res[0]/res[2])*0.1;
                        fout<<"("<<list[i].num<<","<<list[j].num<<","<<list[k].num<<","<<T<<")"<<endl;
                    }
            }
        }
    }
    cout<<"over"<<endl;
}


float jj(float x1,float y1,float z1,float x2,float y2,float z2){
    float res;
    //res = acos((x1*x2+y1*y2+z1*z2)/((x1*x1+y1*y1+z1*z1)+(x2*x2+y2*y2+z2*z2)-(x1*x2+y1*y2+z1*z2)))/3.1415926*180.0;
    float thita = (x1*x2+y1*y2+z1*z2) / ((sqrt(x1*x1+y1*y1+z1*z1))*(sqrt(x2*x2+y2*y2+z2*z2)));
    res = acos(thita)/3.1415926*180.0;
    return res;
}

float* sort_mine(float x,float y,float z)
{
        float* res = (float*)calloc(3,sizeof(float));
        res[0] = x;
        res[1] = y;
        res[2] = z;
        for(int i=0;i<3;i++){
            for(int j=i+1;j<3;j++){
                if(res[i]>res[j]){
                    swap(res[i],res[j]);
                }
            }
        }
        return res;
}
