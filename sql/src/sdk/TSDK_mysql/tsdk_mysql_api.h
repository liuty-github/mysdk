#ifndef __TSDK_MYSQL_API_H__
#define __TSDK_MYSQL_API_H__
#include "common/db_common.h"
 
typedef  void* TMYSQL_HANDLE;
//���ܣ���ʼ��SDK��ʹ��ʱ������һ�μ���
//��Σ���
//����ֵ���ɹ�����DB_SUCCESS��ʧ�ܷ��ض�Ӧ������
TEXPORTS DB_ERR tsdk_mysql_init();

//���ܣ�����ʼ��SDK���ͷ�SDKʱ����һ�μ���
//��Σ���
//����ֵ���ɹ�����DB_SUCCESS��ʧ�ܷ��ض�Ӧ������
TEXPORTS DB_ERR tsdk_mysql_finit();

//���ܣ��������ݿ����һ�������Ӧ1�����ӡ��ɴ������������������ͬ���ݿ�
//��Σ���
//����ֵ���������ݿ����
TEXPORTS TMYSQL_HANDLE tsdk_mysql_createinstance();

//���ܣ��ͷ����ݿ����ͬʱ�Ͽ�����
//��Σ�handle�������(ͨ��createinstance����)
//����ֵ���ɹ�����DB_SUCCESS��ʧ�ܷ��ض�Ӧ������
TEXPORTS DB_ERR tsdk_mysql_releaseinstance(TMYSQL_HANDLE handle);

//���ܣ��������ݿ�
//��Σ�handle:����, host:Ŀ�����ݿ�IP��ַ, user:�û���, pass:����, db:���ݿ�����, port:�˿�, flag:����֧�ֶ������
//����ֵ���ɹ�����DB_SUCCESS��ʧ�ܷ��ض�Ӧ������
TEXPORTS DB_ERR tsdk_mysql_connect(TMYSQL_HANDLE handle, const char*host, const char*user, const char*pass, const char*db, unsigned short port = 3306, unsigned long flag = 0);

//���ܣ��Ͽ�����(��δʵ��)
//��Σ�handle:����
//����ֵ���ɹ�����DB_SUCCESS��ʧ�ܷ��ض�Ӧ������
TEXPORTS DB_ERR tsdk_mysql_disConnect(TMYSQL_HANDLE handle);

//���ܣ��������ݿ�,������ɺ��Զ������������ݿ�
//��Σ�handle:����, dbname:���ݿ�����
//����ֵ���ɹ�����DB_SUCCESS��ʧ�ܷ��ض�Ӧ������
TEXPORTS DB_ERR tsdk_mysql_createdatabase(TMYSQL_HANDLE handle, std::string dbname);

//���ܣ�ɾ�����ݿ�
//��Σ�handle:����, dbname:���ݿ�����
//����ֵ���ɹ�����DB_SUCCESS��ʧ�ܷ��ض�Ӧ������
TEXPORTS DB_ERR tsdk_mysql_deletedatabase(TMYSQL_HANDLE handle, std::string dbname);

//���ܣ������� 
//��Σ�handle:����, tvector:��ͷ����(����push��ȥ��˳�����б�ͷ���д���), tablename:����, tabletype:���ֱ����ʽ(mysql��δʹ�ø�ֵ)
//����ֵ���ɹ�����DB_SUCCESS��ʧ�ܷ��ض�Ӧ������
TEXPORTS DB_ERR tsdk_mysql_createtable(TMYSQL_HANDLE handle, TTABLEVECTOR &tvector, std::string tablename, TABLE_TYPE tabletype = GBK);

//���ܣ�ɾ����
//��Σ�handle:����, tablename:����
//����ֵ���ɹ�����DB_SUCCESS��ʧ�ܷ��ض�Ӧ������
TEXPORTS DB_ERR tsdk_mysql_deletetable(TMYSQL_HANDLE handle, std::string tablename);

/***********************************************insert data*****************************************************/
//���ܣ�����Ƕ���������
//��Σ�handle:����, kv:��������(map��string��Ӧ������,TData��Ӧ��������), tablename:����
//����ֵ���ɹ�����DB_SUCCESS��ʧ�ܷ��ض�Ӧ������
TEXPORTS DB_ERR tsdk_mysql_Insert(TMYSQL_HANDLE handle, TDATAMAP &kv, std::string tablename);

