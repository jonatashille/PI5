#include "stdafx.h"
#include "Query.h"

using namespace std;

Query::Query(void)
{
}


Query::~Query(void)
{
}

Query::Query(sqlite3* pDB,
			 sqlite3_stmt* pVM,
			 bool bEof,
			 bool bOwnVM/*=true*/)
{
	mpDB = pDB;
	mpVM = pVM;
	mbEof = bEof;
	mnCols = sqlite3_column_count(mpVM);
	mbOwnVM = bOwnVM;
}

int Query::NumColunas()
{
	//checkVM();
	return mnCols;
}

const char* Query::ValorCampo(int pnCampo)
{
	return (const char*)sqlite3_column_text(mpVM, pnCampo);
}

const char* Query::ValorCampo(const char* pCampo)
{
	int nCampo = IndexCampo(pCampo);
	return (const char*)sqlite3_column_text(mpVM, nCampo);
}

int Query::IndexCampo(const char* pCampo)
{
	//checkVM();

	if (pCampo)
	{
		for (int nCampo = 0; nCampo < mnCols; nCampo++)
		{
			const char* nTemp = sqlite3_column_name(mpVM, nCampo);

			if (strcmp(pCampo, nTemp) == 0)
			{
				return nCampo;
			}
		}
	}

	/*throw CppSQLite3Exception(CPPSQLITE_ERROR,
							"Invalid field name requested",
							DONT_DELETE_MSG);*/
}

const char* Query::NomeCampo(int nColuna)
{
	//checkVM();

	if (nColuna < 0 || nColuna > mnCols-1)
	{
		/*throw CppSQLite3Exception(CPPSQLITE_ERROR,
								"Invalid field index requested",
								DONT_DELETE_MSG);*/
	}

	return sqlite3_column_name(mpVM, nColuna);
}

void Query::ProximaLinha()
{
	//checkVM();

	int nRet = sqlite3_step(mpVM);

	if (nRet == SQLITE_DONE)
	{
		// no rows
		mbEof = true;
	}
	else if (nRet == SQLITE_ROW)
	{
		// more rows, nothing to do
	}
	else
	{
		nRet = sqlite3_finalize(mpVM);
		mpVM = 0;
		const char* msgErro = sqlite3_errmsg(mpDB);
		cout << msgErro << endl;
		/*throw CppSQLite3Exception(nRet,
								(char*)szError,
								DONT_DELETE_MSG);*/
	}
}