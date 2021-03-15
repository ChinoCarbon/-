#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include"ComputerRoom.h"
#include"Status.h"

#include<iostream>
#include<fstream>
#include<string>
#include<queue>

using namespace std;

string Stat[3] = {"ѧ��" , "��ʦ" , "����Ա"};

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
	cout << "��лʹ��\n";
	exit(0);
}

void Administor::AddAccount()
{
	int Choice;
	
	cout << "ѡ��ע����\n";
	cout << "-------------------------\n";
	cout << "1  ѧ��\n";
	cout << "2  ��ʦ\n";
	cout << "3  ����Ա\n";
	cout << "-------------------------\n";

	cin >> Choice;

	int Accout;
	string Password , Name;
	
Label:
	cout << "�������˺�(������)\n";
	cin >> Accout;

	cout << "����������\n";
	cin >> Password;

	cout << "����������\n";
	cin >> Name;
	
	cout << "�˺�Ϊ��" << Accout << endl << "����Ϊ��" << Password << endl << "�����ǣ�" << Name << endl <<"����ǣ�" << Stat[Choice - 1] << endl;
	cout << "-----------\n1 ��ȷ\n2 ����\n-----------\n";
	
	int ch;
	cin >> ch;
	if (ch == 2) goto Label;
	else
	{
		system("cls");
		cout << "ע��ɹ�\n";
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
		cout << "û���κ�ԤԼ\n";
		fclose(fp);
		return;
	}

	rewind(fp);

	int Accout , Number , Day , Period , IsAccepted;
	char Name[150];

	cout << "ȫ��ԤԼ���� \n\n";
	cout << "-----------------------------------------\n\n";

	string Per[2] = {"����" , "����"};
	string Acc[3] = {"��δ���" , "�����ͨ��" , "���δͨ��"};
	while (!feof(fp))
	{
		fscanf(fp , "%d %s %d %d %d %d " , &Accout , Name , &Number , &Day , &Period , &IsAccepted);
		cout << "ѧ�ţ� " << Accout << " ������ " << Name << " Ԥ���ˣ� " << Number << " �Ż����� ʱ���ǣ���" << Day << Per[Period - 1] << ", ״̬�ǣ� " << Acc[IsAccepted] << endl;
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
	string Per[2] = {"����" , "����"};
	string Acc[3] = {"��δ���" , "�����ͨ��" , "���δͨ��"};

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
		cout << "ѧ�ţ� " << Accout << " ������ " << Name << " Ԥ���ˣ� " << Number << " �Ż����� ʱ���ǣ���" << Day << Per[Period - 1] << ", ״̬�ǣ� " << Acc[IsAccepted] << endl;

		cout << "�Ƿ�ͬ��\n1 ��\n2 ��\n";
		cin >> Choice;
		IsAccepted = Choice;
		
		cout << "�������\n";
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
	cout << "-------------��ӭʹ�û���ԤԼϵͳ--------------\n";
	cout << "-------------1 �鿴����ԤԼ--------------------\n";
	cout << "-------------2 ��ʼ���ԤԼ--------------------\n";
	cout << "-------------3 ע���˺ŵ�¼--------------------\n";
	cout << "-----------------------------------------------\n";


	cout << "���������ѡ��\n";

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
	cout << "������ԤԼ�Ļ���\n";
	cin >> Number;

Label2:
	cout << "���������� �ܣ�1 - 5��\n";
	cin >> Day;

	if (Day < 1 || Day > 5)
	{
		cout << "������� ����������\n";
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
		cout << "û�иû���\n";
		goto Label1;
	}

	if (crptr->Room[Count]->RemainM[Day] == 0 && crptr->Room[Count]->RemainA[Day] == 0)
	{
		cout << "�����Ѿ�û�л�����\n";
		goto Label2;
	}

	cout << "�� " << Day << "\n\n" << "����ʣ����� " << crptr->Room[Count]->RemainM[Day] << "��\n����ʣ����� "
		<< crptr->Room[Count]->RemainA[Day] << "��\n";

Label3:
	cout << "������Ԥ��ʱ��\n1 ����\n2 ����\n";
	cin >> Period;

	if (Period == 1)
	{
		if (crptr->Room[Count]->RemainM[Day] == 0)
		{
			cout << "�����Ѿ�û�л�����\n";
			goto Label3;
		}
		cout << "��Ԥ��������\n";
		crptr->Room[Count]->RemainM[Day] -= 1;
	}
	if (Period == 2)
	{
		if (crptr->Room[Count]->RemainA[Day] == 0)
		{
			cout << "�����Ѿ�û�л�����\n";
			goto Label3;
		}
		cout << "��Ԥ��������\n";
		crptr->Room[Count]->RemainA[Day] -= 1;
	}

	crptr->Write();

	system("pause");
	system("cls");

	cout << "ԤԼ�ɹ�,��ȴ���ʦ���\n";
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
		cout << "��û���κ�ԤԼ\n";
		fclose(fp);
		return;
	}

	rewind(fp);

	int Accout , Number , Day , Period , IsAccepted;
	char Name[150];

	cout << "���ԤԼ���� \n\n";
	cout << "-----------------------------------------\n\n";

	string Per[2] = {"����" , "����"};
	string Acc[3] = {"��δ���" , "�����ͨ��" , "���δͨ��"};
	while (!feof(fp))
	{
		fscanf(fp , "%d %s %d %d %d %d " , &Accout , Name , &Number , &Day , &Period , &IsAccepted);
		if (Accout != this->Accout) continue;
		cout << "ѧ�ţ� " << Accout << " ������ " << Name << " Ԥ���ˣ� " << Number << " �Ż����� ʱ���ǣ���" << Day << Per[Period - 1] << ", ״̬�ǣ� " << Acc[IsAccepted] << endl;
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
		cout << "��û���κ�ԤԼ\n";
		fclose(fp);
		return;
	}

	rewind(fp);

	int Accout , Number , Day , Period , IsAccepted;
	char Name[150];
	int Choice;
	string Per[2] = {"����" , "����"};
	string Acc[3] = {"��δ���" , "�����ͨ��" , "���δͨ��"};

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
	cout << "���� " << tot << " ��ԤԼ\n��ȡ����һ��\n���� 0 ��ȡ��\n";

	cin >> Choice;

	if (Choice > tot || Choice < 0)
	{
		cout << "��Ч����";
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

	cout << "ɾ���ɹ�\n\n";

	fout.close();
}

void Student::showMain() const
{
	cout << "-----------------------------------------------\n";
	cout << "-------------��ӭʹ�û���ԤԼϵͳ--------------\n";
	cout << "--------------1.���л���ԤԼ-------------------\n";
	cout << "--------------2.�鿴�ҵ�ԤԼ-------------------\n";
	cout << "--------------3.�鿴����ԤԼ-------------------\n";
	cout << "--------------4.ȡ���ҵ�ԤԼ-------------------\n";
	cout << "--------------5.ע���˺ŵ�¼-------------------\n";
	cout << "-----------------------------------------------\n";

	cout << "���������ѡ��\n";

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
		cout << "��ǰû���κ���Ϣ\n";
		return;
	}
	
	cout << "ȫ����Ϣ����\n";
	cout << "---------------------------------------\n";
	extern string Stat[3];
	while (!fin.eof())
	{
		fin >> Account >> Password >> Name >> Statu;
		cout << "�˻� " << Account <<" "<< "������ " << Name <<" "<< "����� " << Stat[Statu - 1] << endl;
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
		cout << "û�л�����Ϣ ����ϵ����Ա\n";
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
		cout << Number << " �Ż�����Ϣ\n\n";
		cout << "���� " << Capacity << "\n\n";
		
		for(int i = 1 ; i <= 5 ; i ++)
			cout << "��" << i << " ����ʣ�� " << Mon[i] << " ����ʣ�� " << Aft[i] << endl;
	}

	delete[] Mon;
	delete[] Aft;

	fclose(fp);
}

void Administor::ClearBook()
{
	fstream fc("Book.txt" , ios::trunc);
	fc.close();

	cout << "������\n\n";
}

void Administor::showMain() const
{
	cout << "-----------------------------------------------\n";
	cout << "-------------��ӭʹ�û���ԤԼϵͳ--------------\n";
	cout << "--------------1.�����˺����-------------------\n";
	cout << "--------------2.�鿴�˺���Ϣ-------------------\n";
	cout << "--------------3.�鿴������Ϣ-------------------\n";
	cout << "--------------4.���ԤԼ��Ϣ-------------------\n";
	cout << "--------------5.ע���˺ŵ�¼-------------------\n";
	cout << "-----------------------------------------------\n";

	cout << "���������ѡ��\n";

	int choice;
	cin >> choice;

	extern Status* ptr;

	if (choice == 1) ptr->AddAccount();
	else if (choice == 2) ptr->Seek();
	else if (choice == 3) ptr->SeekComp();
	else if (choice == 4) ptr->ClearBook();
	else ptr->EndP();
}