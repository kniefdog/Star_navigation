#ifndef STAR_DISTINGUISH_H_INCLUDED
#define STAR_DISTINGUISH_H_INCLUDED
#define RAD2DEG (180/3.14159)
struct star
{
	int num;//�Ǻ�
	double  xd; // �ǵ�
	double cj;//�ྭ
	double cw;//��γ
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
	int kuxh[2][7673]; /*�����ŵ��Ƿ��ϽǾ��������Ǻ͸����ڽǾ������Ǻ�*/
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
	fp = fopen("G://�ǹ�//star_navigate//jiaojuku//10-11_jj02.txt","r");
	if(fp == nullptr){
        printf("can not open file1.\n");
		exit(0);
	}

	for (int i = 0; i < 10000; i++)
	{
		fscanf(fp, "%d%lf%lf%lf%d", &l_jj.num, &l_jj.xd, &l_jj.cj, &l_jj.cw, &l_jj.gs);
		if (l_jj.gs > 0 && !feof(fp))
		{
		XBXS = XBXS + 1;      //������
		list_jj[XBXS].num = l_jj.num;
		list_jj[XBXS].xd = l_jj.xd;
		list_jj[XBXS].cj = l_jj.cj;
		list_jj[XBXS].cw = l_jj.cw;
		list_jj[XBXS].gs = l_jj.gs;

			for (int j = 0; j < l_jj.gs; j++)
			{
				fscanf(fp, "%d %lf", &l_jj.xh, &l_jj.jj);
				list_jj[XBXS].a[j] = l_jj.xh; //���Ǻ�
				list_jj[XBXS].b[j] = l_jj.jj; //�����븱��֮��ĽǾ�
			}

		}
	}
	printf("XBXS:%d\n", XBXS);
    fclose(fp);
    for (int m = 0; m<XPXS; m++)/*m,n��������ѭ����m��n��ֵ�ֱ�Ϊ0��1 0��2 1��2 ,��Ӧjj_1_2,jj_1_3,jj_2_3*/
    {
        for (int n = m + 1; n<XPXS; n++)
        {
            e = -1;
            for (int i = 0; i<XBXS; i++)/*�ֱ��ÿ���и��ǵ����ǽ���ѭ��*/
            for (int j = 0; j<list_jj[i].gs; j++)
            {

                jjca = xpjj[m][n] - list_jj[i].b[j];//ƥ�����ޣ�xpjj���������Ƭ�������õĽǾ�
                if (fabs(jjca)<0.15)
                {
                    cout<<"m:  "<<m<<"  n: "<<n<<endl;
                    e = e + 1;
                    l2[q].kuxh[0][e] = list_jj[i].num;    //�����ǺŴ���
                    cout<<"ʶ��������Ǻ���: "<<list_jj[i].num<<endl;
                    l2[q].kuxh[1][e] = list_jj[i].a[j];   //�����ǺŴ���
                    cout<<"ʶ����ĸ��Ǻ���: "<<list_jj[i].a[j]<<endl;
                    l2[q].xxjj[e] = list_jj[i].b[j];      //���Ǻ͸���֮��ĽǾ�
                }
            }
            l2[q].ppgs = e;  /*ppgs : ƥ�����*/
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
        cout<<"qΪ"<<l<<"ʱ:"<<endl;
        cout<<l2[l].ppgs<<"��ƥ�䵽������"<<endl;
    }


	jjgs = q;/*qһ��Ϊ3*/
	int basic = 0;
	for (int i = 0; i<jjgs; i++)
	for (int m = i + 1; m<jjgs; m++)
	{
		if (l2[i].xpxh[0] == l2[m].xpxh[0])
		{
		    //cout<<"l2["<<i<<"].xpxh[0]��"<<l2[i].xpxh[0]<<"----"<<"l2["<<m<<"].xpxh[0]:"<<l2[m].xpxh[0]<<endl;
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
                            if (l2[g].xpxh[0] == l2[i].xpxh[1] && l2[g].xpxh[1] == l2[m].xpxh[1])//��һ���Ǿ��������ڶ����Ǿ�����һ��
                            {
                                cout<<l2[g].xpxh[0]<<" "<<l2[i].xpxh[1]<<" "<<l2[g].xpxh[1]<<" "<<l2[m].xpxh[1]<<endl;
                                for (int v = 0; v <= l2[g].ppgs; v++)
                                {
                                    cout<<l2[g].kuxh[0][v]<<" "<<l2[i].kuxh[1][j]<<"     "<<l2[g].kuxh[1][v]<<" "<<l2[m].kuxh[1][n]<<endl;
                                    if ((l2[g].kuxh[0][v] == l2[i].kuxh[1][j]) && (l2[g].kuxh[1][v] == l2[m].kuxh[1][n]))//��һ���Ǿั����������Ǿั��һ�����ڶ����Ǿั����������Ǿั��һ��
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
	printf("ƥ�䵽��������:%d\n", basic);
	if(basic>1 || basic ==0){
        printf("ƥ�����\n");
        Ri1[0]=0;Ri1[1]=0;Ri1[2]=0;
        Ri2[0]=0;Ri2[1]=0;Ri2[2]=0;
        Ri3[0]=0;Ri3[1]=0;Ri3[2]=0;
	}
	for (int i = 0; i < basic; i++)

	{
		printf("�����Ƭ�ǣ�%d,%d,%d", c[i].a[0], c[i].a[1], c[i].a[2]);
		printf("�����Ӧ�ǿ��ǣ�%d,%d,%d\n", c[i].b[0], c[i].b[1], c[i].b[2]);

	}
	//printf("over");

	if(basic==1){
        /***** */
        int first_star = c[0].b[0];
        cout<<"��һ���ǵ��Ǻ�: "<<first_star<<endl;
        int second_star = c[0].b[1];
        cout<<"�ڶ����ǵ��Ǻ�: "<<second_star<<endl;
        int third_star = c[0].b[2];
        cout<<"�������ǵ��Ǻ�: "<<third_star<<endl;
        /*���ǿ���Ѱ��ʶ����ĺ���*/
        FILE*ftr_xunxing;
        /*
        if ((err = fopen_s(&ftr_xunxing, "D://mycppspace//star_navigate//jiaojuku//10-11.txt", "rt")) != 0)
        {
            printf("can not open file1.\n");
            exit(0);
        }
        */
        ftr_xunxing = fopen("G://�ǹ�//star_navigate//jiaojuku//10-11.txt","r");
        if(ftr_xunxing == nullptr){
            printf("can not open file1.\n");
            exit(0);
        }
        int sb_num;
        float sb_xd,sb_cj,sb_cw;//sb:ʶ��
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
                cout<<first_star<<"���ǳྭ��"<<first_cj<<"��γ��:"<<first_cw<<endl;
            }
             if(second_star == list3[i].num){
                second_cj = list3[i].cj;
                second_cw = list3[i].cw;
                cout<<second_star<<"���ǳྭ��"<<second_cj<<"��γ��:"<<second_cw<<endl;
            }
             if(third_star == list3[i].num){
                third_cj = list3[i].cj;
                third_cw = list3[i].cw;
                cout<<third_star<<"���ǳྭ��"<<third_cj<<"��γ��:"<<third_cw<<endl;
            }
        }
        /*��ȡ������iϵ�µ�ʸ��*/
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
