#pragma once
#include "stdafx.h"

class Menu
{
private :
	int op;
	string query, dml;
public:
	Menu(void);
	~Menu(void);
	void MainScreen();
	void Options();
	void Query();
	void DML();
};

