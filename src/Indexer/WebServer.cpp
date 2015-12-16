/*
文件名: WebServer.cpp
描　述: 

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
/* 向客户端提供的不仅是文件内容。                                          */
/************************************************************************/

/* 定义常量 */
#define HTTP_DEF_PORT      2333     /* 连接的缺省端口 */
#define HTTP_BUF_SIZE      1024     /* 缓冲区的大小 */
#define QUERY_LEN          1024     /* 查询串长度 */


char *http_res_hdr_tmpl = "HTTP/1.1 200 OK\r\nServer: Zhaoyang\r\n"
    "Accept-Ranges: bytes\r\nContent-Length: %d\r\nConnection: close\r\n"
    "Content-Type: %s\r\nAccess-Control-Allow-Origin: *\r\n\r\n";

char *http_404_tmpl = "HTTP/1.1 404 NOT FOUND\r\nContent-Length: 3\r\n"
    "\r\n\r\n404";



/* 定义文件类型对应的 Content-Type */
struct doc_type
{
    char *suffix; /* 文件后缀 */
    char *type;   /* Content-Type */
};

struct doc_type file_type[] = 
{
    {"html",    "text/html"  },
    {"gif",     "image/gif"  },
    {"jpeg",    "image/jpeg" },
    {"jpg",     "image/jpeg" },
    {"png",     "image/png"  },
    {"js",      "application/javascript" },
    {"css",     "test/css"   },
    { NULL,      NULL        }
};




/**************************************************************************
 *
 * 函数功能: 根据文件后缀查找对应的 Content-Type.
 *
 * 参数说明: [IN] suffix, 文件名后缀;
 *
 * 返 回 值: 成功返回文件对应的 Content-Type, 失败返回 NULL.
 *
 **************************************************************************/
char *http_get_type_by_suffix(const char *suffix)
{
    struct doc_type *type;

    for (type = file_type; type->suffix; type++)
    {
        if (strcmp(type->suffix, suffix) == 0)
            return type->type;
    }

    return NULL;
}


/**************************************************************************
 *
 * 函数功能: 解析请求行, 得到查询字串. 请求行格式:
 *           [GET http://localhost:8080/?query=hello_world HTTP/1.1]
 *
 * 参数说明:  [IN]  buf, 字符串指针数组;
 *           [IN]  buflen, buf 的长度;
 *           [OUT] query, 查询字串;
 *           [OUT] filename, 文件名;
 *           [OUT] type, Content-Type header;
 *
 * 返 回 值: void.
 *
 **************************************************************************/
void http_parse_request_cmd(char *buf, int buflen, char *query, char* file_name, char* type)
{

    int length = 0;
    char *begin, *end, *bias;
    char* queryPrefix = "/api?query=";
    
    

    begin = strstr(buf, queryPrefix);
    if(begin==0){

        int length = 0;
        char *begin, *end, *bias;
        char suffix[16];

        /* 查找 URL 的开始位置 */
        begin = strchr(buf, ' ');
        if(begin == 0){
            query[0]=0, file_name[0]=0, type[0]=0;
            return;
        }
        begin += 1;

        /* 查找 URL 的结束位置 */
        end = strchr(begin, ' ');
        if(end == 0){
            query[0]=0, file_name[0]=0, type[0]=0;
            return;
        }
        *end = 0;

        bias = strrchr(begin, '/');
        length = end - bias;

        /* 找到文件名的开始位置 */
        if ((*bias == '/') || (*bias == '\\'))
        {
            bias++;
            length--;
        }

        /* 得到文件名 */
        if (length > 0)
        {
            memcpy(file_name, bias, length);
            file_name[length] = 0;

            begin = strrchr(file_name, '.');
            if (begin)
                strcpy(suffix, begin + 1);
        }
        char* type_ = http_get_type_by_suffix(suffix); /* 文件对应的 Content-Type */
        if (type_ == NULL)
        {
            printf("[Web] Unknown content type `%s`\n", file_name);

            query[0]=0, file_name[0]=0, type[0]=0;
            return;
        }
        strcpy(type, type_);
        query[0]=0;
        return;
    }
    
    strcpy(type, "application/json; charset=gb2312");

    begin += strlen(queryPrefix);
    
    
    end = strstr(begin, " HTTP/1.1");
    if(end==0){
        
        query[0]=0, file_name[0]=0, type[0]=0;
        return;
        
    }
    *end = 0;
    strcpy(query, begin);
    file_name[0]=0;
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
    char filename[40] = {0};
    char type[40] = {0};
    FILE* res_file;

    /* 提取 query 串 */
    http_parse_request_cmd(buf, buf_len, query,filename, type);

    if(query[0]){
        string queryEscaped = unescape(query);
        printf("[Web] Handling query `%s`\n", queryEscaped.c_str());

        /* 处理 query 串*/
        QueryHandler(ofstream("_response.json", ofstream::binary), queryEscaped);
    
        res_file = fopen("_response.json", "r");

    }else if(filename[0]){

        printf("[Web] Serving `%s`\n", filename);
        string local_filename = (string("public/")+string(filename));
        res_file = fopen(local_filename.c_str(), "rb+");

    }else{

        send(soc, http_404_tmpl, strlen(http_404_tmpl),0);return 1;

    }


    if(res_file == NULL){
        send(soc, http_404_tmpl, strlen(http_404_tmpl),0);
        return 1;
    }

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
    if(query[0])
        system("del _response.json /q /f /a");
    
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
        puts("Please check if port 2333 is used by another application.");
        return -1; 
    }

    result = listen(srv_soc, SOMAXCONN);
    printf("[Web] The server is running on port 2333... ...\n");
    
    if(startBrowser){
        char *command = "explorer.exe http://localhost:2333/index.html";
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
