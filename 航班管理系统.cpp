#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>			//��׼���롢���ͷ�ļ�
#include <string.h>			//�����ַ�����������ͷ�ļ�
#include <utility>  
#include"io.h"
#include <sys/stat.h>
#include "windows.h"
#include<conio.h>
#include <stdlib.h>			//����
#define MaxAirlines 1000	//������������ĺ�//������
#define MaxClients	10000	//���������û�
#define PRINT "%d\t\t%d\t\t%s\t\t%s\t\t����%d\t\t%d\t\t%d\n", array_Airline[index_airline].airlineNum, array_Airline[index_airline].airplaneNum, array_Airline[index_airline].departure, array_Airline[index_airline].destionation, array_Airline[index_airline].time, array_Airline[index_airline].totalTickets, remain(array_Airline[index_airline].remainTickets)		//�궨�������ʽ
#define PRINTCLIENT "%d\t\t%d\t\t%s\t\t%s\t\t����%d\t\t%s\t\t%d\t\t%s\n", array_Airline[index_airline].airlineNum, array_Airline[index_airline].airplaneNum, array_Airline[index_airline].departure, array_Airline[index_airline].destionation, array_Airline[index_airline].time, client.name, client.seatNum, client.tips

struct Airline {			//����ṹ��
	int airlineNum;			//�����
	int airplaneNum;		//�ɻ���
	char departure[10];		//�����ص�
	char destionation[10];	//Ŀ�ĵ�
	int time;				//����ʱ�䣨���ڼ���
	int totalTickets;		//��Ʊ��
	int remainTickets[1024];//ʣ��Ʊ��
} array_Airline[MaxAirlines];

struct Client {				//�û��Ľṹ��
	char name[10];			//�û���
	int airlineNum;			//�����
	int seatNum;			//��λ��
	char tips[50];			//��ʾ��Ϣ
} client;

