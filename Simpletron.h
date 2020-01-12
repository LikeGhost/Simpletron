#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>

//输入 / 输出操作
#define READ 10                  //把一个字从终端读入指定的内存单元
#define WRITE 11                 //把指定内存单元中的字写入终端

//加载 / 存储操作
#define LOAD 20                  //把指定内存单元中的字加载到累加器
#define STORE 21                 //把累加器中的字存储在指定内存单元中

//算术运算
#define ADD 30                   //把指定内存单元中的字与累加器中的字相加，结果保存在累加器中
#define SUBTRACT 31              //把累加器中的字与指定内存单元中的字相减，结果保存在累加器中
#define DEVIDE 32                //把累加器中的字除指定内存单元中的字，结果保存在累加器中
#define MULTIPLY 33              //把累加器中的字与指定内存单元中的字相乘，结果保存在累加器中

//控制转移操作
#define BRANCH 40				 //转移到指定的内存单元
#define BRANCHNEG 41             //若累加器为负，转移到指定的内存单元
#define BRANCHZERO 42            //若累加器为0，转移到指定的内存单元
#define HALT 43                  //停止，即程序的任务完成

struct CPU {
	int accumulator = +0000;                    //累加器
	int structioncounter = 00;                //指令计数器
	int	structionregister = +0000;            //指令寄存器
	int	operationcode = 00;                     //操作码
	int operand = 00;                           //操作数

}Proccessor;

int memory[100], keyboard_exit = 0, file_error = 0;//内存的定义，以及错误标志的定义
FILE* fp_dump;//进行转储的文件指针
int Choose_Order_Sign();//选择菜单功能
void(*SetUp)();
void(*Computer_Dump)(int);
void SetUp1();//Keyboard载入的初始化载入
void SetUp2();//File载入的初始化载入
int Run();//寄存器运行SML语句
void Computer_Dump1(int);//选择Keyboard载入的转储
void Computer_Dump2(int);//选择File载入的转储
void ReSetUP();//清除每次运行结束的内存残留
