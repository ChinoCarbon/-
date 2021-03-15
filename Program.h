#pragma once
#include<string>
#include"Status.h"

using namespace std;
class Cmain
{
public:
	int showlogin() const;
	int login(int , string) const;
	void showmain(int , Status*) const;
};