/*
文件名: SongInfo.h
描　述: 歌曲信息类的声明

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-10-16

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/
#pragma once

#include "CharString.h"

namespace Zhaoyang{
	class SongInfo{
	public:
		//文本字段
		CharString title;   //音乐名称
		CharString singer;  //歌手名称
		CharString album;   //专辑名称
		CharString pubDate; //发行时间
		CharString composer;//作词
		CharString lyricist;//作曲
		CharString lyric;   //歌词
	};

}