int totalAirlines;			//ͳ���ܺ�������
int index_airline;			//��ѯ����ʹ�õ��±�
char manager[] = { "root" };
char password[] = { "root" };
Client clients[MaxClients];
void gotoxy(int x, int y)
{
	COORD xy = { 0,0 };
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	xy.X = x;
	xy.Y = y;
	SetConsoleCursorPosition(hout, xy);
}
void DrawRec(int X, int Y, int w, int h)
{
	int i, j;
	//����x,y
	gotoxy(X, Y);
	//�ϱ�--------------------��һ��
	printf("�� ");
	for (i = 0; i < w; i++)
	{
		printf("�� ");
	}
	printf("�� ");
	//���

	for (i = 0; i < h; i++)
	{
		gotoxy(X, Y + 1 + i);
		printf("�� ");
	}
	//�ұ�

	for (i = 0; i < h; i++)
	{
		gotoxy(X + 2 + w * 2, Y + 1 + i);
		printf("�� ");
	}
	//�±�
	gotoxy(X, Y + 1 + h);
	//�ϱ�--------------------
	printf("�� ");
	for (i = 0; i < w; i++)
	{
		printf("�� ");
	}
	printf("�� ");

}
void DrawList(int x, int y, int column, int line, int width, int hight)
{
	/*���Ʊ�� ��������Ϊ �󶥵����� ���� ����  �п� �и�*/
	//������
	//��һ��
	gotoxy(x, y);
	for (int i = 0; i < (width + 1) * column + 1; i++)  //��һ�� //  ÿС������ϽǺͿ��Ϊ��λ ���һ��ֹͣ
	{
		if (i == 0)
		{
			printf("�� ");			//ֵ��ע�� ���ﰴ��˵����ַ�Ӧ��ռ�����ַ�λ 
									//��ʵ����ֻռ��һ��  ���������Ʊ���������һ���ո�
									//��Ȼ��������� ���������Ʊ��ͬ�����
			continue;
		}
		if (i == (width + 1) * column)
		{
			printf("�� ");
			break;
		}
		if (i % (width + 1) == 0)
			printf("�� ");
		else
			printf("�� ");
	}
	//�м���
	for (int j = 0; j < line; j++)
	{
		if (j == 0)
			gotoxy(x, y + 2 * hight);
		else
			gotoxy(x, y + 2 * hight * j);
		for (int i = 0; i < (width + 1) * column + 1; i++)
		{
			if (i == 0)
			{
				printf("�� ");
				continue;
			}
			if (i == (width + 1) * column)
			{
				printf("�� ");
				break;
			}
			if (i % (width + 1) == 0)
				printf("�� ");
			else
				printf("�� ");
		}
	}
	//���һ��
	gotoxy(x, y + (hight + 1) * line);
	for (int i = 0; i < (width + 1) * column + 1; i++)
	{
		if (i == 0)
		{
			printf("�� ");
			continue;
		}
		if (i == (width + 1) * column)
		{
			printf("�� ");
			break;
		}
		if (i % (width + 1) == 0)
			printf("�� ");
		else
			printf("�� ");
	}
	//������
	for (int i = 0; i < line; i++)
		for (int j = 0; j <= column; j++)
		{
			if (i == 0)
				gotoxy(x + 2 * (width + 1) * j, y + i + 1);
			else
				gotoxy(x + 2 * (width + 1) * j, y + i * 2 + 1);
			printf("��");
		}
}
enum Color
{
	black, blue, green, lakeBlue, red, purple, yellow, white, gray,
	lightBlue, lightGreen, lightSimpleGreen, lightRed, lightPurple, lightYellow, brightWhite
};
void userLoginForm();		//��¼ȷ�����ҳ��
void managerLogin();		//����Ա���ȷ��
void managerForm();			//����Աҳ��
void userForm();			//�û�ҳ��
void showAirlineForm();		//��ʾ������Ϣҳ��
void addAirlineForm();		//���Ӻ�����Ϣҳ��
void updateAirlineForm();	//���º�����Ϣҳ��
void deleteAirlineForm();	//ɾ��������Ϣҳ��
void showUserInfoForm();	//��ʾ�����û���Ϣҳ��
void clientShowAirlineForm();//��ʾ������Ϣ
void selectClientInfo();	//��ʾ�û���Ϣҳ��
void bookingTicketsForm();	//��Ʊҳ��
void deleteClientForm();	//��Ʊҳ��
void printAirlineInfo();	//��ʾ������Ϣ����ʼʱ�򣬰�����ȡ�ļ�
void readInfoToArray();		//��������Ϣ���ļ��ж�ȡ��������
void addAirline();			//��Ӻ�����Ϣ
void outputAirlineInfo();	//�����������е���Ϣ���
void outputSingalAirlineInfo(int index); //�������һ��������Ϣ
void updateAirlineInfo();	//�޸ĺ�����Ϣ
int searchAirline(int id);			//��ѯ������Ϣ�������е�λ�ã�ʹ�ö��ַ�����
void printUpdateAirlineOptions();//��ʾ�����޸ĵĺ�����Ϣ
void changeAirlineInfo(int index);//�޸ĺ���������ļ���Ϣ��������Ϣ�޸�
void changeAirlineTickets(int index);//�޸ĺ�����Ϣ�е�ʣ��Ʊ��
void changeClientTickets(int index, int choose, int airline);//�޸ĺ�����Ϣ�е�ʣ��Ʊ��
void deleteAirline();		//ɾ��������Ϣ
void bookingTickets();		//�û���Ʊ
int remain(int* tickets);	//��ѯʣ��Ʊ��
int selectSeat(int index);	//ѡ��һ�ſ���Ϊ���ͻ�
void addUser();				//���û���Ϣ��������û���Ϣ
void outputClientInfo();	//��������û�����Ϣ
int getAllClientInfo(bool show);	//��ʾ���еĹ˿���Ϣ
void cancelTickets();		//ȡ����Ʊ
bool searchClient(char name[10], bool displayInvalid); //���û���Ϣ�в����û���Ϣ��client�ṹ���У�˳�����
bool deleteClient(int airlineId, int seatId);		//ɾ���ͻ���Ʊ
void setSeatNumZero(int airline, int seatId, int index); //���ö�Ӧ����ϢΪ0
void sortAirlineAsTimeUseBubble();	//����ʱ��˳��ʹ��ð�����򷨶Ժ�����Ϣ��������
void sortAirlineAsairlineNumUseInsert();	//���պ����ʹ�ò�������Ժ�����Ϣ��������
void setColor(unsigned short backColor = 0, unsigned short textColor = 7) {
	char command[9] = "color 07";		//Ĭ����ɫ	
	command[6] = '0' + backColor;		//��backColor������Ϊ�ַ��� 
	command[7] = '0' + textColor;		//��textColor������Ϊ�ַ��� 
	system(command);				//����ϵͳ���� 
}
int main() {
	setColor(3, 5);
	userLoginForm();
	return 0;
}


void userLoginForm() {
	printf("\n\n					  ��ӭʹ�ú��ն�Ʊϵͳ\n\n");
	printf("================================================================================================================\n");
	printf("				1.����Ա��¼               2.�û���¼\n");
	printf("				3.�˳�\n");
	printf("================================================================================================================\n");
	printf("��ѡ���¼��ʽ��");
	int choose;
	scanf("%d", &choose);
	switch (choose) {
	case 1:
		managerLogin();
		break;
	case 2:
		printAirlineInfo();
		system("cls");
		userForm();
		break;
	default:
		printf("��Чѡ��3���������ʼҳ��...\n");
		Sleep(2000);
		system("cls");
		userLoginForm();
		break;
	}
}

