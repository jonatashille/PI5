#include "stdafx.h"
#include "SQL.h"


SQL::SQL(void)
{
	cout << "Criou Objeto SQL"  << endl;
}


SQL::~SQL(void)
{
}

void SQL::Abrir()
{
	string filename = "\Banco\banco_exemplo.sqlite";
	sqlite3 *Db;
	int rc;
	rc = sqlite3_open(filename.c_str(), &Db); 
	cout << "Entrou na Funcao Abrir"  << endl;
	if (sqlite3_open(filename.c_str(), &Db))
		cout << "Abriu o Banco de Dados" << endl;
	else
		cout << "Não foi possível abrir o Banco de dados" << endl;
		//const char *filename,   /* Database filename (UTF-8) */
		//sqlite3 **ppDb          /* OUT: SQLite db handle */
}
