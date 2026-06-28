# 第一章前言

## 思维导图

<img src="F:\Linux嵌入式开发\C学习\笔记\前言.png" alt="前言" style="zoom:33%;" />

## 一、程序基础概念

1. **什么是程序**

- 计算机程序 = 软件，是计算机可执行的指令集合
- 运行载体：传统 PC、手机、嵌入式设备、智能终端
- 程序本质：**数据结构 + 算法**

1. **进程与程序**

- 程序：静态代码文件
- 进程：跑起来的程序，动态概念

------

## 二、程序应用领域（C 语言核心方向）

1. 上位机开发

   C++(MFC/QT)、Java(Swing)、C#、Python(pyqt)、C(Gtk/Minigui)

2. 操作系统内核

   C 语言 + 汇编

3. 后端服务器

   Java、PHP、Go、C#

4. 嵌入式领域

   C51（门禁）、STM32（无人机）、ARM Linux

5. 智能终端

   迎宾机器人、人脸识别安检、快递柜

------

## 三、数据结构（对数据的描述）

1. **数据类型**

- 整型：整数
- 浮点型：小数
- 字符型：单个字符
- 复合型：结构体

1. 组织方式

   数组、链表、树、图

------

## 四、算法（对操作的描述）

1. **定义**：告诉计算机的操作步骤，对数据产生作用
2. **分类**

- 逻辑型：条件判断、流程控制
- 数学型：求和、音视频处理（维纳滤波、AEC/AGC/NS）

------

## 五、程序生成三步流程

1. **编程**：用 C/C++/Java 等写源代码
2. **编译**：预处理 → 编译 → 汇编 → 链接
3. **执行**：运行二进制机器码（0101…）

------

## 六、计算机语言层级

1. **机器语言**：二进制 0/1，计算机直接执行
2. **符号语言**：汇编语言
3. **高级语言**

- 面向过程：C 语言
- 面向对象：C++、Java、PHP、C#

------

## 七、C 语言高效学习法 

1. **看视频**

- 不拉进度条
- 熟悉知识点可 1.5 倍速

1. **敲代码**

- 理解 → 对着打 → 默打
- 编译出错不可怕，积累错误提示
- 代码必须调试通过，不半途而废

1. **多总结**

- 记录错误、写博客 / 笔记
- CSDN、云笔记、QQ 空间均可
- **本人使用.md文档每日上传文件至github个人仓库**

1. **初期原则**

- 变量名简单、算法不纠结，先实现功能

------

## 八、学习考核标准

用**链表嵌套**完成：学生成绩管理系统

# 第二章初识 C 语言

思维导图

<img src="F:\Linux嵌入式开发\C学习\笔记\初识C语言.png" alt="初识C语言" style="zoom:33%;" />

## 一、开发环境与工具

### 1. 常用开发工具

- IDE：VSCode、Dev-C++、啊哈 C、VC++、TurboC
- 轻量编辑器：**Notepad++**（小巧、支持 C 语言语法高亮）

### 2. Windows 开发环境搭建

- 编辑：Notepad++，新建 `.c` 后缀文件/之前安装过Vscode
- 编译：安装 **MinGW**，配置 **GCC** 环境变量
- 目的：让 CMD 任意目录都能使用 gcc 命令

------

## 二、编译与运行指令

### 1. 编译命令

plaintext

```
gcc 文件名.c -o 生成的程序名
```

例：`gcc test.c -o pro` → 生成 pro.exe  //window默认生成a.exe

### 2. 运行

直接在 CMD 里输入生成的 exe 文件名执行

------

## 三、C 语言程序基础框架

```c
#include<stdio.h>
	int main()
{
    return 0;
}
```

- 写任何代码前**先搭最小框架**
- 固定结构，保证程序能正常编译运行

------

## 四、变量（核心）

### 1. 变量定义

- 程序运行中**值可以改变**的量
- 规则：**先定义，再使用**
- 比喻：内存 = 蜂巢快递柜，变量 = 可变化的存储格

### 2. 标识符（变量 / 函数名）规则

- 组成：字母、数字、下划线
- 开头：只能是**字母或下划线**，不能数字开头
- 区分大小写
- 命名风格：驼峰、下划线、拼音，尽量**顾名思义**

------

## 五、基本数据类型

1. 整型 int
   - 4 字节，存整数
2. 字符型 char
   - 1 字节，存 ASCII 码字符
3. 浮点型 float
   - 4 字节，存小数
4. 常量
   - 程序运行中值不可变
   - 符号常量：`#define PI 3.14`

5.  **ASCII 速查**

   |  字符   | ASCII 码 | 字符 | ASCII 码 |
   | :-----: | :------: | :--: | :------: |
   |   `0`   |    48    |  A   |  **65**  |
   |   `1`   |    49    | `B`  |    66    |
   |   `9`   |    57    | `Z`  |    90    |
   | **`a`** |  **97**  | `z`  |   122    |
   |  空格   |    32    | `.`  |    46    |

------

## **六、****输入输出函数

### printf基础用法

#### 一、基础用法

##### 1. 原样输出字符串

直接写双引号内容，无占位符，原样打印

```
printf("hello world");
```

##### 2. 格式占位符（核心）

语法：`printf("格式串", 变量/表达式1, 变量/表达式2...);`

格式串中用 `%+格式字符` 匹配对应数据。

------

#### 二、常用占位符 + 完整示例

##### 1. % d 十进制整数

用于 `int` 整型

```
int a = 100;
printf("a = %d\n", a);  // 输出：a = 100
```

##### 2. % c 单个字符 / ASCII 码输出

可直接存字符，也可使用 ASCII 数值

```
char ch1 = 'A';
int num = 65;
printf("字符：%c\n", ch1);  // 输出：字符：A
printf("ASCII转字符：%c\n", num); // 输出：ASCII转字符：A
```

##### 3. % s 字符串

输出 `char` 字符串（以 `\0` 结尾）

```
char str[] = "好好学习";
printf("字符串：%s\n", str); // 输出：字符串：好好学习
```

##### 4. % f 浮点数（小数）

默认保留**6 位小数**；`%.nf` 控制保留 n 位小数

```
double f = 3.1415926;
printf("默认小数：%f\n", f);    // 3.141593
printf("保留2位小数：%.2f\n", f); // 3.14
printf("保留4位小数：%.4f\n", f); // 3.1416
```

##### 5. % x / % X 十六进制

- `%x`：小写字母 a~f
- `%X`：大写字母 A~F

```
int val = 255;
printf("小写十六进制：%x\n", val); // ff
printf("大写十六进制：%X\n", val); // FF
```

##### 6. % p 输出变量地址

必须搭配**取地址符 &**，打印内存地址

```
int b = 20;
printf("变量b的地址：%p\n", &b);
```

------

#### 三、组合输出（多个占位符）

一条语句同时输出多种类型数据

```
int age = 18;
char sex = 'M';
double score = 95.5;

printf("年龄：%d，性别：%c，分数：%.1f\n", age, sex, score);
// 输出：年龄：18，性别：M，分数：95.5
```

------

#### 四、补充知识点

##### 1. 换行符 \n

`\n` 代表换行，放在格式串中实现换行，是最常用转义字符。

##### 2. 数据类型自动转换

不同类型运算 / 输出时，会发生**隐式类型转换**

例：整型 + 浮点型，结果自动转为浮点型

```
int x = 5;
double y = 2.5;
double res = x + y;
printf("结果：%f\n", res); // 7.500000
```

##### 3. 易错点

1. `%c` 只能输出**单个字符**，不能放字符串；
2. `%p` 一定要加 `&`（取变量地址），不能直接写变量名；
3. 占位符数量、顺序、类型，必须和后面参数一一对应，否则乱码 / 报错。

#### 五、合集示例

```c
#include<stdio.h>

int main(){
	//printf练习 
	int a=65;
	float b=3.4;
	char c='a';
	char str[] = "好好学习";
	float res=a+b;
	
	printf("整形a=%d\n",a);
	printf("字符串b=%f\n",b);
	printf("字符c=%c\n",c);
	printf("字符c=%c\n",a);
	printf("字符串str：%s\n", str);
	printf("16进制a=%x\n",a);
	printf("取地址a=%p\n",&a);
	printf("res=%d+%f=%.1f\n",a,b,res);
	
	
	return 0;
}
```



### scanf

#### 一、基础概念 

1. **给普通变量输入，必须加 `&` 取地址**
2. **格式串里写了什么符号，输入时必须原样输入**
3. 多个变量输入，**用空格 / 回车分隔**最安全
4. 输入类型必须和变量类型匹配

------

#### 二、完整可运行示例代码

```
#include<stdio.h>
	int main(){
		//scanf练习
		int age;
		float score;
		char NO;
		char name[20];
		
		
		printf("请输入你的年龄");
		scanf("%d",&age);
		
		printf("请输入你的得分");
		scanf("%f",&score);		
		
		printf("请输入你的号码");
		scanf(" %c",&NO);		
		
		printf("请输入你的姓名");
		scanf("%s",name);		
		
		printf("\n===== 输入结果 =====\n");
		printf("年龄：%d\n", age);
		printf("分数：%.2f\n", score);
		printf("号码：%c\n", NO);
		printf("姓名：%s\n", name);
		
		return 0;
	}
	
```

------

#### 三、重点易错点

##### 1. 什么时候加 `&`？

- ```
  int、float、char 变量 → 必须加 &
  ```

  ```
  scanf("%d", &a); ✅
  scanf("%f", &b); ✅
  ```

- 字符串数组 → 不加 &

  ```
  char str[20];
  scanf("%s", str); ✅
  ```

##### 2. 格式串有符号，输入必须对应

```
// 代码这么写：
scanf("%d-%d", &a, &b);

// 输入必须这样：
18-20 ✅
```

##### 3. 多个输入，用空格 / 回车分

```
scanf("%d %f", &a, &b);
输入：65 3.4 ✅
```

------

#### 四、最简单的多变量输入模板

```
#include <stdio.h>
int main(){
    int a;
    float b;
    
    printf("请输入整数和小数：");
    scanf("%d %f", &a, &b);  // 空格分开
    
    printf("a=%d, b=%.2f", a, b);
    return 0;
}
```

------

##### 总结

1. **变量输入 `&` 不能忘，字符串除外**
2. **格式串符号 = 输入符号**
3. **多变量用空格分隔最安全**
4. **`%d`整型、`%f`浮点、`%c`字符、`%s`字符串**



###  其他输入输出

#### 单个字符：`getchar()` / `putchar()`

- **getchar()**：从键盘读取**一个字符**
- **putchar()**：输出**一个字符**
- 只能处理**单个字符**，不能处理字符串

##### 示例代码

```
#include<stdio.h>
	int main(){
		//getchar()/putchar()练习
		char ar;
		
		printf("请输入一个字符：");
		ar = getchar();
		
		printf("你输出的字符是：");
		putchar(ar);
		putchar('\n');
		return 0;
	}
```

------

#### 字符串：`puts()` / `gets()`

- **puts()**：输出字符串，**自动换行**
- **gets()**：读取一行字符串（不推荐用，有安全隐患，后面讲数组用 fgets）

##### 示例代码

```
#include<stdio.h>
	int main(){
		char str[100];
		printf("请输入一行内容");
		gets(str);
		printf("你输入的内容是：");
		puts(str);
		puts("我是第二行");
		
		return 0;
	}
```



------

## 七、基础练习

1. 输入两个数，输出加减乘除结果

   第一次代码错误   出发需要强制转化

代码

```c
#include<stdio.h>
	int main(){
		int a;
		int b;
		printf("请输入两个数字空格隔开");
		scanf("%d %d",&a,&b);
		
		printf("两数之和%d+%d=%d\n",a,b,(a+b));
		printf("两数之差%d-%d=%d\n",a,b,(a-b));
		printf("两数之积%dx%d=%d\n",a,b,(a*b));
		printf("两数之除%d/%d=%.1f\n",a,b,((float)a/b));
		
		 return 0;
	}
```

2.请编程序将 “China” 译成密码，密码规律是：用原来的字母后面第 4 个字母代替原来的字母。例如，字母 “A” 后面第 4 个字母是 “E”，用 “E” 代替 “A”。因此，“China” 应译为 “Glmre”。请编一程序，用赋初值的方法使 c1,c2,c3,c4,c5 这 5 个变量的值分别为 'C','h','i','n','a'，经过运算，使 c1,c2,c3,c4,c5 分别变为 'G','l','m','r','e'。分别用 putchar 函数和 printf 函数输出这 5 个字符。

代码

```
#include<stdio.h>
	int main(){
		char a1;
		char a2;
		char a3;
		char a4;
		char a5;

		printf("请输入第一个字符a1:");
		scanf("%c",&a1);
		
		printf("请输入第一个字符a2:");
		scanf(" %c",&a2);
		
		printf("请输入第一个字符a3:");
		scanf(" %c",&a3);
		
		printf("请输入第一个字符a4:");
		scanf(" %c",&a4);
		
		printf("请输入第一个字符a5:");
		scanf(" %c",&a5);
		
		printf("a1=%c\na2=%c\na3=%c\na4=%c\na5=%c\n",a1,a2,a3,a4,a5);
		
		printf("a1=%d\na2=%d\na3=%d\na4=%d\na5=%d\n",a1,a2,a3,a4,a5);
	//China=a1=67，a2=104，a3=105，a4=110，a5=97
	//GImre=a1=71，a2=73，a3=109，a4=114，a5=101
		
		
		printf("%c%c%c%c%c=%c%c%c%c%c\n",a1,a2,a3,a4,a5,a1+4,a2-31,a3+4,a4+4,a5+4);
		
		a1=a1+4;
		a2=a2-31;
		a3=a3+4;
		a4=a4+4;
		a5=a5+4;
		putchar(a1);
		putchar(a2);
		putchar(a3);
		putchar(a4);
		putchar(a5);
	
		
		return 0;
	}
```

# 第三章流程控制

<img src="F:\Linux嵌入式开发\C学习\笔记\流程控制.png" alt="流程控制" style="zoom:33%;" />

