#ifndef __TSDK_MYSQL_API_H__
#define __TSDK_MYSQL_API_H__
#include "common/db_common.h"
 
typedef  void* TMYSQL_HANDLE;
//功能：初始化SDK，使用时仅调用一次即可
//入参：无
//返回值：成功返回DB_SUCCESS，失败返回对应错误码
TEXPORTS DB_ERR tsdk_mysql_init();

//功能：反初始化SDK，释放SDK时调用一次即可
//入参：无
//返回值：成功返回DB_SUCCESS，失败返回对应错误码
TEXPORTS DB_ERR tsdk_mysql_finit();

//功能：创建数据库对象，一个对象对应1个连接。可创建多个对象连接至不同数据库
//入参：无
//返回值：返回数据库对象
TEXPORTS TMYSQL_HANDLE tsdk_mysql_createinstance();

//功能：释放数据库对象，同时断开连接
//入参：handle库对象句柄(通过createinstance创建)
//返回值：成功返回DB_SUCCESS，失败返回对应错误码
TEXPORTS DB_ERR tsdk_mysql_releaseinstance(TMYSQL_HANDLE handle);

//功能：连接数据库
//入参：handle:库句柄, host:目标数据库IP地址, user:用户名, pass:密码, db:数据库名称, port:端口, flag:设置支持多条语句
//返回值：成功返回DB_SUCCESS，失败返回对应错误码
TEXPORTS DB_ERR tsdk_mysql_connect(TMYSQL_HANDLE handle, const char*host, const char*user, const char*pass, const char*db, unsigned short port = 3306, unsigned long flag = 0);

//功能：断开连接(暂未实现)
//入参：handle:库句柄
//返回值：成功返回DB_SUCCESS，失败返回对应错误码
TEXPORTS DB_ERR tsdk_mysql_disConnect(TMYSQL_HANDLE handle);

//功能：创建数据库,创建完成后将自动连接至该数据库
//入参：handle:库句柄, dbname:数据库名称
//返回值：成功返回DB_SUCCESS，失败返回对应错误码
TEXPORTS DB_ERR tsdk_mysql_createdatabase(TMYSQL_HANDLE handle, std::string dbname);

//功能：删除数据库
//入参：handle:库句柄, dbname:数据库名称
//返回值：成功返回DB_SUCCESS，失败返回对应错误码
TEXPORTS DB_ERR tsdk_mysql_deletedatabase(TMYSQL_HANDLE handle, std::string dbname);

//功能：创建表 
//入参：handle:库句柄, tvector:表头容器(按照push进去的顺序排列表头进行创建), tablename:表名, tabletype:汉字编码格式(mysql暂未使用该值)
//返回值：成功返回DB_SUCCESS，失败返回对应错误码
TEXPORTS DB_ERR tsdk_mysql_createtable(TMYSQL_HANDLE handle, TTABLEVECTOR &tvector, std::string tablename, TABLE_TYPE tabletype = GBK);

//功能：删除表
//入参：handle:库句柄, tablename:表名
//返回值：成功返回DB_SUCCESS，失败返回对应错误码
TEXPORTS DB_ERR tsdk_mysql_deletetable(TMYSQL_HANDLE handle, std::string tablename);

/***********************************************insert data*****************************************************/
//功能：插入非二进制数据
//入参：handle:库句柄, kv:插入数据(map的string对应表域名,TData对应插入数据), tablename:表名
//返回值：成功返回DB_SUCCESS，失败返回对应错误码
TEXPORTS DB_ERR tsdk_mysql_Insert(TMYSQL_HANDLE handle, TDATAMAP &kv, std::string tablename);

//功能：插入二进制数据
//入参：handle:库句柄, kv:插入数据(map的string对应表域名,TData对应插入数据), tablename:表名
//返回值：成功返回DB_SUCCESS，失败返回对应错误码
TEXPORTS DB_ERR tsdk_mysql_InsertBin(TMYSQL_HANDLE handle, TDATAMAP &kv, std::string tablename);

/***********************************************delete data*****************************************************/
//功能：删除指定id的数据
//入参：handle:库句柄, tablename:表名, idname:自增ID的字段名称, idnum:自增ID值
//返回值：成功返回DB_SUCCESS，失败返回对应错误码
TEXPORTS DB_ERR tsdk_mysql_drop_with_id(TMYSQL_HANDLE handle, std::string tablename, std::string idname, std::string idnum);

//功能：删除包含指定字段的数据
//入参：handle:库句柄, tablename:表名, fieldname:域名, fielddata:域数据
//返回值：成功返回DB_SUCCESS，失败返回对应错误码
TEXPORTS DB_ERR tsdk_mysql_likedrop(TMYSQL_HANDLE handle, std::string tablename, std::string fieldname, std::string fielddata);

//功能：清空表所有数据
//入参：handle:库句柄, tablename:表名, brecover:删除后数据是否可恢复(若为不可恢复再次插入数据则自增ID重新从1开始; 若为可恢复再次插入数据时自增ID从删除前ID的下一个开始)
//返回值：成功返回DB_SUCCESS，失败返回对应错误码
TEXPORTS DB_ERR tsdk_mysql_drop_with_table(TMYSQL_HANDLE handle, std::string tablename, bool brecover = true);

/***********************************************update data*****************************************************/
//功能：更新数据
//入参：handle:库句柄, kv:更新的数据, tablename:表名, where:自增ID域名, idnum:自增ID数字
//返回值：成功返回DB_SUCCESS，失败返回对应错误码
TEXPORTS TUINT64 tsdk_mysql_update(TMYSQL_HANDLE handle, TDATAMAP &kv, std::string tablename, std::string where, std::string idnum);

