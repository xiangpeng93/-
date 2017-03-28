// DBLayerConsole.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../DBLayer/DBLayer.h"
#include <iostream>
using namespace std;
#pragma comment (lib,"../Release/DBLayer.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	Init();
	string test = "INSERT INTO USERINFO (USERNAME , USERCOUNT , USERPHONE ) VALUES ('项鹏', 'pengxiang07072811',18072741787)";
	//Insert((char*)test.c_str());
	test = "SELECT * from USERINFO";
	Select((char*)test.c_str());

	
	char buff[2048] = { 0 };
	char buff1[2048] = { 0 };
	char buff2[2048] = { 0 };
	do {
		memset(buff, 0, sizeof(buff));
		memset(buff1, 0, sizeof(buff));
		memset(buff2, 0, sizeof(buff));
		GetMsg(buff, buff1, buff2);
		cout << buff << endl;
	} while (strcmp(buff, "") != 0);
	system("pause");
	test = "delete from USERINFO WHERE USERNAME='测试2 '";
	Delete((char*)test.c_str());
	return 0;
}

