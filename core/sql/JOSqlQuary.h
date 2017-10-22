#ifndef _SQLITE_QUARY_H_
#define _SQLITE_QUARY_H_

#include <string>
#include <list>
#include <memory>
#include <strstream>
#include <sstream>
#include <iosfwd>
#include "sqlite3.h"
#include "utils/JOMacro.h"

struct sqlite3_stmt;
struct sqlite3;

namespace sqlitequary
{
	extern  sqlite3 * sdb;
	bool openSQLite(const char* filename);
	bool closeSQLite();
}

NS_JOFW_BEGIN

template <typename T>
class JO_DLL JOSqlBaseQuary
{
public:
	
	static bool openSQLite(const char* filename);
	static bool closeSQLite();
	virtual ~JOSqlBaseQuary() {}
	void freeelem(T* t)
	{
		this->freeMemory(t);
		delete t;
	}
	void freelist(std::list<T*>& flist)
	{
		for (typename std::list<T*>::iterator itr = flist.begin(); itr != flist.end(); ++itr)
		{
			T* elem = *itr;
			this->freeelem(elem);
		}
		flist.clear();
	}
	bool insert(T* t)
	{
		//INSERT INTO Persons (LastName, Address) VALUES ('Wilson', 'Champs-Elysees')
		std::string sql = "insert into ";
		sql += this->GetTableName();
		sql += " ( ";
		sql += this->GetNameListString();
		sql += " ) VALUES ( ";
		sql += this->GetValueListString(t);
		sql += ")";
		return this->executeInsert(t, sql);
	}
	bool update(T* t)
	{
		//UPDATE Person SET Address = 'Zhongshan 23', City = 'Nanjing' WHERE LastName = 'Wilson'
		std::string sql = "update ";
		sql += this->GetTableName();
		sql += " set ";
		sql += this->GetUpdateKeyValueListString(t);
		sql += " where ";
		sql += this->GetKeyNameString();
		sql += " = ";
		sql += this->GetKeyValueString(t);
		return this->executeInsert(t, sql);//??
	}
	bool del(T* t)
	{
		//DELETE FROM Person WHERE LastName = 'Wilson' 
		std::string sql = "delete from ";
		sql += this->GetTableName();
		sql += " where ";
		sql += this->GetKeyNameString();
		sql +=  " = ";
		sql += this->GetKeyValueString(t);
		return this->execute(sql);
	}
	bool delall()
	{
		std::string sql = "delete from ";
		sql += this->GetTableName();
		return this->execute(sql);
	}
	std::list<T*> selectAll()
	{
		//SELECT LastName,FirstName FROM Persons
		std::string sql = "select * from " + this->GetTableName();
		return this->executeSelect(sql);
	}

	std::list<T*> selectIntKey(int key)
	{
        std::stringstream ss;
        ss<<key;
//		char temp[12];
//		::_itoa(key, temp, 10);
		std::string sql = "select * from " + this->GetTableName() + " where " + this->GetKeyNameString() + " = " + ss.str();
        
		return this->executeSelect(sql);
	}

	std::list<T*> selectStringKey(const char* keyString)
	{
		std::string sql = "select * from " + this->GetTableName() + " where " + this->GetKeyNameString() + " = " + keyString;
		return this->executeSelect(sql);
	}

	std::list<T*> selectCur(const char* sql_)
	{
		return this->executeSelect(sql_);
	}
protected:
	virtual std::string GetTableName() = 0;
	virtual std::string GetNameListString() = 0;
	virtual std::string GetValueListString(T* t) = 0;
	virtual std::string GetKeyNameString() = 0;
	virtual std::string GetKeyValueString(T* t) = 0;
	virtual std::string GetUpdateKeyValueListString(T* t) = 0;
	virtual T* getFromRow(struct sqlite3_stmt* stmt){return 0;}
	virtual void insertToRow(T* t, struct sqlite3_stmt* stmt) {}
	virtual void freeMemory(T* t){}
	bool execute(const std::string& sql)
	{
		char * errmsg = 0;
		int result = sqlite3_exec( sqlitequary::sdb, sql.c_str(), 0, 0, &errmsg );
		if(result != SQLITE_OK )
		{
			return false;
		}
		return true;
	}
	bool executeInsert(T* t, const std::string& sql)
	{
		sqlite3_stmt * stat;
		int result = sqlite3_prepare( sqlitequary::sdb, sql.c_str(), -1, &stat, 0 );
		if (result != SQLITE_OK)
		{
			return false;
		}
		this->insertToRow(t, stat);
		result = sqlite3_step( stat );
		if (result != SQLITE_OK && result != SQLITE_DONE)
		{
			sqlite3_finalize( stat );
			return false;
		}

		result = sqlite3_finalize( stat );
		if (result != SQLITE_OK)
		{
			return false;
		}
		return true;
	}
	std::list<T*> executeSelect(const std::string& sql)
	{
		std::list<T*> out;
		sqlite3_stmt * stat;
		int result = sqlite3_prepare( sqlitequary::sdb, sql.c_str(), -1, &stat, 0 );
		if (result != SQLITE_OK)
		{
			return out;
		}
		result = sqlite3_step( stat );
		while (result == SQLITE_ROW)
		{
			T* t = this->getFromRow(stat);
			out.push_back(t);
			result = sqlite3_step( stat );
		}
		sqlite3_finalize(stat);
		return out;
	}

