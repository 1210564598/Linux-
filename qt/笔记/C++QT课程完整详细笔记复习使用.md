# C++/Qt 课程完整详细笔记

来源：`C++QT课程文档.pdf`  
整理日期：2026-06-10  
整理目标：按 PDF 目录逐节覆盖，采用“概念简写 + 用法 + 示例代码 + 注意事项”的复习格式。

> 说明：这份是“完整覆盖版”，比之前的概念速记版更长。它按课程 P1-P9 的目录展开，项目章节会侧重开发流程、关键类、核心代码和易错点。

---

# P1 Qt 介绍

## 1.1 Qt 简介

### 概念简写

Qt 是一个跨平台 C++ 应用开发框架，主要用于 GUI 程序，也能开发命令行、网络、串口、数据库、多媒体、嵌入式和移动端应用。

### 用法

- 桌面软件：Qt Widgets。
- 现代动态界面：Qt Quick/QML。
- 网络通信：QtNetwork。
- 串口通信：QtSerialPort。
- 数据库：QtSql。
- 绘图与自定义控件：QtGui + QPainter。

### 注意事项

- GUI 程序必须启动事件循环：`app.exec()`。
- Qt 5 和 Qt 6 核心思想相通，但部分 API 和模块有变化。
- 课程使用 Qt 5.12.9，适合学习 Qt Widgets 和传统桌面开发。

## 1.2 Qt 安装

### 概念简写

Qt 安装的重点是选对 Qt 版本、编译器、Qt Creator 和需要的模块。

### 用法

- Windows 常见选择：Qt 5.12.9 + MinGW 64-bit。
- 安装时选择 Qt Creator、编译器、Qt Charts、Qt Data Visualization 等常用组件。
- 安装后创建 Qt Widgets Application 测试环境。

### 示例检查

```text
新建项目 -> Qt Widgets Application -> 选择 Kit -> 构建运行
```

### 注意事项

- 安装路径不要包含中文和特殊符号。
- Kit 配置不正确会导致无法编译。
- 如果修改 `.pro` 文件后报错，尝试“运行 qmake”后重新构建。

## 1.2.1 Windows Qt 安装

### 概念简写

Windows 下安装 Qt，要同时安装 Qt 库、编译器和 Qt Creator。

### 用法

- 选择 Qt 5.12.9 对应组件。
- 编译器常用 MinGW 64-bit。
- 安装完成后检查 Qt Creator 是否能识别 Kit。

### 注意事项

- MinGW 和 MSVC 编译器不能随便混用。
- 用哪个编译器编译，第三方库也要匹配对应编译器。
- 环境出问题时先看 Kit、编译器路径、qmake 路径。

## 1.2.2 Qt Creator 使用基本介绍

### 概念简写

Qt Creator 是 Qt 官方 IDE，负责写代码、设计 UI、编译、运行和调试。

### 用法

```text
Ctrl + R      运行
Ctrl + B      构建
F5            调试运行
F9            设置断点
F10           单步跳过
F11           单步进入
F1            查看帮助
Ctrl + /      注释/取消注释
```

### 注意事项

- “问题”面板看错误摘要，“编译输出”看完整构建日志。
- Qt 帮助文档很重要，类名上按 `F1` 可以查看模块、头文件、成员函数。
- Designer 适合搭界面，但业务逻辑仍应写在 `.cpp` 中。

---

# P2 C++ 基础

## 2.1 命名空间

### 概念简写

命名空间用于避免同名函数、类、变量冲突。

### 用法

```cpp
namespace MyLib {
    void test();
}

MyLib::test();
```

### 示例代码

```cpp
#include <iostream>

namespace MathTool {
    int add(int a, int b) {
        return a + b;
    }
}

int main()
{
    std::cout << MathTool::add(2, 3) << std::endl;
    return 0;
}
```

### 注意事项

- `std` 是标准库命名空间。
- 不建议在头文件中写 `using namespace std;`。
- 大项目中命名空间能显著减少冲突。

## 2.1.1 命名空间作用

### 概念简写

命名空间把一组名字放进一个作用域。

### 用法

```cpp
std::cout
std::vector<int>
```

### 注意事项

- 作用域限定符是 `::`。
- 头文件里滥用 `using namespace` 会影响所有包含它的文件。

## 2.1.2 自定义命名空间

### 示例代码

```cpp
namespace Circle {
    const double PI = 3.1415926;

    double area(double r) {
        return PI * r * r;
    }
}
```

### 注意事项

- 命名空间中的函数如果写在头文件里，注意多重定义问题；简单函数可用 `inline`。
- 推荐声明放 `.h`，定义放 `.cpp`。

## 2.2 从 C 语言快速入门

### 概念简写

C++ 兼容大量 C 语法，但增加了类、引用、重载、模板、异常、STL 等能力。

### 注意事项

- C++ 中仍可使用指针，但更推荐封装、引用、容器和智能指针。
- Qt 中有自己的字符串、容器、对象系统，与标准 C++ 搭配使用。

## 2.2.1 输入输出

### 概念简写

`cin` 负责输入，`cout` 负责输出，`cerr` 常用于错误输出。

### 示例代码

```cpp
#include <iostream>
using namespace std;

int main()
{
    int age;
    cout << "请输入年龄：";
    cin >> age;
    cout << "年龄：" << age << endl;
    return 0;
}
```

### 注意事项

- `cin >> str` 遇到空格停止。
- 读取整行用 `getline(cin, str)`。
- `endl` 会刷新缓冲区，频繁输出时可用 `"\n"`。

## 2.2.2 基本变量类型

### 概念简写

变量类型决定数据含义、内存大小和运算方式。

### 常见类型

- 整型：`int`、`short`、`long`、`long long`
- 浮点：`float`、`double`
- 字符：`char`
- 布尔：`bool`

### 示例代码

```cpp
#include <iostream>
#include <climits>
using namespace std;

int main()
{
    cout << INT_MIN << " ~ " << INT_MAX << endl;
    cout << "double size = " << sizeof(double) << endl;
    return 0;
}
```

### 注意事项

- 整数除法会丢小数：`5 / 2 == 2`。
- 浮点数比较不要直接用 `==`。
- 不同平台类型大小可能不同，关键场景用固定宽度类型如 `int32_t`。

## 2.2.3 流程控制

### 概念简写

流程控制决定程序执行路线。

### 用法

- 条件：`if`、`else`、`switch`
- 循环：`for`、`while`、`do while`
- 跳转：`break`、`continue`

### 示例代码

```cpp
for (int i = 0; i < 10; ++i) {
    if (i == 5) continue;
    if (i == 8) break;
}
```

### 注意事项

- `switch` 的 `case` 后通常要写 `break`。
- `continue` 跳过本轮，`break` 结束循环。
- 避免使用 `goto`。

## 2.2.4 函数

### 概念简写

函数是可复用的一段逻辑。

### 示例代码

```cpp
int add(int a, int b)
{
    return a + b;
}
```

### 注意事项

- 函数声明和定义要匹配。
- 大对象传参用 `const T&`。
- 需要修改外部变量时用引用或指针。

## 2.2.5 内联函数

### 概念简写

`inline` 建议编译器把函数体展开到调用处，减少调用开销。

### 示例代码

```cpp
inline int square(int x)
{
    return x * x;
}
```

### 注意事项

- `inline` 只是建议，不保证一定内联。
- 适合短小、频繁调用的函数。
- 复杂函数不适合内联。

## 2.2.6 Lambda 表达式

### 概念简写

Lambda 是匿名函数，Qt 信号槽里非常常用。

### 示例代码

```cpp
int base = 10;
auto f = [base](int x) {
    return base + x;
};
```

Qt 中：

```cpp
connect(ui->pushButton, &QPushButton::clicked, this, [=]() {
    ui->label->setText("clicked");
});
```

### 注意事项

- `[=]` 按值捕获，`[&]` 按引用捕获。
- 捕获局部变量时注意生命周期。
- Lambda 里访问 UI 时，确保对象没有被销毁。

## 2.2.7 数组

### 概念简写

数组是一组连续存储的同类型数据。

### 示例代码

```cpp
int arr[3] = {1, 2, 3};
for (int i = 0; i < 3; ++i) {
    cout << arr[i] << endl;
}
```

### 注意事项

- 下标从 0 开始。
- 原生数组不检查越界。
- 实际开发更推荐 `std::vector` 或 Qt 容器。

## 2.2.8 练习

### 建议练习

- 写一个计算器，支持 `+ - * /`。
- 用数组保存成绩，计算最大值、最小值、平均值。
- 用 Lambda 实现回调式计算。

### 注意事项

- 除法要处理除数为 0。
- 输入字符时注意空格和换行残留。

## 2.2.9 指针

### 概念简写

指针保存变量地址。

### 示例代码

```cpp
int a = 10;
int *p = &a;
*p = 20;
```

### 注意事项

- 指针可能为空：`nullptr`。
- 不要访问野指针。
- `new` 与 `delete` 成对，`new[]` 与 `delete[]` 成对。
- Qt 对象可通过父对象管理生命周期。

## 2.2.9 字符串 string 类型

### 概念简写

`std::string` 是 C++ 标准库字符串，`QString` 是 Qt 字符串。

### 示例代码

```cpp
std::string s = "hello";
QString q = QString::fromStdString(s);
std::string s2 = q.toStdString();
```

### 注意事项

- Qt UI 中更常用 `QString`。
- 中文转换注意 UTF-8 和本地编码。
- `std::string::c_str()` 可转 C 风格字符串。

## 2.3 类

### 概念简写

类把数据和函数封装到一起，是面向对象编程的核心。

### 示例代码

