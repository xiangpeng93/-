// DBLayer.cpp : 定义 DLL 应用程序的导出函数。
//
#include <iostream>
#include <vector>
#include <mutex>
#include <Windows.h>

using namespace std;
#include "DBLayer.h"
//, SHOPNAME TEXT, ORDERCOST TEXT, USERGET TEXT
#include "sqlite3.h"
#define USERINFO_TABLE "CREATE TABLE IF NOT EXISTS USERINFO (id INTEGER PRIMARY KEY, USERNAME TEXT, USERCOUNT TEXT, USERPHONE TEXT)"
#define SHOPINFO_TABLE "CREATE TABLE IF NOT EXISTS SHOPINFO (id INTEGER PRIMARY KEY, USERNAME TEXT, USERCOUNT TEXT, USERPHONE TEXT)"
#define HISTROYDATA_TABLE "CREATE TABLE IF NOT EXISTS HISTORYDATA (id INTEGER PRIMARY KEY, USERNAME TEXT, USERCOUNT TEXT, USERPHONE TEXT,SHOPNAME TEXT,COSTMONEY TEXT,COSTMONEYFORUSER TEXT,DATETIME datetime)"
#define USERDATAHISTORY_TABLE "CREATE TABLE IF NOT EXISTS USERDATAHISTORY (id INTEGER PRIMARY KEY, USERNAME TEXT, USERCOUNT TEXT, USERPHONE TEXT,SHOPNAME TEXT,COSTMONEY TEXT,COSTMONEYFORUSER TEXT,DATETIME datetime)"
#define DATABASE "info.db"
sqlite3 * db;
char* sErrMsg = 0;
struct msgInfo{
	string userName;
	string userCount;
	string userPhone;
};
vector<pair<string, msgInfo>> g_returnMsg;

char* g_errMsg = 0;

struct HISTORYINFO{
	string userName;
	string userCount;
	string userPhone; 
	string SHOPNAME;
	string COSTMONEY;
	string COSTMONEYFORUSER;
	string DATETIME;
};
vector<pair<string, HISTORYINFO>> g_returnHistoryMsg;

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

bool g_callback1 = false;
bool g_callback2 = false;
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

	//cout << s.c_str() << endl;
	g_mutex.lock();
	g_returnMsg.push_back(std::pair<string, msgInfo>(id, tempInfo));
	g_mutex.unlock();
	return 0;
}

int callback2(void*para, int nCount, char** pValue, char** pName) {
	char *flag = (char *)para;
	string s;
	HISTORYINFO tempInfo;
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
		else if (strcmp(pName[i], "SHOPNAME") == 0)
		{
			tempInfo.SHOPNAME = pValue[i];
		}
		else if (strcmp(pName[i], "COSTMONEY") == 0)
		{
			tempInfo.COSTMONEY = pValue[i];
		}
		else if (strcmp(pName[i], "COSTMONEYFORUSER") == 0)
		{
			tempInfo.COSTMONEYFORUSER = pValue[i];
		}
		else if (strcmp(pName[i], "DATETIME") == 0)
		{
			tempInfo.DATETIME = pValue[i];
		}
	}

	//cout << s.c_str() << endl;
	g_mutex.lock();

	g_returnHistoryMsg.push_back(std::pair<string, HISTORYINFO>(id, tempInfo));
	g_mutex.unlock();
	return 0;
}
void __stdcall Init()
{
	char chpath[256];
	GetModuleFileNameA(NULL, (char*)chpath, sizeof(chpath));
	string dataPath = chpath;
	int status = dataPath.find_last_of("\\");
	dataPath.erase(status);

	dataPath += "\\";
	dataPath += DATABASE;
	sqlite3_open(dataPath.c_str(), &db);
	sqlite3_exec(db, USERINFO_TABLE, NULL, NULL, &sErrMsg);
	sqlite3_exec(db, SHOPINFO_TABLE, NULL, NULL, &sErrMsg);
	sqlite3_exec(db, HISTROYDATA_TABLE, NULL, NULL, &sErrMsg);
	sqlite3_exec(db, USERDATAHISTORY_TABLE, NULL, NULL, &sErrMsg);
	sqlite3_exec(db, "PRAGMA synchronous = OFF", NULL, NULL, &sErrMsg);
	sqlite3_exec(db, "PRAGMA journal_mode = MEMORY", NULL, NULL, &sErrMsg);
}
void __stdcall Insert(char *sql)
{
	char *flag = "Insert";
	sqlite3_exec(db, sql, NULL, (void *)flag, &sErrMsg);

}

