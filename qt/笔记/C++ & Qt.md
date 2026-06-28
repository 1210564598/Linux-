------

# QT开发

## 前言：课程特点

- 以项目驱动，通过记事本、串口助手、网络助手、仪表盘、天气预报五个项目，覆盖QT开发全流程。
- 零基础友好，前2章完整讲解C++核心语法（尤其是面向对象、STL、模板等QT常用特性）。
- 所有代码均来自实际课堂，可直接运行。

------

## P1 QT介绍（详细）

### 1.1 QT是什么

- Qt（发音“cute”）是一个跨平台的C++应用程序开发框架，主要用于GUI程序，也可用于命令行。
- 支持的操作系统：Windows、macOS、Linux、Android、iOS、嵌入式Linux等。
- **主要模块**：
  - QtCore：核心非GUI功能（事件循环、字符串、容器等）
  - QtGui：窗口系统集成、字体、2D绘图
  - QtWidgets：传统桌面控件（按钮、文本框等）
  - QtNetwork：TCP/IP、HTTP等网络编程
  - QtSerialPort：串口通信
  - QtSql：数据库访问
  - QtMultimedia：音视频
  - QtQuick/QML：现代声明式UI（移动端、嵌入式）
- **版本选择**：Qt5.12.9 LTS（长期支持），课程使用此版本。Qt6有改动，但核心概念相通。

### 1.2 开源版 vs 商业版

- **开源版**：基于LGPL/GPL，必须遵守开源协议（修改的代码需开源，动态链接可闭源）。
- **商业版**：提供专有许可，可闭源，且有官方技术支持。
- 对于学习和小型商业项目，开源版完全足够。

### 1.3 安装步骤（Windows）

1. 下载在线安装器或离线安装包（课程提供百度网盘链接）。
2. **断网**运行安装程序，避免强制登录账号。
3. 选择安装组件（至少选择）：
   - 编译器：MinGW 7.3.0 64-bit（或MSVC 2017 64-bit）
   - Qt 5.12.9 下的 `Sources`（源码）、`Qt Charts`、`Qt Data Visualization`、`Qt Virtual Keyboard`
   - Developer and Designer Tools 下的 `Qt Creator`
4. 安装完成后，打开Qt Creator，配置编译器（Kit）。
5. 测试：新建Qt Widgets Application，点击运行，看到空白窗口即成功。

### 1.4 Qt Creator 使用技巧

- **界面**：左边栏有“欢迎”“编辑”“设计”“调试”“项目”“帮助”。
- **常用快捷键**（补充文档中的表格）：
  - `Ctrl + K`：快速打开任何文件或类
  - `Ctrl + /`：注释/取消注释
  - `F1`：查看光标所在类/函数的帮助文档
  - `Ctrl + i`：自动缩进选中代码
  - `Ctrl + Shift + R`：重命名符号（变量、函数等）
  - Ctrl + ALT + down 向下复制
- **编译输出**：底部4面板 - 问题、搜索结果、应用程序输出、编译输出。

------

## P2 C++基础（全面讲解）

> 本章节是QT开发的预科，但有些内容QT中极少用到（如多重继承、虚继承、运算符重载），文档都列出了，我会标注重点程度。

### 2.1 命名空间（重要）

- **目的**：避免全局命名冲突。

- **定义**：

  cpp

  ```
  namespace MyLib {
      void func() { ... }
  }
  ```

- **使用**：

  - 作用域限定：`MyLib::func()`
  - 引入整个命名空间：`using namespace MyLib;`（小项目可用，头文件中避免使用）
  - 引入特定符号：`using MyLib::func;`

- **标准库命名空间**：`std`，包含`cout`、`vector`、`string`等。

- 例子 ：

```
//头文件
#ifndef CIR_H
#define CIR_H
namespace Cir {
const double PI = 3.141592653;
double areaOfCircle(double radius){
return PI*radius*radius;
}
double lenthOfCircle(double radius){
return 2*PI*radius;
}
}
#endif // CIR_H
```

```
#include "cir.h"
#include <stdio.h>
using namespace Cir;
int main()
{
double radius = 5;
printf("半径为%f的圆，周长为%f,面积为%f\n",
radius,lenthOfCircle(radius), areaOfCircle(radius));
return 0;
}
```



### 2.2 输入输出（重要）

- `std::cin` >> 变量

- `std::cout` << 内容 << std::endl（换行+刷新缓冲区）

- `std::cerr`：无缓冲错误输出

- `std::clog`：有缓冲日志输出

- 示例：

  cpp

  ```
  #include <iostream>
  int main() {
      int age;
      std::cout << "Enter age: ";
      std::cin >> age;
      std::cerr << "If age is wrong, you'll see this immediately." << std::endl;
      retun 0;
  }
  ```

### 2.3 基本变量类型（了解）

- 整型：`int`, `short`, `long`, `long long`, 以及`unsigned`版本。

- 浮点：`float`（~7位精度）、`double`（~15位）、`long double`（更高精度，平台相关）

- 字符：`char`（1字节，ASCII）、`wchar_t`（宽字符，用于Unicode）、C++11新增`char16_t`、`char32_t`。

- 布尔：`bool`（true/false）

- **查看类型范围**：`<climits>`中的`INT_MAX`、`LONG_MIN`等。

- INT_MAX ： int 类型的最大值。

  INT_MIN ： int 类型的最小值。

  UINT_MAX ： unsigned int 类型的最大值。

  LONG_MAX ： long int 类型的最大值。

  LONG_MIN ： long int 类型的最小值。

  LLONG_MAX ： long long int 类型的最大值。

  LLONG_MIN ： long long int 类型的最小值

例子：

```
#include <iostream>
#include <climits>
int main() {
std::cout << "The range of int is from " << INT_MIN << " to " << INT_MAX <<
std::endl;
std::cout << "The maximum value of unsigned int is " << UINT_MAX <<
std::endl;
std::cout << "The range of long long is from " << LLONG_MIN << " to " <<
LLONG_MAX << std::endl;
return 0;
}
```



- **宽字符示例**（输出中文）：

  cpp

  ```
  #include <iostream>
  #include <locale>
  #include <wchar.h>
  int main() {
  // 设置本地化以支持宽字符
  std::setlocale(LC_ALL, "");
  // 使用 wchar_t 类型定义一个宽字符串
  wchar_t wstr[] = L"你好，世界！";
  // 在 C++ 中打印宽字符串
  std::wcout << wstr << std::endl;
  return 0;
  }
  ```

  

### 2.4 流程控制（重要）

- `if-else if-else`、`switch-case-default`（每个case后要break，否则穿透）。
- 循环：`for`、`while`、`do-while`。
- 跳转：`break`、`continue`、`goto`（极不推荐）。

### 2.5 函数（重要）

- 声明与定义分离：声明放在头文件，定义放在cpp文件。
- 参数传递：值传递（拷贝）、指针传递（传递地址）、引用传递（别名，更安全）。
- **默认参数**：从右向左提供默认值。
- **函数重载**：同一作用域，函数名相同，参数列表不同（类型、个数、顺序），返回类型不能作为重载依据。
- 基本结构：

```
返回类型 函数名(参数列表) {
// 函数体
// 返回语句（如果有返回值的话）
}
```

```
#include <iostream>
using namespace std;
// 函数声明
int add(int x, int y);
int main() {
int result = add(5, 3);
cout << "Result: " << result << endl;
return 0;
}
// 函数定义
int add(int x, int y) {
	return x + y;
}
```



### 2.6 内联函数（了解）

- 建议编译器将函数体插入调用点，消除函数调用开销。

- 适用于短小、频繁调用的函数（如getter/setter）。

- 定义通常放在头文件中。

- 现代编译器会智能决定是否内联，`inline`只是建议。

- 示例

  ```
  #include <iostream>
  inline int add(int a, int b) {
  return a + b;
  }
  int main() {
  int result = add(5, 3); // 编译器可能会将此替换为：int result = 5 + 3;
  std::cout << "Result: " << result << std::endl;
  return 0;
  }
  ```

  

### 2.7 Lambda表达式（非常重要，QT中大量使用）

- **语法**：`[捕获](参数) -> 返回类型 { 函数体 }`

- **语法示例**

  ```
  [capture clause](parameters) -> return_type {
  // 函数体
  // 可以使用捕获列表中的变量
  return expression; // 可选的返回语句
  }
  ```

- **捕获方式**：

  - `[]`：不捕获任何外部变量
  - `[=]`：值捕获所有外部变量（只读）
  - `[&]`：引用捕获所有外部变量（可修改）
  - `[x, &y]`：混合捕获

- **示例**：

  cpp

  ```
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
  ```

  

### 2.8 数组指针字符串（重要）

- 在 C++ 中，数组是一种存储固定大小的相同类型元素的序列。数组的所有元素都存储在连续的内存位置上。

- 在 C++ 中， string 类是标准库的一部分，用于表示和操作字符串。

- C++完全兼容C语言指针，多出一个this指针

