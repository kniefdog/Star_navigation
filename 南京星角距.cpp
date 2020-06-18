#include <stdio.h>
#include <stdlib.h>
#include <math.h>
struct star
{
	int num;//–«∫≈
	double xd; // –«µ»
	double cj;//≥‡æ≠
	double cw;//≥‡Œ≥
}l, list[58];

int main()
{
	FILE*fpr;  FILE*ptr;  FILE*fp;
	double  xd;
	double m, j, p, q;
	int n = 0; int sum, k, geshu = 0;
    double x0, y0, z0, x1, y1, z1, jj;
    int i, x, y, z;
	double cj, cw;
	int ch, sh = 0;
	char w[100];
	int zh[9107]; float b[9107];
	errno_t err;
	for (m = 9; m<360; m = m + 15)
	for (j = 9; j<180; j = j + 15)
	{
		p = m;     q = j;
		if ((err = fopen_s(&fp, "D://mycppspace//star_navigate//jiaojuku//12-1.txt", "rt")) != 0)
		{
			printf("can not open file1.\n");
			exit(0);
		}
		sum = 0;  //sum«¯”Ú–«∏ˆ ˝//
		for (k = 0; k <58; k++)
		{
			fscanf(fp, "%d, %lf, %lf, %lf", &l.num, &l.xd, &l.cj, &l.cw);
			if (((l.cw + 90) <= (q + 15)) && ((l.cw + 90)>(q - 15)))
			{
				if ((l.cj <= (p + 15)) && (l.cj>(p - 15)))
				{
					sum++;
					geshu = sum;
					list[geshu].num = l.num;
					list[geshu].xd = l.xd;
					list[geshu].cj = l.cj;
					list[geshu].cw = l.cw;
				}
			}
		}
		fclose(fp);
		if (geshu>0)
		{
			if ((err = fopen_s(&ptr, "D://mycppspace//star_navigate//jiaojuku//12-1_jj02.txt", "a")) != 0)
			{
				printf("can not open file.\n");
				exit(0);
			}
			for (x = 1; x <= geshu; x++)
			{
				fprintf(ptr, "%d %6.3lf %3.8lf %3.8lf", list[x].num, list[x].xd, list[x].cj, list[x].cw);
				x0 = cos(list[x].cj*3.1415926 / 180.0)*cos(list[x].cw*3.1415926 / 180.0);
				y0 = sin(list[x].cj*3.1415926 / 180.0)*cos(list[x].cw*3.1415926 / 180.0);
				z0 = sin(list[x].cw*3.1415926 / 180.0);
				ch = 0;
				if ((err = fopen_s(&fpr, "D://mycppspace//star_navigate//jiaojuku//10-11.txt", "rt")) != 0)
				{
					printf("can not open file1.\n");
					exit(0);
				}

				for (k = 0; k <58; k++)
				{
					fscanf(fpr, "%d, %lf, %lf, %lf", &l.num, &l.xd, &l.cj, &l.cw);

					if ((l.cw<list[x].cw + 18) && (l.cw>(list[x].cw - 18)))
					{
						x1 = cos(l.cj*3.1415926 / 180.0)*cos(l.cw*3.1415926 / 180.0);
						y1 = sin(l.cj*3.1415926 / 180.0)*cos(l.cw*3.1415926 / 180.0);
						z1 = sin(l.cw*3.1415926 / 180.0);
						jj = acos((x0*x1 + y0*y1 + z0*z1) / (sqrt(x0*x0 + y0*y0 + z0*z0) * sqrt(x1*x1 + y1*y1 + z1*z1))) / 3.1415926*180.0;
						if (jj>0.001&&jj<20)
						{
							ch++;
							sh = ch;
							zh[sh] = l.num;
							b[sh] = jj;
						}

					}
				}
				fclose(fpr);
				if (sh>0)
				{
					fprintf(ptr, " %d", sh);
					for (z = 1; z <= sh; z++)
					{
						fprintf(ptr, " %d %lf", zh[z], b[z]);
					}
				}
				fprintf(ptr, "\n");
			}
			fclose(ptr);
		}
	}
	printf("over");
	getchar();
	return 0;
}
