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
	int NumColunas();
	const char* ValorCampo(int);
	const char* ValorCampo(const char*);
	const char* NomeCampo(int);
	int IndexCampo(const char*);

	void ProximaLinha();
};

