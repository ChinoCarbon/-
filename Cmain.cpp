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
	cout << "��ӭʹ�û���ԤԼϵͳ\n";
	int status = 0;

	if (!Logged)
	{
		int Accout;
		string Password;

		cout << "���¼\n";
		
	Label:
		cout << "-------------------------\n";
		cout << "�����������˺�\n";
		cout << "-------------------------\n";

		cin >> Accout;

		cout << "-------------------------\n";
		cout << "��������������\n";
		cout << "-------------------------\n";

		cin >> Password;
		extern string Stat[3];

		if (!(status = login(Accout , Password)))
		{
			cout << "�˺�������� ������ ���˺Ų�����\n";
			goto Label;
		}
		else
		{
			system("cls");
			cout << "��¼�ɹ�\n";
			cout << "��������ǣ�" << Stat[status - 1] << endl;
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

	cout << "��ӭ�� " << Stat[status - 1] << " " << User->Name << endl;

	User->showMain();
}