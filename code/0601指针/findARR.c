#include<stdio.h>


int findD60(int (*p)[4],int hang,int lie){
	for(int i=0;i<hang;i++){
		for(int j=0;j<lie;j++){
			if(p[i][j]<60){
			printf("学号为%d的学生,第%d门课程不合格,成绩为%d\n",i,j,*(*(p+i)+j));
			}
	}
	
}
/*for(int i=0;i<hang;i++){
		for(int j=0;j<lie;j++){
			if(p[i][j]<60){
			printf("学号为%d的学生,第%d门课程不合格,成绩为%d\n",i,j,p[i][j]);
			}
	}
	
}
*/


}
int main(){
	int a[][4]={{93,53,63,59},
	{100,90,67,77},
	{66,77,55,22}};
	int hang=sizeof(a)/sizeof(a[0]);
	int lie=sizeof(a[0])/sizeof(a[0][0]);
	
	findD60(a,hang,lie);

	
	return 0;
}