void managerLogin() {
	char name[10];
	char pass[10];
	printf("�������Ա��¼����");
	scanf("%s", name);
	printf("�������Ա���룺");
	int i;
	getchar();
	for (i = 0; i < 100; i++)
	{
		pass[i] = _getch();
		if (pass[i] != 13 && pass[i] != 8)
		{
			printf("*");
		}
		if (pass[i] == 8)
		{
			printf("\b");
			i--;
			printf(" ");
			printf("\b");
			i--;
		}
		if (pass[i] == 13)
		{
			break;
		}
	}
	pass[i] = '\0';
	if (strcmp(name, manager) || (strcmp(pass, password))) {
		printf("\n####�û������������####\n");
		printf("�������ת����¼����\n");
		Sleep(2000);
		system("cls");//����
		userLoginForm();
	}
	else {
		system("cls");//����
		printAirlineInfo();
		managerForm();
	}
}

void managerForm() {
	printf("						����Աҳ��\n\n");
	printf("================================================================================================================\n");
	printf("				1.�鿴������Ϣ               2.���Ӻ�����Ϣ\n");
	printf("				3.�޸ĺ�����Ϣ               4.�鿴�ͻ���Ϣ\n");
	printf("				5.ɾ��������Ϣ               6.�˳�\n");
	printf("================================================================================================================\n");
	printf("��ѡ���ܣ�");
	int choose;
	scanf("%d", &choose);
	switch (choose) {
	case 1:
		showAirlineForm();
		break;
	case 2:
		addAirlineForm();
		break;
	case 3:
		updateAirlineForm();
		break;
	case 4:
		showUserInfoForm();
		break;
	case 5:
		deleteAirlineForm();
	case 6:
		getchar();
		system("cls");
		userLoginForm();
		break;
	default:
		printf("����ѡ����Ч���������ת������Ա��ҳ��...\n");
		Sleep(2000);
		system("cls");
		managerForm();
	}
}

void showAirlineForm() {
	printf("================================================================================================================\n");
	printf("				1.�����˳��				 2.ʱ��˳��\n");
	printf("				3.����\n");
	printf("================================================================================================================\n");
	printf("��ѡ���ܣ�");
	int order;
	scanf("%d", &order);
	switch (order) {
	case 1:
		sortAirlineAsairlineNumUseInsert();
		break;
	case 2:
		sortAirlineAsTimeUseBubble();
		break;
	case 3:
		managerForm();
		break;
	default:
		printf("����ѡ����Ч���������ת������Ա��ҳ��...\n");
		Sleep(2000);
		system("cls");
		managerForm();
	}
	printf("\n\n");
	outputAirlineInfo();
	printf("\n\n");

	getchar();
	printf("�����������...");
	getchar();
	system("cls");
	managerForm();
}

void addAirlineForm() {
	printf("\n\n");
	addAirline();
	printAirlineInfo();//��Ӻ�����Ϣ֮����Ҫ���º�����Ϣ������
	getchar();
	printf("�����������...");
	getchar();
	system("cls");
	managerForm();
	printf("\n\n");
}

void updateAirlineForm() {
	sortAirlineAsairlineNumUseInsert();
	printf("\n\n");
	outputAirlineInfo();
	updateAirlineInfo();
	printAirlineInfo();
	getchar();
	printf("�����������...");
	getchar();
	system("cls");
	managerForm();
	printf("\n\n");
}

void deleteAirlineForm() {
	sortAirlineAsairlineNumUseInsert();
	printf("\n\n");
	outputAirlineInfo();
	deleteAirline();
	printAirlineInfo();
	getchar();
	printf("�����������...");
	getchar();
	system("cls");
	managerForm();
	printf("\n\n");
}

void showUserInfoForm() {
	printf("\n\n");
	printf("================================================================================================================\n");
	//outputClientInfo();
	getAllClientInfo(true);
	printf("================================================================================================================\n");
	printf("\n\n");

	getchar();
	printf("�����������...");
	getchar();
	system("cls");
	managerForm();

}

void userForm() {
	int choose;
	printf("						�˿�ҳ��\n\n");
	printf("================================================================================================================\n");
	printf("				1.�鿴������Ϣ               2.�鿴�Ѷ���Ʊ\n");
	printf("				3.��Ʊ                       4.��Ʊ\n");
	printf("				5.�˳�\n");
	printf("================================================================================================================\n");
	printf("��ѡ���ܣ�");
	scanf("%d", &choose);
	switch (choose) {
	case 1:
		clientShowAirlineForm();
		break;
	case 2:
		selectClientInfo();
		break;
	case 3:
		bookingTicketsForm();
		break;
	case 4:
		deleteClientForm();
		break;
	case 5:
		getchar();
		system("cls");
		userLoginForm();
		break;
	default:
		printf("����ѡ����Ч���������ת�˿͵�¼����...\n");
		Sleep(2000);
		system("cls");
		userForm();
	}

}

