/*
文件名: SongInfo.h
描　述: 歌曲信息类的声明

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-10-16

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/
#pragma once

#include "String.h"

namespace N{
	class Song{
	public:
		//文本字段
		String title;   //音乐名称
		String singer;  //歌手名称
		String album;   //专辑名称
		String pubDate; //发行时间
		String composer;//作词
		String lyricist;//作曲
		String lyric;   //歌词
	};
}