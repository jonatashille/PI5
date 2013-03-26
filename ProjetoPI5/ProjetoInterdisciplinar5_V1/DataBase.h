#pragma once
#include "Query.h"
#include "Table.h"

class DataBase
{
private:
	sqlite3* mpDB;
	sqlite3_stmt* Compile(const char*);
	void CheckDB();
public:
	DataBase(void);
	~DataBase(void);
	DataBase& operator=(const DataBase&);
	void Open(char*);
	void Close();
	
	bool TableExists(const char*);
	Query ExecQuery(const char*);
	int ExecDML(const char*);
	sqlite_int64 LastRowId();

	Table GetTable(const char*);
};

