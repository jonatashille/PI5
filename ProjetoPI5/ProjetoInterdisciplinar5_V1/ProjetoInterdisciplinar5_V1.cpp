// ProjetoInterdisciplinar5_V1.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "sqlite3.h"
#include "DataBase.h"
#include "Query.h"
#include "Table.h"

using namespace std;

int main()
{
	DataBase db;
	db.Open("banco_exemplo.sqlite");

    Table t = db.GetTable("SELECT * FROM planets;");

    for (int fld = 0; fld < t.NumFields(); fld++)
    {
        cout << t.FieldName(fld) << "|";
    }
    cout << endl;
    for (int row = 0; row < t.NumRows(); row++)
    {
        t.SetRow(row);
        for (int fld = 0; fld < t.NumFields(); fld++)
        {
            if (!t.FieldIsNull(fld))
                cout << t.FieldValue(fld) << "|";
            else
                cout << "NULL" << "|";
        }
        cout << endl;
    }

	/*Query q = db.ExecQuery("SELECT * FROM planets");

	for(int i=0;i < q.NumColuns();i++)
	{
		cout << q.FieldValue(i) << endl;
	}

	for(int i=0;i < q.NumColuns();i++)
	{
		cout << q.FieldName(i) << endl;
	}
	cout << q.FieldValue("object") << endl;
	q.NextLine();
	cout << q.FieldValue("object") << endl;
	q.NextLine();
	cout << q.FieldValue("object") << endl;
	q.NextLine();
	cout << q.FieldValue("object") << endl;
	q.NextLine();
	cout << q.FieldValue("object") << endl;
	q.NextLine();
	cout << q.FieldValue("object") << endl;
	q.NextLine();
	cout << q.FieldValue("object") << endl;
	q.NextLine();
	cout << q.FieldValue("object") << endl;
	q.NextLine();
	cout << q.FieldValue("object") << endl;
	q.NextLine();*/

   return 0;
}


