/*
文件名: main.cpp
描　述: 程序入口点：实验 1——网页信息的提取与分词

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-10-16

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/


#include "Parser.h"
#include "SongInfo.h"
#include "Segmentation.h"
#include "String.h"
#include "StringList.h"
#include "Test.h"
#include <iostream>
#include <string>
#include <fstream>


//main logic
int entryPoint(int argc, char** argv);

// I/O operations
std::ostream& operator<<(std::ostream& os, N::SongInfo& song);
std::string getFileContent(std::string filename);
N::List<N::String>& getInputFilenames(N::String input_directory);
template<class T>std::ostream& operator<<(std::ostream& os, N::List<T>& list);

#define USE_HARD_CODED_PARAMETERS	

int main(int argc, char** argv){
	//N::test();return 0;

#ifdef USE_HARD_CODED_PARAMETERS
	int argc_=4;
	char inputDirectory[]="O:\\iMusic\\pages";
	char outputDirectory[]="O:\\iMusic\\output\\";
	char *argv_[4];
	argv_[1] = "THERE_IS_NO_CONFIG_FILE";
	argv_[2] = inputDirectory;
	argv_[3] = outputDirectory;
	entryPoint(argc_, argv_);
#else
	entryPoint(argc, argv);
#endif
	return system("pause");
}

int entryPoint(int argc, char** argv){
	if(argc != 4){
		std::cout << "Usage: iMusic arg1 arg2 arg3" << std::endl << std::endl;
		std::cout << "    arg1: config file, `iMusic.config` by default." << std::endl;
		std::cout << "    arg2: input directory." << std::endl;
		std::cout << "    arg3: output directory." << std::endl << std::endl;
		return 0;
	}

	//删除 argv[2, 3] 路径末尾的 '\'
	for(int i=2; i<=3; i++){
		int len = strlen(argv[i]);
		if(argv[i][len-1]=='\\')
			argv[i][len-1]=0;
	}

	//TODO: 路径参数合法性检查
	N::String config_filename = argv[1];
	N::Segmentation segmentation;
	N::String input_directory = argv[2];
	N::String output_directory = argv[3];
	std::cout << "Input directory: " << input_directory << std::endl;
	std::cout << "Output directory: " << output_directory << std::endl;


	//从`input_directory`获取文件名列表（0001.html, 0002.html, ....）
	N::List<N::String> filenames = getInputFilenames(input_directory);
	std::cout << "Input filenames: " << std::endl << filenames << std::endl;

	//下面开始遍历这些文件名
	for(int i=0; i<filenames.length; i++){
		N::String filename = filenames[i];
		N::String full_filename = input_directory + N::String("\\") + filenames[i];

		N::String output_filename_without_ext = output_directory + N::String("\\") + filename.subString(0, filename.indexOf('.'));
		N::String info_filename = output_filename_without_ext + N::String(".info");
		N::String seg_filename = output_filename_without_ext + N::String(".txt");

		std::cout << "Loading " << full_filename << std::endl;
		N::String content = getFileContent(full_filename);

		std::cout << "Parsing..." << std::endl;
		N::Parser parser(content);
		N::SongInfo songInfo = parser.songInfo;
		N::List<N::String> segResult = segmentation.exec(parser.songInfo.lyric);

		std::cout << "Writing to " << info_filename << std::endl;
		std::ofstream info_file(info_filename);
		info_file << songInfo;

		std::cout << "Writing to " << seg_filename << std::endl;
		std::ofstream seg_file(seg_filename);
		seg_file << segResult;

		std::cout << "Done." << std::endl << std::endl;
	}
	std::cout << "All done." << std::endl << std::endl;
	return 0;
}

std::string getFileContent(std::string filename){
	std::ifstream file(filename);
	std::string _;
	while(!file.eof()){
		std::string __;
		std::getline(file, __);
		_ += __;
	}
	return _;
}
N::List<N::String>& getInputFilenames(N::String input_directory){
	N::List<N::String> *filenames = new N::List<N::String>();
	N::String command;
	command = N::String("dir ") + input_directory + N::String("\\*.html /b > filelist.txt");
	std::system(std::string(command).c_str());

	std::ifstream file("filelist.txt");
	while(!file.eof()){
		std::string str;
		std::getline(file, str);
		if(str.length())
			filenames->push(str);
	}
	file.close();
	std::system("del filelist.txt /q /f /a");
	return *filenames;
}
std::ostream& operator<<(std::ostream& os, N::SongInfo& song){
	os << song.title << std::endl;
	os << song.singer << std::endl;
	os << song.album << std::endl;
	os << song.pubDate << std::endl;
	os << song.composer << std::endl;
	os << song.lyricist << std::endl;
	os << song.lyric << std::endl;
	return os;
}
template<class T>std::ostream& operator<<(std::ostream& os, N::List<T>& list){
	for(int i=0; i<list.length; i++)
		os << list[i] << std::endl;
	return os;
}