/**************
 *编写主题:
 *编写时间:
*/
#include <iostream>
#include <fstream>
using namespace std;
struct star
{
    int num;
    float xd;
    float cj;
    float cw;
}l,list[1191];

int main()
{
    FILE* fp;
    errno_t err;
    ofstream fout("D://mycppspace//star_navigate//0~60.txt");
	if ((err = fopen_s(&fp, "D://mycppspace//star_navigate//6.0.text", "rt")) != 0)
	{
		printf("can not open file1.\n");
		exit(0);
	}
	while(!feof(fp)){
        fscanf(fp,"%d, %f,%f,%f",&l.num,&l.xd,&l.cj,&l.cw);
       if(l.cw>0 && l.cw<60 && l.xd<4){
        fout<<l.num<<", "<<l.xd<<","<<l.cj<<","<<l.cw<<endl;
       }
	}
    return 0;
}
