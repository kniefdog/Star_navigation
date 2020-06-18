#ifndef MANAGE_PICTURE_H_INCLUDED
#define MANAGE_PICTURE_H_INCLUDED
/*此头文件用于处理读入的相片的像素点和灰度值，得出导航星的Rs以及导航星之间的角距*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <iostream>
#define menxian 150
#define RAD2DEG (180/3.14159)
using namespace std;
struct star_point //该结构体用了存储读入的像素点的信息
{
    int x; //读入的高度值
    int y; //读入的宽度值
    int huidu; //读入的灰度值
    int flag;  //用于判断该像素点是否与别的像素点属于同一个导航星
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
double Rs1[3]; //第1个导航星位于S系下的矢量
double Rs2[3];//第2个导航星位于S系下的矢量
double Rs3[3];//第3个导航星位于S系下的矢量
float jj_1_2;
float jj_1_3;
float jj_2_3;
float T; //存储角距形成的特征量
void manage_pic()
{
    //现在影响比例关系的因素有:
    //角距的大小，像元尺寸的大小，以及图像中心点的坐标

    FILE* fp;//该路径存放的是处理好的相片信息
    //errno_t err;
    int geshu=0;//代表该文件中像素点个数
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
    int x_size,y_size; //相片的宽度与高度
    //CCD每个像素的单元格占4.8微米？？？？？
    double dx=0.0048434244;//每个像素所占的宽度  dx,dy同时变小，角距变小
    double dy=0.0048434244;//每个像素所占的高度
    //double dx=0.176296;//mm
    //double dy=0.176296;//mm
    //double dx=0.006075;//每个像素所占的宽度
    //double dy=0.0048;//每个像素所占的高度
    //double pi=3.1415926/180;
    //double f=19.20; //相机焦距，单位是mm？？？？？？
    double f=35;//f变大，星角距变小
    fscanf(fp,"(%d, %d)",&y_size,&x_size);
    while(!feof(fp)){
        fscanf(fp,"%d %d %d",&star[geshu].y,&star[geshu].x,&star[geshu].huidu);
        //printf("%d %d %d\n",star[geshu].x,star[geshu].y,star[geshu].huidu);
        geshu++;//像素点个数自加
    }

    /*开始根据像素点之间的距离，归类导航星*/
    star[0].flag=Flag;//先规定第一个数据为第一颗星的
    int _hask=0;
    for(int i=1;i<geshu;i++){
        int x_distacne = (star[i].x-star[i-1].x)*(star[i].x-star[i-1].x);//该像素点与前一像素点x坐标的距离
        int y_distance = (star[i].y-star[i-1].y)*(star[i].y-star[i-1].y);
        if(sqrt(x_distacne+y_distance)>20){
            for(int k=0;k<i;k++){
                int x_dis_new = (star[i].x-star[k].x)*(star[i].x-star[k].x);
                int y_dis_new = (star[i].y-star[k].y)*(star[i].y-star[k].y);
                //cout<<"yu"<<k<<"  x:"<<x_dis_new<<" y:"<<y_dis_new<<endl;
                if(sqrt(x_dis_new+y_dis_new)<10)//代表第i点与前面i-1个点中的某一个点距离小于10
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
     //完成像素点数目大小排序
   int num_sort[Flag];//里面存储的是按像素点数目排序的索引号
   BubbleSort(num,Flag,num_sort);
    for(int i=0;i<Flag;i++){
        cout<<num_sort[i]<<" ";
    }
    cout<<endl;
   //求出第一亮星的质心
    int xo=x_size/2; //图片中心点的宽度坐标
    int yo=y_size/2; //图片中心点的高度坐标
    cout<<xo<<endl;
    cout<<yo<<endl;
    float x_0=0;
    float y_0=0;
    int weight_sum0=0;

    ////求出第一亮星的质心
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
     //求出质心相对于相片的方位角
    double fangwei_0;
    fangwei_0 = atan2_mine(  (y_0/weight_sum0-yo)*dy,(x_0/weight_sum0-xo)*dx );
    //fangwei_0 = fangwei_0+180;
    Rs1[0] = cos(fangwei_0/RAD2DEG)*cos(high_0/RAD2DEG);
    Rs1[1] = sin(fangwei_0/RAD2DEG)*cos(high_0/RAD2DEG);
    Rs1[2] = sin(high_0/RAD2DEG);
    float x1_xpzb,y1_xpzb;//x1_xpzb，y1_xpzb分别为相片中恒星的坐标
    x1_xpzb = x_0/weight_sum0-xo;
    y1_xpzb = y_0/weight_sum0-yo;
    //x1_xpzb = x_0/weight_sum0;
    //y1_xpzb = y_0/weight_sum0;
    cout<<"1号星相对于相片的高度角："<<high_0<<",相对于相片的方位角："<<fangwei_0<<endl;
    cout<<"("<<x1_xpzb+xo<<","<<y1_xpzb+yo<<")"<<endl;
    std::cout<<"Rs1: ("<<Rs1[0]<<","<<Rs1[1]<<","<<Rs1[2]<<")"<<std::endl;

    //求出第二亮星的质心
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

    //求出质心相对于相片的方位角
    double fangwei_1;
    fangwei_1 = atan2_mine(  (y_1/weight_sum1-yo)*dy,(x_1/weight_sum1-xo)*dx );
    //求第2亮星相对于s系的坐标即Rs2
    //fangwei_1 = fangwei_1+180;
    Rs2[0] = cos(fangwei_1/RAD2DEG)*cos(high_1/RAD2DEG);
    Rs2[1] = sin(fangwei_1/RAD2DEG)*cos(high_1/RAD2DEG);
    Rs2[2] = sin(high_1/RAD2DEG);
    float x2_xpzb,y2_xpzb;//x2_xpzb，y2_xpzb分别为相片中恒星的坐标
    x2_xpzb = x_1/weight_sum1-xo;
    y2_xpzb = y_1/weight_sum1-yo;
    //x2_xpzb = x_1/weight_sum1;
    //y2_xpzb = y_1/weight_sum1;
    cout<<"2号星相对于相片的高度角："<<high_1<<",相对于相片的方位角："<<fangwei_1<<endl;
    cout<<"("<<x2_xpzb+xo<<","<<y2_xpzb+yo<<")"<<endl;
    cout<<"Rs2: ("<<Rs2[0]<<","<<Rs2[1]<<","<<Rs2[2]<<")"<<endl;

    //求出第三亮星的质心
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
    //求第3亮星相对于s系的坐标即Rs3
    //fangwei_2 = fangwei_2+180;
    Rs3[0] = cos(fangwei_2/RAD2DEG)*cos(high_2/RAD2DEG);
    Rs3[1] = sin(fangwei_2/RAD2DEG)*cos(high_2/RAD2DEG);
    Rs3[2] = sin(high_2/RAD2DEG);
    float x3_xpzb,y3_xpzb;//x3_xpzb，y3_xpzb分别为相片中恒星的坐标
    x3_xpzb = x_2/weight_sum2-xo;
    y3_xpzb = y_2/weight_sum2-yo;
    //x3_xpzb = x_2/weight_sum2;
    //y3_xpzb = y_2/weight_sum2;
    cout<<"3号星相对于相片的高度角："<<high_2<<",相对于相片的方位角："<<fangwei_2<<endl;
    cout<<"("<<x3_xpzb+xo<<","<<y3_xpzb+yo<<")"<<endl;
    cout<<"Rs3: ("<<Rs3[0]<<","<<Rs3[1]<<","<<Rs3[2]<<")"<<endl;

    /*对于444.bmp相片，算出来的一号星（-59.7362，-848.282），二号星（988.664.-807.396），三号星(-38.4294,-576.191)*/
    /*自己修改质心坐标看看对星角距的影响*/
    /*
    x1_xpzb = -59.7362;y1_xpzb =-848.282;
    x2_xpzb = 988.664; y2_xpzb =-807.396;
    x3_xpzb = -38.4294;y3_xpzb =-576.191;
    */
    /*得出相片的坐标点后，开始求取导航星之间的两两角距*/
    //先将相片中恒星的坐标赋值到xpzb结构体数组中
    //xpzb[0].x = x1_xpzb;xpzb[0].y=y1_xpzb;
    //xpzb[1].x = x2_xpzb;xpzb[1].y=y2_xpzb;
    //xpzb[2].x = x3_xpzb;xpzb[2].y=y3_xpzb;

    /*自己仿真时的写法，要除以10，因为当时仿真的时候仿真出的星图每个坐标分量都乘上了10*/
    //xpzb[0].x = x1_xpzb*dx/10;xpzb[0].y=y1_xpzb*dy/10;
    //xpzb[1].x = x2_xpzb*dx/10;xpzb[1].y=y2_xpzb*dy/10;
    //xpzb[2].x = x3_xpzb*dx/10;xpzb[2].y=y3_xpzb*dy/10;

    /*处理真实拍摄星图时的写法*/

    xpzb[0].x = x1_xpzb*dx;xpzb[0].y=y1_xpzb*dy;
    xpzb[1].x = x2_xpzb*dx;xpzb[1].y=y2_xpzb*dy;
    xpzb[2].x = x3_xpzb*dx;xpzb[2].y=y3_xpzb*dy;


    /*求出1号星与2号星之间的角距*/
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
    /*求出1号星与3号星之间的角距*/
    float x3_xpzb_3 = xpzb[2].x,y3_xpzb_3 = xpzb[2].y;
    float K3 = sqrt(x3_xpzb_3*x3_xpzb_3 + y3_xpzb_3*y3_xpzb_3 + f*f);
    x3_xpzb_3 = x3_xpzb_3/K3;
    y3_xpzb_3 = y3_xpzb_3/K3;
    float Z3 = -f/K3;
    jj_1_3 = jj(x1_xpzb_1,y1_xpzb_1,Z1,x3_xpzb_3,y3_xpzb_3,Z3);
    //jj_1_3 = jj(Rs1[0],Rs1[1],Rs1[2],Rs3[0],Rs3[1],Rs3[2]);
    /*求出2号星与3号星之间的角距*/
    jj_2_3 = jj(x2_xpzb_2,y2_xpzb_2,Z2,x3_xpzb_3,y3_xpzb_3,Z3);
    //jj_2_3 = jj(Rs2[0],Rs2[1],Rs2[2],Rs3[0],Rs3[1],Rs3[2]);
    //jj_1_2 = 3.93727;
    //jj_1_3 = 25.0526;
    //jj_2_3 = 28.847;

    printf("一号星与二号星的角距:%10G \n",jj_1_2);
    printf("一号星与三号星的角距:%10G \n",jj_1_3);
    printf("二号星与三号星的角距:%10G \n",jj_2_3);
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
