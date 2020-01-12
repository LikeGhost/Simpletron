#include"SimpleTron.h"

int main() {
	while (1) {
		int Order_Sign = Choose_Order_Sign();
		//����ѡ��˵����ܷ���ֵ����ʼ�������������Ĺ���
		if (Order_Sign == 1) {
			SetUp = &SetUp1;
			Computer_Dump = &Computer_Dump1;
		}
		else {
			fp_dump = fopen("Computer Dump.txt", "w+");
			SetUp = &SetUp2;
			Computer_Dump = &Computer_Dump2;
		}
		(*SetUp)();
		if (file_error) {
			(*Computer_Dump)(1);
		}
		else if (keyboard_exit) {
			(*Computer_Dump)(1);
		}
		else {
			for (int i = 1;; i++) {
				if (Run()) {
					(*Computer_Dump)(i);
					if (Order_Sign == 1) {
						system("pause");
						system("cls");
					}
					ReSetUP();
					break;
				}
				(*Computer_Dump)(i);
				if (Order_Sign == 1) {
					system("pause");
					system("cls");
				}
			}
		}
		if(Order_Sign != 1)
		fclose(fp_dump);
		printf("* Enter 'E' to end the program.\n");
		printf("* Enter other key to continue.\n");
		char ch = getchar();
		if(ch=='E'||ch=='e'){
			break;
		}
		system("cls");
	}
	return 0;
}

int Choose_Order_Sign() {
	
	printf("	Simpletron\n");
	printf("--------------------------\n");
	printf("    1.Keyboard loading.\n");
	printf("    2.File loading.\n");
	printf("--------------------------\n\n");
	Sleep(500);
	printf("* Please select the operation mode:");
	char order_sign[20],t;
	do {
		gets_s(order_sign);
		t = atoi(order_sign);
		if (t == 1 || t == 2)break;
	} while (printf("\n* Wrong selection.\n\n* Please select the right operation mode:"));
	printf("--------------------------\n");
	Sleep(500);
	system("cls");
	return t;
}

void SetUp1() {
	printf("       Keyboard loading\n\n");
	Sleep(500);
	printf("* Enter 23333 to stop the loading.\n\n");
	printf("* Enter -99999 to exit the loading.\n\n");
	Sleep(500);
	printf("SML:\n\n");
	for (int adress = 0;; adress++) {
		int  order;
		char ch[20];
		printf("%02d  ", adress);
		gets_s(ch);
		while (1) {
			order = atoi(ch);//���õõ��ַ���������ת����������ʵ�ֶ�������������жϣ���ͬ
			int operationCode = order / 100;
			if (order == 0) {
				printf("* Please load the right SML.\n\n");
				printf("%02d  ", adress);
				gets_s(ch);
				continue;
			}
			else if (order == 23333) break;
			else if (order == -99999) {
				keyboard_exit = 1;
				return;
			}
			if(operationCode != 10 && operationCode != 11 && operationCode != 20 && operationCode != 21 && operationCode != 30 && operationCode != 31 && operationCode != 32 && operationCode != 33 && operationCode != 40 && operationCode != 41 && operationCode != 42 && operationCode != 43){
				printf("* Please load the right SML.\n\n");
				printf("%02d  ", adress);
				gets_s(ch);
			}
			else {
				break;
			}
		} 
		if (order == 23333) {
			break;
		}
		memory[adress] = order;//����Ҫ���Ҳ�Ϊ����ָ����������ڴ棬��ͬ
	}
	printf("* Program loading complete, Program execution begins.\n");
	printf("--------------------------\n");
}

void SetUp2() {
	printf("       File loading\n\n");
	FILE* fp;
	char filename[30];
	printf("* Please enter the open filename:");
	gets_s(filename);
	while ((fp = fopen(filename, "r+")) == NULL) {
		printf("\n* Please enter the right filename:");
		gets_s(filename);
	}
	for (int i = 0;; i++) {
		int adress, order;
		if (fscanf(fp, "%d %d", &adress, &order) < 0) {
			break;
		}
		int operationCode = order / 100;
		if (operationCode != 10 && operationCode != 11 && operationCode != 20 && operationCode != 21 && operationCode != 30 && operationCode != 31 && operationCode != 32 && operationCode != 33 && operationCode != 40 && operationCode != 41 && operationCode != 42 && operationCode != 43) {
			printf("\n* There are something wrong in your loading file.\n\n");
			file_error = 1;
			return;//������Ҫ����ļ�����ֱ��������Ϊ����
		}
		memory[adress] = order;
	}
	fclose(fp);
	printf("\n* Program loading complete, Program execution begins.\n");
	printf("--------------------------\n");
}

