#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;
struct star{
    int num;
    float xd;
    float cj;
    float cw;
}list1[510];
int main()
{
	FILE* fp;
	ofstream fout("D://mycppspace//star_navigate//jiaojuku//11-12.txt");
	if ((fp = fopen("D://mycppspace//star_navigate//star//star_database.txt", "rt")) == NULL) {
		printf("´打开文件失败\n");
	}
    int i=0;
    for(int i=0;i<510;i++){
        fscanf(fp,"%d, %f, %f, %f",&list1[i].num,&list1[i].xd,&list1[i].cj,&list1[i].cw);
    }
    for(int i=0;i<510;i++){
        if(list1[i].cj>8.154167 && list1[i].cj<38.7125){
            cout<<list1[i].cj<<endl;
            fout<<list1[i].num<<", "<<list1[i].xd<<", "<<list1[i].cj<<", "<<list1[i].cw<<endl;
        }

    }


    return 0;
}
