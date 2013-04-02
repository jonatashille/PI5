#include "stdafx.h"
#include "Query.h"
#include "SQLiteException.h"

using namespace std;

static const bool DONT_DELETE_MSG=false;

Query::Query(void)
{
}


Query::~Query(void)
{
	try
	{
		Finalize();
	}
	catch (...)
	{
	}
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

int Query::NumColuns()
{
	CheckVM();
	return mnCols;
}

const char* Query::FieldValue(int nField)
{
	return (const char*)sqlite3_column_text(mpVM, nField);
}

const char* Query::FieldValue(const char* sField)
{
	int nField = FieldIndex(sField);
	return (const char*)sqlite3_column_text(mpVM, nField);
}

int Query::FieldIndex(const char* sField)
{
	CheckVM();

	if (sField)
	{
		for (int nField = 0; nField < mnCols; nField++)
		{
			const char* nTemp = sqlite3_column_name(mpVM, nField);

			if (strcmp(sField, nTemp) == 0)
			{
				return nField;
			}
		}
	}

	throw SQLiteException(1,
							"Invalid field name requested",
							DONT_DELETE_MSG);
}

const char* Query::FieldName(int nCol)
{
	CheckVM();

	if (nCol < 0 || nCol > mnCols-1)
	{
		throw SQLiteException(1,
								"Invalid field index requested",
								DONT_DELETE_MSG);
	}

	return sqlite3_column_name(mpVM, nCol);
}

void Query::NextLine()
{
	CheckVM();

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
		const char* szError = sqlite3_errmsg(mpDB);
		throw SQLiteException(nRet,
								(char*)szError,
								DONT_DELETE_MSG);
	}
}

bool Query::FieldIsNull(int nField)
{
	return (FieldDataType(nField) == SQLITE_NULL);
}

bool Query::FieldIsNull(const char* sField)
{
	int nField = FieldIndex(sField);
	return (FieldDataType(nField) == SQLITE_NULL);
}

int Query::FieldDataType(int nCol)
{
	CheckVM();

	if (nCol < 0 || nCol > mnCols-1)
	{
		throw SQLiteException(1,
								"Invalid field index requested",
								DONT_DELETE_MSG);
	}

	return sqlite3_column_type(mpVM, nCol);
}

bool Query::eof()
{
	CheckVM();
	return mbEof;
}

void Query::Finalize()
{
	if (mpVM && mbOwnVM)
	{
		int nRet = sqlite3_finalize(mpVM);
		mpVM = 0;
		if (nRet != SQLITE_OK)
		{
			const char* szError = sqlite3_errmsg(mpDB);
			throw SQLiteException(nRet, (char*)szError, DONT_DELETE_MSG);
		}
	}
}

void Query::CheckVM()
{
	if (mpVM == 0)
	{
		throw SQLiteException(1,
								"Null Virtual Machine pointer",
								DONT_DELETE_MSG);
	}
}