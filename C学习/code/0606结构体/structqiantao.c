#include<stdio.h>
//定义出生日期结构体，嵌套到学生结构体中，输入输出学生信息。
struct Data{
	int year;
	int mon;
	int day;
};

struct Student{
	int age;
	char name[40];
	struct Data bir;
};



int main(){
	struct Student stu={22,"黄",{2021,2,2}};
	printf("年龄:%d   名字：%s  生日:%d年%d月%d日",stu.age,stu.name,stu.bir.year,stu.bir.mon,stu.bir.day);
	
	return 0;
}