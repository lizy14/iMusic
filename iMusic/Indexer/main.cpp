/*
�ļ���: 
�衡��: GUI ��ڵ�

������: ������, �廪��ѧ���ѧԺ, lizy14@yeah.net
������: 2015-11-30

������: Visual Studio 2012 (MSVC++ 11.0)
*/

#include "WebServer.h"
void queryHandler(ostream& os, string& query){
    os << "{\"msg\":\"��������ǣ�" << query << "\"}";
}

int main(){
    startServer(queryHandler, false);
}