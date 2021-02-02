#ifndef __TCLASS_MYSQL_H__
#define __TCLASS_MYSQL_H__
#include "common/db_common.h"
#include "Tmysql_type.h"
#include <common/mysql_include/mysql.h>

class Tmysql
{
public:
	//��ʼ��Mysql API
	DB_ERR Init();

	//����ռ�õ�������Դ
	DB_ERR Finit();

	//���ݿ����ӣ��������̰߳�ȫ�� flag����֧�ֶ������
	DB_ERR Connect(const char*host, const char*user, const char*pass, const char*db, unsigned short port = 3306, unsigned long flag = 0);

	//�������ݿ�
	DB_ERR CreateDatabase(std::string &dbname);

	//ɾ�����ݿ�
	DB_ERR DeleteDatabase(std::string &dbname);

	//������
	DB_ERR CreateTable(TTABLEVECTOR &tvector, std::string &tablename, TABLE_TYPE tabletype);

	//ɾ����
	DB_ERR DeleteTable(std::string &tablename);

	/*****************************************��**************************************************/
	//����Ƕ���������
	DB_ERR Insert(TDATAMAP &kv, std::string &tablename);

	//�������������
	DB_ERR InsertBin(TDATAMAP &kv, std::string &tablename);

	/*****************************************ɾ**************************************************/
	//ɾ��ָ��ID������
	DB_ERR DropWithId(std::string &tablename, std::string &idname, std::string &idnum);

	//ɾ������ָ���ֶε�����
	DB_ERR LikeDrop(std::string &tablename, std::string &fieldname, std::string &fielddata);

	//��ձ�,berecover��true,��պ󲻿ɻָ�;��false��պ󲻿ɻָ�
	DB_ERR DropWithTable(std::string &tablename, bool brecover = true);

	/*****************************************��**************************************************/
	//���ظ���������ʧ�ܷ���-1
	TUINT64 Update(TDATAMAP &kv, std::string &tablename, std::string &where, std::string &idnum);

	//���¶���������
	TUINT64 UpdateBin(TDATAMAP &kv, std::string &tablename, std::string &where, std::string &idnum);

	/*****************************************��**************************************************/
	//select from���,��Ͻ�����ӿ�ʹ��
	DB_ERR Select(std::string &tablename);

	//like ģ�����ң���Ͻ�����ӿ�ʹ��
	DB_ERR Like(std::string &tablename, std::string &fieldname, std::string &fielddata);

	//�������ȡ����ȫ�����
	DB_ERR StoreResult();

	//��ʼ���ս����ͨ��Fetch��ȡ
	DB_ERR UseResult();

	//�ͷŽ����ռ�õĿռ�
	DB_ERR FreeResult();

	//��ȡһ������
	TROW FetchRow();

	//���׽ӿ�,����select�����ݽ����ÿ�ε���������һ�εĽ����
	DB_ERR EasySelect(std::string &tablename, TROWS &rows);

	//���׽ӿڣ�ģ������
	DB_ERR EasyLike(std::string &tablename, std::string &fieldname,std::string &fielddata, TROWS &rows);

	/*****************************************����************************************************/
	//�л�mysql��ǰ�����ʽ
	DB_ERR SwitchType(TABLE_TYPE ttype);

	//Mysql�������趨 Connect֮ǰ����
	DB_ERR Options(LX_OPT opt, const void *arg);

	//���ӳ�ʱʱ��
	DB_ERR SetConnectTimeout(int sec);

	//�Զ�������Ĭ�ϲ��Զ�
	DB_ERR SetReconnect(bool isre = true);

	/*****************************************����************************************************/
	//��ʼ����
	DB_ERR StartTransaction();

	//��������
	DB_ERR StopTransaction();

	//�ύ
	DB_ERR Commit();

	//�ع�
	DB_ERR Rollback();

	//ִ��sql���  if sqllen=0 strlen��ȡ�ַ�����
	bool Query(const char*sql, unsigned long sqllen = 0);

private:
	//����insert sql���
	std::string GetInsertSql(TDATAMAP &kv, std::string &tablename);

	//��ȡ�������ݵ�sql��� where����У��û�Ҫ����where
	std::string GetUpdateSql(TDATAMAP &kv, std::string &tablename, std::string &where, std::string &idnum);

	//���ݽṹ���ȡ�������Ӧ���sql���
	std::string GetCreateSql(LPTABLESTRUCT pfield);

	//���������ͻ����Ӧ�ַ���
	std::string GetTypeString(TABLE_DATA_TYPE gbkorutf);

protected:
	//mysql������
	MYSQL *mysql = 0;

	//�����
	MYSQL_RES *result = 0;

	//�ֶ����ƺ�����
	//std::vector<TData> cols;
};




#endif // !__TCLASS_MYSQL_H__


