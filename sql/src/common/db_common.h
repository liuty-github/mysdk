#ifndef __TDBCOMMON_H__
#define __TDBCOMMON_H__
#include "tdefine.h"

//���ֶ�����
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

//������
typedef enum
{
	DB_SUCCESS = 0,
	DB_FAILDE,
	DB_UNSUPPORT_COMMOND,
	DB_INVALID_PARAM,
	DB_INVALID_DATA
}DB_ERR;
//�����뷭��
static const char *g_errstring[30] = {
			"DB_SUCCESS",
			"DB_FAILDE",
			"DB_UNSUPPORT_COMMOND",
			"DB_INVALID_PARAM",
			"DB_INVALID_DATA"};
//��������
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
//���ݽṹ��
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
//����ṹ��
typedef struct
{
	std::string fieldname;//�ֶ�����
	TABLE_DATA_TYPE type;//�ֶ�����
	TABLE_TYPE gbkorutf = NOTYPE;//�����ʽ
	int len = 0;//�ֶγ���
}TABLESTRUCT, *LPTABLESTRUCT;

//������ʱ����ı�ṹ
typedef std::vector <TABLESTRUCT>			TTABLEVECTOR;

//����͸������ݵ����ݽṹ,string�ֶ�����,TData�ֶ�����
typedef std::map <std::string, TData>		TDATAMAP;

//������ݿ���һ�����ݵ�����������Ԫ��Ϊÿ�����ֵ
typedef std::vector<TData>					TROW;

//�����б�, ��ʹ�ü��ײ�ѯ�ӿ�ʱ��һ���Ի�ȡ���в�ѯ�����ݡ�������Ԫ��Ϊ���ݿ��ڵ�һ������
typedef std::vector<TROW>					TROWS;
#endif