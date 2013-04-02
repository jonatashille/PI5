#include "Menu.h"

using namespace std;

Menu::Menu(void)
{
	MainScreen();
}


Menu::~Menu(void)
{
}

void Menu::MainScreen()
{
	cout << "******************************************" << endl;
	cout << "*    Author: Jonatas Alexandre Hille     *" << endl;
	cout << "*         C++ SQLite Interface           *" << endl;
	cout << "******************************************" << endl;
	cout << endl << endl;
}

void Menu::Options()
{
	cout << "Options:" << endl;
	cout << "1-SELECT" << endl;
	cout << "2-INSERT/UPDATE/DELETE" << endl;
	switch(op)
	{
		case 1: getline(cin, query);
		case 2: getline(cin, dml);
	}
}

void Menu::Query()
{
	try
	catch

}
void Menu::DML()
{
}