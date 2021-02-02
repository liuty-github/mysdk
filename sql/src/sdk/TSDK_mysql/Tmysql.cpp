#include "Tmysql.h"
#include "common/db_tools.h"

#if defined( __WIN32__ ) || defined( WIN32 ) || defined( _WIN32 )
#pragma comment(lib,"libmysql.lib")
#endif

using namespace std;
DB_ERR Tmysql::Init()
{
	Finit();
	cout << "Tmysql::Init()" << endl;
	//新创建一个MYSQL 对象
	mysql = mysql_init(0);
	if (!mysql)
	{
		cerr << "mysql_init failed!" << endl;
		return DB_FAILDE;
	}
	Tprint("mysql_init success, mysql = %p",mysql);
	return DB_SUCCESS;
}

//清理占用的所有资源
DB_ERR Tmysql::Finit()
{
	FreeResult();

	if (mysql)
	{
		mysql_close(mysql);
		mysql = NULL;
		Tprint("Tmysql::finit()");
		return DB_SUCCESS;
	}
	return DB_FAILDE;
}

//创建数据库
DB_ERR Tmysql::CreateDatabase(std::string &dbname)
{
	if (dbname.empty())
	{
		Tprint("return %s", g_errstring[DB_INVALID_PARAM]);
		return DB_INVALID_PARAM;
	}
	//string sql = "CREATE DATABASE IF NOT EXISTS `" + dbname + "`";
	//return Query(sql.c_str()) ? DB_SUCCESS : DB_FAILDE;
	std::string queryStr = "create database if not exists ";
	queryStr += dbname;
	if (Query(queryStr.c_str()))
	{
		queryStr = "use ";
		queryStr += dbname;
		if (Query(queryStr.c_str()))
		{
			Tprint("database %s create success", dbname.c_str());
			return DB_SUCCESS;
		}
	}
	Tprint("database %s create faield", dbname.c_str());
	return DB_FAILDE;
}

//删除数据库
DB_ERR Tmysql::DeleteDatabase(std::string &dbname)
{
	if (dbname.empty())
	{
		Tprint("return %s", g_errstring[DB_INVALID_PARAM]);
		return DB_INVALID_PARAM;
	}
	std::string queryStr = "create database if not exists ";
	queryStr += dbname;
	if (Query(queryStr.c_str()))
	{
		queryStr = "drop database `";
		queryStr += dbname;
		queryStr += "`";
		if (Query(queryStr.c_str()))
		{
			Tprint("database %s delete success", dbname.c_str());
			return DB_SUCCESS;
		}
	}
	Tprint("database %s delete faield", dbname.c_str());
	return DB_FAILDE;
}

//数据库连接（不考虑线程安全） flag设置支持多条语句
DB_ERR Tmysql::Connect(const char*host, const char*user, const char*pass, const char*db, unsigned short port, unsigned long flag)
{
	if (!mysql && !Init())
	{
		cerr << "Mysql connect failed! msyql is not init!" << endl;
		return DB_FAILDE;
	}
	if (!mysql_real_connect(mysql, host, user, pass, db, port, 0, flag))
	{
		cerr << "Mysql connect failed!" << mysql_error(mysql) << endl;
		return DB_FAILDE;
	}
	Tprint("mysql connect success!");
	return DB_SUCCESS;
}

DB_ERR Tmysql::SwitchType(TABLE_TYPE ttype)
{
	bool bresult = false;
	string stype;
	switch (ttype)
	{
	case GBK:bresult = Query("set names gbk"); stype = "gbk"; break;
	case UTF8:bresult = Query("set names utf8"); stype = "utf8"; break;
	case NOTYPE:bresult = true; break;
	default:break;
	}
	Tprint("switchtype to %s return %s\n", stype.c_str(), g_errstring[bresult ? DB_SUCCESS : DB_FAILDE]);
	return bresult ? DB_SUCCESS : DB_FAILDE;
}

