#ifndef INVERSE_H_INCLUDED
#define INVERSE_H_INCLUDED
#include <stdio.h>
#include <malloc.h>
double comput_D(double *p,short int n);      //求矩阵的行列式
double Creat_M(double *p, short int m,short int n,short int k);
void Print( double *p,short int n);     //打印n×n的矩阵
double* res = (double *)calloc(18, sizeof(double));
double* result = res; //result里存放的是转换矩阵的9个元素
void inv( void )
{
   double *buffer,*p;   //定义数组首地址指针变量
   short int row=3,num; //定义矩阵行数row及矩阵元素个数
   short int i,j;
   double determ;      //定义矩阵的行列式
   //求代数余子式
   //printf("\nPlease input the number of rows: ");
   //scanf("%d",&row);
   num=2 * row * row;
   buffer = (double *)calloc(num, sizeof(double));     //分配内存单元
   p=buffer;
   //pp=buffer;
   if(p != NULL)
   {
       /*
       for(i=0;i<row;i++)                   //输入各单元值
       {
           printf("Input the number of %d row ",i+1);
           for(j=0;j<row;j++)
           {
               scanf("%f",p++);
           }
       }
       */
       p[0]=Ri1[0];p[1]=Ri2[0];p[2]=Ri3[0];
       p[3]=Ri1[1];p[4]=Ri2[1];p[5]=Ri3[1];
       p[6]=Ri1[2];p[7]=Ri2[2];p[8]=Ri3[2];
       //p数组中存的是Ri组成的矩阵
   }
   else
   printf( "Can’t allocate memory\n" );
   printf("\nThe original matrix is:\n");
   Print(buffer,row);     //打印该矩阵
   determ=comput_D(buffer,row);     //求整个矩阵的行列式
   p=buffer + row * row;
   //pp=buffer + row * row;
   if (determ != 0)
   {
       for (i=0;i<row; i++)       //求逆矩阵
           for (j=0; j<row; j++)
                  *(p+j*row+i)=Creat_M(buffer,i,j,row)/determ;

       printf("The determinant is %G\n",determ);
       p=buffer + row * row;
       printf("\nThe inverse matrix is:\n");
       Print(p,row);     //打印该矩阵
   }
   else
       printf("The determnant is 0, and there is no inverse matrix!\n");
   //free( buffer );

   /*此时p数组中存储的是逆矩阵
    p[0],p[1],p[2]
    p[3],p[4],p[5]
    p[6],p[7],p[8]
   */
    double *p1 = (double *)calloc(num, sizeof(double));
    p1[0]=Rs1[0];p1[1]=Rs2[0];p1[2]=Rs3[0];
    p1[3]=Rs1[1];p1[4]=Rs2[1];p1[5]=Rs3[1];
    p1[6]=Rs1[2];p1[7]=Rs2[2];p1[8]=Rs3[2];
    printf("%s\n","-----------");
    printf("星光矢量在S系下矩阵为:\n");
    for (int i=1;i<=3;i++)
    {
       for (int j=0; j<3;j++)
           printf("%10G ",p1[(i-1)*3+j]);
       printf("\n");
    }
    printf("%s\n","-----------");
    printf("星光矢量在i系下逆矩阵p为:\n");
    for (int i=1;i<=3;i++)
    {
       for (int j=0; j<3;j++)
           printf("%10G ",p[(i-1)*3+j]);
       printf("\n");
    }
    printf("%s\n","-----------");

    *res++=p1[0]*p[0]+p1[1]*p[3]+p1[2]*p[6];
    *res++=p1[0]*p[1]+p1[1]*p[4]+p1[2]*p[7];
    *res++=p1[0]*p[2]+p1[1]*p[5]+p1[2]*p[8];

    *res++=p1[3]*p[0]+p1[4]*p[3]+p1[5]*p[6];
    *res++=p1[3]*p[1]+p1[4]*p[4]+p1[5]*p[7];
    *res++=p1[3]*p[2]+p1[4]*p[5]+p1[5]*p[8];

    *res++=p1[6]*p[0]+p1[7]*p[3]+p1[8]*p[6];
    *res++=p1[6]*p[1]+p1[7]*p[4]+p1[8]*p[7];
    *res++=p1[6]*p[2]+p1[7]*p[5]+p1[8]*p[8];

    printf("result%s\n","---------------");
    for (int i=1;i<=3;i++)
   {
       for (int j=0; j<3;j++)
           printf("%10G ",result[(i-1)*3+j]);
       printf("\n");
   }

}



//——————————————————–
//功能：求矩阵 n X n 的行列式
//入口参数：矩阵首地址 p；矩阵行数 n
//返回值：矩阵的行列式值
//——————————————————–
double comput_D(double *p,short int n)
{
   short int i,j,m;         //i–row; j–column
   short int lop=0;
   double result=0;
   double mid=1;

   if (n!=1)
   {
       lop=(n==2)?1:n;     //控制求和循环次数，若为2阶，则循环1次，否则为n次
       for(m=0;m<lop;m++)
       {
           mid=1;          //顺序求和
           for(i=0,j=m;i<n;i++,j++)
               mid = mid * ( *(p+i*n+j%n) );
           result+=mid;
       }
       for(m=0;m<lop;m++)
       {
           mid=1;          //逆序相减
           for(i=0,j=n-1-m+n; i<n; i++,j--)
               mid=mid * ( *(p+i*n+j%n));
           result-=mid;
       }
      }
   else result=*p;
   return(result);
}
//—————————————————-
//功能：求k×k矩阵中元素A(mn)的代数余子式
//入口参数：k×k矩阵首地址；元素A的下标m,n; 矩阵行数 k
//返回值： k×k矩阵中元素A(mn)的代数余子式
//—————————————————-
double Creat_M(double *p, short int m,short int n,short int k)
{
   short int len;
   short int i,j;
   double mid_result=0;
   short int quo=1;
   double *p_creat,*p_mid;
   len=(k-1)*(k-1);
   p_creat = (double *)calloc(len, sizeof(double));     //分配内存单元
   p_mid=p_creat;
   for(i=0;i<k;i++)
       for(j=0;j<k;j++)
       {
           if (i!=m && j!=n)
               *p_mid++ =* (p+i*k+j);
       }
   //     Print(p_creat,k-1);
   quo = (m + n) %2==0 ? 1:-1;
   mid_result = (double ) quo * comput_D(p_creat,k-1);
   free(p_creat);
   return(mid_result);
}
//——————————————-
//功能：打印n×n的矩阵
//入口参数：n×n矩阵的首地址；该矩阵的行数 n
//返回值： 无
//——————————————-
void Print( double *p,short int n)
{
   int i,j;
   for (i=1;i<=n;i++)
   {
       for (j=0; j<n;j++)
           printf("%10G ",p[(i-1)*n+j]);
       printf("\n");
   }
   printf("————–\n");
}


#endif // INVERSE_H_INCLUDED