```cpp
class Student {
public:
    Student(QString name, int age) : name(name), age(age) {}

    void show() const {
        qDebug() << name << age;
    }

private:
    QString name;
    int age;
};
```

### 注意事项

- `class` 默认 `private`。
- 成员变量通常设为 `private`。
- 成员函数如果不修改对象，建议加 `const`。

## 2.3.1 类的初探

### 概念简写

对象是类的实例，类是对象的模板。

### 用法

```cpp
Student s("Tom", 18);
s.show();
```

### 注意事项

- 对象用 `.` 访问成员。
- 指针对象用 `->` 访问成员。

## 2.3.2 结构体引入类

### 概念简写

C 结构体主要放数据，C++ 类把数据和操作放在一起。

### 示例代码

```cpp
struct Car {
    QString brand;
    int year;
};
```

```cpp
class Car {
public:
    void print() const;
private:
    QString brand;
    int year;
};
```

### 注意事项

- `struct` 默认 public，`class` 默认 private。
- C++ 中 struct 也可以有成员函数，但通常用 class 表示封装。

## 2.3.2.1 回忆结构体

### 概念简写

结构体把多个相关数据组合成一个整体。

### 示例代码

```cpp
struct Person {
    char name[32];
    int age;
};
```

### 注意事项

- C 风格字符串长度要控制，容易越界。
- C++/Qt 中可用 `std::string` 或 `QString`。

## 2.3.2.2 新建 C++ 工程来使用结构体

### 用法

在 Qt Creator 中可新建普通 C++ 项目或 Qt Console 项目测试结构体和类。

### 注意事项

- 控制台项目适合练习语法。
- Qt Widgets 项目适合练习界面和信号槽。

## 2.3.2.3 真正的成员函数

### 概念简写

成员函数是属于类的函数，可以直接访问本对象成员变量。

### 示例代码

```cpp
class Car {
public:
    void print() const {
        qDebug() << brand << year;
    }

private:
    QString brand = "BMW";
    int year = 2024;
};
```

### 注意事项

- 类外定义成员函数要加作用域：`Car::print()`。
- `const` 成员函数不能修改普通成员变量。

## 2.3.4 Qt 中经常出现的用法

### 常见写法

```cpp
Widget *w = new Widget(this);
ui->pushButton->setText("确定");
connect(sender, &Sender::signal, receiver, &Receiver::slot);
```

### 注意事项

- `this` 常作为父对象。
- Qt 中大量使用指针管理控件。
- `ui->xxx` 表示访问 Designer 中的控件。

## 2.4 权限初识

### 概念简写

权限控制成员能在哪里被访问。

### 用法

- `public`：类外可访问。
- `private`：只有本类可访问。
- `protected`：本类和派生类可访问。

### 示例代码

```cpp
class Person {
public:
    void setAge(int a) { if (a >= 0) age = a; }
    int getAge() const { return age; }

private:
    int age = 0;
};
```

### 注意事项

- 不要把所有数据都设为 public。
- 通过函数访问成员变量更安全。

## 2.4.1 基本介绍

### 核心

权限是封装的基础，用来保护对象内部状态。

## 2.4.2 目前能概括的结论

### 结论

- 想让外部调用的函数放 `public`。
- 内部实现细节放 `private`。
- 继承中需要子类访问的成员放 `protected`。

## 2.4.3 提问和回答

### 常见问题

- 为什么不直接 public 成员变量？因为无法控制非法赋值。
- getter/setter 是否都需要？不一定，只暴露必要接口。

## 2.5 引用

### 概念简写

引用是变量的别名。

### 示例代码

```cpp
void addOne(int &x)
{
    ++x;
}
```

### 注意事项

- 引用必须初始化。
- 引用通常不能为空。
- 返回局部变量引用是严重错误。

## 2.6.1 和指针的区别

### 对比

- 指针可以为空，引用通常不能为空。
- 指针可以改变指向，引用初始化后不能重新绑定。
- 指针访问用 `*` 和 `->`，引用像普通变量一样使用。

## 2.6.2 把引用作为参数

### 示例代码

```cpp
void swapValue(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
}
```

### 注意事项

- 需要修改外部变量时用普通引用。
- 只读大对象用 `const T&`。

## 2.6.3 把引用作为返回值

### 示例代码

```cpp
int& at(int *arr, int index)
{
    return arr[index];
}
```

### 注意事项

- 不能返回局部变量引用。
- 返回成员变量引用会暴露内部状态，谨慎使用。

## 2.6 重载

### 概念简写

重载表示同名函数根据参数不同实现不同功能。

## 2.5.1 函数重载

### 示例代码

```cpp
int add(int a, int b);
double add(double a, double b);
```

### 注意事项

- 参数个数、类型、顺序不同才算重载。
- 返回值不同不构成重载。

## 2.5.2 运算符重载

### 概念简写

运算符重载让自定义类也能使用 `+ - == <<` 等运算符。

### 示例代码

```cpp
class Point {
public:
    Point(int x, int y) : x(x), y(y) {}

    Point operator+(const Point &other) const {
        return Point(x + other.x, y + other.y);
    }

private:
    int x;
    int y;
};
```

### 注意事项

- 不要滥用运算符重载，含义要符合直觉。
- `operator=`、拷贝构造、析构与资源管理关系密切。
- Qt 中很多类已重载运算符，例如 `QString` 的 `+`。

## 2.7 构造函数

### 概念简写

构造函数在对象创建时自动调用。

### 示例代码

```cpp
class Car {
public:
    Car(QString brand, int year) : brand(brand), year(year) {}
private:
    QString brand;
    int year;
};
```

### 注意事项

- 构造函数没有返回值。
- 推荐使用初始化列表。
- 构造函数可重载。

## 2.7.1 什么是构造函数

### 核心

构造函数负责初始化对象，让对象创建后处于可用状态。

## 2.7.2 带参数构造函数

### 示例代码

```cpp
Student(QString name, int age) : name(name), age(age) {}
```

### 注意事项

- 参数名和成员名相同时，可用 `this->` 区分，也可用初始化列表。

## 2.7.3 拷贝构造函数

### 概念简写

用已有对象创建新对象时调用。

### 示例代码

```cpp
ClassName(const ClassName &other);
```

### 注意事项

- 形参必须用引用，否则会无限递归拷贝。
- 有指针资源时必须考虑深拷贝。

## 2.7.3.1 基本概念及发生条件

### 发生条件

- `A b = a;`
- 函数参数按值传递对象。
- 函数按值返回对象。

## 2.7.3.2 浅拷贝

### 概念简写

浅拷贝只复制指针地址，不复制指针指向的资源。

### 风险

两个对象指向同一块内存，析构时可能重复释放。

## 2.7.3.3 深拷贝

### 概念简写

深拷贝会重新申请资源，并复制资源内容。

### 示例代码

```cpp
class Buffer {
public:
    Buffer(const char *s) {
        data = new char[strlen(s) + 1];
        strcpy(data, s);
    }

    Buffer(const Buffer &other) {
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
    }

    ~Buffer() {
        delete[] data;
    }

private:
    char *data;
};
```

### 注意事项

- 有 `new` 通常就要考虑拷贝构造、赋值运算符、析构函数。

## 2.7.3.4 规则三则

### 概念简写

如果类需要自定义析构函数、拷贝构造函数、拷贝赋值运算符中的一个，通常三个都要考虑。

### 注意事项

- 现代 C++ 还要了解移动构造和移动赋值，即规则五。
- Qt 的 `QObject` 派生类通常禁用拷贝。

## 2.7.3.5 避免不必要的拷贝

### 用法

- 参数使用 `const T&`。
- 返回值依赖编译器优化。
- 大对象避免按值传递。

### 示例代码

```cpp
void printStudent(const Student &s);
```

## 2.7.3.6 拷贝构造函数的隐式调用

### 例子

```cpp
void func(Student s); // 调用时会拷贝
Student s2 = s1;      // 会拷贝
```

### 注意事项

- 隐式拷贝可能带来性能问题。
- 对不可拷贝对象要用引用或指针传递。

## 2.7.3.7 禁用拷贝构造函数

### 示例代码

```cpp
class A {
public:
    A(const A&) = delete;
    A& operator=(const A&) = delete;
};
```

### 注意事项

- `QObject` 派生类本身就不适合拷贝。
- 禁用拷贝能避免资源重复释放。

## 2.7.3.8 拷贝构造函数总结

### 总结

- 无资源类可用默认拷贝。
- 有裸指针资源要写深拷贝。
- 不允许拷贝就 `= delete`。
- 优先使用标准库容器、智能指针或 Qt 父子对象树减少手动资源管理。

## 2.7.4 使用初始化列表

### 概念简写

初始化列表在构造函数体执行前初始化成员。

基本语法

```
class 类名 {
public:
    类名(参数列表) : 成员1(值1), 成员2(值2), ... {
        // 构造函数体（可空）
    }
};
```



### 示例代码

```cpp
class Car {
public:
    string brand;
    int year;
    Car(string br, int y) : brand(br), year(y) {
        // 此时 brand 和 year 已经初始化完成
    }
};
```

### 注意事项

- `const` 成员必须用初始化列表。
- 引用成员必须用初始化列表。
- 成员初始化顺序按声明顺序，不按初始化列表书写顺序。

## 2.7.5 this 关键字

### 概念简写

`this` 指向当前对象。

### 示例代码

```cpp
class Person {
public:
    Person& setAge(int age) {
        this->age = age;
        return *this;
    }
private:
    int age = 0;
};
```

### 注意事项

- 静态成员函数中没有 `this`。
- 返回 `*this` 可实现链式调用。

## 2.7.6 new 关键字

### 概念简写

`new` 在堆上创建对象，返回指针。

### 示例代码