	void AllocAndCopyString(char*& to, struct sqlite3_stmt* stmt, int index)
	{
		const char* s = (const char*)sqlite3_column_text( stmt, index );
		to = (char*)malloc(strlen(s) + 1);
		::strcpy(to, s);
	}
	template <typename BUFTYPE>
	void AllocAndCopyBuffSize(BUFTYPE*& to, int& bufSize, struct sqlite3_stmt* stmt, int index)
	{
		bufSize = sqlite3_column_bytes( stmt, index);
		if (bufSize == 0)
		{
			to = 0;
			return;
		}
		to = (BUFTYPE*)malloc(bufSize);
		::memcpy(to, sqlite3_column_blob(stmt, index), bufSize);
	}
	template <typename BUFTYPE>
	void AllocAndCopyBuff(BUFTYPE*& to, struct sqlite3_stmt* stmt, int index)
	{
		int bufSize = sqlite3_column_bytes( stmt, index);
		if (bufSize == 0)
		{
			to = 0;
			return;
		}
		to = (BUFTYPE*)malloc(bufSize);
		::memcpy(to, sqlite3_column_blob(stmt, index), bufSize);
	}

	template <typename BUFTYPE>
	void AllocAndCopyStringFromBlob(BUFTYPE*& to, struct sqlite3_stmt* stmt, int index)
	{
		int bufSize = sqlite3_column_bytes( stmt, index);
		if (bufSize == 0)
		{
			to = 0;
			return;
		}
		to = (BUFTYPE*)malloc(bufSize + 1);
		::memcpy(to, sqlite3_column_blob(stmt, index), bufSize);
		to[bufSize] = 0;
	}

	void UploadBuf(void* buf, int bufsize, struct sqlite3_stmt* stmt, int index)
	{
		if (buf == 0 || bufsize == 0)
		{
			sqlite3_bind_blob( stmt, index, 0, 0, NULL );
		}
		else
		{
			sqlite3_bind_blob( stmt, index, buf, bufsize, NULL );
		}
	}
};

struct TestStruct
{
	int id;
	int x;
	float f;
	char* name;
	void* buf;
	int bufsize;
};

class JO_DLL TestStructBaseQuary : public JOSqlBaseQuary<TestStruct>
{
protected:
	virtual std::string GetTableName()
	{
		return "t_teststruct";
	}
	virtual std::string GetNameListString()
	{
		return "id, x, f, name, buf";
	}
	virtual std::string GetValueListString(TestStruct* t)
	{
		std::strstream str;
		str << t->id << ", ";
		str << t->x << ", ";
		str << t->f << ", ";
		str << "'" << t->name << "', ";
		str << "?" << std::ends;//buf ????????? sqlite3_stmt????????????????????????????????????
		const char* tt = str.str();
		return tt;
	}
	virtual std::string GetKeyNameString()
	{
		return "id";
	}
	virtual std::string GetKeyValueString(TestStruct* t)
	{
		std::strstream str;
		str << t->id << std::ends;
		return str.str();
	}
	virtual std::string GetUpdateKeyValueListString(TestStruct* t)
	{
		std::strstream str;
		str << "id = " << t->id << ", ";
		str << "x = " << t->x << ", ";
		str << "f = " << t->f << ", ";
		str << "name = '" << t->name << "', ";
		str << "buf = ?"<< std::ends;//buf ????????? sqlite3_stmt????????????????????????????????????
		return str.str();
	}
	virtual TestStruct* getFromRow(struct sqlite3_stmt* stmt)
	{
		TestStruct* ret = new TestStruct();
		ret->id = sqlite3_column_int( stmt, 0 );
		ret->x = sqlite3_column_int( stmt, 1 );
		ret->f = sqlite3_column_double( stmt, 2 );
		AllocAndCopyString(ret->name, stmt, 3);
		//const char* s = (const char*)sqlite3_column_text( stmt, 3 );
		//ret->name = new char[strlen(s) + 1];
		//::strcpy(ret->name, s);
		AllocAndCopyBuffSize(ret->buf, ret->bufsize, stmt, 4);
		//ret->bufsize = sqlite3_column_bytes( stmt, 4);
		//ret->buf = new char[ret->bufsize];
		//::memcpy(ret->buf, sqlite3_column_blob(stmt, 4), ret->bufsize);
		return ret;
	}
	virtual void insertToRow(TestStruct* t, struct sqlite3_stmt* stmt)
	{
		sqlite3_bind_blob( stmt, 1, t->buf, (int)t->bufsize, NULL );//?????????1??????????????????????????????
	}

	virtual void freeMemory(TestStruct* t)
	{
		free(t->buf);
		free(t->name);
	}
};

NS_JOFW_END

#endif // SqliteHelper_h__
