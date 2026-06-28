#include<stdio.h>
#include<string.h>
//例题1：学生成绩管理系统
//定义学生结构体（学号、姓名、3门课成绩），输入3个学生信息，计算每个学生的平均分并输出。

struct Student{
	int id;
	float scores[3];
	char name[40];
	float avg;
};

void intStruct(struct Student *s){
	printf("请输入名字\n");
	char name[40];
	scanf("%s",name);
	strcpy(s->name,name);
	
	printf("请输入学号\n");
	scanf("%d",&s->id);
	
	printf("请输入成绩\n");
	for(int i=0;i<3;i++){
		scanf("%f",&s->scores[i]);
	}
	float sum=0;
	for(int i=0;i<3;i++){
		sum=(sum+s->scores[i]);
	}
	s->avg=sum/3;
}
void avgARR(struct Student *s,int len){
	
	for(int j=0;j<len;j++){
	float sum=0;
	for(int i=0;i<3;i++){
		sum=(sum+s[j].scores[i]);
	}
	s[j].avg=sum/3;
	}
}


void PrinStruct(struct Student s){
	printf("id:%d 姓名:%s  ",s.id,s.name);

	for(int i=0;i<3;i++){
		
		printf("第%d门课程的成绩为%.2f  ",i+1,s.scores[i]);
	}
	printf("平局分为:%.1f\n",s.avg);
	
}

void avgSort(struct Student *Arr,int len){
	struct Student tmp;
	
	for(int i=0;i<len-1;i++){
		for(int j=0;j<len-i-1;j++){
			if((Arr[j].avg)<(Arr[j+1].avg)){
				tmp=Arr[j+1];
				Arr[j+1]=Arr[j];
				Arr[j]=tmp;
			}
		}
	}
	
}

struct Student* FindavgMax(struct Student *s,int len){
	struct Student *max=s;
	for(int i=1;i<len;i++){
			if((s+i)->avg>max->avg){
				max=s+i;
			}
	}
	return max;
}



int main(){
    struct Student students[3] = {
        {1001, {85, 90, 88}, "张三", 0},
        {1002, {99, 92, 86}, "李四", 0},
        {1003, {80, 75, 79}, "王五", 0}
    };
    int len=sizeof(students)/sizeof(students[0]);
	avgSort(students,len);
	
    avgARR(students,len);
	struct Student *max=FindavgMax(students,len);
	PrinStruct(*max);
 
   // 循环输入
    // for (int i = 0; i < 3; i++) {
        // printf("\n====== 第 %d 个学生 ======\n", i + 1);
        // intStruct(&students[i]);  // 传入每个学生的地址
    // }
    
    // 循环输出
    // printf("\n========== 所有学生信息 ==========\n");
    // for (int i = 0; i < 3; i++) {
        // PrinStruct(students[i]);   // 传入每个学生
    // }
	
	
	return 0;
}