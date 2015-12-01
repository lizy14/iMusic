/*
文件名: 
描　述: 入口点

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-11-30

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/

#include "WebServer.h"
#include "../Parser/IO.h"
#include "JSON.h"

#include "InvertedIndex.h"
using namespace Zhaoyang;


InvertedIndex index;

void queryApiHandler(ostream& os, string& query){

    CharStringList wordsInQuery = index.getSeg()->exec(query);
    auto result = index.query(wordsInQuery);
    std::vector<SongInfo> result_;
    for(auto i: result)
        result_.push_back(*i);

    string json = "{\"seg\":" + JSON(wordsInQuery) + ",\"result\":" + JSON(result_) + "}";

    for(char i : json){
        if(i=='\n')
            os << '\\' << 'n';
        else if(i != '\r')
            os << i;
    }
}
int loadAllSongs(){
    string input_directory = "pages_300\\";
    CharStringList filenames = getInputFilenames(input_directory);
    for(int i=0; i<filenames.length; i++){
        CharString filename = filenames[i];
        CharString full_filename = input_directory + filenames[i];

        cout << "Indexing " << filename << endl;

        CharString content = getFileContent(full_filename);


        Parser parser(content);
        SongInfo song = parser.getSongInfo();
        song.origin = filename;

        index.insert(song);

    }
    return 0;

}



int main(){
    
    loadAllSongs();

    startServer(queryApiHandler, false);
}
