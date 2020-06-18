#ifndef STAR_DISTINGUISH_1_H_INCLUDED
#define STAR_DISTINGUISH_1_H_INCLUDED

#include <iostream>
using namespace std;
struct njjj
{
    int num1;
    int num2;
    int num3;
    float T;
}ll,list1[52589];

struct star1
{
    int num;
    float xd;
    float cj;
    float cw;
}list2[510];

double Ri1[3];
double Ri2[3];
double Ri3[3];

void BubbleSort(int  *p, int length, float * ind_diff);
void star_dis()
{
    FILE*ft;
	errno_t err;
	int ppzs=0;//匹配组数
	int ppnum = 0;//匹配上的数组号
	if ((err = fopen_s(&ft, "D://mycppspace//star_navigate//jiaojuku//10-11_jj.txt", "rt")) != 0)
	{
		printf("can not open file1.\n");
		exit(0);
	}
	for(int i=0;i<52589;i++){
        fscanf(ft,"(%d,%d,%d,%f)\n",&list1[i].num1,&list1[i].num2,&list1[i].num3,&list1[i].T);
	}
	for(int j=0;j<52589;j++){
        if( fabs(list1[j].T - T)<0.0001 ){
            ppzs++;
            cout<<list1[j].num1<<" "<<list1[j].num2<<" "<<list1[j].num3<<endl;
            ppnum = j;
        }

	}
    cout<<"ppzs:"<<ppzs<<endl;
	if(ppzs == 0 || ppzs>1){
        printf("匹配出错\n");
        Ri1[0]=0;Ri1[1]=0;Ri1[2]=0;
        Ri2[0]=0;Ri2[1]=0;Ri2[2]=0;
        Ri3[0]=0;Ri3[1]=0;Ri3[2]=0;
	}
	if(ppzs == 1){
        printf("匹配成功\n");
        /*在星库中寻找识别出的恒星*/
        FILE*ftr_xunxing;
        if ((err = fopen_s(&ftr_xunxing, "D://mycppspace//star_navigate//star//star_database.txt", "rt")) != 0)
        {
            printf("can not open file1.\n");
            exit(0);
        }
        int sb_num;
        float sb_xd,sb_cj,sb_cw;
        for(int i=0;i<510;i++){
            fscanf(ftr_xunxing,"%d,%f,%f,%f",&sb_num,&sb_xd,&sb_cj,&sb_cw);
            list2[i].num = sb_num;
            list2[i].xd = sb_xd;
            list2[i].cj = sb_cj;
            list2[i].cw = sb_cw;
        }
        float xd1,xd2,xd3;//代表识别出的三个星的星等
        int first_star = list1[ppnum].num1;
        cout<<"第一个星的星号: "<<first_star<<endl;

        int second_star = list1[ppnum].num2;
        cout<<"第二个星的星号: "<<second_star<<endl;

        int third_star = list1[ppnum].num3;
        cout<<"第三个星的星号: "<<third_star<<endl;
        for(int i=0;i<510;i++){
            if(first_star == list2[i].num)  xd1 = list2[i].xd;
            if(second_star == list2[i].num) xd2 = list2[i].xd;
            if(third_star == list2[i].num)  xd3 = list2[i].xd;
        }
        cout<<"第1个星的星等: "<<xd1<<endl;
        cout<<"第2个星的星等: "<<xd2<<endl;
        cout<<"第3个星的星等: "<<xd3<<endl;

        int p[3];
        p[0]=first_star,p[1]=second_star,p[2]=third_star; //存放还为按照星等排序的星号
        float d[3];
        d[0]=xd1;d[1]=xd2;d[2]=xd3; //存放还为按照星等排序的星等大小


        BubbleSort(p,3,d); // 按照星等排序，最亮的排在前面

        double first_cj,first_cw;
        double second_cj,second_cw;
        double third_cj,third_cw;

        for(int i=0;i<510;i++){
            if(p[0] == list2[i].num)
                {first_cj =  list2[i].cj;first_cw =  list2[i].cw;}
            if(p[1] == list2[i].num)
                {second_cj =  list2[i].cj;second_cw =  list2[i].cw;}
            if(p[2] == list2[i].num)
                {third_cj =  list2[i].cj;third_cw =  list2[i].cw;}
        }


        /*求取恒星在i系下的矢量*/
        Ri1[0] = cos(first_cj/RAD2DEG)*cos(first_cw/RAD2DEG);
        Ri1[1] = sin(first_cj/RAD2DEG)*cos(first_cw/RAD2DEG);
        Ri1[2] = sin(first_cw/RAD2DEG);
        cout<<first_cj<<" "<<first_cw<<endl;
        cout<<"Ri1: "<<"("<<Ri1[0]<<","<<Ri1[1]<<","<<Ri1[2]<<")"<<endl;

        Ri2[0] = cos(second_cj/RAD2DEG)*cos(second_cw/RAD2DEG);
        Ri2[1] = sin(second_cj/RAD2DEG)*cos(second_cw/RAD2DEG);
        Ri2[2] = sin(second_cw/RAD2DEG);
        cout<<second_cj<<" "<<second_cw<<endl;
        cout<<"Ri2: "<<"("<<Ri2[0]<<","<<Ri2[1]<<","<<Ri2[2]<<")"<<endl;

        Ri3[0] = cos(third_cj/RAD2DEG)*cos(third_cw/RAD2DEG);
        Ri3[1] = sin(third_cj/RAD2DEG)*cos(third_cw/RAD2DEG);
        Ri3[2] = sin(third_cw/RAD2DEG);
        cout<<third_cj<<" "<<third_cw<<endl;
        cout<<"Ri3: "<<"("<<Ri3[0]<<","<<Ri3[1]<<","<<Ri3[2]<<")"<<endl;
        }



}

void BubbleSort(int  *p, int length, float * ind_diff)
{
    for (int m = 0; m < length; m++)
	{
		ind_diff[m] = m;
	}

	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length- i - 1; j++)
		{
			if (p[j] > p[j + 1])
			{
				float temp = p[j];
				p[j] = p[j + 1];
				p[j + 1] = temp;

				int ind_temp = ind_diff[j];
				ind_diff[j] = ind_diff[j + 1];
				ind_diff[j + 1] = ind_temp;
			}
		}
	}
}
#endif // STAR_DISTINGUISH_1_H_INCLUDED
