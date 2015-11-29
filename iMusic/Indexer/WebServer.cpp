/*
文件名: WebServer.cpp
描　述: HTTP Server, 
　　　  接收 GET 请求，提取 query 字串，返回结果 JSON
　　　  仅支持 GB2312 编码
       对外接口请见 `WebServer.h`
       references: 
       http://bbs.csdn.net/topics/390187516, 
       http://blog.csdn.net/zzstack/article/details/20556051

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-11-30

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/


#include "WebServer.h"

void(*QueryHandler)(ostream& os, string& query);
bool startBrowser = false;

#include <math.h>   
#include <stdio.h>
#include <fstream>
using namespace std;

#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")  /* WinSock使用的库函数 */







long hex2dec(char * s){  
    int L=strlen(s);  
    char c;  
    long re=0;  
    while(c=s++[0]){  
        if(c >='0' && c <='9'){  
            c-=48;  
        }else{  
            c=c>'Z'? c-32:c;   
            c-='A'-10;    
        }  
        re+= c<<(4*--L) ;  
    }  
    return re;  
}   

string unescape(char * str){  
    char* re =(char *)calloc( strlen(str) +1,1);  
    char *_str;  
    char * _re=re;  
    char code[5]={0};  
    WCHAR wc;  
    int n;  
    while(str){  
        _str= strchr(str,'%') ;  
        if(!_str) break;  
        if( n=_str-str ){  
            memcpy(_re,str, n   );  
            _re+=n;  
        }  
        strset(code,0);  
        if(_str[1]=='u'){  
            return "Unicode is not supported!";
        }else{  
            memcpy(code,_str+1,2);  
            str=_str+3;   
            _re[0]=hex2dec(code);  
            _re++;    
        }  
    }  
    strcpy(_re,str);  
    return re;  
}  






/*************************************************************************
 * 
 * Copyright (c) 2002-2005 by Zhang Huiyong All Rights Reserved
 *
 * FILENAME:  WebSrv.c
 *
 * PURPOSE :  HTTP 服务器程序, 向客户端提供请求的文件内容. 
 *  
 * AUTHOR  :  张会勇
 * 
 * BOOK    :  <<WinSock网络编程经络>>
 * 
 **************************************************************************/

/************************************************************************/
/* Modified  By Zhaoyang Li, 2015-11-30                                 */
/* 向客户端提供的不再是文件内容。                                          */
/************************************************************************/

/* 定义常量 */
#define HTTP_DEF_PORT      2333     /* 连接的缺省端口 */
#define HTTP_BUF_SIZE      1024     /* 缓冲区的大小 */
#define QUERY_LEN          1024     /* 查询串长度 */


char *http_res_hdr_tmpl = "HTTP/1.1 200 OK\r\nServer: C++\r\n"
    "Accept-Ranges: bytes\r\nContent-Length: %d\r\nConnection: close\r\n"
    "Content-Type: %s\r\nAccess-Control-Allow-Origin: *\r\n\r\n";

char* type = "application/json; charset=gb2312";




/**************************************************************************
 *
 * 函数功能: 解析请求行, 得到查询字串. 请求行格式:
 *           [GET http://localhost:8080/?query=hello_world HTTP/1.1]
 *
 * 参数说明: [IN]  buf, 字符串指针数组;
 *           [IN]  buflen, buf 的长度;
 *           [OUT] query, 查询字串;
 *
 * 返 回 值: void.
 *
 **************************************************************************/
void http_parse_request_cmd(char *buf, int buflen, char *query)
{

    int length = 0;
    char *begin, *end, *bias;
    char* queryPrefix = "?query=";
    
    

    begin = strstr(buf, queryPrefix);
    if(begin==0){
        query = NULL;
        return;  
    }
    begin += strlen(queryPrefix);
    
    
    end = strstr(begin, " HTTP/1.1");
    if(end==0){
        query = NULL;
        return;
    }
    *end = 0;
    strcpy(query, begin);
}


/**************************************************************************
 *
 * 函数功能: 向客户端发送 HTTP 响应.
 *
 * 参数说明: [IN]  buf, 字符串指针数组;
 *           [IN]  buf_len, buf 的长度;
 *
 * 返 回 值: 成功返回非0, 失败返回0.
 *
 **************************************************************************/
