/*
�ļ���: WebServer.h
�衡��: 

������: ������, �廪��ѧ���ѧԺ, lizy14@yeah.net
������: 2015-11-30

������: Visual Studio 2012 (MSVC++ 11.0)
*/

#pragma once

#include <ostream>
#include <string>
using std::ostream;
using std::string;
extern int startServer(void(*f)(ostream& os, string& query), bool startWebBrowser);