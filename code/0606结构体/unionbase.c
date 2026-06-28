#include<stdio.h>
#include<string.h>
union Student{
	int age;
	float score;
	char name[40];
};

int main(){
	union Student st1;
	st1.age=11;
	printf("%d \n",st1.age);
	
	puts("=====");
	st1.score=98.2;
	printf("%d \n",st1.age);
	printf("%.1f \n",st1.score);	
	puts("=====");
	
	strcpy(st1.name,"уехЩ");
	printf("%d \n",st1.age);
	printf("%.1f \n",st1.score);	
	printf("%s \n",st1.name);	
	return 0;
}