# 12.进程间通信IPC

在第一篇博文中我们介绍过，进程间通信（IPC） 分为 PIPE（管道）、Socket（套接字） 和 XSI（System V）。XSI 又分为 msg（消息队列）、sem（信号量数组） 和 shm（共享内存）。

这些手段都是用于进程间通讯的，只有进程间通讯才需要借助第三方机制，线程之间的通讯是不需要借助第三方机制的，因为线程之间的地址空间是共享的。

管道分为命名管道（FIFO）和匿名管道（PIPE），无论是哪种管道，都是由内核帮你创建和维护的。

管道的特点：

1.管道是半双工的，即同一时间数据只能从一端流向另一端。试想，如果一个管道从两边同时输入和输出数据，那么管道里的数据就乱了。

2.管道的两端一端作为读端，一端作为写端。

3.管道具有自适应的特点，默认会适应速度比较慢的一方，管道被写满或读空时速度快的一方会自动阻塞。

 

pipe() 函数

```
1 pipe - create pipe
2 
3 #include <unistd.h>
4 
5 int pipe(int pipefd[2]);
```

 

pipe() 用于创建管道，pipefd 是一个数组，表示管道的两端文件描述符，**pipefd[0] 端作为读端，pipefd[1] 端作为写端**。

pipe() 产生的是匿名管道，在磁盘的任何位置上找不到这个管道文件，而且**匿名管道只能用于具有亲缘关系的进程之间通信**。

一般情况有亲缘关系的进程之间使用管道进行通信时，会把自己不用的一端文件描述符关闭。

下面是创建匿名管道在父子进程之间传送了一个字符串“Hello”的小栗子。



```
 1 #include <stdio.h>
 2 #include <stdlib.h>
 3 #include <unistd.h>
 4 
 5 #include <sys/types.h>
 6 #include <sys/wait.h>
 7 
 8 #define BUFSIZE        1024
 9 
10 int main()
11 {
12     int pd[2];
13     char buf[BUFSIZE];
14     pid_t pid;
15     int len;
16 
17     // 创建匿名管道
18     if(pipe(pd) < 0)
19     {
20         perror("pipe()");
21         exit(1);
22     }
23 
24     // 创建子进程
25     pid = fork();
26     if(pid < 0)
27     {
28         perror("fork()");
29         exit(1);
30     }
31     if(pid == 0) { // 子进程 读取管道数据
32         // 关闭写端
33         close(pd[1]);
34         // 从管道中读取数据，如果子进程比父进程先被调度会阻塞等待数据写入
35         len = read(pd[0],buf,BUFSIZE);
36         puts(buf);
37         /* 管道是 fork() 之前创建的，
38          * 父子进程里都有一份，
39          * 所以退出之前要确保管道两端都关闭
40          */
41         close(pd[0]);
42         exit(0);
43     } else { // 父进程 向管道写入数据
44         close(pd[0]);
45         write(pd[1],"Hello!",6);
46         close(pd[1]);
47         wait(NULL);
48         exit(0);
49     }
50 }
```



在上面的栗子中，父进程创建了一个匿名管道，在 pd[2] 数组中凑齐了读写双方，子进程同样继承了具有读写双方的数组 pd[2]。

父进程先关闭管道的读端然后向管道中写入数据，然后将用完的写端也关闭，等待子进程消亡并为其收尸。

子进程先关闭管道的写端然后读取父进程写入管道的字符串，把它打印到控制台之后再关闭用完的读端，然后退出。

这个程序在 fork() 之后如果是子进程先运行，那么会阻塞在 read() 阶段，等待父进程被调度并向管道中写入数据。

如果在 fork() 之后是父进程先运行，那么父进程会阻塞在 wait() 阶段等待子进程运行结束。

所以无论是谁先运行，只要没有出现异常运行的结果都是我们预期之内的。

 

mkfifo() 函数

```
1 mkfifo - make a FIFO special file (a named pipe)
2 
3 #include <sys/types.h>
4 #include <sys/stat.h>
5 
6 int mkfifo(const char *pathname, mode_t mode);
```

mkfifo() 函数用于创建命名管道，作用与匿名管道相同，不过可以在不同的进程之间使用，相当于对一个普通文件进行读写操作就可以了。

