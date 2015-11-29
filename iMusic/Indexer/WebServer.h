/*
文件名: WebServer.h
描　述: 

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-11-30

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/

#pragma once

#include <ostream>
#include <string>
using std::ostream;
using std::string;
extern int startServer(void(*f)(ostream& os, string& query), bool startWebBrowser);