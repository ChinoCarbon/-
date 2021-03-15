#pragma once

#include<iostream>
#include<vector>

using namespace std;

struct Computer//机房类
{
	Computer(int , int , int* , int*);

	int Capa , Number;

	int RemainM[6] , RemainA[6];
};

class ComputerRoom //机房管理类
{

	friend class Administor;

public:
	ComputerRoom();
	void Write();
	void WriteBook(int , char* , int , int , int , int , int);
	vector<Computer*>Room;
};