## 一、程序流程结构

- **顺序结构**：从上到下依次执行
- **选择结构**：满足条件才执行某段代码
- **循环结构**：满足条件就重复执行

------

## 二、选择结构（判断）

### 1. if 语句

#### （1）单分支

```
if(条件)
{
    语句;
}
```

条件为真，执行大括号里代码。

#### （2）双分支

```
if(条件)
{
    语句1;
}
else
{
    语句2;
}
```

#### （3）多分支

```
if(条件1) {}
else if(条件2) {}
else if(条件3) {}
else {}
```

#### （4）if 嵌套

if 里面再写 if/else，用于多层判断。

------

### 2. 逻辑运算符

- **&& 与**：两个条件都真才真
- **|| 或**：一个真就真
- **! 非**：取反

示例：

```
if(age>=18 && score>=60)
```

------

### 3. switch…case 语句

适合**固定值匹配**，比如成绩等级、菜单选择。

```
switch(变量)
{
    case 值1: 语句; break;
    case 值2: 语句; break;
    default: 都不满足执行;
}
```

**必须写 break**，否则会 “穿透” 执行。

------

## 三、循环结构

### 1. while 循环

先判断，后执行。

```
while(条件)
{
    循环体;
}
```

### 2. do…while 循环

先执行一次，再判断。**至少执行 1 次**。

```
do
{
    循环体;
} while(条件);
```

### 3. for 循环（最常用）

适合**已知循环次数**。

```
for(初始化; 判断条件; 更新)
{
    循环体;
}
```

- 三个表达式都可省略
- 全省略 = 死循环

### 4. 循环嵌套

循环里面套循环，用于打印矩阵、表格。

------

## 四、跳转语句

- **break**：跳出**整个循环 /switch**
- **continue**：跳过本次，直接进入下一次循环

------

## 五、练习代码

### if示例

```c
//示例1：
    #include<stdio.h>
	int main(){
		//if判断练习1
		int money;
		printf("请问你有多钱：");
		scanf("%d",&money);
		if(money>100){
			
			puts("你是个有钱人");
		}
		printf("测试完成\n");
		printf("测试结果%d",money>100);
		return 0;
	}
```

```c
//示例2：
#include<stdio.h>
	int main(){
		int atHomeYesNO;
		puts("你是否在家,输入一在家输入二不在");
		scanf("%d",&atHomeYesNO);
		
		if(atHomeYesNO==1){
			
			printf("扑到你");
		}
		puts("xxxx");
		
	}
```

```c
//示例3
#include<stdio.h>
	int main(){
		int data1;
		int data2;
		int datatmp;
		
		printf("请输入两个数字:从小到大排");
		scanf("%d %d",&data1,&data2);
		if(data1>data2){
			printf("=====\n");
			datatmp=data1;//data1>data2时 进入
			data1=data2;
			data2=datatmp;
		}
		printf("%d %d",data1,data2);
		
	}
```



```
//逻辑运算符
#include<stdio.h>
	int main(){
		int rich;
		int handsome;
		int spend;
		printf("你是否富裕 富裕扣1 不富裕扣0\n");
		scanf("%d",&rich);
		if(rich!=1){
			
			puts("我们不合适");
			return -1;
		}
		printf("你是否帅气 帅气 扣1 不帅气 扣0\n");
		scanf("%d",&handsome);
		
		printf("你是否给我花钱 花钱扣1 不花钱扣0\n");
		scanf("%d",&spend);
		
			if(handsome==1&&spend==1){
			
			puts("我要嫁给你");
		}	else{
			printf("我们不合适捏");
		}		
			
		return 0;
	}
```



#### 2、if   else输入一个字符，大转小

```
#include<stdio.h>
	int main(){
		char ca;
		puts("请输入一个字符");
		scanf("%c",&ca);
		
		if(ca>=65&&ca<=90){
			ca=ca+32;
			printf("%c",ca);
		}else if(ca>=97&&ca<=122){
			printf("%c",ca);
		}else{
			puts("输入异常");
		}
		
		
		return 0;
		
	}
```

#### 用 switch 算商品折扣

```
#include<stdio.h>
	int main(){
	float zhekou;
	int s;
	puts("请输入的要购买的商品价值");
	scanf("%d",&s);
	if(s>0&&s<250){
		puts("没有折扣");
		
	}
	else if(s>=250&&s<500){
		zhekou=0.02;
		printf("折扣为%.2f\n",zhekou);
	}
	else if(s>=500&&s<1000){
		zhekou=0.05;
		printf("折扣为%.2f\n",zhekou);
		
	}
	else if(s>=1000&&s<2000){
		zhekou=0.08;
		printf("折扣为%.2f\n",zhekou);
	}
	else if(s>=2000&&s<3000){
		zhekou=0.10;
		printf("折扣为%.2f\n",zhekou);
	}
	else{
	 zhekou=0.15;
		printf("折扣为%f\n",zhekou);
	}
	
		return 0;
}
```

#### 函数判断输入x的值，输出y相应的值

```
#include<stdio.h>
	int main(){
		int x;
		int y;
		printf("请输入一个数字");
		scanf("%d",&x);
		if(x<1){
		   y=x;
			printf("y=%d",y);
		}
		
		else if(x>=1&&x<10){
			y=(2*x-1);
			printf("y=2*%d-1=%d",x,y);
		}
		
		else if(x>=10){
			y=(3*x-11);
			printf("y=3*%d-11=%d",x,y);
		}	
		
		return 0;
	}
```



### for 循环 

打印矩阵

```
#include<stdio.h>
	int main(){
		
		for(int i=1;i<=4;i++){
			for(int j=1;j<=5;j++){
				printf("%d ",i*j);
				
			}
			printf("\n");
		}
		
		return 0;
	}
```



#### 1~100 求和

```
#include<stdio.h>
int main()
{
    int sum=0;
    for(int i=1;i<=100;i++)
    {
        sum=sum+i;
    }
    printf("%d",sum);
    return 0;
}
```

#### 嵌套循环

### break 与 continue

```
// break：到5就停止
for(int i=1;i<=10;i++){
    if(i==5) break;
    printf("%d ",i);
}

// continue：跳过5，继续后面
for(int i=1;i<=10;i++){
    if(i==5) continue;
    printf("%d ",i);
}
```



## 六、作业

1. 输入三个数，从小到大输出

   ```
   #include<stdio.h>
   	int main(){
   		int a,b,c;
   		int tmp;
   		printf("请输入三个数字");
   		scanf("%d %d %d",&a,&b,&c);
   
   		if(a>b){
   		 tmp=a;
   		 a=b;
   		 b=tmp;//此时a的值小于b的值
   		}
   		if(a>c){
   		 tmp=c;
   		 a=c;
   		 c=tmp;//此时a的值小于c的值
   		}
   		if(b>c){
   		 tmp=b;
   		 b=c;
   		 c=tmp;
   		}
   		
   		printf("%d %d %d ",a,b,c);
   		
   		return 0;
   	}
   ```

   2、成绩分级

   ```
   #include<stdio.h>
   	int main(){
   		int score;
   		int dengji;
   		
   		printf("请输入一个你的成绩：");
   		scanf("%d",&score);
   		if(score>=90&&score<=100){
   			puts("你的成绩为A");
   		}else if(score>=80&&score<=89){
   			puts("你的成绩为B");
   		}else if(score>=70&&score<=79){
   			puts("你的成绩为C");
   		}else if(score>=60&&score<=69){
   			puts("你的成绩为D");
   		}else if(score<=60&&score>=0){
   			puts("你的成绩为E");
   		}else{
   			puts("输入的成绩非法，请重新输入");
   		}
   		
   		return 0;
   	}
   ```

   

   

2. 输入两个正整数m和n求其最大公约数和最小公倍数

   **最大公约数（GCD）**

   能同时整除 m 和 n 的**最大正整数**

   例：12 和 18 → 最大公约数是 **6**

   **最小公倍数（LCM）**

   能同时被 m 和 n 整除的**最小正整数**

   公式：**最小公倍数 = m × n / 最大公约数**

   ```
   #include<stdio.h>
   	int main(){
   		int m,n;
   		int max;
   		printf("请输入两个数字");
   		scanf("%d %d",&m,&n);
   		//最大公约数
   		for(int i=1;m>=i&&n>=i;i++){
   			
   			if(m%i==0&&n%i==0){
   			
   			max=i;
   		
   		}	
   		}
   		printf("%d\n",max);
   		//最小公倍数
   
   		printf("%d",m*n/max);
   		return 0;
   	}
   ```

   

3. 求水仙花数/公式：`百位³ + 十位³ + 个位³ = 原数`

```
#include<stdio.h>
	int main(){
		for(int i=999;i>100;i--){	
		int c=i%10;
		int b=i/10%10;
		int a= i/100;
			
		if(a*a*a+b*b*b+c*c*c==a*100+b*10+c)
			printf("水仙花数%d\n",i);
		}
		
		return 0;
	}
```

# 第四章 数组

![数组](F:\Linux嵌入式开发\C学习\笔记\数组.png)

## 一、数组是什么

- **数组**：把**多个相同类型**的数据，按顺序存在一段**连续内存**里。

- 作用：统一管理一批数据，不用定义很多变量。

- 例子：10 个学生成绩 → int score [10];

- `sizeof(数组)` → **总字节数**

  `sizeof(数组[0])` → **一行 / 一个元素的字节**

  **数组长度 = 总字节 / 单个字节**

------

## 二、一维数组

### 1. 定义

```
类型 数组名[元素个数];
```

```
int a[10];    // 整型数组，10个元素
char b[20];   // 字符数组
float c[5];   // 浮点数组
```

### 2. 下标（编号）

- 从 **0 开始**
- a [0] 第 1 个
- a [1] 第 2 个
- ...
- a [9] 第 10 个

### 3. 初始化

```
int a[5] = {1, 2, 3, 4, 5};   // 全部赋值
int a[5] = {1, 2};            // 部分赋值，后面补0
int a[5] = {0};               // 全部清零
int a[]  = {1,2,3,4};         // 自动算长度
for(int i=0; i<5; i++){       //循环初始化
    a[i]=i;
}
```

### 4. 遍历（最常用）

```
int a[5] = {1,2,3,4,5};
for(int i=0; i<5; i++){
    printf("%d ", a[i]);
}
```

------

## 三、二维数组

### 1. 定义

```
类型 数组名[行][列];
```

例如：

```
int a[2][3];  // 2行3列，共6个元素
```

### 2. 理解

- 可以看成**表格**
- 本质是：**数组里面装数组**

### 3. 初始化

```
int a[2][3] = {
    {1,2,3},
    {4,5,6}
};

int k=0;
for(int i=0; i<2; i++){
    for(int j=0; j<3; j++){
        a[i][j]=k++;
    }
}
```

### 4. 遍历（双层循环）

```
for(int i=0; i<2; i++){
    for(int j=0; j<3; j++){
        printf("%d ", a[i][j]);
    }
}
```

------

## 四、数组经典操作

### 1. 数组逆序

```
#include<stdio.h>
int main(){
		int arry[5];
		for(int i=0;i<5;i++){
			arry[i]=i;
		}
		
		for(int i=0;i<5;i++){
			printf("%d",arry[i]);
			
		}
		puts("\n");
		for(int i=5;i>0;i--){
			printf("%d",arry[i]);
			
		}
	
}
```

### 2. 求最大值

```
#include<stdio.h>
int main(){
	int arry[5]={5,6,41,12,16};
	int max=arry[0];
	
	for(int i=0;i<5;i++){
		if(arry[i]>max){
			max=arry[i];
		}
	}
	printf("%d",max);
	
	
}
```

### 3. 冒泡排序（从小到大）

冒泡排序 = 相邻两个数两两比较，大的往后挪 → 像气泡一样往上浮 → 每轮冒出一个最大数到末尾！

```
#include<stdio.h>
	int main(){
		int arry[5]={5,13,15,10,4};
		int tmp=0;
		int len=sizeof(arry)/sizeof(arry[0]);
		for(int i=0;i<len;i++){//遍历数据
			for(int j=0;j<len-i-1;j++){//交换数据次数
			if(arry[j]>arry[j+1]){
				tmp=arry[j];
				arry[j]=arry[j+1];
				arry[j+1]=tmp;
			}
			}
			
		}
		for(int i=0;i<len;i++){
			printf("%d ",arry[i]);
		}
		
		return 0;
	}
```

### 4.选择排序法

简单选择排序 = 每一轮挑出最大 / 最小值 → 放到正确的位置 → 只交换一次！

```
#include<stdio.h>
int main(){
	int arry[]={4,31,21,15,6,12,15};
	int tmp;
	int len=sizeof(arry)/sizeof(arry[0]);
	int max=arry[0];
	for(int i=0;i<len-1;i++){
		
		for(int j=i+1;j<len;j++){
			if(arry[j]>arry[max]){  
			max=j;
			}	
		}
		tmp=arry[i];
		arry[i]=arry[max];
		arry[max]=tmp;
		
		
	}
		printf("排序后：");
	for(int i=0; i<len; i++){
		printf("%d ", arry[i]);
	}
	return 0;
}	
```

### 5. 斐波那契数列

```
#include<stdio.h>
int main()
{
	int arry[10];
	arry[0]=1;
	arry[1]=1;
	for(int i=2;i<10;i++){
		arry[i]=arry[i-1]+arry[i-2];
		
	}
	
	for(int i=0;i<10;i++){
		
		printf("%d\t",arry[i]);
	}
	
}
```

# 第五章 函数 

![函数](F:\Linux嵌入式开发\C学习\笔记\函数.png)

------

## 一、函数概念

**函数 = 具有独立功能的代码块 → 封装、复用、模块化**

C 程序的入口是 `main()` 函数，所有功能都可以拆成函数。

------

## 二、函数的完整结构

```
返回值类型  函数名( 形式参数列表 )
{
    函数体语句;
    return 返回值;
}
```

### 1. 返回值类型

- 函数执行完要**带回的值的类型**
- `int` `float` `char` `void`（无返回值）
- 无返回值必须写 `void`，不能省略

