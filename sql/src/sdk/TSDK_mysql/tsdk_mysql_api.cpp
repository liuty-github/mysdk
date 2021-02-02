#include "tsdk_mysql_api.h"
#include "common/db_tools.h"
#include "Tmysql.h"

TEXPORTS DB_ERR tsdk_mysql_init()
{

	Tprint("sdk init success!\n");
	return DB_SUCCESS;
}

TEXPORTS DB_ERR tsdk_mysql_finit()
{
	Tprint("sdk finit success!\n");
	return DB_SUCCESS;
}

TEXPORTS TMYSQL_HANDLE tsdk_mysql_createinstance()
{
	Tmysql *mysql_instance = new Tmysql();
	mysql_instance->Init();
	if (mysql_instance == NULL)
	{
		Tprint("create failed!\n");
	}
	Tprint("create instance success handle = %p\n", mysql_instance);
	return reinterpret_cast<TMYSQL_HANDLE>(mysql_instance);
}

TEXPORTS DB_ERR tsdk_mysql_releaseinstance(TMYSQL_HANDLE handle)
{
	CHECKHANDLE(handle);
	Tmysql *phandle = reinterpret_cast<Tmysql*>(handle);
	phandle->Finit();
	delete phandle;
	handle = NULL;
	Tprint("release instance success handle = %p\n", handle);
	return DB_SUCCESS;
}

TEXPORTS DB_ERR tsdk_mysql_connect(TMYSQL_HANDLE handle, const char*host, const char*user, const char*pass, const char*db, unsigned short port, unsigned long flag)
{
	CHECKHANDLE(handle);
	return ((Tmysql*)handle)->Connect(host, user, pass, db, port, flag);
}

TEXPORTS DB_ERR tsdk_mysql_disConnect(TMYSQL_HANDLE handle)
{
	CHECKHANDLE(handle);
	return DB_UNSUPPORT_COMMOND;
}
//�������ݿ�
TEXPORTS DB_ERR tsdk_mysql_createdatabase(TMYSQL_HANDLE handle, std::string dbname)
{
	CHECKHANDLE(handle);
	return ((Tmysql*)handle)->CreateDatabase(dbname);
}
//ɾ�����ݿ�
TEXPORTS DB_ERR tsdk_mysql_deletedatabase(TMYSQL_HANDLE handle, std::string dbname)
{
	CHECKHANDLE(handle);
	return ((Tmysql*)handle)->DeleteDatabase(dbname);
}

TEXPORTS DB_ERR tsdk_mysql_createtable(TMYSQL_HANDLE handle, TTABLEVECTOR &tvector, std::string tablename, TABLE_TYPE tabletype)
{
	CHECKHANDLE(handle);
	return ((Tmysql*)handle)->CreateTable(tvector, tablename, tabletype);
}

TEXPORTS DB_ERR tsdk_mysql_deletetable(TMYSQL_HANDLE handle, std::string tablename)
{
	CHECKHANDLE(handle);
	return ((Tmysql*)handle)->DeleteTable(tablename);
}

/***********************************************insert data*****************************************************/
//����Ƕ���������
TEXPORTS DB_ERR tsdk_mysql_Insert(TMYSQL_HANDLE handle, TDATAMAP &kv, std::string tablename)
{
	CHECKHANDLE(handle);
	return ((Tmysql*)handle)->Insert(kv, tablename);
} 

//�������������
TEXPORTS DB_ERR tsdk_mysql_InsertBin(TMYSQL_HANDLE handle, TDATAMAP &kv, std::string tablename)
{
	CHECKHANDLE(handle);
	return ((Tmysql*)handle)->InsertBin(kv, tablename);
}

/***********************************************delete data*****************************************************/
//ɾ��ָ��ID������
TEXPORTS DB_ERR tsdk_mysql_drop_with_id(TMYSQL_HANDLE handle, std::string tablename, std::string idname, std::string idnum)
{
	CHECKHANDLE(handle);
	return ((Tmysql*)handle)->DropWithId(tablename, idname, idnum);
}
//ɾ������ָ���ֶε�����
TEXPORTS DB_ERR tsdk_mysql_likedrop(TMYSQL_HANDLE handle, std::string tablename, std::string fieldname, std::string fielddata)
{
	CHECKHANDLE(handle);
	return ((Tmysql*)handle)->LikeDrop(tablename, fieldname, fielddata);
}
//��ձ�
TEXPORTS DB_ERR tsdk_mysql_drop_with_table(TMYSQL_HANDLE handle, std::string tablename, bool brecover)
{
	CHECKHANDLE(handle);
	return ((Tmysql*)handle)->DropWithTable(tablename, brecover);
}

