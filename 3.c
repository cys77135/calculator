#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char num[100][60]={0};
char size[100]={0};
char dot_count[100]={0};
char what[100]={0};
void scan();
void print(int);
void sum(int,int);
void min(int,int);

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
		for(i=0;i<strlen(what);i++)
			min(i,i+1);
		print(i);
	}
}
void scan(){
	int n=0,i,j=1,k=0,max;
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
			if(a[i-1]=='-')
				num[n][0]=1;
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
		else if((a[i]=='+'||a[i]=='-'||a[i]=='*'||a[i]=='/')&&!(a[i+1]>='0'&&a[i+1]<='9')){
			n++;
			what[k++]=a[i];
			check_dot=0;
			j=1;
			what[k]='\0';
		}
		else if(a[i]==' '){
			check_dot=0;
			j=1;
		}
	}
	if(!strcmp(a,"clear"))
		system("clear");
	else if(!strcmp(a,"end"))
		exit(1);
	for(n=0;n<100;n++){
		for(j=50,i=size[n];i>=1;i--,j--){
			num[n][j]=num[n][i];
			num[n][i]=0;
		}
	}
}
void print(int n){
	int count=3,first,i;
	first=size[n]%3;
	printf("= ");
	if(num[n][0])
		printf("-");
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
	char result[60]={0};
	if(num[n1][0]==num[n2][0]){
		if(num[n2][0])
			result[0]=1;
		if(size[n1]>size[n2])
			size[n2]=size[n1];
		for(i=59;i>0;i--){
			result[i]+=num[n1][i]+num[n2][i];
			if(result[i]>9){
				result[i-1]+=result[i]/10;
				result[i]=result[i]%10;
			}
		}
		if(result[50-size[n2]]>0)
			size[n2]++;
		if(dot_count[n1]>dot_count[n2])
			dot_count[n2]=dot_count[n1];
	}
	for(i=0;i<60;i++)
		num[n2][i]=result[i];
}
void min(int n1,int n2){
	int i,j,k=0;
	char result[60]={0};
	for(i=59;i>=0;i--){
		if(num[n1][i]>=num[n2][i]){
			result[i]+=num[n1][i]-num[n2][i];
			if(result[i]<0){
				result[i]+=10;
				result[i-1]-=1;
			}
		}
		else{
			result[i]+=num[n1][i]+10-num[n2][i];
			result[i-1]-=1;
		}
	}
	for(i=0;i<60;i++){
		if(result[i]>0){
			for(j=i;j<51;j++){
				k++;
			}
			break;
		}
	}
	size[n2]=k;
	for(i=0;i<60;i++){
		num[n2][i]=result[i];
	}
	if(dot_count[n1]>dot_count[n2]){
		dot_count[n2]=dot_count[n1];
	}
}
