#ifndef QUEST2MAT_H_INCLUDED
#define QUEST2MAT_H_INCLUDED
double* res_mat = (double *)calloc(9, sizeof(double));//用于验证的矩阵
double* q2mat(const double q0,const double q1,const double q2,const double q3)
{
 double q11 = q0*q0, q12 = q0*q1, q13 = q0*q2, q14 = q0*q3,
   q22 = q1*q1, q23 = q1*q2, q24 = q1*q3,
   q33 = q2*q2, q34 = q2*q3,
   q44 = q3*q3;

 double e00 = q11+q22-q33-q44,  e01 = 2*(q23-q14),     e02 = 2*(q24+q13),
 e10 = 2*(q23+q14),      e11 = q11-q22+q33-q44, e12 = 2*(q34-q12),
 e20 = 2*(q24-q13),      e21 = 2*(q34+q12),     e22 = q11-q22-q33+q44;
 res_mat[0] = e00;
 res_mat[1] = e01;
 res_mat[2] = e02;
 res_mat[3] = e10;
 res_mat[4] = e11;
 res_mat[5] = e12;
 res_mat[6] = e20;
 res_mat[7] = e21;
 res_mat[8] = e22;
 return res_mat;
}

#endif // QUEST2MAT_H_INCLUDED
