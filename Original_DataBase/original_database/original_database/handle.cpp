#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <iostream>
#include <fstream>
using namespace std;
int main() 
{
	FILE* fp;
	char a[207]; //����dat�ļ��е�ÿһ����207���ַ�
	double cj, cw, xd; //����ྭ����γ���ǵ�
	char cj1[11];
	char cw1[11];
	char xd1[6];
	fp = fopen("G://�ǹ�//star_navigate//star//tyc201.dat","r"); //��ָ����ԭ�ǿ��ļ�
	fstream fout;
	fout.open("G://�ǹ�//star_navigate//6.0.txt", ios::out | ios::app);  //����õ����ݴ�ŵĵط�
	if (fp == nullptr) {
		printf("can not open file.\n");
		exit(0);
	}
	int count = 1;//�Լ�������Ǳ��
	for (int i = 1; i <= 127000; i++) {
		fread(a, sizeof(char), 207, fp);
		for (int j = 15; j < 26; j++) { //25~35�±�Ϊ�ྭ
			cj1[j - 15] = a[j];
		}
		cj = atof(cj1); //��ȡ�ྭ
		for (int j = 28; j < 39; j++) {
			cw1[j - 28] = a[j];
		}
		cw = atof(cw1); //��ȡ��γ
		for (int j = 110; j < 116; j++) {
			xd1[j - 110] = a[j];
		}
		xd = atof(xd1); //��ȡ�ྭ
		if (xd < 6.0) //��ѡ���ǵ�С��6.0������
		{
			cout << count <<" "<<i<<" "<< cj << " " << cw << " " << xd << endl;
			fout << count << ", " << cj << "," << cw << "," << xd << endl;
			count++;
		}
	}
	return 0;
}