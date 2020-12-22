#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>			//标准输入、输出头文件
#include <string.h>			//包含字符串函数处理头文件
#include <utility>  
#include"io.h"
#include <sys/stat.h>
#include "windows.h"
#include<conio.h>
#include <stdlib.h>			//清屏
#define MaxAirlines 1000	//允许输入的最多的航//班数量
#define MaxClients	10000	//允许最多的用户
#define PRINT "%d\t\t%d\t\t%s\t\t%s\t\t星期%d\t\t%d\t\t%d\n", array_Airline[index_airline].airlineNum, array_Airline[index_airline].airplaneNum, array_Airline[index_airline].departure, array_Airline[index_airline].destionation, array_Airline[index_airline].time, array_Airline[index_airline].totalTickets, remain(array_Airline[index_airline].remainTickets)		//宏定义输出格式
#define PRINTCLIENT "%d\t\t%d\t\t%s\t\t%s\t\t星期%d\t\t%s\t\t%d\t\t%s\n", array_Airline[index_airline].airlineNum, array_Airline[index_airline].airplaneNum, array_Airline[index_airline].departure, array_Airline[index_airline].destionation, array_Airline[index_airline].time, client.name, client.seatNum, client.tips

struct Airline {			//航班结构体
	int airlineNum;			//航班号
	int airplaneNum;		//飞机号
	char departure[10];		//出发地点
	char destionation[10];	//目的地
	int time;				//飞行时间（星期几）
	int totalTickets;		//总票数
	int remainTickets[1024];//剩余票数
} array_Airline[MaxAirlines];

struct Client {				//用户的结构体
	char name[10];			//用户名
	int airlineNum;			//航班号
	int seatNum;			//座位号
	char tips[50];			//提示信息
} client;

