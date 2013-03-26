#pragma once
class Table
{
private:
	void CheckResults();

    int mnCols;
    int mnRows;
    int mnCurrentRow;
    char** msResults;
public:
	Table(void);
	Table(char** sResults, int nRows, int nCols);
	~Table(void);
	void Finalize();

	int NumFields();
	int NumRows();

	const char* FieldValue(int);
	const char* FieldValue(const char*);
	const char* FieldName(int);

	bool FieldIsNull(int);
	bool FieldIsNull(const char*);

	void SetRow(int);
};

