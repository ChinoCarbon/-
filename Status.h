#pragma once
#include <string>
using namespace std;
class Status
{
public:
	virtual void showMain() const {};
	virtual void AddAccount() {};
	virtual void Seek() const {};
	virtual void SeekComp() const;
	virtual void Book() {};
	virtual void ReviewBook() {};
	virtual void SeekSelfBook() {};
	virtual void ClearBook() {};
	virtual void CancelSelfBook() {};
	void SeekBook() const;
	void EndP() const;

	string Name; 
	int status , Accout;

};

class Administor : public Status
{
public:
	Administor(int , string , int);
	void AddAccount();
	void Seek() const;
	void showMain() const;
	void ClearBook();
};

class Teacher : public Status
{
public:
	Teacher(int , string , int);
	void showMain() const;
	void ReviewBook();
};

class Student : public Status
{
public:
	Student(int , string , int);
	void showMain() const;
	void Book();
	void SeekSelfBook();
	void CancelSelfBook();
};