#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char num[101][60]={0};
char size[101]={0};
char dot_count[101]={0};
char what[100]={0};
void scan();
void print(int);
void sum(int,int);

int main(){
	int i=0,j;
	while(1){
		for(i=0;i<=100;i++){
			for(j=0;j<60;j++)
				num[i][j]=0;
			size[i]=0;
			dot_count[i]=0;
		}
		scan();
		sum(0,1);
		print(100);
	}
}
void scan(){
	int n=0,i,j=0,max;
	char tmp;
	char a[1000];
	_Bool check_dot=0;
	for(i=0;i<1000;i++){
		scanf("%c",&tmp);
		if(tmp=='\n'){
			max=i;
			break;
		}
		a[i]=tmp;
	}
	a[max]='\0';
	for(i=0;i<=max;i++){
		if((a[i]>='0'&&a[i]<='9')&&check_dot==0){
			size[n]++;
			num[n][j++]=a[i]-'0';
		}
		else if(a[i]=='.'){
			j=51;
			check_dot=1;
		}
		else if((a[i]>='0'&&a[i]<='9')&&check_dot){
			dot_count[n]+=1;
			num[n][j++]=a[i]-'0';
		}
		else if(a[i]=='\n')
			break;
		else if(a[i]=='+'||a[i]=='-'||a[i]=='*'||a[i]=='/'){
			n++;
			what[j++]=a[i];
			check_dot=0;
			j=0;
		}
		else if(a[i]==' '){
			check_dot=0;
			j=0;
		}
	}
	for(n=0;n<100;n++){
		for(j=50,i=size[n]-1;i>=0;i--,j--){
			num[n][j]=num[n][i];
			num[n][i]=0;
		}
	}
	if(!strcmp(a,"clear"))
			system("clear");
}
void print(int n){
	int count=3,first,i;
	first=size[n]%3;
	for(i=51-size[n];i<=50;i++){
		first--;
		if(count&&first<0)
			count--;
		printf("%d",num[n][i]);
		if(first==0&&count==3&&i!=50)
			printf(",");
		if(count==0&&i!=50){
			printf(",");
			count=3;
		}
	}
	if(dot_count[n]>0){
		count=0;
		printf(".");
		for(i=51;i<=50+dot_count[n];i++){
			printf("%d",num[n][i]);
			count++;
			if(count%3==0&&count!=dot_count[n]){
				printf(",");
			}
		}
	}
	printf("\n");
}
void sum(int n1,int n2){
	int i;
	if(size[n1]>size[n2])
		size[100]=size[n1];
	else
		size[100]=size[n2];
	for(i=59;i>=0;i--){
		num[100][i]+=num[n1][i]+num[n2][i];
		if(num[100][i]>9){
			num[100][i-1]+=num[100][i]/10;
			num[100][i]=num[100][i]%10;
		}
	}
	if(num[100][50-size[100]]>0)
		size[100]++;
	if(dot_count[n1]>dot_count[n2])
		dot_count[100]=dot_count[n1];
	else
		dot_count[100]=dot_count[n2];
}