这个管道文件是任何有权限的进程都可以使用的，两端都像操作一个普通文件一样对它进行打开、读写、关闭动作就可以了，只要一端写入数据另一端就可以读出来。

但是最好一端只读一端只写，否则在实际项目中你很难保证拿出的不是脏数据（自己写进去数据的混合着另一端写进去的数据被其中一端读了出来），除非像下面那个栗子那样结构简单清晰。

参数列表：

　　pathname：管道文件的路径和文件名。

　　mode：创建管道文件的权限。还是老规矩，传入的 mode 值要与系统的 umask 值做运算：(mode & ~umask)

返回值：成功返回 0，失败返回 -1 并设置 errno。

我们看下面的栗子是如何使用命名管道通讯的：



```
 1 #include <stdio.h>
 2 #include <stdlib.h>
 3 #include <unistd.h>
 4 #include <fcntl.h>
 5 
 6 #include <sys/types.h>
 7 #include <sys/stat.h>
 8 
 9 #define PATHNAME    "/tmp/myfifo"
10 
11 int main (void)
12 {
13     pid_t pid;
14     int fd = -1;
15     char buf[BUFSIZ] = "";
16 
17     // 创建一个命名管道，大家可以用 ls -l 命令查看这个管道文件的属性
18     if (mkfifo(PATHNAME, 0644) < 0) {
19         perror("mkfifo()");
20         exit(1);
21     }
22 
23     fflush(NULL);
24     pid = fork();
25     if (pid < 0) {
26         perror("fork()");
27         exit(1);
28     }
29     if (!pid) { // parent
30         pid = fork();
31         if (pid < 0) {
32             perror("fork()");
33             exit(1);
34         }
35         if (!pid) { // parent
36             // 两个子进程都创建完之后父进程直接退出，使两个子进程不具有亲缘关系。
37             exit(0);
38         }
39         /* child 2 */
40         /* 像操作普通文件一样对这个管道进行 open()、read()、write()、close() */
41         fd = open(PATHNAME, O_RDWR);
42         if (fd < 0) {
43             perror("open()");
44             exit(1);
45         }
46         read(fd, buf, BUFSIZ);
47         printf("%s", buf);
48         write(fd, " World!", 8);
49         close(fd);
50         exit(0);
51     } else { // child 1
52         fd = open(PATHNAME, O_RDWR);
53         if (fd < 0) {
54             perror("open()");
55             exit(1);
56         }
57         write(fd, "Hello", 6);
58         sleep(1); // 刚写完管道不要马上读，等第二个进程读取完并且写入新数据之后再读。
59         read(fd, buf, BUFSIZ);
60         close(fd);
61         puts(buf);
62         // 肯定是这个进程最后退出，所以把管道文件删除，不然下次再创建的时候会报文件已存在的错误
63         remove(PATHNAME);
64         exit(0);
65     }
66 
67     return 0;
68 }
```



这段代码很简单，父进程首先在磁盘上创建一个命名管道文件，然后创建两个子进程后退出。每个子进程都对管道文件进行一次读和一次写的动作，然后子进程退出，整个过程就结束了。

第一个子进程在写完管道之后要先休眠，等待第二个子进程从管道的另一端把数据读入并写入新的数据，第一个子进程再醒来读出管道的内容。如果第一个子进程不休眠而是在写完之后马上读管道，很可能在它写完管道之后第二个子进程还没来得及调度，它自己就又把管道里的数据读出来了，这样不仅读出来的不是第二个子进程写入的数据，还会导致第二个子进程永远阻塞在 read() 阶段，因为管道中不会再有数据写入。

管道大家都会用了吗？看上去不是很难是吧，赶快自己动手写写试试吧。

 

协同进程

这一小节主要是说管道是半双工的，两个进程一个只能对它读，另一个只能对它写，否则会出现脏数据，也就是无法区分出读出来的数据是来自于自己的还是来自于另一个进程的。

如果想要实现双工，必须采用两个管道，一个进程对一个管道只读，对另一个管道只写。

明白了这个原理，相信大家可以利用上面的 pipe() 或 mkfifo() 函数利用两个半双工管道实现进程之间的全双工通讯。