### 2. 函数名

- 见名知意：`getMax` `add` `sort`
- 命名规则同变量：字母、数字、下划线，不能数字开头

### 3. 形式参数（形参）

- 函数**接收**外部数据用的变量
- 可以 0 个、1 个、多个
- 格式：`类型 变量名, 类型 变量名`

### 4. 函数体

实现功能的代码

### 5. return

- 结束函数
- 带回返回值
- `void` 函数可以没有 `return`，或写 `return;`

------

## 三、函数的分类

1. **库函数**：系统提供（printf、scanf、strlen、malloc 等）
2. **自定义函数**：自己写

------

## 四、函数的 3 个关键步骤

### 1. 函数声明（原型声明）

告诉编译器：这个函数存在，长这样。

```
int add(int a, int b);
```

- 声明可以写多次，定义只能写一次
- 函数写在 main 后面**必须声明**

### 2. 函数定义

真正写函数功能

```
int add(int a, int b)
{
    return a + b;
}
```

### 3. 函数调用

使用函数

```
int res = add(10, 20);
```

------

## 五、形式参数（形参）vs 实际参数（实参）

### 1. 形参

- 定义函数时的变量：`int add(int a, int b)`
- 调用时才分配内存
- 只在函数内部有效

### 2. 实参

- 调用时传的常量、变量、表达式

```
int x = 10, y = 20;
add(x, y);
```

### 3. 参数传递方式：**值传递**

- 把实参的值**拷贝**给形参
- **函数内修改形参，不会影响实参！**
- 单向传递：实参 → 形参

------

## 六、return 语句用法

### 1. 有返回值

```
int add(int a, int b)
{
    return a + b;
}
```

### 2. 无返回值（void）

```
void fun()
{
    printf("hello");
    // 不需要 return
}
```

```
void fun()
{
    if(...) return;  // 直接退出函数
    printf("hello");
}
```

------

## 七、函数调用的 3 种形式

### 1. 普通调用

```
int m = getMax(3, 5);
```

### 2. 嵌套调用

函数里调用另一个函数

```
int fun1() { return 1; }
int fun2() { return fun1() + 2; }
```

### 3. 递归调用

函数自己调用自己

```
int fact(int n)
{
    if(n == 1) return 1;
    return n * fact(n-1);
}
```

**必须有结束条件，否则死循环**

------

## 八、局部变量 vs 全局变量

### 1. 局部变量

- 定义在**函数 / 复合语句**内部
- 作用域：当前 {} 内
- 生命周期：函数调用时创建，结束销毁
- 无默认值（随机值）

### 2. 全局变量

- 定义在**所有函数外部**
- 作用域：整个源文件
- 生命周期：整个程序运行期
- 默认值为 0

示例：

```
int g_x = 100;  // 全局

void fun()
{
    int a = 10; // 局部
}
```

------

## 九、数组作函数参数

### 1. 数组名作为参数 → 传递的是**首地址**

```
void printArr(int arr[], int len)
{
    for(int i=0; i<len; i++)
        printf("%d ", arr[i]);
}
```

调用：

```
int a[5] = {1,2,3,4,5};
printArr(a, 5);
```

特点：

- 函数内修改数组，**实参数组会跟着变**

### 2. 二维数组作参数

```
void fun(int arr[hang][lie], int hang，int lie)
{
}
```

**列数不能省略！**

------

## 十、作业/练习

### 作业

#### 1. 10个数字找到最大以及下标//找最大

```
#include<stdio.h>

void iniArr(int arr[],int len){  //初始化
	printf("请输入10个数字\n");
	for(int i=0;i<len;i++){
		scanf("%d",&arr[i]);
	}
}

void PriArr(int arr[],int len){
	for(int i=0;i<len;i++){
		printf("%d ",arr[i]);
		
	}	
	printf("\n");
}

int findmaxArr(int arr[],int len,int *xiabiao){
	int max=arr[0];
	*xiabiao=0;
	for(int i=1;i<len;i++){
			if(arr[i]>max){

				max=arr[i];
				*xiabiao=i;
			}
		}
			return max;
	

	
}

int main(){
	int arr[10];
    int len=sizeof(arr)/sizeof(arr[0]);
	int index;
	iniArr(arr,len);
	PriArr(arr,len);
	int maxVA=findmaxArr(arr,len,&index);

 printf("最大值：%d，下标：%d\n", maxVA, index);
	

	return 0;
}
```

#### 2. 冒泡排序封装成函数

```

#include<stdio.h>

void PriArr(int arr[],int len){
	for(int i=0;i<len;i++){
		printf("%d ",arr[i]);
	}
	
}

void mpPaixu(int arr[],int len){
	int tmp;
	for(int i=0;i<len;i++){
		for(int j=0;j<len-1-i;j++){
			if(arr[j+1]>arr[j]){
				tmp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=tmp;
			}
		}
	}
	
}


int main(){
	int arr[5]={2,6,45,95,6};
	int len=sizeof(arr)/sizeof(arr[0]);
	mpPaixu(arr,len);
	PriArr(arr,len);
	
	
	return 0;
}
```

#### 3. 简单排序封装

```
#include<stdio.h>

void iniArr(int arr[],int len){  //初始化
	printf("请输入10个数字\n");
	for(int i=0;i<len;i++){
		scanf("%d",&arr[i]);
	}
}

void PriArr(int arr[],int len){
	for(int i=0;i<len;i++){
		printf("%d ",arr[i]);
		
	}	
	printf("\n");
}

void maxArr(int arr[],int len){
	
	int tmp;
	for(int i=0;i<len-1;i++){
		int max=i;
		for(int j=i+1;j<len;j++){
			if(arr[j]>arr[max]){
				max=j;
			}
		}
			tmp=arr[i];
			arr[i]=arr[max];
			arr[max]=tmp;
	}
	
}

int main(){
	int arr[10];
    int len=sizeof(arr)/sizeof(arr[0]);

	iniArr(arr,len);
	PriArr(arr,len);
	maxArr(arr,len);
	PriArr(arr,len);
	
	

	return 0;
}
```

### 练习

#### 1.无参数有参数函数练习

```
#include<stdio.h>

void Phello(){
	printf("======");
	printf("欢迎到家");
}


int add(int a,int b){

	return a+b;
}

int main(){
	Phello();
	int x=1;
	int y=2;
	int ret;
	ret=add(x,y);
	printf("%d",ret);
	
	return 0;
}
```

#### 2.输入两个整数要求输出其最大值，用函数实现（正常比较，三目比较）

```
#include<stdio.h>

int ScWMax(int a,int b){
	if(a>b){
		return a;
	}else{
		return b;
	}
}
int ScWMax2(int a,int b){

	return a>b?a:b;
}


int main(){
	int a;
	int b;
	int res;
	scanf("%d%d",&a,&b);
	res=ScWMax(a,b);
	printf("%d",res);
	
	puts("\n===========");
	scanf("%d%d",&a,&b);
	res=ScWMax2(a,b);
	printf("%d",res);
	return 0;
}
```

#### 3.字符比较大小

```
#include<stdio.h>

char CharMAX(char a,char b){
	if(a>b){
		return a;
	}else{
		return b;
	}
	
}

int main(){
	char a,b;
	char res;
	scanf("%c %c",&a,&b);
	res=CharMAX(a,b);
	printf("%c\n",res);
	
	return 0;
}
```

#### 4.输入四个数，函数方式找最大值

```
#include<stdio.h>
int Maxtwo(int a,int b){
	if(a>b){
		return a;
	}else{
		return b;
	}
}

int Maxfour(int a,int b,int c,int d){
	int max;
	max=Maxtwo(a,b);
	max=Maxtwo(max,c);
	max=Maxtwo(max,d);
	return max;
}

int main(){
	int a,b,c,d;
	int res;
	scanf("%d%d%d%d",&a,&b,&c,&d);
	res=Maxfour(a,b,c,d);
	printf("%d",res);
	
	
	return 0;
}
```

#### 5.递归![image-20260531214519002](C:\Users\12105\AppData\Roaming\Typora\typora-user-images\image-20260531214519002.png)

```
#include<stdio.h>

int hanshu1(int n){
	int res;
	if(n==1){
		res=10;
		return res;
	}else if(n>1){
		res=hanshu1(n-1)+2;
		return res;
	}
}

int  main(){
	int n;
	int res;
	scanf("%d",&n);
	res=hanshu1(n);
	printf("%d",res);
	
	return 0;
}
```

#### 6.递归n的阶乘

```
#include<stdio.h>

int hanshu2(int n){
	int res;
	if(n==1){
		return 1;
	}else if(n>1){
		res=hanshu2(n-1)*n;
		return res;
	}
	
}

int main(){
	
	int n;
	int res;
	scanf("%d",&n);
	res=hanshu2(n);
	printf("%d",res);
	return 0;
}
```

#### 7.有两个班的同学，分别是10个人和5个人，分别求这两个班的平均分

```
#include<stdio.h>

void iniArr(int arr[],int len){
	for(int i=0;i<len;i++){
	scanf("%d",&arr[i]);
	}
}

void PriArr(int arr[],int len){
	for(int i=0;i<len;i++){
	printf("%d ",arr[i]);
	}
	puts("\n");
	
}

float pingJun(int arr[],int len){
	int sum=0;
	float pj;
	for(int i=0;i<len;i++){
	   sum=sum+arr[i];
	}
	pj=(float)sum/len;
	return pj;
}
 
int main(){
	int arr1[10];
	int arr2[5];
	int len1=sizeof(arr1)/sizeof(arr1[0]);
	int len2=sizeof(arr2)/sizeof(arr2[0]);
	
	iniArr(arr1,len1);
	PriArr(arr1,len1);
	int pj;
	pj=pingJun(arr1,len1);
	printf("%d",pj);
	
	iniArr(arr2,len2);
	PriArr(arr2,len2);
	pj=pingJun(arr2,len2);
	printf("%d",pj);
	return 0;
}
```

#### 8.有3x4矩阵，初始化它并输出，然后求最大值并输出

```
#include<stdio.h>

int TwoArr(int hang,int lie,int arr[hang][lie]){
	int max=arr[0][0];
	for(int i=0;i<hang;i++){
		for(int j=0;j<lie;j++){
			if(arr[i][j]>max){
				max=arr[i][j];
			}
		}
	}
	return max;
	
}

int main(){
	int arr[3][4]={{1,2,3,10},{4,5,6,11},{7,8,9,12}};
	int hang;
	int lie;
	hang=sizeof(arr)/sizeof(arr[0]);
	lie=sizeof(arr[0])/sizeof(arr[0][0]);
	int max=TwoArr(hang,lie,arr);
	printf("%d",max);
	
	return 0;
}
```

#### 9.班上10 个学生，封装一个函数，调用该函数后获得班上的平均分，最高分，最低分

```
#include<stdio.h>

void iniArr(int arr[],int len){
	for(int i=0;i<len;i++){
	scanf("%d",&arr[i]);
	}
}

void PriArr(int arr[],int len){
	for(int i=0;i<len;i++){
	printf("%d ",arr[i]);
	}
	puts("\n");
	
}

float pingJun(int arr[],int len,int *max,int *min){
	int sum=0;
	*max=arr[0];
	*min=arr[0];
	float pj;
	
	for(int i=0;i<len;i++){
	  if(arr[i]>*max){
		 *max=arr[i];
	  }
	  if(arr[i]<*min){
		 *min=arr[i];
	  }
	  
	  sum=sum+arr[i];
	}
	pj=(float)sum/len;
	return pj;
}
 
int main(){
	int arr1[10];
	int len1=sizeof(arr1)/sizeof(arr1[0]);
	int max;
	int min;
	iniArr(arr1,len1);
	PriArr(arr1,len1);
	int pj;
	pj=pingJun(arr1,len1,&max,&min);
	printf("平均值:%d 最大值：%d 最小值%d",pj,max,min);
	
}
```

# 第六章 指针 

------

![指针](F:\Linux嵌入式开发\C学习\笔记\指针.jpg)

## 一、指针的基本概念

### 1. 什么是指针

- **指针 = 内存地址**
- 每个变量在内存中都有一个编号，这个编号就是**地址**，也叫**指针**。

### 2. 变量的两种访问方式

1. **直接访问**：用变量名（如 `a`）
2. **间接访问**：用地址 / 指针（如 `&a`、`*p`）

### 3. 两个核心运算符（必背）

- & 取地址符：获取变量的内存地址

  ```
  &a
  ```

   得到 a 的地址

- \* 解引用符：通过地址取出里面的值

  ```
  *p
  ```

   得到 p 指向的变量的值

------

## 二、指针变量

### 1. 什么是指针变量

专门用来**存放地址**的变量，叫指针变量。

### 2. 定义格式

```
类型名 *指针变量名;
```

例：

```
#include <stdio.h>

int main() {
    int a = 10;
    int *p;          // 定义指针变量
    p = &a;          // p 保存 a 的地址

    printf("a = %d\n", a);     // 10
    printf("&a = %p\n", &a);   // 地址（如 0x7ffc...）
    printf("p = %p\n", p);     // 与 &a 相同
    printf("*p = %d\n", *p);   // 解引用，输出 10

    // 核心等价
    // p == &a  成立
    // *p == a  成立
    return 0;
}
```

### 3. 指针为什么要分类型

- 决定指针指向空间的**大小**
- 决定指针 **+1 时偏移多少字节 **
  - `int*` +1 → 偏移 4 字节
  - `char*` +1 → 偏移 1 字节

### 4. 核心等价关系

```
int a = 10;
int *p = &a;
```

- `p  == &a`  地址相等
- `*p == a`   值相等

------

## 三、指针的用途（为什么要用指针）

1. **函数内部可以修改外部变量**（值传递做不到）
2. 高效操作**数组、字符串**
3. 嵌入式、操作系统底层开发必须用
4. 动态内存管理

------

## 四、指针作为函数参数

### 1. 值传递

- 只传值，**不能修改实参**
- 函数内改的是副本

### 2. 地址传递（指针传递）

- 传地址，**可以修改实参**
- 函数内用 `*指针` 操作原变量

