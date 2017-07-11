#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUF 1024

int num;
char name[BUF],nation[BUF],product[BUF],dist[BUF],class[BUF],genre[BUF],director[BUF];
int start,people,screen,play;
char url[BUF]="http://movie.naver.com/movie/search/result.nhn?";
char query[BUF*2];
FILE* fp;

void clr_query(void)
{
	int i;
	for(i=0; i<BUF*2; i++)
			query[i]=0;
}
void clear(void)
{
	int i;
	for(i=0; i<BUF; i++)
	{
		name[i]=0;
		nation[i]=0;
		product[i]=0;
		dist[i]=0;
		class[i]=0;
		genre[i]=0;
		director[i]=0;
	}
}
void readcol(char temp[])
{
	fscanf(fp,"\"");
	int cnt = 0;
	while(1)
	{
		char ch;
		fscanf(fp,"%c",&ch);
		if(ch=='\"')
			break;
		if(ch==' ')
		{
			temp[cnt++]='%';
			temp[cnt++]='2';
			temp[cnt++]='0';
		}
		else
			temp[cnt++]=ch;
	}
	fscanf(fp,",");
}
void readline()
{
	clear();
	fscanf(fp,"\"");
	fscanf(fp,"%d",&num);
	fscanf(fp,"\",");
	readcol(name);
	fscanf(fp,"%d,",&start);
	readcol(nation);
	readcol(product);
	readcol(dist);
	readcol(class);
	readcol(genre);
	readcol(director);
	fscanf(fp,"%d,%d,%d\n",&people,&screen,&play);
}

int main(void)
{
	int i;
	fp = fopen("alldata.csv","r");
	
	fscanf(fp,"\"\",\"name\",\"start\",\"nation\",\"product\",\"dist\",\"class\",\"genre\",\"director\",\"people\",\"screen\",\"play\"\n");
	
	for(i=1; i<=513; i++)
	{
		readline();
		sprintf(query,"wget \"%ssection=all&ie=utf8&query=%s\" -O %03d.html -q",url,name,num);
		printf("%s\n",query);
		system(query);
		clr_query();

		sprintf(query,"iconv -c -f EUC-KR -t UTF-8 %03d.html > %03dconv.html",num,num);
		system(query);
		clr_query();

		sprintf(query,"python find.py %03dconv.html > output%03d.txt",num,num);
		system(query);
		clr_query();

		sprintf(query,"python find.py %03dconv.html >> namelist.txt",num);
		system(query);
		clr_query();
        
        system("rm -f *.html");
        system("rm -f output*");
	}
	fclose(fp);
	return 0;
}
