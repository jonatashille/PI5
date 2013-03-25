#pragma once
#include "Query.h"
class DataBase
{
private:
	sqlite3* mpDB;
	sqlite3_stmt* Preparar(const char*);
public:
	DataBase(void);
	~DataBase(void);
	void Abrir(char*);
	void Fechar();
	void CheckBD();
	bool ExisteTabela(const char*);
	Query ExecutaQuery(const char*);
};

