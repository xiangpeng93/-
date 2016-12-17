// DBLayer.cpp : ���� DLL Ӧ�ó���ĵ���������
//
#include <iostream>
#include <vector>
#include <mutex>
using namespace std;
#include "DBLayer.h"
//, SHOPNAME TEXT, ORDERCOST TEXT, USERGET TEXT
#include "sqlite3.h"
#define USERINFO_TABLE "CREATE TABLE IF NOT EXISTS USERINFO (id INTEGER PRIMARY KEY, USERNAME TEXT, USERCOUNT TEXT, USERPHONE TEXT)"
#define DATABASE "info.db"
sqlite3 * db;
char* sErrMsg = 0;

vector<string> g_returnMSg;
mutex g_mutex;
class AutoLock{
public:
	AutoLock(mutex *mex)
	{
		m_mutex = mex;
		m_mutex->lock();
	}
	AutoLock()
	{
		m_mutex->unlock();
	}
private:
	mutex *m_mutex;
};
int callback(void*para, int nCount, char** pValue, char** pName) {
	/*****************************************************************************
	sqlite ÿ�鵽һ����¼���͵���һ������ص�
	para������ sqlite3_exec �ﴫ��� void * ����, ͨ��para����������Դ���һЩ�����ָ�루������ָ  �롢�ṹָ�룩��Ȼ����������ǿ��ת���ɶ�Ӧ�����ͣ���������void*���ͣ�����ǿ��ת����������Ͳſ��ã���Ȼ�������Щ����
	nCount����һ��(��)��¼�ж��ٸ��ֶ� (��������¼�ж�����)
	char ** pValue �Ǹ��ؼ�ֵ������������ݶ������������ʵ�����Ǹ�1ά���飨��Ҫ��Ϊ��2ά���飩��ÿһ��Ԫ�ض���һ�� char* ֵ����һ���ֶ����ݣ����ַ�������ʾ����/0��β��
	char ** pName ��pValue�Ƕ�Ӧ�ģ���ʾ����ֶε��ֶ�����, Ҳ�Ǹ�1ά����
	*****************************************************************************/
	char *flag = (char *)para;
	string s;
	for (int i = 0; i<nCount; i++){
		s += pName[i];
		s += ":";
		s += pValue[i];
		s += "\n";
		

	}

	cout << s.c_str() << endl;
	g_mutex.lock();
	g_returnMSg.push_back(s);
	g_mutex.unlock();
	return 0;
}

void __stdcall Init()
{
	sqlite3_open(DATABASE, &db);
	sqlite3_exec(db, USERINFO_TABLE, NULL, NULL, &sErrMsg);
	sqlite3_exec(db, "PRAGMA synchronous = OFF", NULL, NULL, &sErrMsg);
	sqlite3_exec(db, "PRAGMA journal_mode = MEMORY", NULL, NULL, &sErrMsg);
}
void __stdcall Insert(char *sql)
{
	sqlite3_exec(db, sql, callback, NULL, &sErrMsg);
}

void  __stdcall Select(char *sql)
{
	char *flag = "insert";
	sqlite3_exec(db, sql, callback, (void *)flag, &sErrMsg);
}

void __stdcall Delect(char *sql)
{

}

void __stdcall GetMsg(char *msg)
{
	g_mutex.lock();
	if (g_returnMSg.size() > 0)
	{
		string tempMsg =*(g_returnMSg.begin());
		strcpy_s(msg, tempMsg.length() + 1, tempMsg.c_str());
		g_returnMSg.erase(g_returnMSg.begin());
	}
	g_mutex.unlock();

}

void __stdcall Fini()
{

}

