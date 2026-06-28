#include<stdio.h>
#include<string.h>

struct Candidate{
	char name[40];
	int votes;
};

//初始化
void IniCand(struct Candidate *p,int len){
	printf("+++++初始化开始+++++\n");
	int i=0;
	for(i=0;i<len;i++){
		printf("请输入你的名字\n");
		scanf("%s",p[i].name);
		p[i].votes=0;
	}
}

//打印数组
void PriCand(struct Candidate *p,int len,int invalid){
	printf("+++++打印信息如下+++++\n");
	
	for(int i=0;i<len;i++){
		printf("名字：%s 第%d候选人票数为%d\n",p[i].name,i+1,p[i].votes);
	}
		printf("本轮无效投票数：%d\n",invalid);
}

//开始投票
void StartVotes(struct Candidate *p,int len,int *inva){
	printf("+++++投票开始+++++\n");
	char name[40];
	for(int i=0;i<5;i++){
		printf("请输入你投票人的名字\n");
		scanf("%s",name);
		
		int found=0;
		for(int j=0;j<len;j++){
			if(strcmp(name,p[j].name)==0){ //strcmp
				p[j].votes++;
				found=1;
				break;
			}	
		}
		if(found==0){
			printf("无效投票\n");
			(*inva)++;
		}
	}
}
 
 void sortCand(struct Candidate *ArrC,int len){
	 
	struct Candidate tmp;
	for(int i=0;i<len-1;i++){
		for(int j=0;j<len-i-1;j++)
		if(ArrC[j].votes<ArrC[j+1].votes){
			tmp=ArrC[j+1];
			ArrC[j+1]=ArrC[j];
			ArrC[j]=tmp;
		}//选首位即是最大值，练习写一个findmax
	}	 
 }
 
void findMaxCand(struct Candidate *ArrC,int len){
	 int max=ArrC[0].votes;
	 int n=0;
	 for(int i=1;i<len;i++){
		if(ArrC[i].votes>max){
			max=ArrC[i].votes;
			n=i;
		}
	 }
	 printf("当选人为%s最大投票数：%d ",ArrC[n].name,max);
 }

int main(){
	struct Candidate ArrC[3];
	int len=sizeof(ArrC)/sizeof(ArrC[0]);
	int invalid=0;
	
	IniCand(ArrC,len);
	StartVotes(ArrC,len,&invalid);
	sortCand(ArrC,len);
	PriCand(ArrC,len,invalid);
	findMaxCand(ArrC,len);

	return 0;
}