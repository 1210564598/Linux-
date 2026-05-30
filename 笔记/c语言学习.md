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

## 四、数组经典操作（必背）

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
			if(arry[j]>arry[max]){  //更新位置
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
