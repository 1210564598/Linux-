#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(){
	//输入输出函数
	/*char str[100];
	printf("hello\n");
	fgets(str,sizeof(str),stdin);
	puts(str);
	
	scanf("%s",str);
	puts(str);*/
	//字符串操作函数
	char str1[50]="hello";
	char str2[60]="hi";
	char str3[100]="you name";
	char str4[10]="nishishui";
	char str5[10]="nishis";
	strlen(str1);//获取字符串你长度 =5
	strcpy(str1,"nihao");
	puts(str1);
	strcpy(str1,str2);//复制
	puts(str1);
	strncpy(str1,str3,3);//复制n个字符
	str1[3]='\0';
	puts(str1);
	
	strcat(str1,str2);
	puts(str1);
	strcat(str1,"hello"); //追加字符
	puts(str1);
	
	
	if(strcmp(str4,str5)==0){//比较全部
		printf("你输入的内容相同\n");
	}else if(strcmp(str4,str5)>0){
		printf("第一个字符串的数值大\n");
	}else if(strcmp(str4,str5)<0){
		printf("第二个字符串的数值大\n");
	}
	
	printf("%d",strncmp(str4,str5,3));//比较前三字符
	
	char *p = strchr(str1, 'h');  // 查找字符 'h'
	if (p != NULL) {
		printf("找到字符 'h'，位置: %d\n", p - str1);  // 输出索引位置
	} else {
    printf("未找到字符 'h'\n");
	}
	
	char *p1=strstr(str1,"hell");
	if(p1!=NULL){
		printf("找到字串：%s,位置是%d\n",p1,p1 - str1);
	}
	
	char data[]="apple,baaba,orange";
	    char *token = strtok(data, ",");
    while (token != NULL) {
        printf("分割: %s\n", token);
        token = strtok(NULL, ",");
    }

	
	return 0;
}