栗子 LZ 就不写了，大家自己多动手练练吧，遇到问题可以贴到评论里与 LZ 讨论。

 

XSI IPC

XSI IPC 是 System V 规范里面的进程间通信手段，而不是 POSIX 标准的。关于 System V、POSIX 等等的前世今生大家可以自行 Google 一下，网上 balabalabala...... 一大堆什么都有，LZ 就不把那些东西放在这里了。

在学习 XSI IPC 之前，我们先来认识两条命令：

> ipcs 命令可以查看 XSI IPC 的使用情况。
>
> ipcrm 命令可以删除指定的 XSI IPC。

为什么要先介绍这两个命令呢？如果实验的过程中需要查看 IPC 是否建立成功，可以通过 ipcs 命令，如果实验出问题了，则可以使用 ipcrm 命令删除错误的 IPC。



```
>$ ipcs

------ Shared Memory Segments --------
key        shmid      owner      perms      bytes      nattch     status      
0x00000000 32769      usera      600        393216     2          dest         
0x00000000 65538      usera      600        393216     2          dest         
0x00000000 98307      usera      600        393216     2          dest         
0x00000000 131076     usera      600        393216     2          dest         
0x00000000 163845     usera      600        393216     2          dest         
0x00000000 196614     usera      600        393216     2          dest         
0x00000000 229383     usera      600        393216     2          dest         
0x00000000 262152     usera      600        393216     2          dest         
0x00000000 294921     usera      600        393216     2          dest         
0x00000000 327690     usera      600        393216     2          dest         
0x00000000 360459     usera      600        393216     2          dest         
0x00000000 393228     usera      600        393216     2          dest         
0x00000000 425997     usera      600        393216     2          dest         
0x00000000 458766     usera      600        393216     2          dest         
0x00000000 491535     usera      600        393216     2          dest         
0x00000000 524304     usera      600        393216     2          dest         
0x00000000 557073     usera      600        393216     2          dest         
0x00000000 589842     usera      600        393216     2          dest         
0x00000000 655380     usera      600        393216     2          dest         

------ Semaphore Arrays --------
key        semid      owner      perms      nsems     

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages  

>$
```



 

通过 ipcs 命令可以看出来，命令的输出结果分为三个部分，第一部分是系统中当前开辟的**共享内存（shm）**，第二部分是**信号量数组（sem）**，第三部分是**消息队列（msg）**。

可以看到，不论是哪一部分，都有一列叫做“key”，没错，使用 XSI IPC 通信的进程就是通过同一个 key 值操作同一个共享资源的。这个 key 是一个正整数，与文件描述符不同的是，生成一个新 key 值时它不采用当前可用数值中的最小值，而是类似生成进程 ID 的方式，key 值连续的加 1，直至达到一个整数的最大正值，然后再回转到 0 从头开始累加。

 

 

XSI 消息队列（msg）

消息队列可以让通信双方传送结构体数据，这样也提高了传送数据的灵活性。

既然是通讯，那么在通信之前就要先在通信双方约定通信协议，协议就是通信双方约定的数据交换格式。

从消息队列开始一直到 Socket，我们都会看到比较类似的程序架构，因为无论是消息队列还是 Socket，它们都需要约定通信协议，而且都是按照一定的步骤才能实现通讯。

消息队列在约定协议的时候，在我们自己定义的结构体里要强制添加一个 long mtype; 成员。这个成员的作用是用于区分多种消息类型中的不同类型的数据包，当只有一种类型的包时这个成员没什么用，但是也必须得带上。

 

既然是通讯，那么就要区分**主动端**（先发包的一方）和**被动端**（先收包的一方，先运行），它们运行的时机不同，作用不同，甚至调用的函数也不同，所以我们的后面的每个栗子几乎都要编译出 2 个不同的可执行程序来测试。

前面说了，学到这里操作基本上都是按部就班的了，所以 msg、sem 和 shm 都有一系列函数遵循下面的命名规则：

> xxx**get**() // 创建
>
> xxx**op**() // 相关操作
>
> xxx**ctl**() // 其它的控制或销毁

下面我们看看消息队列的创建函数：msgget()



```
1 msgget - get a System V message queue identifier
2 
3 #include <sys/types.h>
4 #include <sys/ipc.h>
5 #include <sys/msg.h>
6 
7 int msgget(key_t key, int msgflg);
```