```cpp
Student *s = new Student("Tom", 18);
delete s;
s = nullptr;
```

### 注意事项

- `new`/`delete` 成对。
- `new[]`/`delete[]` 成对。
- Qt 中有父对象时通常不用手动 delete。

## 2.8 析构函数

### 概念简写

析构函数在对象销毁前自动调用，用于释放资源。

### 示例代码

```cpp
class Test {
public:
    ~Test() {
        qDebug() << "析构";
    }
};
```

### 注意事项

- 析构函数无参数、无返回值。
- 一个类只有一个析构函数。
- 基类有虚函数时，析构函数建议为 `virtual`。

## 2.8.1 什么是析构函数

### 核心

析构函数是资源清理入口，例如释放内存、关闭文件、断开连接。

## 2.9 静态成员

### 概念简写

静态成员属于类本身，不属于某个对象。

### 示例代码

```cpp
class Student {
public:
    Student() { ++count; }
    static int count;
};

int Student::count = 0;
```

### 注意事项

- 静态成员变量要在类外定义。
- 静态成员函数不能直接访问普通成员变量。

## 2.9.1 静态成员的定义

### 用法

```cpp
class A {
public:
    static int num;
};

int A::num = 0;
```

## 2.9.2 静态成员变量的作用

### 常见用途

- 统计对象数量。
- 保存共享配置。
- 实现工具函数或工厂函数。

## 2.10 继承

### 概念简写

继承让子类复用父类成员并扩展功能。

### 示例代码

```cpp
class Animal {
public:
    void eat() {}
};

class Dog : public Animal {
public:
    void bark() {}
};
```

### 注意事项

- 常用 public 继承。
- 构造先父类后子类，析构先子类后父类。

## 2.10.1 继承基本概念

### 核心

子类“是一种”父类时，适合使用继承。

## 2.10.2 权限对继承的影响

### 简表

| 基类成员 | public 继承后 | protected 继承后 | private 继承后 |
|---|---|---|---|
| public | public | protected | private |
| protected | protected | protected | private |
| private | 不可直接访问 | 不可直接访问 | 不可直接访问 |

### 注意事项

- 父类 private 成员被继承但子类不能直接访问。
- Qt 中大多数继承是 public 继承。

## 2.10.3 基类构造函数

### 示例代码

```cpp
class Base {
public:
    Base(int x) {}
};

class Derived : public Base {
public:
    Derived(int x, int y) : Base(x), y(y) {}
private:
    int y;
};
```

### 注意事项

- 子类构造函数需要在初始化列表中调用父类有参构造。

## 2.10.4 虚函数

### 概念简写

虚函数允许子类重写，并通过父类指针/引用调用子类实现。

### 示例代码

```cpp
class Animal {
public:
    virtual void speak() {
        qDebug() << "animal";
    }
    virtual ~Animal() {}
};

class Dog : public Animal {
public:
    void speak() override {
        qDebug() << "dog";
    }
};
```

### 注意事项

- 重写建议加 `override`。
- 多态依赖虚函数。

### virtual 关键字

`virtual` 声明虚函数，使调用在运行时根据真实对象类型决定。

### override 关键字

`override` 告诉编译器该函数必须重写父类虚函数，能防止拼写或参数错误。

## 2.10.5 多重继承

### 概念简写

一个类同时继承多个父类。

### 示例代码

```cpp
class A {};
class B {};
class C : public A, public B {};
```

### 注意事项

- 多重继承容易增加复杂度。
- Qt 中界面类一般单继承 QWidget，再组合其他对象。

## 2.10.6 虚继承

### 概念简写

虚继承用于解决菱形继承中基类重复的问题。

### 示例代码

```cpp
class A {};
class B : virtual public A {};
class C : virtual public A {};
class D : public B, public C {};
```

### 注意事项

- Qt 日常开发中较少直接使用虚继承。
- 需要理解即可，不建议新手频繁使用。

### 菱形继承问题示例

`D` 同时继承 `B` 和 `C`，而 `B`、`C` 又都继承 `A`，会导致 `D` 中有两份 `A`。

### 使用虚继承解决菱形继承问题

让 `B`、`C` 使用 `virtual public A`，最终 `D` 中只有一份共享的 `A`。

## 2.11 多态

### 概念简写

多态是同一接口对不同对象产生不同效果。

### 示例代码

```cpp
class Shape {
public:
    virtual double area() const = 0;
    virtual ~Shape() {}
};

class Rect : public Shape {
public:
    Rect(double w, double h) : w(w), h(h) {}
    double area() const override { return w * h; }
private:
    double w;
    double h;
};
```

### 注意事项

- 多态一般通过基类指针或引用调用虚函数实现。
- 抽象类不能直接创建对象。

## 2.11.1 如何实现多态

### 三条件

- 有继承关系。
- 父类有虚函数。
- 子类重写虚函数，通过父类指针/引用调用。

## 2.11.2 抽象类

### 概念简写

含有纯虚函数的类是抽象类。

### 示例代码

```cpp
class Interface {
public:
    virtual void run() = 0;
};
```

## 2.11.3 纯虚函数 - 接口

### 用法

纯虚函数只规定接口，不提供实现。

### 注意事项

- 接口类析构函数也建议为 virtual。

## 2.12 友元

### 概念简写

友元允许外部函数或类访问本类 private/protected 成员。

## 2.12.1 什么是友元

### 注意事项

- 友元会破坏封装，谨慎使用。
- 常用于运算符重载、调试输出。

## 2.12.2 友元函数

### 示例代码

```cpp
class Point {
    friend void printPoint(const Point &p);
private:
    int x = 1;
    int y = 2;
};

void printPoint(const Point &p)
{
    qDebug() << p.x << p.y;
}
```

## 2.12.3 友元类

### 示例代码

```cpp
class A {
    friend class B;
private:
    int value = 10;
};
```

## 2.12.4 友元成员函数

### 概念简写

只让另一个类的某个成员函数成为友元，而不是整个类。

### 注意事项

- 声明顺序较复杂，了解即可。

## 2.13 模板

### 概念简写

模板用于编写类型无关的通用代码。

## 2.13.1 类模板

### 示例代码

```cpp
#    
#include <string>
template <typename T>
class Box {
public:
    Box() {}
    Box(T v) : value(v) {} 初始化列表
    T get() const { return value; }
 	void set(T v) { value = v; }
private:
    T value;
};

int main() {
    //传统方式
    Box<int>p3;
    p3.set(43);
   cout << p3.get();
    
    // 存储 int 类型
    Box<int> intBox(42);
    std::cout << intBox.get() << std::endl;  // 输出 42

    // 存储 double 类型
    Box<double> doubleBox(3.14);
    std::cout << doubleBox.get() << std::endl;  // 输出 3.14

    // 存储字符串（需要包含 <string>）

    Box<std::string> strBox("Hello, Box!");
    std::cout << strBox.get() << std::endl;  // 输出 Hello, Box!

    // C++17 起可以省略模板参数（类模板实参推导）
    Box autoBox(100);          // 自动推导为 Box<int>
    std::cout << autoBox.get() << std::endl;

    return 0;
}
```

### 注意事项

- 模板通常写在头文件中。

## 2.13.2 函数模板

### 示例代码

```cpp
template <typename T>
T maxValue(T a, T b)
{
    return a > b ? a : b;
}
int main() {
    int x = 10, y = 20;
    std::cout << maxValue(x, y) << std::endl;   // 输出 20，T 自动推导为 int

    double d1 = 3.14, d2 = 2.71;
    std::cout << maxValue(d1, d2) << std::endl; // 输出 3.14，T 推导为 double

    return 0;
}
```

## 2.13.3 模板特化

### 概念简写

模板特化是为某种具体类型提供特殊实现。

### 示例代码

```cpp
template <typename T>
class Printer {
public:
    void print(const T &v) { qDebug() << v; }
};

template <>
class Printer<QString> {
public:
    void print(const QString &v) { qDebug() << "QString:" << v; }
};
```

### 注意事项

- 特化用于某些类型需要特殊处理的情况。
- 不要为了小差异过度特化。

## 2.14 标准模板库 STL

### 概念简写

STL 提供常用容器、算法和迭代器。

## 2.14.1 容器

### 常见容器

- `vector`：动态数组。
- `list`：链表。
- `set`：集合。
- `map`：键值对。

### 注意事项

- Qt 也提供 `QVector`、`QList`、`QSet`、`QMap`。

## 2.14.2 vector

### 示例代码

```cpp
std::vector<int> v;
v.push_back(1);
v.push_back(2);
for (int x : v) {
    qDebug() << x;
}
```

### 注意事项

- 随机访问快。
- 中间插入删除可能搬移大量元素。

## 2.14.3 list

### 示例代码

```cpp
std::list<int> lst;
lst.push_back(1);
lst.push_front(0);
```

### 注意事项

- 插入删除方便。
- 不支持下标随机访问。

## 2.14.4 set

### 示例代码

```cpp
std::set<int> s;
s.insert(3);
s.insert(3);
s.insert(1);
```

### 注意事项

- 自动排序。
- 自动去重。

## 2.14.5 map

### 示例代码

```cpp
std::map<std::string, int> score;
score["Tom"] = 90;
```

### 注意事项

- `map[key]` 不存在时会创建默认值。
- 只查询可用 `find()`。

## 2.15 异常

### 概念简写

异常用于处理运行期错误。

## 2.15.1 异常基本

### 示例代码

```cpp
try {
    throw std::runtime_error("error");
} catch (const std::exception &e) {
    qDebug() << e.what();
}
```

### 注意事项

- Qt 中很多 API 用返回值、错误码、信号表示错误。
- 不要把异常当普通流程控制。

## 2.15.2 自定义异常

### 示例代码

