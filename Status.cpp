#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include"ComputerRoom.h"
#include"Status.h"

#include<iostream>
#include<fstream>
#include<string>
#include<queue>

using namespace std;

string Stat[3] = {"学生" , "教师" , "管理员"};

Administor::Administor(int Accout , string Name , int Stat)
{
	this->Accout = Accout;
	this->Name = Name;
	this->status = Stat;
}

Teacher::Teacher(int Accout , string Name , int Stat)
{
	this->Accout = Accout;
	this->Name = Name;
	this->status = Stat;
}

Student::Student(int Accout , string Name , int Stat)
{
	this->Accout = Accout;
	this->Name = Name;
	this->status = Stat;
}

void Status::EndP() const
{
	cout << "感谢使用\n";
	exit(0);
}

void Administor::AddAccount()
{
	int Choice;
	
	cout << "选择注册人\n";
	cout << "-------------------------\n";
	cout << "1  学生\n";
	cout << "2  教师\n";
	cout << "3  管理员\n";
	cout << "-------------------------\n";

	cin >> Choice;

	int Accout;
	string Password , Name;
	
Label:
	cout << "请输入账号(纯数字)\n";
	cin >> Accout;

	cout << "请输入密码\n";
	cin >> Password;

	cout << "请输入姓名\n";
	cin >> Name;
	
	cout << "账号为：" << Accout << endl << "密码为：" << Password << endl << "姓名是：" << Name << endl <<"身份是：" << Stat[Choice - 1] << endl;
	cout << "-----------\n1 正确\n2 错误\n-----------\n";
	
	int ch;
	cin >> ch;
	if (ch == 2) goto Label;
	else
	{
		system("cls");
		cout << "注册成功\n";
		ofstream fout("staffmessage.txt" , ios::app | ios::binary);
		fout << Accout <<" "<< Password <<" "<<Name<<" "<< Choice << " ";
		fout.close();
	}
}
void Status::SeekBook() const
{
	FILE* fp = fopen("Book.txt" , "r");

	char ch = fgetc(fp);
	if (ch == EOF)
	{
		cout << "没有任何预约\n";
		fclose(fp);
		return;
	}

	rewind(fp);

	int Accout , Number , Day , Period , IsAccepted;
	char Name[150];

	cout << "全部预约如下 \n\n";
	cout << "-----------------------------------------\n\n";

	string Per[2] = {"上午" , "下午"};
	string Acc[3] = {"还未审核" , "审核已通过" , "审核未通过"};
	while (!feof(fp))
	{
		fscanf(fp , "%d %s %d %d %d %d " , &Accout , Name , &Number , &Day , &Period , &IsAccepted);
		cout << "学号： " << Accout << " 姓名： " << Name << " 预定了： " << Number << " 号机房。 时间是：周" << Day << Per[Period - 1] << ", 状态是： " << Acc[IsAccepted] << endl;
	}
	cout << "\n-----------------------------------------\n";

	fclose(fp);
}

void Teacher::ReviewBook()
{
	FILE* fp = fopen("Book.txt" , "r");
	int Accout , Number , Day , Period , IsAccepted;
	char Name[150];
	int Choice;
	string Per[2] = {"上午" , "下午"};
	string Acc[3] = {"还未审核" , "审核已通过" , "审核未通过"};

	struct Booker
	{
		Booker(int Accout , char* Name , int Number , int Day , int Period , int IsAccepted)
		{
			this->Accout = Accout;
			this->Name = Name;
			this->Number = Number;
			this->Day = Day;
			this->Period = Period;
			this->IsAccepted = IsAccepted;
		}
		int Accout , Number , Day , Period , IsAccepted;
		char* Name;
	};
	queue<Booker>q;

	while (!feof(fp))
	{
		fscanf(fp , "%d %s %d %d %d %d " , &Accout , Name , &Number , &Day , &Period , &IsAccepted);
		if (IsAccepted) continue;
		cout << "学号： " << Accout << " 姓名： " << Name << " 预定了： " << Number << " 号机房。 时间是：周" << Day << Per[Period - 1] << ", 状态是： " << Acc[IsAccepted] << endl;

		cout << "是否同意\n1 是\n2 否\n";
		cin >> Choice;
		IsAccepted = Choice;
		
		cout << "操作完成\n";
		q.push(Booker(Accout , Name , Number , Day , Period , IsAccepted));
	}

	fclose(fp);
	extern ComputerRoom* crptr;

	while (!q.empty())
	{
		Booker x = q.front();
		q.pop();
		crptr->WriteBook(x.Accout , x.Name , x.Number , x.Day , x.Period , x.IsAccepted , 0);
	}
}

