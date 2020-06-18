#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <iostream>
#include <fstream>
using namespace std;
int main() 
{
	FILE* fp;
	char a[207]; //代表dat文件中的每一行有207个字符
	double cj, cw, xd; //定义赤经，赤纬，星等
	char cj1[11];
	char cw1[11];
	char xd1[6];
	fp = fopen("G://星光//star_navigate//star//tyc201.dat","r"); //打开指定的原星库文件
	fstream fout;
	fout.open("G://星光//star_navigate//6.0.txt", ios::out | ios::app);  //处理好的数据存放的地方
	if (fp == nullptr) {
		printf("can not open file.\n");
		exit(0);
	}
	int count = 1;//自己定义恒星编号
	for (int i = 1; i <= 127000; i++) {
		fread(a, sizeof(char), 207, fp);
		for (int j = 15; j < 26; j++) { //25~35下标为赤经
			cj1[j - 15] = a[j];
		}
		cj = atof(cj1); //获取赤经
		for (int j = 28; j < 39; j++) {
			cw1[j - 28] = a[j];
		}
		cw = atof(cw1); //获取赤纬
		for (int j = 110; j < 116; j++) {
			xd1[j - 110] = a[j];
		}
		xd = atof(xd1); //获取赤经
		if (xd < 6.0) //挑选出星等小于6.0的星星
		{
			cout << count <<" "<<i<<" "<< cj << " " << cw << " " << xd << endl;
			fout << count << ", " << cj << "," << cw << "," << xd << endl;
			count++;
		}
	}
	return 0;
}