/***********************************************update data*****************************************************/
//��������
TEXPORTS TUINT64 tsdk_mysql_update(TMYSQL_HANDLE handle, TDATAMAP &kv, std::string tablename, std::string where, std::string idnum)
{
	CHECKHANDLE(handle);
	return ((Tmysql*)handle)->Update(kv, tablename, where, idnum);
}
//���¶���������
TEXPORTS TUINT64 tsdk_mysql_updatebin(TMYSQL_HANDLE handle, TDATAMAP &kv, std::string tablename, std::string where, std::string idnum)
{
	CHECKHANDLE(handle);
	return ((Tmysql*)handle)->UpdateBin(kv, tablename, where, idnum);
}

/***********************************************serach data*****************************************************/
//��ȷ����
TEXPORTS DB_ERR tsdk_mysql_select(TMYSQL_HANDLE handle, std::string tablename)
{
	CHECKHANDLE(handle);
	return ((Tmysql*)handle)->Select(tablename);
}
//ģ������
TEXPORTS DB_ERR tsdk_mysql_like(TMYSQL_HANDLE handle, std::string tablename, std::string fieldname, std::string fielddata)
{
	CHECKHANDLE(handle);
	return ((Tmysql*)handle)->Like(tablename, fieldname, fielddata);
}
//�������ȡ
//����ȫ�����
TEXPORTS DB_ERR tsdk_mysql_storeresult(TMYSQL_HANDLE handle)
{
	CHECKHANDLE(handle);
	return ((Tmysql*)handle)->StoreResult();
}

//��ȡһ������
DB_ERR tsdk_mysql_fetchrow(TMYSQL_HANDLE handle, TROW &row)
{
	CHECKHANDLE(handle);
	row = ((Tmysql*)handle)->FetchRow();
	return DB_SUCCESS;
}

//��ʼ���ս����ͨ��Fetch��ȡ
TEXPORTS DB_ERR tsdk_mysql_useresult(TMYSQL_HANDLE handle)
{
	CHECKHANDLE(handle);
	return ((Tmysql*)handle)->UseResult();
}

//�ͷŽ����ռ�õĿռ�
TEXPORTS DB_ERR tsdk_mysql_freeresult(TMYSQL_HANDLE handle)
{
	CHECKHANDLE(handle);
	return ((Tmysql*)handle)->FreeResult();
}
TEXPORTS DB_ERR tsdk_mysql_easyselect(TMYSQL_HANDLE handle, std::string tablename, TROWS &rows)
{
	CHECKHANDLE(handle);
	return ((Tmysql*)handle)->EasySelect(tablename, rows);
}
TEXPORTS DB_ERR tsdk_mysql_easylike(TMYSQL_HANDLE handle, std::string tablename, std::string fieldname, std::string fielddata, TROWS &rows)
{
	CHECKHANDLE(handle);
	return ((Tmysql*)handle)->EasyLike(tablename, fieldname, fielddata, rows);
}

TEXPORTS DB_ERR tsdk_mysql_switchtype(TMYSQL_HANDLE handle, TABLE_TYPE ttype/* = UTF8 */)
{
	CHECKHANDLE(handle);
	return ((Tmysql*)handle)->SwitchType(ttype);
}
/***************************************************�������*******************************************************/
//���ӳ�ʱʱ��
TEXPORTS DB_ERR tsdk_mysql_setconnecttimeout(TMYSQL_HANDLE handle, int sec)
{
	CHECKHANDLE(handle);
	return ((Tmysql*)handle)->SetConnectTimeout(sec);
}

//�Զ�������Ĭ�ϲ��Զ�
TEXPORTS DB_ERR tsdk_mysql_setreconnect(TMYSQL_HANDLE handle, bool isre)
{
	CHECKHANDLE(handle);
	return ((Tmysql*)handle)->SetReconnect(isre);
}
//ִ��sql���  if sqllen=0 strlen��ȡ�ַ�����
TEXPORTS DB_ERR tsdk_mysql_query(TMYSQL_HANDLE handle, const char*sql, unsigned long sqllen)
{
	CHECKHANDLE(handle);
	return ((Tmysql*)handle)->Query(sql, sqllen) == true ? DB_SUCCESS : DB_FAILDE;
}

/***************************************************����ӿ�*******************************************************/
TEXPORTS DB_ERR tsdk_mysql_commit(TMYSQL_HANDLE handle)
{
	CHECKHANDLE(handle);
	return ((Tmysql*)handle)->Commit();
}

TEXPORTS DB_ERR tsdk_mysql_rollback(TMYSQL_HANDLE handle)
{
	CHECKHANDLE(handle);
	return ((Tmysql*)handle)->Rollback();
}
//����ӿ�
TEXPORTS DB_ERR tsdk_mysql_starttransaction(TMYSQL_HANDLE handle)
{
	CHECKHANDLE(handle);
	return ((Tmysql*)handle)->StartTransaction();
}

TEXPORTS DB_ERR tsdk_mysql_stoptransaction(TMYSQL_HANDLE handle)
{
	CHECKHANDLE(handle);
	return ((Tmysql*)handle)->StopTransaction();
}