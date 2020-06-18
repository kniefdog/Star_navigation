#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "manage_picture.h"
#include "star_distinguish.h"
#include "fun_quest.h"
#include "inverse.h"
#include "quest2mat.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    FILE* fpr;
    //errno_t err;
    string file_name = "G://星光//star_navigate//quest.txt";
    cout<<"---------"<<endl;
    ofstream fout(file_name,std::ios::app);
    /*
    if ((err = fopen_s(&fpr, "D://mycppspace//star_navigate//quest.txt", "a")) != 0)
	{
		printf("can not open file1.\n");
		exit(0);
	}
	*/
    manage_pic();
    star_dis();
    inv();
    //cout << "Hello world!" << endl;
    cout<<"---------"<<endl;
    double* q = m2qua(result[0],result[1],result[2],
                      result[3],result[4],result[5],
                      result[6],result[7],result[8]);
    cout<<"旋转矩阵对应的四元数为:"<<endl;
    for(int i=0;i<4;i++){
        cout<<res_q[i]<<endl;
    }
    //fprintf(fpr,"%6.6lf,%6.6lf,%6.6lf,%6.6lf\n",res_q[0],res_q[1],res_q[2],res_q[3]);
    fout<<res_q[0]<<","<<res_q[1]<<","<<res_q[2]<<","<<res_q[3]<<endl;
    cout<<"四元数对应的转换矩阵为："<<endl;
    double* mat = q2mat(res_q[0],res_q[1],res_q[2],res_q[3]);
    for (int i=1;i<=3;i++)
    {
       for (int j=0; j<3;j++)
           printf("%10G ",mat[(i-1)*3+j]);
       printf("\n");
    }
    return 0;
}