msgget() 函数的作用是创建一个消息队列，消息队列是双工的，两边都可以读写。

参数列表：

　　key 相当于通信双方的街头暗号，拥有相同 key 的双方才可以通信。

　　key 值必须是唯一的，系统中有个 ftok() 函数可以用于获取 key，通过文件 inode 和 salt 进行 hash 运算来生成唯一的 key，只要两个进程使用相同的文件和 salt 就可以生成一样的 key 值了。

　　msgflg：特殊要求。无论有多少特殊要求，只要使用了 IPC_CREAT，就必须按位或一个权限，权限也不是你想指定多大就能多大的，还是老规矩，要用它 &= ~umask，这个我们前面提到过。

同一个消息队列只需要创建一次，所以谁先运行起来谁有责任创建消息队列，后运行起来的就不需要创建了。

同理，对于后启动的进程来说，消息队列不是它创建的，那么它也没有必要销毁了。

 

msgrcv() 函数和 msgsnd() 函数



```
 1 msgrcv, msgsnd - message operations
 2 
 3 #include <sys/types.h>
 4 #include <sys/ipc.h>
 5 #include <sys/msg.h>
 6 
 7 int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
 8 
 9 ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp,
10                int msgflg);
11 
12 /* msgp 成员的定义要类似 msgbuf 这个结构体，第一个成员必须是 long 类型的 mtype，并且必须是 > 0 的值 */
13 struct msgbuf {
14     long mtype;       /* 消息类型，必须 > 0 */
15     char mtext[1];    /* 消息数据字段 */
16 };
```



msgrcv() 函数从 msgid 这个消息队列中接收数据，并将接收到的数据放到 msgp 结构体中，这段空间有 msgz 个字节大小，msgz 的值要减掉强制的成员 mtype 的大小（sizeof(long)）。

msgtyp 是 msgp 结构体中的 mtype 成员，表示要接收哪种类型的消息。虽然 msg 是消息队列，但是它并不完全遵循队列的形式，可以让接收者挑消息接收。如果不挑消息可以填写 0，这样就按照队列中的消息顺序返回。

msfglg 是特殊要求位图，没有写0。

msgsnd() 函数向 msgid 这个消息队列发送 msgp 结构体数据，msgp 的大小是 msgsz，msgflg 是特殊要求，没有特殊要求可以写 0。 

 

msgctl() 函数



```
1 msgctl - message control operations
2 
3 #include <sys/types.h>
4 #include <sys/ipc.h>
5 #include <sys/msg.h>
6 
7 int msgctl(int msqid, int cmd, struct msqid_ds *buf);
```



msgctl() 函数是不是有点眼熟呢？没错，跟 iocrtl()、fcntl() 这种函数的用法很类似。通过 cmd 指定具体的命令，然后通过 buf 为 cmd 命令设定参数，当然有些命令是需要参数的，有些命令则不需要参数。

最长用的 cmd 就是 IPC_RMID，表示删除（结束）某个 IPC 通信，并且这个命令不需要 buf 参数，直接传入 NULL 即可。

buf 结构体里面的成员很多，由于 cmd 一般只有 IPC_RMID 比较常用，所以 LZ 就不把 buf 结构体拿出来挨个成员解释了，需要用到的童鞋自行查阅一下 man 手册吧，遇到了什么问题可以在评论中讨论。

 

看下面的小栗子，我们把上面讲到的几个消息队列的函数使用一遍，在两个进程之间实现简单的通讯。