### 3. 经典例子：两数交换（正确写法）

```
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}
```

调用：

```
swap(&a, &b);
```

------

## 五、指针与一维数组

### 1. 数组名的本质

**数组名 = 数组首元素地址**

```
int arr[5];
int *p = arr;  // 等价 p = &arr[0]
```

### 2. 数组元素访问（三种写法等价）

```
arr[i]
*(arr + i)
*(p + i)
```

### 3. 指针遍历数组

```
for (int i = 0; i < 5; i++) {
    printf("%d ", *(p + i));
}
```

### 4. 数组名与指针的区别

- 数组名是**常量地址**，不能 `arr++`
- 指针是变量，可以 `p++`

------

## 六、指针与二维数组

### 1. 二维数组本质

**数组的数组（父数组 + 子数组）**

### 2. 地址含义

- `a`       父数组地址
- `a[0]`=第 0 行子数组地址（首元素地址）
- `&a[0][0]` 第 0 行第 0 列元素地址
- `a[i][j]`具体元素值

### 3. 访问元素

```
a[i][j]  ==  *(*(a+i)+j)
```

### 4.指针运算的步长差异

| 表达式     | 类型         | +1 跳过的字节数 | 说明            |
| :--------- | :----------- | :-------------- | :-------------- |
| `a`        | `int (*)[3]` | 12 (3×4)        | 跳一整行        |
| `a + 1`    | `int (*)[3]` | 12              | 指向下一行      |
| `a[0]`     | `int *`      | 4               | 跳一个 int 元素 |
| `*(a + 0)` | `int *`      | 4               | 跳一个 int 元素 |
| `&a[0]`    | `int (*)[3]` | 12              | 跳一整行        |

### 5.等价转换规则

| 原始写法   | 等价写法1     | 等价写法2         | 等价写法3            |
| :--------- | :------------ | :---------------- | :------------------- |
| `a[i]`     | `*(a + i)`    | —                 | —                    |
| `&a[i]`    | `a + i`       | —                 | —                    |
| `a[i][j]`  | `*(a[i] + j)` | `*(*(a + i) + j)` | `(*(a + i))[j]`      |
| `&a[i][j]` | `a[i] + j`    | `*(a + i) + j`    | `&(*(*(a + i) + j))` |

## 七、指针相关常见概念

### 1. 数组指针 

定义：`int (*p)[4];` —— `p` 指向一个包含4个整型元素的一维数组。

- 常用于操作二维数组的某一行。

```
#include <stdio.h>

int main() {
    int arr[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int (*p)[3] = arr;   // p 指向 arr 的第 0 行

    printf("arr[0] 的地址 = %p\n", arr[0]);
    printf("p       指向 = %p\n", p);
    printf("p+1     指向 = %p\n", p + 1);   // 跳过 12 字节

    return 0;
}
```

### 2. 指针数组

**定义**：存放指针的数组，每个元素都是指针。

```
#include <stdio.h>

int main() {
    int a = 10, b = 20, c = 30;
    int *p[3];           // 定义指针数组
    
    p[0] = &a;           // 存放 a 的地址
    p[1] = &b;           // 存放 b 的地址
    p[2] = &c;           // 存放 c 的地址
    
    printf("p[0] = %p, *p[0] = %d\n", p[0], *p[0]);  // a 的地址, 10
    printf("p[1] = %p, *p[1] = %d\n", p[1], *p[1]);  // b 的地址, 20
    printf("p[2] = %p, *p[2] = %d\n", p[2], *p[2]);  // c 的地址, 30
    
    printf("sizeof(p) = %zu\n", sizeof(p));   // 24 (64位系统)
    
    return 0;
}
```

### 3. 函数指针

- **函数名即函数的入口地址**。
- 定义：`返回类型 (*指针变量名)(参数列表);`

```
int add(int a, int b) {
    return a + b;
}

int main() {
    int (*p)(int, int);   // 定义函数指针
    p = add;              // p 指向 add 函数（函数名就是地址）
    
    printf("%d\n", p(3, 5));   // 8，通过指针调用函数
    printf("%d\n", (*p)(3, 5)); // 8，另一种写法
    return 0;
}
```

### 4. 指针函数

定义：`类型 *函数名(参数列表)`返回值是指针的函数

```
#include <stdio.h>

// 指针函数：返回 int* 类型
int *getMax(int *x, int *y) {
    return (*x > *y) ? x : y;   // 返回地址
}

int main() {
    int a = 10, b = 20;
    int *p = getMax(&a, &b);    // 调用指针函数，得到地址
    printf("较大值 = %d\n", *p); // 20
    return 0;
}
```

- 注意：不能返回局部变量的地址（函数结束局部变量释放）。

### 5. 二级指针

指向指针的指针

```
int **p;
```

- 作用：需要在函数内部修改外部指针变量的指向时使用（类似用一级指针修改普通变量）。
- **注意**：二级指针不能直接指向二维数组（类型不匹配）。

## 八、练习/作业

1.初识指针

```
#include<stdio.h>

int main(){
	int a=10;
	int *p=&a;
	printf("%d\n",a);
	printf("%p\n",&a);
	printf("%p\n",p);
	printf("%d\n,",*p);
	
	return 0;
}
```

2.封装一个函数，实现两个数的交换

```
#include<stdio.h>

void swap(int *a,int *b){
	int tmp;
	tmp=*a;
	*a=*b;
	*b=tmp;
	
}

int main(){
	int a=10;
	int b=20;
	swap(&a,&b);
	printf("交换身体a=%d,b=%d",a,b);
	
	return 0;
}
```

3.函数封装数组初始化，遍历

```
#include<stdio.h>
void IniArr(int *p,int len){
	for(int i=0;i<len;i++){
		scanf("%d",(p+i));
	
	}
}
	

void PriArr(int *p,int len){
	for(int i =0;i<len;i++){
		printf("%d ",*(p+i));
		printf("%d ",p[i]);
	}
	
}

int main(){
	int arr[5];
	int len=sizeof(arr)/sizeof(arr[0]);
	IniArr(arr,len);
	PriArr(arr,len);
	return 0;
}
```

4.将数组中的n个元素按逆序存放

```
#include<stdio.h>
void reArr(int *p,int len){
	int tmp;
	int i=0,j=len-1;
	while(i<j){
		for(i=0,j=len-1;i<j;i++,j--){
			tmp=p[i];
			p[i]=p[j];
			p[j]=tmp;
			//tmp=*(p+i);
			//*(p+i)=*(p+j);
			//*(p+j)=tmp;
		}
	}
}

void PriArr(int *p,int len){
	for(int i =0;i<len;i++){
		printf("%d ",*(p+i));
	}
	
}

int main(){
	int arr[]={2,23,4,6,6};
	int len=sizeof(arr)/sizeof(arr[0]);
	
	reArr(arr,len);
	PriArr(arr,len);
	
	
	return 0;
}
```

5.数组指针

```
#include<stdio.h>
void reArr(int *p,int len){
	int tmp;
	int i=0,j=len-1;
	while(i<j){
		for(i=0,j=len-1;i<j;i++,j--){
			tmp=p[i];
			p[i]=p[j];
			p[j]=tmp;
			//tmp=*(p+i);
			//*(p+i)=*(p+j);
			//*(p+j)=tmp;
		}
	}
}

void PriArr(int *p,int len){
	for(int i =0;i<len;i++){
		printf("%d ",*(p+i));
	}
	
}

int main(){
	int arr[]={2,23,4,6,6};
	int len=sizeof(arr)/sizeof(arr[0]);
	
	reArr(arr,len);
	PriArr(arr,len);
	
	
	return 0;
}
```

6。指针数组练习题有两个整数a和b由用户输入1.2.3，如输出/则给出a,b中的大数，输入2给出a,b中的小数，输入3给出a，b的和

```
#include<stdio.h>

int add(int a,int b){
	return a+b;
}
int sub(int a,int b){
	return a-b;
}
int mul(int a,int b){
	return a*b;
}

int main(){
	int a=12;int b=3;
	int num;
	int (*p)(int,int);
	printf("请输入1，2，3中的一种将数字进行+-x的不同运算");
	scanf("%d",&num);
	switch(num){
		case 1:
			p=add;
		break;
		case 2:
			p=sub;
		break;
		case 3:
			p=mul;
		break;
		default:
		printf("输入异常");
		break;
	}
	printf("%d",p(a,b));
	
	
	return 0;
}
```

7.指针数组

```
#include<stdio.h>

int add(int a,int b){
	return a+b;
}
int sub(int a,int b){
	return a-b;
}
int mul(int a,int b){
	return a*b;
}

int main(){
	int a=10;
	int b=20;
	int (*p[3])(int,int)={add,sub,mul};
	for(int i=0;i<3;i++){
		printf("%d ",(*p[i])(a,b));
	}
	
	
	return 0;
}
```

8.指针函数练习1：由a个学生，每个学生由b门课程，输入序号给出这个学生所有的成绩

```
#include<stdio.h>


int *zhanshi(int (*p)[4],int weizhi){
	int *date;
	date=(int *)(p+weizhi);
	return date;
}

int main(){
	int a[][4]={{93,53,63,59},
	{100,90,67,77},
	{66,77,55,22}};
	int *px;
	int weizhi;
	scanf("%d",&weizhi);
	px=zhanshi(a,weizhi);
	for(int i=0;i<4;i++){
		printf("%d ",*(px+i));
	}
	
	return 0;
}
```

9.找出所有学生中成绩不合格的学生以及学生号

```
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
```

10.二级指针用法

```
int value = 100;
int *ptr = &value;    // 一级指针：存储value的地址
int **pptr = &ptr;    // 二级指针：存储ptr的地址

// 关系说明
// pptr → ptr → value
// *pptr = ptr (value的地址)
// **pptr = value (100)
```

11.总结各种指针的定义

```
一个整形数：int a;

一个指向整形数的指针：int *a;

一个指向指针的指针，它指向的指针指向一个整形数：int **a;

一个有10个整形数的数组：int a[10];

一个有10个指针的数组，每个指针指向一个整形数：int *a[10];

一个有10个整形数的数组的指针：int (*a)[10];

一个指向指针的指针，被指向的指针指向一个有10个整形数的数组：int (**a)[10];

一个指向数组的指针，该数组有10个整形数：int (a)[10];

一个指向函数的指针，该函数有一个整形数并返回一个整形数：int (*a)(int);

一个有10个指针的数组，每个指针指向一个函数，该函数有一个整形数并返回一个整形数：int (*a[10])(int);

一个函数的指针，指向的函数的类型是有两个整形数并且返回一个函数指针的函数，返回的函数指针指向一个有整形数且返回整形数的函数：int ((a)(int,int))(int);



```

作业：

 1.输入三个数a,b,c; 要求不管怎么输入，在输出的时候，a,b,c就是由大到小的顺序输出，用函数封装实现

```
#include<stdio.h>

void paixu(int *a,int *b,int *c){
	int tmp;
	if(*a<*b){
		tmp=*b;
		*b=*a;
		*a=tmp;
		
	}
	if(*a<*c){
		tmp=*c;
		*c=*a;
		*a=tmp;
		
	}
	if(*b<*c){
		tmp=*c;
		*c=*b;
		*b=tmp;
	}
}

int main(){
	int a,b,c;
	scanf("%d%d%d",&a,&b,&c);
	paixu(&a,&b,&c);
	printf("a=%d b=%d c=%d\n",a,b,c);
	return 0;
}
```

# 第七章：字符串 

------

![字符串](F:\Linux嵌入式开发\C学习\笔记\字符串.png)

### 一、字符串的本质

**字符串就是字符数组**，以 `'\0'`（空字符）作为结束标志。

```
// 字符数组（字符串）
char str1[] = "hello";
char str2[] = {'h', 'e', 'l', 'l', 'o', '\0'};  // 等价于上面

// 整型数组（对比）
int arr[] = {1, 2, 3, 4, 5};  // 没有结束标志
```

------

### 二、字符串的定义与初始化

#### 2.1 多种定义方式

| 方式                 | 代码                                       | 存储位置 | 是否可修改 |
| :------------------- | :----------------------------------------- | :------- | :--------- |
| 字符数组（变量）     | `char str[] = "hello";`                    | 栈       | ✅ 可修改   |
| 字符数组（指定大小） | `char str[10] = "hello";`                  | 栈       | ✅ 可修改   |
| 字符数组（逐个赋值） | `char str[] = {'h','e','l','l','o','\0'};` | 栈       | ✅ 可修改   |
| 字符指针（常量）     | `char *p = "hello";`                       | 常量区   | ❌ 不可修改 |
| 动态分配             | `char *p = (char*)malloc(10);`             | 堆       | ✅ 可修改   |

```
#include <stdio.h>

int main() {
    // 1. 字符串变量（可修改）
    char str1[] = "hello";
    str1[0] = 'H';
    printf("%s\n", str1);   // "Hello"
    
    // 2. 字符串常量（不可修改，危险！）
    char *str2 = "world";
    // str2[0] = 'W';   // ❌ 严重错误！段错误
    
    // 3. 指定大小初始化
    char str3[10] = "hello";
    printf("%s\n", str3);   // "hello"
    
    return 0;
}
```

#### 2.2 字符数组 vs 字符指针

| 特性       | `char str[] = "hello"` | `char *p = "hello"` |
| :--------- | :--------------------- | :------------------ |
| 存储位置   | 栈（可读写）           | 常量区（只读）      |
| 是否可修改 | ✅ 可以                 | ❌ 不可以            |
| `sizeof`   | 整个数组大小（6）      | 指针大小（8）       |
| 能否自增   | `str++` ❌              | `p++` ✅             |

------

### 三、字符串的存储与结束标志

#### 3.1 `'\0'` 结束标志

```
char str[] = "hello";
// 实际存储：'h' 'e' 'l' 'l' 'o' '\0'
// 内存大小：6字节（5个字符 + 1个'\0'）
```

#### 3.2 `sizeof` vs `strlen`