int http_send_response(SOCKET soc, char *buf, int buf_len)
{
    int read_len, file_len, hdr_len, send_len;
    char read_buf[HTTP_BUF_SIZE];
    char http_header[HTTP_BUF_SIZE];
    char query[QUERY_LEN] = "";
    

    /* 提取 query 串 */
    http_parse_request_cmd(buf, buf_len, query);
    string queryEscaped = unescape(query);
    printf("[Web] Handling query `%s`\n", queryEscaped.c_str());


    /* 处理 query 串*/
    QueryHandler(ofstream("response.json"), queryEscaped);

    FILE* res_file;
    res_file = fopen("response.json", "r");
    if(res_file == NULL)    
        return 0;
    fseek(res_file, 0, SEEK_END);
    file_len = ftell(res_file);
    fseek(res_file, 0, SEEK_SET);

    /* 构造 HTTP 首部，并发送 */

    hdr_len = sprintf(http_header, http_res_hdr_tmpl, file_len, type);
    send_len = send(soc, http_header, hdr_len, 0);

    if (send_len == SOCKET_ERROR)
    {
        printf("[Web] Fail to send, error = %d\n", WSAGetLastError());
        return 0;
    }

    do /* 发送 HTTP 的消息体 */
    {
        read_len = fread(read_buf, sizeof(char), HTTP_BUF_SIZE, res_file);

        if (read_len > 0)
        {
            send_len = send(soc, read_buf, read_len, 0);
            file_len -= read_len;
        }
    } while ((read_len > 0) && (file_len > 0));

    fclose(res_file);
    
    return 1;
}


int start_server(unsigned short port = HTTP_DEF_PORT)
{
    WSADATA wsa_data;
    SOCKET	srv_soc = 0, acpt_soc;  /* socket 句柄 */	
    struct sockaddr_in serv_addr;   /* 服务器地址  */
    struct sockaddr_in from_addr;   /* 客户端地址  */
    char recv_buf[HTTP_BUF_SIZE];
    
    int from_len = sizeof(from_addr);
    int	result = 0, recv_len;


    WSAStartup(MAKEWORD(2,0), &wsa_data); /* 初始化 WinSock 资源 */
    
    srv_soc = socket(AF_INET, SOCK_STREAM, 0); /* 创建 socket */
    if (srv_soc == INVALID_SOCKET)
    {
        printf("[Web] socket() Fails, error = %d\n", WSAGetLastError());
        return -1; 
    }
    
    /* 服务器地址 */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    result = bind(srv_soc, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    if (result == SOCKET_ERROR) /* 绑定失败 */
    {
        closesocket(srv_soc);
        printf("[Web] Fail to bind, error = %d\n", WSAGetLastError());
        return -1; 
    }

    result = listen(srv_soc, SOMAXCONN);
    printf("[Web] The server is running on port 2333... ...\n");
    
    if(startBrowser){
        char *command = "explorer.exe frontend\\index.html";
        system(command);
    }

    while (1)
    {
        acpt_soc = accept(srv_soc, (struct sockaddr *) &from_addr, &from_len);
        if (acpt_soc == INVALID_SOCKET) /* 接受失败 */
        {
            printf("[Web] Fail to accept, error = %d\n", WSAGetLastError());
            break; 
        }

        printf("[Web] Accepted address:[%s], port:[%d]\n", 
            inet_ntoa(from_addr.sin_addr), ntohs(from_addr.sin_port));
        
        recv_len = recv(acpt_soc, recv_buf, HTTP_BUF_SIZE, 0);
        if (recv_len == SOCKET_ERROR) /* 接收失败 */
        {
            closesocket(acpt_soc);
            printf("[Web] Fail to recv, error = %d\n", WSAGetLastError());
            goto outside_break; 
        }

        recv_buf[recv_len] = 0;
        /* 向客户端发送响应数据 */
        result = http_send_response(acpt_soc, recv_buf, recv_len);
        
        closesocket(acpt_soc);
    }
    outside_break:
    closesocket(srv_soc);
    WSACleanup();
    printf("[Web] The server is stopped.\n");

    return 0;
}

int startServer(void(*f)(ostream& os, string& query), bool s){
    startBrowser = s;
    QueryHandler = f;
    start_server();
    return 1;
}
