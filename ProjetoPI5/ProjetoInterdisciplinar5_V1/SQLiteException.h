#pragma once
class SQLiteException
{
private:
    int mnErrCode;
    char* mpszErrMess;
public:
	SQLiteException(const int, char*, bool bDeleteMsg = true);
	SQLiteException(const SQLiteException&);
	virtual ~SQLiteException(void);

    const int errorCode() { return mnErrCode; }

    const char* errorMessage() { return mpszErrMess; }

	static const char* errorCodeAsString(int nErrCode);
};

