/*
�ļ���: Segmentation
�衡��: ���ķִ����������

������: ������, �廪��ѧ���ѧԺ, lizy14@yeah.net
������: 2015-10-16

������: Visual Studio 2012 (MSVC++ 11.0)
*/

#pragma once

#include "StringList.h"
using N::String;
using N::StringList;

namespace N{
	class Segmentation{
	public:
		Segmentation(void);
		~Segmentation(void);
		static StringList& exec(String);
	};
}
