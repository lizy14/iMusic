/*
�ļ���: SongInfo.h
�衡��: ������Ϣ�������

������: ������, �廪��ѧ���ѧԺ, lizy14@yeah.net
������: 2015-10-16

������: Visual Studio 2012 (MSVC++ 11.0)
*/
#pragma once

#include "String.h"

namespace N{
	class Song{
	public:
		//�ı��ֶ�
		String title;   //��������
		String singer;  //��������
		String album;   //ר������
		String pubDate; //����ʱ��
		String composer;//����
		String lyricist;//����
		String lyric;   //���
	};
}