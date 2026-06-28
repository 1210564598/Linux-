# Linux 系统编程 —— 文件编程

## 一、核心思想与应用场景

1. **学习目标**：掌握 Linux 系统调用 API，用代码自动化完成文件创建、打开、读写、偏移、关闭，替代手动操作文件（Word、配置、游戏存档、账单等场景）。
2. **Linux 设计理念**：**一切皆文件**，普通文件、文件夹、硬件设备、管道、Socket 都统一用文件接口操作。
3. 分层架构（VFS 虚拟文件系统）
   - 用户层：应用程序调用系统 API
   - 系统调用层 SCI：统一接口
   - VFS 虚拟文件系统：屏蔽 ext4/ext3/btrfs 等不同文件系统差异
   - 块设备层 + 驱动：对接磁盘硬件

## 二、文件基础概念

### 1. 静态文件 & 动态文件

- **静态文件**：存于磁盘块设备上的原始文件。
- **动态文件**：调用`open`后，内核将磁盘文件加载到内存生成副本；读写仅操作内存动态文件，调用`close`时同步写回磁盘。
- 设计优势：内存按字节灵活读写，磁盘只能按块操作，效率更高。

### 2. 文件描述符 fd

1. 定义：非负整数，进程内唯一标识打开的文件，内核通过 fd 关联文件内核数据结构。
2. 标准默认 fd（进程启动自动打开）
   - 0：标准输入 STDIN_FILENO
   - 1：标准输出 STDOUT_FILENO
   - 2：标准错误 STDERR_FILENO
3. 特性：仅当前进程有效；`open`成功返回最小可用 fd，失败返回 - 1。

## 三、核心系统调用 API（无缓冲系统调用）

### 1. open /creat 打开 / 创建文件

#### 头文件

```
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
```

#### 函数原型

```
int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);
int creat(const char *pathname, mode_t mode);
```

#### 参数说明

1. `pathname`：文件路径，缺省为当前目录。

2. ```
   flags
   ```

   （必选三选一 + 可选组合）

   - 基础权限：`O_RDONLY`只读 / `O_WRONLY`只写 / `O_RDWR`读写
   - 扩展标志：
     - `O_CREAT`：文件不存在则创建，必须搭配第三个参数 mode
     - `O_EXCL`：配合 O_CREAT，文件已存在则报错
     - `O_TRUNC`：打开时清空原有文件内容
     - `O_APPEND`：写入自动追加到文件末尾

3. ```
   mode
   ```

   ：新建文件权限，仅 O_CREAT 生效，数字权限规则：

   - S_IRUSR (4) 读、S_IWUSR (2) 写、S_IXUSR (1) 执行，7 = 读写执行。

#### creat 简化：等价`open(path, O_WRONLY|O_CREAT|O_TRUNC, mode)`，专门用于新建文件。

### 2. write 写入文件

#### 头文件

```
#include <unistd.h>
```

#### 原型

```
ssize_t write(int fd, const void *buf, size_t count);
```

- buf：待写入数据缓冲区；count：期望写入字节数
- 返回值：成功返回实际写入字节，0 无写入；失败返回 - 1
- 特性：O_APPEND 模式下写前自动偏移到文件末尾；文件偏移量随写入自动后移。

### 3. read 读取文件

#### 原型

```
ssize_t read(int fd, void *buf, size_t count);
```

- buf：存放读取数据的缓冲区
- 返回值：成功返回读到字节，0 代表读到文件末尾 EOF；失败返回 - 1。

### 4. lseek 文件读写指针偏移（光标定位）

#### 头文件

```
#include <sys/types.h>
#include <unistd.h>
```

#### 原型

```
off_t lseek(int fd, off_t offset, int whence);
```

- offset：偏移字节数，**正数向后、负数向前**
- whence 基准位置：
  - SEEK_SET：文件开头
  - SEEK_CUR：当前指针位置
  - SEEK_END：文件末尾
- 用途：跳转读写位置、获取文件总大小。

### 5. close 关闭文件

```
int close(int fd);
```

- 功能：释放文件描述符，将内存动态文件同步写入磁盘；进程最后一个 fd 关闭后释放内核资源。
- 返回 0 成功，-1 失败。

## 四、文件编程标准流程

1. open/creat 打开 / 创建文件，获取 fd（必须判断打开是否成功）
2. read/write/lseek 执行读写、偏移操作
3. close 关闭文件（不关闭会丢失数据、占用资源）

## 五、拓展知识点

1. 文件底层原理：inode 节点、文件共享、用户文件权限模型。
2. 两类文件操作接口区分
   - **系统调用（open/read/write）**：内核提供，无用户缓冲区，直接操作内核缓冲区。
   - **标准库 IO（fopen/fread/fwrite/fseek/fclose/fgetc/fputc）**：C 库封装，自带用户缓冲区，底层仍调用系统调用。
3. 实战练手项目
   - 实现简易 cp 复制命令（读源文件、写入目标文件）
   - 修改文本配置文件（键值对如 SPEED=5）
   - 二进制读写：将结构体存入文件、读取结构体数据。

## 六、关键注意事项

1. open 创建文件必须指定 mode 权限，否则权限异常。
2. 读写前必须校验 fd 是否合法，避免操作无效文件。
3. 操作完成务必 close，否则内存数据无法同步到磁盘，文件损坏。
4. 文件描述符仅当前进程生效，多进程 fd 互不通用。
5. 静态文件读写间接通过内存动态副本，不直接操作磁盘块。

## 七、例子

#### Linux 文件系统调用完整示例（创建、写、读、偏移、关闭）

#### 示例 1：基础读写文件（open/write/read/lseek/close）

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    // 1. 创建并打开文件：不存在则创建，存在则清空，可读可写，权限0644
    int fd = open("test.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if(fd == -1)  // 原本文件存在打开失败判断
    {
        perror("open failed");
        return -1;
    }

    // 2. 写入数据
    char buf_w[] = "Hello Linux File IO!\n";
    ssize_t w_len = write(fd, buf_w, strlen(buf_w));
    printf("成功写入 %ld 字节\n", w_len);

    // 3. 光标移到文件开头，准备读取
    lseek(fd, 0, SEEK_SET);

    // 4. 读取文件内容
    char buf_r[128] = {0};
    ssize_t r_len = read(fd, buf_r, sizeof(buf_r));
    printf("读取 %ld 字节，内容：%s", r_len, buf_r);

    // 5. 关闭文件，同步数据到磁盘
    close(fd);
    return 0;
}
```

### 编译运行

```
gcc file_demo.c -o file_demo
./file_demo
```

#### 示例 2：实现简易 cp 命令（练手项目）

功能：`./mycp src.txt dest.txt` 复制文件

```
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("用法：%s 源文件 目标文件\n", argv[0]);
        return -1;
    }

    // 打开源文件只读
    int fd_src = open(argv[1], O_RDONLY);
    if(fd_src == -1)
    {
        perror("open src");
        return -1;
    }

    // 创建目标文件，读写，权限644
    int fd_dst = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd_dst == -1)
    {
        perror("open dst");
        close(fd_src);
        return -1;
    }

    char buf[BUF_SIZE];
    ssize_t len;
    // 循环读取源文件，写入目标文件
    while((len = read(fd_src, buf, BUF_SIZE)) > 0)
    {
        write(fd_dst, buf, len);
    }

    close(fd_src);
    close(fd_dst);
    printf("复制完成\n");
    return 0;
}
```

#### 示例 3：结构体写入 / 读取二进制文件

```
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// 定义结构体
typedef struct {
    int speed;
    int length;
    int score;
} Config;