int Run() {
	Proccessor.structionregister = memory[Proccessor.structioncounter];//�õ�ִ�����
	//�ֳ�ִ��ָ����ڴ�
	Proccessor.operationcode = Proccessor.structionregister / 100;
	Proccessor.operand = Proccessor.structionregister % 100;
	switch (Proccessor.operationcode)
	{
		//���� / �������
	case READ:                  //��һ���ִ��ն˶���ָ�����ڴ浥Ԫ
		printf("* Please enter the read number:");
		while (scanf("%d", &memory[Proccessor.operand])!=1) {
			printf("\n* Please enter the right number:");
			while (getchar() != '\n') {};
		}
		getchar();
		printf("\n\n");
		Proccessor.structioncounter++;
		break;
	case WRITE:                 //��ָ���ڴ浥Ԫ�е���д���ն�
		printf("* Write the number in memory %d:%d\n", Proccessor.operand, memory[Proccessor.operand]);
		printf("\n\n");
		Proccessor.structioncounter++;
		break;

		//���� / �洢����
	case LOAD:                  //��ָ���ڴ浥Ԫ�е��ּ��ص��ۼ���
		Proccessor.accumulator = memory[Proccessor.operand];
		Proccessor.structioncounter++;
		break;
	case STORE:                 //���ۼ����е��ִ洢��ָ���ڴ浥Ԫ��
		memory[Proccessor.operand] = Proccessor.accumulator;
		Proccessor.structioncounter++;
		break;

		//��������
	case ADD:                   //��ָ���ڴ浥Ԫ�е������ۼ����е�����ӣ�����������ۼ�����
		Proccessor.accumulator = Proccessor.accumulator + memory[Proccessor.operand];
		Proccessor.structioncounter++;
		break;
	case SUBTRACT:              //���ۼ����е�����ָ���ڴ浥Ԫ�е������������������ۼ�����
		Proccessor.accumulator = Proccessor.accumulator - memory[Proccessor.operand];
		Proccessor.structioncounter++;
		break;
	case DEVIDE:                //���ۼ����е��ֳ�ָ���ڴ浥Ԫ�е��֣�����������ۼ�����
		if (!memory[Proccessor.operand]) {
			printf("* ERROR!\n\n");
			printf("* The divisor cannot be ZERO\n\n.");
			return 1;
		}
		Proccessor.accumulator = Proccessor.accumulator / memory[Proccessor.operand];
		Proccessor.structioncounter++;
		break;
	case MULTIPLY:              //���ۼ����е�����ָ���ڴ浥Ԫ�е�����ˣ�����������ۼ�����
		Proccessor.accumulator = Proccessor.accumulator * memory[Proccessor.operand];
		Proccessor.structioncounter++;
		break;

		//����ת�Ʋ���
	case BRANCH:                //ת�Ƶ�ָ�����ڴ浥Ԫ
		Proccessor.structioncounter = Proccessor.operand;
		break;
	case BRANCHNEG:             //���ۼ���Ϊ����ת�Ƶ�ָ�����ڴ浥Ԫ
		if (Proccessor.accumulator < 0) {
			Proccessor.structioncounter = Proccessor.operand;
		}
		else {
			Proccessor.structioncounter++;
		}
		break;
	case BRANCHZERO:            //���ۼ���Ϊ0��ת�Ƶ�ָ�����ڴ浥Ԫ
		if (Proccessor.accumulator == 0) {
			Proccessor.structioncounter = Proccessor.operand;
		}
		else {
			Proccessor.structioncounter++;
		}
		break;
	case HALT:             //ֹͣ����������������
		return 1;
	}
	return 0;
}

void Computer_Dump1(int i) {

	printf("NO.%d��\n", i);
	printf("�Ĵ�����\n\n");
	printf("accumulator                 %10d\n", Proccessor.accumulator);
	printf("instructionCounter                  %02d\n", Proccessor.structioncounter);
	printf("instructionRegister              %+05d\n", Proccessor.structionregister);
	printf("operationCode                       %02d\n", Proccessor.operationcode);
	printf("operand                             %02d\n", Proccessor.operand);
	printf("\n�ڴ棺\n");
	printf("%8c", ' ');
	for (int k = 0; k < 10; k++) {
		printf("%8d", k);
	}
	printf("\n");
	for (int k = 0; k < 100; k++) {
		if (k % 10 == 0) printf("\n%8d", k);

		if (memory[k] == 0) {
			printf("%3c%+05d", ' ', 0);
		}
		else {
			printf("%8d", memory[k]);
		}
	}

	printf("\n\n");
	printf("--------------------------\n");
}

void Computer_Dump2(int i) {

	fprintf(fp_dump, "NO.%d��\n", i);
	fprintf(fp_dump, "�Ĵ�����\n\n");
	fprintf(fp_dump, "accumulator                 %10d\n", Proccessor.accumulator);
	fprintf(fp_dump, "instructionCounter                  %02d\n", Proccessor.structioncounter);
	fprintf(fp_dump, "instructionRegister              %+05d\n", Proccessor.structionregister);
	fprintf(fp_dump, "operationCode                       %02d\n", Proccessor.operationcode);
	fprintf(fp_dump, "operand                             %02d\n", Proccessor.operand);
	fprintf(fp_dump, "\n�ڴ棺\n");
	fprintf(fp_dump, "%8c", ' ');
	for (int k = 0; k < 10; k++) {
		fprintf(fp_dump, "%8d", k);
	}
	fprintf(fp_dump, "\n");
	for (int k = 0; k < 100; k++) {
		if (k % 10 == 0) fprintf(fp_dump, "\n%8d", k);

		if (memory[k] == 0) {
			fprintf(fp_dump, "%3c%+05d", ' ', 0);
		}
		else {
			fprintf(fp_dump, "%8d", memory[k]);
		}
	}

	fprintf(fp_dump, "\n\n");
	fprintf(fp_dump, "--------------------------\n");
}
void ReSetUP(){
	for (int i=0;i<100;i++) {
		memory[i] = 0;
	}
}