//功能：更新二进制数据
//入参：handle:库句柄, kv:更新的数据, tablename:表名, where:自增ID域名, idnum:自增ID数字
//返回值：成功返回DB_SUCCESS，失败返回对应错误码
TEXPORTS TUINT64 tsdk_mysql_updatebin(TMYSQL_HANDLE handle, TDATAMAP &kv, std::string tablename, std::string where, std::string idnum);

/***********************************************serach data*****************************************************/
//功能：查找(查找指定表的数据，需要配合结果集获取接口使用)
//入参：handle:库句柄, tablename:表名
//返回值：成功返回DB_SUCCESS，失败返回对应错误码
TEXPORTS DB_ERR tsdk_mysql_select(TMYSQL_HANDLE handle, std::string tablename);

//模糊查找(模糊查找某个域包含指定字段的行,需要配合结果集获取接口使用)
//入参：handle:库句柄, tablename:表名, fieldname:域名, fielddata:域数据
//返回值：成功返回DB_SUCCESS，失败返回对应错误码
TEXPORTS DB_ERR tsdk_mysql_like(TMYSQL_HANDLE handle, std::string tablename, std::string fieldname, std::string fielddata);

//功能：结果集获取-返回全部结果(在tsdk_mysql_select或tsdk_mysql_like后调用)
//入参：handle:库句柄
//返回值：成功返回DB_SUCCESS，失败返回对应错误码
TEXPORTS DB_ERR tsdk_mysql_storeresult(TMYSQL_HANDLE handle);

//功能：结果集获取-获取一行数据(在tsdk_mysql_storeresult后调用)
//入参：handle:库句柄	出参：vdata:结果存放容器
//返回值：成功返回DB_SUCCESS，失败返回对应错误码
TEXPORTS DB_ERR tsdk_mysql_fetchrow(TMYSQL_HANDLE handle, TROW &row);

//功能：结果集获取-开始接收结果，通过Fetch获取
//入参：handle:库句柄
//返回值：成功返回DB_SUCCESS，失败返回对应错误码
TEXPORTS DB_ERR tsdk_mysql_useresult(TMYSQL_HANDLE handle);

//功能：释放结果集占用的空间,获取完结果后调用，释放内存
//入参：handle:库句柄
//返回值：成功返回DB_SUCCESS，失败返回对应错误码
TEXPORTS DB_ERR tsdk_mysql_freeresult(TMYSQL_HANDLE handle);

//功能：简易select,直接执行select并获取全部结果
//入参：handle:库句柄, tablename:表名	出参：rows:结果存放容器
//返回值：成功返回DB_SUCCESS，失败返回对应错误码
TEXPORTS DB_ERR tsdk_mysql_easyselect(TMYSQL_HANDLE handle, std::string tablename, TROWS &rows);

//功能：简易模糊查找,直接执行模糊查找并获取全部结果
//入参：handle:库句柄, tablename:表名, fieldname:域名. fielddata:域数据	  出参：rows:结果存放容器
//返回值：成功返回DB_SUCCESS，失败返回对应错误码
TEXPORTS DB_ERR tsdk_mysql_easylike(TMYSQL_HANDLE handle, std::string tablename, std::string fieldname, std::string fielddata, TROWS &rows);

/***************************************************设置相关*******************************************************/
//功能：切换工作编码格式gbk or utf-8
//入参：handle:库句柄, ttype:编码类型
//返回值：成功返回DB_SUCCESS，失败返回对应错误码
TEXPORTS DB_ERR tsdk_mysql_switchtype(TMYSQL_HANDLE handle, TABLE_TYPE ttype = GBK);

//功能：执行sql语句
//入参：handle:库句柄, sql:sql语句, sqllen:sql语句长度(传0默认自动获取sql语句长度)
//返回值：成功返回DB_SUCCESS，失败返回对应错误码
TEXPORTS DB_ERR tsdk_mysql_query(TMYSQL_HANDLE handle, const char*sql, unsigned long sqllen = 0);

//功能：设置连接超时时间
//入参：handle；库句柄, sec:超时时间(秒)
//返回值：成功返回DB_SUCCESS，失败返回对应错误码
TEXPORTS DB_ERR tsdk_mysql_setconnecttimeout(TMYSQL_HANDLE handle, int sec);

//功能：设置自动重连，默认不自动
//入参：handle:库句柄, isre:自动重连标志
//返回值：成功返回DB_SUCCESS，失败返回对应错误码
TEXPORTS DB_ERR tsdk_mysql_setreconnect(TMYSQL_HANDLE handle, bool isre = true);

/***************************************************事务接口*******************************************************/
//功能：开启事务操作
//入参：handle:库句柄
//返回值：成功返回DB_SUCCESS，失败返回对应错误码
TEXPORTS DB_ERR tsdk_mysql_starttransaction(TMYSQL_HANDLE handle);

//功能：停止事务操作
//入参：handle:库句柄
//返回值：成功返回DB_SUCCESS，失败返回对应错误码
TEXPORTS DB_ERR tsdk_mysql_stoptransaction(TMYSQL_HANDLE handle);

//功能：提交事务操作(事务操作中, 执行sql语句后必须以commit提交执行sql语句或rollback回滚前面的sql语句来结束操作)
//入参：handle:库句柄
//返回值：成功返回DB_SUCCESS，失败返回对应错误码
TEXPORTS DB_ERR tsdk_mysql_commit(TMYSQL_HANDLE handle);

//功能：回滚事务操作(执行回滚后，意味着前面的所有sql操作全部失效)
//入参：handle:库句柄
//返回值：成功返回DB_SUCCESS，失败返回对应错误码
TEXPORTS DB_ERR tsdk_mysql_rollback(TMYSQL_HANDLE handle);



#endif