int totalAirlines;			//统计总航班数量
int index_airline;			//查询航班使用的下标
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
	//到达x,y
	gotoxy(X, Y);
	//上边--------------------第一排
	printf("┏ ");
	for (i = 0; i < w; i++)
	{
		printf("━ ");
	}
	printf("┓ ");
	//左边

	for (i = 0; i < h; i++)
	{
		gotoxy(X, Y + 1 + i);
		printf("┃ ");
	}
	//右边

	for (i = 0; i < h; i++)
	{
		gotoxy(X + 2 + w * 2, Y + 1 + i);
		printf("┃ ");
	}
	//下边
	gotoxy(X, Y + 1 + h);
	//上边--------------------
	printf("┗ ");
	for (i = 0; i < w; i++)
	{
		printf("━ ");
	}
	printf("┛ ");

}
void DrawList(int x, int y, int column, int line, int width, int hight)
{
	/*绘制表格 参数依次为 左顶点坐标 列数 行数  行宽 行高*/
	//画横线
	//第一排
	gotoxy(x, y);
	for (int i = 0; i < (width + 1) * column + 1; i++)  //第一排 //  每小格的左上角和宽度为单位 最后一个停止
	{
		if (i == 0)
		{
			printf("┏ ");			//值得注意 这里按理说这个字符应该占两个字符位 
									//但实际上只占了一个  所以我在制表符后面加了一个空格
									//不然会产生错误 下面所有制表符同样如此
			continue;
		}
		if (i == (width + 1) * column)
		{
			printf("┓ ");
			break;
		}
		if (i % (width + 1) == 0)
			printf("┳ ");
		else
			printf("━ ");
	}
	//中间排
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
				printf("┣ ");
				continue;
			}
			if (i == (width + 1) * column)
			{
				printf("┫ ");
				break;
			}
			if (i % (width + 1) == 0)
				printf("╋ ");
			else
				printf("━ ");
		}
	}
	//最后一排
	gotoxy(x, y + (hight + 1) * line);
	for (int i = 0; i < (width + 1) * column + 1; i++)
	{
		if (i == 0)
		{
			printf("┗ ");
			continue;
		}
		if (i == (width + 1) * column)
		{
			printf("┛ ");
			break;
		}
		if (i % (width + 1) == 0)
			printf("┻ ");
		else
			printf("━ ");
	}
	//画竖线
	for (int i = 0; i < line; i++)
		for (int j = 0; j <= column; j++)
		{
			if (i == 0)
				gotoxy(x + 2 * (width + 1) * j, y + i + 1);
			else
				gotoxy(x + 2 * (width + 1) * j, y + i * 2 + 1);
			printf("┃");
		}
}
enum Color
{
	black, blue, green, lakeBlue, red, purple, yellow, white, gray,
	lightBlue, lightGreen, lightSimpleGreen, lightRed, lightPurple, lightYellow, brightWhite
};
void userLoginForm();		//登录确定身份页面
void managerLogin();		//管理员身份确认
void managerForm();			//管理员页面
void userForm();			//用户页面
void showAirlineForm();		//显示航班信息页面
void addAirlineForm();		//增加航班信息页面
void updateAirlineForm();	//更新航班信息页面
void deleteAirlineForm();	//删除航班信息页面
void showUserInfoForm();	//显示所有用户信息页面
void clientShowAirlineForm();//显示航班信息
void selectClientInfo();	//显示用户信息页面
void bookingTicketsForm();	//订票页面
void deleteClientForm();	//退票页面
void printAirlineInfo();	//显示航班信息，开始时候，包含读取文件
void readInfoToArray();		//将航班信息从文件中读取到数组中
void addAirline();			//添加航班信息
void outputAirlineInfo();	//仅仅将数组中的信息输出
void outputSingalAirlineInfo(int index); //输出单独一条航班信息
void updateAirlineInfo();	//修改航线信息
int searchAirline(int id);			//查询航班信息在数组中的位置，使用二分法查找
void printUpdateAirlineOptions();//显示可以修改的航班信息
void changeAirlineInfo(int index);//修改航班数组和文件信息，逐条信息修改
void changeAirlineTickets(int index);//修改航班信息中的剩余票数
void changeClientTickets(int index, int choose, int airline);//修改航班信息中的剩余票数
void deleteAirline();		//删除航班信息
void bookingTickets();		//用户订票
int remain(int* tickets);	//查询剩余票数
int selectSeat(int index);	//选择一张空作为给客户
void addUser();				//在用户信息表中添加用户信息
void outputClientInfo();	//输出所有用户的信息
int getAllClientInfo(bool show);	//显示所有的顾客信息
void cancelTickets();		//取消机票
bool searchClient(char name[10], bool displayInvalid); //在用户信息中查找用户信息到client结构体中，顺序查找
bool deleteClient(int airlineId, int seatId);		//删除客户机票
void setSeatNumZero(int airline, int seatId, int index); //设置对应的信息为0
void sortAirlineAsTimeUseBubble();	//按照时间顺序使用冒泡排序法对航班信息进行排序
void sortAirlineAsairlineNumUseInsert();	//按照航班号使用插入排序对航班信息进行排序
void setColor(unsigned short backColor = 0, unsigned short textColor = 7) {
	char command[9] = "color 07";		//默认颜色	
	command[6] = '0' + backColor;		//将backColor变量改为字符型 
	command[7] = '0' + textColor;		//将textColor变量改为字符型 
	system(command);				//调用系统函数 
}
int main() {
	setColor(3, 5);
	userLoginForm();
	return 0;
}


void userLoginForm() {
	printf("\n\n					  欢迎使用航空订票系统\n\n");
	printf("================================================================================================================\n");
	printf("				1.管理员登录               2.用户登录\n");
	printf("				3.退出\n");
	printf("================================================================================================================\n");
	printf("请选择登录方式：");
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
		printf("无效选择，3秒后跳到初始页面...\n");
		Sleep(2000);
		system("cls");
		userLoginForm();
		break;
	}
}

void managerLogin() {
	char name[10];
	char pass[10];
	printf("输入管理员登录名：");
	scanf("%s", name);
	printf("输入管理员密码：");
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
		printf("\n####用户名或密码错误####\n");
		printf("两秒后跳转到登录界面\n");
		Sleep(2000);
		system("cls");//清屏
		userLoginForm();
	}
	else {
		system("cls");//清屏
		printAirlineInfo();
		managerForm();
	}
}

void managerForm() {
	printf("						管理员页面\n\n");
	printf("================================================================================================================\n");
	printf("				1.查看航班信息               2.增加航班信息\n");
	printf("				3.修改航班信息               4.查看客户信息\n");
	printf("				5.删除航班信息               6.退出\n");
	printf("================================================================================================================\n");
	printf("请选择功能：");
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
		printf("输入选项无效，两秒后跳转到管理员主页面...\n");
		Sleep(2000);
		system("cls");
		managerForm();
	}
}

