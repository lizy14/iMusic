/*
文件名: 
描　述: GUI 入口点

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-11-30

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/

#include "WebServer.h"
void queryHandler(ostream& os, string& query){
    os << "{\"msg\":\"您输入的是：" << query << "\"}";
}

int main(){
    startServer(queryHandler, false);
}