```cpp
class MyError : public std::exception {
public:
    const char* what() const noexcept override {
        return "my error";
    }
};
```

---

# P3 记事本项目

## 3.1 项目概述

### 功能简写

通过记事本项目学习 Qt Widgets、UI 设计、信号槽、文件读写、编码、快捷键和事件。

#### 3.1.1 功能介绍

### 功能列表

- 打开文本文件。
- 保存文本文件。
- 支持编码选择。
- 显示当前行列。
- 当前行高亮。
- 关闭时提示保存。
- 快捷键打开/保存。
- Ctrl + 滚轮缩放字体。

#### 3.1.2 界面预览

### 组成

- 顶部按钮区。
- 编码选择下拉框。
- 中间文本编辑区。
- 底部行列状态显示。

#### 3.2.3 工程概述

### 文件结构

- `main.cpp`：程序入口。
- `widget.h/.cpp`：主窗口类。
- `widget.ui`：界面文件。
- `.pro`：工程配置。

## 3.2 UI 设计师工具

#### 概念简写

Designer 用于拖拽控件、设置属性、创建布局。

#### 注意事项

- 控件命名要有意义，如 `btnOpen`、`textEdit`。
- 复杂逻辑不要写在 UI 文件里。

### 3.2.1 QPushButton

#### 用法

```cpp
connect(ui->btnOpen, &QPushButton::clicked, this, &Widget::openFile);
```

#### 注意事项

- 按钮文字通过 `setText()` 设置。
- 信号常用 `clicked()`。

### 3.2.2 QHBoxLayout

#### 概念简写

水平布局从左到右排列控件。

#### 示例代码

```cpp
QHBoxLayout *layout = new QHBoxLayout;
layout->addWidget(ui->btnOpen);
layout->addWidget(ui->btnSave);
```

### 3.2.3 TextEdit

#### 用法

```cpp
ui->textEdit->setPlainText("hello");
QString text = ui->textEdit->toPlainText();
```

#### 注意事项

- 普通文本用 `setPlainText()`。
- 富文本用 `setHtml()`。

### 3.2.4 QVBoxLayout

#### 概念简写

垂直布局从上到下排列控件。

### 3.2.5 主窗体元素设计

#### 建议

- 上方操作区：打开、保存、编码。
- 中间编辑区：`QTextEdit`。
- 下方状态区：行列、路径、修改状态。

## 3.3 按键响应 - 初识信号与槽

#### 概念简写

按钮点击发出信号，槽函数处理业务。

### 3.3.1 信号与槽基本介绍

#### 链接打开按钮

```cpp
connect(ui->btnOpen, &QPushButton::clicked, this, &Widget::onOpenClicked);
```

#### 注意事项

- 新语法 connect 编译期检查更多错误。

### 3.3.2 QPushButton 设置信号与槽

#### 示例代码

qDebug()相当于cout

```cpp
void Widget::on_btnOpen_clicked()
{
    qDebug() << "open clicked";
}
```

#### 注意事项

- 自动槽函数名格式通常是 `on_对象名_信号名()`。

### 3.3.3 自定义信号与槽

emit mysignal();  //触发点击事件

#### 示例代码

```cpp
signals:
    void mysignal();
    void mysignalparams(int value);
private slots:
    void myslot();
    void myslotparams(int value);
```

```c++
#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
     
        
        connect(this,SIGNAL(mysignal()),this,SLOT(myslot()));
    emit mysignal();  //触发点击事件

           		                       connect(this,SIGNAL(mysignalparams(int)),this,SLOT(myslotparams(int)));
    emit mysignalparams(3);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::myslot()
{
    qDebug() << "open clicked";
}

void Widget::myslotparams(int value)
{
    qDebug() << "open clicked myslotparams";
}


```



#### 注意事项

- 有自定义信号槽的类需要 `Q_OBJECT`。

### 3.3.4信号和槽的四种方式练习（待补充）

qt图像界面中可以直接设置 发送者  信号 接受者 槽

#### 方式一:创建按钮buttom转到槽 直接选择  clicked()信号,系统自动创建on_pushButton_clicked方法，以及头文件

方式二:添加按钮pushButton_2,构造函数on_btnCon_clickedMyself()，

手动添加on_btnCon_clickedMyself()到头文件

方法三添加按钮pushButton_3使用  Lambda表达式方式

方法四添加按钮pushButton_4使用  函数方式

widget.cpp

```
#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
//第一种样例：QObject::connect(sender,SIGNAL(signal())
,receiver, SLOT(slot()));
 
 QObject::connect(ui->pushButton_2, SIGNAL(clicked()), this,SLOT(on_btnCon_clickedMyself()));
 
 
 
//第三中方式：QObject::connect(sender,&Sender::signal, [=]() {/* lambda body */ });
   
   QObject::connect(ui->pb3, &QPushButton::clicked,
                         [=]() {
                       cout << "btnLambda点击事件" << endl;
                         });



//第四种方式：QObject::connect(sender, &Sender::signal, receiver,&Receiver::slot);
     
     QObject::connect(ui->pb4,  &QPushButton::clicked,
                     this,&Widget::on_func_clicked);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    cout<<"直接链接"<<endl;
}

void Widget::on_btnCon_clickedMyself(){
    cout<<"第二种方式"<<endl;
}

void Widget::on_func_clicked(){
    cout<<"第四种方式"<<endl;

}

```



## 3.4 文件操作类 QFile

示例代码

```cpp
void Widget::on_pushButton_clicked()
{
    //1. 打开文件
     QFile file("F:/LinuxEDStudy/qt/text.txt");
     if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    //2. 读取文件
     char context[100] = {'\0'};
     if( file.read(context,100) == -1) return;
     //3. 输出文件内容
     qDebug() << context;

    //4. 关闭内容
     file.close();
}

void Widget::on_pushButton_2_clicked()
{
    //1. 打开文件
     QFile file;
      file.setFileName("F:/LinuxEDStudy/qt/text2.txt");
     if(!file.open(QIODevice::WriteOnly | QIODevice::Text))return;
     file.write("xxxxxxaaaabbbcccdd");
     // 3. 关闭
     file.close();


}

```

注意事项

- 文件打开必须判断成功与否。

### 3.4.1 QTextStream

#### 示例代码

```cpp
//读文件
void Widget::on_pushButton_3_clicked()
{
    //1. 打开文件
     QFile file("F:/LinuxEDStudy/qt/text.txt");
     if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
     //读取文件内容 
     QTextStream in(&file);
     in.setCodec("UTF-8");//设置编码
    //逐行读取
     while (!in.atEnd()) {
        QString line = in.readLine();
        qDebug()<<line;}
    
    //读取文件大小的
    // QString sizefile=file.read(file.size());
    //qDebug()<<sizefile;
     // 读取全部内容
    // QByteArray allData = file.readAll();
     // qDebug()<<allData;
}

写入文件
void Widget::on_pushButton_4_clicked()
{
    //1. 打开文件
     QFile file("F:/LinuxEDStudy/qt/text3.txt");
     if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) return;
     //stream写入
     QTextStream out(&file);
     out<<"1213141411qqqqq";
     QString sizefile=file.read(file.size());
     qDebug()<<sizefile;
     file.close();
}

```

#### 注意事项

- Qt 5 支持 `QTextCodec` 设置编码。
- Qt 6 移除了 `QTextCodec`。
- in.setCodec("UTF-8")设置编码;

## 3.5 QFileDialog

###  QFileDialog 的核心功能

`QFileDialog`主要通过以下四个静态方法，覆盖了绝大部分日常使用场景：

| 功能场景         | 使用的静态方法                        | 返回值类型    |
| :--------------- | :------------------------------------ | :------------ |
| **打开单个文件** | `QFileDialog::getOpenFileName()`      | `QString`     |
| **打开多个文件** | `QFileDialog::getOpenFileNames()`     | `QStringList` |
| **保存文件**     | `QFileDialog::getSaveFileName()`      | `QString`     |
| **选择目录**     | `QFileDialog::getExistingDirectory()` | `QString`     |

//打开单个文件

```cpp
//单文件打开
void Widget::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "openfile", "F:/LinuxEDStudy/qt", "Text (*.txt);;All (*.*)");
     qDebug()<<fileName;


     QFile file(fileName);//打开文件
     if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) return;
    QTextStream in(&file);
    while (!in.atEnd()) {
          QString line = in.readLine();
          qDebug()<<line;}


}//用户取消时返回空字符串。
```

### 3.5.1 QFileDialog 打开文件流程

1. **实例化**：首先，创建一个 QFileDialog 对象的实例。
2. **设置模式**：根据需要设置对话框的模式，如打开文件、保存文件等
3. **设置过滤器**：如果需要，可以设置文件类型过滤器，以限制用户可以选择的文件类型。
4. **显示对话框**：通过调用 exec() 方法显示对话框，并在用户作出选择后执行相应的操作。
5. **使用QStringList链表**：获取打开的文件目录。
6. **遍历容器**，使用 `QFile` 打开文件。
7. **设置打开文件模式**：通过调用open（）方法设置打开文件模式
8. **使用 `QTextStream**` 读取或写入。

### 3.5.2 QFileDialog 分步骤多文件打开**