void showAirlineForm() {
	printf("================================================================================================================\n");
	printf("				1.航班号顺序				 2.时间顺序\n");
	printf("				3.返回\n");
	printf("================================================================================================================\n");
	printf("请选择功能：");
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
		printf("输入选项无效，两秒后跳转到管理员主页面...\n");
		Sleep(2000);
		system("cls");
		managerForm();
	}
	printf("\n\n");
	outputAirlineInfo();
	printf("\n\n");

	getchar();
	printf("按任意键继续...");
	getchar();
	system("cls");
	managerForm();
}

void addAirlineForm() {
	printf("\n\n");
	addAirline();
	printAirlineInfo();//添加航班信息之后，需要更新航班信息的数组
	getchar();
	printf("按任意键继续...");
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
	printf("按任意键继续...");
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
	printf("按任意键继续...");
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
	printf("按任意键继续...");
	getchar();
	system("cls");
	managerForm();

}

void userForm() {
	int choose;
	printf("						顾客页面\n\n");
	printf("================================================================================================================\n");
	printf("				1.查看航班信息               2.查看已定机票\n");
	printf("				3.订票                       4.退票\n");
	printf("				5.退出\n");
	printf("================================================================================================================\n");
	printf("请选择功能：");
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
		printf("输入选项无效，两秒后跳转顾客登录界面...\n");
		Sleep(2000);
		system("cls");
		userForm();
	}

}

void clientShowAirlineForm() {
	printf("================================================================================================================\n");
	printf("				1.航班号顺序				 2.时间顺序\n");
	printf("				3.返回\n");
	printf("================================================================================================================\n");
	printf("请选择功能：");
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
		printf("输入选项无效，两秒后跳转顾客登录界面...\n");
		Sleep(2000);
		system("cls");
		userForm();
	}
	printf("\n\n");

	outputAirlineInfo();
	printf("\n\n");

	getchar();
	printf("按任意键继续...");
	getchar();
	system("cls");
	userForm();
}

void selectClientInfo() {
	printf("\n\n");
	char name[10];
	printf("输入用户名：");
	scanf("%s", &name);
	printf("订票信息如下：\n");
	searchClient(name, false);
	printf("\n\n");

	getchar();
	printf("按任意键继续...");
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
	printf("按任意键继续...");
	getchar();
	system("cls");
	userForm();

}

void deleteClientForm() {
	printf("\n\n");
	cancelTickets();
	printf("\n\n");

	getchar();
	printf("按任意键继续...");
	getchar();
	system("cls");
	userForm();
}

void printAirlineInfo() {
	FILE* read = fopen("./airline.txt", "r+");
	if (read == NULL) {
		printf("航班信息为空\n");
	}
	else {
		readInfoToArray();			//读取文件内容到数组中



	}
	fclose(read);
}

void outputAirlineInfo() {
	printf("航班号\t\t飞机号\t\t出发地\t\t目的地\t\t起飞时间\t机票总数\t剩余票数\n");		//信息标题
	for (index_airline = 0; index_airline < totalAirlines; index_airline++) {
		printf(PRINT);
	}
}
void outputSingalAirlineInfo(int index) {
	printf("航班号\t\t飞机号\t\t出发地\t\t目的地\t\t起飞时间\t机票总数\t剩余票数\n");
	index_airline = index;
	printf(PRINT);
}

void readInfoToArray() {
	FILE* readToArray = fopen("./airline.txt", "r");

	totalAirlines = 0;
	while (!feof(readToArray)) {
		fread(&array_Airline[totalAirlines], sizeof(struct Airline), 1, readToArray);		//逐块读取数据
		totalAirlines++;
	}
	fclose(readToArray);
	//printf("%d", totalAirlines);
	totalAirlines--;//为什么会多一
}