void clientShowAirlineForm() {
	printf("================================================================================================================\n");
	printf("				1.�����˳��				 2.ʱ��˳��\n");
	printf("				3.����\n");
	printf("================================================================================================================\n");
	printf("��ѡ���ܣ�");
	int order;
	scanf("%d", &order);
	switch (order) {
	case 1:
		sortAirlineAsairlineNumUseInsert();
		break;
	case 2:
		sortAirlineAsTimeUseBubble();
		break;
	default:
		printf("����ѡ����Ч���������ת�˿͵�¼����...\n");
		Sleep(2000);
		system("cls");
		userForm();
	}
	printf("\n\n");

	outputAirlineInfo();
	printf("\n\n");

	getchar();
	printf("�����������...");
	getchar();
	system("cls");
	userForm();
}

void selectClientInfo() {
	printf("\n\n");
	char name[10];
	printf("�����û�����");
	scanf("%s", &name);
	printf("��Ʊ��Ϣ���£�\n");
	searchClient(name, false);
	printf("\n\n");

	getchar();
	printf("�����������...");
	getchar();
	system("cls");
	userForm();
}

void bookingTicketsForm() {
	printf("\n\n");
	outputAirlineInfo();
	bookingTickets();
	printf("\n\n");

	getchar();
	printf("�����������...");
	getchar();
	system("cls");
	userForm();

}

void deleteClientForm() {
	printf("\n\n");
	cancelTickets();
	printf("\n\n");

	getchar();
	printf("�����������...");
	getchar();
	system("cls");
	userForm();
}

void printAirlineInfo() {
	FILE* read = fopen("./airline.txt", "r+");
	if (read == NULL) {
		printf("������ϢΪ��\n");
	}
	else {
		readInfoToArray();			//��ȡ�ļ����ݵ�������



	}
	fclose(read);
}

void outputAirlineInfo() {
	printf("�����\t\t�ɻ���\t\t������\t\tĿ�ĵ�\t\t���ʱ��\t��Ʊ����\tʣ��Ʊ��\n");		//��Ϣ����
	for (index_airline = 0; index_airline < totalAirlines; index_airline++) {
		printf(PRINT);
	}
}
void outputSingalAirlineInfo(int index) {
	printf("�����\t\t�ɻ���\t\t������\t\tĿ�ĵ�\t\t���ʱ��\t��Ʊ����\tʣ��Ʊ��\n");
	index_airline = index;
	printf(PRINT);
}

void readInfoToArray() {
	FILE* readToArray = fopen("./airline.txt", "r");

	totalAirlines = 0;
	while (!feof(readToArray)) {
		fread(&array_Airline[totalAirlines], sizeof(struct Airline), 1, readToArray);		//����ȡ����
		totalAirlines++;
	}
	fclose(readToArray);
	//printf("%d", totalAirlines);
	totalAirlines--;//Ϊʲô���һ
}

void addAirline() {
	int week;		//�������ʱ�䣬��һ�����죬��1��7��ʾ
	FILE* writeInfo = fopen("./airline.txt", "ab+");
	char end[10];
	do {
		printf("������������Ҫ���ӵĺ�����Ϣ(�Իس�������):  \n");
		printf("================================================================================================================\n");
		printf("�����: ");
		array_Airline[totalAirlines].airlineNum = totalAirlines;
		printf("%d\n", array_Airline[totalAirlines].airlineNum);
		printf("������ɻ���: ");
		scanf("%d", &array_Airline[totalAirlines].airplaneNum);
		printf("����������ص�: ");
		scanf("%s", &array_Airline[totalAirlines].departure);
		printf("������Ŀ�ĵ�: ");
		scanf("%s", &array_Airline[totalAirlines].destionation);
		printf("���������ʱ��(1-7): ");
		scanf("%d", &week);
		while (week < 1 || week > 7) {
			printf("������ȷʱ�䣬��һ�������� 1 �� 7 ��ʾ��");
			scanf("%d", &week);
		}
		array_Airline[totalAirlines].time = week;
		printf("��Ʊ����: ");
		scanf("%d", &array_Airline[totalAirlines].totalTickets);
		//ʣ��Ʊ��Ϊ��Ʊ����
		for (int i = 0; i < array_Airline[totalAirlines].totalTickets; i++) {
			//printf("%d", i);
			array_Airline[totalAirlines].remainTickets[i] = 0;
		}
		//д���ļ�
		fwrite(&array_Airline[totalAirlines], sizeof(struct Airline), 1, writeInfo);
		totalAirlines++;
		printf("������,�Ƿ�������?�����y��n�Իس�������:");
		scanf("%s", end);
	} while (!strcmp(end, "y"));
	fclose(writeInfo);
}

