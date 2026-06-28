#include<stdio.h>
//定义出生日期结构体，嵌套到学生结构体中，输入输出学生信息。用枚举表示学生状态（正常、休学、毕业），并输出。
enum status{
	Normal,
	Graduate,
	leaveSchool
};

struct Data{
	int year;
	int mon;
	int day;
};

struct Student{
	int age;
	char name[40];
	struct Data bir;
	enum status sta;
};

char* getStatus(enum status stu){
	switch(stu){
		case Normal:return "正常";
		
		case Graduate:return "毕业";
		
		case leaveSchool:return "离校";
		default:return "未知";
		
	}
	
}

int main(){
	struct Student stu[3]={
		{22,"黄",{2021,1,3},Normal},
		{21,"xx",{2022,2,2},leaveSchool},
		{23,"cc",{2023,3,1},Graduate}};
	for(int i=0;i<3;i++){
		printf("年龄:%d\n名字：%s\n生日:%d年%d月%d日 学生状态：%s\n",
		stu[i].age,stu[i].name,
		stu[i].bir.year,stu[i].bir.mon,stu[i].bir.day,
		getStatus(stu[i].sta));
		printf("\n");
	}

	
	return 0;
}