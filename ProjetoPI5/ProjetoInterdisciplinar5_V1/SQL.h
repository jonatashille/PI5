#pragma once
#include "stdafx.h"

using namespace std;

class SQL
{
private:
	sqlite3 *db;
	//int rc;
	//char *zErrMsg;
	const char	*data;
	sqlite3_stmt* Preparar(const char*);
public:
	SQL(void);
	~SQL(void);
	void Abrir(char*);
	void Executar();
	static int callback (void*,int,char**,char**);
};