```
  1 /* proto.h 定义双方都需要使用的数据或对象 */
  2 #ifndef PROTO_H__
  3 #define PROTO_H__
  4 
  5 #define NAMESIZE        32
  6 
  7 /* 通讯双方生成 key 值共同使用的文件 */
  8 #define KEYPATH            "/tmp/out"            
  9 /* 通讯双方生成 key 值共同使用的 salt 值 */
 10 #define KEYPROJ            'a'
 11 
 12 /* 消息类型，只要是大于 0 的合法整数即可 */
 13 #define MSGTYPE            10
 14 
 15 /* 通讯双方约定的协议 */
 16 struct msg_st
 17 {
 18     long mtype;
 19     char name[NAMESIZE];
 20     int math;
 21     int chinese;
 22 };
 23 
 24 
 25 #endif
 26 
 27 
 28 /******************** rcver.c 接收方 ********************/
 29 #include <stdio.h>
 30 #include <stdlib.h>
 31 #include <sys/types.h>
 32 #include <sys/ipc.h>
 33 #include <sys/msg.h>
 34 
 35 #include "proto.h"
 36 
 37 int main()
 38 {
 39     key_t key;
 40     int msgid;
 41     struct msg_st rbuf;
 42 
 43     // 通过 /tmp/out 文件和字符 'a' 生成唯一的 key，注意文件必须是真实存在的
 44     key = ftok(KEYPATH,KEYPROJ);
 45     if(key < 0)
 46     {
 47         perror("ftok()");
 48         exit(1);
 49     }
 50 
 51     // 接收端应该先启动，所以消息队列由接收端创建
 52     msgid = msgget(key,IPC_CREAT|0600);
 53     if(msgid < 0)
 54     {
 55         perror("msgget()");
 56         exit(1);
 57     }
 58 
 59     // 不停的接收消息
 60     while(1)
 61     {
 62         // 没有消息的时候会阻塞等待
 63         if(msgrcv(msgid,&rbuf,sizeof(rbuf)-sizeof(long),0,0) < 0)
 64         {
 65             perror("msgrcv");
 66             exit(1);
 67         }
 68 
 69         /* 用结构体中强制添加的成员判断消息类型，
 70          * 当然在这个例子中只有一种消息类型，所以不判断也可以。
 71          * 如果包含多种消息类型这里可以写一组 switch...case 结构
 72          */
 73         if(rbuf.mtype == MSGTYPE)
 74         {
 75             printf("Name = %s\n",rbuf.name);
 76             printf("Math = %d\n",rbuf.math);
 77             printf("Chinese = %d\n",rbuf.chinese);
 78         }
 79     }
 80 
 81     /* 谁创建谁销毁。
 82      * 当然这个程序是无法正常结束的，只能通过信号杀死。
 83      * 使用信号杀死之后大家可以用 ipcs 命令查看一下，消息队列应该是没有被销毁的，
 84      * 大家可以使用上面我们提到的 ipcrm 命令把它删掉。
 85      */
 86     msgctl(msgid,IPC_RMID,NULL);
 87 
 88     exit(0);
 89 }
 90 
 91 
 92 
 93 
 94 /******************** snder.c 发送方 ********************/
 95 #include <stdio.h>
 96 #include <stdlib.h>
 97 #include <sys/types.h>
 98 #include <sys/ipc.h>
 99 #include <sys/msg.h>
100 #include <string.h>
101 #include <unistd.h>
102 #include <time.h>
103 
104 #include "proto.h"
105 
106 
107 int main()
108 {
109     key_t key;
110     int msgid;
111     struct msg_st sbuf;
112 
113     // 设置随机数种子
114     srand(time(NULL));
115     // 用与接收方相同的文件和 salt 生成一样的key，这样才可以通讯
116     key = ftok(KEYPATH,KEYPROJ);
117     if(key < 0)
118     {
119         perror("ftok()");
120         exit(1);
121     }
122 
123     // 取得消息队列
124     msgid = msgget(key,0);
125     if(msgid < 0)
126     {
127         perror("msgget()");
128         exit(1);
129     }
130 
131     // 为要发送的结构体赋值
132     sbuf.mtype = MSGTYPE;    
133     strcpy(sbuf.name,"Alan");
134     sbuf.math = rand()%100;
135     sbuf.chinese = rand()%100;
136 
137     // 发送结构体
138     if(msgsnd(msgid,&sbuf,sizeof(sbuf)-sizeof(long),0) < 0)
139     {
140         perror("msgsnd()");
141         exit(1);
142     }
143 
144     puts("ok!");
145 
146     // 消息队列不是发送方创建的，所以发送方不用负责销毁
147 
148     exit(0);
149 }
```



 

这段程序的源文件有三个：proto.h、rcver.c 和 snder.c。

