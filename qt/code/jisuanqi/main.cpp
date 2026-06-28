#include <iostream>

using namespace std;

//回调函数
int calx(int a,int b,int (*p)(int a ,int b) ){
    cout<<"开始计算"<<endl;
    p(a,b);
}

int main()
{
    int a=0;
    int b=0;
    char cal;

    while(1){
        cout<<"请输入数字 + —  * / 数子\n";
        cin>>a;

        cin>>cal;

        cin>>b;

        auto miv=[](int a,int b)->double{return (double)a/b;};
        switch (cal) {
        case '+':
            cout<<calx(a,b,[](int a,int b)->int{return a+b;})<<endl;
                  break;
        case '-':
            cout<<calx(a,b,[](int a,int b)->int{return a-b;})<<endl;
                  break;
        case '*':
            cout<<calx(a,b,[](int a,int b)->int{return a*b;})<<endl;
                  break;
        case '/':
            cout<<miv(a,b)<<endl;
                  break;

        }
        cout << "新一轮计算\n" << endl;
    }

    return 0;
}
