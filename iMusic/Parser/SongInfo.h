/*
�ļ���: SongInfo.h
�衡��: ������Ϣ�������

������: ������, �廪��ѧ���ѧԺ, lizy14@yeah.net
������: 2015-10-16

������: Visual Studio 2012 (MSVC++ 11.0)
*/
#pragma once

#include "CharString.h"

namespace Zhaoyang{
	class SongInfo{
	public:
		//�ı��ֶ�
		CharString title;   //��������
		CharString singer;  //��������
		CharString album;   //ר������
		CharString pubDate; //����ʱ��
		CharString composer;//����
		CharString lyricist;//����
		CharString lyric;   //���
	};

}