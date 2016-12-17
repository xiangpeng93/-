// DBLayer.cpp : 定义 DLL 应用程序的导出函数。
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
	sqlite 每查到一条记录，就调用一次这个回调
	para是你在 sqlite3_exec 里传入的 void * 参数, 通过para参数，你可以传入一些特殊的指针（比如类指  针、结构指针），然后在这里面强制转换成对应的类型（这里面是void*类型，必须强制转换成你的类型才可用）。然后操作这些数据
	nCount是这一条(行)记录有多少个字段 (即这条记录有多少列)
	char ** pValue 是个关键值，查出来的数据都保存在这里，它实际上是个1维数组（不要以为是2维数组），每一个元素都是一个 char* 值，是一个字段内容（用字符串来表示，以/0结尾）
	char ** pName 跟pValue是对应的，表示这个字段的字段名称, 也是个1维数组
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

