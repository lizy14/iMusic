/*
文件名: IO.h
描　述: 输入输出操作

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-10-22

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/

#pragma once

#include "CharString.h"
#include "CharStringList.h"
#include "Parser.h"
#include "Segmentation.h"
#include "SongInfo.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace Zhaoyang;

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::ostream;
using std::string;

//main logic
extern int entryPoint(int argc, char** argv);

// I/O operations
ostream& operator<<(ostream& os, SongInfo& song);
string getFileContent(string filename);
CharStringList getInputFilenames(CharString input_directory);
template<class T> ostream& operator<<(ostream& os, List<T>& list);