| 函数     | 作用           | 是否包含 `'\0'` | 示例                  |
| :------- | :------------- | :-------------- | :-------------------- |
| `sizeof` | 计算内存字节数 | ✅ 包含          | `sizeof("hello")` = 6 |
| `strlen` | 计算字符串长度 | ❌ 不包含        | `strlen("hello")` = 5 |

```
#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "hello";
    
    printf("sizeof(str) = %zu\n", sizeof(str));   // 6（包含'\0'）
    printf("strlen(str) = %zu\n", strlen(str));   // 5（不包含'\0'）
    
    char str2[10] = "hello";
    printf("sizeof(str2) = %zu\n", sizeof(str2)); // 10（整个数组大小）
    printf("strlen(str2) = %zu\n", strlen(str2)); // 5（字符串长度）
    
   return 0;
}
```

------

### 四、动态开辟字符串

#### 4.1 常用内存函数

| 函数      | 作用         | 原型                                      |
| :-------- | :----------- | :---------------------------------------- |
| `malloc`  | 分配内存     | `void *malloc(size_t size)`               |
| `calloc`  | 分配并清零   | `void *calloc(size_t nmemb, size_t size)` |
| `realloc` | 重新分配内存 | `void *realloc(void *ptr, size_t size)`   |
| `free`    | 释放内存     | `void free(void *ptr)`                    |
| `memset`  | 设置内存值   | `void *memset(void *s, int c, size_t n)`  |

#### 4.2 动态字符串示例

```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // 1. 动态分配字符串
    char *str = (char*)malloc(20 * sizeof(char));
    if (str == NULL) {
        printf("分配失败\n");
        return 1;
    }
    
    // 2. 复制字符串
    strcpy(str, "hello");
    printf("%s\n", str);   // "hello"
    
    // 3. 重新分配更大空间
    str = (char*)realloc(str, 50 * sizeof(char));
    strcat(str, " world");
    printf("%s\n", str);   // "hello world"
    
    // 4. 释放内存
    free(str);
    str = NULL;   // 防止悬指针
    
    return 0;
}
```

#### 4.3 常见错误：悬挂指针

```
int *p = (int*)malloc(sizeof(int));
free(p);
// p 变成悬挂指针（野指针）
// *p = 10;   // ❌ 错误！内存已释放

// 正确做法：释放后置为 NULL
free(p);
p = NULL;
```

------

### 五、字符串常用 API

#### 5.1 输入输出函数

| 函数                      | 作用                     | 安全性     |
| :------------------------ | :----------------------- | :--------- |
| `printf("%s", str)`       | 输出字符串               | ✅ 安全     |
| `puts(str)`               | 输出字符串并换行         | ✅ 安全     |
| `scanf("%s", str)`        | 读取字符串（遇空格停止） | ⚠️ 可能溢出 |
| `gets(str)`               | 读取一行（已废弃）       | ❌ 不安全   |
| `fgets(str, size, stdin)` | 安全读取一行             | ✅ 安全     |

```
#include <stdio.h>

int main() {
    char str[100];
    
    // 不安全（已废弃）
    // gets(str);
    
    // 安全方式
    printf("请输入字符串: ");
    fgets(str, sizeof(str), stdin);
    
    // 去掉末尾的换行符
    str[strcspn(str, "\n")] = '\0';
    
    printf("你输入了: %s\n", str);
    
    return 0;
}
```

#### 5.2 字符串操作函数

| 函数                               | 作用          | 示例                              |
| :--------------------------------- | :------------ | :-------------------------------- |
| `strlen(str)`                      | 获取长度      | `int len = strlen("hello");` // 5 |
| `strcpy(dest, src)`不自动添加 `\0` | 复制字符串    | `strcpy(dest, "hello");`          |
| `strncpy(dest, src, n)`            | 复制前n个字符 | `strncpy(dest, src, 5);`          |
| `strcat(dest, src)`                | 拼接字符串    | `strcat(dest, " world");`         |
| `strcmp(str1, str2)`               | 比较字符串    | `if (strcmp(s1, s2) == 0)`        |
| `strncmp(s1, s2, n)`               | 比较前n个字符 | `strncmp(s1, s2, 3)`              |
| `strchr(str, ch)`                  | 查找字符      | `char *p = strchr(str, 'a');`     |
| `strstr(str, substr)`              | 查找子串      | `char *p = strstr(str, "abc");`   |
| `strtok(str, delim)`               | 分割字符串    | `char *p = strtok(str, ",");`     |

#### 5.3 完整示例

```
#include <stdio.h>
#include <string.h>

int main() {
    char str1[50] = "hello";
    char str2[50] = "world";
    char str3[50];
    
    // 1. 获取长度
    printf("str1长度: %zu\n", strlen(str1));   // 5
    
    // 2. 复制字符串
    strcpy(str3, str1);
    printf("str3: %s\n", str3);   // "hello"
    
    // 3. 拼接字符串
    strcat(str1, " ");
    strcat(str1, str2);
    printf("拼接后: %s\n", str1);  // "hello world"
    
    // 4. 比较字符串
    if (strcmp(str1, "hello world") == 0) {
        printf("字符串相等\n");
    }
    
    // 5. 查找字符
    char *p = strchr(str1, 'w');
    if (p != NULL) {
        printf("找到 'w'，位置: %ld\n", p - str1);  // 6
    }
    
    // 6. 查找子串
    char *sub = strstr(str1, "world");
    if (sub != NULL) {
        printf("找到子串: %s\n", sub);  // "world"
    }
    
    // 7. 字符串分割
    char data[] = "apple,banana,orange";
    char *token = strtok(data, ",");
    while (token != NULL) {
        printf("分割: %s\n", token);
        token = strtok(NULL, ",");
    }
    
    return 0;
}
```

**输出**：

```
str1长度: 5
str3: hello
拼接后: hello world
字符串相等
找到 'w'，位置: 6
找到子串: world
分割: apple
分割: banana
分割: orange
```

------

### 六、字符串常见操作实现

#### 6.1 自己实现 `strlen`

```
int myStrlen(char *a){
	int len=0;
	while(*(a+len)!='\0'){
		len++;
	}
	return len;
}


    // 或
    // const char *p = str;
    // while (*p++) len++;
    // return len;

```

#### 6.2 自己实现 `strcpy`

```
char *Mycopy(char *a,char *b){
		char *poi=a;
		while((*a=*b)!='\0'){
			a++;
			b++;
		}
		return poi;
}
```

#### 6.3 自己实现 `strcmp`

```
int Mycmp(char *a,char *b){
		while((*a==*b)&&*a&&*b){
			a++;
			b++;
		}
		return *a-*b;
}
```

#### 6.4 自己实现 `strcat`

```
char *my_strcat(char *dest, const char *src) {
    char *p = dest;
    
    // 找到 dest 的末尾
    while (*dest != '\0') {
        dest++;
    }
    
    // 复制 src
    while ((*dest++ = *src++) != '\0');
    
    return p;
}
```

------

### 七、常见错误与注意事项

#### 7.1 错误清单

| 错误             | 说明                             | 正确做法                           |
| :--------------- | :------------------------------- | :--------------------------------- |
| 忘记 `'\0'`      | 字符数组没有结束标志             | 字符串必须留一个位置给 `'\0'`      |
| 修改字符串常量   | `char *p = "hello"; p[0]='H';`   | 用字符数组 `char str[] = "hello";` |
| 缓冲区溢出       | `strcpy(dest, src)` 时 dest 太小 | 用 `strncpy` 或确保空间足够        |
| 返回局部数组地址 | `return arr;`（arr是局部数组）   | 用 `static` 或动态分配             |
| 忘记 `free`      | 动态分配的内存没释放             | 配对使用 `malloc/free`             |
| 悬挂指针         | free 后继续使用                  | free 后置为 `NULL`                 |

#### 7.2 安全函数建议

```
// 不安全
char str[5];
strcpy(str, "hello");   // 溢出！

// 安全
char str[10];
strncpy(str, "hello", sizeof(str) - 1);
str[sizeof(str) - 1] = '\0';

// 或使用 fgets 代替 gets
fgets(str, sizeof(str), stdin);
```

------

### 八、字符串与指针总结表

| 知识点     | 核心内容                                         |
| :--------- | :----------------------------------------------- |
| 本质       | 以 `'\0'` 结尾的字符数组                         |
| 字符串变量 | `char str[] = "hello"`（可修改）                 |
| 字符串常量 | `char *p = "hello"`（只读，不可修改）            |
| 长度计算   | `strlen`（不含`'\0'`）vs `sizeof`（含`'\0'`）    |
| 动态分配   | `malloc` + `free`，防内存泄漏                    |
| 常用函数   | `strcpy`、`strcat`、`strcmp`、`strstr`、`strtok` |
| 安全输入   | 用 `fgets` 替代 `gets`                           |
| 输出       | `printf("%s")` 或 `puts`                         |

## 九、练习/作业

MYAPI

```
#include<stdio.h>


int myStrlen(char *a){
	int len=0;
	while(*(a+len)!='\0'){
		len++;
	}
	return len;
}

char *Mycopy(char *a,char *b){
		char *poi=a;
		while((*a=*b)!='\0'){
			a++;
			b++;
		}
		return poi;
}

int Mycmp(char *a,char *b){
		while((*a==*b)&&*a&&*b){
			a++;
			b++;
		}
		return *a-*b;
}

char *Mycat(char *a,char *b){
		char *poi=a;
		while((*a++)!='\0'){} // 找到末尾
		a--; // 回退到 '\0' 位置 ← 加上这一行
		
		while((*a++=*b++)!='\0'){}
		
		return poi;
}


int main(){
	char a[10]="hello";
	char b[]="hi";
	printf("%d\n",myStrlen(b));
	// Mycopy(a,b);
	// puts(a);
	printf("%d\n",Mycmp(a,b));
	Mycat(a,b);
	puts(a);
	return 0;
}
```

字符串基础用法

```
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
	

int main(){
	char str1[]="hello";
	char str2[10]="hello";
	char str3[]={'h','e','l','l','o','\0'};
	char *p1="hello";
	char *p2=(char *)malloc(5);//分配完后要初始化
	strcpy(p2,"hello");
	
	printf("size=%d\n",sizeof(str1));//6
	printf("size=%d\n",strlen(str1));//5
	printf("size2=%d\n",sizeof(str2));//10
	printf("size2=%d\n",strlen(str2));//5	
	printf("size3=%d\n",sizeof(str3));//6
	printf("size3=%d\n",strlen(str3));//5
	printf("sizep1=%d\n",sizeof(p1));//8
	printf("sizep1=%d\n",strlen(p1));//5
	printf("sizep2=%d\n",sizeof(p2));//8
	printf("sizep2=%d\n",strlen(p2));//5
	
	
	free(p2);
	p2=NULL;
	return 0;
}
```

常见api使用

```
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
```

# 第八章 结构体、共用体、枚举、typedef 

------

![结构体](F:\Linux嵌入式开发\C学习\笔记\结构体.png)

### 一、为什么需要结构体

**问题**：数组只能存储相同类型的数据，无法表示一个学生的完整信息（姓名、学号、成绩等不同类型的数据）。

**解决方案**：结构体可以将不同类型的变量组合成一个整体。

| 数据类型 | 特点     | 示例                                                      |
| :------- | :------- | :-------------------------------------------------------- |
| 数组     | 相同类型 | `int scores[5]`                                           |
| 结构体   | 不同类型 | `struct Student { char name[20]; int id; float score; };` |

------

### 二、结构体（struct）

#### 2.1 定义结构体模板

```
// 方式1：标准定义
struct Student {
    int id;
    char name[50];
    float score;
};

// 方式2：定义模板的同时定义变量
struct Student {
    int id;
    char name[50];
    float score;
} stu1, stu2;

// 方式3：匿名结构体（不推荐，只能用一次）
struct {
    int id;
    char name[50];
} stu1;
```

#### 2.2 定义结构体变量

```
struct Student stu1;                        // 普通变量
struct Student stu2 = {1001, "张三", 85.5}; // 初始化
struct Student *p = &stu1;                  // 结构体指针
struct Student arr[30];                     // 结构体数组
```

#### 2.3 结构体初始化的多种方式

```
// 方式1：按顺序初始化
struct Student s1 = {1001, "张三", 85};

// 方式2：指定成员初始化（C99，更安全）
struct Student s2 = {.id = 1002, .name = "李四", .score = 92};

// 方式3：部分初始化（未初始化的成员为0）
struct Student s3 = {1003};  // id=1003, name="", score=0

// 方式4：先定义后逐个赋值
struct Student s4;
s4.id = 1004;
strcpy(s4.name, "王五");  // ⚠️ 不能直接 s4.name = "王五"
s4.score = 78;
```

**易错点**：字符串成员不能直接赋值，要用 `strcpy`。

#### 2.4 访问结构体成员

| 方式     | 运算符 | 示例                                     |
| :------- | :----- | :--------------------------------------- |
| 普通变量 | `.`    | `stu1.id = 1001;`                        |
| 指针变量 | `->`   | `p->id = 1001;` 等价于 `(*p).id = 1001;` |

```
struct Student stu;
struct Student *p = &stu;

stu.id = 1001;      // 用 .
p->id = 1001;       // 用 ->
(*p).id = 1001;     // 等价于上面
```

#### 2.5 结构体数组

```
// 批量初始化
struct Student class[] = {
    {1001, "张三", 85},
    {1002, "李四", 92},
    {1003, "王五", 78}
};

// 计算元素个数（常用技巧）
int n = sizeof(class) / sizeof(class[0]);

// 遍历
for (int i = 0; i < n; i++) {
    printf("%d %s %.2f\n", class[i].id, class[i].name, class[i].score);
}
```

------

### 三、结构体指针

#### 3.1 基本用法

```
struct Student stu = {1001, "张三", 85};
struct Student *p = &stu;

printf("%d\n", p->id);      // 1001
printf("%s\n", p->name);    // 张三
printf("%.2f\n", p->score); // 85
```

#### 3.2 结构体指针作为函数参数

