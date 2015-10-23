/*
文件名: Segmentation
描　述: 中文分词器类的声明

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-10-16

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/

#pragma once

#include "CharStringList.h"
#include <fstream>

namespace Zhaoyang{
	class Segmentation{
	public:
		Segmentation(CharString);//读取配置文件，加载词库
		~Segmentation(void);
		static CharStringList exec(CharString);//对传入的字符串执行分词，返回分词结果
	};
}
