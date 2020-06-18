#ifndef MANAGE_PICTURE_H_INCLUDED
#define MANAGE_PICTURE_H_INCLUDED
/*��ͷ�ļ����ڴ���������Ƭ�����ص�ͻҶ�ֵ���ó������ǵ�Rs�Լ�������֮��ĽǾ�*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <iostream>
#define menxian 150
#define RAD2DEG (180/3.14159)
using namespace std;
struct star_point //�ýṹ�����˴洢��������ص����Ϣ
{
    int x; //����ĸ߶�ֵ
    int y; //����Ŀ��ֵ
    int huidu; //����ĻҶ�ֵ
    int flag;  //�����жϸ����ص��Ƿ��������ص�����ͬһ��������
}star[10000];
struct xpzb
{
    float x;
    float y;
}xpzb[3];
void BubbleSort(int  *p, int length, int * ind_diff);
double atan2_mine( double y ,double x);
double jj(double x1,double y1,double z1,double x2,double y2,double z2);
float* sort_mine(float x,float y,float z);
double Rs1[3]; //��1��������λ��Sϵ�µ�ʸ��
double Rs2[3];//��2��������λ��Sϵ�µ�ʸ��
double Rs3[3];//��3��������λ��Sϵ�µ�ʸ��
float jj_1_2;
float jj_1_3;
float jj_2_3;
float T; //�洢�Ǿ��γɵ�������
void manage_pic()
{
    //����Ӱ�������ϵ��������:
    //�Ǿ�Ĵ�С����Ԫ�ߴ�Ĵ�С���Լ�ͼ�����ĵ������

    FILE* fp;//��·����ŵ��Ǵ���õ���Ƭ��Ϣ
    //errno_t err;
    int geshu=0;//������ļ������ص����
    float* res;
    /*
    if ((err = fopen_s(&fp, "G://star//matlab//test.txt", "rt")) != 0)
	{
		printf("111can not open file.\n");
		exit(0);
	}
	*/
	fp = fopen("G://star//matlab//test.txt","r");
	if(fp == nullptr){
        printf("111can not open file.\n");
		exit(0);
	}
	int Flag=1;
    int x_size,y_size; //��Ƭ�Ŀ����߶�
    //CCDÿ�����صĵ�Ԫ��ռ4.8΢�ף���������
    double dx=0.0048434244;//ÿ��������ռ�Ŀ��  dx,dyͬʱ��С���Ǿ��С
    double dy=0.0048434244;//ÿ��������ռ�ĸ߶�
    //double dx=0.176296;//mm
    //double dy=0.176296;//mm
    //double dx=0.006075;//ÿ��������ռ�Ŀ��
    //double dy=0.0048;//ÿ��������ռ�ĸ߶�
    //double pi=3.1415926/180;
    //double f=19.20; //������࣬��λ��mm������������
    double f=35;//f����ǽǾ��С
    fscanf(fp,"(%d, %d)",&y_size,&x_size);
    while(!feof(fp)){
        fscanf(fp,"%d %d %d",&star[geshu].y,&star[geshu].x,&star[geshu].huidu);
        //printf("%d %d %d\n",star[geshu].x,star[geshu].y,star[geshu].huidu);
        geshu++;//���ص�����Լ�
    }

    /*��ʼ�������ص�֮��ľ��룬���ർ����*/
    star[0].flag=Flag;//�ȹ涨��һ������Ϊ��һ���ǵ�
    int _hask=0;
    for(int i=1;i<geshu;i++){
        int x_distacne = (star[i].x-star[i-1].x)*(star[i].x-star[i-1].x);//�����ص���ǰһ���ص�x����ľ���
        int y_distance = (star[i].y-star[i-1].y)*(star[i].y-star[i-1].y);
        if(sqrt(x_distacne+y_distance)>20){
            for(int k=0;k<i;k++){
                int x_dis_new = (star[i].x-star[k].x)*(star[i].x-star[k].x);
                int y_dis_new = (star[i].y-star[k].y)*(star[i].y-star[k].y);
                //cout<<"yu"<<k<<"  x:"<<x_dis_new<<" y:"<<y_dis_new<<endl;
                if(sqrt(x_dis_new+y_dis_new)<10)//�����i����ǰ��i-1�����е�ĳһ�������С��10
                {
                    star[i].flag = star[k].flag;
                    _hask=1;
                    break;
                }
            }
            if(_hask==0)
                {
                    star[i].flag =++Flag;
                }
            _hask=0;
        }
        else{
            star[i].flag=star[i-1].flag;
        }
    }
    for(int i=0;i<geshu;i++){
        cout<<star[i].x<<" "<<star[i].y<<" "<<star[i].huidu<<" "<<star[i].flag<<endl;
    }
    cout<<Flag<<endl;
    int num[Flag];
    int Count = 0;
    while(Count < Flag){
         int num_star=0;
         for(int k=0;k<geshu;k++){
            if(star[k].flag == Count+1)
                num_star++;
        }
        num[Count] = num_star;
        Count++;
    }
    for(int i=0;i<Flag;i++){
        cout<<num[i]<<endl;
    }
     //������ص���Ŀ��С����
   int num_sort[Flag];//����洢���ǰ����ص���Ŀ�����������
   BubbleSort(num,Flag,num_sort);
    for(int i=0;i<Flag;i++){
        cout<<num_sort[i]<<" ";
    }
    cout<<endl;
   //�����һ���ǵ�����
    int xo=x_size/2; //ͼƬ���ĵ�Ŀ������
    int yo=y_size/2; //ͼƬ���ĵ�ĸ߶�����
    cout<<xo<<endl;
    cout<<yo<<endl;
    float x_0=0;
    float y_0=0;
    int weight_sum0=0;

    ////�����һ���ǵ�����
    for(int m=0;m<geshu;m++)
    {
        if(star[m].flag == num_sort[0]+1)
        {
            x_0 = x_0+star[m].x*(star[m].huidu-menxian);
            y_0 = y_0+star[m].y*(star[m].huidu-menxian);
            weight_sum0 =weight_sum0+(star[m].huidu-menxian);
        }
    }
    double x0_abs,y0_abs;
    if((x_0/weight_sum0-xo)*dx>0) x0_abs=(x_0/weight_sum0-xo)*dx;
    else{x0_abs=-(x_0/weight_sum0-xo)*dx;}
    if((y_0/weight_sum0-yo)*dy>0) y0_abs=(y_0/weight_sum0-yo)*dy;
    else{y0_abs=-(y_0/weight_sum0-yo)*dy;}
    double high_0;
    high_0 = atan(f/(sqrt(x0_abs*x0_abs+y0_abs*y0_abs)))*180.0/3.1415926;
     //��������������Ƭ�ķ�λ��
    double fangwei_0;
    fangwei_0 = atan2_mine(  (y_0/weight_sum0-yo)*dy,(x_0/weight_sum0-xo)*dx );
    //fangwei_0 = fangwei_0+180;
    Rs1[0] = cos(fangwei_0/RAD2DEG)*cos(high_0/RAD2DEG);
    Rs1[1] = sin(fangwei_0/RAD2DEG)*cos(high_0/RAD2DEG);
    Rs1[2] = sin(high_0/RAD2DEG);
    float x1_xpzb,y1_xpzb;//x1_xpzb��y1_xpzb�ֱ�Ϊ��Ƭ�к��ǵ�����
    x1_xpzb = x_0/weight_sum0-xo;
    y1_xpzb = y_0/weight_sum0-yo;
    //x1_xpzb = x_0/weight_sum0;
    //y1_xpzb = y_0/weight_sum0;
    cout<<"1�����������Ƭ�ĸ߶Ƚǣ�"<<high_0<<",�������Ƭ�ķ�λ�ǣ�"<<fangwei_0<<endl;
    cout<<"("<<x1_xpzb+xo<<","<<y1_xpzb+yo<<")"<<endl;
    std::cout<<"Rs1: ("<<Rs1[0]<<","<<Rs1[1]<<","<<Rs1[2]<<")"<<std::endl;

    //����ڶ����ǵ�����
    float x_1=0;
    float y_1=0;
    int weight_sum1=0;
    for(int m=0;m<geshu;m++)
    {
        if(star[m].flag == num_sort[1]+1)
        {
            x_1 = x_1+star[m].x*(star[m].huidu-menxian);
            y_1 = y_1+star[m].y*(star[m].huidu-menxian);
            weight_sum1 = weight_sum1 +(star[m].huidu-menxian);
        }
    }

    double x1_abs,y1_abs;
    if((x_1/weight_sum1-xo)*dx>0) x1_abs=(x_1/weight_sum1-xo)*dx;
    else{x1_abs=-(x_1/weight_sum1-xo)*dx;}
    if((y_1/weight_sum1-yo)*dy>0) y1_abs=(y_1/weight_sum1-yo)*dy;
    else{y1_abs=-(y_1/weight_sum1-yo)*dy;}
    double high_1;
    high_1 = atan(f/(sqrt(x1_abs*x1_abs+y1_abs*y1_abs)))*180.0/3.1415926;

    //��������������Ƭ�ķ�λ��
    double fangwei_1;
    fangwei_1 = atan2_mine(  (y_1/weight_sum1-yo)*dy,(x_1/weight_sum1-xo)*dx );
    //���2���������sϵ�����꼴Rs2
    //fangwei_1 = fangwei_1+180;
    Rs2[0] = cos(fangwei_1/RAD2DEG)*cos(high_1/RAD2DEG);
    Rs2[1] = sin(fangwei_1/RAD2DEG)*cos(high_1/RAD2DEG);
    Rs2[2] = sin(high_1/RAD2DEG);
    float x2_xpzb,y2_xpzb;//x2_xpzb��y2_xpzb�ֱ�Ϊ��Ƭ�к��ǵ�����
    x2_xpzb = x_1/weight_sum1-xo;
    y2_xpzb = y_1/weight_sum1-yo;
    //x2_xpzb = x_1/weight_sum1;
    //y2_xpzb = y_1/weight_sum1;
    cout<<"2�����������Ƭ�ĸ߶Ƚǣ�"<<high_1<<",�������Ƭ�ķ�λ�ǣ�"<<fangwei_1<<endl;
    cout<<"("<<x2_xpzb+xo<<","<<y2_xpzb+yo<<")"<<endl;
    cout<<"Rs2: ("<<Rs2[0]<<","<<Rs2[1]<<","<<Rs2[2]<<")"<<endl;

    //����������ǵ�����
    float x_2=0;
    float y_2=0;
    int weight_sum2=0;
    for(int m=0;m<geshu;m++)
    {
        if(star[m].flag == num_sort[2]+1)
        {
            x_2 = x_2+star[m].x*(star[m].huidu-menxian);
            y_2 = y_2+star[m].y*(star[m].huidu-menxian);
            weight_sum2 = weight_sum2+(star[m].huidu-menxian);
        }
    }
    double x2_abs,y2_abs;
    if((x_2/weight_sum2-xo)*dx>0) x2_abs=(x_2/weight_sum2-xo)*dx;
    else{x2_abs=-(x_2/weight_sum2-xo)*dx;}
    if((y_2/weight_sum2-yo)*dy>0) y2_abs=(y_2/weight_sum2-yo)*dy;
    else{y2_abs=-(y_2/weight_sum2-yo)*dy;}
    double high_2;
    high_2 = atan(f/(sqrt(x2_abs*x2_abs+y2_abs*y2_abs)))*180.0/3.1415926;
    double fangwei_2;
    //cout<<(x_2/weight_sum2-xo)*dx<<"  "<<(y_2/weight_sum2-yo)*dy<<endl;
    fangwei_2 = atan2_mine(  (y_2/weight_sum2-yo)*dy,(x_2/weight_sum2-xo)*dx );
    //���3���������sϵ�����꼴Rs3
    //fangwei_2 = fangwei_2+180;
    Rs3[0] = cos(fangwei_2/RAD2DEG)*cos(high_2/RAD2DEG);
    Rs3[1] = sin(fangwei_2/RAD2DEG)*cos(high_2/RAD2DEG);
    Rs3[2] = sin(high_2/RAD2DEG);
    float x3_xpzb,y3_xpzb;//x3_xpzb��y3_xpzb�ֱ�Ϊ��Ƭ�к��ǵ�����
    x3_xpzb = x_2/weight_sum2-xo;
    y3_xpzb = y_2/weight_sum2-yo;
    //x3_xpzb = x_2/weight_sum2;
    //y3_xpzb = y_2/weight_sum2;
    cout<<"3�����������Ƭ�ĸ߶Ƚǣ�"<<high_2<<",�������Ƭ�ķ�λ�ǣ�"<<fangwei_2<<endl;
    cout<<"("<<x3_xpzb+xo<<","<<y3_xpzb+yo<<")"<<endl;
    cout<<"Rs3: ("<<Rs3[0]<<","<<Rs3[1]<<","<<Rs3[2]<<")"<<endl;

    /*����444.bmp��Ƭ���������һ���ǣ�-59.7362��-848.282���������ǣ�988.664.-807.396����������(-38.4294,-576.191)*/
    /*�Լ��޸��������꿴�����ǽǾ��Ӱ��*/
    /*
    x1_xpzb = -59.7362;y1_xpzb =-848.282;
    x2_xpzb = 988.664; y2_xpzb =-807.396;
    x3_xpzb = -38.4294;y3_xpzb =-576.191;
    */
    /*�ó���Ƭ�������󣬿�ʼ��ȡ������֮��������Ǿ�*/
    //�Ƚ���Ƭ�к��ǵ����긳ֵ��xpzb�ṹ��������
    //xpzb[0].x = x1_xpzb;xpzb[0].y=y1_xpzb;
    //xpzb[1].x = x2_xpzb;xpzb[1].y=y2_xpzb;
    //xpzb[2].x = x3_xpzb;xpzb[2].y=y3_xpzb;

    /*�Լ�����ʱ��д����Ҫ����10����Ϊ��ʱ�����ʱ����������ͼÿ�����������������10*/
    //xpzb[0].x = x1_xpzb*dx/10;xpzb[0].y=y1_xpzb*dy/10;
    //xpzb[1].x = x2_xpzb*dx/10;xpzb[1].y=y2_xpzb*dy/10;
    //xpzb[2].x = x3_xpzb*dx/10;xpzb[2].y=y3_xpzb*dy/10;

    /*������ʵ������ͼʱ��д��*/

    xpzb[0].x = x1_xpzb*dx;xpzb[0].y=y1_xpzb*dy;
    xpzb[1].x = x2_xpzb*dx;xpzb[1].y=y2_xpzb*dy;
    xpzb[2].x = x3_xpzb*dx;xpzb[2].y=y3_xpzb*dy;


    /*���1������2����֮��ĽǾ�*/
    float x1_xpzb_1 = xpzb[0].x,y1_xpzb_1 = xpzb[0].y;
    float x2_xpzb_2 = xpzb[1].x,y2_xpzb_2 = xpzb[1].y;
    float K1 = sqrt(x1_xpzb_1*x1_xpzb_1 + y1_xpzb_1*y1_xpzb_1 + f*f);
    float K2 = sqrt(x2_xpzb_2*x2_xpzb_2 + y2_xpzb_2*y2_xpzb_2 + f*f);

    x1_xpzb_1 = x1_xpzb_1/K1;
    y1_xpzb_1 = y1_xpzb_1/K1;
    float Z1 = -f/K1;

    x2_xpzb_2 = x2_xpzb_2/K2;
    y2_xpzb_2 = y2_xpzb_2/K2;
    float Z2 = -f/K2;
    jj_1_2 = jj(x1_xpzb_1,y1_xpzb_1,Z1,x2_xpzb_2,y2_xpzb_2,Z2);
    //jj_1_2 = jj(Rs1[0],Rs1[1],Rs1[2],Rs2[0],Rs2[1],Rs2[2]);
    /*���1������3����֮��ĽǾ�*/
    float x3_xpzb_3 = xpzb[2].x,y3_xpzb_3 = xpzb[2].y;
    float K3 = sqrt(x3_xpzb_3*x3_xpzb_3 + y3_xpzb_3*y3_xpzb_3 + f*f);
    x3_xpzb_3 = x3_xpzb_3/K3;
    y3_xpzb_3 = y3_xpzb_3/K3;
    float Z3 = -f/K3;
    jj_1_3 = jj(x1_xpzb_1,y1_xpzb_1,Z1,x3_xpzb_3,y3_xpzb_3,Z3);
    //jj_1_3 = jj(Rs1[0],Rs1[1],Rs1[2],Rs3[0],Rs3[1],Rs3[2]);
    /*���2������3����֮��ĽǾ�*/
    jj_2_3 = jj(x2_xpzb_2,y2_xpzb_2,Z2,x3_xpzb_3,y3_xpzb_3,Z3);
    //jj_2_3 = jj(Rs2[0],Rs2[1],Rs2[2],Rs3[0],Rs3[1],Rs3[2]);
    //jj_1_2 = 3.93727;
    //jj_1_3 = 25.0526;
    //jj_2_3 = 28.847;

    printf("һ����������ǵĽǾ�:%10G \n",jj_1_2);
    printf("һ�����������ǵĽǾ�:%10G \n",jj_1_3);
    printf("�������������ǵĽǾ�:%10G \n",jj_2_3);
    res = sort_mine(jj_1_2,jj_1_3,jj_2_3);
    T = res[1]+log10(res[2]+res[0]/res[2])*0.1;
    cout<<T<<endl;


}

double jj(double x1,double y1,double z1,double x2,double y2,double z2){
    double res;
    //res = acos((x1*x2+y1*y2+z1*z2)/((x1*x1+y1*y1+z1*z1)+(x2*x2+y2*y2+z2*z2)-(x1*x2+y1*y2+z1*z2)))/3.1415926*180.0;
    double thita = (x1*x2+y1*y2+z1*z2) / ((sqrt(x1*x1+y1*y1+z1*z1))*(sqrt(x2*x2+y2*y2+z2*z2)));
    res = acos(thita)/3.1415926*180.0;
    return res;
}

double atan2_mine( double y ,double x)
{
    if(fabs(x)<1e-8)
    {
        if(y>0) return 90;
        return 270;
    }
    double res =  atan(y/x)*RAD2DEG;
    if(y/x>0)
    {
        if(x<0)return res+180;
        return res;

    }else
    if(x<0)
    {
        return res+180;
    }
    return res;

}


void BubbleSort(int  *p, int length, int * ind_diff)
{
    for (int m = 0; m < length; m++)
	{
		ind_diff[m] = m;
	}

	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length- i - 1; j++)
		{
			if (p[j] < p[j + 1])
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


#endif // MANAGE_PICTURE_H_INCLUDED