void  __stdcall Select(char *sql)
{
	g_mutex.lock();
	g_returnMsg.clear();
	g_mutex.unlock();
	char *flag = "Select";
	//sqlite3_exec(db, sql, callback, (void *)flag, &sErrMsg);
	char** pResult;
	int nRow;
	int nCol;
	int nResult = sqlite3_get_table(db, sql, &pResult, &nRow, &nCol, &g_errMsg);
	if (nResult != SQLITE_OK)
	{
		cout << g_errMsg << endl;
		sqlite3_free(g_errMsg);
		return;
	}

	int nIndex = nCol;
	for (int i = 0; i < nRow; i++)
	{
		string id;
		msgInfo tempInfo;
		for (int j = 0; j < nCol; j++)
		{
			string strOut;
			strOut += pResult[j];
			strOut += ":";
			if (pResult[nIndex] != NULL)
			{
				strOut += pResult[nIndex];

				if (strcmp(pResult[j], "id") == 0)
				{
					id = pResult[nIndex];
				}
				if (strcmp(pResult[j], "USERNAME") == 0)
				{
					tempInfo.userName = pResult[nIndex];
				}
				else if (strcmp(pResult[j], "USERCOUNT") == 0)
				{
					tempInfo.userCount = pResult[nIndex];
				}
				else if (strcmp(pResult[j], "USERPHONE") == 0)
				{
					tempInfo.userPhone = pResult[nIndex];
				}
			}
			strOut += " ";

			++nIndex;
			cout << strOut.c_str();
		}
		cout << endl;
		if (!id.empty())
		{
			g_mutex.lock();
			g_returnMsg.push_back(std::pair<string, msgInfo>(id, tempInfo));
			g_mutex.unlock();
		}
	}
	sqlite3_free_table(pResult);  //使用完后务必释放为记录分配的内存，否则会内存泄漏

	Sleep(100);

}

void  __stdcall Select2(char *sql)
{
	g_mutex.lock();
	g_returnMsg.clear();
	g_mutex.unlock();
	char *flag = "Select";
	cout << sql << endl;
	//sqlite3_exec(db, sql, callback2, (void *)flag, &sErrMsg);
	char** pResult;
	int nRow;
	int nCol;
	int nResult = sqlite3_get_table(db, sql, &pResult, &nRow, &nCol, &g_errMsg);
	if (nResult != SQLITE_OK)
	{
		cout << g_errMsg << endl;
		sqlite3_free(g_errMsg);
		return;
	}

	int nIndex = nCol;
	for (int i = 0; i < nRow; i++)
	{
		string id;
		HISTORYINFO tempInfo;
		for (int j = 0; j < nCol; j++)
		{
			string strOut;
			strOut += pResult[j];
			strOut += ":";
			if (pResult[nIndex] != NULL)
			{
				strOut += pResult[nIndex];
				if (strcmp(pResult[j], "id") == 0)
				{
					id = pResult[nIndex];
				}
				else if (strcmp(pResult[j], "USERNAME") == 0)
				{
					tempInfo.userName = pResult[nIndex];
				}
				else if (strcmp(pResult[j], "USERCOUNT") == 0)
				{
					tempInfo.userCount = pResult[nIndex];
				}
				else if (strcmp(pResult[j], "USERPHONE") == 0)
				{
					tempInfo.userPhone = pResult[nIndex];
				}
				else if (strcmp(pResult[j], "SHOPNAME") == 0)
				{
					tempInfo.SHOPNAME = pResult[nIndex];
				}
				else if (strcmp(pResult[j], "COSTMONEY") == 0)
				{
					tempInfo.COSTMONEY = pResult[nIndex];
				}
				else if (strcmp(pResult[j], "COSTMONEYFORUSER") == 0)
				{
					tempInfo.COSTMONEYFORUSER = pResult[nIndex];
				}
				else if (strcmp(pResult[j], "DATETIME") == 0)
				{
					tempInfo.DATETIME = pResult[nIndex];
				}
			}
			strOut += " ";

			++nIndex;
			cout << strOut.c_str();
		}
		cout << endl;
		if (!id.empty())
		{
			g_mutex.lock();
			g_returnHistoryMsg.push_back(std::pair<string, HISTORYINFO>(id, tempInfo));
			g_mutex.unlock();
		}
	}
	sqlite3_free_table(pResult);  //使用完后务必释放为记录分配的内存，否则会内存泄漏
	Sleep(100);
}

