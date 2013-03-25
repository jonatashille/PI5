#include "stdafx.h"
#include "DataBase.h"

using namespace std;

//Métodos Privados
sqlite3_stmt* DataBase::Preparar(const char* pQuery)
{
	CheckBD();

	const char* szTail=0;
	sqlite3_stmt* pVM;

	int rc = sqlite3_prepare_v2(mpDB, pQuery, -1, &pVM, &szTail);

	if (rc != SQLITE_OK)
	{
		const char* szError = sqlite3_errmsg(mpDB);
		/*throw CppSQLite3Exception(nRet,
								(char*)szError,
								DONT_DELETE_MSG);*/
	}

	return pVM;
}

DataBase::DataBase(void)
{
	mpDB = 0;
}


DataBase::~DataBase(void)
{
}

void DataBase::Abrir(char* pArquivo)
{
	int nRet = sqlite3_open(pArquivo, &mpDB);

	if (nRet != SQLITE_OK)
	{
		const char* szError = sqlite3_errmsg(mpDB);
		//throw CppSQLite3Exception(nRet, (char*)szError, DONT_DELETE_MSG);
	}
}

void DataBase::Fechar()
{
	if (mpDB)
	{
		if (sqlite3_close(mpDB) == SQLITE_OK)
		{
			mpDB = 0;
		}
		else
		{
			cout << "Nao foi possivel fechar o banco de dados" << endl;
			/*throw CppSQLite3Exception(CPPSQLITE_ERROR,
									"Unable to close database",
									DONT_DELETE_MSG);*/
		}
	}
}

void DataBase::CheckBD()
{
	if (!mpDB)
	{
		cout << "O banco de dados nao esta aberto" << endl;
		/*throw CppSQLite3Exception(CPPSQLITE_ERROR,
								"Database not open",
								DONT_DELETE_MSG);*/
	}
}

bool DataBase::ExisteTabela(const char* pTabela)
{
	/*char szSQL[256];
	sprintf(szSQL,
			"select count(*) from sqlite_master where type='table' and name='%s'",
			szTable);
	int nRet = execScalar(szSQL);
	return (nRet > 0);*/
	return true;
}

Query DataBase::ExecutaQuery(const char* pQuery)
{
	CheckBD();

	sqlite3_stmt* pVM = Preparar(pQuery);

	int nRet = sqlite3_step(pVM);

	if (nRet == SQLITE_DONE)
	{
		// no rows
		return Query(mpDB, pVM, true/*eof*/);
	}
	else if (nRet == SQLITE_ROW)
	{
		// at least 1 row
		return Query(mpDB, pVM, false/*eof*/);
	}
	else
	{
		nRet = sqlite3_finalize(pVM);
		const char* msgErro = sqlite3_errmsg(mpDB);
		cout << msgErro << endl;
		//throw CppSQLite3Exception(nRet, (char*)szError, DONT_DELETE_MSG);
	}
}