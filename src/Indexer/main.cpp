/*
文件名: 
描　述: 实验二的入口点

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015-11-30

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/
//#define DEBUGGING
#include "WebServer.h"
#include "../Parser/IO.h"
#include "JSON.h"

#include "InvertedIndex.h"

#include <fstream>
#include <iostream>
using std::ifstream;
using std::ofstream;
using std::istream;
using std::ostream;

using namespace Zhaoyang;

InvertedIndex *index;

void queryApiHandler(ostream& os, string& query){

    CharStringList wordsInQuery = index->getSeg()->exec(query);
    CharStringList wordsInQuery_;
    
    for(int i=0; i<wordsInQuery.length; i++){
        auto& keywordInfo = index->getKeywords()[wordsInQuery[i]];
        if(keywordInfo.numberOfAppearances <= 100)//TODO: magic number
            wordsInQuery_.push(wordsInQuery[i]);
    }
    


    auto result = index->search(wordsInQuery);
    std::vector<SongInfo> result_;
    int maxNumberOfResults = 10; //non-negative integer
    for(auto i: result){
        result_.push_back(*(i.p));
        if(!(--maxNumberOfResults))
            break;
    }

    auto recommandResult = index->recommend(query);
    std::vector<SongInfo> recommandResult_;
    for(auto i: recommandResult){
        recommandResult_.push_back(*(i));
    }
    string json = "{\"seg\":" + JSON(wordsInQuery_) + ",\"result\":" + JSON(result_) + ",\"recommend\":"+ JSON(recommandResult_) + "}";

    for(char i : json){
        if(i=='\n')
            os << '\\' << 'n';
        else if(i != '\r')
            os << i;
    }
}

inline CharString getIdByFilename(CharString s){
    s = s.subString(0, s.indexOf('.'));
    while(s[0]=='0')
        s = s.subString(1, -1);
    return s;
}
void searchQueryHandler(istream& is, ostream& os){
    while(1){
        if(is.eof())
            break;
        string query;
        getline(is, query);
        CharStringList wordsInQuery = index->getSeg()->exec(query);
        auto result = index->search(wordsInQuery);

        for(auto& i : result){
            os << '(' << getIdByFilename(i.p->origin) << ',' << i.weight << ')' << ' ';
        }
        os << '\n';
    }
}

void recommendationQueryHandler(istream& is, ostream& os){
    while(1){
        if(is.eof())
            break;
        string _;
        getline(is, _);
        CharString query(_);
        
        auto result = index->recommend(query);

        if(result.size()==0)
            os << "Song with specified title not found.";
        else{
            bool flag = false; //special handling for the first item in result
            for(auto& i: result)
                if(flag)
                    os << '(' << getIdByFilename(i->origin) << ',' << i->title << ')' << ',';
                else
                    flag = true;
        }
        os << '\n';
    }
}

int processAllSongs(){
    string input_directory = "pages_300\\";
    CharStringList filenames = getInputFilenames(input_directory);
    for(int i=0; i<filenames.length; i++){
        CharString filename = filenames[i];
        CharString full_filename = input_directory + filenames[i];
        cout << "Processing " << filename << endl;
        CharString content = getFileContent(full_filename);
        Parser parser(content);
        SongInfo song = parser.getSongInfo();
        song.origin = filename;
        index->insert(song);
    }
    return 0;
}


int main(){
#ifdef DEBUGGING
    system("printDateAndTime");
#endif

    index = new InvertedIndex();

#ifdef DEBUGGING
    system("printDateAndTime");
#endif

    processAllSongs();

    //just for fun
    /*index->getKeywords().travel([](InvertedIndex::Keywords::Pair p){
        cout << p.key << ',' << p.value.numberOfAppearances << endl;
    });*/


    int func = 2; //function switch
    switch(func){
    case 0: //GUI, server only (doesn't open browser)
        puts("Starting web server...");
        startServer(queryApiHandler, false);
        break;
    case 1: //GUI
        puts("Starting web server and your default browser...");
        startServer(queryApiHandler, true);
        break;
    case 2: //keyword search
        puts("reading query1.txt...");
        searchQueryHandler(
#ifdef DEBUGGING
            std::cin, std::cout);
#else
            ifstream("query1.txt"), 
            ofstream("result1.txt"));
#endif
        break;
    case 3: //recommendation
        puts("reading query2.txt...");
        recommendationQueryHandler(
#ifdef DEBUGGING
            std::cin, std::cout);
#else
            ifstream("query2.txt"), 
            ofstream("result2.txt"));
#endif
        break;
    }
    
    cout << "All done. Bye.\n";
    delete index;
    return 0;
}
