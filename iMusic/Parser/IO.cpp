/*
文件名: IO.h
描　述: 输入输出操作的实现

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-10-22

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/

#include "IO.h"

int entryPoint(int argc, char** argv){
	if(argc != 4){
		cout << "Usage: iMusic arg1 arg2 arg3" << endl << endl;
		cout << "    arg1: config file, `iMusic.config` by default." << endl;
		cout << "    arg2: input directory." << endl;
		cout << "    arg3: output directory." << endl << endl;
		return 0;
	}


	//TODO: 路径参数合法性检查
	//确保路径以 '\' 结尾
	CharString config_filename = argv[1];
	Segmentation segmentation;
	CharString input_directory = argv[2];
	if(input_directory[-1]!='\\')
		input_directory.append('\\');
	CharString output_directory = argv[3];
	if(output_directory[-1]!='\\')
		output_directory.append('\\');
	cout << "Input directory: " << input_directory << endl;
	cout << "Output directory: " << output_directory << endl;


	//从`input_directory`获取文件名列表（0001.html, 0002.html, ....）
	CharStringList filenames = getInputFilenames(input_directory);
	cout << "Input filenames: " << endl << filenames << endl;

	//下面开始遍历这些文件名
	for(int i=0; i<filenames.length; i++){
		CharString filename = filenames[i];
		CharString full_filename = input_directory + filenames[i];

		CharString output_filename_without_ext = output_directory + filename.subString(0, filename.indexOf('.'));
		CharString info_filename = output_filename_without_ext + CharString(".info");
		CharString seg_filename = output_filename_without_ext + CharString(".txt");

		cout << "Loading " << full_filename << endl;
		CharString content = getFileContent(full_filename);

		cout << "Parsing..." << endl;
		Parser parser(content);
		SongInfo songInfo = parser.songInfo;
		CharStringList segResult = segmentation.exec(parser.songInfo.lyric);

		cout << "Writing to " << info_filename << endl;
		ofstream info_file(info_filename);
		info_file << songInfo;

		cout << "Writing to " << seg_filename << endl;
		ofstream seg_file(seg_filename);
		seg_file << segResult;

		cout << "Done." << endl << endl;
	}
	cout << "All done." << endl << endl;
	return 0;
}

string getFileContent(string filename){
	ifstream file(filename);
	string _;
	while(!file.eof()){
		string __;
		getline(file, __);
		_ += __;
	}
	return _;
}
CharStringList getInputFilenames(CharString input_directory){
	CharStringList filenames;
	CharString command;
	command = CharString("dir ") + input_directory + CharString("\\*.html /b > filelist.txt");
	system(string(command).c_str());

	ifstream file("filelist.txt");
	while(!file.eof()){
		string str;
		getline(file, str);
		if(str.length())
			filenames.push(str);
	}
	file.close();
	system("del filelist.txt /q /f /a");
	return filenames;
}
ostream& operator<<(ostream& os, SongInfo& song){
	os << song.title << endl;
	os << song.singer << endl;
	os << song.album << endl;
	os << song.pubDate << endl;
	os << song.composer << endl;
	os << song.lyricist << endl;
	os << song.lyric << endl;
	return os;
}
template<class T>ostream& operator<<(ostream& os, List<T>& list){
	for(int i=0; i<list.length; i++)
		os << list[i] << endl;
	return os;
}
