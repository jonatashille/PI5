// ProjetoInterdisciplinar5_V1.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "sqlite3.h"
#include "DataBase.h"
#include "Query.h"

using namespace std;

int main()
{
	DataBase db;
	db.Abrir("banco_exemplo.sqlite");
	Query q = db.ExecutaQuery("SELECT * FROM planets");

	for(int i=0;i < q.NumColunas();i++)
	{
		cout << q.ValorCampo(i) << endl;
	}

	for(int i=0;i < q.NumColunas();i++)
	{
		cout << q.NomeCampo(i) << endl;
	}
	cout << q.ValorCampo("object") << endl;
	q.ProximaLinha();
	cout << q.ValorCampo("object") << endl;
	q.ProximaLinha();
	cout << q.ValorCampo("object") << endl;
	q.ProximaLinha();
	cout << q.ValorCampo("object") << endl;
	q.ProximaLinha();
	cout << q.ValorCampo("object") << endl;
	q.ProximaLinha();
	cout << q.ValorCampo("object") << endl;
	q.ProximaLinha();
	cout << q.ValorCampo("object") << endl;
	q.ProximaLinha();
	cout << q.ValorCampo("object") << endl;
	q.ProximaLinha();
	cout << q.ValorCampo("object") << endl;
	q.ProximaLinha();

   return 0;
}