void addAirline() {
	int week;		//航班出行时间，周一到周天，用1到7表示
	FILE* writeInfo = fopen("./airline.txt", "ab+");
	char end[10];
	do {
		printf("请依次输入您要增加的航班信息(以回车键结束):  \n");
		printf("================================================================================================================\n");
		printf("航班号: ");
		array_Airline[totalAirlines].airlineNum = totalAirlines;
		printf("%d\n", array_Airline[totalAirlines].airlineNum);
		printf("请输入飞机号: ");
		scanf("%d", &array_Airline[totalAirlines].airplaneNum);
		printf("请输入出发地点: ");
		scanf("%s", &array_Airline[totalAirlines].departure);
		printf("请输入目的地: ");
		scanf("%s", &array_Airline[totalAirlines].destionation);
		printf("请输入出发时间(1-7): ");
		scanf("%d", &week);
		while (week < 1 || week > 7) {
			printf("输入正确时间，周一到周天用 1 到 7 表示：");
			scanf("%d", &week);
		}
		array_Airline[totalAirlines].time = week;
		printf("机票总数: ");
		scanf("%d", &array_Airline[totalAirlines].totalTickets);
		//剩余票数为机票总数
		for (int i = 0; i < array_Airline[totalAirlines].totalTickets; i++) {
			//printf("%d", i);
			array_Airline[totalAirlines].remainTickets[i] = 0;
		}
		//写入文件
		fwrite(&array_Airline[totalAirlines], sizeof(struct Airline), 1, writeInfo);
		totalAirlines++;
		printf("添加完毕,是否继续添加?请键入y或n以回车键结束:");
		scanf("%s", end);
	} while (!strcmp(end, "y"));
	fclose(writeInfo);
}

void updateAirlineInfo() {
	char chooseChangeAirline[2];
	bool changeClient = false;
	int id;
	do {
		printf("\n输入需要修改的航班的航班号：");
		scanf("%d", &id);
		sortAirlineAsairlineNumUseInsert();
		int index = searchAirline(id);
		if (index == -1) {
			printf("输入的航班不存在");
		}
		else {
			//航班信息只要修改，顾客信息表中的提示信息就要修改，所以有必要将用户的信息添加到临时数组中
			int week;	//表示修改的新的时间，周一到周天用1到7表示
			char choose[2];	//选择是否继续修改该条航班信息
			do {
				changeClient = false;
				outputSingalAirlineInfo(index);
				//不仅仅要修改数组的内容还要修改文件中内容
				printf("\n");
				printUpdateAirlineOptions();
				printf("选择需要修改的选项：");
				int option;
				scanf("%d", &option);
				if (option > 5) {
					printf("选项无效");
					break;
				}
				switch (option) {
				case 1:
					printf("输入新的飞机号：");
					scanf("%d", &array_Airline[index].airplaneNum);
					break;
				case 2:
					changeClient = true;
					printf("输入新的出发地：");
					scanf("%s", &array_Airline[index].departure);
					break;
				case 3:
					changeClient = true;
					printf("输入新的目的地：");
					scanf("%s", &array_Airline[index].destionation);
					break;
				case 4:
					printf("输入新的时间：");
					scanf("%d", &week);
					while (week < 1 || week > 7) {
						printf("输入正确时间，周一到周天用 1 到 7 表示：");
						scanf("%d", &week);
					}
					array_Airline[index].time = week;
					break;
				case 5:
					break;
				default:
					printf("输入选项无效\n");
					Sleep(1);
					break;
				}
				outputSingalAirlineInfo(index);
				printf("是否继续修改该条航线信息(y/n)：");
				scanf("%s", choose);
			} while (!strcmp(choose, "y"));
			changeAirlineInfo(index);
		}
		if (changeClient) {
			changeClientTickets(0, 3, id);
			printf("相关用户提示信息已经修改\n");
		}
		else {
			changeClientTickets(0, 2, id);
			printf("相关用户提示信息已经修改\n");
		}
		printf("是否需要修改其他航线(y/n)：");
		scanf("%s", chooseChangeAirline);
		//调用修改用户信息的方法
	} while (!strcmp(chooseChangeAirline, "y"));
}

int searchAirline(int id) {
	//先将航班信息按照航班号进行排序再查找
	//二分法查找
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

	return -1; //没有查到
}

void changeAirlineInfo(int index) {
	FILE* change = fopen("airline.dat", "rb+");
	fseek(change, sizeof(struct Airline) * index, 0);
	fwrite(&array_Airline[index], sizeof(struct Airline), 1, change); //修改文件内容
	fclose(change);
}
void printUpdateAirlineOptions() {
	printf("				修改航班信息页面\n\n");
	printf("================================================================================================================\n");
	printf("             1.飞机号				2.出发地\n");
	printf("             3.目的地				4.时间\n");
	printf("             5.退出\n");
	printf("================================================================================================================\n");
}