int main()
{
    // 写入结构体
    Config cfg1 = {5, 100, 90};
    int fd = open("config.bin", O_RDWR | O_CREAT | O_TRUNC, 0644);
    write(fd, &cfg1, sizeof(Config));

    // 光标回到开头读取
    lseek(fd, 0, SEEK_SET);
    Config cfg2;
    read(fd, &cfg2, sizeof(Config));

    printf("speed=%d, length=%d, score=%d\n", cfg2.speed, cfg2.length, cfg2.score);

    close(fd);
    return 0;
}
```

### 关键 API 使用要点

1. `O_TRUNC`：打开文件清空原有内容；`O_APPEND` 每次写追加到末尾
2. `lseek(fd, 0, SEEK_END)` 可获取文件总大小（返回值为文件字节数）
3. 文件描述符用完必须 `close()`，否则数据滞留内存不落地磁盘
4. `perror()` 快速打印系统调用错误信息，方便排错

## C 标准库文件 IO：fopen/fread/fwrite/fseek/fclose 完整用法

### 一、与系统调用 open/read/write 区别

1. **系统调用（open/read/write）**：内核接口，无用户缓冲区，操作文件描述符`fd`；
2. **标准库 IO（fopen 系列）**：C 库封装，自带**用户缓冲区**，底层最终调用 open/read/write，操作文件指针`FILE*`；
3. 适用场景：日常开发优先用标准库，简单跨平台；底层内核、设备操作选系统调用。

### 二、全部函数头文件

```
#include <stdio.h>
```

#### 1. fopen 打开文件

##### 原型

```
FILE *fopen(const char *path, const char *mode);
```

##### 返回值

- 成功：返回`FILE*`文件指针；
- 失败：返回`NULL`，配合`perror`查看错误。

##### mode 打开模式（重点）

| 模式 |   作用   | 文件不存在 |      文件存在      |
| :--: | :------: | :--------: | :----------------: |
|  r   |   只读   | 报错 NULL  |       从头读       |
|  w   |   只写   |    创建    |    清空原有内容    |
|  a   |  追加写  |    创建    |      末尾追加      |
|  r+  |   读写   | 报错 NULL  |      从头读写      |
|  w+  |   读写   |    创建    |    清空原有内容    |
|  a+  | 读写追加 |    创建    | 读从头，写自动末尾 |

##### 二进制兼容（Windows 区分文本 / 二进制，Linux 可加可不加）

```
rb wb ab rb+ wb+ ab+
```

#### 2. fclose 关闭文件

##### 原型

```
int fclose(FILE *stream);
```

- 功能：刷新缓冲区数据到文件、释放 FILE 资源；
- 返回：成功 0，失败 EOF (-1)；
- 必须调用，否则缓冲区数据丢失、资源泄漏。

#### 3. fwrite 写入数据（二进制 / 文本通用）

##### 原型

```
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
```

参数：

1. `ptr`：待写入数据缓冲区首地址
2. `size`：单个数据块字节大小
3. `nmemb`：要写入多少个块
4. `stream`：FILE 文件指针

返回值：**实际成功写入的块数量**，小于 nmemb 代表出错。

#### 4. fread 读取数据

##### 原型

```
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
```

参数同 fwrite；

返回值：读到的块数；返回 0 代表读到文件末尾 / 读取失败。

#### 5. fseek 文件指针偏移（对应 lseek）

##### 原型

```
int fseek(FILE *stream, long offset, int whence);
```

1. `offset`：偏移字节，正数向后、负数向前

2. ```
   whence
   ```

    基准位置：

   - `SEEK_SET`：文件开头

   - `SEEK_CUR`：当前指针位置

   - ```
     SEEK_END：文件末尾
     返回：成功 0，失败非 0。
     ```

##### 配套工具函数

- `ftell(FILE* fp)`：获取当前指针距离文件开头的字节数（求文件大小常用）
- `rewind(FILE* fp)`：等价 `fseek(fp,0,SEEK_SET)`，直接回到文件开头

### 三、完整示例代码

#### 示例 1：基础文本读写

```
#include <stdio.h>
#include <string.h>

int main(void)
{
    // 1. w模式打开，不存在创建，存在清空
    FILE *fp = fopen("std.txt", "w+");
    if(fp == NULL)
    {
        perror("fopen");
        return -1;
    }

    // 写入字符串
    char buf_w[] = "标准库IO fwrite测试\n";
    fwrite(buf_w, sizeof(char), strlen(buf_w), fp);

    // 光标回到文件开头
    rewind(fp);

    // 读取内容
    char buf_r[128] = {0};
    size_t ret = fread(buf_r, sizeof(char), 127, fp);
    printf("读取块数：%zu，内容：%s", ret, buf_r);

    fclose(fp);
    return 0;
}
```

#### 示例 2：二进制读写结构体（对应系统调用结构体示例）

```
#include <stdio.h>

typedef struct {
    int speed;
    int length;
    int score;
} Config;

int main(void)
{
    // 二进制读写用wb、rb
    FILE *fp = fopen("cfg.bin", "wb+");
    if(!fp)
    {
        perror("fopen");
        return -1;
    }

    Config c1 = {5, 100, 90};
    // 写入1个Config大小的数据块
    fwrite(&c1, sizeof(Config), 1, fp);

    // 偏移到文件开头
    fseek(fp, 0, SEEK_SET);

    Config c2;
    fread(&c2, sizeof(Config), 1, fp);
    printf("speed:%d len:%d score:%d\n", c2.speed, c2.length, c2.score);

    fclose(fp);
    return 0;
}
```

#### 示例 3：获取文件大小（fseek+ftell）

```
#include <stdio.h>

int get_file_size(const char *path)
{
    FILE *fp = fopen(path, "rb");
    if(fp == NULL)
        return -1;
    // 指针移到文件末尾
    fseek(fp, 0, SEEK_END);
    // 获取当前偏移值即总字节
    long size = ftell(fp);
    fclose(fp);
    return size;
}

int main(void)
{
    long sz = get_file_size("std.txt");
    printf("文件总字节：%ld\n", sz);
    return 0;
}
```

#### 四、常见易错点

1. fopen 返回值必须判 NULL，不能直接操作；
2. `w`/`w+` 打开会直接清空文件，谨慎使用；
3. a 模式只能在末尾写，无法通过 fseek 修改前面内容；
4. fwrite/fread 是按**块**计数，不是字节，不要混淆 size 和 nmemb；
5. 程序结束前必须 fclose，否则缓冲区数据不会落地磁盘；
6. 文本模式 Windows 会自动转换`\n<->\r\n`，二进制模式 rb/wb 不转换，Linux 无区别。

### 补充：字符读写配套函数（拓展）

```
int fgetc(FILE* fp);  // 读单个字符
int fputc(int c, FILE* fp); // 写单个字符
char *fgets(char *s, int size, FILE *fp); // 读一行字符串
int fputs(const char *s, FILE *fp); // 写一行字符串
int feof(FILE *fp); // 判断是否到达文件末尾
```



# Linux 系统编程 —— 进程（完整笔记 + 配套示例代码）

## 一、基础核心概念

### 1. 程序 vs 进程

- **程序**：静态概念，磁盘上编译生成的二进制可执行文件，仅占用磁盘空间，无运行资源。
- **进程**：程序的一次运行实例，操作系统为其分配内存、PID、文件描述符等资源，动态存在；同一个程序可同时运行多个进程。

### 2. 查看系统进程命令

1. ```
   ps ：查看进程快照，常搭配 
   ```

   ```
   grep 过滤指定进程
   ```

   ```
   ps aux | grep test
   ```

2. `top`：动态实时监控进程资源占用，类似 Windows 任务管理器

### 3. 进程标识符 PID

每个进程拥有唯一非负整数 ID，相当于进程身份证：

- PID=0：交换进程 swapper，内核调度进程；
- PID=1：init/systemd，系统初始化、收养孤儿进程；
- API：
  - `getpid()`：获取当前进程 PID
  - `getppid()`：获取父进程 PID

**示例代码：获取 PID**

```
#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("当前进程pid：%d\n", getpid());
    printf("父进程pid：%d\n", getppid());
    return 0;
}
```

### 4. 父进程 & 子进程

进程 A 调用`fork()`创建进程 B，则 A 为父进程，B 为子进程，父子是相对关系。

### 5. C 程序内存空间分布（低地址 → 高地址）

1. **正文段.text**：只读机器指令，父子进程共享；
2. **初始化数据段.data**：全局初始化变量 `int a=10;`；
3. **未初始化段.bss**：全局未初始化变量，内核自动清零；
4. **堆 heap**：`malloc/free` 动态内存，位于 bss 与栈之间；
5. **栈 stack**：局部变量、函数栈帧、函数返回地址；
6. 命令行参数、环境变量（内存最高地址）。

## 二、进程创建 fork /vfork

### 1. fork()

头文件：`#include <unistd.h>`

原型：`pid_t fork(void);`

#### 返回值（调用 1 次，返回 2 次）

1. 返回 `0`：当前代码运行在**子进程**；
2. 返回 **正数**：当前代码运行在**父进程**，返回值为子进程 PID；
3. 返回 `-1`：进程创建失败。

#### 底层机制：写时复制 COW

现代 Linux 不会完整复制父进程内存：

1. 父子共享堆、栈、数据段，页面设置只读；
2. 任意进程修改内存时，内核仅复制被修改的内存页，节省内存开销；
3. 只读正文段永久共享。

#### fork 两大使用场景

1. 网络服务：父进程等待客户端连接，fork 子进程处理请求，父进程继续监听；
2. Shell 终端：子进程 fork 后调用 exec 执行外部命令。

**示例 1：基础 fork 区分父子进程**

```
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
    pid_t pid = fork();
    if(pid == -1)
    {
        perror("fork fail");
        return -1;
    }
    else if(pid == 0)
    {
        // 子进程
        printf("【子进程】pid=%d, 父pid=%d\n", getpid(), getppid());
    }
    else
    {
        // 父进程
        printf("【父进程】pid=%d, 子pid=%d\n", getpid(), pid);
    }
    return 0;
}
```

**示例 2：验证 COW 写时复制**

