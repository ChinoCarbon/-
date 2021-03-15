#include"Program.h"
#include"Status.h"
#include"ComputerRoom.h"

#include<iostream>
#include<cstdlib>

using namespace std;
ComputerRoom* crptr;

int main()
{
	Cmain Main;
	
	int status;
	if (!(status = Main.showlogin())) exit(0);
	
	extern Status* ptr;
	
	ComputerRoom CR;
	crptr = &CR;

	while (1)
	{
		system("pause");
		system("cls");
		Main.showmain(status , ptr);
	}
}