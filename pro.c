#include<stdio.h>
#include<string.h>
#include<stdbool.h>
int main()
{
	char a[100],b[100];
	int i,j,k,l,m,n,o=0,p;
	char c[100],d[100],e[100]={0},f[100];
	bool check=0;
	scanf("%s%s",a,b);
	l=strlen(a);
	m=strlen(b);
	n=l;
	k=m;
	for(i=0;l>=0;i++){
		c[i]=a[l-1];
		l--;
	}
	for(j=0;m>=0;j++){
		d[j]=b[m-1];
		m--;
	}
	for(i=k;i<n;i++){
		d[i]='0';
	}
	for(i=0;i<n;i++){
		if(c[i]>=d[i]){
			e[i]+=(c[i]-'0')-(d[i]-'0');
			if(e[i]<0){
				e[i]+=10;
				e[i+1]-=1;
			}
		}
		else{
			e[i]+=(c[i]-'0')+10-(d[i]-'0');
			e[i+1]-=1;
		}
	}
	for(j=0;j<n;j++){
		if(e[j]=='\0'){
			e[j]='0';
		}
	}
	printf("%s\n%s\n",c,d);
	k=strlen(e);
	for(i=k-1;i>=0;i--){
		f[o]=e[i];
		if(f[o]==48){
			f[o]=0;
		}
		o++;
	}
	for(j=0;j<k;j++){
		printf("%d",f[j]);
	}
	return 0;
}
