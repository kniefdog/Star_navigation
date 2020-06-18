#ifndef STAR_DISTINGUISH_H_INCLUDED
#define STAR_DISTINGUISH_H_INCLUDED
#define RAD2DEG (180/3.14159)
struct star
{
	int num;//星号
	double  xd; // 星等
	double cj;//赤经
	double cw;//赤纬
	int gs,xh;
	double jj;
	int a[1000];
	double b[1000];
}l_jj, list_jj[30000];

struct xinxi
{
	int a[3];
	int b[3];
}c[1000];

struct mail
{
	int xpxh[2];
	int kuxh[2][7673]; /*这里存放的是符合角距误差的主星和副星在角距库里的星号*/
	double xxjj[110];
	double xjjj;
	int ppgs;

}l2[72];

struct star2{
    int num;
    float xd;
    float cj;
    float cw;
}list3[40];

double Ri1[3];
double Ri2[3];
double Ri3[3];

void star_dis()
{
    int   jjgs,q, e;
    double jjca;
    //double pi=3.1415926/180;;
    /*
    double xpjj[3][3] = { { 0,        jj_1_2, jj_1_3 },
                        { 0, 0,         jj_2_3 },
                        { 0, 0, 0 } };
                        */
    double xpjj[3][3] = { { 0,        3.545970, 14.113499 },
                        { 0, 0,         10.571091 },
                        { 0, 0, 0 } };

	q = 0;
	FILE*fp;
	int XBXS=0,XPXS=3;
	//errno_t err;
	/*
	if (
        (err = fopen_s(&fp, "D://mycppspace//star_navigate//jiaojuku//10-11_jj02.txt", "rt")
            ) != 0)
	{
		printf("can not open file1.\n");
		exit(0);
	}
	*/
	fp = fopen("G://星光//star_navigate//jiaojuku//10-11_jj02.txt","r");
	if(fp == nullptr){
        printf("can not open file1.\n");
		exit(0);
	}

	for (int i = 0; i < 10000; i++)
	{
		fscanf(fp, "%d%lf%lf%lf%d", &l_jj.num, &l_jj.xd, &l_jj.cj, &l_jj.cw, &l_jj.gs);
		if (l_jj.gs > 0 && !feof(fp))
		{
		XBXS = XBXS + 1;      //主星数
		list_jj[XBXS].num = l_jj.num;
		list_jj[XBXS].xd = l_jj.xd;
		list_jj[XBXS].cj = l_jj.cj;
		list_jj[XBXS].cw = l_jj.cw;
		list_jj[XBXS].gs = l_jj.gs;

			for (int j = 0; j < l_jj.gs; j++)
			{
				fscanf(fp, "%d %lf", &l_jj.xh, &l_jj.jj);
				list_jj[XBXS].a[j] = l_jj.xh; //副星号
				list_jj[XBXS].b[j] = l_jj.jj; //主星与副星之间的角距
			}

		}
	}
	printf("XBXS:%d\n", XBXS);
    fclose(fp);
    for (int m = 0; m<XPXS; m++)/*m,n进行两层循环，m和n的值分别为0，1 0，2 1，2 ,对应jj_1_2,jj_1_3,jj_2_3*/
    {
        for (int n = m + 1; n<XPXS; n++)
        {
            e = -1;
            for (int i = 0; i<XBXS; i++)/*分别对每个有副星的主星进行循环*/
            for (int j = 0; j<list_jj[i].gs; j++)
            {

                jjca = xpjj[m][n] - list_jj[i].b[j];//匹配门限，xpjj是输入的相片计算所得的角距
                if (fabs(jjca)<0.15)
                {
                    cout<<"m:  "<<m<<"  n: "<<n<<endl;
                    e = e + 1;
                    l2[q].kuxh[0][e] = list_jj[i].num;    //主星星号储存
                    cout<<"识别出的主星号是: "<<list_jj[i].num<<endl;
                    l2[q].kuxh[1][e] = list_jj[i].a[j];   //副星星号储存
                    cout<<"识别出的副星号是: "<<list_jj[i].a[j]<<endl;
                    l2[q].xxjj[e] = list_jj[i].b[j];      //主星和副星之间的角距
                }
            }
            l2[q].ppgs = e;  /*ppgs : 匹配个数*/
            //printf("jjca:%d\n", l2[q].ppgs);
            //for (i = 0; i < e; i++)
            //{
                //printf("z:%d\n", l2[q].kuxh[0][i]);
                //printf("f:%d\n", l2[q].kuxh[1][i]);
            //}
            if (e >= 0)
            {
                l2[q].xpxh[0] = m;
                cout<<"l2["<<q<<"].xpxh[0] :"<<l2[q].xpxh[0]<<endl;
                l2[q].xpxh[1] = n;
                cout<<"l2["<<q<<"].xpxh[1] :"<<l2[q].xpxh[1]<<endl;
                l2[q].xjjj = xpjj[m][n];
                q = q + 1;
            }
        }
    }

    cout<<"e:"<<e<<endl;
    cout<<"q:"<<q<<endl;
    for(int l = 0;l<q;l++){
        cout<<"q为"<<l<<"时:"<<endl;
        cout<<l2[l].ppgs<<"是匹配到的组数"<<endl;
    }


	jjgs = q;/*q一般为3*/
	int basic = 0;
	for (int i = 0; i<jjgs; i++)
	for (int m = i + 1; m<jjgs; m++)
	{
		if (l2[i].xpxh[0] == l2[m].xpxh[0])
		{
		    //cout<<"l2["<<i<<"].xpxh[0]："<<l2[i].xpxh[0]<<"----"<<"l2["<<m<<"].xpxh[0]:"<<l2[m].xpxh[0]<<endl;
			//printf("jjca:%d\n", jjgs);

			for (int j = 0; j <= l2[i].ppgs; j++)
            {
                for (int n = 0; n <= l2[m].ppgs; n++)
                {
                    cout<<"l2[i].kuxh[0][j]: "<<l2[i].kuxh[0][j]<<" l2[m].kuxh[0][n] "<<l2[m].kuxh[0][n]<<endl;
                    if (l2[i].kuxh[0][j] == l2[m].kuxh[0][n])
                    {
                        cout<<"l2[i].kuxh[0][j]: "<<l2[i].kuxh[0][j]<<"----- l2[m].kuxh[0][n] "<<l2[m].kuxh[0][n]<<endl;
                        for (int g = m + 1; g<jjgs; g++)
                        {
                            cout<<l2[g].xpxh[0]<<" "<<l2[i].xpxh[1]<<" "<<l2[g].xpxh[1]<<" "<<l2[m].xpxh[1]<<endl;
                            if (l2[g].xpxh[0] == l2[i].xpxh[1] && l2[g].xpxh[1] == l2[m].xpxh[1])//第一个角距的主星与第二个角距主星一样
                            {
                                cout<<l2[g].xpxh[0]<<" "<<l2[i].xpxh[1]<<" "<<l2[g].xpxh[1]<<" "<<l2[m].xpxh[1]<<endl;
                                for (int v = 0; v <= l2[g].ppgs; v++)
                                {
                                    cout<<l2[g].kuxh[0][v]<<" "<<l2[i].kuxh[1][j]<<"     "<<l2[g].kuxh[1][v]<<" "<<l2[m].kuxh[1][n]<<endl;
                                    if ((l2[g].kuxh[0][v] == l2[i].kuxh[1][j]) && (l2[g].kuxh[1][v] == l2[m].kuxh[1][n]))//第一个角距副星与第三个角距副星一样，第二个角距副星与第三个角距副星一样
                                    {
                                        cout<<l2[g].kuxh[0][v]<<" "<<l2[i].kuxh[1][j]<<"     "<<l2[g].kuxh[1][v]<<" "<<l2[m].kuxh[1][n]<<endl;
                                        c[basic].a[0] = l2[i].xpxh[0];  c[basic].b[0] = l2[i].kuxh[0][j];
                                        c[basic].a[1] = l2[i].xpxh[1];  c[basic].b[1] = l2[i].kuxh[1][j];
                                        c[basic].a[2] = l2[m].xpxh[1];  c[basic].b[2] = l2[m].kuxh[1][n];
                                        basic = basic + 1;
                                    }
                                }
                            }
                        }
                    }
                }
            }
		}
	}
	printf("匹配到的星组数:%d\n", basic);
	if(basic>1 || basic ==0){
        printf("匹配出错\n");
        Ri1[0]=0;Ri1[1]=0;Ri1[2]=0;
        Ri2[0]=0;Ri2[1]=0;Ri2[2]=0;
        Ri3[0]=0;Ri3[1]=0;Ri3[2]=0;
	}
	for (int i = 0; i < basic; i++)

	{
		printf("输出相片星：%d,%d,%d", c[i].a[0], c[i].a[1], c[i].a[2]);
		printf("输出对应星库星：%d,%d,%d\n", c[i].b[0], c[i].b[1], c[i].b[2]);

	}
	//printf("over");

	if(basic==1){
        /***** */
        int first_star = c[0].b[0];
        cout<<"第一个星的星号: "<<first_star<<endl;
        int second_star = c[0].b[1];
        cout<<"第二个星的星号: "<<second_star<<endl;
        int third_star = c[0].b[2];
        cout<<"第三个星的星号: "<<third_star<<endl;
        /*在星库中寻找识别出的恒星*/
        FILE*ftr_xunxing;
        /*
        if ((err = fopen_s(&ftr_xunxing, "D://mycppspace//star_navigate//jiaojuku//10-11.txt", "rt")) != 0)
        {
            printf("can not open file1.\n");
            exit(0);
        }
        */
        ftr_xunxing = fopen("G://星光//star_navigate//jiaojuku//10-11.txt","r");
        if(ftr_xunxing == nullptr){
            printf("can not open file1.\n");
            exit(0);
        }
        int sb_num;
        float sb_xd,sb_cj,sb_cw;//sb:识别
        double first_cj,first_cw;
        double second_cj,second_cw;
        double third_cj,third_cw;

        for(int i=0;i<40;i++){
            fscanf(ftr_xunxing,"%d,%f,%f,%f",&sb_num,&sb_xd,&sb_cj,&sb_cw);
            list3[i].num = sb_num;
            list3[i].xd = sb_xd;
            list3[i].cj = sb_cj;
            list3[i].cw = sb_cw;
        }

        for(int i=0;i<40;i++){
            if(first_star == list3[i].num){
                first_cj = list3[i].cj;
                first_cw = list3[i].cw;
                cout<<first_star<<"号星赤经是"<<first_cj<<"赤纬是:"<<first_cw<<endl;
            }
             if(second_star == list3[i].num){
                second_cj = list3[i].cj;
                second_cw = list3[i].cw;
                cout<<second_star<<"号星赤经是"<<second_cj<<"赤纬是:"<<second_cw<<endl;
            }
             if(third_star == list3[i].num){
                third_cj = list3[i].cj;
                third_cw = list3[i].cw;
                cout<<third_star<<"号星赤经是"<<third_cj<<"赤纬是:"<<third_cw<<endl;
            }
        }
        /*求取恒星在i系下的矢量*/
        Ri1[0] = cos(first_cj/RAD2DEG)*cos(first_cw/RAD2DEG);
        Ri1[1] = sin(first_cj/RAD2DEG)*cos(first_cw/RAD2DEG);
        Ri1[2] = sin(first_cw/RAD2DEG);
        //cout<<first_cj<<" "<<first_cw<<endl;
        cout<<"Ri1: "<<"("<<Ri1[0]<<","<<Ri1[1]<<","<<Ri1[2]<<")"<<endl;

        Ri2[0] = cos(second_cj/RAD2DEG)*cos(second_cw/RAD2DEG);
        Ri2[1] = sin(second_cj/RAD2DEG)*cos(second_cw/RAD2DEG);
        Ri2[2] = sin(second_cw/RAD2DEG);
        //cout<<second_cj<<" "<<second_cw<<endl;
        cout<<"Ri2: "<<"("<<Ri2[0]<<","<<Ri2[1]<<","<<Ri2[2]<<")"<<endl;

        Ri3[0] = cos(third_cj/RAD2DEG)*cos(third_cw/RAD2DEG);
        Ri3[1] = sin(third_cj/RAD2DEG)*cos(third_cw/RAD2DEG);
        Ri3[2] = sin(third_cw/RAD2DEG);
        //cout<<third_cj<<" "<<third_cw<<endl;
        cout<<"Ri3: "<<"("<<Ri3[0]<<","<<Ri3[1]<<","<<Ri3[2]<<")"<<endl;
        }

}


#endif // STAR_DISTINGUISH_H_INCLUDED
