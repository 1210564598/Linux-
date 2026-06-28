#include <stdio.h>
#include <stdlib.h>
struct car{
   char* barnd;
   int year;
   char* type;
   void (*printcar)(char* barnd,int year,char* type);//函数指针
};

void printcar1(char* barnd,int year,char* type){
    printf("%s %d %s",barnd,year,type);
}

int main()
{
    struct car car1;
    car1.barnd="宝马";
    car1.type="坦克";
    car1.year=1880;

    car1.printcar=printcar1;
    car1.printcar(car1.barnd,car1.year,car1.type);


    struct car *pcar=(struct car*)malloc(sizeof(struct car));
    pcar->type="飞机";
    pcar->year=1888;
    pcar->barnd="aodi";

    pcar->printcar=printcar1;
    pcar->printcar(pcar->barnd,pcar->year,pcar->type);
    free(pcar);


    printf("Hello World!\n");
    return 0;
}
