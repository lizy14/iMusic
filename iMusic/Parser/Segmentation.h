/*
�ļ���: Segmentation
�衡��: ���ķִ����������

������: ������, �廪��ѧ���ѧԺ, lizy14@yeah.net
������: 2015-10-16

������: Visual Studio 2012 (MSVC++ 11.0)
*/

#pragma once

#include "CharStringList.h"
#include <fstream>

namespace Zhaoyang{
	class Segmentation{
	public:
		Segmentation(CharString);//��ȡ�����ļ������شʿ�
		~Segmentation(void);
		static CharStringList exec(CharString);//�Դ�����ַ���ִ�зִʣ����طִʽ��
	};
}