void Teacher::showMain() const
{
	cout << "-----------------------------------------------\n";
	cout << "-------------欢迎使用机房预约系统--------------\n";
	cout << "-------------1 查看所有预约--------------------\n";
	cout << "-------------2 开始审核预约--------------------\n";
	cout << "-------------3 注销账号登录--------------------\n";
	cout << "-----------------------------------------------\n";


	cout << "请输入你的选择\n";

	int choice;
	cin >> choice;

	extern Status* ptr;

	if (choice == 1) ptr->SeekBook();
	if (choice == 2) ptr->ReviewBook();
	else ptr->EndP();
}

void Student::Book()
{
	extern Status* ptr;
	ptr->SeekComp();
	
	cout << endl;

	extern ComputerRoom* crptr;
	int Number , Day , Period;

Label1:
	cout << "请输入预约的机房\n";
	cin >> Number;

Label2:
	cout << "请输入日期 周（1 - 5）\n";
	cin >> Day;

	if (Day < 1 || Day > 5)
	{
		cout << "输入错误 请重新输入\n";
		goto Label2;
	}

	int Count = 0;

	int flag = 0;
	for (vector<Computer*>::iterator i = crptr->Room.begin(); i != crptr->Room.end(); i ++ , Count ++)
		if ((*i)->Number == Number)
		{
			flag = 1;
			break;
		}
	if (!flag)
	{
		cout << "没有该机房\n";
		goto Label1;
	}

	if (crptr->Room[Count]->RemainM[Day] == 0 && crptr->Room[Count]->RemainA[Day] == 0)
	{
		cout << "当天已经没有机器了\n";
		goto Label2;
	}

	cout << "周 " << Day << "\n\n" << "上午剩余机器 " << crptr->Room[Count]->RemainM[Day] << "个\n下午剩余机器 "
		<< crptr->Room[Count]->RemainA[Day] << "个\n";

Label3:
	cout << "请输入预定时间\n1 上午\n2 下午\n";
	cin >> Period;

	if (Period == 1)
	{
		if (crptr->Room[Count]->RemainM[Day] == 0)
		{
			cout << "上午已经没有机器了\n";
			goto Label3;
		}
		cout << "你预定了上午\n";
		crptr->Room[Count]->RemainM[Day] -= 1;
	}
	if (Period == 2)
	{
		if (crptr->Room[Count]->RemainA[Day] == 0)
		{
			cout << "上午已经没有机器了\n";
			goto Label3;
		}
		cout << "你预定了下午\n";
		crptr->Room[Count]->RemainA[Day] -= 1;
	}

	crptr->Write();

	system("pause");
	system("cls");

	cout << "预约成功,请等待老师审核\n";
	char Name[50];

	strncpy(Name , this->Name.c_str() , this->Name.length());

	crptr->WriteBook(this->Accout , Name , Number , Day , Period , 0 , 1);
}

void Student::SeekSelfBook()
{
	FILE* fp = fopen("Book.txt" , "r");

	char ch = fgetc(fp);
	if (ch == EOF)
	{
		cout << "你没有任何预约\n";
		fclose(fp);
		return;
	}

	rewind(fp);

	int Accout , Number , Day , Period , IsAccepted;
	char Name[150];

	cout << "你的预约如下 \n\n";
	cout << "-----------------------------------------\n\n";

	string Per[2] = {"上午" , "下午"};
	string Acc[3] = {"还未审核" , "审核已通过" , "审核未通过"};
	while (!feof(fp))
	{
		fscanf(fp , "%d %s %d %d %d %d " , &Accout , Name , &Number , &Day , &Period , &IsAccepted);
		if (Accout != this->Accout) continue;
		cout << "学号： " << Accout << " 姓名： " << Name << " 预定了： " << Number << " 号机房。 时间是：周" << Day << Per[Period - 1] << ", 状态是： " << Acc[IsAccepted] << endl;
	}
	cout << "\n-----------------------------------------\n";

	fclose(fp);
}

