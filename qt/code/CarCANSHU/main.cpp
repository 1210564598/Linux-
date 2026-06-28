#include <iostream>
#include <string>
using namespace std; // 使用std命名空间

class Car {
    public:
    string brand; // 不需要使用std::string
    int year;
    // 无参构造函数
    Car() {
    brand = "未知";
    year = 0;
    cout << "无参构造函数被调用" << endl; // 不需要使用std::cout和std::endl
}
     Car(string br,int y) {
        brand = br;
        year =y;
        cout << "有参构造函数被调用" << endl; // 不需要使用std::cout和std::endl
    }
    void display() {
    cout << "Brand: " << brand << ", Year: " << year << endl;
}
};
int main() {
    Car myCar; // 创建Car对象
    myCar.display(); // 显示车辆信息

    Car myCar2("SU7",2024);
     myCar2.display();

    Car *myCar1=new Car("lixiang",2024);
    myCar1->display(); // 显示车辆信息
    return 0;
}