- **C++ string**：

  cpp

  ```
  #include <iostream>
  #include <string>
  int main() {
  std::string str = "Hello, world!";
  std::cout << str << std::endl; // 输出字符串
  str += " I am a C++ string."; // 字符串连接
  std::cout << str << std::endl;
  std::string substr = str.substr(7, 5); // 获取子字符串
  std::cout << "Substring: " << substr << std::endl;
  return 0;
  }
  ```
  
  ## std::string 常用成员函数表
  
  | 函数名                                               | 功能                             | 参数                                                    | 返回值类型                        |
  | :--------------------------------------------------- | :------------------------------- | :------------------------------------------------------ | :-------------------------------- |
  | `length()` / `size()`                                | 返回字符串的长度                 | 无                                                      | `size_t`                          |
  | `empty()`                                            | 检查字符串是否为空               | 无                                                      | `bool`                            |
  | `append(const string& str)`                          | 向字符串末尾追加另一个字符串     | `str`：要追加的字符串                                   | `string&`                         |
  | `substr(size_t pos = 0, size_t len = npos)`          | 返回一个子字符串                 | `pos`：起始位置（默认0） `len`：子串长度（默认到末尾）  | `string`                          |
  | `find(const string& str, size_t pos = 0)`            | 查找子字符串首次出现的位置       | `str`：要查找的字符串 `pos`：搜索起始位置（默认0）      | `size_t`（未找到返回 `npos`）     |
  | `compare(const string& str)`                         | 比较两个字符串（字典序）         | `str`：要比较的字符串                                   | `int`（0 相等，<0 小于，>0 大于） |
  | `erase(size_t pos = 0, size_t len = npos)`           | 删除字符串中的一部分             | `pos`：起始位置（默认0） `len`：删除长度（默认到末尾）  | `string&`                         |
  | `insert(size_t pos, const string& str)`              | 在指定位置插入字符串             | `pos`：插入位置 `str`：要插入的字符串                   | `string&`                         |
  | `replace(size_t pos, size_t len, const string& str)` | 替换字符串中的一部分             | `pos`：起始位置 `len`：被替换的长度 `str`：替换的字符串 | `string&`                         |
  | `c_str()`                                            | 返回 C 风格字符串表示（只读）    | 无                                                      | `const char*`                     |
  | `operator[](size_t pos)`                             | 访问指定位置的字符（不检查边界） | `pos`：字符索引                                         | `char&`                           |

### 2.9 类（核心）

C++ 中的类（class）是一种编程结构，用于创建对象。这些对象可以拥有属性（即数据成员）和行为

（即成员函数或方法）。

C++ 类的基本结构通常包含：

1. **数据成员**：定义类的属性。这些是类内部的变量，用于存储对象的状态。
2. **成员函数**：定义类的行为。这些是可以操作对象的数据成员的函数。
3. **构造函数和析构函数**：特殊的成员函数。构造函数在创建对象时自动调用，用于初始化对象。析构

函数在对象销毁时调用，用于执行清理操作。

4. **访问修饰符**：如 public , private , protected ，用于控制对类成员的访问权限。例如， public

成员可以在类的外部访问，而 private 成员只能在类内部访问。

5. **继承**：允许一个类继承另一个类的特性。这是代码重用和多态性的关键。

通过这些特性，C++ 类提供了一种强大的方式来组织和处理数据，使得代码更加模块化、易于理解和维

护。

- **从结构体到类**：

  - C结构体只有数据，函数需要用函数指针模拟（繁琐）。
  - C++类将数据和操作封装在一起。

- **成员访问**：对象用`.`，指针用`->`。

- **构造函数**：与类同名，无返回值，可重载。

  - 默认构造函数（无参数）。
  - 有参构造函数：用于初始化成员。
  - 拷贝构造函数：`ClassName(const ClassName& other)`。

- **析构函数**：`~ClassName()`，无参数无返回值，用于释放资源。

- **类的基本结构：**

  ```
  class Student {
  public:
      Student(const std::string& n, int a) : name(n), age(a) {}
      void introduce() const { /* ... */ }
  private:
      std::string name;
      int age;
  };
  
  int main() {
      // 动态创建对象
      Student* p = new Student("张三", 18);
      p->introduce();          // 使用 -> 调用成员函数
      delete p;                // 必须手动释放内存，否则内存泄漏
      p = nullptr;             // 可选：将指针置空
      return 0;
  }
  ```


示例：car例子

```c
//结构体
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


```

```c++
//类
#include <iostream>

using namespace std;

class car{
public:
    string barnd;
    int year;
    string type;
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
    car1.printcar(car1.barnd,car1.year,car1.type);

    car *car2=new car();
    car2->type="feiji";
    car2->barnd="xiaomi";
    car2->year=1777;
    car2->printcar(car2->type,car2->year,car2->barnd);
    cout << "Hello World!" << endl;
    return 0;
}

```

```c++
//组合类
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

```



### 2.10 权限（核心）

| 访问权限  | 类内部   | **类外部，对象不能访问私有成员** | 派生类（子类） | 类外部     |
| :-------- | :------- | :------------------------------- | :------------- | :--------- |
| public    | ✔️ 可访问 | ✔️ 可访问                         | ✔️ 可访问       | ✔️ 可访问   |
| private   | ✔️ 可访问 | ❌ 不可访问                       | ❌ 不可访问     | ❌ 不可访问 |
| protected | ✔️ 可访问 | ❌ 不可访问                       | ✔️ 可访问       | ❌ 不可访问 |

- **class默认private，struct默认public**。



### 2.11 引用（核心）

- 定义：`int &ref = var;`，ref是var的别名，**必须初始化**，不能更改指向。

- 常用作函数参数（避免拷贝，且可修改实参）：

  ```
  void swap(int &a, int &b) { int t=a; a=b; b=t; }
  ```

  ```
  //把引用作为参数
  #include <iostream>
  using namespace std;
  // 函数声明
  void swap(int& x, int& y);
  
  
  int main ()
  {
  // 局部变量声明
  int a = 100;
  int b = 200;
  cout << "交换前，a 的值：" << a << endl;
  cout << "交换前，b 的值：" << b << endl;
  /* 调用函数来交换值 */
  swap(a, b);
  cout << "交换后，a 的值：" << a << endl;
  cout << "交换后，b 的值：" << b << endl;
  return 0;
  }
  
  
  // 函数定义
  void swap(int& x, int& y)
  {
  int temp;
  temp = x; /* 保存地址 x 的值 */
  x = y; /* 把 y 赋值给 x */
  y = temp; /* 把 x 赋值给 y */
  return;
  }
  ```

- 可作为返回值（返回局部变量的引用是未定义行为，返回静态成员或对象成员的引用是安全的）。

- **与指针区别**：引用不为空、无需解引用、不能重新绑定。



**把引用作为返回值**

```
#include <iostream>
using namespace std;
double vals[] = {10.1, 12.6, 33.1, 24.1, 50.0};
double& setValues(int i) {
double& ref = vals[i];
return ref; // 返回第 i 个元素的引用，ref 是一个引用变量，ref 引用 vals[i]
}
// 要调用上面定义函数的主函数
int main ()
{
cout << "改变前的值" << endl;
for ( int i = 0; i < 5; i++ )
{
cout << "vals[" << i << "] = ";
cout << vals[i] << endl;
}
setValues(1) = 20.23; // 改变第 2 个元素  setValues(1)函数调用当左值可以修改
setValues(3) = 70.8; // 改变第 4 个元素
cout << "改变后的值" << endl;
for ( int i = 0; i < 5; i++ )
{
cout << "vals[" << i << "] = ";
cout << vals[i] << endl;
}
return 0;
}
```



当返回一个引用时，要注意被引用的对象不能超出作用域。

```
int& func() {
int q;
//! return q; // 在编译时发生错误
static int x;
return x; // 安全，x 在函数作用域外依然是有效的
}
```



### 2.12 **函数重载**/（运算符重载（了解））

- 在同一个作用域内，可以声明几个功能类似的同名函数，

  这些同名函数的形式参数（指参数的个数、类型或者顺序）必须不同。您不能仅通过返回类型的不同来

  重载函数。

  ```
  #include <iostream>
  using namespace std;
  class printData
  {
  public:
  void print(int i) {
  cout << "整数为: " << i << endl;
  }
  void print(double f) {
  cout << "浮点数为: " << f << endl;
  }
  void print(char c[]) {
  cout << "字符串为: " << c << endl;
  }
  };
  int main(void)
  {
  printData pd;
  // 输出整数
  pd.print(5);
  // 输出浮点数
  pd.print(500.263);
  // 输出字符串
  char c[] = "Hello C++";
  pd.print(c);
  return 0;
  }
  ```

  

  ### 运算符重载

  operator

- 可重载的运算符：`+ - * / = == != < > [] () << >>`等。

- 不能重载的：`::`、`.`、`.*`、`?:`、`sizeof`等。

- 示例：加法

  ```c++
  #include <iostream>
  class Point {
      public:
      int x, y;
  // 重载 + 运算符
  	Point operator+(Point other)；
  };
  Point Point::operator+(Point other) {
      Point ret;
      ret.x=x+other.x;
      ret.y=y+other.y;
  	return ret;
  }
  int main() {
      Point p1;
      p1.x = 1;
      p1.y = 2;
      Point p2;
      p2.x = 2;
      p2.y = 3;
  
      Point p3 = p1 + p2; // 使用重载的 + 运算符
      std::cout << "p3.x: " << p3.x << ", p3.y: " << p3.y << std::endl; // 输出
      p3.x: 4, p3.y: 6
      return 0;
  }
  ```
  
  在这个例子中， operator+ 被重载为一个成员函数，接受一个 Point 类型的常量引用作为参数，并返
  
  回两个点相加的结果。

### 2.13 **构造函数**/析构函数/拷贝控制（重点理解）

#### 构造函数

- 类的**构造函数**是类的一种特殊的成员函数，它会在每次创建类的新对象时执行。

- **构造成员变量的初始化值，内存空间等**

  构造函数的名称与类的名称是完全相同的，并且不会返回任何类型，也不会返回 void。构造函数可用于

  为某些成员变量设置初始值。

```
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

```

#### 初始化列表