bool Tmysql::Query(const char*sql, unsigned long sqllen)
{
	if (!mysql)
	{
		Tprint( "Query failed:mysql is NULL" );
		return false;
	}
	if (!sql)
	{
		Tprint("sql is null" );
		return false;
	}
	if (sqllen <= 0)
		sqllen = (unsigned long)strlen(sql);
	if (sqllen <= 0)
	{
		Tprint("Query sql is empty or wrong format!" );
		return false;
	}

	int re = mysql_real_query(mysql, sql, sqllen);
	if (re != 0)
	{
		Tprint("mysql_real_query failed! error is:%s" , mysql_error(mysql) );
		return false;
	}
	return true;

}

//Mysql参数的设定
DB_ERR Tmysql::Options(LX_OPT opt, const void *arg)
{
	if (!mysql)
	{
		Tprint("Option failed:mysql is NULL" );
		return DB_FAILDE;
	}
	int re = mysql_options(mysql, (mysql_option)opt, arg);
	if (re != 0)
	{
		Tprint("mysql_options failed!error is:%s" , mysql_error(mysql) );
		return DB_FAILDE;
	}
	return DB_SUCCESS;
}

//连接超时时间
DB_ERR Tmysql::SetConnectTimeout(int sec)
{
	return Options(LX_OPT_CONNECT_TIMEOUT, &sec);
}

//自动重连，默认不自动
DB_ERR Tmysql::SetReconnect(bool isre)
{
	return Options(LX_OPT_RECONNECT, &isre);
}

//select
DB_ERR Tmysql::Select(std::string &tablename)
{
	if (tablename.empty())
	{
		Tprint("return %s", g_errstring[DB_INVALID_PARAM]);
		return DB_INVALID_PARAM;
	}
	string sql = "select * from " + tablename;
	return (Query(sql.c_str()) == true) ? DB_SUCCESS : DB_FAILDE;
}

//like
DB_ERR Tmysql::Like(std::string &tablename, std::string &fieldname, std::string &fielddata)
{
	if (tablename.empty() || fieldname.empty() || fielddata.empty())
	{
		Tprint("return %s", g_errstring[DB_INVALID_PARAM]);
		return DB_INVALID_PARAM;
	}
	string sql = "select * from " + tablename + " where " + fieldname + " like '%" + fielddata + "%'";
	return (Query(sql.c_str()) == true) ? DB_SUCCESS : DB_FAILDE;
}

//返回全部结果
DB_ERR Tmysql::StoreResult()
{
	if (!mysql)
	{
		Tprint("StoreResult failed:mysql is NULL" );
		return DB_FAILDE;
	}
	FreeResult();
	result = mysql_store_result(mysql);
	if (!result)
	{
		Tprint("mysql_store_result failed!error is:%s", mysql_error(mysql));
		return DB_FAILDE;
	}
	return DB_SUCCESS;
}

//开始接收结果，通过Fetch获取
DB_ERR Tmysql::UseResult()
{
	if (!mysql)
	{
		Tprint("UseResult failed:mysql is NULL");
		return DB_FAILDE;
	}
	FreeResult();
	result = mysql_use_result(mysql);
	if (!result)
	{
		Tprint("mysql_use_result failed!erorr is:%s", mysql_error(mysql));
		return DB_FAILDE;
	}
	return DB_SUCCESS;
}

//释放结果集占用的空间
DB_ERR Tmysql::FreeResult()
{
	if (result)
	{
		mysql_free_result(result);
		result = NULL;
		return DB_SUCCESS;
	}
	return DB_FAILDE;
}

