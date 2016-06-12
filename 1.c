#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char num[100][60]={0};                      // 계산할 숫자
char size[100]={0};                         // 숫자의 자릿수
char dot_count[100]={0};                    // 숫자의 소수점 자릿수
char what[100]={0};                         // 연산 기호
char re[60]={0};                            // 나머지 
char vari[10]={0};                          // 변수
char varn[10][62]={0};                      // 변수 숫자
int v=0,ck;                                 
_Bool check_var;
int scan();                                 // 입력 함수
void print(int);                            // 출력 함수
void sum(int,int);                          // 더하기 함수
void min(int,int);                          // 빼기 함수
void mul(int,int);                          // 곱하기 함수
void di(int,int);                           // 나누기 함수
void rem(int,int);                          // 나머지 함수
int nu(int,int);                            // 사이즈 비교 함수
void copy(int,int);                         // 복사 함수
void put(int,int);                          // 변수 숫자 넣는 함수
void var();                                 // VAR함수
char alpha(char);                           // 대소문자 정리 함수
int call(char,int);                         // 변수 숫자 호출 함수
void cal();                                 // 계산 함수
void load();                                // load 함수
void save();                                // save 함수

int main(){
	int i=0,j;
	printf("Start....\n");
	while(1){
		for(i=0;i<=100;i++){                // 배열 초기화
			for(j=0;j<60;j++)
				num[i][j]=0;
			size[i]=0;
			dot_count[i]=0;
			what[i]=0;
		}
		if(scan()){                         
			if(!check_var)
				cal();
			print(strlen(what));       // 부호 개수 번째 숫자 출력       
		}
	}
}
void cal(){
	int i=0,j,count=0;
	for(i=0;i<strlen(what);i++){             // 곱하기 나누기 나머지 먼저 계산
		if(what[i]=='*')
			mul(i,i+1);
		if(what[i]=='/')
			di(i,i+1);
		if(what[i]=='%')
			rem(i,i+1);
	}
	for(i=0;i<strlen(what);i++){               // 복합 연산 
		if(what[i]=='+'||what[i]=='-'){
			j=i+1;
			count=0;
			while(j<strlen(what)){
				if(what[j]=='*'||what[j]=='/'||what[j]=='%'){
					count++;
					j++;
				}
				else
					break;
			}
			if(what[i]=='+')
				sum(i,i+1+count);
			else if(what[i]=='-')
				min(i,i+1+count);
		}
	}
}
int scan(){
	int n=0,i,j=1,k=0,l=0,max;
	char tmp;
	char a[1000]={0},check[100]={0};
	_Bool check_dot=0,check_error=0;
	check_var=0;
	printf("(input) ");
	for(i=0;i<1000;i++){                     // 1000개 글자까지 입력 가능
		scanf("%c",&tmp);
		if(tmp=='\n'){                   // 몇자리인지 max에 저장
			max=i;
			break;
		}
		a[i]=tmp;
	}
	a[max]='\0';
	if(!strcmp(a,"clear")){                  // clear 입력시 clear 실행
		system("clear");
		return 0;
	}
	if(!strcmp(a,"VAR")){                   // VAR 입력시 var 함수 실행
		var();
		return 0;
	}
	if(!strcmp(a,"save")){                  // save 입력시 save 함수 실행
		save();
		return 0;
	}
	if(!strcmp(a,"load")){                  // load 입력시 load 함수 실행
		load();
		return 0;
	}
	if(!strcmp(a,"end"))                    // end 입력시 프로그램 종료
		exit(1);
	for(i=0;i<=max;i++){                    // 숫자는 숫자에 저장
		if((a[i]>='0'&&a[i]<='9')&&check_dot==0){
			if(a[i-1]=='-')
				num[n][0]=1;
			size[n]++;
			num[n][j++]=a[i]-'0';
		}
		   else if(check_dot&&a[i]=='.') {     // . 두 개 이상일 때 에러
            		printf("= error\n");
        		 return 0;
        	}
		else if(a[i]=='.'){           // 소수점 확인 소수점 아래 숫자로 위치 변경
			j=51;
			check_dot=1;
		}
		else if((a[i]>='0'&&a[i]<='9')&&check_dot){     // 소수점 아래 숫자 저장
			dot_count[n]+=1;
			num[n][j++]=a[i]-'0';
		}
		else if((a[i]=='+'||a[i]=='-'||a[i]=='*'||a[i]=='/'||a[i]=='%')&&!(a[i+1]>='0'&&a[i+1]<='9')){ 
			n++;                   // 다음 숫자로 변경
			what[k++]=a[i];        // 연산 기호 저장
			check_dot=0;
			j=1;
			what[k]='\0';
		}
		else if(a[i]==' '){                 // 자리수와 소수점 초기화
			check_dot=0;
			j=1;
		}
		else if((a[i]>='a'&&a[i]<='z')||(a[i]>='A'&&a[i]<='Z')){      // 변수 확인
			if((a[i+1]==' '&&a[i+2]=='=')){                       // 변수 저장 
				for(l=0;l<10;l++)                             // 기존에 있던 변수인지 확인
					if(a[i]==vari[l]||vari[l]==0){
						v=l;
						break;
					}
				if(l==10)
					v=0;
				if(ck<10)                                    // 비어있는 변수 배열에 저장
				vari[v]=a[i];
				check_var=1;
			}
			else{                                                // 변수 호출
				if(call(a[i],n))
					check[n]=1;
				else{
					printf("= undefined\n");
					return 0;
				}
			}
			if(ck>=10){
				printf("= error\n");
				return 0;
			}
			ck++;
		}
		else if((a[i]=='(')||(a[i]==')')) {                         // (,) 입력시 에러
			printf("= error\n");
			return 0;
		} 
		else if(a[i]=='\0')  {                                     // 엔터 시 입력 중지
			break;
		}
		else { 
			printf("= error\n");                               // 이외에 것 에러
			return 0;
		}
	}

	for(n=0;n<100;n++){                                                // 계산을 위한 숫자 배열 변경
		if(!check[n]){
			for(j=50,i=size[n];i>=1;i--,j--){
				num[n][j]=num[n][i];
				num[n][i]=0;
			}
		}
	}
	if(check_var){                                                     // 변수 입력시 계산 
		cal();
		put(v,strlen(what));
	}
	return 1;
}
void print(int n){
	int count=3,first,i;
	first=size[n]%3;
	printf("= ");
	if(num[n][0])                                   // 단항 -부호 
		printf("-");
	for(i=51-size[n];i<=50;i++){                    // 소수점 앞자리 , 출력
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
	if(dot_count[n]>0){                             // 소수점 뒷자리 ,  출력
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
	if(num[n1][0]==num[n2][0]){                           // 두 숫자의 부호가 같을시 계산
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
		if(result[50-size[n2]]>0)                   // 자리수 올라갔을때
			size[n2]++;
		if(dot_count[n1]>dot_count[n2])
			dot_count[n2]=dot_count[n1];
		for(i=0;i<60;i++)
			num[n2][i]=result[i];
	}
	else if(num[n2][0]){                                // 두번째 숫자만 음수일때 -로
		num[n2][0]=0;
		min(n1,n2);
	}
	else if(num[n1][0]){                                // 첫번째 숫자만 음수일때 -로
		num[n1][0]=0;
		min(n2,n1);
		copy(n1,n2);
	}
}
void min(int n1,int n2){
	int i,j,k=0,l=0;
	char result[60]={0},ex[60]={0};
	if(!num[n1][0]&&!num[n2][0]){                       // 두 수 모두 양수일 때
		if(size[n2]>=size[n1]){                     // 두번째 수가 더 클 때 바꾸기
			if(size[n2]==size[n1]){
				for(i=1;i<60;i++){
					if(num[n1][i]==num[n2][i]){
						if(num[n1][i+1]<num[n2][i+1]){
							num[n2][0]=1;
							for(j=1;j<60;j++){
								ex[j]=num[n1][j];
								num[n1][j]=num[n2][j];
								num[n2][j]=ex[j];
							}
						}
					}
				}
			}
			else{
				num[n2][0]=1;
				for(i=1;i<60;i++){
					ex[i]=num[n1][i];
					num[n1][i]=num[n2][i];
					num[n2][i]=ex[i];
				}
			}
		}
		for(i=59;i>0;i--){
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
		for(i=1;i<60;i++){
			if(result[i]>0){
				for(j=i;j<51;j++){
					k++;
				}
				break;
			}
		}
		for(i=0;i<60;i++){
			if(num[n1][i]==num[n2][i]){
				l++;
			}
		}
		if(l==60){
			k=1;
		}
		size[n2]=k;
		for(i=1;i<60;i++){
			num[n2][i]=result[i];
		}
		if(dot_count[n1]>dot_count[n2]){
			dot_count[n2]=dot_count[n1];
		}
	}
	else if(num[n1][0]&&!num[n2][0]){              //양수 - 음수 계산할 때 더하기로
		num[n2][0]=1;
		sum(n1,n2);
	}
	else if(!num[n1][0]&&num[n2][0]){              //음수 - 양수 계산할 때 더하기로
		num[n2][0]=0;
		sum(n1,n2);
	}
	else if(num[n1][0]&&num[n2][0]){               //음수 - 음수 계산할 때 부호 없애고 빼기
		num[n1][0]=0;
		num[n2][0]=0;
		min(n2,n1);
		copy(n1,n2);
	}
}
void mul(int n1,int n2)
{
	int a,i,j,b=59,c1=0,t;
	char result[200]={0};
	if(num[n1][0]!=num[n2][0])
		num[n2][0]=1;
	else
		num[n2][0]=0;
	for(i=59;i>0;i--){
		for(j=59;j>0;j--){
			if(num[n1][i] && num[n2][j])
				result[118-i-j+1]+=(result[118-i-j]+num[n1][i]*num[n2][j])/10;
			if(num[n1][i] && num[n2][j])
				result[118-i-j]=(result[118-i-j]+num[n1][i]*num[n2][j])%10;
		}
	}
	for(a=size[n1]+size[n2];a>=0;--a)                // 자리수 확인
	{
		if(result[18+a]){
			size[n2]=a+1;
			break;
		}
		else if(a==0)
			size[n2]=1;
	}
	for(a=9;a<67;++a,--b){                          // 소수점 아래 자리 확인
		if(c1==0 && b > 50 && result[a]!=0){
			c1++;
			dot_count[n2] = b-50;
		}
		else if(c1 == 0 && b <= 50)
			dot_count[n2] = 0;
		num[n2][b]=result[a];
	}
}
void di(int n1,int n2)
{
	int a,al=50;
	char result[60]={0},ex[60]={0},cou=0;
	if(num[n1][0]!=num[n2][0])
		num[n2][0]=1;
	else
		num[n2][0]=0;
	for(a=1;a<60;a++)
		ex[a]=num[n2][a];                       // 나누는 수 저장
	while(nu(n1,n2)==2){                            // 나눠지는 수가 클 때 나누는 수 자리수 맞추기
		for(a= 1;a<=59;++a)
			num[n2][a]=num[n2][a+1];
		num[n2][59]=0;
		--al;
		for(a=1;a<60;a++)
			ex[a]=num[n2][a];
	}
	while(nu(n1,n2)==1){                           // 나눠지는 수보다 나누는 수가 클때 자리수 맞추기
		for(a=59;a>1;--a)
			num[n2][a]=num[n2][a-1];
		++al;
		num[n2][1]=0;
		for(a=1;a<60;a++)
			ex[a]=num[n2][a];
	}
	if(nu(n1,n2)==0)                               // 두 수가 같으면 1
		result[al]=1;
	while(al<=59&&nu(n1,n2)!=0){                   // 나눠지는 수가 더 클 때까지 빼기
		while(nu(n1,n2)==2||nu(n1,n2)==0){
			min(n1,n2);
			for(a=0;a<60;++a)              // 나눠지는  수 교체
				num[n1][a]=num[n2][a];
			for(a=0;a<60;a++)              // 나누는 수 교체
				num[n2][a]=ex[a];
			cou++;
		}
		result[al]=cou;
		cou=0;
		if(al==50){                            // 몫이 정수 첫째자리일 때 나머지 저장
			for(a=0;a<=60;++a)
				re[a]=num[n1][a];
		}
		if(nu(n1,n2)==0) break;                // 0이 되면 종료
		for(a=59;a>0;--a)                      // 나누는 수 자리수 맞추기
			num[n2][a]=num[n2][a-1];
		++al;
		num[n2][1]=0;
		for(a=1;a<60;a++)
			ex[a]=num[n2][a];
	}
	for(a=1;a<60;a++)
		num[n2][a]=result[a];
	for(a=1;a<=50;a++){
		if(result[a]){
			size[n2]=50-a+1;
			break;
		}
		if(a==50)
			size[n2]=1;
	}
	for(a=59;a>50;--a){
		if(result[a]){
			dot_count[n2]=a-50;
			break;
		}
		else if(a==51)
			dot_count[n2]=0;
	}
}
void rem(int n1,int n2)
{
	int a;
	if(nu(n1,n2)==2){                    // 나눠지는 수가 더 클때
		di(n1,n2);                   // 나누기 함수 실행 후 나머지 받아오기
		for(a=0;a<=60;a++)
			num[n2][a]=re[a];
		for(a=1;a<=50;a++){
			if(re[a]){
				size[n2]=50-a+1;
				break;
			}
			if(a==50)
				size[n2]=1;
		}
		for(a=59;a>50;--a){
			if(re[a]){
				dot_count[n2]=a-50;
				break;
			}
			else if(a==51)
				dot_count[n2]=0;
		}
	}
	else if(nu(n1,n2)==0){                  // 두 수 같으면 0
		for(a=0;a<60;++a)
			num[n2][a]=0;
	}
	else if(nu(n1,n2)==1){                  // 나누는 수 가 더 크면 나눠지는 수 그대로
		for(a=0;a<60;a++)
			num[n2][a]=num[n1][a];
		size[n2]=size[n1];
	}
}
int nu(int n1,int n2)                          // 첫번째 수가 더크면 2 작으면 1 같으면 0
{
	int i;
	for(i=0;i<60;i++){
		if(num[n1][i]>num[n2][i]){
			return 2;
			break;
		}
		if(num[n1][i]<num[n2][i]){
			return 1;
			break;
		}
	}
	return 0;
}
void copy(int n1,int n2){                     // 두 숫자 바꿀 때 복사
	int i=0;
	for(i=0;i<60;i++)
		num[n2][i]=num[n1][i];
	size[n2]=size[n1];
	dot_count[n2]=dot_count[n1];
}
void put(int v,int n){                        // 59까진 일반 숫자배열 60은 자리수 61은 소수점 자리수
	int i;
	for(i=0;i<60;i++)
		varn[v][i]=num[n][i];
	varn[v][60]=size[n];
	varn[v][61]=dot_count[n];
}
void var(){                                   // 입력된 순서대로 변수와 그 숫자 출력
	int i,j,a,u=0;
	size[0]=0;
	dot_count[0]=0;
	for(i=0;i<10;i++){
		if(vari[i]){
			printf("%c ",vari[i]);
			for(j=0;j<60;j++)
				num[0][j]=varn[i][j];
			size[0] = varn[i][60];
			dot_count[0] = varn[i][61];
			print(0);
		} 
		if(vari[0]==0){
			printf("정의된 변수가 없습니다.\n");
			break;
		}


	}
}

char alpha(char a){
	if(a>='a'&&a<='z')
		return a-('a'-'A');
	else
		return a;
}
int call(char a,int n){                       // 변수 호출 할 때 계산을 위한 숫자배열에 넣기
	int i,j;
	for(i=0;i<10;i++)
		if(alpha(vari[i])==alpha(a))
			break;
	if(i==10)
		return 0;
	for(j=0;j<60;j++)
		num[n][j]=varn[i][j];
	size[n]=varn[i][60];
	dot_count[n]=varn[i][61];
	return 1;
}
void save() {                             // 전 파일 제거 후 변수숫자 순서로 그대로 저장
	system("rm var 2> /dev/null");

	int i,o;

	FILE *fp = fopen("var","a");

	for(i=0;i<10;i++){
		if(vari[i]!=0){
			fprintf(fp,"%c",vari[i]);
		} 
		else{
			break;
		}
		for(o=0;o<62;o++)
			fprintf(fp,"%c",varn[i][o]);

	}
	fclose(fp);
}

void load() {                                //변수숫자 순서로 저장한 값 불러오기
	int i,j,tmp;

	FILE *fp2 = fopen("var","rt+");

	for(i=0;i<10;i++){
		fscanf(fp2,"%c",&vari[i]);

		for(j=0;j<60;j++){
			fscanf(fp2,"%c",&varn[i][j]);
		}
		fscanf(fp2,"%c",&varn[i][60]);
		fscanf(fp2,"%c",&varn[i][61]);
	}
	fclose(fp2);
}