初始化列表是 C++ 构造函数的一种特殊语法，用于在进入构造函数体**之前**直接初始化成员变量。

基本语法

```
class 类名 {
public:
    类名(参数列表) : 成员1(值1), 成员2(值2), ... {
        // 构造函数体（可空）
    }
};
```

```
class Car {
public:
    string brand;
    int year;
    Car(string br, int y) : brand(br), year(y) {
        // 此时 brand 和 year 已经初始化完成
    }
};
```

析构函数



#### 拷贝构造（未学习）

- **深拷贝 vs 浅拷贝**：

  - 浅拷贝：只复制指针值，多个对象指向同一堆内存，析构时多次delete导致崩溃。
  - 深拷贝：分配新内存，复制内容。

- **规则三则**：若自定义了析构函数、拷贝构造函数、拷贝赋值运算符中的任何一个，则通常需要实现所有三个。

- **禁用拷贝**：C++11中使用`= delete`。

  cpp

  ```
  class NonCopyable {
  public:
      NonCopyable(const NonCopyable&) = delete;
      NonCopyable& operator=(const NonCopyable&) = delete;
  };
  ```

  

### 2.14 静态成员（重要）

- 静态成员变量：属于类而非对象，所有对象共享一份，必须在类外单独定义（初始化）。

- 静态成员函数：只能访问静态成员，不需要对象即可调用。

- 典型用途：单例模式、对象计数。

  cpp

  ```
  class Counter {
      static int count;
  public:
      Counter() { count++; }
      static int getCount() { return count; }
  };
  int Counter::count = 0;
  ```

  

### 2.15 继承（核心）

- 语法：`class Derived : public Base`
- 三种继承方式：
  - public继承：基类public→派生类public，protected→protected，private不可访问。
  - protected继承：基类public/protected→派生类protected。
  - private继承：基类public/protected→派生类private。
- 构造顺序：先基类构造，再派生类构造；析构顺序相反。
- **虚函数**：在基类中声明`virtual`，派生类重写。通过基类指针/引用调用时，动态绑定到实际对象类型。
- **override**：C++11关键字，显式表示重写基类虚函数，帮助编译器检查。
- **纯虚函数**：`virtual void func() = 0;`，使类成为抽象类，不能实例化。
- **多重继承**：一个类有多个直接基类，可能导致菱形继承问题。
- **虚继承**：解决菱形继承，使用`virtual`关键字，确保最派生类只有一个基类子对象。

### 2.16 多态（核心）

- 编译时多态：函数重载、模板。

- 运行时多态：通过虚函数。

- 示例：

  cpp

  ```
  class Animal { public: virtual void speak() { cout << "??" << endl; } };
  class Dog : public Animal { public: void speak() override { cout << "Woof" << endl; } };
  class Cat : public Animal { public: void speak() override { cout << "Meow" << endl; } };
  void letSpeak(Animal* a) { a->speak(); }
  int main() {
      Dog d; Cat c;
      letSpeak(&d); // Woof
      letSpeak(&c); // Meow
  }
  ```

  

### 2.17 友元（了解）

- 友元函数：非成员函数可以访问类的私有成员。

- 友元类：整个类作为友元。

- 友元成员函数：某个类的成员函数作为另一个类的友元。

- 常用场景：重载`<<`和`>>`。

  cpp

  ```
  class Point {
      int x, y;
  public:
      friend std::ostream& operator<<(std::ostream& os, const Point& p);
  };
  std::ostream& operator<<(std::ostream& os, const Point& p) {
      os << "(" << p.x << "," << p.y << ")"; return os;
  }
  ```

  

### 2.18 模板（重要，STL基础）

- **函数模板**：

  cpp

  ```
  template <typename T>
  T max(T a, T b) { return a > b ? a : b; }
  ```

  

- **类模板**：

  cpp

  ```
  template <class T>
  class Stack {
      std::vector<T> data;
  public:
      void push(const T& val) { data.push_back(val); }
      T pop() { T top = data.back(); data.pop_back(); return top; }
  };
  ```

  

- **模板特化**：为特定类型提供特殊实现。

  cpp

  ```
  template <>
  class Stack<bool> { /* 位压缩实现 */ };
  ```

  

### 2.19 STL常用容器（非常重要）

- **vector**：动态数组，支持随机访问，尾部增删快，中间增删慢。
- **list**：双向链表，任意位置增删快，不支持随机访问。
- **set/map**：有序关联容器，基于红黑树，插入查找O(log n)。`set`只有键，`map`是键值对。
- **unordered_set/unordered_map**：哈希表，平均O(1)，无序。
- 迭代器：`begin()`、`end()`，用于遍历。
- 算法：`sort`、`find`、`copy`等，在`<algorithm>`中。

### 2.20 异常处理（了解）

- 基本语法：

  cpp

  ```
  try {
      // 可能抛出异常的代码
      if (error) throw std::runtime_error("something wrong");
  } catch (const std::exception& e) {
      std::cerr << e.what() << std::endl;
  }
  ```

  

- 自定义异常：继承`std::exception`，重写`what()`。

- **注意**：QT中很少用C++异常，因为信号槽机制已经提供了安全的错误处理方式。但文件、网络等底层操作可能抛出异常。

------

## P3 记事本项目（全流程代码+解释）

### 3.1 项目创建

- 选择`Qt Widgets Application`，基类选择`QMainWindow`（带菜单栏）或`QWidget`（简单窗口）。课程选择`QWidget`。
- 勾选“生成窗体”，自动生成`.ui`文件。

### 3.2 UI设计（Qt Designer）

- **控件布局**：

  - 顶部：`QHBoxLayout`放置“打开”“保存”“关闭”按钮、编码选择`QComboBox`。
  - 中间：`QTextEdit`（设置`font`、`lineWrapMode`等）。
  - 底部：`QLabel`显示行列号。

- **样式表示例**（设置按钮圆角+背景色）：

  css

  ```
  QPushButton {
      background-color: #4CAF50;
      border-radius: 5px;
      color: white;
      padding: 5px;
  }
  QPushButton:hover { background-color: #45a049; }
  ```

  ```
      this->setLayout(ui->verticalLayout);
  ```

### 3.3 核心类成员变量

- `QFile file;`：当前打开的文件对象。
- `QString currentFilePath;`：当前文件路径。
- `QTextCodec *codec;`：用于编码转换。

### 3.4 打开文件功能

cpp

```
void Widget::on_btnOpen_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, "打开文件", "", "文本文件 (*.txt)");
    if (fileName.isEmpty()) return;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "错误", "无法打开文件");
        return;
    }
    // 读取文件内容
    QTextStream in(&file);
    QString codecName = ui->comboCodec->currentText();
    QTextCodec *codec = QTextCodec::codecForName(codecName.toUtf8());
    if (codec) in.setCodec(codec);
    ui->textEdit->setPlainText(in.readAll());
    file.close();
    currentFilePath = fileName;
    this->setWindowTitle(currentFilePath + " - 记事本");
}
```



### 3.5 保存文件功能

cpp

```
void Widget::on_btnSave_clicked() {
    if (currentFilePath.isEmpty()) {
        currentFilePath = QFileDialog::getSaveFileName(this, "保存文件", "", "文本文件 (*.txt)");
        if (currentFilePath.isEmpty()) return;
    }
    QFile file(currentFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "错误", "无法保存文件");
        return;
    }
    QTextStream out(&file);
    QString codecName = ui->comboCodec->currentText();
    QTextCodec *codec = QTextCodec::codecForName(codecName.toUtf8());
    if (codec) out.setCodec(codec);
    out << ui->textEdit->toPlainText();
    file.close();
    this->setWindowTitle(currentFilePath + " - 记事本");
}
```



### 3.6 显示行列号

- 连接`QTextEdit`的`cursorPositionChanged()`信号。

- 槽函数：

  cpp

  ```
  void Widget::updateCursorPosition() {
      QTextCursor cursor = ui->textEdit->textCursor();
      int line = cursor.blockNumber() + 1;
      int col = cursor.columnNumber() + 1;
      ui->labelPos->setText(QString("行: %1 列: %2").arg(line).arg(col));
  }
  ```

  

### 3.7 当前行高亮

- 在`cursorPositionChanged()`槽中更新高亮。

  cpp

  ```
  void Widget::highlightCurrentLine() {
      QList<QTextEdit::ExtraSelection> extraSelections;
      if (!ui->textEdit->isReadOnly()) {
          QTextEdit::ExtraSelection selection;
          QColor lineColor = QColor(Qt::yellow).lighter(160);
          selection.format.setBackground(lineColor);
          selection.format.setProperty(QTextFormat::FullWidthSelection, true);
          selection.cursor = ui->textEdit->textCursor();
          selection.cursor.clearSelection();
          extraSelections.append(selection);
      }
      ui->textEdit->setExtraSelections(extraSelections);
  }
  ```

  

### 3.8 Ctrl+滚轮缩放字体

- 给`textEdit`安装事件过滤器。

  cpp

  ```
  ui->textEdit->installEventFilter(this);
  ```

  

- 重写`eventFilter`：

  cpp

  ```
  bool Widget::eventFilter(QObject *obj, QEvent *event) {
      if (obj == ui->textEdit && event->type() == QEvent::Wheel) {
          QWheelEvent *wheel = static_cast<QWheelEvent*>(event);
          if (QApplication::keyboardModifiers() & Qt::ControlModifier) {
              QFont font = ui->textEdit->font();
              int size = font.pointSize();
              size += (wheel->angleDelta().y() > 0) ? 1 : -1;
              if (size >= 6 && size <= 72) {
                  font.setPointSize(size);
                  ui->textEdit->setFont(font);
              }
              return true;
          }
      }
      return QWidget::eventFilter(obj, event);
  }
  ```

  