//���ܣ��������������
//��Σ�handle:����, kv:��������(map��string��Ӧ������,TData��Ӧ��������), tablename:����
//����ֵ���ɹ�����DB_SUCCESS��ʧ�ܷ��ض�Ӧ������
TEXPORTS DB_ERR tsdk_mysql_InsertBin(TMYSQL_HANDLE handle, TDATAMAP &kv, std::string tablename);

/***********************************************delete data*****************************************************/
//���ܣ�ɾ��ָ��id������
//��Σ�handle:����, tablename:����, idname:����ID���ֶ�����, idnum:����IDֵ
//����ֵ���ɹ�����DB_SUCCESS��ʧ�ܷ��ض�Ӧ������
TEXPORTS DB_ERR tsdk_mysql_drop_with_id(TMYSQL_HANDLE handle, std::string tablename, std::string idname, std::string idnum);

//���ܣ�ɾ������ָ���ֶε�����
//��Σ�handle:����, tablename:����, fieldname:����, fielddata:������
//����ֵ���ɹ�����DB_SUCCESS��ʧ�ܷ��ض�Ӧ������
TEXPORTS DB_ERR tsdk_mysql_likedrop(TMYSQL_HANDLE handle, std::string tablename, std::string fieldname, std::string fielddata);

//���ܣ���ձ���������
//��Σ�handle:����, tablename:����, brecover:ɾ���������Ƿ�ɻָ�(��Ϊ���ɻָ��ٴβ�������������ID���´�1��ʼ; ��Ϊ�ɻָ��ٴβ�������ʱ����ID��ɾ��ǰID����һ����ʼ)
//����ֵ���ɹ�����DB_SUCCESS��ʧ�ܷ��ض�Ӧ������
TEXPORTS DB_ERR tsdk_mysql_drop_with_table(TMYSQL_HANDLE handle, std::string tablename, bool brecover = true);

/***********************************************update data*****************************************************/
//���ܣ���������
//��Σ�handle:����, kv:���µ�����, tablename:����, where:����ID����, idnum:����ID����
//����ֵ���ɹ�����DB_SUCCESS��ʧ�ܷ��ض�Ӧ������
TEXPORTS TUINT64 tsdk_mysql_update(TMYSQL_HANDLE handle, TDATAMAP &kv, std::string tablename, std::string where, std::string idnum);

//���ܣ����¶���������
//��Σ�handle:����, kv:���µ�����, tablename:����, where:����ID����, idnum:����ID����
//����ֵ���ɹ�����DB_SUCCESS��ʧ�ܷ��ض�Ӧ������
TEXPORTS TUINT64 tsdk_mysql_updatebin(TMYSQL_HANDLE handle, TDATAMAP &kv, std::string tablename, std::string where, std::string idnum);

/***********************************************serach data*****************************************************/
//���ܣ�����(����ָ��������ݣ���Ҫ��Ͻ������ȡ�ӿ�ʹ��)
//��Σ�handle:����, tablename:����
//����ֵ���ɹ�����DB_SUCCESS��ʧ�ܷ��ض�Ӧ������
TEXPORTS DB_ERR tsdk_mysql_select(TMYSQL_HANDLE handle, std::string tablename);

//ģ������(ģ������ĳ�������ָ���ֶε���,��Ҫ��Ͻ������ȡ�ӿ�ʹ��)
//��Σ�handle:����, tablename:����, fieldname:����, fielddata:������
//����ֵ���ɹ�����DB_SUCCESS��ʧ�ܷ��ض�Ӧ������
TEXPORTS DB_ERR tsdk_mysql_like(TMYSQL_HANDLE handle, std::string tablename, std::string fieldname, std::string fielddata);

//���ܣ��������ȡ-����ȫ�����(��tsdk_mysql_select��tsdk_mysql_like�����)
//��Σ�handle:����
//����ֵ���ɹ�����DB_SUCCESS��ʧ�ܷ��ض�Ӧ������
TEXPORTS DB_ERR tsdk_mysql_storeresult(TMYSQL_HANDLE handle);

//���ܣ��������ȡ-��ȡһ������(��tsdk_mysql_storeresult�����)
//��Σ�handle:����	���Σ�vdata:����������
//����ֵ���ɹ�����DB_SUCCESS��ʧ�ܷ��ض�Ӧ������
TEXPORTS DB_ERR tsdk_mysql_fetchrow(TMYSQL_HANDLE handle, TROW &row);

