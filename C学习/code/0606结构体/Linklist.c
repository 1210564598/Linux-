#include<stdio.h>
#include<stdlib.h>

struct Linklist{
	int data;
	struct Linklist *next;
};

void Prilinklist(struct Linklist *p){
	while(p!=NULL){
		printf("%d ",p->data);
		p=p->next;
	}
	
}

int main(){
	struct Linklist s1;
	struct Linklist s2;
	struct Linklist s3;
	s1.data=10;
	s1.next=&s2;
	s2.data=20;
	s2.next=&s3;
	s3.data=30;
	s3.next=NULL;
	
	struct Linklist *head=&s1;
	Prilinklist(head);
	
	return 0;
}