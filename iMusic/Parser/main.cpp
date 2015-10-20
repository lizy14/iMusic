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
#include "CharString.h"
#include "CharStringList.h"
#include "Test.h"
#include <iostream>
#include <string>
#include <fstream>


//main logic
int entryPoint(int argc, char** argv);

// I/O operations
std::ostream& operator<<(std::ostream& os, Zhaoyang::SongInfo& song);
std::string getFileContent(std::string filename);
Zhaoyang::CharStringList& getInputFilenames(Zhaoyang::CharString input_directory);
template<class T>std::ostream& operator<<(std::ostream& os, Zhaoyang::List<T>& list);

#define USE_HARD_CODED_PARAMETERS	

int main(int argc, char** argv){
	Zhaoyang::Test::test();return system("pause");

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


	//TODO: 路径参数合法性检查
	//确保路径以 '\' 结尾
	Zhaoyang::CharString config_filename = argv[1];
	Zhaoyang::Segmentation segmentation;
	Zhaoyang::CharString input_directory = argv[2];
	if(input_directory[-1]!='\\')
		input_directory.append('\\');
	Zhaoyang::CharString output_directory = argv[3];
	if(output_directory[-1]!='\\')
		output_directory.append('\\');
	std::cout << "Input directory: " << input_directory << std::endl;
	std::cout << "Output directory: " << output_directory << std::endl;


	//从`input_directory`获取文件名列表（0001.html, 0002.html, ....）
	Zhaoyang::List<Zhaoyang::CharString> filenames = getInputFilenames(input_directory);
	std::cout << "Input filenames: " << std::endl << filenames << std::endl;

	//下面开始遍历这些文件名
	for(int i=0; i<filenames.length; i++){
		Zhaoyang::CharString filename = filenames[i];
		Zhaoyang::CharString full_filename = input_directory + filenames[i];

		Zhaoyang::CharString output_filename_without_ext = output_directory + filename.subString(0, filename.indexOf('.'));
		Zhaoyang::CharString info_filename = output_filename_without_ext + Zhaoyang::CharString(".info");
		Zhaoyang::CharString seg_filename = output_filename_without_ext + Zhaoyang::CharString(".txt");

		std::cout << "Loading " << full_filename << std::endl;
		Zhaoyang::CharString content = getFileContent(full_filename);

		std::cout << "Parsing..." << std::endl;
		Zhaoyang::Parser parser(content);
		Zhaoyang::SongInfo songInfo = parser.songInfo;
		Zhaoyang::List<Zhaoyang::CharString> segResult = segmentation.exec(parser.songInfo.lyric);

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
Zhaoyang::CharStringList& getInputFilenames(Zhaoyang::CharString input_directory){
	Zhaoyang::CharStringList *filenames = new Zhaoyang::CharStringList();
	Zhaoyang::CharString command;
	command = Zhaoyang::CharString("dir ") + input_directory + Zhaoyang::CharString("\\*.html /b > filelist.txt");
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
std::ostream& operator<<(std::ostream& os, Zhaoyang::SongInfo& song){
	os << song.title << std::endl;
	os << song.singer << std::endl;
	os << song.album << std::endl;
	os << song.pubDate << std::endl;
	os << song.composer << std::endl;
	os << song.lyricist << std::endl;
	os << song.lyric << std::endl;
	return os;
}
template<class T>std::ostream& operator<<(std::ostream& os, Zhaoyang::List<T>& list){
	for(int i=0; i<list.length; i++)
		os << list[i] << std::endl;
	return os;
}