```
// 方式1：传值（拷贝整个结构体，效率低）
void printStudent(struct Student s) {
    printf("%d %s %.2f\n", s.id, s.name, s.score);
}

// 方式2：传指针（推荐，效率高，可修改原数据）
void updateScore(struct Student *p, float newScore) {
    p->score = newScore;
}

int main() {
    struct Student stu = {1001, "张三", 85};
    updateScore(&stu, 95);
    printStudent(stu);
    return 0;
}
```

| 传参方式 | 效率                 | 能否修改原数据 |
| :------- | :------------------- | :------------- |
| 传值     | 低（拷贝整个结构体） | ❌              |
| 传指针   | 高（只传4/8字节）    | ✅              |

#### 3.3 结构体指针数组

```
struct Student *pArr[3];
pArr[0] = &stu1;
pArr[1] = &stu2;
pArr[2] = &stu3;

for (int i = 0; i < 3; i++) {
    printf("%s\n", pArr[i]->name);
}
```

#### 3.4 结构体与函数：返回结构体的正确方式

```
// ❌ 错误：返回局部变量的地址
struct Student* getStudent() {
    struct Student s = {1001, "张三", 85};
    return &s;  // 危险！函数结束s被销毁
}

// ✅ 正确方式1：返回结构体本身（拷贝）
struct Student getStudent() {
    struct Student s = {1001, "张三", 85};
    return s;  // 拷贝一份返回
}

// ✅ 正确方式2：使用静态局部变量
struct Student* getStudent() {
    static struct Student s = {1001, "张三", 85};
    return &s;  // 静态变量生命周期是整个程序
}

// ✅ 正确方式3：动态分配
struct Student* getStudent() {
    struct Student *s = (struct Student*)malloc(sizeof(struct Student));
    s->id = 1001;
    strcpy(s->name, "张三");
    s->score = 85;
    return s;  // 调用者负责 free
}
```

------

### 四、共用体/联合体（union）

#### 4.1 定义与特点

```
union Data {
    int i;
    float f;
    char str[20];
};
```

**特点**：

- 所有成员**共享同一块内存空间**
- 大小由**最大的成员**决定
- **同一时间只能使用一个成员**，赋值会覆盖其他成员

| 对比 | 结构体 struct              | 共用体 union           |
| :--- | :------------------------- | :--------------------- |
| 内存 | 各成员独立分配             | 所有成员共享一块内存   |
| 大小 | 各成员大小之和（考虑对齐） | 最大成员的大小         |
| 赋值 | 互不影响                   | 会互相覆盖             |
| 用途 | 同时存储多个不同类型数据   | 同一时间只使用一种类型 |

#### 4.2 示例

```
union Data data;
data.i = 10;
printf("%d\n", data.i);   // 10

data.f = 3.14;
printf("%f\n", data.f);   // 3.14
printf("%d\n", data.i);   // 垃圾值（被覆盖了）
```

#### 4.3 共用体的实际应用场景

```
// 场景1：数据解析（网络协议、嵌入式）
union IPAddress {
    unsigned int addr;      // 4字节整数
    unsigned char bytes[4]; // 4个字节
};

union IPAddress ip;
ip.addr = 0xC0A80101;  // 192.168.1.1
printf("%d.%d.%d.%d\n", ip.bytes[0], ip.bytes[1], ip.bytes[2], ip.bytes[3]);

// 场景2：节省内存（同一时间只用一种类型）
typedef union {
    int i;
    float f;
    char str[20];
} Data;

Data d;
d.i = 10;      // 此时用 int
// d.f = 3.14;  // 此时用 float，会覆盖 int
```

------

### 五、枚举类型（enum）

#### 5.1 定义与使用

```
enum Weekday {
    MON, TUE, WED, THU, FRI, SAT, SUN
};

enum Weekday today = MON;
```

**特点**：

- 枚举常量默认从 **0** 开始递增
- 可手动指定值

```
enum Color {
    RED = 1,
    GREEN = 3,
    BLUE = 5
};
// RED=1, GREEN=3, BLUE=5
```

#### 5.2 枚举的高级用法

```
// 1. 手动指定值（常用于状态码）
enum Status {
    SUCCESS = 0,
    ERROR_FILE = -1,
    ERROR_MEMORY = -2,
    ERROR_NETWORK = -3
};

// 2. 枚举作为函数返回值
enum Status readFile() {
    // ... 处理逻辑
    return SUCCESS;
}

// 3. 枚举作为数组索引
enum Month { JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };
int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
printf("1月有%d天\n", days[JAN]);  // 31
```

#### 5.3 枚举与宏定义的对比

| 特性         | 枚举 enum    | 宏 #define   |
| :----------- | :----------- | :----------- |
| 作用域       | 遵循块作用域 | 全局替换     |
| 调试         | 可见符号名   | 预处理后消失 |
| 类型安全     | 有类型检查   | 无类型检查   |
| 自动递增     | ✅ 支持       | ❌ 不支持     |
| 相关常量分组 | ✅ 好         | ⚠️ 需手动     |

------

### 六、typedef 关键字

#### 6.1 为类型起别名

```
// 基本类型
typedef int Integer;
Integer a = 10;  // 等价于 int a = 10;

// 结构体（最常用）
typedef struct Student {
    int id;
    char name[50];
} Stu;  // Stu 是 struct Student 的别名

Stu s1;  // 等价于 struct Student s1;

// 匿名结构体 + typedef
typedef struct {
    int x;
    int y;
} Point;

Point p1 = {10, 20};
```

#### 6.2 简化指针类型

```
typedef int *IntPtr;
IntPtr p1, p2;  // 等价于 int *p1, *p2;

// 结构体指针
typedef struct Student *StuPtr;
StuPtr p = &stu;
```

#### 6.3 简化函数指针

```
// 定义函数指针类型
typedef int (*FuncPtr)(int, int);

// 使用
FuncPtr p = add;  // 等价于 int (*p)(int,int) = add;
```

#### 6.4 typedef 的常见陷阱

```
// 陷阱1：与指针结合
typedef int *Ptr;
Ptr a, b;   // a和b都是 int*

#define Ptr2 int *
Ptr2 c, d;  // 相当于 int *c, d;  d是int，不是指针！

// 陷阱2：与 const 结合
typedef int *Ptr;
const Ptr p;  // p是常量指针（指向int的常量指针），不是指向const int
```

#### 6.5 typedef vs #define

| 特性         | typedef      | #define    |
| :----------- | :----------- | :--------- |
| 处理阶段     | 编译期       | 预处理期   |
| 作用域       | 遵循块作用域 | 全局替换   |
| 复杂类型     | ✅ 适合       | ⚠️ 容易出错 |
| 类型安全检查 | ✅ 有         | ❌ 无       |

------

### 七、结构体嵌套

#### 7.1 结构体包含结构体

```
struct Date {
    int year;
    int month;
    int day;
};

struct Student {
    int id;
    char name[50];
    struct Date birthday;  // 嵌套结构体
};

// 访问
struct Student stu;
stu.birthday.year = 2000;
stu.birthday.month = 1;
stu.birthday.day = 1;
```

#### 7.2 结构体自引用（链表节点）

```
struct Node {
    int data;
    struct Node *next;  // 指向自身类型的指针
};

struct Node *head = NULL;
```

------

### 八、内存对齐（了解）

```
struct A {
    char c;   // 1字节
    int i;    // 4字节
};
// sizeof(struct A) = 8（不是5）
// 原因：内存对齐，char后面有3个填充字节
```

| 规则                             | 说明              |
| :------------------------------- | :---------------- |
| 成员按最大类型对齐               | 节省 CPU 访问时间 |
| 结构体大小是最大成员大小的整数倍 | 方便数组访问      |

### 九、经典例题

#### 例题1：学生成绩管理系统（基础）

**题目**：

```
#include<stdio.h>
#include<string.h>
//例题1：学生成绩管理系统
//定义学生结构体（学号、姓名、3门课成绩），输入3个学生信息，计算每个学生的平均分并输出。

struct Student{
	int id;
	float scores[3];
	char name[40];
	float avg;
};

void intStruct(struct Student *s){
	printf("请输入名字\n");
	char name[40];
	scanf("%s",name);
	strcpy(s->name,name);
	
	printf("请输入学号\n");
	scanf("%d",&s->id);
	
	printf("请输入成绩\n");
	for(int i=0;i<3;i++){
		scanf("%f",&s->scores[i]);
	}
	float sum=0;
	for(int i=0;i<3;i++){
		sum=(sum+s->scores[i]);
	}
	s->avg=sum/3;
}
void avgARR(struct Student *s,int len){
	
	for(int j=0;j<len;j++){
	float sum=0;
	for(int i=0;i<3;i++){
		sum=(sum+s[j].scores[i]);
	}
	s[j].avg=sum/3;
	}
}


void PrinStruct(struct Student s){
	printf("id:%d 姓名:%s  ",s.id,s.name);

	for(int i=0;i<3;i++){
		
		printf("第%d门课程的成绩为%.2f  ",i+1,s.scores[i]);
	}
	printf("平局分为:%.1f\n",s.avg);
	
}

void avgSort(struct Student *Arr,int len){
	struct Student tmp;
	
	for(int i=0;i<len-1;i++){
		for(int j=0;j<len-i-1;j++){
			if((Arr[j].avg)<(Arr[j+1].avg)){
				tmp=Arr[j+1];
				Arr[j+1]=Arr[j];
				Arr[j]=tmp;
			}
		}
	}
	
}

struct Student* FindavgMax(struct Student *s,int len){
	struct Student *max=s;
	for(int i=1;i<len;i++){
			if((s+i)->avg>max->avg){
				max=s+i;
			}
	}
	return max;
}



int main(){
    struct Student students[3] = {
        {1001, {85, 90, 88}, "张三", 0},
        {1002, {99, 92, 86}, "李四", 0},
        {1003, {80, 75, 79}, "王五", 0}
    };
    int len=sizeof(students)/sizeof(students[0]);
	avgSort(students,len);
	
    avgARR(students,len);
	struct Student *max=FindavgMax(students,len);
	PrinStruct(*max);
 
   // 循环输入
    // for (int i = 0; i < 3; i++) {
        // printf("\n====== 第 %d 个学生 ======\n", i + 1);
        // intStruct(&students[i]);  // 传入每个学生的地址
    // }
    
    // 循环输出
    // printf("\n========== 所有学生信息 ==========\n");
    // for (int i = 0; i < 3; i++) {
        // PrinStruct(students[i]);   // 传入每个学生
    // }
	
	
	return 0;
}
```



------

#### 例题2：按成绩排序

**题目**：在上题基础上，按平均分从高到低排序输出。

c

```
void avgSort(struct Student *Arr,int len){
	struct Student tmp;
	
	for(int i=0;i<len-1;i++){
		for(int j=0;j<len-i-1;j++){
			if((Arr[j].avg)<(Arr[j+1].avg)){
				tmp=Arr[j+1];
				Arr[j+1]=Arr[j];
				Arr[j]=tmp;
			}
		}
	}
	
}
```



------

#### 例题3：最高分学生（结构体指针作参数）

**题目**：写一个函数，找出平均分最高的学生，返回其指针。

```
struct Student* FindavgMax(struct Student *s,int len){
	struct Student *max=s;
	for(int i=1;i<len;i++){
			if((s+i)->avg>max->avg){
				max=s+i;
			}
	}
	return max;
}
```



------

#### 例题4：选票系统（结构体数组 + 指针）

**题目**：有3个候选人，5个人投票，统计每人得票数。



```
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
```



------

#### 例题5：链表入门（结构体自引用）补充

**题目**：创建一个简单的链表，包含3个节点，并遍历输出。

```
#include<stdio.h>
#include<stdlib.h>

struct Linklist{
	int data;
	struct Linklist *next;
};

void Prilinklist(struct Linklist *p){
	while(p!=NULL){
		printf("%d ",p->data);
		p=p->next;
	}
	
}

int main(){
	struct Linklist s1;
	struct Linklist s2;
	struct Linklist s3;
	s1.data=10;
	s1.next=&s2;
	s2.data=20;
	s2.next=&s3;
	s3.data=30;
	s3.next=NULL;
	
	struct Linklist *head=&s1;
	Prilinklist(head);
	
	return 0;
}
```



------

#### 例题6：共用体判断大小端补充

**题目**：用共用体判断当前系统是大端还是小端模式。

```
#include <stdio.h>

typedef union {
    int i;
    char c;
} EndianTest;

int main() {
    EndianTest e;
    e.i = 1;  // 小端：低地址存0x01；大端：低地址存0x00
    
    if (e.c == 1) {
        printf("小端模式\n");
    } else {
        printf("大端模式\n");
    }
    
    return 0;
}
```



------

#### 例题7：结构体嵌套（日期 + 学生）补充

**题目**：定义出生日期结构体，嵌套到学生结构体中，输入输出学生信息。

```
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
```



------

#### 例题8：枚举 + 结构体（学生状态）补充

**题目**：用枚举表示学生状态（正常、休学、毕业），并输出。

c

```
#include<stdio.h>
//定义出生日期结构体，嵌套到学生结构体中，输入输出学生信息。用枚举表示学生状态（正常、休学、毕业），并输出。
enum status{
	Normal,
	Graduate,
	leaveSchool
};

struct Data{
	int year;
	int mon;
	int day;
};

struct Student{
	int age;
	char name[40];
	struct Data bir;
	enum status sta;
};

char* getStatus(enum status stu){
	switch(stu){
		case Normal:return "正常";
		
		case Graduate:return "毕业";
		
		case leaveSchool:return "离校";
		default:return "未知";
		
	}
	
}

int main(){
	struct Student stu[3]={
		{22,"黄",{2021,1,3},Normal},
		{21,"xx",{2022,2,2},leaveSchool},
		{23,"cc",{2023,3,1},Graduate}};
	for(int i=0;i<3;i++){
		printf("年龄:%d\n名字：%s\n生日:%d年%d月%d日 学生状态：%s\n",
		stu[i].age,stu[i].name,
		stu[i].bir.year,stu[i].bir.mon,stu[i].bir.day,
		getStatus(stu[i].sta));
		printf("\n");
	}

	
	return 0;
}
```