void updateAirlineInfo() {
	char chooseChangeAirline[2];
	bool changeClient = false;
	int id;
	do {
		printf("\n������Ҫ�޸ĵĺ���ĺ���ţ�");
		scanf("%d", &id);
		sortAirlineAsairlineNumUseInsert();
		int index = searchAirline(id);
		if (index == -1) {
			printf("����ĺ��಻����");
		}
		else {
			//������ϢֻҪ�޸ģ��˿���Ϣ���е���ʾ��Ϣ��Ҫ�޸ģ������б�Ҫ���û�����Ϣ��ӵ���ʱ������
			int week;	//��ʾ�޸ĵ��µ�ʱ�䣬��һ��������1��7��ʾ
			char choose[2];	//ѡ���Ƿ�����޸ĸ���������Ϣ
			do {
				changeClient = false;
				outputSingalAirlineInfo(index);
				//������Ҫ�޸���������ݻ�Ҫ�޸��ļ�������
				printf("\n");
				printUpdateAirlineOptions();
				printf("ѡ����Ҫ�޸ĵ�ѡ�");
				int option;
				scanf("%d", &option);
				if (option > 5) {
					printf("ѡ����Ч");
					break;
				}
				switch (option) {
				case 1:
					printf("�����µķɻ��ţ�");
					scanf("%d", &array_Airline[index].airplaneNum);
					break;
				case 2:
					changeClient = true;
					printf("�����µĳ����أ�");
					scanf("%s", &array_Airline[index].departure);
					break;
				case 3:
					changeClient = true;
					printf("�����µ�Ŀ�ĵأ�");
					scanf("%s", &array_Airline[index].destionation);
					break;
				case 4:
					printf("�����µ�ʱ�䣺");
					scanf("%d", &week);
					while (week < 1 || week > 7) {
						printf("������ȷʱ�䣬��һ�������� 1 �� 7 ��ʾ��");
						scanf("%d", &week);
					}
					array_Airline[index].time = week;
					break;
				case 5:
					break;
				default:
					printf("����ѡ����Ч\n");
					Sleep(1);
					break;
				}
				outputSingalAirlineInfo(index);
				printf("�Ƿ�����޸ĸ���������Ϣ(y/n)��");
				scanf("%s", choose);
			} while (!strcmp(choose, "y"));
			changeAirlineInfo(index);
		}
		if (changeClient) {
			changeClientTickets(0, 3, id);
			printf("����û���ʾ��Ϣ�Ѿ��޸�\n");
		}
		else {
			changeClientTickets(0, 2, id);
			printf("����û���ʾ��Ϣ�Ѿ��޸�\n");
		}
		printf("�Ƿ���Ҫ�޸���������(y/n)��");
		scanf("%s", chooseChangeAirline);
		//�����޸��û���Ϣ�ķ���
	} while (!strcmp(chooseChangeAirline, "y"));
}

int searchAirline(int id) {
	//�Ƚ�������Ϣ���պ���Ž��������ٲ���
	//���ַ�����
	int low = 0, high = totalAirlines, mid;
	while (low <= high) {
		mid = (low + high) / 2;
		if (id == array_Airline[mid].airlineNum) {
			return mid;
		}
		else if (id < array_Airline[mid].airlineNum) {
			high = mid - 1;
		}
		else {
			low = mid + 1;
		}
	}

	return -1; //û�в鵽
}

void changeAirlineInfo(int index) {
	FILE* change = fopen("airline.dat", "rb+");
	fseek(change, sizeof(struct Airline) * index, 0);
	fwrite(&array_Airline[index], sizeof(struct Airline), 1, change); //�޸��ļ�����
	fclose(change);
}
void printUpdateAirlineOptions() {
	printf("				�޸ĺ�����Ϣҳ��\n\n");
	printf("================================================================================================================\n");
	printf("             1.�ɻ���				2.������\n");
	printf("             3.Ŀ�ĵ�				4.ʱ��\n");
	printf("             5.�˳�\n");
	printf("================================================================================================================\n");
}

void deleteAirline() {
	printf("ѡ����Ҫɾ���ĺ���ĺ���ţ�");
	int airline;
	scanf("%d", &airline);
	if (searchAirline(airline) == -1) {
		printf("����ĺ������Ч");
	}
	else {
		char choose[2];
		printf("ȷ��Ҫɾ���˺�����Ϣ��(y/n):");
		scanf("%s", &choose);
		if (!strcmp(choose, "y")) {
			index_airline = airline;
			int total = array_Airline[airline].totalTickets - remain(array_Airline[airline].remainTickets);
			printf("������ %d ���˿��յ�Ӱ�죬���ٴ�ȷ��(y/n): ", total);
			scanf("%s", &choose);
			if (!strcmp(choose, "y")) {
				//����صĹ˿͵���Ϣȫ�ĳ���Ч
				changeClientTickets(0, 3, airline);
				//����д������Ϣ�ļ�
				FILE* reWrite = fopen("airline.dat", "w");
				for (int i = 0; i < totalAirlines; i++) {
					if (array_Airline[i].airlineNum != airline) {
						fwrite(&array_Airline[i], sizeof(struct Airline), 1, reWrite);
					}
				}
				fclose(reWrite);
				totalAirlines--;

				printAirlineInfo();
			}
			else {
				printf("ɾ�����������Ѿ�ȡ��\n");
			}
		}
		else {
			printf("ɾ�����������Ѿ�ȡ��\n");
		}
	}
}