```
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int num = 100;
    pid_t pid = fork();
    if(pid < 0)
    {
        perror("fork");
        return -1;
    }
    if(pid == 0)
    {
        num = 200;
        printf("子进程 num=%d, 虚拟地址=%p\n", num, &num);
    }
    else
    {
        sleep(1);
        printf("父进程 num=%d, 虚拟地址=%p\n", num, &num);
    }
    return 0;
}
```

现象：虚拟地址看似相同，实际为不同物理内存，修改互不影响。

### 2. vfork () 与 fork 核心区别

1. 不拷贝内存，父子**完全共享地址空间**；
2. 调度规则：子进程优先运行，子进程`exit()`/exec 后父进程才会执行；
3. 限制：子进程不能使用`return`，必须调用`exit()`或 exec，否则程序崩溃。

**示例 3：vfork 演示**

```
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    int a = 10;
    pid_t pid = vfork();
    if(pid == -1)
    {
        perror("vfork");
        return -1;
    }
    if(pid == 0)
    {
        a = 1000;
        printf("子进程 a=%d\n", a);
        exit(0); // vfork子进程必须exit
    }
    printf("父进程 a=%d\n", a);
    return 0;
}
```

## 三、进程退出方式

### 1. 正常退出

1. main 函数`return`；
2. 标准库 `exit(status)`：刷新 IO 缓冲区，执行退出回调；
3. 系统调用 `_exit()` / `_Exit()`：直接终止进程，不刷新缓冲区；
4. 最后一个线程返回 / `pthread_exit`。

### 2. 异常退出

1. `abort()` 主动触发崩溃；
2. 接收未捕获信号（Ctrl+C、段错误等）；
3. 线程取消响应。

### 退出状态说明

进程终止时携带退出状态，父进程必须通过`wait/waitpid`回收；未回收则子进程变为**僵尸进程**。

## 四、等待子进程 wait /waitpid

### 1. wait()

原型：`pid_t wait(int *status);`

- 阻塞等待任意子进程退出；
- 无任何子进程直接返回 - 1；
- status：接收子进程退出状态，传`NULL`代表不关心退出码。

**示例 4：wait 阻塞回收子进程**

```
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void)
{
    pid_t pid = fork();
    int status;
    if(pid == -1)
    {
        perror("fork");
        return -1;
    }
    if(pid == 0)
    {
        printf("子进程运行，即将退出\n");
        exit(66); // 自定义退出码66
    }
    // 父进程阻塞等待子进程结束
    wait(&status);
    if(WIFEXITED(status))
    {
        printf("子进程正常退出，退出码：%d\n", WEXITSTATUS(status));
    }
    return 0;
}
```

### 2. waitpid ()（功能更灵活）

原型：`pid_t waitpid(pid_t pid, int *status, int options);`

#### pid 参数

- pid=-1：等待任意子进程，等价 wait；
- pid>0：等待指定 PID 的子进程；
- pid=0：等待同进程组所有子进程；
- pid<-1：等待对应进程组所有子进程。

#### options 常用标志

- `WNOHANG`：非阻塞，无子进程退出直接返回 0；
- `WUNTRACED`：返回暂停的子进程状态；
- `WCONTINUED`：返回暂停后恢复运行的子进程。

### 3. 解析退出状态宏（配合 status）

1. `WIFEXITED(status)`：正常退出为真，`WEXITSTATUS()`获取 exit 参数；
2. `WIFSIGNALED(status)`：信号杀死为真，`WTERMSIG()`获取信号编号；
3. `WIFSTOPPED(status)`：进程暂停，`WSTOPSIG()`获取暂停信号；
4. `WIFCONTINUED(status)`：暂停后恢复运行。

**示例 5：waitpid 非阻塞回收 WNOHANG**

```
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid = fork();
    int status;
    if(pid == 0)
    {
        sleep(2);
        printf("子进程结束\n");
        exit(0);
    }
    // 循环非阻塞等待
    while(1)
    {
        pid_t ret = waitpid(pid, &status, WNOHANG);
        if(ret == 0)
        {
            printf("子进程运行中，父进程执行其他业务\n");
            sleep(1);
        }
        else if(ret == pid)
        {
            printf("成功回收子进程，无僵尸\n");
            break;
        }
    }
    return 0;
}
```

## 五、特殊进程

### 1. 僵尸进程

子进程先退出，父进程未调用 wait/waitpid 回收退出状态，子进程 PCB 残留内核，占用 PID 资源。

解决：父进程主动 wait/waitpid、SIGCHLD 信号异步回收。

**示例 6：僵尸进程演示**

```
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid = fork();
    if(pid == 0)
    {
        printf("子进程立刻退出，10秒内为僵尸进程\n");
        exit(0);
    }
    // 父进程休眠10秒，不回收子进程
    sleep(10);
    wait(NULL);
    printf("回收完成，僵尸消失\n");
    return 0;
}
```

运行后新开终端执行 `ps aux | grep defunct` 可看到僵尸标记。

### 2. 孤儿进程

父进程先退出，子进程失去父进程；PID=1 的 init/systemd 自动收养孤儿进程，孤儿不会成为僵尸。

**示例 7：孤儿进程演示**

```
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    pid_t pid = fork();
    if(pid == 0)
    {
        sleep(3);
        printf("孤儿进程 pid=%d, 新父pid=%d\n", getpid(), getppid());
    }
    else
    {
        printf("父进程直接退出\n");
        return 0;
    }
    return 0;
}
```

## 六、exec 函数族

### 作用

fork 创建子进程后，子进程调用 exec 替换自身程序；进程 PID 不变，原有代码、数据、堆栈全部清空，加载新可执行文件。

执行成功无返回；失败返回 - 1，继续执行原代码。

### 函数后缀含义

- `l`：可变参数列表传参，末尾必须传`NULL`；
- `v`：字符串指针数组传参；
- `p`：自动检索 PATH 环境变量，只需传程序名，不用全路径；
- `e`：自定义环境变量数组。

**示例 8：execlp 替换子进程程序（最常用）**

```
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid = fork();
    if(pid == 0
    {
        // 子进程执行 ls -l
        execlp("ls", "ls", "-l", NULL);
        // 执行失败才会走到这里
        perror("execlp fail");
        exit(-1);
    }
    wait(NULL);
    printf("子进程执行外部命令完毕\n");
    return 0;
}
```

## 七、system /popen

### 1. system()

```
int system(const char *cmd);
```

- 创建子进程调用 shell 执行命令；
- 优点：使用简单；缺点：无法获取命令输出内容。

**示例 9：system 执行 shell 命令**

```
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("执行pwd命令：\n");
    int ret = system("pwd");
    printf("system返回状态：%d\n", ret);
    return 0;
}
```

### 2. popen

底层创建管道执行 shell 命令；优势：可以读取命令标准输出，获取执行结果。

**示例 10：popen 读取命令输出**

```
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *fp = popen("whoami", "r");
    char buf[128] = {0};
    fgets(buf, sizeof(buf), fp);
    printf("当前登录用户：%s", buf);
    pclose(fp);
    return 0;
}
```

## 八、综合实战：fork + execlp + waitpid 标准服务模型

```
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void)
{
    printf("父进程持续监听任务...\n");
    pid_t pid = fork();
    if(pid == -1)
    {
        perror("fork");
        return -1;
    }
    if(pid == 0)
    {
        // 子进程执行外部程序date
        execlp("date", "date", NULL);
        perror("exec error");
        exit(1);
    }
    // 父进程阻塞等待子进程回收
    int status;
    waitpid(pid, &status, 0);
    if(WIFEXITED(status))
    {
        printf("任务执行完成，子进程退出码:%d\n", WEXITSTATUS(status));
    }
    return 0;
}
```

# Linux 进程间通信 (IPC) 五种方式

## 一、IPC 基础概念

IPC（InterProcess Communication）：不同进程之间交换、传递信息的技术。

Linux 本地 IPC：**无名管道、FIFO 命名管道、消息队列、信号量、共享内存、信号 (Signal)**；Socket/Streams 可实现跨主机进程通信。

表格

|    IPC 方式    |   通信范围   |   响应速度   |         可靠性         |     携带数据量     | 吞吐量 |        核心用途        |
| :------------: | :----------: | :----------: | :--------------------: | :----------------: | :----: | :--------------------: |
|    无名管道    |  仅亲缘进程  |    毫秒级    |          较高          |       字节流       |   低   |  简单亲缘进程单向通信  |
| FIFO 命名管道  | 本机任意进程 |    毫秒级    |          较高          |       字节流       |   低   | 无亲缘进程简单数据传输 |
|    消息队列    | 本机任意进程 |    毫秒级    |          较高          |     带类型消息     |   中   |  结构化消息、异步通信  |
|     信号量     | 本机任意进程 |      —       |        原子可靠        |     不传输数据     |   无   |    进程互斥、同步锁    |
|    共享内存    | 本机任意进程 |    微秒级    |     需加锁保证可靠     |    任意大小数据    |  最高  |   大批量高速数据交互   |
| 信号（Signal） |   本地本机   | 高（微秒级） | 低（普通信号容易丢失） | 极低（仅信号编号） |  极低  | 进程控制、简单异步通知 |

