#ifndef FUN_QUEST_H_INCLUDED
#define FUN_QUEST_H_INCLUDED
#include <math.h>
double* res_q = (double *)calloc(4, sizeof(double));//存放四元数
double* m2qua(const double e00,const double e01,const double e02,
              const double e10,const double e11,const double e12,
              const double e20,const double e21,const double e22)
{
    double q0, q1, q2, q3, qq4;
    if(e00>=e11+e22)
 {
        q1 = 0.5*sqrt(1+e00-e11-e22);  qq4 = 4*q1;
        q0 = (e21-e12)/qq4; q2 = (e01+e10)/qq4; q3 = (e02+e20)/qq4;
 }
    else if(e11>=e00+e22)
 {
        q2 = 0.5*sqrt(1-e00+e11-e22);  qq4 = 4*q2;
        q0 = (e02-e20)/qq4; q1 = (e01-e10)/qq4; q3 = (e12+e21)/qq4;
 }
    else if(e22>=e00+e11)
 {
        q3 = 0.5*sqrt(1-e00-e11+e22);  qq4 = 4*q3;
        q0 = (e10-e01)/qq4; q1 = (e02+e20)/qq4; q2 = (e12+e21)/qq4;
 }
    else
 {
        q0 = 0.5*sqrt(1+e00+e11+e22);  qq4 = 4*q0;
        q1 = (e21-e12)/qq4; q2 = (e02-e20)/qq4; q3 = (e10-e01)/qq4;
 }
 double nq = sqrt(q0*q0+q1*q1+q2*q2+q3*q3);
 q0 /= nq; q1 /= nq; q2 /= nq; q3 /= nq;
 res_q[0] = q0;//这里的q0得出的旋转角度是cos(p/2),p为旋转角
 res_q[1] = q1;
 res_q[2] = q2;
 res_q[3] = q3;
 return res_q;
}

#endif // FUN_QUEST_H_INCLUDED
