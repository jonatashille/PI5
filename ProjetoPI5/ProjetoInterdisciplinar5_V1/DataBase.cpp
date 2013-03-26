#include "stdafx.h"
#include "DataBase.h"

using namespace std;

//Métodos Privados
sqlite3_stmt* DataBase::Compile(const char* sQuery)
{
	CheckDB();

	const char* szTail=0;
	sqlite3_stmt* pVM;

	int rc = sqlite3_prepare_v2(mpDB, sQuery, -1, &pVM, &szTail);

	if (rc != SQLITE_OK)
	{
		const char* sErrMsg = sqlite3_errmsg(mpDB);
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
	try
	{
		Close();
	}
	catch (...)
	{
	}
}

DataBase& DataBase::operator=(const DataBase& db)
{
	this->mpDB = db.mpDB;
	return *this;
}

void DataBase::Open(char* sFile)
{
	int nRet = sqlite3_open(sFile, &mpDB);

	if (nRet != SQLITE_OK)
	{
		const char* sErrMsg = sqlite3_errmsg(mpDB);
		//throw CppSQLite3Exception(nRet, (char*)szError, DONT_DELETE_MSG);
	}
}

void DataBase::Close()
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

void DataBase::CheckDB()
{
	if (!mpDB)
	{
		cout << "O banco de dados nao esta aberto" << endl;
		/*throw CppSQLite3Exception(CPPSQLITE_ERROR,
								"Database not open",
								DONT_DELETE_MSG);*/
	}
}

bool DataBase::TableExists(const char* sTabela)
{
	/*char szSQL[256];
	sprintf(szSQL,
			"select count(*) from sqlite_master where type='table' and name='%s'",
			szTable);
	int nRet = execScalar(szSQL);
	return (nRet > 0);*/
	return true;
}

Query DataBase::ExecQuery(const char* sQuery)
{
	CheckDB();

	sqlite3_stmt* pVM = Compile(sQuery);

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
		const char* sErrMsg = sqlite3_errmsg(mpDB);
		cout << sErrMsg << endl;
		//throw CppSQLite3Exception(nRet, (char*)szError, DONT_DELETE_MSG);
	}
}

int DataBase::ExecDML(const char* sSQL)
{
	CheckDB();

	char* szError=0;

	int nRet = sqlite3_exec(mpDB, sSQL, 0, 0, &szError);

	if (nRet == SQLITE_OK)
	{
		return sqlite3_changes(mpDB);
	}
	else
	{
		//throw CppSQLite3Exception(nRet, szError);
	}
}

sqlite_int64 DataBase::LastRowId()
{
	return sqlite3_last_insert_rowid(mpDB);
}

Table DataBase::GetTable(const char* sQuery)
{
	CheckDB();

	char* szError=0;
	char** sResults=0;
	int nRet;
	int nRows(0);
	int nCols(0);

	nRet = sqlite3_get_table(mpDB, sQuery, &sResults, &nRows, &nCols, &szError);

	if (nRet == SQLITE_OK)
	{
		return Table(sResults, nRows, nCols);
	}
	else
	{
		//throw CppSQLite3Exception(nRet, szError);
	}
}