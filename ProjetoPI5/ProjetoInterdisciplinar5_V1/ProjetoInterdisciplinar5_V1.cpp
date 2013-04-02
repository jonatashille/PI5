// ProjetoInterdisciplinar5_V1.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "sqlite3.h"
#include "DataBase.h"
#include "Query.h"
#include "Table.h"
#include "SQLiteException.h"

using namespace std;

int main()
{
	string sql;
	try
	{
		DataBase db;
		db.Open("banco_exemplo.sqlite");

		cout << "Digite o script:" << endl;
		getline(cin,sql);

		Table t = db.GetTable(sql.c_str());

		for (int fld = 0; fld < t.NumFields(); fld++)
		{
			cout << t.PrintFieldName(t, fld);
		}
		cout << endl;
		for (int fld = 0; fld < t.NumFields(); fld++)
		{
			cout << setw(20) << "---------------------";
		}
		cout << endl;
		for (int row = 0; row < t.NumRows(); row++)
		{
			t.SetRow(row);
			for (int fld = 0; fld < t.NumFields(); fld++)
			{
				if (!t.FieldIsNull(fld))
					cout << t.PrintFieldValue(t, fld);
				else
					cout << "NULL" << "|";
			}
			cout << endl;
		}
	}
	catch(SQLiteException& e)
	{
		cerr << e.errorCode() << ":" << e.errorMessage() << endl;
	}

   return 0;
}