void Student::CancelSelfBook()
{
	FILE* fp = fopen("Book.txt" , "r");

	char ch = fgetc(fp);
	if (ch == EOF)
	{
		cout << "你没有任何预约\n";
		fclose(fp);
		return;
	}

	rewind(fp);

	int Accout , Number , Day , Period , IsAccepted;
	char Name[150];
	int Choice;
	string Per[2] = {"上午" , "下午"};
	string Acc[3] = {"还未审核" , "审核已通过" , "审核未通过"};

	struct Booker
	{
		Booker(int Accout , char* Name , int Number , int Day , int Period , int IsAccepted)
		{
			this->Accout = Accout;
			this->Name = Name;
			this->Number = Number;
			this->Day = Day;
			this->Period = Period;
			this->IsAccepted = IsAccepted;
		}
		int Accout , Number , Day , Period , IsAccepted;
		char* Name;
	};
	queue<Booker>q;

	SeekSelfBook();

	int tot = 0;
	while (!feof(fp))
	{
		fscanf(fp , "%d %s %d %d %d %d " , &Accout , Name , &Number , &Day , &Period , &IsAccepted);
		if (this->Accout == Accout) tot ++;
		q.push(Booker(Accout , Name , Number , Day , Period , IsAccepted));
	}

	fclose(fp);

	ofstream fout("Book.txt" , ios::out);

Label:
	cout << "你有 " << tot << " 个预约\n想取消哪一个\n输入 0 不取消\n";

	cin >> Choice;

	if (Choice > tot || Choice < 0)
	{
		cout << "无效输入";
		goto Label;
	}

	while (!q.empty())
	{
		Booker x = q.front();
		q.pop();

		if (this->Accout == x.Accout) Choice --;
		if (Choice == 0)
		{
			Choice = -1;
			continue;
		}
		fout << x.Accout << " " << x.Name << " " << x.Number << " " << x.Day << " " << x.Period << " " << x.IsAccepted << " ";
	}

	cout << "删除成功\n\n";

	fout.close();
}

void Student::showMain() const
{
	cout << "-----------------------------------------------\n";
	cout << "-------------欢迎使用机房预约系统--------------\n";
	cout << "--------------1.进行机房预约-------------------\n";
	cout << "--------------2.查看我的预约-------------------\n";
	cout << "--------------3.查看所有预约-------------------\n";
	cout << "--------------4.取消我的预约-------------------\n";
	cout << "--------------5.注销账号登录-------------------\n";
	cout << "-----------------------------------------------\n";

	cout << "请输入你的选择\n";

	int choice;
	cin >> choice;

	extern Status* ptr;

	if (choice == 1) ptr->Book();
	else if (choice == 2) ptr->SeekSelfBook();
	else if (choice == 3) ptr->SeekBook();
	else if (choice == 4) ptr->CancelSelfBook();
	else ptr->EndP();
}

void Administor::Seek() const
{
	ifstream fin("staffmessage.txt" , ios::in | ios::binary);

	int Account , Statu;
	string Password , Name;
	if (fin.eof())
	{
		cout << "当前没有任何信息\n";
		return;
	}
	
	cout << "全部信息如下\n";
	cout << "---------------------------------------\n";
	extern string Stat[3];
	while (!fin.eof())
	{
		fin >> Account >> Password >> Name >> Statu;
		cout << "账户 " << Account <<" "<< "姓名是 " << Name <<" "<< "身份是 " << Stat[Statu - 1] << endl;
	}
	cout << "---------------------------------------\n";
	fin.close();

	system("pause");
	system("cls");
}

void Status::SeekComp() const
{
	FILE* fp = fopen("ComputerRoom.txt" , "r");

	int* Mon , * Aft , Number , Capacity;
	Mon = new int[6];
	Aft = new int[6];

	extern int Tot_of_cr;

	if (!Tot_of_cr)
	{
		cout << "没有机房信息 请联系管理员\n";
		delete[] Mon;
		delete[] Aft;

		fclose(fp);
		return;
	}

	while (!feof(fp))
	{
		fscanf(fp , "%d %d " , &Number , &Capacity);
		for (int i = 1; i <= 5; i ++) fscanf(fp , "%d " , &Mon[i]);
		for (int i = 1; i <= 5; i ++) fscanf(fp , "%d " , &Aft[i]);

		cout << "----------------------------------------\n";
		cout << Number << " 号机房信息\n\n";
		cout << "容量 " << Capacity << "\n\n";
		
		for(int i = 1 ; i <= 5 ; i ++)
			cout << "周" << i << " 上午剩余 " << Mon[i] << " 下午剩余 " << Aft[i] << endl;
	}

	delete[] Mon;
	delete[] Aft;

	fclose(fp);
}

void Administor::ClearBook()
{
	fstream fc("Book.txt" , ios::trunc);
	fc.close();

	cout << "清空完成\n\n";
}

void Administor::showMain() const
{
	cout << "-----------------------------------------------\n";
	cout << "-------------欢迎使用机房预约系统--------------\n";
	cout << "--------------1.进行账号添加-------------------\n";
	cout << "--------------2.查看账号信息-------------------\n";
	cout << "--------------3.查看机房信息-------------------\n";
	cout << "--------------4.清空预约信息-------------------\n";
	cout << "--------------5.注销账号登录-------------------\n";
	cout << "-----------------------------------------------\n";

	cout << "请输入你的选择\n";

	int choice;
	cin >> choice;

	extern Status* ptr;

	if (choice == 1) ptr->AddAccount();
	else if (choice == 2) ptr->Seek();
	else if (choice == 3) ptr->SeekComp();
	else if (choice == 4) ptr->ClearBook();
	else ptr->EndP();
}