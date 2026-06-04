#include<stdio.h>
#include<string.h>
#include<stdlib.h>
	

int main(){
	char str1[]="hello";
	char str2[10]="hello";
	char str3[]={'h','e','l','l','o','\0'};
	char *p1="hello";
	char *p2=(char *)malloc(5);//分配完后要初始化
	strcpy(p2,"hello");
	
	printf("size=%d\n",sizeof(str1));//6
	printf("size=%d\n",strlen(str1));//5
	printf("size2=%d\n",sizeof(str2));//10
	printf("size2=%d\n",strlen(str2));//5	
	printf("size3=%d\n",sizeof(str3));//6
	printf("size3=%d\n",strlen(str3));//5
	printf("sizep1=%d\n",sizeof(p1));//8
	printf("sizep1=%d\n",strlen(p1));//5
	printf("sizep2=%d\n",sizeof(p2));//8
	printf("sizep2=%d\n",strlen(p2));//5
	
	
	free(p2);
	p2=NULL;
	return 0;
}