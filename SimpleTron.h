#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>

//���� / �������
#define READ 10                  //��һ���ִ��ն˶���ָ�����ڴ浥Ԫ
#define WRITE 11                 //��ָ���ڴ浥Ԫ�е���д���ն�

//���� / �洢����
#define LOAD 20                  //��ָ���ڴ浥Ԫ�е��ּ��ص��ۼ���
#define STORE 21                 //���ۼ����е��ִ洢��ָ���ڴ浥Ԫ��

//��������
#define ADD 30                   //��ָ���ڴ浥Ԫ�е������ۼ����е�����ӣ�����������ۼ�����
#define SUBTRACT 31              //���ۼ����е�����ָ���ڴ浥Ԫ�е������������������ۼ�����
#define DEVIDE 32                //���ۼ����е��ֳ�ָ���ڴ浥Ԫ�е��֣�����������ۼ�����
#define MULTIPLY 33              //���ۼ����е�����ָ���ڴ浥Ԫ�е�����ˣ�����������ۼ�����

//����ת�Ʋ���
#define BRANCH 40				 //ת�Ƶ�ָ�����ڴ浥Ԫ
#define BRANCHNEG 41             //���ۼ���Ϊ����ת�Ƶ�ָ�����ڴ浥Ԫ
#define BRANCHZERO 42            //���ۼ���Ϊ0��ת�Ƶ�ָ�����ڴ浥Ԫ
#define HALT 43                  //ֹͣ����������������

struct CPU {
	int accumulator = +0000;                    //�ۼ���
	int structioncounter = 00;                //ָ�������
	int	structionregister = +0000;            //ָ��Ĵ���
	int	operationcode = 00;                     //������
	int operand = 00;                           //������

}Proccessor;

int memory[100], keyboard_exit = 0, file_error = 0;//�ڴ�Ķ��壬�Լ������־�Ķ���
FILE* fp_dump;//����ת�����ļ�ָ��
int Choose_Order_Sign();//ѡ��˵�����
void(*SetUp)();
void(*Computer_Dump)(int);
void SetUp1();//Keyboard����ĳ�ʼ������
void SetUp2();//File����ĳ�ʼ������
int Run();//�Ĵ�������SML���
void Computer_Dump1(int);//ѡ��Keyboard�����ת��
void Computer_Dump2(int);//ѡ��File�����ת��
void ReSetUP();//���ÿ�����н������ڴ����