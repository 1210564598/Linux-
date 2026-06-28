#include <iostream>

using namespace std;

class whell{
public:
    string brand;
    int year11;

    void printwhell(string brand,int year11);
};

void whell::printwhell(string brand,int year11){
    string str1="品牌\t"+brand+"年限"+to_string(year11);
     cout<<str1<<endl;
}


class car{
public:
    string barnd;
    int year;
    string type;
    class whell w1;
    class whell *w2;

    void printcar(string barnd,int year,string type);
};

void car::printcar(string barnd,int year,string type){
    cout<<"品牌："<<barnd<<"\t类型："<<type<<"\t年限："<<year<<endl;
  string str="品牌"+barnd+"类型"+type+"年限"+to_string(year);
    cout<<str<<endl;

}
int main()
{
    car car1;
    car1.barnd="奥迪";
    car1.type="官车";
    car1.year=1999;
    car1.w1.brand="轮胎人";
    car1.w1.year11=1555;
   // car1.w1.printwhell(car1.w1.brand,car1.w1.year11);
  //  car1.printcar(car1.barnd,car1.year,car1.type);

    car *car2=new car();
    car2->type="feiji";
    car2->barnd="xiaomi";
    car2->year=1777;

    car2->w2 = new whell();
    car2->w2->brand="汽车人";
    car2->w2->year11=17777;
    car2->w2->printwhell(car2->w2->brand,car2->w2->year11);
  //  car2->printcar(car2->type,car2->year,car2->barnd);
    cout << "Hello World!" << endl;
    return 0;
}