```cpp
void Widget::on_pushButton_2_clicked()
{
   //选择多文件打开
   // QStringList fileName = QFileDialog::getOpenFileNames(this, "openfile", "F:/LinuxEDStudy/qt", "Text (*.txt);;All (*.*)");

    // 创建一个 QFileDialog 实例
    QFileDialog fileNames(this);
    fileNames.setWindowTitle("选择多个文件");
    fileNames.setDirectory("F:/LinuxEDStudy/qt");
    // 关键：设置文件模式为“已存在的多个文件”
    fileNames.setFileMode(QFileDialog::ExistingFiles);   // 多选
        // 其他可选模式：
        // QFileDialog::AnyFile          - 任意文件（保存对话框常用）
        // QFileDialog::ExistingFile     - 单个已存在文件
        // QFileDialog::Directory        - 选择目录
        // QFileDialog::ExistingFiles    - 多个已存在文件

    // 设置文件过滤器
    fileNames.setNameFilter("Text (*.txt);;Images (*.png *.jpg);;All files(*)");
    fileNames.exec();
    //exec() 是 QDialog 的方法，通常用于模态显示对话框。
    QStringList fileName = fileNames.selectedFiles();
    //selectedFiles() 是 Qt 中 QFileDialog 类的一个成员函数，用于获取用户在文件对话框中最终选中并确认的文件或目录的路径列表。
    qDebug() << "opt file：" << fileName;
    
    for(QString &filepath:fileName){//遍历fileName容器 逐个输出容器中的fileNe
        qDebug() << filepath;
        //打开文件
        QFile file(filepath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
        //file.open(QIODevice::ReadOnly | QIODevice::Text以只读且文本模式打开文件。}
        QTextStream in(&file);
        if(!in.atEnd()){
            QString line=in.readLine();
             qDebug() <<line;
        }
    }


```

### 3.5.3 QFileDialog 保存开发案例

```cpp
void Widget::on_pushButton_3_clicked()
{
       QString filesave=QFileDialog::getSaveFileName(this,
                                                     tr("savefile"),
                                                     "F:/LinuxEDStudy/qt",
                                                     ("Text (*.txt);;Word文档 (*.doc)") );
        qDebug()<<filesave;

        QFile file(filesave);
        if(!file.open(QIODevice::ReadWrite | QIODevice::Text))return;
        QTextStream out(&file);
        out<<"123456";


}

```

## 3.6 记事本功能初步实现

### 3.6.1 开发流程

```
//打开功能
1、将QFile file;写入头文件
2、写入内容需要在源文件进行追加 append(context);
//保存功能
1、在源文件的使用 toPlainText()获取 QTextEdit 控件纯文本内容的函数。
//关闭功能
1、使用isOpen()判断是否打开
2、文件打开 需要的关闭使用  file.close();
3、清空文本编辑框中的内容   clear();
```

### 3.6.2 代码实现

```cpp
//打开
void Widget::on_btnFileOpen_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "F:/LinuxEDStudy/qt",
                                                    tr("Text (*.txt)"));

    ui->textEdit->clear();//清空

    file.setFileName(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "file open error";
    }

    QTextStream in(&file);
    in.setCodec("UTF-8");
    //in.setCodec("ANSI");
    while(!in.atEnd()){
        QString context = in.readLine();
       // qDebug() << qPrintable(context);
       // ui->textEdit->setText(context);//覆盖
        ui->textEdit->append(context);//追加
    }
}
//保存
void Widget::on_btnSave_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                "F:/LinuxEDStudy/qt",
                                tr("Text (*.txt *.doc)"));

    file.setFileName(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << "file open error";
    }

    QTextStream out(&file);
    out.setCodec("UTF-8");
    QString context = ui->textEdit->toPlainText();//ui->textEdit->toPlainText()获取 QTextEdit 控件纯文本内容的函数。
    out << context;
}

//关闭
void Widget::on_btnClose_clicked()
{

    if(file.isOpen()){

        file.close();
        ui->textEdit->clear();
    }
}
```

### 3.6.3 打开功能优化

#### 优化点

- 字符编码相关问题解决
- 检测光标位置，并在右下角显示光标位置
- 在程序左上方显示当前打开的文件名称

### 3.6.4 QComboBox

#### 用法

```
1、ui界面选择Combo Box按钮 添加显示的内容
2、链接按钮给出信号   currentIndexChanged（）;事件
connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(on_currentIndexChanged(int)));
3、添加头文件on_currentIndexChanged(int)；
4、编写槽函数
```

```cpp
connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(on_currentIndexChanged(int)));
```

### 3.6.5 记事本支持字符编码

#### 示例代码

```cpp
void Widget::on_currentIndexChanged(int text)
{
    qDebug() << "currentItSignal";
    if (!file.isOpen()) return;//没有打开文件  则触发也不改变
    ui->textEdit->clear();

    QTextStream in(&file);
   // in.setCodec(ui->comboBox->currentText().toStdString().c_str());
    in.setCodec(ui->comboBox->currentText().toUtf8().constData());
    //setCodec(char *)
    //ui->comboBox->currentText() 获取当前选中的文本
    //toStdString()将QString 转为c++中的String
    //c_str()将c++中的String 转为char *
    
    //currentText() → 拿到选中的文字，是 QString 类型（Qt 自己的字符串）。 
    //.toUtf8() → 把文字转成 UTF-8 编码的字节数组（QByteArray），就像把汉字或字母变成一个个字节，末尾自动加一个 \0。
   // .constData() → 取出这个字节数组的内部地址，也就是 const char*，C 风格字符串的指针。
    //整个链式调用写在一行，保证指针使用的时候内存还没被释放。
   in.seek(0);
    while(!in.atEnd()){
        QString context = in.readLine();

        ui->textEdit->append(context);//追加
    }


}
```

#### 注意事项

- 这是 Qt 5 写法。
- Qt 6 项目建议统一 UTF-8。

### 3.6.6 添加行列显示

用法

```
1、链接按钮给出信号   
SIGNAL(cursorPositionChanged())
connect(ui->textEdit,SIGNAL(cursorPositionChanged()),this,SLOT(on_cursorPositionChanged()));
2、添加头文件
3、编写槽函数
```

```
//cursorPositionChanged() 是 QTextEdit 类的一个信号，当文本编辑框中的光标位置发生移动（例如用户用鼠标点击、键盘方向键、或者代码中调用 setTextCursor()）时，这个信号就会被发射。
```

#### 示例代码

```cpp
void Widget::on_cursorPositionChanged()
{
    QTextCursor cursorpos=ui->textEdit->textCursor();
    //textCursor()：QTextEdit 的成员函数，返回一个表示当前光标位置、选中区域及文本编辑状态的 QTextCursor 对象。
    QString blockNum = QString::number(cursorpos.blockNumber()+1);
    QString columnNum = QString::number(cursorpos.columnNumber()+1);
    QString labelMes="L"+blockNum+",C"+columnNum+"  ";
    //QString::number(...)：将整数转换为 QString 字符串
    //blockNumber()：返回光标所在的文本块（block）的编号。在纯文本文档中，一个 block 通常对应一行（按换行符分隔）。
    //columnNumber():用于获取光标在当前行中的逻辑列号。
    ui->labelPosition->setText(labelMes);
}

```

### 3.6.7 添加文件打开提示

#### 用法 

```
//设置打开文件标题
this->setWindowTitle(fileName+"  Notebook");
```

### 3.6.8 设置当前行高亮

步骤

```
1、创建泛型QList
2、定义单个QTextEdit::ExtraSelectionc对象
3、获得改行位置selection.cursor=ui->textEdit->textCursor();
4、设置颜色QColor lineColo创建一个QColor 对象
5、election.format你设置的那个“高亮效果对象”里的格式部分（比如背景色、字体颜色等）。
6、setProperty(...)给这个格式设置一个“特殊属性”。属性有很多种，这里用的是 FullWidthSelection。
7、QTextFormat::FullWidthSelection这是一个固定的属性名，意思是“整行宽度选择”。把它设为 true，就告诉编辑器：这个高亮效果要占满整行的宽度（从左边缘到右边缘）。
8、extraSelections.append(selection);追加对象进入QList
9、setExtraSelections(...)QTextEdit 自带的函数，意思是“设置额外选区”。它接收一个列表，列表里的每一项都描述了一种“额外效果”（比如某一段文字的背景变蓝）。调用这个函数后，编辑器就会清除旧效果、显示新效果。
10、extraSelections 你之前构造好的列表，里面目前只放了一个元素：描述“当前行高亮”的效果（什么颜色、铺满整行、哪一行等）。
```



#### 示例代码

```cpp
    //设置当前行高亮
    QList<QTextEdit::ExtraSelection> extraSelections;
    QTextEdit::ExtraSelection selection;
    //知道当前行
    selection.cursor=ui->textEdit->textCursor();
    //设置颜色
    QColor lineColor = QColor(230, 240, 255); // 淡蓝色
    selection.format.setBackground(lineColor);
    selection.format.setProperty(QTextFormat::FullWidthSelection, true);
    //
    extraSelections.append(selection);
    ui->textEdit->setExtraSelections(extraSelections);
    //setBackground() 是 QTextCharFormat 的成员函数，用于设置背景画刷（QBrush）
```

#### 3.6.8.1 QList

#### 概念简写

`QList` 是 Qt 容器，用来保存一组对象。

**包含头文件**：首先，你需要包含 QList 的头文件。

```
#include <QList>
```

**创建** **QList** **实例**：创建一个 QList 对象，并指定存储的元素类型。

```
QList<int> list;
```

**添加元素**：使用 append 或 push_back 方法添加元素。

```
list.append(1);
list.append(2);
list.append(3);
```

**访问元素**：可以使用下标操作符或 at() 方法访问元素。

```
int firstElement = list[0];
int secondElement = list.at(1);
```

**遍历列表**：使用迭代器或范围基的 for 循环遍历列表。

```
for(int i = 0; i < list.size(); ++i) { // size = sizeof(arr)/sizeof(arr[0])
qDebug() << list[i];
}
// 或者使用范围基的 for 循环
for(int item : list) {
qDebug() << item;
}
```

