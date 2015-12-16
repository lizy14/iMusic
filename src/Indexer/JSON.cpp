/*
文件名: JSON.cpp
描　述: 

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/

#include "JSON.h"


namespace Zhaoyang{
    string JSON(string str){return string("\"")+str+string("\"");}
    string JSON(SongInfo song){
        stringstream ss;
        ss << "{";
        ss << "\"title\":\"" << song.title << "\","; 
        ss << "\"singer\":\"" << song.singer << "\","; 
        ss << "\"album\":\"" << song.album << "\","; 
        ss << "\"pubDate\":\"" << song.pubDate << "\","; 
        ss << "\"composer\":\"" << song.composer << "\","; 
        ss << "\"lyricist\":\"" << song.lyricist << "\","; 
        ss << "\"lyric\":\"" << song.lyric << "\""; 
        ss << "}";
        return ss.str();
    }
}