//删除指定ID的数据
DB_ERR Tmysql::DropWithId(std::string &tablename, std::string &idname, std::string &idnum)
{
	//delete FROM A WHERE id = 'B' 
	if (tablename.empty() || idname.empty() || idnum.empty())
	{
		Tprint("return %s", g_errstring[DB_INVALID_PARAM]);
		return DB_INVALID_DATA;
	}
	string sql = "delete from " + tablename + " where " + idname + "=" + idnum;
	if (!Query(sql.c_str()))
	{
		Tprint("drop faield in table:%s, col:%s, data:%s\n", tablename.c_str(), idname.c_str(), idnum.c_str());
		return DB_FAILDE;
	}
	Tprint("drop success in table:%s, col:%s, data:%s\n", tablename.c_str(), idname.c_str(), idnum.c_str());
	return DB_SUCCESS;
}
//删除包含指定字段的数据
DB_ERR Tmysql::LikeDrop(std::string &tablename, std::string &fieldname, std::string &fielddata)
{
	//DELETE from tablename where 字段名 like '%字段值%'
	if (tablename.empty() || fieldname.empty() || fielddata.empty())
	{
		Tprint("return %s", g_errstring[DB_INVALID_PARAM]);
		return DB_INVALID_DATA;
	}
	string sql = "delete from " + tablename + " where `" + fieldname + "` like '%" + fielddata + "%'";
	if (!Query(sql.c_str()))
	{
		Tprint("drop faield in table:%s, col:%s, data:%s\n", tablename.c_str(), fieldname.c_str(), fielddata.c_str());
		return DB_FAILDE;
	}
	Tprint("drop success in table:%s, col:%s, data:%s\n", tablename.c_str(), fieldname.c_str(), fielddata.c_str());
	return DB_SUCCESS;
}
//清空表
DB_ERR Tmysql::DropWithTable(std::string &tablename, bool brecover)
{
	if (tablename.empty())
	{
		Tprint("return %s", g_errstring[DB_INVALID_PARAM]);
		return DB_INVALID_DATA;
	}
	//DELETE FROM `tablename`;可恢复
	//TRUNCATE TABLE `tablename`;不可恢复
	string sql = "";
	if (brecover == true)
	{
		sql += "DELETE FROM `";
	}
	else
	{
		sql += "TRUNCATE TABLE `";
	}
	sql += tablename;
	sql += "`";
	if (Query(sql.c_str()) == false)
	{
		Tprint("drop faield in table:%s", tablename.c_str());
		return DB_FAILDE;
	}
	Tprint("drop success in table:%s", tablename.c_str());
	return DB_SUCCESS;
}
//获取一行数据
TROW Tmysql::FetchRow()
{
	TROW re;
	if (!result)
	{
		Tprint("reult is null");
		return re;
	}
	MYSQL_ROW row = mysql_fetch_row(result);
	if (!row)
	{
		Tprint("row is null");
		return re;
	}

	//列数
	int num = mysql_num_fields(result);

	unsigned long *lens = mysql_fetch_lengths(result);
	for (int i = 0; i < num; i++)
	{
		TData data;
		data.data = row[i];
		data.size = lens[i];
		//获取列的类型
		auto field = mysql_fetch_field_direct(result, i);
		data.type = (FIELD_TYPE)field->type;
		re.push_back(data);
	}
	Tprint("return success");
	return re;
}

std::string Tmysql::GetTypeString(TABLE_DATA_TYPE gbkorutf)
{
	std::string typestring = g_datatype[gbkorutf];
	return typestring;
}

std::string Tmysql::GetCreateSql(LPTABLESTRUCT pfield)
{
	std::string fieldsql = "`" + pfield->fieldname + "` ";
	fieldsql += GetTypeString(pfield->type);
	if (pfield->len != 0)
	{
		fieldsql += "(";
		fieldsql += to_string(pfield->len);
		fieldsql += ")";
	}
	if (pfield->gbkorutf == GBK)
	{
		fieldsql += " CHARACTER SET gbk COLLATE gbk_bin";
	}
	else if (pfield->gbkorutf == UTF8)
	{
		fieldsql += " CHARACTER SET utf8 COLLATE utf8_bin";
	}
	else//NOTYPE才考虑是否将此字段设为自增ID
	{
		if (pfield->type == DBTYPE_ID)
		{
			fieldsql += ",PRIMARY KEY(`";
			fieldsql += pfield->fieldname;
			fieldsql += "`)";
		}
	}
	return fieldsql;
}