### 3.9 快捷键

cpp

```
// 在构造函数中
QShortcut *shortcutOpen = new QShortcut(QKeySequence::Open, this);
connect(shortcutOpen, &QShortcut::activated, this, &Widget::on_btnOpen_clicked);
QShortcut *shortcutSave = new QShortcut(QKeySequence::Save, this);
connect(shortcutSave, &QShortcut::activated, this, &Widget::on_btnSave_clicked);
```



### 3.10 关闭时提示保存

cpp

```
void Widget::closeEvent(QCloseEvent *event) {
    if (ui->textEdit->document()->isModified()) {
        QMessageBox::StandardButton ret = QMessageBox::warning(this, "提示", "文档已修改，是否保存？",
            QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Save) {
            on_btnSave_clicked();
            event->accept();
        } else if (ret == QMessageBox::Discard) {
            event->accept();
        } else {
            event->ignore();
        }
    } else {
        event->accept();
    }
}
```



------

## P4 串口调试助手（核心要点）

### 4.1 添加串口模块

- 在`.pro`文件中：`QT += serialport`

### 4.2 扫描可用串口

cpp

```
foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
    ui->comboPort->addItem(info.portName());
}
```



### 4.3 打开串口

cpp

```
void Widget::on_btnOpen_clicked() {
    serial = new QSerialPort(this);
    serial->setPortName(ui->comboPort->currentText());
    serial->setBaudRate(ui->comboBaud->currentText().toInt());
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    if (serial->open(QIODevice::ReadWrite)) {
        connect(serial, &QSerialPort::readyRead, this, &Widget::readData);
        ui->btnOpen->setEnabled(false);
        ui->btnClose->setEnabled(true);
    } else {
        QMessageBox::critical(this, "错误", "无法打开串口");
    }
}
```



### 4.4 读取数据

cpp

```
void Widget::readData() {
    QByteArray data = serial->readAll();
    if (ui->checkHex->isChecked()) {
        ui->textReceive->append(data.toHex(' ').toUpper());
    } else {
        ui->textReceive->append(QString::fromUtf8(data));
    }
}
```



### 4.5 发送数据

cpp

```
void Widget::on_btnSend_clicked() {
    QString text = ui->textSend->toPlainText();
    if (ui->checkSendHex->isChecked()) {
        QByteArray hexData = QByteArray::fromHex(text.toUtf8());
        serial->write(hexData);
    } else {
        serial->write(text.toUtf8());
    }
}
```



### 4.6 定时发送

cpp

```
QTimer *timer = new QTimer(this);
timer->setInterval(ui->spinInterval->value());
connect(timer, &QTimer::timeout, this, &Widget::on_btnSend_clicked);
connect(ui->btnAutoSend, &QPushButton::toggled, timer, &QTimer::setEnabled);
```



------

## P5 网络调试助手（详细代码）

### 5.1 添加network模块

- `.pro`文件：`QT += network`

### 5.2 TCP服务端

#### 5.2.1 启动服务器

cpp

```
void ServerWidget::on_btnListen_clicked() {
    quint16 port = ui->lineEditPort->text().toUShort();
    tcpServer = new QTcpServer(this);
    connect(tcpServer, &QTcpServer::newConnection, this, &ServerWidget::onNewConnection);
    if (!tcpServer->listen(QHostAddress::Any, port)) {
        QMessageBox::critical(this, "错误", "监听失败");
        return;
    }
    ui->btnListen->setEnabled(false);
    ui->btnStop->setEnabled(true);
}
```



#### 5.2.2 处理新连接

cpp

```
void ServerWidget::onNewConnection() {
    QTcpSocket *client = tcpServer->nextPendingConnection();
    QString peer = client->peerAddress().toString() + ":" + QString::number(client->peerPort());
    ui->comboClients->addItem(peer);
    clients[peer] = client;
    connect(client, &QTcpSocket::readyRead, this, &ServerWidget::onReadyRead);
    connect(client, &QTcpSocket::disconnected, this, &ServerWidget::onDisconnected);
}
```



#### 5.2.3 读取数据

cpp

```
void ServerWidget::onReadyRead() {
    QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
    QByteArray data = client->readAll();
    QString peer = client->peerAddress().toString() + ":" + QString::number(client->peerPort());
    ui->textBrowser->append(QString("[%1] 收到: %2").arg(peer).arg(QString::fromUtf8(data)));
}
```



#### 5.2.4 发送数据

cpp

```
void ServerWidget::on_btnSend_clicked() {
    QString currentClient = ui->comboClients->currentText();
    if (clients.contains(currentClient)) {
        QByteArray data = ui->textSend->toPlainText().toUtf8();
        clients[currentClient]->write(data);
        ui->textBrowser->append(QString("[服务端] 发送: %1").arg(QString::fromUtf8(data)));
    }
}
```



### 5.3 TCP客户端

#### 5.3.1 连接服务器

cpp

```
void ClientWidget::on_btnConnect_clicked() {
    QString ip = ui->lineEditIP->text();
    quint16 port = ui->lineEditPort->text().toUShort();
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, &QTcpSocket::connected, this, &ClientWidget::onConnected);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &ClientWidget::onReadyRead);
    connect(tcpSocket, &QTcpSocket::disconnected, this, &ClientWidget::onDisconnected);
    tcpSocket->connectToHost(ip, port);
}
```



#### 5.3.2 接收数据

cpp

```
void ClientWidget::onReadyRead() {
    QByteArray data = tcpSocket->readAll();
    ui->textBrowser->append(QString("服务端: %1").arg(QString::fromUtf8(data)));
}
```



#### 5.3.3 发送数据

cpp

```
void ClientWidget::on_btnSend_clicked() {
    QByteArray data = ui->textSend->toPlainText().toUtf8();
    tcpSocket->write(data);
    ui->textBrowser->append(QString("客户端: %1").arg(QString::fromUtf8(data)));
}
```



### 5.4 颜色区分消息

cpp

```
void ClientWidget::appendMessage(const QString &msg, const QColor &color) {
    QTextCursor cursor = ui->textBrowser->textCursor();
    cursor.movePosition(QTextCursor::End);
    QTextCharFormat fmt;
    fmt.setForeground(QBrush(color));
    cursor.insertText(msg, fmt);
    cursor.insertText("\n");
    ui->textBrowser->setTextCursor(cursor);
}
```



------

## P6 自定义控件（仪表盘深度讲解）

### 6.1 绘制原理

- 重写`paintEvent`，所有绘图操作在`QPainter`上进行。
- 启用抗锯齿：`painter.setRenderHint(QPainter::Antialiasing);`
- 使用`translate`移动原点，`rotate`旋转坐标系，简化绘制。

### 6.2 绘制刻度盘

- 范围0~240（速度值），对应角度150°~390°（跨度240°）。所以每单位速度对应1°。
- 刻度线：循环60次，每旋转4°画一次。每5次画长线，其余短线。
- 数字：通过`qCos`/`qSin`计算位置，平移坐标系后绘制。

### 6.3 指针绘制

- 用`QPolygon`定义三角形指针，`painter.drawPolygon`。
- 根据当前速度值旋转指针：`painter.rotate(150 + speedValue * 1.0)`。

### 6.4 动态更新

- 使用`QTimer`周期性改变速度值，并调用`update()`触发重绘。
- 速度值可以模拟正弦变化或从0到240来回扫描。

### 6.5 完整代码结构（头文件）

cpp

```
class Dashboard : public QWidget {
    Q_OBJECT
private:
    int speed;          // 当前速度 0-240
    QTimer *timer;
    bool increasing;
public:
    Dashboard(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *event) override;
private slots:
    void updateSpeed();
};
```



### 6.6 部分绘制代码

cpp

```
void Dashboard::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    int side = qMin(width(), height());
    painter.setViewport((width() - side)/2, (height() - side)/2, side, side);
    painter.setWindow(-100, -100, 200, 200);  // 逻辑坐标 -100..100

    // 绘制外圆
    painter.drawEllipse(-90, -90, 180, 180);
    // 绘制刻度...
    // 绘制指针
    painter.save();
    painter.rotate(150 + speed * 1.0); // 起点150°，每单位1°
    painter.drawConvexPolygon(pointerPoints, 3);
    painter.restore();
}
```



------

## P7 天气预报项目（HTTP+JSON详细）

### 7.1 添加网络模块

- `.pro`添加`QT += network`

### 7.2 发送HTTP请求

cpp

```
QNetworkAccessManager *manager = new QNetworkAccessManager(this);
connect(manager, &QNetworkAccessManager::finished, this, &WeatherWidget::onReplyFinished);
QUrl url("http://v1.yiketianqi.com/api?city=福州&appid=123456&appsecret=abc");
manager->get(QNetworkRequest(url));
```



### 7.3 解析JSON响应

cpp

```
void WeatherWidget::onReplyFinished(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << reply->errorString();
        return;
    }
    QByteArray data = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject root = doc.object();

    // 解析当前天气
    QString city = root["city"].toString();
    QString wea = root["wea"].toString();
    QString tem = root["tem"].toString();
    QString win = root["win"].toString();
    QString air = root["air_level"].toString();

    // 更新UI
    ui->labelCity->setText(city);
    ui->labelTemp->setText(tem + "°C");
    ui->labelWeather->setText(wea);
    ui->labelWind->setText(win);
    ui->labelAir->setText(air);

    // 设置天气图标
    QPixmap pixmap(QString(":/icons/%1.png").arg(wea));
    ui->labelIcon->setPixmap(pixmap);

    // 解析未来7天预报（数组）
    if (root.contains("data") && root["data"].isArray()) {
        QJsonArray forecast = root["data"].toArray();
        for (int i = 0; i < forecast.size(); ++i) {
            QJsonObject day = forecast[i].toObject();
            QString date = day["date"].toString();
            QString dayTemp = day["tem1"].toString();
            QString nightTemp = day["tem2"].toString();
            // 显示到列表...
        }
    }
    reply->deleteLater();
}
```