void deleteAirline() {
	printf("选择需要删除的航班的航班号：");
	int airline;
	scanf("%d", &airline);
	if (searchAirline(airline) == -1) {
		printf("输入的航班号无效");
	}
	else {
		char choose[2];
		printf("确认要删除此航班信息吗？(y/n):");
		scanf("%s", &choose);
		if (!strcmp(choose, "y")) {
			index_airline = airline;
			int total = array_Airline[airline].totalTickets - remain(array_Airline[airline].remainTickets);
			printf("将会有 %d 名顾客收到影响，请再次确认(y/n): ", total);
			scanf("%s", &choose);
			if (!strcmp(choose, "y")) {
				//将相关的顾客的信息全改成无效
				changeClientTickets(0, 3, airline);
				//重新写航班信息文件
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
				printf("删除航班命令已经取消\n");
			}
		}
		else {
			printf("删除航班命令已经取消\n");
		}
	}
}

void bookingTickets() {
	readInfoToArray();
	char choose[2];
	printf("输入用户名：");
	scanf("%s", &client.name);
	printf("输入航班号：");
	scanf("%d", &index_airline);
	if (searchAirline(index_airline) != -1) {
		client.airlineNum = index_airline;
		strcpy(client.tips, "有效");//给字符数组赋值。。。。。尴尬
		//查询该航班剩余票数
		outputSingalAirlineInfo(index_airline);
		if (remain(array_Airline[index_airline].remainTickets) > 0) {
			printf("请仔细查看航班信息再确认(y/n):");
			scanf("%s", choose);

			if (!strcmp(choose, "y")) {
				//保证座位号不为0
				client.seatNum = selectSeat(index_airline);
				printf("谢谢您选择本次航班:\n");
				printf("航班号\t\t飞机号\t\t出发地\t\t目的地\t\t起飞时间\t用户名\t\t用户座位号\t提示\n");
				//修改航班信息表和客户信息表
				changeAirlineTickets(index_airline);
				printf(PRINTCLIENT);
				//添加用户信息表
				addUser();
			}
			else {
				printf("本次订票已取消");
			}
		}
		else {
			printf("该航班已经没有剩余的票，此次购票自动取消");
		}

	}
	else {
		printf("该航班不存在，此次购票自动取消");
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
		printf("用户信息为空\n");
	}
	else {
		printf("航班号\t\t飞机号\t\t出发地\t\t目的地\t\t起飞时间\t用户名\t用户座位号\n");		//信息标题
		fread(&client, sizeof(struct Client), 1, readCustomer);		//逐块读取数据
		index_airline = client.airlineNum;
		while (!feof(readCustomer)) {
			printf(PRINTCLIENT);
			fread(&client, sizeof(struct Client), 1, readCustomer);		//逐块读取数据
			index_airline = client.airlineNum;
		}
	}
	fclose(readCustomer);
}
int getAllClientInfo(bool show) {
	//把所有的用户信息读到数组中，根据机票是否有效和航班号进行排序
	//依次读取用户信息，当读到无效的机票，就让他和第一个有效的机票位置交换
	int firstValid = 1;	//记录第一个有效机票的位置，也是无效机票的张数
	int index = 1;	//下表从1开始存储，0位作为交换的中转站
	FILE* readCustomer = fopen("./customer.txt", "r");
	if (readCustomer == NULL) {
		printf("用户信息为空\n");
	}
	else {
		if (show) {
			fread(&clients[index], sizeof(struct Client), 1, readCustomer);		//逐块读取数据
			//读到的第一个如果无效不用交换，但是要把标记第一个有效位的数值
			if (clients[index].seatNum == -1 || clients[index].seatNum == 0) {
				firstValid++;
			}
			index++;	
			while (!feof(readCustomer)) {
				fread(&clients[index], sizeof(struct Client), 1, readCustomer);		//逐块读取数据

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
	//将读到的信息进行排序，无效的订票信息和有效的订票信息分开来排序，都使用冒泡
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

			printf("航班号\t\t用户名\t\t座位号\t\t提示\n");
			for (int i = 1; i < index; i++) {
				printf("%d\t\t%s\t\t%d\t\t%s\n", clients[i].airlineNum, clients[i].name, clients[i].seatNum, clients[i].tips);
			}
			fclose(readCustomer);
			return 0;
		}
		else {
			int clientIndex = 0;
			while (!feof(readCustomer)) {
				fread(&clients[clientIndex], sizeof(struct Client), 1, readCustomer);		//逐块读取数据
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

	printf("输入用户名：");
	scanf("%s", &name);
	if (!searchClient(name, false)) {
		printf(" %s %s\n", name, "没有订票信息");
	}
	else { //根据航班号和座位号确定座位号
		printf("输入航班号，座位号，以确定需要取消的机票：\n");
		printf("航班号：");
		scanf("%d", &airlineId);
		printf("座位号：");
		scanf("%d", &seatId);
		if (deleteClient(airlineId, seatId)) {
			printf("已经成功删除\n");
		}
		else {
			printf("输入信息不匹配，取消机票失败\n");
		}
	}
}

bool searchClient(char name[10], bool displayInvalid) {
	bool had = false;
	int index = 0;
	FILE* readCustomer = fopen("./customer.txt", "r");
	if (readCustomer == NULL) {
		printf("查询信息为空\n");
		return false;
	}

	printf("航班号\t\t飞机号\t\t出发地\t\t目的地\t\t起飞时间\t用户名\t\t座位号\t\t提示\n");		//信息标题
	fread(&client, sizeof(struct Client), 1, readCustomer);		//逐块读取数据
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
				if (client.seatNum == 0) {//修改顾客的座位号为-1，并更新用户表中信息
					client.seatNum = -1;
					changeClientTickets(index, 1, 0);
				}
			}
		}
		fread(&client, sizeof(struct Client), 1, readCustomer);		//逐块读取数据
		index_airline = client.airlineNum;
		index++;
	}
	fclose(readCustomer);
	if (!had) {
		printf("查询信息为空\n");
	}
	return had;
}

bool deleteClient(int airlineId, int seatId) {
	bool change = false;
	int index = 0;	//记录修改用户信息表的时候需要跳转几个用户结构体
	FILE* readCustomer = fopen("./customer.txt", "r");
	fread(&client, sizeof(struct Client), 1, readCustomer);		//逐块读取数据
	index_airline = client.airlineNum;
	while (!feof(readCustomer)) {
		if ((client.airlineNum == airlineId) && (client.seatNum == seatId)) {
			//修改用户信息表中座位号为-1
			client.seatNum = -1;
			strcpy(client.tips, "退票");
			//修改航班表中的remainTickets对应的位置为0
			//此时需要修改的用户已经读取到client中了
			setSeatNumZero(airlineId, seatId, index);

			change = true;
		}

		fread(&client, sizeof(struct Client), 1, readCustomer);		//逐块读取数据
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
		if (choose == 2) {//需要修改用户的提示信息为，航班信息已修改，请注意飞机号和起飞时间
			strcpy(tips, "航班信息已修改，请注意出行安排");
			int total = getAllClientInfo(false);
			for (int i = 0; i < total; i++) {
				//有-1的判断：当管理员将航班取消的时候，为-1的信息改成0也没意义了，反倒给顾客混乱信息
				if (clients[i].airlineNum == airline && clients[i].seatNum != -1) {
					strcpy(clients[i].tips, tips);
					fseek(change, sizeof(struct Client) * i, 0);
					fwrite(&clients[i], sizeof(struct Client), 1, change);
				}
			}
			fclose(change);
		}
		else if (choose == 3) {//需要修改用户的航班信息为：抱歉，航线已修改，此机票作废，已经退款
			strcpy(tips, "抱歉，航线已修改，此机票作废，已经退款");
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
	//将数组中存储的数据复原为从0开始
	for (int i = 0; i < totalAirlines; i++) {
		array_Airline[i] = array_Airline[i + 1];
	}
}

void sortAirlineAsairlineNumUseInsert() {
	//使用array_Airline[0]作为监视哨，需要将数组整体后移一位
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
	//将数组中存储的数据复原为从0开始
	for (int i = 0; i < totalAirlines; i++) {
		array_Airline[i] = array_Airline[i + 1];
	}
}