proto.h 中的 KEYPROJ （salt 值）用一个字符来替代整形数，为什么不直接写数字呢？因为宏定义是没有数据类型的，没有单位的数字是不靠谱的，而字符的 ASCII 码一定是一个 0-255 之间的整形数。

接收方要先运行，所以又接收方创建消息队列。发送方要使用相同的文件和 salt 生成于接收方相同的 key 值，这样它们才能使用同一个消息队列。

发送方生成一个结构体，用随机数为结构体中的两个成员赋值，分别模拟学生的数学和语文成绩，接收方在接收到数据之后把每个成员解析出来，并打印到控制台上。

可以看出来，发送方和接收方必须使用相同的结构体才能保证数据能够正常被解析，所以这个结构体就是我们上面所说的“协议”。既然是协议，我们就要把它定义在一个共用的结构体（proto.h）中，让发送方和接收方都引用这个头文件，这样就能保证它们可以使用相同的结构体通讯了。

 

信号量



```
1 semget - get a semaphore set identifier
2 
3 #include <sys/types.h>
4 #include <sys/ipc.h>
5 #include <sys/sem.h>
6 
7 int semget(key_t key, int nsems, int semflg);
```



 

semget() 函数用于创建信号量。

成功返回 sem  ID，失败返回 -1 并设置 errno。

参数列表：

　　key：具有亲缘关系的进程之间可以使用一个匿名的 key 值，key 使用宏 IPC_PRIVATE 即可。

　　nsems：表示你到底有多少个 sem。信号量实际上是一个计数器，所以如果设置为 1 可以用来模拟互斥量。

　　semflg：IPC_CREAT 表示创建 sem，同时需要按位或一个权限，如果是匿名 IPC 则无需指定这个宏，直接给权限就行了。

 

semctl()



```
1 semctl - semaphore control operations
2 
3 #include <sys/types.h>
4 #include <sys/ipc.h>
5 #include <sys/sem.h>
6 
7 int semctl(int semid, int semnum, int cmd, ...);
```



 

semctl() 函数用来控制或销毁信号量。

参数列表：

　　semnum：信号量素组下标；

　　cmd：可选的宏参见《APUE》第三版 P457。常用的有 IPC_RMID，表示从系统中删除该信号量集合。SETVAL 可以为第几个成员设置值。关于这两个宏的用法，我们在下面的栗子中会见到。

　　...：根据不同的命令设置不同的参数，所以后面的参数是变长的。

 

semop()



```
 1 semop - semaphore operations
 2 
 3 #include <sys/types.h>
 4 #include <sys/ipc.h>
 5 #include <sys/sem.h>
 6 
 7 int semop(int semid, struct sembuf *sops, unsigned nsops);
 8 
 9 
10 struct sembuf {
11     unsigned short sem_num; /* 对第几个资源（数组下标）操作 */
12     short sem_op; /* 取几个资源写负数几(不要写减等于)，归还几个资源就写正数几 */
13     short sem_flg; /* 特殊要求 */
14 };
```



 

这个函数就是让我们操作信号量的。由于多个信号量可以组成数组，所以我们又看到了熟悉的函数定义方式，一个参数作为数组的起始位置，另一个参数指定数组的长度。

参数列表：

　　sops：结构体数组起始位置；

　　nsops：结构体数组长度；

返回值：成功返回0，失败返回-1并设置 errno。

前面说过了，信号量实际上就是计数器，所以每次在使用资源之前，我们需要扣减信号量，当信号量被减到 0 时会阻塞等待。每次使用完成资源之后，需要归还信号量，也就是增加信号量的数值。

下面我们使用上面操作信号量的函数实现一个通过信号量实现互斥量的栗子。