### 7.4 无边框窗口与拖动

- 设置窗口标志：`setWindowFlags(Qt::FramelessWindowHint);`

- 重写鼠标事件：

  cpp

  ```
  void WeatherWidget::mousePressEvent(QMouseEvent *event) {
      if (event->button() == Qt::LeftButton) {
          dragPos = event->globalPos() - frameGeometry().topLeft();
          event->accept();
      }
  }
  void WeatherWidget::mouseMoveEvent(QMouseEvent *event) {
      if (event->buttons() & Qt::LeftButton) {
          move(event->globalPos() - dragPos);
          event->accept();
      }
  }
  ```

  

### 7.5 右键退出菜单

cpp

```
void WeatherWidget::contextMenuEvent(QContextMenuEvent *event) {
    QMenu menu;
    menu.addAction("退出", this, &QWidget::close);
    menu.exec(event->globalPos());
}
```



### 7.6 样式表示例（圆角背景）

css

```
QWidget#centralWidget {
    background-color: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                                      stop:0 #0a0f2a, stop:1 #1a2340);
    border-radius: 10px;
}
QLabel {
    color: white;
    font-family: "Microsoft YaHei";
    font-size: 14px;
}
```



------

## P8 Ubuntu搭建QT环境（详细命令）

### 8.1 安装VMware Tools（复制粘贴增强）

bash

```
sudo apt install open-vm-tools-desktop
sudo reboot
```



### 8.2 安装编译器和依赖

bash

```
sudo apt update
sudo apt install build-essential
sudo apt install libgl1-mesa-dev   # OpenGL库
```



### 8.3 安装QT5.12.9

- 下载离线安装包，给予执行权限`chmod +x qt-opensource-linux-x64-5.12.9.run`

- 运行前建议断开网络，避免登录。

- 选择安装路径（例如`/opt/Qt5.12.9`），选择组件：GCC 64-bit、Qt Charts等。

- 添加环境变量（可选）：

  bash

  ```
  echo 'export PATH=/opt/Qt5.12.9/5.12.9/gcc_64/bin:$PATH' >> ~/.bashrc
  source ~/.bashrc
  ```

  

### 8.4 中文输入法

- 安装fcitx和拼音：

  bash

  ```
  sudo apt install fcitx fcitx-sunpinyin
  ```

  

- 在系统设置中，将fcitx设为默认输入法，重启。

- 从网上下载`libfcitxplatforminputcontextplugin.so`，复制到两个位置：

  bash

  ```
  cp libfcitxplatforminputcontextplugin.so /opt/Qt5.12.9/Tools/QtCreator/lib/Qt/plugins/platforminputcontexts/
  cp libfcitxplatforminputcontextplugin.so /opt/Qt5.12.9/5.12.9/gcc_64/plugins/platforminputcontexts/
  chmod 777 /opt/Qt5.12.9/Tools/QtCreator/lib/Qt/plugins/platforminputcontexts/libfcitxplatforminputcontextplugin.so
  chmod 777 /opt/Qt5.12.9/5.12.9/gcc_64/plugins/platforminputcontexts/libfcitxplatforminputcontextplugin.so
  ```

  

### 8.5 共享文件夹

- VMware设置共享文件夹，路径如`shared`

- 挂载到Ubuntu：

  bash

  ```
  sudo vmhgfs-fuse .host:/shared /mnt/shared -o allow_other
  ```

  

- 或添加到`/etc/fstab`自动挂载。

------

## 总结

这份超详细笔记涵盖了文档中所有重点，并补充了代码原理和额外说明。学习路径建议：

1. 先通读C++部分，重点掌握类、继承、多态、STL容器。
2. 按照项目顺序逐个实现：记事本 → 串口助手 → 网络助手 → 仪表盘 → 天气预报。
3. 每个项目自己从头写一遍，不要直接复制代码，遇到问题再查笔记。
4. 学会使用Qt帮助文档（F1）和调试技巧（断点、qDebug）。

## P1 QT 介绍与环境搭建

### 1.1 QT 简介
* **定义**：Qt 是一个由 C++ 编写的跨平台图形用户界面（GUI）应用程序开发框架。
* **跨平台特性**：一套代码，通过不同平台的编译器编译后，即可运行在 Windows、Linux、macOS、Android、iOS 及嵌入式 Linux 系统上。
* **版本与授权**：
  * **商业版**：提供闭源商业授权及官方技术支持。
  * **开源版**：遵守 LGPL/GPL 协议。工业开发中通常采用动态链接方式使用其基础库，即可合法免费商用。
* **技术演进**：
  * **Qt 5.x**：引入了 QML 和 Qt Quick，极大地优化了二维动画和移动端性能。本课程使用企业级稳定版本 **Qt 5.12.9**。
  * **Qt 6.x**：优化了下一代 3D 图形 API 抽象层（RHI），是未来的技术趋势。

### 1.2 QT 安装 (Windows)
* **断网离线安装法**：下载官方离线安装包 `qt-opensource-windows-x86-5.12.9.exe`。启动安装程序前，必须**切断计算机网络**（拔掉网线或禁用网卡），从而直接跳过强制登录 Qt 账户的步骤。
* **核心组件勾选规范**：
  * `MinGW 7.3.0 64-bit`（必选）：Windows 下的 GCC 编译器套件。
  * `Sources`（源码包）：方便后续调试时点击跳转查看 Qt 底层 C++ 源码。
  * `Qt Charts`（图表模块）：用于绘制工业折线图、波形图、饼图。
  * `Qt Virtual Keyboard`（虚拟键盘）：用于嵌入式触摸屏的软键盘输入。

### 1.3 Qt Creator 使用基本介绍
* **工程目录结构**：
  * `.pro` 文件：项目的管理配置文件（类似于 Makefile 或 CMakeLists.txt）。
  * `Headers`（`.h`）：存放类的声明、成员变量和方法签名。
  * `Sources`（`.cpp`）：存放业务逻辑的具体代码实现。
  * `Forms`（`.ui`）：可视化界面布局文件，由布局设计器（Qt Designer）打开。
* **构建目录分离（Shadow Build）**：Qt 默认开启影子构建，编译生成的 `.obj`、`.exe` 文件会存放在与源码目录同级的独立构建文件夹中，防止污染源码。

---