void bookingTickets() {
	readInfoToArray();
	char choose[2];
	printf("�����û�����");
	scanf("%s", &client.name);
	printf("���뺽��ţ�");
	scanf("%d", &index_airline);
	if (searchAirline(index_airline) != -1) {
		client.airlineNum = index_airline;
		strcpy(client.tips, "��Ч");//���ַ����鸳ֵ��������������
		//��ѯ�ú���ʣ��Ʊ��
		outputSingalAirlineInfo(index_airline);
		if (remain(array_Airline[index_airline].remainTickets) > 0) {
			printf("����ϸ�鿴������Ϣ��ȷ��(y/n):");
			scanf("%s", choose);

			if (!strcmp(choose, "y")) {
				//��֤��λ�Ų�Ϊ0
				client.seatNum = selectSeat(index_airline);
				printf("лл��ѡ�񱾴κ���:\n");
				printf("�����\t\t�ɻ���\t\t������\t\tĿ�ĵ�\t\t���ʱ��\t�û���\t\t�û���λ��\t��ʾ\n");
				//�޸ĺ�����Ϣ��Ϳͻ���Ϣ��
				changeAirlineTickets(index_airline);
				printf(PRINTCLIENT);
				//����û���Ϣ��
				addUser();
			}
			else {
				printf("���ζ�Ʊ��ȡ��");
			}
		}
		else {
			printf("�ú����Ѿ�û��ʣ���Ʊ���˴ι�Ʊ�Զ�ȡ��");
		}

	}
	else {
		printf("�ú��಻���ڣ��˴ι�Ʊ�Զ�ȡ��");
	}
}

int remain(int* tickets) {
	int num = 0;
	for (int i = 0; i < array_Airline[index_airline].totalTickets; i++) {
		if (tickets[i] == 0) {
			num++;
		}
	}
	return num;
}

void changeAirlineTickets(int index) {
	FILE* change = fopen("./airline.txt", "rb+");
	fseek(change, sizeof(struct Airline) * index, 0);
	fwrite(&array_Airline[index], sizeof(struct Airline), 1, change);
	fclose(change);
}

int selectSeat(int index) {
	for (int i = 0; i < array_Airline[index].totalTickets; i++) {
		if (array_Airline[index].remainTickets[i] == 0) {
			array_Airline[index].remainTickets[i] = 1;
			return i + 1;
		}
	}
	return -1;
}

void addUser() {
	FILE* userFile = fopen("./customer.txt", "ab+");
	fwrite(&client, sizeof(client), 1, userFile);
	fclose(userFile);
}

