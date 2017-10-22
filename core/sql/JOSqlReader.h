#ifndef __JO_SqlReader_h__
#define __JO_SqlReader_h__

#include "utils/JOMacro.h"
struct sqlite3_stmt;

struct JOSqlBlob
{
	const void* blobBuf;
	int blobSize;
};

class JO_DLL JOSqlReader
{
private:
	JOSqlReader(){}
public:
	JOSqlReader(struct sqlite3_stmt* stmt);
	~JOSqlReader();

	int getDataCount();
	int readInt(int col);
	int readInt64(int col);
	double readDouble(int col);
	JOSqlBlob readBlob(int col);
	const char* readString(int col);
	
private:
	struct sqlite3_stmt* m_pStmt;
};

#endif // __JO_SqlReader_h__