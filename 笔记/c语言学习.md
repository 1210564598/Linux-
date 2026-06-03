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

## 六、指针与二维数组（

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

- 定义：`int (*p)[4];` —— `p` 指向一个包含4个整型元素的一维数组。
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
		printf("%d ",*(p+i));
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