System V IPC（消息队列、信号量、共享内存）内核对象不会随进程结束自动销毁，必须手动删除。

------

## 1. 无名管道（Pipe）

### 1. 核心特点

1. 半双工：数据单向流动，固定读端`fd[0]`、写端`fd[1]`；双向通信需创建两根管道。
2. 仅亲缘进程通信：父子 / 兄弟进程，无亲缘进程无法使用。
3. 特殊内存文件：不存在磁盘文件系统，仅存内核内存；可用`read/write`读写。
4. 生命周期：随进程，所有进程关闭 fd 后管道销毁。

### 2. 核心 API

```c
#include <unistd.h>
int pipe(int fd[2]);
// 返回0成功，-1失败
```

### 3. 完整代码示例：父进程写，子进程读

```c
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd[2];
    pid_t pid;
    char buf[128] = {0};

    // 1. 创建管道
    pipe(fd);

    // 2. 创建子进程
    pid = fork();

    if(pid > 0)  // 父进程：写数据
    {
        close(fd[0]);   // 父关闭读端
        write(fd[1], "hello pipe", strlen("hello pipe"));
        close(fd[1]);
    }
    else if(pid == 0) // 子进程：读数据
    {
        close(fd[1]);   // 子关闭写端
        read(fd[0], buf, sizeof(buf));
        printf("子进程读到：%s\n", buf);
        close(fd[0]);
    }
    return 0;
}
```

### 4. 优缺点

- 优点：简单、内核原生、轻量；
- 缺点：仅亲缘进程、半双工、缓冲区容量有限、无法持久。

------

## 2. FIFO 命名管道

### 1. 核心特点

1. 无亲缘进程也可通信；
2. 存在磁盘路径，是特殊文件类型，永久存在（需手动删除）；
3. open 阻塞特性：默认阻塞，一端只读 open 会等写端打开，只写 open 等读端打开。
4. 读取后数据自动清除。

### 2. 核心 API

```c
#include <sys/stat.h>
int mkfifo(const char *pathname, mode_t mode);
```

### 3. 代码示例

#### 读端 fifo_read.c

```c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main()
{
    mkfifo("./myfifo", 0664);
    int fd = open("./myfifo", O_RDONLY);
    char buf[128] = {0};
    read(fd, buf, sizeof(buf));
    printf("收到：%s\n", buf);
    close(fd);
    return 0;
}
```

#### 写端 fifo_write.c

```c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd = open("./myfifo", O_WRONLY);
    write(fd, "hello fifo", 10);
    close(fd);
    return 0;
}
```

### 4. 优缺点

- 优点：支持任意进程通信、有文件标识易于管理；
- 缺点：传输速度慢、缓冲区有限。

------

## 3. 消息队列（Message Queue）

### 1. 核心特点

1. 内核链表存储，通过唯一 key / 队列 ID 标识；
2. 面向记录：每条消息带自定义 type 类型，支持按类型选择性读取，不强制 FIFO；
3. 独立于进程：进程退出队列与数据不会销毁，需手动删除；
4. 存在系统容量上限，消息有固定大小。

### 2. 四大核心 API

```c
1 #include <sys/msg.h>
2 // 创建或打开消息队列：成功返回队列ID，失败返回-1
3 int msgget(key_t key, int flag);
4 // 添加消息：成功返回0，失败返回-1
5 int msgsnd(int msqid, const void *ptr, size_t size, int flag);
6 // 读取消息：成功返回消息数据的长度，失败返回-1
7 int msgrcv(int msqid, void *ptr, size_t size, long type,int flag);
8 // 控制消息队列：成功返回0，失败返回-1
9 int msgctl(int msqid, int cmd, struct msqid_ds *buf);

```

#### msgrcv type 读取规则

- `type=0`：读取队列第一条消息；
- `type>0`：读取匹配该 type 的第一条消息；
- `type<0`：读取类型≤绝对值、数值最小的消息（简易优先级）。

### 3. 消息结构体

```c
struct msg_form {
    long mtype;    // 消息类型，必须在最前面
    char mtext[256];
};
```

### 4. 示例代码

#### 发送端 msg_send.c

```c
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf {
    long mtype;
    char mtext[128];
};

int main()
{
    key_t key = ftok(".", 66);
    int msgid = msgget(key, IPC_CREAT|0664);

    struct msgbuf msg;
    msg.mtype = 100;
    sprintf(msg.mtext, "hello msgqueue");

    msgsnd(msgid, &msg, sizeof(msg.mtext), 0);
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
```

#### 接收端 msg_recv.c

```c
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf {
    long mtype;
    char mtext[128];
};

int main()
{
    key_t key = ftok(".", 66);
    int msgid = msgget(key, IPC_CREAT|0664);

    struct msgbuf msg;
    msgrcv(msgid, &msg, sizeof(msg.mtext), 100, 0);
    printf("接收：%s\n", msg.mtext);
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
```

### 5. 优缺点

- 优点：支持定向读取、进程解耦、自带消息边界；
- 缺点：系统全局容量限制、读写有拷贝开销。

------

## 4. 共享内存（Shared Memory）

### 1. 核心特点

1. **Linux 最快 IPC**：进程直接映射同一块物理内存，无内核数据拷贝；
2. 多进程同时读写，存在竞态条件，**必须配合信号量同步**；
3. 生命周期：创建后持久存在，手动 shmctl 删除；进程断开映射不会销毁内存。

### 2. 核心 API

```c
1 #include <sys/shm.h>
2 // 创建或获取一个共享内存：成功返回共享内存ID，失败返回-1
3 int shmget(key_t key, size_t size, int flag);
4 // 连接共享内存到当前进程的地址空间：成功返回指向共享内存的指针，失败返回-1
5 void *shmat(int shm_id, const void *addr, int flag);
6 // 断开与共享内存的连接：成功返回0，失败返回-1
7 int shmdt(void *addr); 
8 // 控制共享内存的相关信息：成功返回0，失败返回-1
9 int shmctl(int shm_id, int cmd, struct shmid_ds *buf);

```

### 3. 代码示例

#### 写进程 shm_write.c

```c
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main()
{
    key_t key = ftok(".", 101);
    int shmid = shmget(key, 4096, IPC_CREAT|0664);
    char *p = (char *)shmat(shmid, NULL, 0);
    strcpy(p, "hello shared memory");
    shmdt(p);
    return 0;
}
```

#### 读进程 shm_read.c

```c
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
    key_t key = ftok(".", 101);
    int shmid = shmget(key, 4096, IPC_CREAT|0664);
    char *p = (char *)shmat(shmid, NULL, 0);
    printf("读到：%s\n", p);
    shmdt(p);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
```

### 4. 优缺点

- 优点：传输速度最快、大数据传输友好；
- 缺点：无自带同步机制，多进程读写需额外加锁。

------

## 5. 信号 Signal（新增内容，直接放在最后）

### 1. 核心特点

1. 异步通信，中断程序正常执行流；仅用于本机进程。
2. 非实时信号 (1~31) 不排队，容易丢失；实时信号 (34~64) 支持排队。
3. 只能传递信号编号，不能传输大量业务数据。
4. 常用于进程终止、Ctrl+C 中断、程序异常、定时器事件。

### 2. 核心 API

```c
#include <signal.h>
sighandler_t signal(int signum, sighandler_t handler);

int kill(pid_t pid, int sig);
//功能：向指定进程发送信号。
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);

```

### 3. 代码示例

```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sig_handler(int sig)
{
    printf("捕获到信号 %d，准备退出程序\n", sig);
}

int main()
{
    // 注册Ctrl+C信号处理函数
    signal(SIGINT, sig_handler);
    while (1)
    {
        sleep(1);
        printf("程序运行中...\n");
    }
    return 0;
}
```

```c
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>   // 补充头文件

// 三参数信号回调：配合SA_SIGINFO使用
void handler(int signum, siginfo_t *info, void *context)
{
    printf("get signum = %d\n", signum);
    if(context != NULL)
    {
        // 删除错误的 info->si_int
        // 正确读取sigqueue传递的附加数据
        printf("get data = %d\n", info->si_value.sival_int);
        // 额外拓展：打印发送信号的进程PID
        printf("sender pid = %d\n", info->si_pid);
    }
}

int main()
{
    struct sigaction act;

    // 指定三参数回调函数
    act.sa_sigaction = handler;
    act.sa_flags = SA_SIGINFO; // 开启附加信息功能
    sigemptyset(&act.sa_mask); // 清空阻塞掩码（必加）

    // 注册SIGUSR1信号处理函数
    sigaction(SIGUSR1, &act, NULL);

    printf("接收进程启动，pid=%d，等待SIGUSR1信号...\n", getpid());
    while(1)
    {
        pause(); // 阻塞休眠，收到信号才唤醒
    }
    return 0;
}
```

