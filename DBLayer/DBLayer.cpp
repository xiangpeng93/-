// DBLayer.cpp : 定义 DLL 应用程序的导出函数。
//
#include <iostream>
#include <map>
#include <mutex>
using namespace std;
#include "DBLayer.h"
//, SHOPNAME TEXT, ORDERCOST TEXT, USERGET TEXT
#include "sqlite3.h"
#define USERINFO_TABLE "CREATE TABLE IF NOT EXISTS USERINFO (id INTEGER PRIMARY KEY, USERNAME TEXT, USERCOUNT TEXT, USERPHONE TEXT)"
#define DATABASE "info.db"
sqlite3 * db;
char* sErrMsg = 0;
struct msgInfo{
	string userName;
	string userCount;
	string userPhone;
};
map<string, msgInfo> g_returnMsg;

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
	char *flag = (char *)para;
	string s;
	msgInfo tempInfo;
	string id;
	for (int i = 0; i<nCount; i++){
		s += pName[i];
		s += ":";
		s += pValue[i];
		s += "\n";
		if (strcmp(pName[i], "id") == 0)
		{
			id = pValue[i];
		}
		if (strcmp(pName[i], "USERNAME") == 0)
		{
			tempInfo.userName = pValue[i];
		}
		else if (strcmp(pName[i], "USERCOUNT") == 0)
		{
			tempInfo.userCount = pValue[i];
		}
		else if (strcmp(pName[i], "USERPHONE") == 0)
		{
			tempInfo.userPhone = pValue[i];
		}
	}

	cout << s.c_str() << endl;
	g_mutex.lock();
	g_returnMsg.insert(std::pair<string, msgInfo>(id, tempInfo));
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
	char *flag = "Insert";
	sqlite3_exec(db, sql, callback, (void *)flag, &sErrMsg);
}

void  __stdcall Select(char *sql)
{
	char *flag = "Select";
	sqlite3_exec(db, sql, callback, (void *)flag, &sErrMsg);
}

void __stdcall Delect(char *sql)
{
	char *flag = "Delect";
	sqlite3_exec(db, sql, NULL, (void *)flag, &sErrMsg);
}

void __stdcall GetMsg(char *userName, char *userCount, char *userPhone)
{
	g_mutex.lock();
	if (g_returnMsg.size() > 0)
	{
		map<string, msgInfo>::iterator iter = (g_returnMsg.begin());
		if (iter->second.userName.length() > 0)
			strcpy_s(userName, iter->second.userName.length() + 1, iter->second.userName.c_str());
		if (iter->second.userCount.length() > 0)
			strcpy_s(userCount, iter->second.userCount.length() + 1, iter->second.userName.c_str());
		if (iter->second.userPhone.length() > 0)
			strcpy_s(userPhone, iter->second.userPhone.length() + 1, iter->second.userName.c_str());
		g_returnMsg.erase(iter);
	}
	g_mutex.unlock();

}

void __stdcall Fini()
{
	sqlite3_close(db);
}

