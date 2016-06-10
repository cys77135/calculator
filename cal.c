#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char num[100][60]={0};
char size[100]={0};
char dot_count[100]={0};
char what[100]={0};
char re[60]={0};
char vari[10]={0};
char varn[10][62]={0};
int v=0;
int scan();
void print(int);
void sum(int,int);
void min(int,int);
void mul(int,int);
void di(int,int);
void rem(int,int);
int nu(int,int);
void copy(int,int);
void big(int,int);
void put(int,int);
void var();

int main(){
    int i=0,j,count=0;
    while(1){
        for(i=0;i<=100;i++){
            for(j=0;j<60;j++)
                num[i][j]=0;
            size[i]=0;
            dot_count[i]=0;
        }
        if(scan()){
            for(i=0;i<strlen(what);i++){
                if(what[i]=='*')
                    mul(i,i+1);
                if(what[i]=='/')
                    di(i,i+1);
                if(what[i]=='%')
                    rem(i,i+1);
            }
            for(i=0;i<strlen(what);i++){
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
            if(vari[v])
                put(v,strlen(what));
            print(strlen(what));
        }
    }
}

int scan(){
    int n=0,i,j=1,k=0,l=0,t,max;
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
        else if((a[i]=='+'||a[i]=='-'||a[i]=='*'||a[i]=='/'||a[i]=='%')&&!(a[i+1]>='0'&&a[i+1]<='9')){
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
        else if(i==2&&(a[0]>='a'&&a[0]<='z')&&(a[1]==' '&&a[2]=='=')){
            for(l=0;l<=10;l++){
                if(vari[l]==a[0]){
                    v=l;
                    break;
                }
            if(l==10){
                for(t=0;t<10;t++){
                    if(!vari[t]){
                        vari[t]=a[0];
                        v=t;
                        break;
                    }
                }
                }
            }
        }
    }
   
    if(!strcmp(a,"clear")){
        system("clear");
        return 0;
    }
    if(!strcmp(a,"VAR")){
        var();
        return 0;
    }
    if(!strcmp(a,"end"))
        exit(1);
    for(n=0;n<100;n++){
        for(j=50,i=size[n];i>=1;i--,j--){
            num[n][j]=num[n][i];
            num[n][i]=0;
        }
    }
    return 1;
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
        for(i=0;i<60;i++)
            num[n2][i]=result[i];
    }
    else if(num[n2][0]){
        num[n2][0]=0;
        min(n1,n2);
    }
    else if(num[n1][0]){
        num[n1][0]=0;
        min(n2,n1);
        copy(n1,n2);
    }
}
void min(int n1,int n2){
    int i,j,k=0,l=0;
    char result[60]={0},ex[60]={0};
    if(!num[n1][0]&&!num[n2][0]){
        if(size[n2]>=size[n1]){
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
    else if(num[n1][0]&&!num[n2][0]){
        num[n2][0]=1;
        sum(n1,n2);
    }
    else if(!num[n1][0]&&num[n2][0]){
        num[n2][0]=0;
        sum(n1,n2);
    }
    else if(num[n1][0]&&num[n2][0]){
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
    for(a=size[n1]+size[n2];a>=0;--a)
    {
        if(result[18+a]){
            size[n2]=a+1;
            break;
        }
        else if(a==0)
            size[n2]=1;
    }
    for(a=9;a<67;++a,--b){
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
    char result[60]={0},ex[60]={0},cou=0,mi=0;
    if(num[n1][0]==num[n2][0]){
        num[n1][0]=0;
        num[n2][0]=0;
    }
    else if(num[n1][0]!=num[n2][0]){
        mi++;
        num[n1][0]=0;
        num[n2][0]=0;
    }
    for(a=0;a<60;a++)
        ex[a]=num[n2][a];
    
    while(nu(n1,n2)==2){
        for(a= 1;a<=59;++a)
            num[n2][a]=num[n2][a+1];
        num[n2][59]=0;
        --al;
        for(a=0;a<60;a++)
            ex[a]=num[n2][a];
    }
    while(nu(n1,n2)==1){
        for(a=59;a>1;--a)
            num[n2][a]=num[n2][a-1];
        ++al;
        num[n2][1]=0;
        for(a=0;a<60;a++)
            ex[a]=num[n2][a];
    }
    if(nu(n1,n2)==0)
        result[al]=1;
    while(al<=59&&nu(n1,n2)!=0){
        while(nu(n1,n2)==2||nu(n1,n2)==0){
            min(n1,n2);
            for(a=0;a<60;++a)
                num[n1][a]=num[n2][a];
            for(a=0;a<60;a++)
                num[n2][a]=ex[a];
            cou++;
        }
        result[al]=cou;
        cou=0;
        if(al==50){
            for(a=0;a<=60;++a)
                re[a]=num[n1][a];
        }
        if(nu(n1,n2)==0) break;
        for(a=59;a>0;--a)
            num[n2][a]=num[n2][a-1];
        ++al;
        num[n2][1]=0;
        for(a=0;a<60;a++)
            ex[a]=num[n2][a];
    }
    for(a=0;a<60;a++)
        num[n2][a]=result[a];
    for(a=0;a<=50;a++){
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
    if(mi)
        num[n2][0]='-';
}
void rem(int n1,int n2)
{
    int a;
    if(nu(n1,n2)==2){
        di(n1,n2);
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
    else if(nu(n1,n2)==0){
        for(a=0;a<60;++a)
            num[n2][a]=0;
    }
    else if(nu(n1,n2)==1){
        for(a=0;a<60;a++)
            num[n2][a]=num[n1][a];
        size[n2]=size[n1];
    }
}
int nu(int n1,int n2)
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
void copy(int n1,int n2){
    int i=0;
    for(i=0;i<60;i++)
        num[n2][i]=num[n1][i];
    size[n2]=size[n1];
    dot_count[n2]=dot_count[n1];
}
void put(int v,int n){
    int i;
    for(i=0;i<60;i++)
        varn[v][i]=num[n][i];
    varn[v][60]=size[n];
    varn[v][61]=dot_count[n];
}
void var(){
    int i,j,a;
    for(i=0;i<10;i++){
        if(vari[i])
            printf("%c ",vari[i]);
        else
            break;
        for(j=0;j<60;j++)
            num[0][j]=varn[i][j];
        size[0] = varn[i][60];
        dot_count[0] = varn[i][61];
        print(0);
}
    printf("\n");
}