void __stdcall Delete(char *sql)
{
	cout << sql << endl;
	char *flag = "Delete";
	sqlite3_exec(db, sql, NULL, (void *)flag, &sErrMsg);

}

void __stdcall Delete2(char *sql)
{
	char *flag = "Delete";
	sqlite3_exec(db, sql, NULL, (void *)flag, &sErrMsg);

}

void __stdcall GetMsg(char *userName, char *userCount, char *userPhone)
{
	int i = 0;
	

	g_mutex.lock();

	if (g_returnMsg.size() > 0)
	{
		vector<pair<string, msgInfo>>::iterator iter = (g_returnMsg.begin());
		if (iter->second.userName.length() > 0)
			strcpy_s(userName, iter->second.userName.length() + 1, iter->second.userName.c_str());
		if (iter->second.userCount.length() > 0)
			strcpy_s(userCount, iter->second.userCount.length() + 1, iter->second.userCount.c_str());
		if (iter->second.userPhone.length() > 0)
			strcpy_s(userPhone, iter->second.userPhone.length() + 1, iter->second.userPhone.c_str());
		g_returnMsg.erase(iter);
	}
	g_mutex.unlock();

}

void __stdcall GetMsg2(char *userName, char *userCount, char *userPhone, char *shopName, char *costMoney, char *costMoneyForUser,char * dataTime)
{
	int i = 0;
	
	g_mutex.lock();
	if (g_returnHistoryMsg.size() > 0)
	{
		vector<pair<string, HISTORYINFO>>::iterator iter = (g_returnHistoryMsg.begin());
		if (iter->second.userName.length() > 0)
			strcpy_s(userName, iter->second.userName.length() + 1, iter->second.userName.c_str());
		if (iter->second.userCount.length() > 0)
			strcpy_s(userCount, iter->second.userCount.length() + 1, iter->second.userCount.c_str());
		if (iter->second.userPhone.length() > 0)
			strcpy_s(userPhone, iter->second.userPhone.length() + 1, iter->second.userPhone.c_str());
		if (iter->second.SHOPNAME.length() > 0)
			strcpy_s(shopName, iter->second.SHOPNAME.length() + 1, iter->second.SHOPNAME.c_str());
		if (iter->second.COSTMONEY.length() > 0)
			strcpy_s(costMoney, iter->second.COSTMONEY.length() + 1, iter->second.COSTMONEY.c_str());
		if (iter->second.COSTMONEYFORUSER.length() > 0)
			strcpy_s(costMoneyForUser, iter->second.COSTMONEYFORUSER.length() + 1, iter->second.COSTMONEYFORUSER.c_str());
		if (iter->second.DATETIME.length() > 0)
			strcpy_s(dataTime, iter->second.DATETIME.length() + 1, iter->second.DATETIME.c_str());

		g_returnHistoryMsg.erase(iter);
	}

	g_mutex.unlock();

}

void __stdcall Fini()
{
	sqlite3_close(db);
}