**移除元素**：使用 removeAt 、 removeOne 或 clear 方法移除元素

```
list.removeAt(1); // 移除索引为 1 的元素
list.removeOne(3); // 移除一个值为 3 的元素
list.clear(); // 清空整个列
```

#### 注意事项

- Qt 5 中 `QList` 很常见。
- Qt 6 中 `QVector` 和 `QList` 实现趋同。

#### 3.8.2 ExtraSelection 简介

#### 概念简写

**`ExtraSelection`** 是 Qt 中 `QTextEdit` 类定义的一个**结构体**（`struct`）。它的作用很简单：**让你在不改变文本内容的前提下，给编辑器里的某些文本区域“额外”加上背景色、前景色等视觉效果**。





## 3.7 文件保存功能优化

#### 核心流程

判断当前路径 -> 若无路径则另存为 -> 打开文件 -> 写入文本 -> 清除修改状态。

### 3.7.1 代码

```c++
void Widget::on_btnSave_clicked()
{
    if(!file.isOpen()){
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                "F:/LinuxEDStudy/qt",
                                tr("Text (*.txt *.doc)"));


    file.setFileName(fileName);
    if(!file.open(QIODevice::ReadWrite  | QIODevice::Text)){
        qDebug() << "file open error";
    }
    this->setWindowTitle(fileName+"  Notebook");
    }
    QTextStream out(&file);
    out.setCodec(ui->comboBox->currentText().toStdString().c_str());
    QString context = ui->textEdit->toPlainText();//ui->textEdit->toPlainText()获取 QTextEdit 控件纯文本内容的函数。
    out << context;
}
```



## 3.8 关闭优化

#### 概念简写

窗口关闭时，如果文档已修改，需要询问是否保存。

### 3.8.1 QMessageBox

#### 示例代码

```cpp
QMessageBox::StandardButton ret = QMessageBox::warning(
    this,
    "提示",
    "文档已修改，是否保存？",
    QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel
);
```

### 3.7.3 代码实现

```cpp
void Widget::on_btnClose_clicked()
{

    if (ui->textEdit->document()->isModified()) {
           QMessageBox::StandardButton reply;
           reply = QMessageBox::question(this,
                                         tr("Modifieding NO save"),
                                         tr("Modifieding save yes/no"),
                                         QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
           if (reply == QMessageBox::Save) {
                       on_btnSave_clicked();
            }else if (reply == QMessageBox::Discard) {
               if (file.isOpen()) {
                       file.close();
                   }
                   ui->textEdit->clear();
                   this->setWindowTitle("Notebook");
           }else if (reply == QMessageBox::Cancel) {
                    return;
           }else{}


    }
}

```



## 3.9 实现快捷键功能

#### 概念简写

快捷键让用户通过键盘触发功能。

### 3.9.1 快捷键开发基础

#### 示例代码

```cpp
//快捷键
    QShortcut *shortcutOpen = new QShortcut(QKeySequence("Ctrl+o"), this);
    QShortcut *shortcutsave = new QShortcut(QKeySequence("Ctrl+s"), this);

    connect(shortcutOpen, &QShortcut::activated, [this]() {
        on_btnFileOpen_clicked();  // 直接调用已有槽函数
    });
        connect(shortcutsave, &QShortcut::activated, [this]() {
              on_btnSave_clicked();  // 直接调用已有槽函数
    });





void Widget::zoomIn()
{
    QFont font = ui->textEdit->font();
    int newSize = font.pointSize() + 1;
    if (newSize <= 72) {  // 限制最大字号，避免过大
        font.setPointSize(newSize);
        ui->textEdit->setFont(font);
    }
}

void Widget::zoomOut()
{
    QFont font = ui->textEdit->font();
    int newSize = font.pointSize() - 1;
    if (newSize >= 6) {   // 限制最小字号
        font.setPointSize(newSize);
        ui->textEdit->setFont(font);
    }
}


```

### 3.9.2 记事本添加快捷键

#### 常用快捷键

- `Ctrl + O`：打开。
- `Ctrl + S`：保存。

## 3.10 实现字体放大缩小功能

### 3.10.1事件

#### 概念简写

事件是 Qt 对用户输入和系统通知的封装，如鼠标、键盘、绘图、关闭。

#### 事件处理过程

事件会经过： 事件派发 -> 事件过滤->事件分发->事件处理 几个阶段。

每一个Qt应用程序都对应一个唯一的 QApplication 应用程序对象，然后调用这个对象的 exec() 函数，这样Qt框架内部的事件检测就开始了

```c++
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow* w = new MainWindow;
	w.show();
	return a.exec();
}
```

1.当事件产生之后，Qt使用用应用程序对象调用 notify() 函数将事件发送到指定的窗口：

```c++
bool QApplication::notify(QObject *receiver, QEvent *e);
```

2. 事件在发送过程中可以通过事件过滤器进行过滤，默认不对任何产生的事件进行过滤。

```c++
// 需要先给窗口安装过滤器, 该事件才会触发
[virtual] bool QObject::eventFilter(QObject *watched, QEvent *event)；
```

3. 当事件发送到指定窗口之后，窗口的事件分发器会对收到的事件进行分类:

```

[override virtual protected] bool QWidget::event(QEvent *event);
```

4. 事件分发器会将分类之后的事件（鼠标事件、键盘事件、绘图事件。。。）分发给对应的事件处理器函数进行处理，每个事件处理器函数都有默认的处理动作（我们也可以重写这些事件处理器函
数），比如：鼠标事件：

```
// 鼠标按下
[virtual protected] void QWidget::mousePressEvent(QMouseEvent *event);
// 鼠标释放
[virtual protected] void QWidget::mouseReleaseEvent(QMouseEvent *event);
// 鼠标移动
[virtual protected] void QWidget::mouseMoveEvent(QMouseEvent *event)
```

#### 重写关闭事件

```cpp
//关闭窗口提示
void Widget::closeEvent(QCloseEvent *event)
{
     int ret = QMessageBox::warning(this, tr("My Application"),
                                   tr("close the window\nDo you want to close the window?"),
                                   QMessageBox::Ok | QMessageBox::No);
    switch(ret){
    case QMessageBox::Ok:
        event->accept();
        break;
    case QMessageBox::No:
        event->ignore();
        break;
    }
}

```

#### 事件方式实现字体放大缩小

流程

1、建一个自定义控件类MyTextEdit继承QTextEdit

2、实现方法MyTextEdit(QWidget *parent);

```
MyTextEdit::MyTextEdit(QWidget *parent):QTextEdit(parent){}

```

3、UI中提升类MyTextEdit作QTextEdit的派生类

4、重写三个事件

```
protected:
    void wheelEvent(QWheelEvent *e) override;//滚轮点击
    void keyPressEvent(QKeyEvent *e) override;//鼠标压
    void keyReleaseEvent(QKeyEvent *e) override;//鼠标松
```

代码

```c++
//mytextedit.h
#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H

#include <QCloseEvent>
#include <QTextEdit>



class MyTextEdit : public QTextEdit
{
public:
    MyTextEdit(QWidget *parent);

protected:
    void wheelEvent(QWheelEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;
private:
    bool ctrlKeyPressed = 0;
};

#endif // MYTEXTEDIT_H

```

```c++
//mytextedit.cpp
#include "mytextedit.h"

MyTextEdit::MyTextEdit(QWidget *parent):QTextEdit(parent){}
void MyTextEdit::wheelEvent(QWheelEvent *e)
{
    {
        if(ctrlKeyPressed == 1){
            if(e->angleDelta().y() > 0){
                zoomIn();
            }else if(e->angleDelta().y() < 0){
                zoomOut();
            }
            e->accept();
        }else{
            QTextEdit::wheelEvent(e);
        }
    }
}


void MyTextEdit::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Control){
        // qDebug() << "ctrl Pressed";
        ctrlKeyPressed = 1;
    }
    QTextEdit::keyPressEvent(e);
}

void MyTextEdit::keyReleaseEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Control){
        // qDebug() << "ctrl Release";
        ctrlKeyPressed = 0;
    }
    QTextEdit::keyPressEvent(e);
}
```

```c++
ctrlKeyPressed == 1：检查 Ctrl 键是否处于按下状态。

e->angleDelta().y()：获取鼠标滚轮垂直滚动的角度值（正：向上，负：向下）。

zoomIn()：增大文本编辑区的字体大小。

zoomOut()：减小文本编辑区的字体大小。

e->accept()：表示该滚轮事件已被处理，不再向上传递。

QTextEdit::wheelEvent(e)：调用基类的滚轮事件处理函数，执行正常的滚动行为（不缩放）。

//keyPressEvent
e->key() == Qt::Key_Control  判断本次键盘事件是否是由 Ctrl 键产生的

ctrlKeyPressed = 1：设置 Ctrl 键状态标志为“按下”。

QTextEdit::keyPressEvent(e)：调用基类事件处理，保证其他按键正常响应。

```



#### 事件过滤器

#### 1. 核心概念

- **安装过滤器**：调用 `target->installEventFilter(filter)`，其中 `target` 是被监视的对象，`filter` 是监视者（通常是一个 `QObject` 子类）。
- **重写 `eventFilter`**：在监视者类中重写 `bool eventFilter(QObject *watched, QEvent *event)` 方法。
- **处理事件**：在 `eventFilter` 中判断 `watched` 和 `event` 的类型，决定是否处理。
- **返回值**：
  - 返回 `true`：表示事件已被处理，不再继续传递（目标对象和后续过滤器都不会收到此事件）。
  - 返回 `false`：表示事件未被处理，Qt 会继续传递给目标对象的其他过滤器或目标对象本身。

```cpp
ui->textEdit->installEventFilter(this);
```

