#include<stdio.h>

struct Student{
	int age;
	char name[70];
	float score;
};

void PrinStudent(struct Student s){
	printf("%d %s %.1f\n",s.age,s.name,s.score);
}

void PrinpointStudent(struct Student *s){
	printf("%d %s %.2f\n",s->age,s->name,s->score);
}	


int main(){
	struct Student st1={13,"王五",99.2};
	struct Student *p=&st1;
	PrinStudent(st1);
	PrinpointStudent(p);

	return 0;
}