DB_ERR Tmysql::CreateTable(TTABLEVECTOR &tvector, std::string &tablename, TABLE_TYPE tabletype)
{
	if (tvector.empty() || tablename.empty() || tabletype > NOTYPE)
	{
		Tprint("return %s", g_errstring[DB_INVALID_PARAM]);
		return DB_INVALID_PARAM;
	}
	/*"CREATE TABLE IF NOT EXISTS `t_utf8` \
		(`id` INT AUTO_INCREMENT,	\
		`name` VARCHAR(1024) CHARACTER SET utf8 COLLATE utf8_bin,\
		PRIMARY KEY(`id`))";*/
	string sql = "CREATE TABLE IF NOT EXISTS `" + tablename + "` (";
	TTABLEVECTOR::iterator iter = tvector.begin();
	for (;iter != tvector.end(); ++iter)
	{
		sql += GetCreateSql(&(*iter));
		sql += ",";
	}
	sql[sql.size() - 1] = ' ';
	sql += ")";
	Tprint("%s\n", sql.c_str());
	return Query(sql.c_str()) == true ? DB_SUCCESS : DB_FAILDE;
}

DB_ERR Tmysql::DeleteTable(std::string &tablename)
{
	if (tablename.empty())
	{
		Tprint("return %s", g_errstring[DB_INVALID_PARAM]);
		return DB_INVALID_PARAM;
	}
	string sql = "DROP TABLE IF EXISTS `" + tablename + "`";
	return Query(sql.c_str()) == true ? DB_SUCCESS : DB_FAILDE;
}

