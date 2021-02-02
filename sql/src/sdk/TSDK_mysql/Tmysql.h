#ifndef __TCLASS_MYSQL_H__
#define __TCLASS_MYSQL_H__
#include "common/db_common.h"
#include "Tmysql_type.h"
#include <common/mysql_include/mysql.h>

class Tmysql
{
public:
	//初始化Mysql API
	DB_ERR Init();

	//清理占用的所有资源
	DB_ERR Finit();

	//数据库连接（不考虑线程安全） flag设置支持多条语句
	DB_ERR Connect(const char*host, const char*user, const char*pass, const char*db, unsigned short port = 3306, unsigned long flag = 0);

	//创建数据库
	DB_ERR CreateDatabase(std::string &dbname);

	//删除数据库
	DB_ERR DeleteDatabase(std::string &dbname);

	//创建表
	DB_ERR CreateTable(TTABLEVECTOR &tvector, std::string &tablename, TABLE_TYPE tabletype);

	//删除表
	DB_ERR DeleteTable(std::string &tablename);

	/*****************************************增**************************************************/
	//插入非二进制数据
	DB_ERR Insert(TDATAMAP &kv, std::string &tablename);

	//插入二进制数据
	DB_ERR InsertBin(TDATAMAP &kv, std::string &tablename);

	/*****************************************删**************************************************/
	//删除指定ID的数据
	DB_ERR DropWithId(std::string &tablename, std::string &idname, std::string &idnum);

	//删除包含指定字段的数据
	DB_ERR LikeDrop(std::string &tablename, std::string &fieldname, std::string &fielddata);

	//清空表,berecover传true,清空后不可恢复;传false清空后不可恢复
	DB_ERR DropWithTable(std::string &tablename, bool brecover = true);

	/*****************************************改**************************************************/
	//返回更新数量，失败返回-1
	TUINT64 Update(TDATAMAP &kv, std::string &tablename, std::string &where, std::string &idnum);

	//更新二进制数据
	TUINT64 UpdateBin(TDATAMAP &kv, std::string &tablename, std::string &where, std::string &idnum);

	/*****************************************查**************************************************/
	//select from查表,配合结果集接口使用
	DB_ERR Select(std::string &tablename);

	//like 模糊查找，配合结果集接口使用
	DB_ERR Like(std::string &tablename, std::string &fieldname, std::string &fielddata);

	//结果集获取返回全部结果
	DB_ERR StoreResult();

	//开始接收结果，通过Fetch获取
	DB_ERR UseResult();

	//释放结果集占用的空间
	DB_ERR FreeResult();

	//获取一行数据
	TROW FetchRow();

	//简易接口,返回select的数据结果，每次调用清理上一次的结果集
	DB_ERR EasySelect(std::string &tablename, TROWS &rows);

	//简易接口，模糊查找
	DB_ERR EasyLike(std::string &tablename, std::string &fieldname,std::string &fielddata, TROWS &rows);

	/*****************************************设置************************************************/
	//切换mysql当前编码格式
	DB_ERR SwitchType(TABLE_TYPE ttype);

	//Mysql参数的设定 Connect之前调用
	DB_ERR Options(LX_OPT opt, const void *arg);

	//连接超时时间
	DB_ERR SetConnectTimeout(int sec);

	//自动重连，默认不自动
	DB_ERR SetReconnect(bool isre = true);

	/*****************************************事务************************************************/
	//开始事务
	DB_ERR StartTransaction();

	//结束事务
	DB_ERR StopTransaction();

	//提交
	DB_ERR Commit();

	//回滚
	DB_ERR Rollback();

	//执行sql语句  if sqllen=0 strlen获取字符长度
	bool Query(const char*sql, unsigned long sqllen = 0);

private:
	//生成insert sql语句
	std::string GetInsertSql(TDATAMAP &kv, std::string &tablename);

	//获取更新数据的sql语句 where语句中，用户要包含where
	std::string GetUpdateSql(TDATAMAP &kv, std::string &tablename, std::string &where, std::string &idnum);

	//根据结构体获取创建表对应域的sql语句
	std::string GetCreateSql(LPTABLESTRUCT pfield);

	//根据域类型获得相应字符串
	std::string GetTypeString(TABLE_DATA_TYPE gbkorutf);

protected:
	//mysql上下文
	MYSQL *mysql = 0;

	//结果集
	MYSQL_RES *result = 0;

	//字段名称和类型
	//std::vector<TData> cols;
};




#endif // !__TCLASS_MYSQL_H__