```c++
bool Widget::eventFilter(QObject *watched, QEvent *event)
{

    if(event->type() == QEvent::Wheel){
        if(QGuiApplication::keyboardModifiers() == Qt::ControlModifier){

             QWheelEvent *wheelEvent = dynamic_cast<QWheelEvent*>(event);
             if(wheelEvent->angleDelta().y() > 0){
                 zoomIn();
             }else if(wheelEvent->angleDelta().y()<0){
                 zoomOut();
             }
             return true;
        }

        return false;
    }
}

```

**`QGuiApplication::keyboardModifiers()`**：返回当前键盘上按下的**修饰键组合**（如 Ctrl、Shift、Alt、Meta）

`Qt::ControlModifier` 是 Qt 命名空间中定义的一个**修饰键标志常量**，用于表示键盘上的 **Ctrl 键**

`QWheelEvent *wheelEvent = dynamic_cast<QWheelEvent*>(event);` 

作用：将通用的 `QEvent*` 指针转换为具体的 `QWheelEvent*` 指针，以便调用滚轮专用方法（如 `angleDelta()`）。

## 3.12 记事本项目总结

### 总结

记事本项目覆盖 Qt Widgets 入门最重要的内容：UI、信号槽、文件、编码、状态更新、事件和快捷键。

| 章节   | 功能/组件                   | 核心用法摘要                                                 | 关键代码 / 注意事项                                          |
| :----- | :-------------------------- | :----------------------------------------------------------- | :----------------------------------------------------------- |
| 3.2.1  | QPushButton                 | 点击信号与槽连接                                             | `connect(ui->btnOpen, &QPushButton::clicked, this, &Widget::openFile);` 文字用 `setText()`，信号常用 `clicked()` |
| 3.2.2  | QHBoxLayout                 | 水平排列控件                                                 | `layout->addWidget(ui->btnOpen);`                            |
| 3.2.3  | QTextEdit                   | 文本编辑区                                                   | 普通文本：`setPlainText()` / `toPlainText()` 富文本：`setHtml()` |
| 3.2.4  | QVBoxLayout                 | 垂直排列控件                                                 | 用法同 QHBoxLayout，方向垂直                                 |
| 3.3.1  | 信号与槽基本连接            | 新式 connect 语法                                            | `connect(sender, &Sender::signal, receiver, &Receiver::slot);` 编译期检查更安全 |
| 3.3.2  | 自动槽函数                  | 按 `on_对象名_信号名` 命名                                   | `void on_btnOpen_clicked();` 自动关联 UI 中的按钮            |
| 3.3.3  | 自定义信号与槽              | 需要 Q_OBJECT 宏                                             | 声明 `signals: void mysignal();` 发射 `emit mysignal();`     |
| 3.3.4  | 四种连接方式                | ①转到槽 ②手动 SIGNAL/SLOT ③Lambda ④函数指针                  | 推荐 Lambda 和函数指针，类型安全                             |
| 3.4    | QFile 基础                  | 读写二进制/文本                                              | 打开：`file.open(QIODevice::ReadOnly)` 读取：`file.read(size)` / `readAll()` 写入：`file.write(data)` **必须判断打开是否成功** |
| 3.4.1  | QTextStream                 | 文本流式读写                                                 | 绑定 QFile：`QTextStream in(&file);` 编码：Qt5 `in.setCodec("UTF-8");`，Qt6 已移除，改用 UTF-8 默认 |
| 3.5    | QFileDialog 静态方法        | 快速获取文件路径                                             | `getOpenFileName()` 单文件 `getOpenFileNames()` 多文件 `getSaveFileName()` 保存 `getExistingDirectory()` 目录 |
| 3.5.1  | QFileDialog 单文件打开流程  | 实例化 → 设模式 → 过滤器 → exec()                            | 步骤详解见该章节                                             |
| 3.5.2  | QFileDialog 多文件打开      | `setFileMode(ExistingFiles)`                                 | `QStringList files = dialog.selectedFiles();` 遍历处理       |
| 3.5.3  | QFileDialog 保存文件        | `getSaveFileName` 返回路径                                   | 打开文件用 `WriteOnly` 模式，`QTextStream` 写入              |
| 3.6.2  | 记事本打开/保存/关闭        | 打开：clear → 读文件 → append 到 textEdit 保存：toPlainText() → 写文件 关闭：isOpen() → close → clear | 窗口标题显示文件名：`setWindowTitle(fileName+" Notebook");`  |
| 3.6.4  | QComboBox                   | 编码选择下拉框                                               | `currentIndexChanged(int)` 信号 获取当前文本：`currentText()` |
| 3.6.5  | 编码支持                    | Qt5 切换编码重新读取                                         | `in.setCodec(ui->comboBox->currentText().toUtf8().constData());` 需要 `seek(0)` 回到文件头再读 |
| 3.6.6  | 行列显示                    | 光标位置变化信号                                             | `connect(ui->textEdit, &QTextEdit::cursorPositionChanged, ...);` 通过 `QTextCursor` 获取 `blockNumber()+1` 和 `columnNumber()+1` |
| 3.6.8  | 当前行高亮                  | 使用 ExtraSelection                                          | 创建 `QTextEdit::ExtraSelection`，设置 `cursor`、`format.setBackground()`、`FullWidthSelection`，`setExtraSelections(list)` |
| 3.7    | 保存优化                    | 区分另存为和直接保存                                         | 若无路径则调用 `getSaveFileName`；若已打开则直接写入，保留原路径 |
| 3.8    | 关闭时提示保存              | QMessageBox + isModified()                                   | `QMessageBox::question(Save/Discard/Cancel)`，根据按钮执行对应操作 |
| 3.9    | 快捷键                      | QShortcut                                                    | `new QShortcut(QKeySequence("Ctrl+O"), this);` 连接 `activated` 信号调用槽函数 |
| 3.10.1 | 事件处理基础                | 重写事件处理器                                               | `closeEvent`、`wheelEvent`、`keyPressEvent` 等虚函数         |
| 3.10.1 | Ctrl+滚轮缩放（事件过滤器） | 安装过滤器，判断 Ctrl+Wheel                                  | `ui->textEdit->installEventFilter(this);` 在 `eventFilter` 中检查 `QEvent::Wheel` 和 `Qt::ControlModifier`，调用 `zoomIn()/zoomOut()` |
| 3.10.1 | 自定义控件重写事件          | 继承 QTextEdit                                               | 重写 `wheelEvent`、`keyPressEvent`、`keyReleaseEvent`，通过标志位记录 Ctrl 状态，组合实现缩放 |



# P4 串口调试助手项目

## 4.1 项目概述

### 功能简写

串口助手用于扫描串口、打开串口、接收数据、发送数据、十六进制显示和定时发送。

### 常用类

- `QSerialPort`
- `QSerialPortInfo`
- `QByteArray`
- `QTimer`

### 注意事项

- `.pro` 添加 `QT += serialport`。
- 串口通信是字节流。

## 4.2 串口通信核心代码开发

### 扫描串口

```cpp
foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
    ui->comboPort->addItem(info.portName());
}
```

### 打开串口

```cpp
serial = new QSerialPort(this);
serial->setPortName(ui->comboPort->currentText());
serial->setBaudRate(ui->comboBaud->currentText().toInt());
serial->setDataBits(QSerialPort::Data8);
serial->setParity(QSerialPort::NoParity);
serial->setStopBits(QSerialPort::OneStop);
serial->setFlowControl(QSerialPort::NoFlowControl);

if (serial->open(QIODevice::ReadWrite)) {
    connect(serial, &QSerialPort::readyRead, this, &Widget::readData);
}
```

### 读取数据

```cpp
void Widget::readData()
{
    QByteArray data = serial->readAll();
    ui->textReceive->append(QString::fromUtf8(data));
}
```

### 发送数据

```cpp
serial->write(ui->textSend->toPlainText().toUtf8());
```

### 十六进制

```cpp
ui->textReceive->append(data.toHex(' ').toUpper());
QByteArray send = QByteArray::fromHex(text.toUtf8());
```

### 定时发送

```cpp
QTimer *timer = new QTimer(this);
connect(timer, &QTimer::timeout, this, &Widget::on_btnSend_clicked);
timer->start(1000);
```

### 注意事项

- 参数不一致会乱码。
- `readyRead` 不代表收到完整一帧。
- 十六进制输入需要校验。
- 关闭串口要停止定时器。

---

# P5 网络调试助手

## 5.1 TCP 网络调试助手

### 功能简写

网络助手包含 TCP 服务端和 TCP 客户端，用于连接、收发、显示消息。

## 5.1.1 项目概述

### 功能

- 服务端监听。
- 客户端连接。
- 双方发送消息。
- 显示连接状态。
- 区分消息来源。

## 5.1.2 开发流程

1. `.pro` 添加 `QT += network`。
2. 设计服务端 UI 和客户端 UI。
3. 服务端创建 `QTcpServer`。
4. 客户端创建 `QTcpSocket`。
5. 连接信号槽。
6. 实现收发和断开处理。

## 5.1.3 Qt TCP 服务器关键流程

```cpp
tcpServer = new QTcpServer(this);
connect(tcpServer, &QTcpServer::newConnection, this, &ServerWidget::onNewConnection);
tcpServer->listen(QHostAddress::Any, port);
```

## 5.1.4 Qt TCP 客户端关键流程

```cpp
tcpSocket = new QTcpSocket(this);
connect(tcpSocket, &QTcpSocket::connected, this, &ClientWidget::onConnected);
connect(tcpSocket, &QTcpSocket::readyRead, this, &ClientWidget::onReadyRead);
tcpSocket->connectToHost(ip, port);
```

## 5.1.2 TCP 协议

### 概念简写