//生成insert sql语句
std::string Tmysql::GetInsertSql(TDATAMAP &kv, std::string &tablename)
{
	string sql = "";
	sql = "insert into `";
	sql += tablename;
	sql += "`";
	//insert into t_video (name,size) values("name1","1024")
	string keys = "";
	string vals = "";

	//迭代map
	for (TDATAMAP::iterator ptr = kv.begin(); ptr != kv.end(); ptr++)
	{
		//字段名
		keys += "`";
		keys += ptr->first;
		keys += "`,";

		vals += "'";
		vals += ptr->second.data;
		vals += "',";
	}
	//去除多余的逗号
	keys[keys.size() - 1] = ' ';
	vals[vals.size() - 1] = ' ';

	sql += "(";
	sql += keys;
	sql += ")values(";
	sql += vals;
	sql += ")";
	return sql;
}
//插入非二进制数据
DB_ERR Tmysql::Insert(TDATAMAP &kv, std::string &tablename)
{
	if (kv.empty() || tablename.empty())
	{
		Tprint("return %s", g_errstring[DB_INVALID_PARAM]);
		return DB_INVALID_DATA;
	}
	if (!mysql)
	{
		Tprint("Insert failed:mysql is NULL");
		return DB_FAILDE;
	}
	string sql = GetInsertSql(kv, tablename);
	if (sql.empty())
		return DB_FAILDE;
	if (!Query(sql.c_str()))
		return DB_FAILDE;
	TUINT64 num = mysql_affected_rows(mysql);
	if (num <= 0)
		return DB_FAILDE;
	Tprint("return success");
	return DB_SUCCESS;
}
//插入二进制数据
DB_ERR Tmysql::InsertBin(TDATAMAP &kv, std::string &tablename)
{
	string sql = "";
	if (kv.empty() || tablename.empty() || !mysql)
	{
		Tprint("return %s", g_errstring[DB_INVALID_PARAM]);
		return DB_INVALID_PARAM;
	}
	sql = "insert into `";
	sql += tablename;
	sql += "`";
	//insert into t_video (name,size) values(?,?)
	string keys = "";
	string vals = "";
	//绑定字段
	MYSQL_BIND bind[256] = { 0 };
	int i = 0;
	//迭代map
	for (TDATAMAP::iterator ptr = kv.begin(); ptr != kv.end(); ptr++)
	{
		//字段名
		keys += "`";
		keys += ptr->first;
		keys += "`,";

		vals += "?,";
		bind[i].buffer = (char*)ptr->second.data;
		bind[i].buffer_length = ptr->second.size;
		bind[i].buffer_type = (enum_field_types)ptr->second.type;
		i++;
	}
	//去除多余的逗号
	keys[keys.size() - 1] = ' ';
	vals[vals.size() - 1] = ' ';

	sql += "(";
	sql += keys;
	sql += ")values(";
	sql += vals;
	sql += ")";
	//预处理SQL语句
	MYSQL_STMT *stmt = mysql_stmt_init(mysql);
	if (!stmt)
	{
		cerr << "mysql_stmt_init failed!" << mysql_error(mysql) << endl;
		return DB_FAILDE;
	}
	if (mysql_stmt_prepare(stmt, sql.c_str(), (unsigned long)(sql.length())) != 0)
	{
		mysql_stmt_close(stmt);
		cerr << "mysql_stmt_prepare failed!" << mysql_error(mysql) << endl;
		return DB_FAILDE;
	}

	if (mysql_stmt_bind_param(stmt, bind) != 0)
	{
		mysql_stmt_close(stmt);
		cerr << "mysql_stmt_bind_param failed!" << mysql_stmt_error(stmt) << endl;
		return DB_FAILDE;
	}
	if (mysql_stmt_execute(stmt) != 0)
	{
		mysql_stmt_close(stmt);
		cerr << "mysql_stmt_execute failed!" << mysql_stmt_error(stmt) << endl;
		return DB_FAILDE;
	}
	mysql_stmt_close(stmt);
	Tprint("return success");
	return DB_SUCCESS;
}

//获取更新数据的sql语句 where语句中，用户要包含where
std::string Tmysql::GetUpdateSql(TDATAMAP &kv, std::string &tablename, std::string &where, std::string &idnum)
{
	//update t_video set name='update001',size=1000 where id=10
	string sql = "";
	sql = "update `";
	sql += tablename;
	sql += "` set ";
	for (TDATAMAP::iterator ptr = kv.begin(); ptr != kv.end(); ptr++)
	{
		sql += "`";
		sql += ptr->first;
		sql += "`='";
		sql += ptr->second.data;
		sql += "',";
	}
	//去除多余的逗号
	sql[sql.size() - 1] = ' ';
	sql += " where ";
	sql += where;
	sql += "=";
	sql += idnum;
	return sql;
}

TUINT64 Tmysql::Update(TDATAMAP &kv, std::string &tablename, std::string &where, std::string &idnum)
{
	if (kv.empty() || tablename.empty() || where.empty())
	{
		Tprint("return %s", g_errstring[DB_INVALID_PARAM]);
		return -1;
	}
	if (!mysql)return -1;
	string sql = GetUpdateSql(kv, tablename, where, idnum);
	if (sql.empty())
		return -1;
	if (!Query(sql.c_str()))
	{
		return -1;
	}
	Tprint("return success");
	return mysql_affected_rows(mysql);
}

