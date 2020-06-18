#ifndef INVERSE_H_INCLUDED
#define INVERSE_H_INCLUDED
#include <stdio.h>
#include <malloc.h>
double comput_D(double *p,short int n);      //����������ʽ
double Creat_M(double *p, short int m,short int n,short int k);
void Print( double *p,short int n);     //��ӡn��n�ľ���
double* res = (double *)calloc(18, sizeof(double));
double* result = res; //result���ŵ���ת�������9��Ԫ��
void inv( void )
{
   double *buffer,*p;   //���������׵�ַָ�����
   short int row=3,num; //�����������row������Ԫ�ظ���
   short int i,j;
   double determ;      //������������ʽ
   //���������ʽ
   //printf("\nPlease input the number of rows: ");
   //scanf("%d",&row);
   num=2 * row * row;
   buffer = (double *)calloc(num, sizeof(double));     //�����ڴ浥Ԫ
   p=buffer;
   //pp=buffer;
   if(p != NULL)
   {
       /*
       for(i=0;i<row;i++)                   //�������Ԫֵ
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
       //p�����д����Ri��ɵľ���
   }
   else
   printf( "Can��t allocate memory\n" );
   printf("\nThe original matrix is:\n");
   Print(buffer,row);     //��ӡ�þ���
   determ=comput_D(buffer,row);     //���������������ʽ
   p=buffer + row * row;
   //pp=buffer + row * row;
   if (determ != 0)
   {
       for (i=0;i<row; i++)       //�������
           for (j=0; j<row; j++)
                  *(p+j*row+i)=Creat_M(buffer,i,j,row)/determ;

       printf("The determinant is %G\n",determ);
       p=buffer + row * row;
       printf("\nThe inverse matrix is:\n");
       Print(p,row);     //��ӡ�þ���
   }
   else
       printf("The determnant is 0, and there is no inverse matrix!\n");
   //free( buffer );

   /*��ʱp�����д洢���������
    p[0],p[1],p[2]
    p[3],p[4],p[5]
    p[6],p[7],p[8]
   */
    double *p1 = (double *)calloc(num, sizeof(double));
    p1[0]=Rs1[0];p1[1]=Rs2[0];p1[2]=Rs3[0];
    p1[3]=Rs1[1];p1[4]=Rs2[1];p1[5]=Rs3[1];
    p1[6]=Rs1[2];p1[7]=Rs2[2];p1[8]=Rs3[2];
    printf("%s\n","-----------");
    printf("�ǹ�ʸ����Sϵ�¾���Ϊ:\n");
    for (int i=1;i<=3;i++)
    {
       for (int j=0; j<3;j++)
           printf("%10G ",p1[(i-1)*3+j]);
       printf("\n");
    }
    printf("%s\n","-----------");
    printf("�ǹ�ʸ����iϵ�������pΪ:\n");
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



//�������������������������������������C
//���ܣ������ n X n ������ʽ
//��ڲ����������׵�ַ p���������� n
//����ֵ�����������ʽֵ
//�������������������������������������C
double comput_D(double *p,short int n)
{
   short int i,j,m;         //i�Crow; j�Ccolumn
   short int lop=0;
   double result=0;
   double mid=1;

   if (n!=1)
   {
       lop=(n==2)?1:n;     //�������ѭ����������Ϊ2�ף���ѭ��1�Σ�����Ϊn��
       for(m=0;m<lop;m++)
       {
           mid=1;          //˳�����
           for(i=0,j=m;i<n;i++,j++)
               mid = mid * ( *(p+i*n+j%n) );
           result+=mid;
       }
       for(m=0;m<lop;m++)
       {
           mid=1;          //�������
           for(i=0,j=n-1-m+n; i<n; i++,j--)
               mid=mid * ( *(p+i*n+j%n));
           result-=mid;
       }
      }
   else result=*p;
   return(result);
}
//����������������������������������-
//���ܣ���k��k������Ԫ��A(mn)�Ĵ�������ʽ
//��ڲ�����k��k�����׵�ַ��Ԫ��A���±�m,n; �������� k
//����ֵ�� k��k������Ԫ��A(mn)�Ĵ�������ʽ
//����������������������������������-
double Creat_M(double *p, short int m,short int n,short int k)
{
   short int len;
   short int i,j;
   double mid_result=0;
   short int quo=1;
   double *p_creat,*p_mid;
   len=(k-1)*(k-1);
   p_creat = (double *)calloc(len, sizeof(double));     //�����ڴ浥Ԫ
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
//����������������������������-
//���ܣ���ӡn��n�ľ���
//��ڲ�����n��n������׵�ַ���þ�������� n
//����ֵ�� ��
//����������������������������-
void Print( double *p,short int n)
{
   int i,j;
   for (i=1;i<=n;i++)
   {
       for (j=0; j<n;j++)
           printf("%10G ",p[(i-1)*n+j]);
       printf("\n");
   }
   printf("���������C\n");
}


#endif // INVERSE_H_INCLUDED