TCP 是可靠的、面向连接的字节流协议。

### 注意事项

- TCP 不保证一次 `readAll()` 就是一条完整消息。
- 需要应用层协议解决粘包和半包。

## 5.1.4 Socket

### 概念简写

Socket 是网络通信端点，由 IP 和端口标识。

### 注意事项

- 服务端监听端口。
- 客户端连接服务端 IP + 端口。

## 5.2 UI 设计

### 建议控件

- IP 输入框。
- 端口输入框。
- 监听/连接按钮。
- 发送文本框。
- 接收显示区。
- 客户端列表。

## 5.3 网络通信核心代码

### 常用类

- `QTcpServer`
- `QTcpSocket`
- `QHostAddress`
- `QByteArray`

## 5.3.1 创建 TCP 服务端核心代码

```cpp
void ServerWidget::onNewConnection()
{
    QTcpSocket *client = tcpServer->nextPendingConnection();
    connect(client, &QTcpSocket::readyRead, this, &ServerWidget::onReadyRead);
    connect(client, &QTcpSocket::disconnected, this, &ServerWidget::onDisconnected);
}
```

## 5.3.2 创建 TCP 客户端核心代码

```cpp
tcpSocket->connectToHost(ui->lineIP->text(), ui->linePort->text().toUShort());
tcpSocket->write(ui->textSend->toPlainText().toUtf8());
```

## 5.4 TCP 服务端项目开发

### 核心

服务端要能管理多个客户端，并在客户端断开时清理。

### 注意事项

- 可用 `QMap<QString, QTcpSocket*>` 保存客户端。
- 断开后从容器删除。

## 5.5 TCP 客户端项目开发

### 核心

客户端负责连接、断开、发送、接收和状态显示。

## 5.6 项目总结

### 总结

网络助手重点是理解 TCP 流式通信、Socket 生命周期和消息边界。

---

# P6 自定义控件

## 6.1 QPaintEvent 绘图事件

### 概念简写

`paintEvent()` 是控件重绘时自动调用的函数。

### 示例代码

```cpp
void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawLine(0, 0, 100, 100);
}
```

### 注意事项

- 不要手动调用 `paintEvent()`。
- 刷新用 `update()`。

## 6.2 QPainter 画家

### 概念简写

`QPainter` 用于绘制图形、文字和图片。

## 6.2.1 概述

### 常用函数

- `drawLine`
- `drawRect`
- `drawEllipse`
- `drawText`
- `drawPixmap`
- `setPen`
- `setBrush`

## 6.2.2 渐变色

### 概念简写

渐变用于平滑过渡颜色。

## 6.2.2.1 线性渐变

```cpp
QLinearGradient g(0, 0, width(), 0);
g.setColorAt(0, Qt::red);
g.setColorAt(1, Qt::blue);
painter.setBrush(g);
```

## 6.2.2.2 径向渐变

```cpp
QRadialGradient g(width()/2, height()/2, 100);
g.setColorAt(0, Qt::white);
g.setColorAt(1, Qt::black);
```

## 6.2.2.3 圆锥形渐变

```cpp
QConicalGradient g(width()/2, height()/2, 0);
g.setColorAt(0, Qt::red);
g.setColorAt(0.5, Qt::yellow);
g.setColorAt(1, Qt::red);
```

## 6.3 坐标转移

### 概念简写

通过 `translate`、`rotate`、`scale` 改变坐标系，简化绘图。

### 示例代码

```cpp
painter.translate(width()/2, height()/2);
painter.rotate(30);
```

### 注意事项

- 变换影响后续绘制。
- 用 `save()`/`restore()` 保护状态。

## 6.4 画雷达案例

### 思路

- 将原点移动到中心。
- 循环旋转坐标画射线。
- 画多个同心圆。
- 用定时器旋转扫描线。

## 6.5 仪表表盘

### 思路

- 画外圈。
- 画刻度。
- 画数字。
- 画指针。
- 画内环和中心点。
- 用 `QTimer` 动态更新。

## 6.5.1 初步完成

### 重点

先完成基础圆盘和刻度，不追求美观。

## 6.5.2 稍微美化

### 重点

添加颜色、渐变、抗锯齿。

## 6.5.3 优化数字显示后代码整理

### 重点

数字位置用三角函数计算。

```cpp
double x = radius * qCos(qDegreesToRadians(angle));
double y = radius * qSin(qDegreesToRadians(angle));
```

## 6.5.4 画一个指针

```cpp
QPolygon pointer;
pointer << QPoint(0, -70) << QPoint(-5, 0) << QPoint(5, 0);
painter.drawPolygon(pointer);
```

## 6.5.5 内环

### 作用

内环让表盘更有层次，也可遮住指针尾部。

## 6.5.6 完结

### 总结

自定义控件要把绘制拆成多个函数，例如 `drawBg()`、`drawScale()`、`drawPointer()`。

## 6.6 汽车表盘参考样式

### 扩展

- 增加报警色区。
- 增加单位显示。
- 增加平滑动画。
- 增加不同主题。

---

# P7 天气预报项目

## 7.1 项目概述

### 功能简写

天气项目通过 HTTP 获取天气 JSON，解析后显示城市、温度、天气、风力、空气质量和未来预报。

## 7.2 stylesheet 样式

### 概念简写

QSS 类似 CSS，用于设置 Qt 控件样式。

### 示例代码

```cpp
ui->pushButton->setStyleSheet(
    "QPushButton { background: #2d8cf0; color: white; border-radius: 4px; }"
);
```

### 注意事项

- 样式复杂时放到 `.qss` 文件。
- 注意选择器范围，避免影响所有子控件。

## 7.3 窗体无状态栏 - 关闭

### 用法

```cpp
setWindowFlags(Qt::FramelessWindowHint);
```

### 注意事项

- 无边框后要自己做关闭、最小化、拖动。

## 7.4 窗口跟随移动

### 示例代码

```cpp
void WeatherWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragPos = event->globalPos() - frameGeometry().topLeft();
    }
}

void WeatherWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPos() - dragPos);
    }
}
```

## 7.5 天气预报数据接口

### 用法

接口通常返回 JSON，需要根据文档读取字段。

### 注意事项

- API key 不建议硬编码。
- URL 中中文城市名要编码。
- 处理接口失败、字段缺失、网络错误。

## 7.6 软件开发网络通信架构

### 概念简写

客户端和服务器通过网络协议交换数据，天气软件属于客户端请求服务器 API。

## 7.6.1 BS 架构 / CS 架构

### 对比

- BS：Browser/Server，浏览器访问服务器。
- CS：Client/Server，专用客户端访问服务器。

## 7.6.2 HTTP 基本概念

### 核心

HTTP 是请求-响应协议，客户端发送请求，服务器返回响应。

### 常见方法

- GET：获取数据。
- POST：提交数据。

## 7.7 Qt 的 HTTP 编程

### 示例代码

```cpp
QNetworkAccessManager *manager = new QNetworkAccessManager(this);
connect(manager, &QNetworkAccessManager::finished, this, &WeatherWidget::onReplyFinished);
manager->get(QNetworkRequest(QUrl(url)));
```

### 注意事项

- `.pro` 添加 `QT += network`。
- `QNetworkReply` 用完 `deleteLater()`。

## 7.8 JSON 数据

### 概念简写

JSON 是常见数据交换格式，包含对象、数组、字符串、数字、布尔值。

## 7.8.1 概述

### 示例

```json
{
  "city": "福州",
  "tem": "25",
  "data": []
}
```

## 7.8.2 Qt 生成 JSON 数据

### 示例代码

```cpp
QJsonObject obj;
obj["city"] = "福州";
obj["temp"] = 25;

QJsonDocument doc(obj);
QByteArray json = doc.toJson();
```

## 7.8.3 Qt 解析 JSON 数据

### 示例代码

```cpp
QJsonDocument doc = QJsonDocument::fromJson(data);
QJsonObject root = doc.object();
QString city = root["city"].toString();
QJsonArray arr = root["data"].toArray();
```

### 注意事项

- 解析前检查错误。
- 字段可能为空。
- 类型不匹配时取值可能失败。



---

# 综合复习路线

## 第一阶段：C++ 基础

重点：类、对象、构造析构、引用、指针、继承、多态、模板、STL。

## 第二阶段：Qt Widgets

重点：控件、布局、信号槽、文件读写、事件。

## 第三阶段：项目实战

顺序：记事本 -> 串口助手 -> 网络助手 -> 自定义仪表盘 -> 天气预报。

## 第四阶段：排错能力

重点：编译错误、链接错误、模块未添加、编码问题、对象生命周期、网络半包粘包。

---

# 高频易错点

| 问题 | 原因 | 解决 |
|---|---|---|
| 找不到 Qt 类头文件 | `.pro` 没加模块 | 添加 `QT += xxx` 后运行 qmake |
| 信号槽不触发 | 连接错误或对象销毁 | 使用新语法 connect，检查生命周期 |
| 中文乱码 | 编码不一致 | 统一 UTF-8，必要时设置 QTextCodec |
| 文件保存后仍提示修改 | 未清除 modified 状态 | `document()->setModified(false)` |
| 串口乱码 | 参数不一致 | 检查波特率、数据位、校验位、停止位 |
| TCP 消息错乱 | 粘包/半包 | 设计应用层协议 |
| 绘图变形 | 未处理窗口缩放 | 使用 `qMin(width(), height())` |
| 界面卡死 | UI 线程执行耗时任务 | 用异步、线程或定时器拆分 |
| 对象重复释放 | 手动 delete 有父对象子对象 | Qt 对象设置父对象后不要重复 delete |
| Linux 运行缺库 | 动态库缺失 | 用 `ldd` 查看依赖 |

