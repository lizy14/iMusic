/*
�ļ���: JSON.cpp
�衡��: 

������: ������, �廪��ѧ����ѧԺ, lizy14@yeah.net
������: 

������: Visual Studio 2012 (MSVC++ 11.0)
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