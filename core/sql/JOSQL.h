/********************************************************************
CREATED: 18/1/2014   14:54
FILE: 	 JOSQL.cpp
AUTHOR:  James Ou 
*********************************************************************/

#ifndef __JO_SQL_H__
#define __JO_SQL_H__

#include <string>
#include <list>
#include "core/sql/JOSqlReader.h"
#include "utils/JOMacro.h"
#include "utils/JOSingleton.h"

NS_JOFW_BEGIN


class JOITask;

typedef int (*sqlite3_callback)(void*,int,char**, char**);
struct JO_DLL ISqlReadStreamCallBack
{
    virtual void onSqTablelLoad(JOSqlReader *pReader, const std::string &tableName, bool bFinish) = 0;
};


struct JO_DLL JOLoadSqlInfo
{
    std::string sql;
    std::string tableName;
    ISqlReadStreamCallBack *pCallback;
    bool bAvailable;
    int luaHandle;
};

class JO_DLL JOSQL : public JOSingleton<JOSQL>
{
public:
	JOSQL();
	virtual ~JOSQL();
public:
	/*
	用来创建一个db数据库 db为数据库的名字
	打开数据库
	*/
    void initDB(const char *db);  
	/*
	用来判断表格是否存在
	name:表示表名
	*/
    bool tableIsExist(std::string name);  
      
	/*
	用来创建一个表名为name的表格，创建时会先匹配时否有该表的存在如果存在则不创建
	创建表  string sqls = "create table user(id integer,username text,password text)";
	*/    
    void createTable(std::string sql,std::string name);  
	/*
	用来删除一张表名为name的表格，删除时会先匹配是否有该表的存在如果不存在则不执行删除操作
	删除表名
	*/
    void deleteTable(std::string name);  
	
	/*
	sqlstr=" insert into MyTable_1( name ) values ( '????????? ) ";  	
	sqlstr="delete from MyTable_1 where ID = 2"; 	
	sqlstr="update MyTable_1 set name='????????? where ID = 3";  
	*/
	void execSql(std::string sql,
		sqlite3_callback callback = nullptr,  /* Callback function */
		void * arg = nullptr                 /* 1st argument to callback */
		);

	
	void startLoadSqlData(std::string sql,const char* tableName, ISqlReadStreamCallBack* pCallback, bool bAsyn=false);
    void cancelLoadSqlData(ISqlReadStreamCallBack *pCallback);
	/*
	通过callback返回每行数据
	*/
	void execLuaLoadSqlData(std::string sql,const char* tableName, LUA_FUNCTION luaFunc, bool bAsyn=false);
    void cancelLoadSqlData(int luaHandle);
	/*
	获取一个记录的条数
	获得记录的条数
	*/
    int getDataCount(std::string sql);  
    
    void getDataInfo(std::string sql,void *pSend);  
	/*
    关闭打开的数据库    
	*/
    void closeDB();
    
    void tick();
    
protected:
    void asynLoadSqlData(void);

private:	
    std::list<JOLoadSqlInfo> loadInfoList;
    JOITask *pTask;

};

NS_JOFW_END

#endif  // __JO_SQL_H__