发送代码

```c
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        printf("用法：%s 信号号 目标PID\n", argv[0]);
        return -1;
    }
    int signum = atoi(argv[1]);
    pid_t pid = atoi(argv[2]);

    union sigval value;
    value.sival_int = 100; // 自定义传递数据

    int ret = sigqueue(pid, signum, value);
    if(ret == -1)
    {
        perror("sigqueue");
        return -1;
    }
    printf("信号发送完成，携带数据：%d\n", value.sival_int);
    return 0;
}
```

### 4. 优缺点

优点：响应极快（微秒级），实现简单；

缺点：数据携带能力极弱，普通信号容易丢失。

## 6. 信号量（Semaphore）

### 1. 核心定位

**不用于传输数据，只做进程同步 / 互斥**；常配合共享内存使用。

### 2. 核心特点

1. 本质计数器，PV 操作具备原子性；
2. 二值信号量（0/1）：互斥锁；通用信号量：资源计数；
3. 支持信号量数组（信号量集）；
4. 资源不自动释放，程序退出后残留，需手动删除。

### 3. 核心 API

```c
1 #include <sys/sem.h>
2 // 创建或获取一个信号量组：若成功返回信号量集ID，失败返回-1
3 int semget(key_t key, int num_sems, int sem_flags);
4 // 对信号量组进行操作，改变信号量的值：成功返回0，失败返回-1
5 int semop(int semid, struct sembuf semoparray[], size_t numops);  
6 // 控制信号量的相关信息
7 int semctl(int semid, int sem_num, int cmd, ...);


结构体
1 struct sembuf 
2 {
3     short sem_num; // 信号量组中对应的序号，0～sem_nums-1
4     short sem_op;  // 信号量值在一次操作中的改变量
5     short sem_flg; // IPC_NOWAIT, SEM_UNDO
6 }

```

### 4. 完整示例

```c
#include <stdio.h>
#include <sys/ipc.h>    // ftok、IPC键值头文件
#include <sys/sem.h>    // System V信号量核心API：semget semop semctl
#include <unistd.h>     // fork、sleep系统调用
#include <sys/wait.h>   // wait() 回收子进程
#include <stdlib.h>     // exit() 退出函数

/**
 * @brief 信号量P操作（申请资源，信号量数值-1）
 * @param semid 信号量集ID
 * 逻辑：信号量>0则减1直接返回；等于0时当前进程阻塞休眠，等待V操作唤醒
 */
void P(int semid)
{
    // sembuf结构体：单次信号量操作的配置
    struct sembuf op;
    op.sem_num = 0;    // 操作信号量集中第0个信号量（本程序只创建1个）
    op.sem_op  = -1;   // P操作：计数器减1
    op.sem_flg = 0;    // 标志位0：资源不足时阻塞；IPC_NOWAIT为不阻塞直接返回错误

    // 执行信号量操作，第三个参数1表示只操作1个信号量
    int ret = semop(semid, &op, 1);
    if (ret == -1)
    {
        perror("P操作 semop 失败");
        exit(EXIT_FAILURE); // 出错直接退出程序
    }
}

/**
 * @brief 信号量V操作（释放资源，信号量数值+1）
 * @param semid 信号量集ID
 * 逻辑：信号量数值+1；若有进程因该信号量阻塞，自动唤醒一个等待进程
 */
void V(int semid)
{
    struct sembuf op;
    op.sem_num = 0;    // 操作第0号信号量
    op.sem_op  = 1;    // V操作：计数器加1
    op.sem_flg = 0;    // 阻塞模式（此处无影响）

    int ret = semop(semid, &op, 1);
    if (ret == -1)
    {
        perror("V操作 semop 失败");
        exit(EXIT_FAILURE);
    }
}

int main()
{
    // 1. ftok：生成唯一IPC键值，用于多个进程打开同一个信号量集
    // 参数1：路径文件（当前目录.）；参数2：项目id(0~255)
    key_t key = ftok(".", 99);
    if (key == -1)
    {
        perror("ftok 创建key失败");
        return -1;
    }

    // 2. semget：创建/获取信号量集
    // key：IPC键；nsems：集合内信号量个数；IPC_CREAT不存在则创建，0664权限
    int semid = semget(key, 1, IPC_CREAT | 0664);
    if (semid == -1)
    {
        perror("semget 创建信号量集失败");
        return -1;
    }

    // 3. semctl SETVAL：初始化第0个信号量的数值为0
    // 初值设0：同步信号量，代表初始无资源，P操作会阻塞
    int init_ret = semctl(semid, 0, SETVAL, 0);
    if (init_ret == -1)
    {
        perror("semctl SETVAL 初始化失败");
        return -1;
    }

    // 4. 创建子进程
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork 创建子进程失败");
        return -1;
    }

    // 父进程分支：pid > 0，pid存放子进程PID
    if (pid > 0)
    {
        printf("【父进程】准备执行P操作，信号量初值为0，即将阻塞等待子进程V\n");
        P(semid); // 信号量=0，父进程阻塞，直到子进程调用V唤醒

        // 被唤醒后执行下面代码
        printf("【父进程运行】\n");

        // wait阻塞等待子进程完全结束，防止子进程成为僵尸进程
        wait(NULL);
        printf("【父进程】子进程已执行完毕，开始销毁信号量\n");

        // IPC_RMID：内核删除信号量集，释放内核资源
        int del_ret = semctl(semid, 0, IPC_RMID);
        if (del_ret == -1)
        {
            perror("semctl IPC_RMID 删除信号量失败");
        }
    }
    // 子进程分支：pid == 0
    else if (pid == 0)
    {
        sleep(1); // 延迟1秒，保证父进程先执行P并进入阻塞状态
        printf("【子进程运行】\n");
        V(semid); // 信号量+1，唤醒阻塞的父进程
        printf("【子进程】执行完V操作，唤醒父进程\n");

        _exit(0); // 子进程直接退出，不用走主函数后续销毁逻辑
    }

    return 0;
}
```

### 5. 优缺点

- 优点：可靠同步互斥、原子操作；
- 缺点：无法传递业务数据、API 复杂。

------

## 7、通用补充知识点

