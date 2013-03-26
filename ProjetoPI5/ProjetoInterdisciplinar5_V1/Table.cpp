#include "stdafx.h"
#include "Table.h"


Table::Table(void)
{
	msResults = 0;
	mnRows = 0;
	mnCols = 0;
	mnCurrentRow = 0;
}

Table::Table(char** sResults, int nRows, int nCols)
{
	msResults = sResults;
	mnRows = nRows;
	mnCols = nCols;
	mnCurrentRow = 0;
}

Table::~Table(void)
{
	try
	{
		Finalize();
	}
	catch (...)
	{
	}
}

void Table::Finalize()
{
	if (msResults)
	{
		sqlite3_free_table(msResults);
		msResults = 0;
	}
}

int Table::NumFields()
{
	CheckResults();
	return mnCols;
}

int Table::NumRows()
{
	CheckResults();
	return mnRows;
}

const char* Table::FieldValue(int nField)
{
	CheckResults();

	if (nField < 0 || nField > mnCols-1)
	{
		/*throw CppSQLite3Exception(CPPSQLITE_ERROR,
								"Invalid field index requested",
								DONT_DELETE_MSG);*/
	}

	int nIndex = (mnCurrentRow*mnCols) + mnCols + nField;
	return msResults[nIndex];
}

const char* Table::FieldValue(const char* sField)
{
	CheckResults();

	if (sField)
	{
		for (int nField = 0; nField < mnCols; nField++)
		{
			if (strcmp(sField, msResults[nField]) == 0)
			{
				int nIndex = (mnCurrentRow*mnCols) + mnCols + nField;
				return msResults[nIndex];
			}
		}
	}

	/*throw CppSQLite3Exception(CPPSQLITE_ERROR,
							"Invalid field name requested",
							DONT_DELETE_MSG);*/
}

const char* Table::FieldName(int nCol)
{
	CheckResults();

	if (nCol < 0 || nCol > mnCols-1)
	{
		/*throw CppSQLite3Exception(CPPSQLITE_ERROR,
								"Invalid field index requested",
								DONT_DELETE_MSG);*/
	}

	return msResults[nCol];
}

bool Table::FieldIsNull(int nField)
{
	CheckResults();
	return (FieldValue(nField) == 0);
}

bool Table::FieldIsNull(const char* sField)
{
	CheckResults();
	return (FieldValue(sField) == 0);
}

void Table::SetRow(int nRow)
{
	CheckResults();

	if (nRow < 0 || nRow > mnRows-1)
	{
		/*throw CppSQLite3Exception(CPPSQLITE_ERROR,
								"Invalid row index requested",
								DONT_DELETE_MSG);*/
	}

	mnCurrentRow = nRow;
}

void Table::CheckResults()
{
	if (msResults == 0)
	{
		/*throw CppSQLite3Exception(CPPSQLITE_ERROR,
								"Null Results pointer",
								DONT_DELETE_MSG);*/
	}
}
