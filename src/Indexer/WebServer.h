/*
文件名: WebServer.h
描　述: HTTP Server, 
　　　  1. serves static contents under `./public/`;
　　　  2. calls `queryHandler` for `GET /api?query=%s` requests.
　　　  GB2312 only.

　　　  对外仅提供一个接口，
　　　  `extern int startServer(void(*queryHandler)(ostream& os, string& query), bool startWebBrowser);`

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-11-30

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/

#pragma once

#include <ostream>
#include <string>
using std::ostream;
using std::string;
extern int startServer(void(*queryHandler)(ostream& os, string& query), bool startWebBrowser);
