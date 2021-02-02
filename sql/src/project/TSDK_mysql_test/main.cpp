#include "sdk/TSDK_mysql/tsdk_mysql_api.h"
#include "common/db_tools.h"
#include <iostream>
#if TPLATFORM == TWIN
#pragma comment(lib,"TSDK_mysql.lib")
#endif
static TMYSQL_HANDLE _handle_ = NULL;
using namespace std;
void init()
{
	tsdk_mysql_init();
	_handle_ = tsdk_mysql_createinstance();
	democonncet:
	char ip[20] = { 0 };
	char user[20] = { 0 };
	char passwd[20] = { 0 };
	char dbname[20] = { 0 };
	cout << "first,I want to get some details about your mysql which you will connect" << endl;
	cout << "input your mysql ipaddress:" << ""; cin >> ip;
	cout << "input your mysql user name:" << ""; cin >> user;
	cout << "input your mysql password:" << ""; cin >> passwd;
	cout << "input your mysql database name:" << ""; cin >> dbname;
	DB_ERR ret = tsdk_mysql_connect(_handle_, ip, user, passwd, dbname);
	if (ret == DB_SUCCESS)
	{
		cout << "*********************************demo init success*********************************" << endl;
	}
	else
	{
		cout << "*********************************demo init failed*********************************" << endl;
		goto democonncet;
	}
}
void finit()
{
	tsdk_mysql_disConnect(_handle_);
	DB_ERR ret = tsdk_mysql_releaseinstance(_handle_);
	if (ret == DB_SUCCESS)
	{
		cout << "*********************************demo finit success*********************************" << endl;
	}
	else
	{
		cout << "*********************************demo finit failed*********************************" << endl;
	}
}
void createdtable()
{
	tsdk_mysql_deletetable(_handle_, "testdb");
	TTABLEVECTOR mytable;
	TABLESTRUCT a0;
	a0.fieldname = "Num";
	a0.type = DBTYPE_ID;
	mytable.push_back(a0);

	TABLESTRUCT a1;
	a1.fieldname = "filetype";
	a1.type = DBTYPE_VARCHAR;
	a1.gbkorutf = GBK;
	a1.len = 128;
	mytable.push_back(a1);

	TABLESTRUCT a2;
	a2.fieldname = "fieldata";
	a2.type = DBTYPE_VARCHAR;
	a2.len = 1024;
	mytable.push_back(a2);

	TABLESTRUCT a3;
	a3.fieldname = "shuoming";
	a3.type = DBTYPE_VARCHAR;
	a3.len = 128;
	mytable.push_back(a3);

	TABLESTRUCT a4;
	a4.fieldname = "shuoming2";
	a4.type = DBTYPE_VARCHAR;
	a4.len = 128;
	mytable.push_back(a4);

	DB_ERR ret = tsdk_mysql_createtable(_handle_, mytable, "testdb");
	if (ret == DB_SUCCESS)
	{
		cout << "*********************************create testdb success*********************************" << endl;
	}
	else
	{
		cout << "*********************************create testdb failed*********************************" << endl;
	}
}
void insertdata()
{
	DB_ERR ret;
	tsdk_mysql_switchtype(_handle_, GBK);
	for (int i = 0; i < 20; ++i)
	{
		TDATAMAP k;
		k["filetype"] = "文字";
		char szbufp[12] = { 0 };
		sprintf(szbufp, "%d", i);
		k["fieldata"] = szbufp;
		k["shuoming"] = "shuoming111";
		k["shuoming2"] = "shuoming222";
		ret = tsdk_mysql_Insert(_handle_, k, "testdb");
	}
	TROWS rows;
	tsdk_mysql_easyselect(_handle_, "testdb", rows);
	TROWS::iterator iter = rows.begin();
	for (auto row : rows)
	{
		//遍历每一列
		for (auto c : row)
		{
			if (c.data) cout << c.data << " ";
		}
		cout << endl;
	}
	if (ret == DB_SUCCESS)
	{
		cout << "*********************************insert data success*********************************" << endl;
	}
	else
	{
		cout << "*********************************insert data failed*********************************" << endl;
	}
}
void updatedata()
{
	TDATAMAP k2;
	k2["filetype"] = "文字";
	char szbufp[12] = { 0 };
	sprintf(szbufp, "%d", 6666);
	k2["fieldata"] = szbufp;
	k2["shuoming"] = "shuoming111";
	k2["shuoming2"] = "shuoming222";
	TUINT64 ret = tsdk_mysql_update(_handle_, k2, "testdb", "Num", "9");
	
	tsdk_mysql_select(_handle_, "testdb");
	tsdk_mysql_storeresult(_handle_);
	while (true)
	{
		TROW rowdata;
		tsdk_mysql_fetchrow(_handle_, rowdata);
		if (rowdata.empty())
		{
			break;
		}
		TROW::iterator iter = rowdata.begin();
		for (; iter != rowdata.end(); ++iter)
		{
			cout << (*iter).data << " ";
		}
		cout << endl;
	}
	tsdk_mysql_freeresult(_handle_);
	if (ret > 0)
	{
		cout << "*********************************update data success*********************************" << endl;
		cout << "*********************************I change the date in Num9*********************************" << endl;
	}
	else
	{
		cout << "*********************************update data failed*********************************" << endl;
	}
}
void createdtable_bin()
{
	tsdk_mysql_deletetable(_handle_, "testdb_bin");


	TTABLEVECTOR mytable;
	TABLESTRUCT a0;
	a0.fieldname = "num";
	a0.type = DBTYPE_ID;
	mytable.push_back(a0);

	TABLESTRUCT a1;
	a1.fieldname = "filename";
	a1.type = DBTYPE_VARCHAR;
	a1.gbkorutf = UTF8;
	a1.len = 128;
	mytable.push_back(a1);

	TABLESTRUCT a2;
	a2.fieldname = "len";
	a2.type = DBTYPE_VARCHAR;
	a2.len = 20;
	mytable.push_back(a2);

	TABLESTRUCT a3;
	a3.fieldname = "data";
	a3.type = DBTYPE_BLOB;
	mytable.push_back(a3);

	DB_ERR ret = tsdk_mysql_createtable(_handle_, mytable, "testdb_bin");
	if (ret == DB_SUCCESS)
	{
		cout << "*********************************create testdb_bin success*********************************" << endl;
	}
	else
	{
		cout << "*********************************create testdb_bin failed*********************************" << endl;
	}
}
void insertdata_bin()
{
	tsdk_mysql_drop_with_table(_handle_, "testdb_bin", false);

	TUINT32 len = 0;
	char filepath[50] = { 0 };
	cout << "input your file path:" << ""; cin >> filepath;

	char *pdata = LoadFile(filepath, len);

	TDATAMAP k;
	k["filename"] = filepath;
	k["len"] = &len;
	TData picdata;
	picdata.data = pdata;
	picdata.size = len;
	picdata.type = LX_TYPE_STRING;
	k["data"] = picdata;
	DB_ERR ret = tsdk_mysql_InsertBin(_handle_, k, "testdb_bin");
	if (ret == DB_SUCCESS)
	{
		cout << "*********************************insert bin data success*********************************" << endl;
	}
	else
	{
		cout << "*********************************insert bin data failed*********************************" << endl;
	}

	memset(filepath, 0, sizeof(filepath));
	cout << "input your new file path:" << ""; cin >> filepath;

	TROWS rows;
	tsdk_mysql_easylike(_handle_, "testdb_bin", "num", "1", rows);
	TROW row = rows[0];
	TUINT64 size = row[3].size;
	const char *pdatasave = row[3].data;
	SaveFile(filepath, pdatasave, size);
}
void updatedata_bin()
{
	TUINT32 len = 0;
	char filepath[50] = { 0 };
	cout << "input your update file path:" << ""; cin >> filepath;
	char *pdata = LoadFile(filepath, len);
	char sznum[20] = { 0 };
	sprintf(sznum, "%d", len);
	TDATAMAP k;
	k["filename"] = filepath;
	k["len"] = &len;
	TData picdata;
	picdata.data = pdata;
	picdata.size = len;
	picdata.type = LX_TYPE_STRING;
	k["data"] = picdata;
	TUINT64 ret = tsdk_mysql_updatebin(_handle_, k, "testdb_bin", "num", "1");
	if (ret > 0)
	{
		cout << "*********************************update bin data success*********************************" << endl;
	}
	else
	{
		cout << "*********************************update bin data failed*********************************" << endl;
	}

	memset(filepath, 0, sizeof(filepath));
	cout << "input your new update file path:" << ""; cin >> filepath;

	TROWS rows;
	tsdk_mysql_easylike(_handle_, "testdb_bin", "num", "1", rows);
	TROW row = rows[0];
	TUINT64 size = row[3].size;
	const char *pdataupdate = row[3].data;
	SaveFile(filepath, pdataupdate, size);
}
int main()
{
	std::cout << "wow~" << std::endl;
	init();
demoenter:
	cout << "************************commond list***********************"<< endl;
	cout << "1:create a table, which name is testdb" << endl;
	cout << "2:insert some dates to testdb" << endl;
	cout << "3:update some dates on testdb" << endl;
	cout << "4:create a table, which name is testdb_bin" << endl;
	cout << "5:insert some bin dates to testdb_bin" << endl;
	cout << "6:update some bin dates on testdb_bin" << endl;
	cout << "7:exit this testdemo" << endl;
	cout << "emport a num which you want to do:" << "";
	int commond = 0;
	cin.clear();
	cin >> commond;
	cin.clear();
	switch (commond)
	{
	case 1:createdtable(); break;
	case 2:insertdata(); break;
	case 3:updatedata(); break;
	case 4:createdtable_bin(); break;
	case 5:insertdata_bin(); break;
	case 6:updatedata_bin(); break;
	case 7:finit();cout << "bye~" << endl; return 0;
	default:cout << "************************unsupport commond!************************" << endl; break;
	}
	goto demoenter;
	return 0;
}