//���ܣ��������ȡ-��ʼ���ս����ͨ��Fetch��ȡ
//��Σ�handle:����
//����ֵ���ɹ�����DB_SUCCESS��ʧ�ܷ��ض�Ӧ������
TEXPORTS DB_ERR tsdk_mysql_useresult(TMYSQL_HANDLE handle);

//���ܣ��ͷŽ����ռ�õĿռ�,��ȡ��������ã��ͷ��ڴ�
//��Σ�handle:����
//����ֵ���ɹ�����DB_SUCCESS��ʧ�ܷ��ض�Ӧ������
TEXPORTS DB_ERR tsdk_mysql_freeresult(TMYSQL_HANDLE handle);

//���ܣ�����select,ֱ��ִ��select����ȡȫ�����
//��Σ�handle:����, tablename:����	���Σ�rows:����������
//����ֵ���ɹ�����DB_SUCCESS��ʧ�ܷ��ض�Ӧ������
TEXPORTS DB_ERR tsdk_mysql_easyselect(TMYSQL_HANDLE handle, std::string tablename, TROWS &rows);

//���ܣ�����ģ������,ֱ��ִ��ģ�����Ҳ���ȡȫ�����
//��Σ�handle:����, tablename:����, fieldname:����. fielddata:������	  ���Σ�rows:����������
//����ֵ���ɹ�����DB_SUCCESS��ʧ�ܷ��ض�Ӧ������
TEXPORTS DB_ERR tsdk_mysql_easylike(TMYSQL_HANDLE handle, std::string tablename, std::string fieldname, std::string fielddata, TROWS &rows);

/***************************************************�������*******************************************************/
//���ܣ��л����������ʽgbk or utf-8
//��Σ�handle:����, ttype:��������
//����ֵ���ɹ�����DB_SUCCESS��ʧ�ܷ��ض�Ӧ������
TEXPORTS DB_ERR tsdk_mysql_switchtype(TMYSQL_HANDLE handle, TABLE_TYPE ttype = GBK);

//���ܣ�ִ��sql���
//��Σ�handle:����, sql:sql���, sqllen:sql��䳤��(��0Ĭ���Զ���ȡsql��䳤��)
//����ֵ���ɹ�����DB_SUCCESS��ʧ�ܷ��ض�Ӧ������
TEXPORTS DB_ERR tsdk_mysql_query(TMYSQL_HANDLE handle, const char*sql, unsigned long sqllen = 0);

//���ܣ��������ӳ�ʱʱ��
//��Σ�handle������, sec:��ʱʱ��(��)
//����ֵ���ɹ�����DB_SUCCESS��ʧ�ܷ��ض�Ӧ������
TEXPORTS DB_ERR tsdk_mysql_setconnecttimeout(TMYSQL_HANDLE handle, int sec);

//���ܣ������Զ�������Ĭ�ϲ��Զ�
//��Σ�handle:����, isre:�Զ�������־
//����ֵ���ɹ�����DB_SUCCESS��ʧ�ܷ��ض�Ӧ������
TEXPORTS DB_ERR tsdk_mysql_setreconnect(TMYSQL_HANDLE handle, bool isre = true);

/***************************************************����ӿ�*******************************************************/
//���ܣ������������
//��Σ�handle:����
//����ֵ���ɹ�����DB_SUCCESS��ʧ�ܷ��ض�Ӧ������
TEXPORTS DB_ERR tsdk_mysql_starttransaction(TMYSQL_HANDLE handle);

//���ܣ�ֹͣ�������
//��Σ�handle:����
//����ֵ���ɹ�����DB_SUCCESS��ʧ�ܷ��ض�Ӧ������
TEXPORTS DB_ERR tsdk_mysql_stoptransaction(TMYSQL_HANDLE handle);

//���ܣ��ύ�������(���������, ִ��sql���������commit�ύִ��sql����rollback�ع�ǰ���sql�������������)
//��Σ�handle:����
//����ֵ���ɹ�����DB_SUCCESS��ʧ�ܷ��ض�Ӧ������
TEXPORTS DB_ERR tsdk_mysql_commit(TMYSQL_HANDLE handle);

//���ܣ��ع��������(ִ�лع�����ζ��ǰ�������sql����ȫ��ʧЧ)
//��Σ�handle:����
//����ֵ���ɹ�����DB_SUCCESS��ʧ�ܷ��ض�Ӧ������
TEXPORTS DB_ERR tsdk_mysql_rollback(TMYSQL_HANDLE handle);



#endif