1. `ftok()`：根据文件 + 字符生成唯一 key，用于消息队列 / 信号量 / 共享内存标识；
2. System V IPC 资源程序退出不会自动释放，必须手动`IPC_RMID`删除；
3. 管道、FIFO 是字节流；消息队列自带消息边界；
4. 本机使用以上 6 种 IPC，跨主机只能使用 Socket
5. ipcm -m 查看共享内存    ipcrm -m +id号删除共享内存
6. kill -l 查看信号名字以及序号  man 7 signal
7. [进程间通信详解-CSDN博客](https://blog.csdn.net/wh_sjc/article/details/70283843)

# Linux 线程编程

------

## 1. 线程基础

### 1.1 什么是线程？

- 线程是进程内的“小工人”，一个进程可以有多个线程同时干活。
- 同一进程的线程**共享**内存、文件等资源，但各有自己的**栈空间和寄存器**。
- 好处：创建快、通信方便（直接访问共享变量）、充分利用多核 CPU。

### 1.2 线程 vs 进程

| 维度     | 进程                         | 线程                         |
| :------- | :--------------------------- | :--------------------------- |
| 内存     | 独立地址空间                 | 共享进程地址空间             |
| 创建开销 | 大（需复制整个进程信息）     | 小（只分配栈和寄存器）       |
| 通信     | 通过管道、共享内存等内核机制 | 直接读写共享变量             |
| 健壮性   | 一个进程崩溃不影响其他进程   | 一个线程崩溃可能导致进程终止 |

### 1.3 Linux 线程模型（NPTL）

- Linux 使用 **1:1 模型**：每个用户态线程对应一个内核轻量级进程（LWP）。
- 内核通过 `task_struct` 管理每个线程，每个线程有唯一的 `tid`。
- 编程时使用 `pthread` 库（POSIX 标准）。

------

## 2. 线程生命周期

**状态**：

- **就绪 / 运行**：可以运行或正在 CPU 上。
- **阻塞**：等待某个条件（如锁、I/O），暂时不运行。
- **终止**：线程函数执行完，但资源还没回收。
- **停止**：被 `SIGSTOP` 暂停，可用 `SIGCONT` 恢复。

**流转**：创建 → 就绪 → 运行 ⇄ 阻塞 → 终止

------

## 3. POSIX 线程 API

> 所有示例编译时需加 `-pthread`，例如：
>
> bash
>
> ```
> gcc -o myprogram myprogram.c -pthread
> ```

### 3.1 线程管理

#### 创建线程

```c
int pthread_create(
    pthread_t *thread,          // [输出] 保存新线程的 ID
    const pthread_attr_t *attr, // 线程属性，一般传 NULL 使用默认值
    void *(*start_routine)(void*), // 线程要执行的函数（返回 void*，接收一个 void* 参数）
    void *arg                   // 传给线程函数的参数，没有则传 NULL
);
// 返回值：成功返回 0，失败返回错误码（如 EAGAIN 系统资源不足）
```

#### 等待线程结束（回收资源）

```c
int pthread_join(
    pthread_t thread,   // 要等待的线程 ID
    void **retval       // [输出] 接收线程函数的返回值，不关心可传 NULL
);
// 返回值：成功返回 0，失败返回错误码
// 注意：只有未分离的线程才能被 join
```

#### 分离线程（自动回收）

```c
int pthread_detach(pthread_t thread);
// 将线程设置为分离状态，线程结束时系统自动回收其资源，无需 pthread_join
// 成功返回 0，失败返回错误码
```

#### 退出当前线程

```c
void pthread_exit(void *retval);
// 终止当前线程，retval 是返回给其他线程的状态（可被 pthread_join 获取）
// 注意：它不会关闭文件或清理进程，只是结束调用它的那个线程
```

#### 获取当前线程 ID

```c
pthread_t pthread_self(void);
// 返回调用线程自己的 ID
```

#### 基本示例

```c
#include <pthread.h>
#include <stdio.h>

// 线程函数，参数和返回值都是 void*
void* worker(void* arg) {
    printf("子线程 ID: %ld\n", pthread_self());
    return (void*)0;   // 返回退出状态
}

int main() {
    pthread_t tid;
    // 创建线程，传入 worker 函数，无参数
    pthread_create(&tid, NULL, worker, NULL);
    // 等待线程结束，不关心返回值
    pthread_join(tid, NULL);
    return 0;
}
```

#### 分离线程示例

```c
pthread_t tid;
pthread_attr_t attr;
pthread_attr_init(&attr);  // 初始化属性对象
pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);  // 设置分离状态
pthread_create(&tid, &attr, worker, NULL);  // 创建分离线程
pthread_attr_destroy(&attr);  // 销毁属性对象
// 不需要 pthread_join，线程结束后自动回收
```

### 3.2 线程属性（`pthread_attr_t`）

线程属性用于在创建线程前设置其行为（分离状态、栈大小、调度策略等）。

```c
int pthread_attr_init(pthread_attr_t *attr);
// 初始化一个线程属性对象，使用前必须调用
// 成功返回 0

int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);
// 设置分离状态：
//   PTHREAD_CREATE_JOINABLE（默认，需要 join）
//   PTHREAD_CREATE_DETACHED（自动回收）
// 成功返回 0

int pthread_attr_setschedpolicy(pthread_attr_t *attr, int policy);
// 设置调度策略：
//   SCHED_OTHER（默认，普通分时调度）
//   SCHED_FIFO（实时，先入先出）
//   SCHED_RR（实时，时间片轮转）
// 成功返回 0

int pthread_attr_setschedparam(pthread_attr_t *attr, const struct sched_param *param);
// 设置调度参数，主要是优先级
// struct sched_param { int sched_priority; };
// 对于 SCHED_FIFO/RR，优先级范围 1~99，数值越大优先级越高
// 成功返回 0

int pthread_attr_destroy(pthread_attr_t *attr);
// 销毁属性对象，释放资源
// 成功返回 0
```

------

## 4. 线程同步机制

多个线程同时修改共享数据会引起**竞态条件**，必须使用同步工具。

### 4.1 互斥锁（Mutex）

相当于一把“门锁”，同一时间只有一个线程能进门。

#### 函数原型（带注释）

```c
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
// 动态初始化互斥锁，attr 一般传 NULL
// 成功返回 0

// 静态初始化器（推荐用于全局锁）
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int pthread_mutex_lock(pthread_mutex_t *mutex);
// 加锁：如果锁已被别人持有，则阻塞等待直到锁可用
// 成功返回 0

int pthread_mutex_trylock(pthread_mutex_t *mutex);
// 尝试加锁：如果锁被占用，立即返回 EBUSY 而不是阻塞
// 成功获得锁返回 0，锁已被占用返回 EBUSY

int pthread_mutex_unlock(pthread_mutex_t *mutex);
// 解锁，唤醒可能等待该锁的线程
// 成功返回 0

int pthread_mutex_destroy(pthread_mutex_t *mutex);
// 销毁互斥锁（动态初始化的锁需手动销毁）
// 成功返回 0
```

#### 示例：保护计数器

```c
#include <pthread.h>
#include <stdio.h>

int counter = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;  // 静态初始化

void* inc(void* arg) {
    for (int i = 0; i < 100000; i++) {
        pthread_mutex_lock(&lock);    // 上锁
        counter++;                    // 临界区，只有拿到锁的线程才能执行
        pthread_mutex_unlock(&lock);  // 开锁
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, inc, NULL);
    pthread_create(&t2, NULL, inc, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("counter = %d\n", counter);  // 一定是 200000
    return 0;
}
```



### 4.2 条件变量（Condition Variable）

用于“等待某个条件成立”，比如“队列不空我才消费”。必须搭配互斥锁使用。

#### 函数原型（带注释）

```c
int pthread_cond_init(pthread_cond_t *cond, const pthread_condattr_t *attr);
// 初始化条件变量，attr 通常传 NULL
// 成功返回 0

// 静态初始化器
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
// 原子操作：先释放 mutex，然后阻塞等待条件变量被唤醒
// 被唤醒时，会在函数返回前重新获取 mutex
// 必须与一个互斥锁配合使用！
// 成功返回 0

int pthread_cond_signal(pthread_cond_t *cond);
// 唤醒至少一个正在等待该条件变量的线程
// 成功返回 0

int pthread_cond_broadcast(pthread_cond_t *cond);
// 唤醒所有正在等待该条件变量的线程
// 成功返回 0

int pthread_cond_destroy(pthread_cond_t *cond);
// 销毁条件变量
// 成功返回 0
```

#### 重要范式（必须用 while，避免虚假唤醒）

```c
// 等待端
pthread_mutex_lock(&mutex);
while (!condition) {                      // while 循环检查，不是 if！
    pthread_cond_wait(&cond, &mutex);    // 释放锁并等待
}
// 条件满足，执行操作...
pthread_mutex_unlock(&mutex);

// 通知端
pthread_mutex_lock(&mutex);
condition = 1;                            // 更新条件
pthread_cond_signal(&cond);               // 唤醒等待者
pthread_mutex_unlock(&mutex);
```

#### 完整示例：等待-通知

```c
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  cond  = PTHREAD_COND_INITIALIZER;
int done = 0;  // 条件

void* waiter(void* arg) {
    pthread_mutex_lock(&mutex);
    while (!done)  // 必须用 while 检查
        pthread_cond_wait(&cond, &mutex);
    printf("线程 %ld 收到通知\n", pthread_self());
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* notifier(void* arg) {
    sleep(1);
    pthread_mutex_lock(&mutex);
    done = 1;                        // 修改条件
    pthread_cond_signal(&cond);      // 发通知
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t wt, nt;
    pthread_create(&wt, NULL, waiter, NULL);
    pthread_create(&nt, NULL, notifier, NULL);
    pthread_join(wt, NULL);
    pthread_join(nt, NULL);
    return 0;
}
```

### 4.3 POSIX 信号量（Semaphore）

信号量是一个计数器，可控制同时访问某一资源的线程数量。

#### 函数原型（带注释）

```c
#include <semaphore.h>  // 头文件

int sem_init(
    sem_t *sem,            // 信号量变量
    int pshared,           // 0 表示线程间共享，非 0 表示进程间共享（通常用 0）
    unsigned int value     // 初始值，表示允许同时访问的资源数
);
// 成功返回 0，失败返回 -1

int sem_wait(sem_t *sem);
// P 操作：将信号量值减 1，如果值已是 0，则阻塞等待直到值 > 0
// 成功返回 0，失败返回 -1

int sem_post(sem_t *sem);
// V 操作：将信号量值加 1，如果有线程在等待，则唤醒其中一个
// 成功返回 0，失败返回 -1

int sem_destroy(sem_t *sem);
// 销毁信号量
// 成功返回 0，失败返回 -1
```



#### 示例：限制最多 2 个线程同时运行

```c
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

sem_t sem;  // 全局信号量

void* worker(void* arg) {
    sem_wait(&sem);   // 获取许可（计数器减1，若为0则等待）
    printf("线程 %ld 开始工作\n", pthread_self());
    sleep(1);
    printf("线程 %ld 完成工作\n", pthread_self());
    sem_post(&sem);   // 释放许可（计数器加1）
    return NULL;
}

int main() {
    sem_init(&sem, 0, 2);  // 0：线程间共享，2：最多2个线程同时运行
    pthread_t threads[5];
    for (int i = 0; i < 5; i++)
        pthread_create(&threads[i], NULL, worker, NULL);
    for (int i = 0; i < 5; i++)
        pthread_join(threads[i], NULL);
    sem_destroy(&sem);
    return 0;
}
```

### 4.4 屏障（Barrier）

让一组线程在某点互相等待，直到所有线程都到达，再一起继续。

#### 函数原型（带注释）

c

```
int pthread_barrier_init(
    pthread_barrier_t *barrier,            // 屏障变量
    const pthread_barrierattr_t *attr,     // 属性，一般传 NULL
    unsigned count                         // 需要等待的线程总数
);
// 成功返回 0

int pthread_barrier_wait(pthread_barrier_t *barrier);
// 调用线程到达屏障点，并阻塞，直到所有 count 个线程都调用了这个函数
// 最后一个到达的线程会返回 PTHREAD_BARRIER_SERIAL_THREAD（宏），其他线程返回 0
// 成功返回 0 或 PTHREAD_BARRIER_SERIAL_THREAD

int pthread_barrier_destroy(pthread_barrier_t *barrier);
// 销毁屏障
// 成功返回 0
```

#### 示例：3 个线程同时同步

```c
#include <pthread.h>
#include <stdio.h>

pthread_barrier_t barrier;

void* task(void* arg) {
    int id = *(int*)arg;
    printf("线程 %d 到达屏障\n", id);
    pthread_barrier_wait(&barrier);  // 等待其他线程
    printf("线程 %d 越过屏障\n", id);
    return NULL;
}

int main() {
    pthread_barrier_init(&barrier, NULL, 3);  // 等待 3 个线程
    pthread_t t[3];
    int ids[3] = {1, 2, 3};
    for (int i = 0; i < 3; i++)
        pthread_create(&t[i], NULL, task, &ids[i]);
    for (int i = 0; i < 3; i++)
        pthread_join(t[i], NULL);
    pthread_barrier_destroy(&barrier);
    return 0;
}
```

### 4.5 读写锁（补充，可选）

读写锁允许多个读者同时读，但写者独占。适合读多写少的场景。

```c
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);   // 读锁，多个读者可同时持锁
int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);   // 写锁，独占
int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);   // 解锁
```

------

## 5. 线程调度

控制线程的优先级和调度策略。

#### 设置调度策略和优先级

```c
int pthread_setschedparam(
    pthread_t thread,               // 目标线程 ID
    int policy,                     // 调度策略：SCHED_OTHER, SCHED_FIFO, SCHED_RR
    const struct sched_param *param // struct sched_param { int sched_priority; };
);
// 成功返回 0，失败返回错误码
```

示例：

```c
struct sched_param param;
param.sched_priority = 50;  // 实时优先级 1~99，普通用户需要特殊权限
pthread_setschedparam(pthread_self(), SCHED_FIFO, &param);
```

------

## 6. 最佳实践与常见陷阱

### 6.1 线程 vs 进程选择

- **选线程**：任务间需要频繁共享数据、轻量、响应快。
- **选进程**：需要强隔离、容错、跨机器扩展。

### 6.2 常见错误

1. **忘记初始化同步对象**：使用 `PTHREAD_MUTEX_INITIALIZER` 等静态初始化器最省心。
2. **死锁**：两个线程各持一把锁，又互相等对方的锁。解决：总是按相同顺序加锁。
3. **虚假唤醒**：`pthread_cond_wait` 返回不一定是因为有人发了 signal，必须用 `while` 重新检查条件。
4. **非线程安全函数**：如 `strtok`、`ctime`，应改用其 `_r` 结尾的可重入版本。

### 6.3 性能建议

- 临界区尽量短，只保护必要的代码。
- 大锁拆成多个小锁（如哈希表每个桶一把锁）。
- 简单计数用原子操作（`<stdatomic.h>`）代替互斥锁。
- 线程数量：CPU 密集型 ≈ CPU 核数，I/O 密集型可以多一些，但不要太多。

------

## 7. 调试工具

| 工具 / 命令                | 作用                                                         |
| :------------------------- | :----------------------------------------------------------- |
| `ps -T -p <pid>`           | 查看进程的所有线程 ID                                        |
| `top -H -p <pid>`          | 实时查看各线程 CPU、内存占用                                 |
| `gdb`                      | `info threads` 列出线程，`thread <num>` 切换，`thread apply all bt` 打印所有线程调用栈 |
| `valgrind --tool=helgrind` | 检测数据竞争和锁错误                                         |
| `gcc -fsanitize=thread`    | 编译时加入 ThreadSanitizer，运行时报告数据竞争               |

------

## 8. 完整示例：生产者-消费者

下面这个程序使用互斥锁和两个条件变量实现安全的有界缓冲区。

``` c
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define ITERATIONS  10

int buffer[BUFFER_SIZE];
int count = 0;   // 当前缓冲区中的产品数量
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  not_full  = PTHREAD_COND_INITIALIZER;  // 缓冲区不满
pthread_cond_t  not_empty = PTHREAD_COND_INITIALIZER;  // 缓冲区不空

void* producer(void* arg) {
    for (int i = 0; i < ITERATIONS; ++i) {
        pthread_mutex_lock(&mutex);
        // 如果缓冲区满，则等待“不满”的条件
        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&not_full, &mutex);
        }
        // 生产数据
        buffer[count++] = i;
        printf("生产者: 生产 %d (库存 %d)\n", i, count);
        // 唤醒可能正在等待“不空”的消费者
        pthread_cond_signal(&not_empty);
        pthread_mutex_unlock(&mutex);
        usleep(100000);  // 模拟生产耗时
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 0; i < ITERATIONS; ++i) {
        pthread_mutex_lock(&mutex);
        // 如果缓冲区空，则等待“不空”的条件
        while (count == 0) {
            pthread_cond_wait(&not_empty, &mutex);
        }
        // 消费数据
        int item = buffer[--count];
        printf("消费者: 消费 %d (库存 %d)\n", item, count);
        // 唤醒可能正在等待“不满”的生产者
        pthread_cond_signal(&not_full);
        pthread_mutex_unlock(&mutex);
        usleep(150000);  // 模拟消费耗时
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);
    return 0;
}
```

------

## 9. 总结

- Linux 线程基于 NPTL，每个线程在内核中有独立的 `task_struct`。
- 核心 API：`pthread_create`、`pthread_join`、互斥锁、条件变量、信号量、屏障。
- 同步三件套：**互斥锁**保护临界区，**条件变量**实现等待-通知，**信号量**控制并发数量。
- 编写健壮多线程程序的要点：检查返回值、`while` 防止虚假唤醒、固定锁顺序避免死锁、使用线程安全函数。
- 调试利器：`helgrind`、`ThreadSanitizer`。

# Linux 网络编程

------

## 一、TCP/UDP 对比

1. 连接特性

- TCP：面向连接，通信前建立连接（类比打电话拨号）
- UDP：无连接，发送数据前无需建立连接

1. 传输可靠性

- TCP：可靠服务，数据无差错、不丢失、不重复、按序到达
- UDP：尽力交付，不保证可靠传输

1. 数据处理单位

- TCP：面向字节流，无边界连续字节
- UDP：面向报文，每次发送独立完整报文

1. 拥塞控制

- TCP：拥有拥塞控制，网络拥堵自动降低发送速率
- UDP：无拥塞控制，适合 IP 电话、实时视频会议等实时业务

1. 通信模式

- TCP：仅支持点对点一对一通信
- UDP：支持一对一、一对多、多对一、多对多

1. 头部开销

- TCP 首部 20 字节；UDP 首部仅 8 字节

1. 通信信道

- TCP：全双工可靠信道；UDP：不可靠信道

## 二、端口号作用

1. 一台主机仅有一个 IP，但可同时运行 Web、FTP、Telnet 等多种服务；IP 仅定位主机，无法区分主机内不同进程。
2. **IP 地址 + 端口号** 唯一标识一台主机内的网络服务进程。
3. 端口是程序访问网络的通道，服务器使用固定知名端口：

- FTP TCP：21
- Telnet TCP：23
- TFTP UDP：69

## 三、字节序

### 1. 概念

字节序：多字节数字在内存存储、网络传输时高低字节的排列顺序。

### 2. 两种字节序

1. Little endian（小端）：低序字节存储在内存起始地址，x86 主机默认使用

2. Big endian（大端）：高序字节存储在内存起始地址

   规定：网络字节序统一为大端字节序

### 3. 字节序转换 API

头文件：`<netinet/in.h>`

```c
// 主机字节序 → 网络字节序
uint16_t htons(uint16_t host16bitvalue); // short(2字节)端口转换
uint32_t htonl(uint32_t host32bitvalue);  // long(4字节)IP转换

// 网络字节序 → 主机字节序
uint16_t ntohs(uint16_t net16bitvalue);
uint32_t ntohl(uint32_t net32bitvalue);
```

缩写含义：h=host 主机，n=net 网络，s=short，l=long

宏 `INADDR_ANY`：绑定本机所有网卡地址，操作系统自动获取本地 IP

## 四、IP 地址转换 API

头文件：`<arpa/inet.h>`

1. ```
   int inet_aton(const char* straddr,struct in_addr *addrp);
   ```

   功能：字符串格式 IP（如 "192.168.1.100"）转为网络二进制 IP，存入 in_addr 结构体

2. ```
   char* inet_ntoa(struct in_addr inaddr);
   ```

   功能：网络二进制 IP 转换为人类可读字符串 IP

## 五、Socket 服务器开发总流程（TCP）

1. socket () 创建套接字，指定通信协议
2. bind () 绑定本机 IP 与端口
3. listen () 开启监听，等待客户端连接
4. accept () 阻塞接收客户端连接，生成通信套接字
5. send () /recv () 客户端与服务端数据交互
6. close () 关闭套接字，释放资源

客户端流程：

1. socket () 创建套接字
2. connect () 主动连接服务器 IP 端口
3. send () /recv () 数据收发
4. close () 关闭套接字

通俗类比：

IP = 楼栋号，端口 = 房间号；服务器监听 = 开门等候访客；客户端 connect = 上门拜访。

## 六、全部核心函数原型、参数、详细用法

### 1. socket 创建套接字

```
#include <sys/socket.h>
int socket(int domain, int type, int protocol);
```

参数：

- domain：协议族

  AF_INET：IPv4；AF_INET6：IPv6；AF_UNIX：本地 Unix 域；AF_ROUTE 路由套接字；AF_KEY 密钥套接字

- type：套接字类型

  SOCK_STREAM：TCP 流式套接字，面向连接可靠传输

  SOCK_DGRAM：UDP 数据报套接字，无连接

  SOCK_RAW：原始套接字，直接操作底层 IP/ICMP

- protocol：协议编号，填 0 自动匹配 type 对应协议；也可手动指定 IPPROTO_TCP/IPPROTO_UDP

  返回值：成功返回套接字文件描述符，失败返回 - 1

### 2. bind 绑定 IP 端口

```
#include <sys/socket.h>
int bind(int sockfd,const struct sockaddr *addr,socklen_t addrlen);
```

参数：

- sockfd：socket 返回的套接字 fd

- addr：通用地址结构体指针，IPv4 使用 sockaddr_in 强制转换

- addrlen：地址结构体字节大小

  返回值：成功 0，失败 - 1

通用地址结构与 IPv4 专用结构：

```
// 通用结构体
struct sockaddr{
    unsigned short sa_family; //协议族
    char sa_data[14]; //存储IP+端口
};
// IPv4专用结构体（开发常用）
struct sockaddr_in{
    sa_family_t sin_family;    //协议族AF_INET
    in_port_t sin_port;        //端口，必须htons转网络序
    struct in_addr sin_addr;   //IP地址
    unsigned char sin_zero[8]; //内存对齐填充，无实际作用
};
struct in_addr{
    uint32_t s_addr; //网络字节序IP
};
```

### 3. listen 开启监听

```
#include <sys/socket.h>
int listen(int sockfd, int backlog);
```

参数：

- sockfd：bind 完成后的监听套接字

- backlog：连接等待队列最大长度，常用 128

  返回值：成功 0，失败 - 1

### 4. accept 接收客户端连接

```
#include <sys/socket.h>
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```

参数：

- sockfd：服务器监听套接字

- addr：输出参数，存储客户端 IP、端口信息

- addrlen：传入地址结构体长度，函数自动修改为客户端地址实际长度

  返回值：成功返回全新通信套接字 cfd（仅用于和当前客户端收发）；无连接时阻塞；失败返回 - 1

### 5. connect 客户端连接服务器

```
#include <sys/socket.h>
int connect(int sockfd,const struct sockaddr *addr,socklen_t addrlen);
```

参数：

- sockfd：客户端 socket fd

- addr：存储**服务器**IP、端口的地址结构

- addrlen：地址结构体大小

  返回值：连接成功 0，失败 - 1，errno 记录错误码

### 6. send TCP 发送数据

```
#include <sys/socket.h>
ssize_t send(int s,const void *msg,size_t len,int flags);
```

参数：

- s：accept 返回的已连接套接字 cfd

- msg：待发送数据缓冲区

- len：需要发送的数据长度

- flags：控制选项，日常使用填 0

  返回值：成功返回实际发送字节数，失败 - 1

### 7. recv TCP 接收数据

```
#include <sys/socket.h>
ssize_t recv(int s, void *buf, size_t len, int flags);
```

参数：

- s：已建立连接的套接字

- buf：接收数据缓冲区

- len：缓冲区最大容量

- flags：填 0

  返回值：大于 0：读到数据长度；等于 0：客户端正常断开；-1：读取错误

## 七、完整 TCP 服务端代码 server.c

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8888
#define BUF_LEN 1024

int main()
{
    //1. socket创建监听套接字
    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    if(lfd == -1)
    {
        perror("socket create fail");
        exit(EXIT_FAILURE);
    }

    //填充IPv4地址结构
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);        //端口转网络字节序
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); //监听本机所有IP
    memset(serv_addr.sin_zero, 0, sizeof(serv_addr.sin_zero));

    //2. bind绑定IP端口
    int ret = bind(lfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if(ret == -1)
    {
        perror("bind fail");
        close(lfd);
        exit(EXIT_FAILURE);
    }

    //3. listen开启监听
    ret = listen(lfd, 128);
    if(ret == -1)
    {
        perror("listen fail");
        close(lfd);
        exit(EXIT_FAILURE);
    }
    printf("TCP服务端启动，监听端口 %d\n", PORT);

    //循环等待客户端接入
    while(1)
    {
        struct sockaddr_in cli_addr;
        socklen_t cli_len = sizeof(cli_addr);
        //4. accept阻塞接收客户端连接
        int cfd = accept(lfd, (struct sockaddr*)&cli_addr, &cli_len);
        if(cfd == -1)
        {
            perror("accept fail");
            continue;
        }

        //打印客户端IP、端口（inet_ntoa、ntohs转换字节序）
        char cli_ip[32];
        strcpy(cli_ip, inet_ntoa(cli_addr.sin_addr));
        unsigned short cli_port = ntohs(cli_addr.sin_port);
        printf("新客户端接入：%s:%d\n", cli_ip, cli_port);

        //5. recv接收客户端数据
        char buf[BUF_LEN] = {0};
        ssize_t n = recv(cfd, buf, sizeof(buf), 0);
        if(n > 0)
        {
            printf("收到客户端消息：%s\n", buf);
            send(cfd, buf, n, 0);
            printf("消息已回发给客户端\n");
        }
        else if(n == 0)
        {
            printf("客户端断开连接\n");
        }
        else
        {
            perror("recv error");
        }

        close(cfd);
        printf("等待下一个客户端连接\n\n");
    }

    close(lfd);
    return 0;
}
```

## 八、完整 TCP 客户端代码 client.c

```c
50000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000020000000.
     #+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8888
