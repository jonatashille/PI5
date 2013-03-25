#include "stdafx.h"
#include "SQL.h"

//Métodos Privados
sqlite3_stmt* SQL::Preparar(const char* pQuery)
{
	//checkDB();

	const char* szTail=0;
	sqlite3_stmt* pVM;

	int rc = sqlite3_prepare_v2(db, pQuery, -1, &pVM, &szTail);

	if (rc != SQLITE_OK)
	{
		const char* szError = sqlite3_errmsg(db);
		/*throw CppSQLite3Exception(nRet,
								(char*)szError,
								DONT_DELETE_MSG);*/
	}

	return pVM;
}

SQL::SQL(void)
{
	//zErrMsg = 0;
	//stmt = NULL;
}

SQL::~SQL(void)
{
	sqlite3_close(db);
	//sqlite3_finalize( stmt );
}

void SQL::Abrir(char *arquivo)
{
	char *zErrMsg = 0;
	int rc = sqlite3_open(arquivo, &db);
	if( rc )
	{
		fprintf(stderr, "Nao foi possivel abrir: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}
}

void SQL::Executar()
{
	/*rc = sqlite3_exec(db, "SELECT * FROM planets", callback, 0, &zErrMsg);
	if( rc!=SQLITE_OK )
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}*/

    int rc = sqlite3_prepare();
    if ( rc != SQLITE_OK) exit( -1 );
	int col=1;
    while( sqlite3_step( stmt ) == SQLITE_ROW ) {
        data = (const char*)sqlite3_column_text( stmt,  col);
        printf( "%s\n", data ? data : "[NULL]" );
    }
    
    
}
// nColunas = Numero de Colunas
// vColunas = Valores das Colunas
// nomeColuna = Nome das Colunas
int SQL::callback(void *NotUsed, int nColunas, char **vColunas, char **nomeColuna)
{
	int i;
	for(i=0; i<nColunas; i++)
	{
		cout << nomeColuna[i] << " | ";
		//printf("%s = %s\n", nomeColuna[i], vColunas[i] ? vColunas[i] : "NULL");
	}
	printf("\n");
	getchar();
	return 0;
}