1. ## P2 C++基础（全面讲解）

   > 本章节是QT开发的预科，但有些内容QT中极少用到（如多重继承、虚继承、运算符重载），文档都列出了，我会标注重点程度。

   ### 2.1 命名空间（重要）

   - **目的**：避免全局命名冲突。

   - **定义**：

     cpp

     ```
     namespace MyLib {
         void func() { ... }
     }
     ```

     

   - **使用**：

     - 作用域限定：`MyLib::func()`
     - 引入整个命名空间：`using namespace MyLib;`（小项目可用，头文件中避免使用）
     - 引入特定符号：`using MyLib::func;`

   - **标准库命名空间**：`std`，包含`cout`、`vector`、`string`等。

   ### 2.2 输入输出（重要）

   - `std::cin` >> 变量

   - `std::cout` << 内容 << std::endl（换行+刷新缓冲区）

   - `std::cerr`：无缓冲错误输出

   - `std::clog`：有缓冲日志输出

   - 示例：

     cpp

     ```
     #include <iostream>
     int main() {
         int age;
         std::cout << "Enter age: ";
         std::cin >> age;
         std::cerr << "If age is wrong, you'll see this immediately." << std::endl;
         return 0;
     }
     ```

     

   ### 2.3 基本变量类型（了解）

   - 整型：`int`, `short`, `long`, `long long`, 以及`unsigned`版本。

   - 浮点：`float`（~7位精度）、`double`（~15位）、`long double`（更高精度，平台相关）

   - 字符：`char`（1字节，ASCII）、`wchar_t`（宽字符，用于Unicode）、C++11新增`char16_t`、`char32_t`。

   - 布尔：`bool`（true/false）

   - **查看类型范围**：`<climits>`中的`INT_MAX`、`LONG_MIN`等。

   - **宽字符示例**（输出中文）：

     cpp

     ```
     #include <iostream>
     #include <locale>
     int main() {
         setlocale(LC_ALL, "");  // 或者 std::locale::global(std::locale(""));
         wchar_t wstr[] = L"你好世界";
         std::wcout << wstr << std::endl;
         return 0;
     }
     ```

     

   ### 2.4 流程控制（重要）

   - `if-else if-else`、`switch-case-default`（每个case后要break，否则穿透）。
   - 循环：`for`、`while`、`do-while`。
   - 跳转：`break`、`continue`、`goto`（极不推荐）。

   ### 2.5 函数（重要）

   - 声明与定义分离：声明放在头文件，定义放在cpp文件。
   - 参数传递：值传递（拷贝）、指针传递（传递地址）、引用传递（别名，更安全）。
   - **默认参数**：从右向左提供默认值。
   - **函数重载**：同一作用域，函数名相同，参数列表不同（类型、个数、顺序），返回类型不能作为重载依据。

   ### 2.6 内联函数（了解）

   - 建议编译器将函数体插入调用点，消除函数调用开销。
   - 适用于短小、频繁调用的函数（如getter/setter）。
   - 定义通常放在头文件中。
   - 现代编译器会智能决定是否内联，`inline`只是建议。

   ### 2.7 Lambda表达式（非常重要，QT中大量使用）

   - **语法**：`[捕获](参数) -> 返回类型 { 函数体 }`

   - **捕获方式**：

     - `[]`：不捕获任何外部变量
     - `[=]`：值捕获所有外部变量（只读）
     - `[&]`：引用捕获所有外部变量（可修改）
     - `[x, &y]`：混合捕获

   - **示例**：

     cpp

     ```
     int factor = 2;
     auto times = [factor](int a) { return a * factor; };
     std::cout << times(5); // 10
     ```

     

   - **在QT信号槽中**：

     cpp

     ```
     QPushButton *btn = new QPushButton("Click");
     connect(btn, &QPushButton::clicked, [=](){
         qDebug() << "Button clicked";
     });
     ```

     

   ### 2.8 数组与字符串（重要）

   - C风格数组：固定大小，`int arr[10];`，容易越界。

   - C风格字符串：`char str[] = "hello";`，以`\0`结尾，操作函数`strcpy`、`strlen`等，不安全。

   - **C++ string**：

     cpp

     ```
     #include <string>
     std::string s1 = "Hello";
     std::string s2 = " World";
     std::string s3 = s1 + s2;  // "Hello World"
     int len = s3.length();
     const char* cstr = s3.c_str();  // 转为C风格
     ```

     

   ### 2.9 类（核心）

   - **从结构体到类**：

     - C结构体只有数据，函数需要用函数指针模拟（繁琐）。
     - C++类将数据和操作封装在一起。

   - **成员访问**：对象用`.`，指针用`->`。

   - **构造函数**：与类同名，无返回值，可重载。

     - 默认构造函数（无参数）。
     - 有参构造函数：用于初始化成员。
     - 拷贝构造函数：`ClassName(const ClassName& other)`。

   - **析构函数**：`~ClassName()`，无参数无返回值，用于释放资源。

   - **初始化列表**：

     cpp

     ```
     class Student {
     private:
         const int id;   // const成员必须用初始化列表
         std::string name;
     public:
         Student(int i, const std::string& n) : id(i), name(n) {}
     };
     ```

     

   - **this指针**：指向当前对象，用于区分成员和参数，或返回对象引用实现链式调用。

   ### 2.10 权限（核心）

   - public：任何地方可访问。
   - protected：类内和派生类可访问。
   - private：仅类内可访问。
   - **class默认private，struct默认public**。

   ### 2.11 引用（核心）

   - 定义：`int &ref = var;`，ref是var的别名，必须初始化，不能更改指向。

   - 常用作函数参数（避免拷贝，且可修改实参）：

     cpp

     ```
     void swap(int &a, int &b) { int t=a; a=b; b=t; }
     ```

     

   - 可作为返回值（返回局部变量的引用是未定义行为，返回静态成员或对象成员的引用是安全的）。

   - **与指针区别**：引用不为空、无需解引用、不能重新绑定。

   ### 2.12 运算符重载（了解，QT中较少自定义）

   - 可重载的运算符：`+ - * / = == != < > [] () << >>`等。

   - 不能重载的：`::`、`.`、`.*`、`?:`、`sizeof`等。

   - 示例：复数加法

     cpp

     ```
     class Complex {
         double real, imag;
     public:
         Complex operator+(const Complex& other) const {
             return Complex(real + other.real, imag + other.imag);
         }
     };
     ```

     

   ### 2.13 拷贝控制（重点理解）

   - **深拷贝 vs 浅拷贝**：

     - 浅拷贝：只复制指针值，多个对象指向同一堆内存，析构时多次delete导致崩溃。
     - 深拷贝：分配新内存，复制内容。

   - **规则三则**：若自定义了析构函数、拷贝构造函数、拷贝赋值运算符中的任何一个，则通常需要实现所有三个。

   - **禁用拷贝**：C++11中使用`= delete`。

     cpp

     ```
     class NonCopyable {
     public:
         NonCopyable(const NonCopyable&) = delete;
         NonCopyable& operator=(const NonCopyable&) = delete;
     };
     ```

     

   ### 2.14 静态成员（重要）

   - 静态成员变量：属于类而非对象，所有对象共享一份，必须在类外单独定义（初始化）。

   - 静态成员函数：只能访问静态成员，不需要对象即可调用。

   - 典型用途：单例模式、对象计数。

     cpp

     ```
     class Counter {
         static int count;
     public:
         Counter() { count++; }
         static int getCount() { return count; }
     };
     int Counter::count = 0;
     ```

     

   ### 2.15 继承（核心）

   - 语法：`class Derived : public Base`
   - 三种继承方式：
     - public继承：基类public→派生类public，protected→protected，private不可访问。
     - protected继承：基类public/protected→派生类protected。
     - private继承：基类public/protected→派生类private。
   - 构造顺序：先基类构造，再派生类构造；析构顺序相反。
   - **虚函数**：在基类中声明`virtual`，派生类重写。通过基类指针/引用调用时，动态绑定到实际对象类型。
   - **override**：C++11关键字，显式表示重写基类虚函数，帮助编译器检查。
   - **纯虚函数**：`virtual void func() = 0;`，使类成为抽象类，不能实例化。
   - **多重继承**：一个类有多个直接基类，可能导致菱形继承问题。
   - **虚继承**：解决菱形继承，使用`virtual`关键字，确保最派生类只有一个基类子对象。

   ### 2.16 多态（核心）

   - 编译时多态：函数重载、模板。

   - 运行时多态：通过虚函数。

   - 示例：

     cpp

     ```
     class Animal { public: virtual void speak() { cout << "??" << endl; } };
     class Dog : public Animal { public: void speak() override { cout << "Woof" << endl; } };
     class Cat : public Animal { public: void speak() override { cout << "Meow" << endl; } };
     void letSpeak(Animal* a) { a->speak(); }
     int main() {
         Dog d; Cat c;
         letSpeak(&d); // Woof
         letSpeak(&c); // Meow
     }
     ```

     

   ### 2.17 友元（了解）

   - 友元函数：非成员函数可以访问类的私有成员。

   - 友元类：整个类作为友元。

   - 友元成员函数：某个类的成员函数作为另一个类的友元。

   - 常用场景：重载`<<`和`>>`。

     cpp

     ```
     class Point {
         int x, y;
     public:
         friend std::ostream& operator<<(std::ostream& os, const Point& p);
     };
     std::ostream& operator<<(std::ostream& os, const Point& p) {
         os << "(" << p.x << "," << p.y << ")"; return os;
     }
     ```

     

   ### 2.18 模板（重要，STL基础）

   - **函数模板**：

     cpp

     ```
     template <typename T>
     T max(T a, T b) { return a > b ? a : b; }
     ```

     

   - **类模板**：

     cpp

     ```
     template <class T>
     class Stack {
         std::vector<T> data;
     public:
         void push(const T& val) { data.push_back(val); }
         T pop() { T top = data.back(); data.pop_back(); return top; }
     };
     ```

     

   - **模板特化**：为特定类型提供特殊实现。

     cpp

     ```
     template <>
     class Stack<bool> { /* 位压缩实现 */ };
     ```

     

   ### 2.19 STL常用容器（非常重要）

   - **vector**：动态数组，支持随机访问，尾部增删快，中间增删慢。
   - **list**：双向链表，任意位置增删快，不支持随机访问。
   - **set/map**：有序关联容器，基于红黑树，插入查找O(log n)。`set`只有键，`map`是键值对。
   - **unordered_set/unordered_map**：哈希表，平均O(1)，无序。
   - 迭代器：`begin()`、`end()`，用于遍历。
   - 算法：`sort`、`find`、`copy`等，在`<algorithm>`中。

   ### 2.20 异常处理（了解）

   - 基本语法：

     cpp

     ```
     try {
         // 可能抛出异常的代码
         if (error) throw std::runtime_error("something wrong");
     } catch (const std::exception& e) {
         std::cerr << e.what() << std::endl;
     }
     ```

     

   - 自定义异常：继承`std::exception`，重写`what()`。

   - **注意**：QT中很少用C++异常，因为信号槽机制已经提供了安全的错误处理方式。但文件、网络等底层操作可能抛出异常。

   ------

   ## P3 记事本项目（全流程代码+解释）

   ### 3.1 项目创建

   - 选择`Qt Widgets Application`，基类选择`QMainWindow`（带菜单栏）或`QWidget`（简单窗口）。课程选择`QWidget`。
   - 勾选“生成窗体”，自动生成`.ui`文件。

   ### 3.2 UI设计（Qt Designer）

   - **控件布局**：

     - 顶部：`QHBoxLayout`放置“打开”“保存”“关闭”按钮、编码选择`QComboBox`。
     - 中间：`QTextEdit`（设置`font`、`lineWrapMode`等）。
     - 底部：`QLabel`显示行列号。

   - **样式表示例**（设置按钮圆角+背景色）：

     css

     ```
     QPushButton {
         background-color: #4CAF50;
         border-radius: 5px;
         color: white;
         padding: 5px;
     }
     QPushButton:hover { background-color: #45a049; }
     ```

     

   ### 3.3 核心类成员变量

   - `QFile file;`：当前打开的文件对象。
   - `QString currentFilePath;`：当前文件路径。
   - `QTextCodec *codec;`：用于编码转换。

   ### 3.4 打开文件功能

   cpp

   ```
   void Widget::on_btnOpen_clicked() {
       QString fileName = QFileDialog::getOpenFileName(this, "打开文件", "", "文本文件 (*.txt)");
       if (fileName.isEmpty()) return;
       QFile file(fileName);
       if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
           QMessageBox::warning(this, "错误", "无法打开文件");
           return;
       }
       // 读取文件内容
       QTextStream in(&file);
       QString codecName = ui->comboCodec->currentText();
       QTextCodec *codec = QTextCodec::codecForName(codecName.toUtf8());
       if (codec) in.setCodec(codec);
       ui->textEdit->setPlainText(in.readAll());
       file.close();
       currentFilePath = fileName;
       this->setWindowTitle(currentFilePath + " - 记事本");
   }
   ```

   

   ### 3.5 保存文件功能

   cpp

   ```
   void Widget::on_btnSave_clicked() {
       if (currentFilePath.isEmpty()) {
           currentFilePath = QFileDialog::getSaveFileName(this, "保存文件", "", "文本文件 (*.txt)");
           if (currentFilePath.isEmpty()) return;
       }
       QFile file(currentFilePath);
       if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
           QMessageBox::warning(this, "错误", "无法保存文件");
           return;
       }
       QTextStream out(&file);
       QString codecName = ui->comboCodec->currentText();
       QTextCodec *codec = QTextCodec::codecForName(codecName.toUtf8());
       if (codec) out.setCodec(codec);
       out << ui->textEdit->toPlainText();
       file.close();
       this->setWindowTitle(currentFilePath + " - 记事本");
   }
   ```

   

   ### 3.6 显示行列号

   - 连接`QTextEdit`的`cursorPositionChanged()`信号。

   - 槽函数：

     cpp

     ```
     void Widget::updateCursorPosition() {
         QTextCursor cursor = ui->textEdit->textCursor();
         int line = cursor.blockNumber() + 1;
         int col = cursor.columnNumber() + 1;
         ui->labelPos->setText(QString("行: %1 列: %2").arg(line).arg(col));
     }
     ```

     

   ### 3.7 当前行高亮

   - 在`cursorPositionChanged()`槽中更新高亮。

     cpp

     ```
     void Widget::highlightCurrentLine() {
         QList<QTextEdit::ExtraSelection> extraSelections;
         if (!ui->textEdit->isReadOnly()) {
             QTextEdit::ExtraSelection selection;
             QColor lineColor = QColor(Qt::yellow).lighter(160);
             selection.format.setBackground(lineColor);
             selection.format.setProperty(QTextFormat::FullWidthSelection, true);
             selection.cursor = ui->textEdit->textCursor();
             selection.cursor.clearSelection();
             extraSelections.append(selection);
         }
         ui->textEdit->setExtraSelections(extraSelections);
     }
     ```

     

   ### 3.8 Ctrl+滚轮缩放字体

   - 给`textEdit`安装事件过滤器。

     cpp

     ```
     ui->textEdit->installEventFilter(this);
     ```

     

   - 重写`eventFilter`：

     cpp

     ```
     bool Widget::eventFilter(QObject *obj, QEvent *event) {
         if (obj == ui->textEdit && event->type() == QEvent::Wheel) {
             QWheelEvent *wheel = static_cast<QWheelEvent*>(event);
             if (QApplication::keyboardModifiers() & Qt::ControlModifier) {
                 QFont font = ui->textEdit->font();
                 int size = font.pointSize();
                 size += (wheel->angleDelta().y() > 0) ? 1 : -1;
                 if (size >= 6 && size <= 72) {
                     font.setPointSize(size);
                     ui->textEdit->setFont(font);
                 }
                 return true;
             }
         }
         return QWidget::eventFilter(obj, event);
     }
     ```

     

   ### 3.9 快捷键

   cpp

   ```
   // 在构造函数中
   QShortcut *shortcutOpen = new QShortcut(QKeySequence::Open, this);
   connect(shortcutOpen, &QShortcut::activated, this, &Widget::on_btnOpen_clicked);
   QShortcut *shortcutSave = new QShortcut(QKeySequence::Save, this);
   connect(shortcutSave, &QShortcut::activated, this, &Widget::on_btnSave_clicked);
   ```

   

   ### 3.10 关闭时提示保存

   cpp

   ```
   void Widget::closeEvent(QCloseEvent *event) {
       if (ui->textEdit->document()->isModified()) {
           QMessageBox::StandardButton ret = QMessageBox::warning(this, "提示", "文档已修改，是否保存？",
               QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
           if (ret == QMessageBox::Save) {
               on_btnSave_clicked();
               event->accept();
           } else if (ret == QMessageBox::Discard) {
               event->accept();
           } else {
               event->ignore();
           }
       } else {
           event->accept();
       }
   }
   ```

   

   ------

   ## P4 串口调试助手（核心要点）

   ### 4.1 添加串口模块

   - 在`.pro`文件中：`QT += serialport`

   ### 4.2 扫描可用串口

   cpp

   ```
   foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
       ui->comboPort->addItem(info.portName());
   }
   ```

   

   ### 4.3 打开串口

   cpp

   ```
   void Widget::on_btnOpen_clicked() {
       serial = new QSerialPort(this);
       serial->setPortName(ui->comboPort->currentText());
       serial->setBaudRate(ui->comboBaud->currentText().toInt());
       serial->setDataBits(QSerialPort::Data8);
       serial->setParity(QSerialPort::NoParity);
       serial->setStopBits(QSerialPort::OneStop);
       serial->setFlowControl(QSerialPort::NoFlowControl);
       if (serial->open(QIODevice::ReadWrite)) {
           connect(serial, &QSerialPort::readyRead, this, &Widget::readData);
           ui->btnOpen->setEnabled(false);
           ui->btnClose->setEnabled(true);
       } else {
           QMessageBox::critical(this, "错误", "无法打开串口");
       }
   }
   ```

   

   ### 4.4 读取数据

   cpp

   ```
   void Widget::readData() {
       QByteArray data = serial->readAll();
       if (ui->checkHex->isChecked()) {
           ui->textReceive->append(data.toHex(' ').toUpper());
       } else {
           ui->textReceive->append(QString::fromUtf8(data));
       }
   }
   ```

   

   ### 4.5 发送数据

   cpp

   ```
   void Widget::on_btnSend_clicked() {
       QString text = ui->textSend->toPlainText();
       if (ui->checkSendHex->isChecked()) {
           QByteArray hexData = QByteArray::fromHex(text.toUtf8());
           serial->write(hexData);
       } else {
           serial->write(text.toUtf8());
       }
   }
   ```

   

   ### 4.6 定时发送

   cpp

   ```
   QTimer *timer = new QTimer(this);
   timer->setInterval(ui->spinInterval->value());
   connect(timer, &QTimer::timeout, this, &Widget::on_btnSend_clicked);
   connect(ui->btnAutoSend, &QPushButton::toggled, timer, &QTimer::setEnabled);
   ```

   

   ------

   ## P5 网络调试助手（详细代码）

   ### 5.1 添加network模块

   - `.pro`文件：`QT += network`

   ### 5.2 TCP服务端

   #### 5.2.1 启动服务器

   cpp

   ```
   void ServerWidget::on_btnListen_clicked() {
       quint16 port = ui->lineEditPort->text().toUShort();
       tcpServer = new QTcpServer(this);
       connect(tcpServer, &QTcpServer::newConnection, this, &ServerWidget::onNewConnection);
       if (!tcpServer->listen(QHostAddress::Any, port)) {
           QMessageBox::critical(this, "错误", "监听失败");
           return;
       }
       ui->btnListen->setEnabled(false);
       ui->btnStop->setEnabled(true);
   }
   ```

   

   #### 5.2.2 处理新连接

   cpp

   ```
   void ServerWidget::onNewConnection() {
       QTcpSocket *client = tcpServer->nextPendingConnection();
       QString peer = client->peerAddress().toString() + ":" + QString::number(client->peerPort());
       ui->comboClients->addItem(peer);
       clients[peer] = client;
       connect(client, &QTcpSocket::readyRead, this, &ServerWidget::onReadyRead);
       connect(client, &QTcpSocket::disconnected, this, &ServerWidget::onDisconnected);
   }
   ```

   

   #### 5.2.3 读取数据

   cpp

   ```
   void ServerWidget::onReadyRead() {
       QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
       QByteArray data = client->readAll();
       QString peer = client->peerAddress().toString() + ":" + QString::number(client->peerPort());
       ui->textBrowser->append(QString("[%1] 收到: %2").arg(peer).arg(QString::fromUtf8(data)));
   }
   ```

   

   #### 5.2.4 发送数据

   cpp

   ```
   void ServerWidget::on_btnSend_clicked() {
       QString currentClient = ui->comboClients->currentText();
       if (clients.contains(currentClient)) {
           QByteArray data = ui->textSend->toPlainText().toUtf8();
           clients[currentClient]->write(data);
           ui->textBrowser->append(QString("[服务端] 发送: %1").arg(QString::fromUtf8(data)));
       }
   }
   ```

   

   ### 5.3 TCP客户端

   #### 5.3.1 连接服务器

   cpp

   ```
   void ClientWidget::on_btnConnect_clicked() {
       QString ip = ui->lineEditIP->text();
       quint16 port = ui->lineEditPort->text().toUShort();
       tcpSocket = new QTcpSocket(this);
       connect(tcpSocket, &QTcpSocket::connected, this, &ClientWidget::onConnected);
       connect(tcpSocket, &QTcpSocket::readyRead, this, &ClientWidget::onReadyRead);
       connect(tcpSocket, &QTcpSocket::disconnected, this, &ClientWidget::onDisconnected);
       tcpSocket->connectToHost(ip, port);
   }
   ```

   

   #### 5.3.2 接收数据

   cpp

   ```
   void ClientWidget::onReadyRead() {
       QByteArray data = tcpSocket->readAll();
       ui->textBrowser->append(QString("服务端: %1").arg(QString::fromUtf8(data)));
   }
   ```

   

   #### 5.3.3 发送数据

   cpp

   ```
   void ClientWidget::on_btnSend_clicked() {
       QByteArray data = ui->textSend->toPlainText().toUtf8();
       tcpSocket->write(data);
       ui->textBrowser->append(QString("客户端: %1").arg(QString::fromUtf8(data)));
   }
   ```

   

   ### 5.4 颜色区分消息

   cpp

   ```
   void ClientWidget::appendMessage(const QString &msg, const QColor &color) {
       QTextCursor cursor = ui->textBrowser->textCursor();
       cursor.movePosition(QTextCursor::End);
       QTextCharFormat fmt;
       fmt.setForeground(QBrush(color));
       cursor.insertText(msg, fmt);
       cursor.insertText("\n");
       ui->textBrowser->setTextCursor(cursor);
   }
   ```

   

   ------

   ## P6 自定义控件（仪表盘深度讲解）

   ### 6.1 绘制原理

   - 重写`paintEvent`，所有绘图操作在`QPainter`上进行。
   - 启用抗锯齿：`painter.setRenderHint(QPainter::Antialiasing);`
   - 使用`translate`移动原点，`rotate`旋转坐标系，简化绘制。

   ### 6.2 绘制刻度盘

   - 范围0~240（速度值），对应角度150°~390°（跨度240°）。所以每单位速度对应1°。
   - 刻度线：循环60次，每旋转4°画一次。每5次画长线，其余短线。
   - 数字：通过`qCos`/`qSin`计算位置，平移坐标系后绘制。

   ### 6.3 指针绘制

   - 用`QPolygon`定义三角形指针，`painter.drawPolygon`。
   - 根据当前速度值旋转指针：`painter.rotate(150 + speedValue * 1.0)`。

   ### 6.4 动态更新

   - 使用`QTimer`周期性改变速度值，并调用`update()`触发重绘。
   - 速度值可以模拟正弦变化或从0到240来回扫描。

   ### 6.5 完整代码结构（头文件）

   cpp

   ```
   class Dashboard : public QWidget {
       Q_OBJECT
   private:
       int speed;          // 当前速度 0-240
       QTimer *timer;
       bool increasing;
   public:
       Dashboard(QWidget *parent = nullptr);
   protected:
       void paintEvent(QPaintEvent *event) override;
   private slots:
       void updateSpeed();
   };
   ```

   

   ### 6.6 部分绘制代码

   cpp

   ```
   void Dashboard::paintEvent(QPaintEvent *) {
       QPainter painter(this);
       painter.setRenderHint(QPainter::Antialiasing);
       int side = qMin(width(), height());
       painter.setViewport((width() - side)/2, (height() - side)/2, side, side);
       painter.setWindow(-100, -100, 200, 200);  // 逻辑坐标 -100..100
   
       // 绘制外圆
       painter.drawEllipse(-90, -90, 180, 180);
       // 绘制刻度...
       // 绘制指针
       painter.save();
       painter.rotate(150 + speed * 1.0); // 起点150°，每单位1°
       painter.drawConvexPolygon(pointerPoints, 3);
       painter.restore();
   }
   ```

   

   ------

   ## P7 天气预报项目（HTTP+JSON详细）

   ### 7.1 添加网络模块

   - `.pro`添加`QT += network`

   ### 7.2 发送HTTP请求

   cpp

   ```
   QNetworkAccessManager *manager = new QNetworkAccessManager(this);
   connect(manager, &QNetworkAccessManager::finished, this, &WeatherWidget::onReplyFinished);
   QUrl url("http://v1.yiketianqi.com/api?city=福州&appid=123456&appsecret=abc");
   manager->get(QNetworkRequest(url));
   ```

   

   ### 7.3 解析JSON响应

   cpp

   ```
   void WeatherWidget::onReplyFinished(QNetworkReply *reply) {
       if (reply->error() != QNetworkReply::NoError) {
           qDebug() << reply->errorString();
           return;
       }
       QByteArray data = reply->readAll();
       QJsonDocument doc = QJsonDocument::fromJson(data);
       QJsonObject root = doc.object();
   
       // 解析当前天气
       QString city = root["city"].toString();
       QString wea = root["wea"].toString();
       QString tem = root["tem"].toString();
       QString win = root["win"].toString();
       QString air = root["air_level"].toString();
   
       // 更新UI
       ui->labelCity->setText(city);
       ui->labelTemp->setText(tem + "°C");
       ui->labelWeather->setText(wea);
       ui->labelWind->setText(win);
       ui->labelAir->setText(air);
   
       // 设置天气图标
       QPixmap pixmap(QString(":/icons/%1.png").arg(wea));
       ui->labelIcon->setPixmap(pixmap);
   
       // 解析未来7天预报（数组）
       if (root.contains("data") && root["data"].isArray()) {
           QJsonArray forecast = root["data"].toArray();
           for (int i = 0; i < forecast.size(); ++i) {
               QJsonObject day = forecast[i].toObject();
               QString date = day["date"].toString();
               QString dayTemp = day["tem1"].toString();
               QString nightTemp = day["tem2"].toString();
               // 显示到列表...
           }
       }
       reply->deleteLater();
   }
   ```

   

   ### 7.4 无边框窗口与拖动

   - 设置窗口标志：`setWindowFlags(Qt::FramelessWindowHint);`

   - 重写鼠标事件：

     cpp

     ```
     void WeatherWidget::mousePressEvent(QMouseEvent *event) {
         if (event->button() == Qt::LeftButton) {
             dragPos = event->globalPos() - frameGeometry().topLeft();
             event->accept();
         }
     }
     void WeatherWidget::mouseMoveEvent(QMouseEvent *event) {
         if (event->buttons() & Qt::LeftButton) {
             move(event->globalPos() - dragPos);
             event->accept();
         }
     }
     ```

     

   ### 7.5 右键退出菜单

   cpp

   ```
   void WeatherWidget::contextMenuEvent(QContextMenuEvent *event) {
       QMenu menu;
       menu.addAction("退出", this, &QWidget::close);
       menu.exec(event->globalPos());
   }
   ```

   

   ### 7.6 样式表示例（圆角背景）

   css

   ```
   QWidget#centralWidget {
       background-color: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                                         stop:0 #0a0f2a, stop:1 #1a2340);
       border-radius: 10px;
   }
   QLabel {
       color: white;
       font-family: "Microsoft YaHei";
       font-size: 14px;
   }
   ```

   

   ------

   ## P8 Ubuntu搭建QT环境（详细命令）

   ### 8.1 安装VMware Tools（复制粘贴增强）

   bash

   ```
   sudo apt install open-vm-tools-desktop
   sudo reboot
   ```

   

   ### 8.2 安装编译器和依赖

   bash

   ```
   sudo apt update
   sudo apt install build-essential
   sudo apt install libgl1-mesa-dev   # OpenGL库
   ```

   

   ### 8.3 安装QT5.12.9

   - 下载离线安装包，给予执行权限`chmod +x qt-opensource-linux-x64-5.12.9.run`

   - 运行前建议断开网络，避免登录。

   - 选择安装路径（例如`/opt/Qt5.12.9`），选择组件：GCC 64-bit、Qt Charts等。

   - 添加环境变量（可选）：

     bash

     ```
     echo 'export PATH=/opt/Qt5.12.9/5.12.9/gcc_64/bin:$PATH' >> ~/.bashrc
     source ~/.bashrc
     ```

     

   ### 8.4 中文输入法

   - 安装fcitx和拼音：

     bash

     ```
     sudo apt install fcitx fcitx-sunpinyin
     ```

     

   - 在系统设置中，将fcitx设为默认输入法，重启。

   - 从网上下载`libfcitxplatforminputcontextplugin.so`，复制到两个位置：

     bash

     ```
     cp libfcitxplatforminputcontextplugin.so /opt/Qt5.12.9/Tools/QtCreator/lib/Qt/plugins/platforminputcontexts/
     cp libfcitxplatforminputcontextplugin.so /opt/Qt5.12.9/5.12.9/gcc_64/plugins/platforminputcontexts/
     chmod 777 /opt/Qt5.12.9/Tools/QtCreator/lib/Qt/plugins/platforminputcontexts/libfcitxplatforminputcontextplugin.so
     chmod 777 /opt/Qt5.12.9/5.12.9/gcc_64/plugins/platforminputcontexts/libfcitxplatforminputcontextplugin.so
     ```

     

   ### 8.5 共享文件夹

   - VMware设置共享文件夹，路径如`shared`

   - 挂载到Ubuntu：

     bash

     ```
     sudo vmhgfs-fuse .host:/shared /mnt/shared -o allow_other
     ```

     

   - 或添加到`/etc/fstab`自动挂载。

   ------

   ## 总结

   这份超详细笔记涵盖了文档中所有重点，并补充了代码原理和额外说明。学习路径建议：

   1. 先通读C++部分，重点掌握类、继承、多态、STL容器。
   2. 按照项目顺序逐个实现：记事本 → 串口助手 → 网络助手 → 仪表盘 → 天气预报。
   3. 每个项目自己从头写一遍，不要直接复制代码，遇到问题再查笔记。
   4. 学会使用Qt帮助文档（F1）和调试技巧（断点、qDebug）。
