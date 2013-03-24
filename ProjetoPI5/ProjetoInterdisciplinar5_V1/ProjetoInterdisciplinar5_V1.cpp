// ProjetoInterdisciplinar5_V1.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "sqlite3.h"

/* argc = quantidade de colunas
   argv = valores das colunas
   azColName = identificador das colunas */
static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
   int i;
   for(i=0; i<argc; i++)
   {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main(int argc, char **argv)
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;

   /*if( argc!=3 )
   {
      fprintf(stderr, "Uso: %s DATABASE SQL-STATEMENT\n", argv[0]);
      exit(1);
   }

   /* abre o database */
   rc = sqlite3_open("banco_exemplo.sqlite", &db);
   if( rc )
   {
      fprintf(stderr, "Nao foi possivel abrir: %s\n", sqlite3_errmsg(db));
      sqlite3_close(db);
      exit(1);
   }

   /* executa a SQL (para cada linha retornada, chama a funcao "callback") */
   rc = sqlite3_exec(db, "SELECT * FROM planets", callback, 0, &zErrMsg);
   if( rc!=SQLITE_OK )
   {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   sqlite3_close(db);
   return 0;
}