```
  1 #include <stdio.h>
  2 #include <stdlib.h>
  3 #include <string.h>
  4 #include <unistd.h>
  5 #include <sys/wait.h>
  6 #include <sys/types.h>
  7 #include <sys/ipc.h>
  8 #include <sys/sem.h>
  9 #include <errno.h>
 10 
 11 #define PROCNUM        20    
 12 #define FNAME        "/tmp/out"
 13 #define BUFSIZE        1024
 14 
 15 // 多个函数都要使用这个信号量 ID，所以定义为全局变量
 16 static int semid;
 17 
 18 static void P(void)
 19 {
 20     struct sembuf op;
 21 
 22     op.sem_num = 0; // 只有一个资源，所以数组下标是 0
 23     op.sem_op = -1; // 取一个资源就减1
 24     op.sem_flg = 0; // 没有特殊要求
 25     while(semop(semid,&op,1) < 0)
 26     {
 27         // 出现假错就重试
 28         if(errno != EINTR && errno != EAGAIN)
 29         {
 30             perror("semop()");
 31             exit(1);
 32         }
 33     }
 34 
 35 }
 36 
 37 static void V(void)
 38 {
 39     struct sembuf op;
 40 
 41     op.sem_num = 0;
 42     op.sem_op = 1; // 归还一个资源
 43     op.sem_flg = 0;
 44     while(semop(semid,&op,1) < 0)
 45     {
 46         if(errno != EINTR && errno != EAGAIN)
 47         {
 48             perror("semop()");
 49             exit(1);
 50         }
 51     }
 52 }
 53 
 54 static void func_add()
 55 {
 56     FILE *fp;
 57     char buf[BUFSIZE];
 58 
 59     fp = fopen(FNAME,"r+");    
 60     if(fp == NULL)
 61     {
 62         perror("fopen()");
 63         exit(1);
 64     }
 65 
 66     // 先取得信号量在操作文件，取不到就阻塞等待，避免发生竞争
 67     P();
 68     fgets(buf,BUFSIZE,fp);
 69     rewind(fp);    
 70     sleep(1); // 调试用，为了放大竞争，更容易看出来互斥量发挥了作用
 71     fprintf(fp,"%d\n",atoi(buf)+1);
 72     fflush(fp);
 73     // 操作结束之后归还信号量，让其它进程可以取得信号量
 74     V();
 75     fclose(fp);
 76 
 77     return ;
 78 }
 79 
 80 int main()
 81 {
 82     int i;
 83     pid_t pid;
 84 
 85     // 在具有亲缘关系的进程之间使用，所以设置为 IPC_PRIVATE 即可。
 86     // 另外想要实现互斥量的效果，所以信号量数量设置为 1 个即可。
 87     semid = semget(IPC_PRIVATE,1,0600);
 88     if(semid < 0)
 89     {
 90         perror("semget()");
 91         exit(1);
 92     }
 93 
 94     // 将 union semun.val 的值设置为 1
 95     if(semctl(semid,0,SETVAL,1) < 0)
 96     {
 97         perror("semctl()");
 98         exit(1);
 99     }
100 
101 
102     // 创建 20 个子进程
103     for(i = 0 ; i < PROCNUM ; i++)
104     {
105         pid = fork();        
106         if(pid < 0)
107         {
108             perror("fork()");
109             exit(1);
110         }
111         if(pid == 0)    // child
112         {
113             func_add();
114             exit(0);
115         }
116     }
117 
118     for(i = 0 ; i < PROCNUM ; i++)
119         wait(NULL);
120 
121     // 销毁信号量
122     semctl(semid,0,IPC_RMID);
123 
124     exit(0);
125 }
```



 

大家还记得以前我们写的用 20 个进程同时向一个文件中写入累加的数值吗？还是这个程序，这次我们使用信号量来实现它们之间的互斥效果。

程序的结构跟以前的实现方式差不多，只不过锁的形式不一样了而已。代码中注释已经写得比较明白了，LZ 这就不做太多解释了。

 

 

共享存储

还记得之前在《高级 IO》部分的博文中我们利用 mmap() 函数实现过一个共享内存吗？

这次我们使用的是 XSI 的共享内存，比使用 mmap() 实现的共享内存稍微麻烦一点。不过不用担心，也一样很简单，不就是遵循上面说的那个命名规则的三个函数嘛，有了消息队列和信号量的铺垫，相信不用 LZ 讲大家也差不多能猜出来 shm 是个什么套路了。

没错，第一个函数就是 shmget()，我们来看一下它的函数原型：

```
1 shmget - allocates a shared memory segment
2 
3 #include <sys/ipc.h>
4 #include <sys/shm.h>
5 
6 int shmget(key_t key, size_t size, int shmflg);
```

 

参数列表：

