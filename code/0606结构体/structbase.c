#include<stdio.h>
#include<string.h>
struct student{
	int age;
	char name[40];
	float score;
};

struct student1{
	int age;
	char name[40];
	float score;
}stu1,stu2;

int main(){
	
	struct student st1;
	struct student st2={11,"张三",85.5};
	struct student *p=&st2;
	struct student arr[2];
	st1.age=12;
	strcpy(st1.name,"里斯");
	st1.score=87.7;
	arr[1]=st1;
	arr[0]=st2;
	int n=sizeof(arr)/sizeof(arr[0]);
	for(int i=0;i<n;i++){
		printf("%d %s %.2f\n",arr[i].age,arr[i].name,arr[i].score);
	}
	printf("%d %s %.2f",p->age,p->name,p->score);
	return 0;
}