void outputClientInfo() {
	FILE* readCustomer = fopen("./customer.txt", "r");
	if (readCustomer == NULL) {
		printf("�û���ϢΪ��\n");
	}
	else {
		printf("�����\t\t�ɻ���\t\t������\t\tĿ�ĵ�\t\t���ʱ��\t�û���\t�û���λ��\n");		//��Ϣ����
		fread(&client, sizeof(struct Client), 1, readCustomer);		//����ȡ����
		index_airline = client.airlineNum;
		while (!feof(readCustomer)) {
			printf(PRINTCLIENT);
			fread(&client, sizeof(struct Client), 1, readCustomer);		//����ȡ����
			index_airline = client.airlineNum;
		}
	}
	fclose(readCustomer);
}
int getAllClientInfo(bool show) {
	//�����е��û���Ϣ���������У����ݻ�Ʊ�Ƿ���Ч�ͺ���Ž�������
	//���ζ�ȡ�û���Ϣ����������Ч�Ļ�Ʊ���������͵�һ����Ч�Ļ�Ʊλ�ý���
	int firstValid = 1;	//��¼��һ����Ч��Ʊ��λ�ã�Ҳ����Ч��Ʊ������
	int index = 1;	//�±��1��ʼ�洢��0λ��Ϊ��������תվ
	FILE* readCustomer = fopen("./customer.txt", "r");
	if (readCustomer == NULL) {
		printf("�û���ϢΪ��\n");
	}
	else {
		if (show) {
			fread(&clients[index], sizeof(struct Client), 1, readCustomer);		//����ȡ����
			//�����ĵ�һ�������Ч���ý���������Ҫ�ѱ�ǵ�һ����Чλ����ֵ
			if (clients[index].seatNum == -1 || clients[index].seatNum == 0) {
				firstValid++;
			}
			index++;	
			while (!feof(readCustomer)) {
				fread(&clients[index], sizeof(struct Client), 1, readCustomer);		//����ȡ����

				if (clients[index].seatNum == -1 || (
					clients[index].seatNum == 0 && strlen(clients[index].name) > 1)) {
					if (index > firstValid) {
						clients[0] = clients[firstValid];
						clients[firstValid] = clients[index];
						clients[index] = clients[0];
					}
					firstValid++;
				}

				index++;
			}
			index -= 1;
	//����������Ϣ����������Ч�Ķ�Ʊ��Ϣ����Ч�Ķ�Ʊ��Ϣ�ֿ������򣬶�ʹ��ð��
			bool change;
			if (firstValid != 1) {
				for (int i = 1; i < firstValid; i++) {
					change = false;
					for (int j = 1; j < firstValid - i; j++) {
						if (clients[j].airlineNum > clients[j + 1].airlineNum) {
							clients[0] = clients[j];
							clients[j] = clients[j + 1];
							clients[j + 1] = clients[0];
							change = true;
						}
					}
					if (!change) {
						break;
					}
				}
			}

			for (int i = firstValid; i < index; i++) {
				change = false;
				for (int j = firstValid; j < index - i; j++) {
					if (clients[j].airlineNum > clients[j + 1].airlineNum) {
						clients[0] = clients[j];
						clients[j] = clients[j + 1];
						clients[j + 1] = clients[0];
						change = true;
					}
				}
				if (!change) {
					break;
				}
			}

			printf("�����\t\t�û���\t\t��λ��\t\t��ʾ\n");
			for (int i = 1; i < index; i++) {
				printf("%d\t\t%s\t\t%d\t\t%s\n", clients[i].airlineNum, clients[i].name, clients[i].seatNum, clients[i].tips);
			}
			fclose(readCustomer);
			return 0;
		}
		else {
			int clientIndex = 0;
			while (!feof(readCustomer)) {
				fread(&clients[clientIndex], sizeof(struct Client), 1, readCustomer);		//����ȡ����
				clientIndex++;
			}
			fclose(readCustomer);
			clientIndex--;
			return clientIndex;
		}
	}
}

void cancelTickets() {
	char name[10];
	int airlineId;
	int seatId;

	readInfoToArray();

	printf("�����û�����");
	scanf("%s", &name);
	if (!searchClient(name, false)) {
		printf(" %s %s\n", name, "û�ж�Ʊ��Ϣ");
	}
	else { //���ݺ���ź���λ��ȷ����λ��
		printf("���뺽��ţ���λ�ţ���ȷ����Ҫȡ���Ļ�Ʊ��\n");
		printf("����ţ�");
		scanf("%d", &airlineId);
		printf("��λ�ţ�");
		scanf("%d", &seatId);
		if (deleteClient(airlineId, seatId)) {
			printf("�Ѿ��ɹ�ɾ��\n");
		}
		else {
			printf("������Ϣ��ƥ�䣬ȡ����Ʊʧ��\n");
		}
	}
}

bool searchClient(char name[10], bool displayInvalid) {
	bool had = false;
	int index = 0;
	FILE* readCustomer = fopen("./customer.txt", "r");
	if (readCustomer == NULL) {
		printf("��ѯ��ϢΪ��\n");
		return false;
	}

	printf("�����\t\t�ɻ���\t\t������\t\tĿ�ĵ�\t\t���ʱ��\t�û���\t\t��λ��\t\t��ʾ\n");		//��Ϣ����
	fread(&client, sizeof(struct Client), 1, readCustomer);		//����ȡ����
	index_airline = client.airlineNum;
	while (!feof(readCustomer)) {
		if (!strcmp(name, client.name)) {
			if (displayInvalid) {
				printf(PRINTCLIENT);
				had = true;
			}
			else {
				if (client.seatNum != -1) {
					printf(PRINTCLIENT);
					had = true;
				}
				if (client.seatNum == 0) {//�޸Ĺ˿͵���λ��Ϊ-1���������û�������Ϣ
					client.seatNum = -1;
					changeClientTickets(index, 1, 0);
				}
			}
		}
		fread(&client, sizeof(struct Client), 1, readCustomer);		//����ȡ����
		index_airline = client.airlineNum;
		index++;
	}
	fclose(readCustomer);
	if (!had) {
		printf("��ѯ��ϢΪ��\n");
	}
	return had;
}

