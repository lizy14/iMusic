/*
�ļ���: WebServer.h
�衡��: HTTP Server, 
������  1. serves static contents under `./public/`;
������  2. calls `queryHandler` for `GET /api?query=%s` requests.
������  GB2312 only.

������  ������ṩһ���ӿڣ�
������  `extern int startServer(void(*queryHandler)(ostream& os, string& query), bool startWebBrowser);`

������: ������, �廪��ѧ���ѧԺ, lizy14@yeah.net
������: 2015-11-30

������: Visual Studio 2012 (MSVC++ 11.0)
*/

#pragma once

#include <ostream>
#include <string>
using std::ostream;
using std::string;
extern int startServer(void(*queryHandler)(ostream& os, string& query), bool startWebBrowser);