# 链表

链表是一种重要的动态数据结构，由一系列节点组成，每个节点包含数据和指向下一个节点的指针。

### 1. 链表的基本概念

**优点：**

- 动态内存分配，不需要预知最大长度
- 插入删除操作高效（只需修改指针）
- 内存利用率高

**缺点：**

- 不支持随机访问
- 需要额外存储指针，内存开销大
- 实现比数组复杂

### 2. 单向链表的基本实现

#### 2.1 节点结构定义

```
// 节点结构定义
typedef struct Node {
    int data;
    struct Node *next;  // 修正：指向自身类型
} Node;
```

#### 2.2 创建节点

```
//创建单个节点
Node *Crealinklist(int data){
	Node *newnode=(Node*)malloc(sizeof(Node));
	if(newnode==NULL)return NULL;
	newnode->data=data;
	newnode->next=NULL;
	return newnode;
}
```

### 3. 链表基本操作

#### 3.1 不带头节点的尾插法建立链表

```
//带头节点的尾插法
Node *htailInsert(int n){
	Node* head=(Node*)malloc(sizeof(Node));
	head->next=NULL;
	Node* tail=NULL;
	int data;
	
	printf("请输入%d个数据",n);
	for(int i=0;i<n;i++){
		printf("请输入第%d个数据的值：",i+1);
		scanf("%d",&data);
		Node* newnode=(Node*)malloc(sizeof(Node));
		if(newnode==NULL)continue;
		newnode->data=data;
		newnode->next=NULL;
		if(head->next==NULL){
			head->next=newnode;
			tail=newnode;
		}else{
			tail->next=newnode;
			tail=newnode;
		}
	}
	return head;
}
```

#### 3.2 带头节点的尾插法

```
Node *htailInsert(int n){
	Node* head=(Node*)malloc(sizeof(Node));
	head->next=NULL;
	Node* tail=NULL;
	int data;
	
	printf("请输入%d个数据",n);
	for(int i=0;i<n;i++){
		printf("请输入第%d个数据的值：",i+1);
		scanf("%d",&data);
		Node* newnode=(Node*)malloc(sizeof(Node));
		if(newnode==NULL)continue;
		newnode->data=data;
		if(head->next==NULL){
			head->next=newnode;
			tail=newnode;
		}else{
			tail->next=newnode;
			tail=newnode;
		}
	}
	return head;
}
```

#### 3.3带头节点头插法

```
//带头节点头插法
Node *hheadInsert(int n){
	
	Node *head = (Node*)malloc(sizeof(Node));
	head->next=NULL;
	int data;
	printf("请输入%d个数据",n);
	for(int i=0;i<n;i++){
		printf("请输入第%d个数据的值：",i+1);
		scanf("%d",&data);
		Node* newnode=(Node*)malloc(sizeof(Node));
		if(newnode==NULL)continue;
		
		newnode->data=data;
		newnode->next=head->next;
		head->next=newnode;	
}
return head;
}
```

#### 3.4不带头节点的头插法

```
//不带头节点的头插法
Node *headInsert(int n){
	Node *head=NULL;
	int data;
	printf("请输入%d个数据",n);
	for(int i=0;i<n;i++){
		printf("请输入第%d个数据的值：",i+1);
		scanf("%d",&data);
		Node* newnode=(Node*)malloc(sizeof(Node));
		if(newnode==NULL)continue;
		newnode->data=data;
		newnode->next=head;
		head=newnode;
		
	}
	return head;
}
```

#### 3.5打印链表/搜索链表

```
//不带头节点打印
void PrihList(Node* head){
	Node* p=head;
	while(p!=NULL){
		printf("%d ",p->data);
		p=p->next;
	}
}
//带头节点寻找
void searchList(Node* head,int data){
	Node* p=head;
	int i=1;
	while(p!=NULL){
		if(p->data==data){
			printf("第%d次寻找 找到：%d",i,p->data);
		}
		p=p->next;
		i++;
	}
}

//带头节点寻找
void searchList(Node* head,int data){
	Node* p=head->next;
	int i=1;
	while(p!=NULL){
		if(p->data==data){
			printf("第%d次寻找 找到：%d",i,p->data);
		}
		p=p->next;
		i++;
	}
}

//带头节点打印
void PrihList(Node* head){
	Node* p=head->next;
	while(p!=NULL){
		printf("%d ",p->data);
		p=p->next;
	}
}
```

#### 3.6 删除操作

```
//删除节点操作
Node* DeleteList(Node* head,int target){
	 // ========== 情况1：空链表 ==========
	 if(head==NULL){
		printf("链表为空\n");
		return NULL;
	 }
	 //========== 情况2：删除的为头节点 ==========
	 if(head->data==target){
		Node* tmp=head;
		head=head->next;
		free(tmp);
        printf("删除头节点成功\n");
        return head;  // 返回新头指针
	 }
	 //========== 情况3：删除的非头节点 ==========
	 Node* prev=head;
	 while(prev->next!=NULL&&prev->next->data!=target){
		 prev=prev->next;
	 }
	 if(prev->next==NULL){
		printf("未找到%d的节点\n",target);
	 }
	 //删除操作
	 Node* temp=prev->next; //将要删除的节点保存
	 prev->next=temp->next;//将前前驱节点指向当前节点的指针转移为当前指针指向后一项的指针
	free(temp);
	return head;
}

//带头节点的删除
Node* DeleteHeList(Node* head,int target){
	//情况1空指针
	if(head==NULL||head->next==NULL){
		printf("空指针\n");
		return NULL;
	}
	//情况2删除
	Node *prev=head;
	while(prev->next!=NULL&&prev->next->data!=target){
		prev=prev->next;
	}
	if(prev->next==NULL){
		printf("未找到\n");
		return head;
	}
	Node* tmp=prev->next;
	prev->next=tmp->next;
	free(tmp);
	return head;
	}
```





#### 

### 4. 链表反转

```
// 迭代方式反转链表
Node* reverseList(Node* head) {
    Node* prev = NULL;
    Node* current = head;
    Node* next = NULL;
    
    while (current != NULL) {
        next = current->next;   // 保存下一个节点
        current->next = prev;   // 反转指针
        prev = current;         // 移动prev
        current = next;         // 移动current
    }
    return prev;  // 返回新的头节点
}

// 递归方式反转链表
Node* reverseListRecursive(Node* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    
    Node* newHead = reverseListRecursive(head->next);
    head->next->next = head;
    head->next = NULL;
    return newHead;
}
```

### 5. 完整示例程序

```
#include<stdio.h>
#include <stdlib.h>
//节点结构定义
typedef struct Node {
	int data;
	struct Node *next;
}Node;
//创建单个节点
Node *createNode(int data){
	Node *newnode=(Node*)malloc(sizeof(Node));
	if(newnode==NULL)return NULL;
	newnode->data=data;
	newnode->next=NULL;
	return newnode;
}
//不带头节点的尾插法建立链表
Node *tailInsert(int n){
	Node* head=NULL;
	Node* tail=NULL;
	int data;
	
	printf("请输入%d个数据",n);
	for(int i=0;i<n;i++){
		printf("请输入第%d个数据的值：",i+1);
		scanf("%d",&data);
		Node* newnode=(Node*)malloc(sizeof(Node));
		if(newnode==NULL){
    printf("内存分配失败\n");
    continue;
	}
	newnode->data = data;
	newnode->next = NULL; 
		
		
		if(head==NULL){
			head=newnode;
			tail=newnode;
		}else{
			tail->next=newnode;
			tail=newnode;
		}
	}
	return head;
}
//带头节点的尾插法
Node *htailInsert(int n){
	Node* head=(Node*)malloc(sizeof(Node));
	head->next=NULL;
	Node* tail=NULL;
	int data;
	
	printf("请输入%d个数据",n);
	for(int i=0;i<n;i++){
		printf("请输入第%d个数据的值：",i+1);
		scanf("%d",&data);
		Node* newnode=(Node*)malloc(sizeof(Node));
		if(newnode==NULL)continue;
		newnode->data=data;
		if(head->next==NULL){
			head->next=newnode;
			tail=newnode;
		}else{
			tail->next=newnode;
			tail=newnode;
		}
	}
	return head;
}


//带头节点头插法
Node *hheadInsert(int n){
	
	Node *head = (Node*)malloc(sizeof(Node));
	head->next=NULL;
	int data;
	printf("请输入%d个数据",n);
	for(int i=0;i<n;i++){
		printf("请输入第%d个数据的值：",i+1);
		scanf("%d",&data);
		Node* newnode=(Node*)malloc(sizeof(Node));
		if(newnode==NULL)continue;
		
		newnode->data=data;
		newnode->next=head->next;
		head->next=newnode;	
}
return head;
}
//不带头节点的头插法
Node *headInsert(int n){
	Node *head=NULL;
	int data;
	printf("请输入%d个数据",n);
	for(int i=0;i<n;i++){
		printf("请输入第%d个数据的值：",i+1);
		scanf("%d",&data);
		Node* newnode=(Node*)malloc(sizeof(Node));
		if(newnode==NULL)continue;
		newnode->data=data;
		newnode->next=head;
		head=newnode;
		
	}
	return head;
}

//在指定位置插入
Node *headwzInsert(Node* head,int Insertwz,int data){
	Node *newnode = createNode(data);
	if(newnode==NULL){
		printf("内存分配失败\n");
		return head;
	}
    // 处理空链表
    if (head == NULL) {
        if (Insertwz == 1) {
            return newnode;  // ? 空链表只能在位置1插入
        } else {
            printf("错误：空链表只能在位置1插入\n");
            free(newnode);
            return NULL;
        }
    }
	
	if (Insertwz == 1) {
        newnode->next = head;
        return newnode;
    }
    
	Node* prev=head;
	int i=1;
	while(prev->next!=NULL&&i<Insertwz-1){
		prev=prev->next;
		i++;
	}
	
	    // 检查位置是否有效
	if (i < Insertwz - 1) {
    free(newnode);
    printf("错误：插入位置 %d 超出链表范围\n", Insertwz);
    return head;
    }
	
	newnode->next=prev->next;
	prev->next=newnode;
	
	return head;
}


//不带头节点打印
void PrihList(Node* head){
	Node* p=head;
	while(p!=NULL){
		printf("%d ",p->data);
		p=p->next;
	}
}
//不带头节点寻找
void searchList(Node* head,int data){
	Node* p=head;
	int i=1;
	while(p!=NULL){
		if(p->data==data){
			printf("在第%d个位置找到：%d",i,p->data);
		}
		p=p->next;
		i++;
	}
}

//带头节点寻找 
void searchListhead(Node* head,int data){
	Node* p=head->next;
	int i=1;
	while(p!=NULL){
		if(p->data==data){
			printf("在第%d个位置找到：%d",i,p->data);
		}
		p=p->next;
		i++;
	}
}

//带头节点打印
void PrihListhead(Node* head){
	Node* p=head->next;
	while(p!=NULL){
		printf("%d ",p->data);
		p=p->next;
	}
}
//获取链表长度
int getLenList(Node* head){
	Node* p=head;
	int len=0;
	while(p!=NULL){
		p=p->next;
		len++;
	}
	return len;
}
//获取链表长度带head
int getLenListhead(Node* head){
	Node* p=head->next;
	int len=0;
	while(p!=NULL){
		p=p->next;
		len++;
	}
	return len;
}
//删除节点操作
Node* DeleteList(Node* head,int target){
	 // ========== 情况1：空链表 ==========
	 if(head==NULL){
		printf("链表为空\n");
		return NULL;
	 }
	 //========== 情况2：删除的为头节点 ==========
	 if(head->data==target){
		Node* tmp=head;
		head=head->next;
		free(tmp);
        printf("删除头节点成功\n");
        return head;  // 返回新头指针
	 }
	 //========== 情况3：删除的非头节点 ==========
	 Node* prev=head;
	 while(prev->next!=NULL&&prev->next->data!=target){
		 prev=prev->next;
	 }
	 if(prev->next==NULL){
		printf("未找到%d的节点\n",target);
	 }
	 //删除操作
	 Node* temp=prev->next; //将要删除的节点保存
	 prev->next=temp->next;//将前前驱节点指向当前节点的指针转移为当前指针指向后一项的指针
	free(temp);
	return head;
}

//带头节点的删除
Node* DeleteHeList(Node* head,int target){
	//情况1空指针
	if(head==NULL||head->next==NULL){
		printf("空指针\n");
		return NULL;
	}
	//情况2删除
	Node *prev=head;
	while(prev->next!=NULL&&prev->next->data!=target){
		prev=prev->next;
	}
	if(prev->next==NULL){
		printf("未找到\n");
		return head;
	}
	Node* tmp=prev->next;
	prev->next=tmp->next;
	free(tmp);
	return head;
}
// 释放链表内存
void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

// 释放带头节点链表
void freeListWithHead(Node* head) {
    if (head == NULL) return;
    Node* current = head->next;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(head);  // 释放头节点
}




int main(){
    printf("=== 测试1：不带头节点尾插法 ===\n");
    Node* list1 = tailInsert(3);
    printf("链表内容：");
    PrihList(list1);
    printf("\n链表长度：%d\n", getLenList(list1));
    
    printf("\n=== 测试2：查找元素 ===\n");
    searchList(list1, 1);
    
    printf("\n=== 测试3：指定位置插入 ===\n");
    list1 = headwzInsert(list1, 2, 99);
    PrihList(list1);
    
    printf("\n=== 测试4：删除节点 ===\n");
    list1 = DeleteList(list1, 99);
    PrihList(list1);
    
    freeList(list1);
    return 0;
 
}
```



### 6. 其他类型链表

#### 6.1 双向链表

```
// 双向链表节点
typedef struct DNode {
    int data;
    struct DNode* prev;
    struct DNode* next;
} DNode;

// 创建双向节点
DNode* createDNode(int data) {
    DNode* newNode = (DNode*)malloc(sizeof(DNode));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// 双向链表头插
DNode* insertAtHeadD(DNode* head, int data) {
    DNode* newNode = createDNode(data);
    if (head != NULL) {
        newNode->next = head;
        head->prev = newNode;
    }
    return newNode;
}
```