bool deleteClient(int airlineId, int seatId) {
	bool change = false;
	int index = 0;	//��¼�޸��û���Ϣ���ʱ����Ҫ��ת�����û��ṹ��
	FILE* readCustomer = fopen("./customer.txt", "r");
	fread(&client, sizeof(struct Client), 1, readCustomer);		//����ȡ����
	index_airline = client.airlineNum;
	while (!feof(readCustomer)) {
		if ((client.airlineNum == airlineId) && (client.seatNum == seatId)) {
			//�޸��û���Ϣ������λ��Ϊ-1
			client.seatNum = -1;
			strcpy(client.tips, "��Ʊ");
			//�޸ĺ�����е�remainTickets��Ӧ��λ��Ϊ0
			//��ʱ��Ҫ�޸ĵ��û��Ѿ���ȡ��client����
			setSeatNumZero(airlineId, seatId, index);

			change = true;
		}

		fread(&client, sizeof(struct Client), 1, readCustomer);		//����ȡ����
		index_airline = client.airlineNum;
		index++;
	}
	fclose(readCustomer);

	return change;
}

void setSeatNumZero(int airline, int seatId, int index) {
	array_Airline[airline].remainTickets[seatId - 1] = 0;
	changeAirlineTickets(airline);
	changeClientTickets(index, 1, 0);
}

void changeClientTickets(int index, int choose, int airline) {
	FILE* change = fopen("./customer.txt", "rb+");
	if (choose == 1) {
		fseek(change, sizeof(struct Client) * index, 0);
		//printf("%s, %d", client.name, client.seatNum);
		fwrite(&client, sizeof(struct Client), 1, change);
		fclose(change);
	}
	else {
		char tips[50];
		if (choose == 2) {//��Ҫ�޸��û�����ʾ��ϢΪ��������Ϣ���޸ģ���ע��ɻ��ź����ʱ��
			strcpy(tips, "������Ϣ���޸ģ���ע����а���");
			int total = getAllClientInfo(false);
			for (int i = 0; i < total; i++) {
				//��-1���жϣ�������Ա������ȡ����ʱ��Ϊ-1����Ϣ�ĳ�0Ҳû�����ˣ��������˿ͻ�����Ϣ
				if (clients[i].airlineNum == airline && clients[i].seatNum != -1) {
					strcpy(clients[i].tips, tips);
					fseek(change, sizeof(struct Client) * i, 0);
					fwrite(&clients[i], sizeof(struct Client), 1, change);
				}
			}
			fclose(change);
		}
		else if (choose == 3) {//��Ҫ�޸��û��ĺ�����ϢΪ����Ǹ���������޸ģ��˻�Ʊ���ϣ��Ѿ��˿�
			strcpy(tips, "��Ǹ���������޸ģ��˻�Ʊ���ϣ��Ѿ��˿�");
			int total = getAllClientInfo(false);
			for (int i = 0; i < total; i++) {
				if (clients[i].airlineNum == airline && clients[i].seatNum != -1) {
					strcpy(clients[i].tips, tips);
					clients[i].seatNum = 0;
					fseek(change, sizeof(struct Client) * i, 0);
					fwrite(&clients[i], sizeof(struct Client), 1, change);
				}
			}
			fclose(change);
		}

	}
}

void sortAirlineAsTimeUseBubble() {
	for (int i = totalAirlines; i >= 0; i--) {
		array_Airline[i] = array_Airline[i - 1];
	}

	bool change = true;
	for (int i = 1; i <= totalAirlines; i++) {
		change = false;
		for (int j = 1; j <= totalAirlines - i; j++) {
			if (array_Airline[j].time > array_Airline[j + 1].time) {
				array_Airline[0] = array_Airline[j];
				array_Airline[j] = array_Airline[j + 1];
				array_Airline[j + 1] = array_Airline[0];
				change = true;
			}
		}
		if (!change) {
			break;
		}
	}
	//�������д洢�����ݸ�ԭΪ��0��ʼ
	for (int i = 0; i < totalAirlines; i++) {
		array_Airline[i] = array_Airline[i + 1];
	}
}

void sortAirlineAsairlineNumUseInsert() {
	//ʹ��array_Airline[0]��Ϊ�����ڣ���Ҫ�������������һλ
	for (int i = totalAirlines; i >= 0; i--) {
		array_Airline[i] = array_Airline[i - 1];
	}
	int j;
	for (int i = 2; i <= totalAirlines; i++) {
		array_Airline[0] = array_Airline[i];
		j = i - 1;
		while (array_Airline[0].airlineNum < array_Airline[j].airlineNum) {
			array_Airline[j + 1] = array_Airline[j];
			j = j - 1;
		}
		array_Airline[j + 1] = array_Airline[0];
	}
	//�������д洢�����ݸ�ԭΪ��0��ʼ
	for (int i = 0; i < totalAirlines; i++) {
		array_Airline[i] = array_Airline[i + 1];
	}
}