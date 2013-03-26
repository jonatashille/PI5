#pragma once
class Query
{
private:
	sqlite3* mpDB;
    sqlite3_stmt* mpVM;
    bool mbEof;
    int mnCols;
    bool mbOwnVM;
public:
	Query(void);
	~Query(void);
	Query(sqlite3* pDB,
		  sqlite3_stmt* pVM,
          bool bEof,
          bool bOwnVM=true);
	int NumColuns();
	const char* FieldValue(int);
	const char* FieldValue(const char*);
	const char* FieldName(int);
	int FieldIndex(const char*);
	void NextLine();
	bool FieldIsNull(int);
	bool FieldIsNull(const char*);
	int FieldDataType(int);
	bool eof();
	void Finalize();
	void CheckVM();
};

