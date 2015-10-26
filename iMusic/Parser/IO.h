/*
�ļ���: IO.h
�衡��: �����������

������: ������, �廪��ѧ���ѧԺ, lizy14@yeah.net
������: 2015-10-22

������: Visual Studio 2012 (MSVC++ 11.0)
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
