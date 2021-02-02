#ifndef __TDBCOMMON_H__
#define __TDBCOMMON_H__
#include "tdefine.h"

//表字段类型
enum TABLE_DATA_TYPE {
			DBTYPE_INT = 0,
			DBTYPE_VARCHAR,
			DBTYPE_DATETIME,
			DBTYPE_BLOB,
			DBTYPE_BINARY,
			DBTYPE_LONGBLOB,
			DBTYPE_MEDIUMBLOB,
			DBTYPE_TINYBLOB,//255
			DBTYPE_VARBINARY,
			DBTYPE_DATA,
			DBTYPE_TIME,
			DBTYPE_TIMESTAMP,
			DBTYPE_YEAR,
			DBTYPE_GEOMETRY,
			DBTYPE_GEOMETRYCOLLECTION,
			DBTYPE_LINESTRING,
			DBTYPE_MULTILINESTRING,
			DBTYPE_MULTIPOINT,
			DBTYPE_POINT,
			DBTYPE_POLYGON,
			DBTYPE_BIGINT,
			DBTYPE_DECIMAL,
			DBTYPE_DOUBLE,
			DBTYPE_FLOAT,
			DBTYPE_MEDIUMINT,
			DBTYPE_REAL,
			DBTYPE_SMALLINT,
			DBTYPE_TINYINT,
			DBTYPE_CHAR,
			DBTYPE_JSON,
			DBTYPE_NCHAR,
			DBTYPE_NVARCHAR,
			DBTYPE_LONGTEXT,
			DBTYPE_MEDIUMTEXT,
			DBTYPE_TEXT,
			DBTYPE_TINYTEXT,
			DBTYPE_BIT,
			DBTYPE_BOOLEAN,
			DBTYPE_ENUM,
			DBTYPE_SET,
			DBTYPE_ID
};

//错误码
typedef enum
{
	DB_SUCCESS = 0,
	DB_FAILDE,
	DB_UNSUPPORT_COMMOND,
	DB_INVALID_PARAM,
	DB_INVALID_DATA
}DB_ERR;
//错误码翻译
static const char *g_errstring[30] = {
			"DB_SUCCESS",
			"DB_FAILDE",
			"DB_UNSUPPORT_COMMOND",
			"DB_INVALID_PARAM",
			"DB_INVALID_DATA"};
//数据类型
enum FIELD_TYPE {
	LX_TYPE_DECIMAL,
	LX_TYPE_TINY,
	LX_TYPE_SHORT,
	LX_TYPE_LONG,
	LX_TYPE_FLOAT,
	LX_TYPE_DOUBLE,
	LX_TYPE_NULL,
	LX_TYPE_TIMESTAMP,
	LX_TYPE_LONGLONG,
	LX_TYPE_INT24,
	LX_TYPE_DATE,
	LX_TYPE_TIME,
	LX_TYPE_DATETIME,
	LX_TYPE_YEAR,
	LX_TYPE_NEWDATE, /**< Internal to MySQL. Not used in protocol */
	LX_TYPE_VARCHAR,
	LX_TYPE_BIT,
	LX_TYPE_TIMESTAMP2,
	LX_TYPE_DATETIME2, /**< Internal to MySQL. Not used in protocol */
	LX_TYPE_TIME2,     /**< Internal to MySQL. Not used in protocol */
	LX_TYPE_JSON = 245,
	LX_TYPE_NEWDECIMAL = 246,
	LX_TYPE_ENUM = 247,
	LX_TYPE_SET = 248,
	LX_TYPE_TINY_BLOB = 249,
	LX_TYPE_MEDIUM_BLOB = 250,
	LX_TYPE_LONG_BLOB = 251,
	LX_TYPE_BLOB = 252,
	LX_TYPE_VAR_STRING = 253,
	LX_TYPE_STRING = 254,
	LX_TYPE_GEOMETRY = 255
};
//数据结构体
struct TData
{  
	TData(const char* data = 0)
	{
		this->type = LX_TYPE_STRING;
		if (!data)return;
		this->data = data;
		this->size = (unsigned int)strlen(data);
	}
	TData(const TUINT32 *d)
	{
		this->type = LX_TYPE_LONG;
		this->data = (const char*)d;
		this->size = sizeof(TUINT32);
	}
	const char * data = 0;
	unsigned int size = 0;
	FIELD_TYPE type;
};

typedef enum
{
	UTF8 = 0,
	GBK,
	NOTYPE
}TABLE_TYPE;
//表域结构体
typedef struct
{
	std::string fieldname;//字段名称
	TABLE_DATA_TYPE type;//字段类型
	TABLE_TYPE gbkorutf = NOTYPE;//编码格式
	int len = 0;//字段长度
}TABLESTRUCT, *LPTABLESTRUCT;

//创建表时传入的表结构
typedef std::vector <TABLESTRUCT>			TTABLEVECTOR;

//插入和更新数据的数据结构,string字段名称,TData字段数据
typedef std::map <std::string, TData>		TDATAMAP;

//存放数据库内一行数据的容器，容器元素为每个域的值
typedef std::vector<TData>					TROW;

//数据列表, 在使用简易查询接口时会一次性获取所有查询的数据。容器内元素为数据库内的一行数据
typedef std::vector<TROW>					TROWS;
#endif