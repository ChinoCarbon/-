#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include"ComputerRoom.h"
#include"Status.h"

#include<iostream>
#include<fstream>

using namespace std;

int Tot_of_cr = 0; //�ܻ�����

Computer::Computer(int Number , int Capacity , int* Mon , int* Aft)
{
	this->Capa = Capacity;
	this->Number = Number;
	for (int i = 1; i <= 5; i ++)
	{
		RemainA[i] = Aft[i];
		RemainM[i] = Mon[i];
	}
};

void ComputerRoom::WriteBook(int Accout , char* Name , int Count , int Day , int Period , int IsAccepted , int IsApp /*�Ƿ�׷��д��*/)
{
	ofstream fout;

	if (!IsApp) fout.open("Book.txt" , ios::out);
	else fout.open("Book.txt" , ios::app);
	extern Status* ptr;
	
	fout << Accout << " " << Name << " " << Count << " " << Day << " " << Period << " " << IsAccepted << " ";
	//д��˳�� �˺� ���� ������ ���ڼ� ����\���� �Ƿ�ͬ��
}

void ComputerRoom::Write()
{
	ofstream fout("ComputerRoom.txt" , ios::binary | ios::trunc);

	for (vector<Computer*>::iterator i = this->Room.begin(); i != this->Room.end(); i ++)
	{
		fout << (*i)->Number << " " << (*i)->Capa << " ";
		for (int j = 1; j <= 5; j ++) fout << (*i)->RemainM[j] << " ";
		for (int j = 1; j <= 5; j ++) fout << (*i)->RemainA[j] << " ";
	}

	fout.close();
}

ComputerRoom::ComputerRoom()
{
	extern Status* ptr;
	
	ifstream fin("ComputerRoom.txt" , ios::binary | ios::in);

	int Choice , Capacity = 0; 
	int* Mon , * Aft;
	if (!fin.is_open() || fin.eof())
	{
		ofstream fout("ComputerRoom.txt" , ios::binary | ios::app);
		if (ptr->status == 3)
		{
			cout << "����û���κλ�����Ϣ���Ƿ���ӻ�����\n1 ��\n2 �˳�\n\n���������ѡ��\n";
			cin >> Choice;
			if (Choice == 1)
			{
				while (++Tot_of_cr)
				{
					cout << "�������" << " " << Tot_of_cr << " �Ż���\n";
					cout << "����������� ���� 0 �������\n";

					cin >> Capacity;
					if (!Capacity)
					{
						cout << "�������\n";
						break;
					}
					else
					{
						cout << Tot_of_cr << " �Ż�������Ϊ " << Capacity << endl << endl;

						Mon = new int[6];
						Aft = new int[6];

						for (int i = 1; i <= 5; i ++) Mon[i] = Aft[i] = Capacity;
						this->Room.push_back(new Computer(Tot_of_cr , Capacity , Mon , Aft));
						fout << Tot_of_cr << " " << Capacity <<" "; 
						for (int i = 1; i <= 9; i ++) fout << Capacity << " "; fout << Capacity;

						delete[] Mon;
						delete[] Aft;
					}

				}
			}
			else exit(0);
		}
		else
		{
			cout << "����û���κλ�����Ϣ����֪ͨ����Ա���\n";
			exit(0);
		}

		fout.close();
	}
	else
	{
		fin.close();
		FILE* fp = fopen("ComputerRoom.txt" , "r");

		while (!feof(fp))
		{
			Tot_of_cr ++;
			int Number = 0;
			
			Mon = new int[6];
			Aft = new int[6];

			fscanf(fp , "%d %d " , &Number , &Capacity);

			for (int i = 1; i <= 5; i ++) fscanf(fp , "%d " , &Mon[i]);
			for (int i = 1; i <= 5; i ++) fscanf(fp , "%d " , &Aft[i]);

			this->Room.push_back(new Computer(Number , Capacity , Mon , Aft));

			delete[] Mon;
			delete[] Aft;
		}

		fclose(fp);
	}
}