#include"Program.h"
#include"Status.h"

#include<iostream>
#include<fstream>

using namespace std;

int Logged;
Status* ptr;

int Cmain::login(int accout , string password) const
{
	ifstream fin("staffmessage.txt" , ios::in | ios::binary);
	
	bool IsRight = 0;
	int Account , Stat;
	string Password , Name;

	while (!fin.eof())
	{
		fin >> Account >> Password >> Name >> Stat;
		cout << Account << " " << Password << endl;
		if (Account == accout && Password == password)
		{
			IsRight = 1;

			if (Stat == 1) ptr = new Student(Account , Name , Stat);
			else if (Stat == 2) ptr = new Teacher(Account , Name , Stat);
			else ptr = new Administor(Account , Name , Stat);
			
			break;
		}
	}

	fin.close();
	return IsRight ? Stat : 0;
}

int Cmain::showlogin() const
{
	cout << "---------------------------------------\n";
	cout << "欢迎使用机房预约系统\n";
	int status = 0;

	if (!Logged)
	{
		int Accout;
		string Password;

		cout << "请登录\n";
		
	Label:
		cout << "-------------------------\n";
		cout << "请输入您的账号\n";
		cout << "-------------------------\n";

		cin >> Accout;

		cout << "-------------------------\n";
		cout << "请输入您的密码\n";
		cout << "-------------------------\n";

		cin >> Password;
		extern string Stat[3];

		if (!(status = login(Accout , Password)))
		{
			cout << "账号密码错误 或者是 该账号不存在\n";
			goto Label;
		}
		else
		{
			system("cls");
			cout << "登录成功\n";
			cout << "您的身份是：" << Stat[status - 1] << endl;
			Logged = 1;
			system("pause");
			system("cls");
		}
	}

	return status;
}

void Cmain::showmain(int status , Status* User) const
{
	system("cls");

	extern string Stat[3];

	cout << "欢迎你 " << Stat[status - 1] << " " << User->Name << endl;

	User->showMain();
}