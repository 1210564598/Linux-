#include<stdio.h>


int myStrlen(char *a){
	int len=0;
	while(*(a+len)!='\0'){
		len++;
	}
	return len;
}

char *Mycopy(char *a,char *b){
		char *poi=a;
		while((*a=*b)!='\0'){
			a++;
			b++;
		}
		return poi;
}

int Mycmp(char *a,char *b){
		while((*a==*b)&&*a&&*b){
			a++;
			b++;
		}
		return *a-*b;
}

char *Mycat(char *a,char *b){
		char *poi=a;
		while((*a++)!='\0'){} // 找到末尾
		a--; // 回退到 '\0' 位置 ← 加上这一行
		
		while((*a++=*b++)!='\0'){}
		
		return poi;
}


int main(){
	char a[10]="hello";
	char b[]="hi";
	printf("%d\n",myStrlen(b));
	// Mycopy(a,b);
	// puts(a);
	printf("%d\n",Mycmp(a,b));
	Mycat(a,b);
	puts(a);
	return 0;
}