#### 6.2 循环链表

```
// 创建循环链表
Node* createCircularList(int arr[], int n) {
    if (n == 0) return NULL;
    
    Node* head = createNode(arr[0]);
    Node* tail = head;
    
    for (int i = 1; i < n; i++) {
        tail->next = createNode(arr[i]);
        tail = tail->next;
    }
    
    tail->next = head;  // 最后一个节点指向头节点
    return head;
}
```













# 补充：疑难杂症 

------

### 一、补码、反码、进制

#### 1.1 原码、反码、补码

| 类型 | 正数（+5） | 负数（-5） |
| :--- | :--------- | :--------- |
| 原码 | 00000101   | 10000101   |
| 反码 | 00000101   | 11111010   |
| 补码 | 00000101   | 11111011   |

**规则**：

- 正数：原码 = 反码 = 补码
- 负数：反码 = 原码符号位不变，其余取反；补码 = 反码 + 1
- 计算机存储的是**补码**

#### 1.2 进制转换

| 进制     | 前缀                | 示例          |
| :------- | :------------------ | :------------ |
| 二进制   | `0b` 或 `0B`（C99） | `0b1010` = 10 |
| 八进制   | `0`                 | `012` = 10    |
| 十进制   | 无                  | `10`          |
| 十六进制 | `0x` 或 `0X`        | `0xA` = 10    |

```
int a = 0b1010;   // 二进制（C99支持）
int b = 012;      // 八进制 = 10
int c = 10;       // 十进制
int d = 0xA;      // 十六进制 = 10

printf("%d %d %d %d\n", a, b, c, d);  // 10 10 10 10
```

#### 1.3 数据长度（sizeof）

| 类型        | 32位系统 | 64位系统 |
| :---------- | :------- | :------- |
| `char`      | 1        | 1        |
| `short`     | 2        | 2        |
| `int`       | 4        | 4        |
| `long`      | 4        | 8        |
| `long long` | 8        | 8        |
| `float`     | 4        | 4        |
| `double`    | 8        | 8        |
| `指针`      | 4        | 8        |

------

### 二、自增、自减运算符

| 运算符 | 含义          | 示例       | 结果             |
| :----- | :------------ | :--------- | :--------------- |
| `i++`  | 先使用，后加1 | `a = i++;` | a = 原i, i = i+1 |
| `++i`  | 先加1，后使用 | `a = ++i;` | i = i+1, a = 新i |
| `i--`  | 先使用，后减1 | `a = i--;` | a = 原i, i = i-1 |
| `--i`  | 先减1，后使用 | `a = --i;` | i = i-1, a = 新i |

```
int i = 5;
int a = i++;  // a=5, i=6
int b = ++i;  // i=7, b=7
```



**常见陷阱**：

```
int i = 5;
int a = i++ + ++i;  // 未定义行为！不同编译器结果不同
// 不要在一个表达式里对同一变量多次自增
```



------

### 三、变量的存储方式和生存周期

#### 3.1 存储类别

| 关键字           | 存储位置       | 生命周期 | 作用域     | 初始值 |
| :--------------- | :------------- | :------- | :--------- | :----- |
| `auto`（默认）   | 栈             | 代码块内 | 代码块内   | 随机   |
| `static`（局部） | 静态区         | 整个程序 | 代码块内   | 0      |
| `static`（全局） | 静态区         | 整个程序 | 本文件内   | 0      |
| `extern`         | 全局           | 整个程序 | 多文件共享 | 0      |
| `register`       | 寄存器（建议） | 代码块内 | 代码块内   | 随机   |

#### 3.2 示例

```
// static局部变量：函数结束不销毁
void func() {
    static int count = 0;  // 只初始化一次
    count++;
    printf("第%d次调用\n", count);
}

int main() {
    func();  // 第1次调用
    func();  // 第2次调用
    func();  // 第3次调用
    return 0;
}
```

#### 3.3 static 对全局变量的影响

```
// file1.c
int global = 10;        // 可被其他文件访问
static int hidden = 20; // 只能在本文件访问

// file2.c
extern int global;      // ✅ 可以访问
// extern int hidden;   // ❌ 错误，static限制在本文件
```

------

### 四、内部函数和外部函数

#### 4.1 内部函数（static）

```
// 只能在当前文件内调用
static void helper() {
    printf("内部函数\n");
}
```

#### 4.2 外部函数（extern，默认）

```
// 方式1：不加extern（默认）
void func1() { }

// 方式2：加extern（显式）
extern void func2() { }

// 在另一个文件中声明后即可调用
// extern void func1();  // 声明
```

#### 4.3 多文件示例

```
// math.c
int add(int a, int b) {
    return a + b;
}

static int sub(int a, int b) {  // 内部函数，只能在math.c使用
    return a - b;
}

// main.c
#include <stdio.h>
extern int add(int, int);  // 声明外部函数

int main() {
    printf("%d\n", add(3, 5));  // ✅ 可以
    // printf("%d\n", sub(3, 5));  // ❌ 错误，sub不可见
    return 0;
}
```

------

### 五、其他常见疑难杂症

#### 5.1 类型转换（隐式）

```
int a = 3.14;      // 3（截断）
double b = 3;      // 3.0
char c = 65;       // 'A'（ASCII）
int d = 'A';       // 65
```

#### 5.2 强制类型转换

```
int a = 10, b = 3;
float c = (float)a / b;  // 3.333...（不加(float)会得3）
```

#### 5.3 逗号运算符

```
int a = (5, 10);   // a = 10（取最后一个表达式的值）
int i, j;
for (i = 0, j = 10; i < j; i++, j--);  // 常用在for循环
```

#### 5.4 三目运算符

```
int max = (a > b) ? a : b;  // 如果a>b取a，否则取b
```

## C语言链表详解

链表是一种重要的动态数据结构，由一系列节点组成，每个节点包含数据和指向下一个节点的指针。

### 1. 链表的基本概念

**优点：**

- 动态内存分配，不需要预知最大长度
- 插入删除操作高效（只需修改指针）
- 内存利用率高

**缺点：**

- 不支持随机访问
- 需要额外存储指针，内存开销大
- 实现比数组复杂

### 2. 单向链表的基本实现

#### 2.1 节点结构定义

c

```
#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构
typedef struct Node {
    int data;           // 数据域
    struct Node* next;  // 指针域
} Node;

// 或者这样定义（更常见）
struct ListNode {
    int val;
    struct ListNode *next;
};
```



#### 2.2 创建节点

c

```
// 创建新节点
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
```



### 3. 链表基本操作

#### 3.1 初始化链表

c

```
// 初始化空链表
Node* initList() {
    return NULL;  // 空链表头指针为NULL
}

// 带头节点的初始化
Node* initListWithHead() {
    Node* head = (Node*)malloc(sizeof(Node));
    if (head == NULL) return NULL;
    head->data = 0;      // 头节点数据可以不用
    head->next = NULL;
    return head;
}
```



#### 3.2 插入操作

c

```
// 1. 头插法（在链表头部插入）
Node* insertAtHead(Node* head, int data) {
    Node* newNode = createNode(data);
    newNode->next = head;
    return newNode;  // 返回新的头节点
}

// 2. 尾插法（在链表尾部插入）
Node* insertAtTail(Node* head, int data) {
    Node* newNode = createNode(data);
    
    if (head == NULL) {
        return newNode;
    }
    
    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    return head;
}

// 3. 在指定位置插入（位置从0开始）
Node* insertAtPosition(Node* head, int data, int position) {
    if (position < 0) return head;
    
    // 头插法情况
    if (position == 0) {
        return insertAtHead(head, data);
    }
    
    Node* newNode = createNode(data);
    Node* current = head;
    
    // 找到要插入位置的前一个节点
    for (int i = 0; i < position - 1 && current != NULL; i++) {
        current = current->next;
    }
    
    if (current == NULL) {
        printf("位置超出链表长度\n");
        free(newNode);
        return head;
    }
    
    newNode->next = current->next;
    current->next = newNode;
    return head;
}
```



#### 3.3 删除操作

c

```
// 1. 删除头节点
Node* deleteAtHead(Node* head) {
    if (head == NULL) {
        printf("链表为空\n");
        return NULL;
    }
    
    Node* temp = head;
    head = head->next;
    free(temp);
    return head;
}

// 2. 删除指定值的节点（删除第一个匹配的）
Node* deleteByValue(Node* head, int value) {
    if (head == NULL) return NULL;
    
    // 如果头节点就是要删除的节点
    if (head->data == value) {
        return deleteAtHead(head);
    }
    
    Node* current = head;
    while (current->next != NULL && current->next->data != value) {
        current = current->next;
    }
    
    if (current->next == NULL) {
        printf("未找到值为%d的节点\n", value);
        return head;
    }
    
    Node* temp = current->next;
    current->next = temp->next;
    free(temp);
    return head;
}

// 3. 删除指定位置的节点
Node* deleteAtPosition(Node* head, int position) {
    if (head == NULL || position < 0) return head;
    
    if (position == 0) {
        return deleteAtHead(head);
    }
    
    Node* current = head;
    for (int i = 0; i < position - 1 && current->next != NULL; i++) {
        current = current->next;
    }
    
    if (current->next == NULL) {
        printf("位置超出链表范围\n");
        return head;
    }
    
    Node* temp = current->next;
    current->next = temp->next;
    free(temp);
    return head;
}
```



#### 3.4 查找操作

c

```
// 查找指定值的节点
Node* search(Node* head, int target) {
    Node* current = head;
    int position = 0;
    
    while (current != NULL) {
        if (current->data == target) {
            printf("找到节点: 值=%d, 位置=%d\n", current->data, position);
            return current;
        }
        current = current->next;
        position++;
    }
    
    printf("未找到值为%d的节点\n", target);
    return NULL;
}

// 获取链表长度
int getLength(Node* head) {
    int length = 0;
    Node* current = head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}
```



#### 3.5 遍历和打印

c

```
// 打印链表
void printList(Node* head) {
    Node* current = head;
    printf("链表: ");
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// 递归方式遍历
void printListRecursive(Node* head) {
    if (head == NULL) {
        printf("NULL\n");
        return;
    }
    printf("%d -> ", head->data);
    printListRecursive(head->next);
}
```



### 4. 链表反转

c

```
// 迭代方式反转链表
Node* reverseList(Node* head) {
    Node* prev = NULL;
    Node* current = head;
    Node* next = NULL;
    
    while (current != NULL) {
        next = current->next;   // 保存下一个节点
        current->next = prev;   // 反转指针
        prev = current;         // 移动prev
        current = next;         // 移动current
    }
    return prev;  // 返回新的头节点
}

// 递归方式反转链表
Node* reverseListRecursive(Node* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    
    Node* newHead = reverseListRecursive(head->next);
    head->next->next = head;
    head->next = NULL;
    return newHead;
}
```



### 5. 完整示例程序

c

```
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 创建节点
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// 尾插法创建链表
Node* createList(int arr[], int n) {
    Node* head = NULL;
    for (int i = 0; i < n; i++) {
        head = insertAtTail(head, arr[i]);
    }
    return head;
}

// 释放链表内存
void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

// 主函数演示
int main() {
    // 创建链表
    int arr[] = {1, 2, 3, 4, 5};
    Node* list = createList(arr, 5);
    
    printf("原链表: ");
    printList(list);
    printf("链表长度: %d\n", getLength(list));
    
    // 头插法
    list = insertAtHead(list, 0);
    printf("头插0后: ");
    printList(list);
    
    // 尾插法
    list = insertAtTail(list, 6);
    printf("尾插6后: ");
    printList(list);
    
    // 指定位置插入
    list = insertAtPosition(list, 100, 3);
    printf("位置3插入100: ");
    printList(list);
    
    // 删除操作
    list = deleteByValue(list, 3);
    printf("删除值为3的节点: ");
    printList(list);
    
    list = deleteAtPosition(list, 2);
    printf("删除位置2的节点: ");
    printList(list);
    
    // 反转链表
    list = reverseList(list);
    printf("反转后: ");
    printList(list);
    
    // 查找
    search(list, 100);
    
    // 释放内存
    freeList(list);
    
    return 0;
}
```



### 6. 其他类型链表

#### 6.1 双向链表

c

```
// 双向链表节点
typedef struct DNode {
    int data;
    struct DNode* prev;
    struct DNode* next;
} DNode;

// 创建双向节点
DNode* createDNode(int data) {
    DNode* newNode = (DNode*)malloc(sizeof(DNode));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// 双向链表头插
DNode* insertAtHeadD(DNode* head, int data) {
    DNode* newNode = createDNode(data);
    if (head != NULL) {
        newNode->next = head;
        head->prev = newNode;
    }
    return newNode;
}
```



#### 6.2 循环链表

c

```
// 创建循环链表
Node* createCircularList(int arr[], int n) {
    if (n == 0) return NULL;
    
    Node* head = createNode(arr[0]);
    Node* tail = head;
    
    for (int i = 1; i < n; i++) {
        tail->next = createNode(arr[i]);
        tail = tail->next;
    }
    
    tail->next = head;  // 最后一个节点指向头节点
    return head;
}
```



### 7. 常见问题和技巧

c

```
// 1. 检测环（快慢指针）
int hasCycle(Node* head) {
    if (head == NULL) return 0;
    
    Node* slow = head;
    Node* fast = head;
    
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return 1;
    }
    return 0;
}

// 2. 寻找中间节点（快慢指针）
Node* findMiddle(Node* head) {
    if (head == NULL) return NULL;
    
    Node* slow = head;
    Node* fast = head;
    
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// 3. 删除重复节点（已排序链表）
Node* deleteDuplicates(Node* head) {
    if (head == NULL) return NULL;
    
    Node* current = head;
    while (current->next != NULL) {
        if (current->data == current->next->data) {
            Node* temp = current->next;
            current->next = temp->next;
            free(temp);
        } else {
            current = current->next;
        }
    }
    return head;
}
```



### 