　　key：共享内存的唯一标识，具有亲缘关系的进程之间使用共享内存可以使用 IPC_PRIVATE 宏代替。

　　size：是共享内存的大小。

　　shmflg：IPC_CREAT 表示创建 shm，同时需要按位或一个权限，如果是匿名 IPC 则无需指定这个宏，直接给权限就行了。

返回值：成功返回 shm ID；失败返回 -1，man 手册里没说是否设置 errno，这个需要大家根据自己的环境测试一下，或者查阅自己环境下的 man 手册。

 

shmat() 函数和 shmdt() 函数



```
1 shmat - shared memory operations
2 
3 #include <sys/types.h>
4 #include <sys/shm.h>
5 
6 void *shmat(int shmid, const void *shmaddr, int shmflg);78 int shmdt(const void *shmaddr);
```



 

虽然函数名叫做 shmat，根据上面说过的约定，用 man 手册查 shmop 也是可以查到这个命令的。

shmat() 函数使进程与共享内存关联起来。

shmat()函数中的 shmaddr 参数是共享内存的起始地址，传入 NULL 由内核帮我们寻找合适的地址，一般情况我们都是传入 NULL 值。

shmdt() 函数用于使进程分离共享内存，共享内存使用完毕之后需要用这个函数分离。分离不带表释放了这块空间，使用共享内存的双方依然要遵守“谁申请，谁释放”的原则，所以没有申请的一方是不需要释放的，但是双方都需要分离。

 

shmctl()

```
1 shmctl - shared memory control
2 
3 #include <sys/ipc.h>
4 #include <sys/shm.h>
5 
6 int shmctl(int shmid, int cmd, struct shmid_ds *buf);
```

 

与消息队列和信号量一样，这个函数用于控制或删除共享内存。

参数 LZ 就不做介绍了，只说一下如何删除共享内存吧。cmd 参数设置为 IPC_RMID 并且 buf 参数设置为 NULL 就可以删除共享内存了。

下面我们来看一个共享内存实现进程间通讯的栗子。



```
 1 #include <stdio.h>
 2 #include <stdlib.h>
 3 #include <sys/mman.h>
 4 #include <sys/types.h>
 5 #include <sys/stat.h>
 6 #include <unistd.h>
 7 #include <fcntl.h>
 8 #include <string.h>
 9 #include <sys/ipc.h>
10 #include <sys/shm.h>
11 #include <sys/wait.h>
12 
13 // 申请的共享内存大小，单位是字节
14 #define MEMSIZE        1024
15 
16 int main()
17 {
18     char *str;
19     pid_t pid;
20     int shmid;
21 
22     // 有亲缘关系的进程 key 参数可以使用 IPC_PRIVATE 宏，并且创建共享内存 shmflg 参数不需要使用 IPC_CREAT 宏
23     shmid = shmget(IPC_PRIVATE,MEMSIZE,0600);
24     if(shmid < 0)
25     {
26         perror("shmget()");
27         exit(1);
28     }
29 
30     pid = fork();
31     if(pid < 0)
32     {
33         perror("fork()");
34         exit(1);
35     }
36     if(pid == 0) // 子进程
37     {
38         // 关联共享内存
39         str = shmat(shmid,NULL,0);
40         if(str == (void *)-1)
41         {
42             perror("shmat()");
43             exit(1);
44         }
45         // 向共享内存写入数据
46         strcpy(str,"Hello!");
47         // 分离共享内存
48         shmdt(str);
49         // 无需释放共享内存
50         exit(0);
51     }
52     else // 父进程
53     {
54         // 等待子进程结束再运行，因为需要读取子进程写入共享内存的数据
55         wait(NULL);
56         // 关联共享内存
57         str = shmat(shmid,NULL,0);
58         if(str == (void *)-1)
59         {
60             perror("shmat()");
61             exit(1);
62         }
63         // 直接把共享内存中的数据打印出来
64         puts(str);
65         // 分离共享内存
66         shmdt(str);
67         // 释放共享内存
68         shmctl(shmid,IPC_RMID,NULL);
69         exit(0);
70     }
71 
72     exit(0);
73 }
```



 

最后父进程要在父子进程用完共享内存之后调用 shmctl() 使用 IPC_RMID 宏来回收资源，参数为 NULL。