#define BUF_LEN 1024

int main()
{
    //1. 创建客户端套接字
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    //填充服务器地址信息
    struct sockaddr_in ser_addr;
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(SERVER_PORT);
   
    1/00+/字符串IP转网络地址
    memset(ser_addr.sin_zero, 0, 8);

    //2. connect连接服务器
    int ret = connect(fd, (struct sockaddr*)&ser_addr, sizeof(ser_addr));
    if(ret == -1)
    {
        perror("connect fail");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("成功连接服务器 %s:%d\n", SERVER_IP, SERVER_PORT);

    //send发送数据
    char send_buf[BUF_LEN] = "Hello Linux Socket 网络编程测试";
    send(fd, send_buf, strlen(send_buf), 0);
    printf("客户端发送：%s\n", send_buf);

    //recv接收服务端回显
    char recv_buf[BUF_LEN] = {0};
    ssize_t n = recv(fd, recv_buf, BUF_LEN, 0);
    if(n > 0)
    {
        printf("服务器回显内容：%s\n", recv_buf);
    }

    close(fd);
    printf("客户端退出\n");
    return 0;
}
```

## 九、PPT 简易文字架构图

```
【客户端程序 client.c】
main()
├─ socket() → 创建客户端fd
├─ sockaddr_in 结构体填充服务器IP端口
│  └─ 工具：htons()、inet_aton()
├─ connect() 建立TCP连接
├─ send() 发送数据
├─ recv() 接收回显
└─ close() 释放fd

                ↓ TCP双向通信

【服务端程序 server.c】
main()
├─ socket() → 创建监听fd lfd
├─ sockaddr_in 绑定本机信息
│  └─ 工具：htons()、htonl(INADDR_ANY)
├─ bind() 绑定地址端口
├─ listen() 开启监听
├─ while(1) 循环处理客户端
│  ├─ accept() 阻塞等待，生成通信cfd
│  │  └─ 工具：inet_ntoa()、ntohs()打印客户端信息
│  ├─ recv() 接收客户端数据
│  ├─ send() 回发消息
│  └─ close(cfd) 关闭当前客户端通道
└─ close(lfd) 程序退出释放监听fd
```