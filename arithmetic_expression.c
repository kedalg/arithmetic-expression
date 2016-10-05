#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
typedef struct{
    char *base;
    char *top;
    int stacksize;
}sc;
typedef struct{
    float *base;
    float *top;
    int stacksize;
}sf;
int InitStackc(sc *s){
    (*s).base=(char*)malloc(100*sizeof(char));
    if(!(*s).base) exit(-2);
    (*s).top=(*s).base;
    (*s).stacksize=100;
    return 1;
}
int InitStackf(sf *s){
    (*s).base=(char*)malloc(100*sizeof(char));
    if(!(*s).base) exit(-2);
    (*s).top=(*s).base;
    (*s).stacksize=100;
    return 1;
}
char GetTopc(sc s){
    char e;
    e=*(s.top-1);
    return e;
}
float GetTopf(sf s){
    float e;
    e=*(s.top-1);
    return e;
}
int Pushc(sc *s,char e){
    if((*s).top-(*s).base>=(*s).stacksize){
        (*s).base=(char*)realloc((*s).base,((*s).stacksize+10)*sizeof(char));
        if(!(*s).base) exit(-2);
        (*s).top=(*s).base+(*s).stacksize;
        (*s).stacksize+=10;
    }
    *(*s).top++=e;
    return 1;
}
int Pushf(sf *s,float e){
    if((*s).top-(*s).base>=(*s).stacksize){
        (*s).base=(float*)realloc((*s).base,((*s).stacksize+10)*sizeof(float));
        if(!(*s).base) exit(-2);
        (*s).top=(*s).base+(*s).stacksize;
        (*s).stacksize+=10;
    }
    *(*s).top++=e;
    return 1;
}
int Popc(sc *s,char *e){
    if((*s).top==(*s).base) return 0;
    (*e)=*--(*s).top;
    return 1;
}
int Popf(sf *s,float *e){
    if((*s).top==(*s).base) return 0;
    (*e)=*--(*s).top;
    return 1;
}
char proceed(char c1,char c2){
    char *row,*col,*op="+-*/()#";
    char opt[7][8]={
        ">><<<>>",
        ">><<<>>",
        ">>>><>>",
        ">>>><>>",
        "<<<<<=@",
        ">>>>@>>",
        "<<<<<@="};
        row=strchr(op,c1);
        col=strchr(op,c2);
        return opt[row-op][col-op];
}
float operate(float a,char d,float b){
    if(d=='+') return(a+b);
    else if(d=='-') return(a-b);
    else if(d=='*') return(b*a);
    else return(a/b);
}
float StringToFloat(char *ch){
    char *p=ch;
    float v1=0.0,v2=0.0,t=0.1;
    while(*p!='\0'&&*p!='.'){
        v1=v1*10+*p-'0';
        p++;
    }
    p++;
    while(*p!='\0'){
        v2=v2+(*p-'0')*t;
        t*=0.1;
        p++;
    }
    return v1+v2;
}
float evaluateexpression(char *s1){
    sc OPTR;
    sf OPND;
    int i=0,j=0;
    char s2[80];
    char x,theta;
    float a,b,e;
    InitStackc(&OPTR);
    Pushc(&OPTR,'#');
    InitStackf(&OPND);
    while(s1[i]!='#'||GetTopc(OPTR)!='#'){
        if(s1[i]>='0'&&s1[i]<='9'||s1[i]=='.'){
            s2[j]=s1[i];
            j++;
            if((s1[i+1]<'0'||s1[i+1]>'9')&&s1[i+1]!='.'){
                s2[j]='\0';
                s2[j+1]='\0';
                Pushf(&OPND,StringToFloat(s2));
                j=0;
            }
            i++;
        }
        else{
            switch(proceed(GetTopc(OPTR),s1[i])){
                case '<':
                    Pushc(&OPTR,s1[i]);
                    i++;
                    break;
                case '=':
                    Popc(&OPTR,&x);
                    i++;
                    break;
                case '>':
                    Popc(&OPTR,&theta);
                    Popf(&OPND,&b);
                    Popf(&OPND,&a);
                    Pushf(&OPND,operate(a,theta,b));
                    break;
            }
        }
    }
    return GetTopf(OPND);
}
void main(){
    char str[80];
    printf("please imput arithmetic expression:\n");
    gets(str);
    printf("the value of the arithmetic expression is:%f\n",evaluateexpression(str));
}