TUINT64 Tmysql::UpdateBin(TDATAMAP &kv, std::string &tablename, std::string &where, std::string &idnum)
{
	if (kv.empty() || tablename.empty() || where.empty())
	{
		Tprint("return %s", g_errstring[DB_INVALID_PARAM]);
		return -1;
	}
	if (!mysql || kv.empty() || tablename.empty())
	{
		return -1;
	}
	string sql = "";
	sql = "update `";
	sql += tablename;
	sql += "` set ";
	MYSQL_BIND bind[256] = { 0 };
	int i = 0;
	for (TDATAMAP::iterator ptr = kv.begin(); ptr != kv.end(); ptr++)
	{
		sql += "`";
		sql += ptr->first;
		sql += "`=?,";
		bind[i].buffer = (char*)ptr->second.data;
		bind[i].buffer_length = ptr->second.size;
		bind[i].buffer_type = (enum_field_types)ptr->second.type;
		i++;
	}
	//去除多余的逗号
	sql[sql.size() - 1] = ' ';
	sql += " where ";
	sql += where;
	sql += "=";
	sql += idnum;

	//预处理SQL语句上下文
	MYSQL_STMT *stmt = mysql_stmt_init(mysql);
	if (!stmt)
	{
		cerr << "mysql_stmt_init failed!" << mysql_error(mysql) << endl;
		return -1;
	}
	if (mysql_stmt_prepare(stmt, sql.c_str(), (unsigned long)(sql.length())) != 0)
	{
		mysql_stmt_close(stmt);
		cerr << "mysql_stmt_prepare failed!" << mysql_error(mysql) << endl;
		return -1;
	}

	if (mysql_stmt_bind_param(stmt, bind) != 0)
	{
		mysql_stmt_close(stmt);
		cerr << "mysql_stmt_bind_param failed!" << mysql_stmt_error(stmt) << endl;
		return -1;
	}
	if (mysql_stmt_execute(stmt) != 0)
	{
		mysql_stmt_close(stmt);
		cerr << "mysql_stmt_execute failed!" << mysql_stmt_error(stmt) << endl;
		return -1;
	}
	mysql_stmt_close(stmt);
	Tprint("return success");
	return mysql_stmt_affected_rows(stmt);
}


DB_ERR Tmysql::StartTransaction()
{
	return (Query("set autocommit=0")==true)?DB_SUCCESS:DB_FAILDE;
}

DB_ERR Tmysql::StopTransaction()
{
	return (Query("set autocommit=1") == true) ? DB_SUCCESS : DB_FAILDE;
}

DB_ERR Tmysql::Commit()
{
	return (Query("commit") == true) ? DB_SUCCESS : DB_FAILDE;

}
DB_ERR Tmysql::Rollback()
{
	return (Query("rollback") == true) ? DB_SUCCESS : DB_FAILDE;
}
//简易接口,返回select的数据结果，每次调用清理上一次的结果集
DB_ERR Tmysql::EasySelect(std::string &tablename, TROWS &rows)
{
	if (tablename.empty() || !(&rows))
	{
		Tprint("return %s", g_errstring[DB_INVALID_PARAM]);
		return DB_INVALID_PARAM;
	}
	string sql = "select * from " + tablename;
	FreeResult();
	if (!Query(sql.c_str()))
		return DB_FAILDE;
	if (StoreResult() != DB_SUCCESS)
		return DB_FAILDE;
	for (;;)
	{
		auto row = FetchRow();
		if (row.empty())break;
		rows.push_back(row);
	}
	Tprint("return success");
	return DB_SUCCESS;
}

DB_ERR Tmysql::EasyLike(std::string &tablename, std::string &fieldname, std::string &fielddata, TROWS &rows)
{
	if (tablename.empty() || fieldname.empty() || fielddata.empty() || !(&rows))
	{
		Tprint("return %s", g_errstring[DB_INVALID_PARAM]);
		return DB_INVALID_PARAM;
	}
	FreeResult();
	string sql = "select * from " + tablename + " where " + fieldname + " like '%" + fielddata + "%'";
	if (!Query(sql.c_str()))
		return DB_FAILDE;
	if (StoreResult() != DB_SUCCESS)
		return DB_FAILDE;
	for (;;)
	{
		auto row = FetchRow();
		if (row.empty())break;
		rows.push_back(row);
	}
	Tprint("return success");
	return DB_SUCCESS;
}