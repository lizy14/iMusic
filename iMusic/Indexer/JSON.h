#pragma once

#include "../Parser/SongInfo.h"
#include "../Parser/List.h"

#include <sstream>
#include <vector>
namespace Zhaoyang{
    using std::string;
    using std::stringstream;
    using std::vector;

    string JSON(SongInfo song);

    string JSON(string str);

    template <class T>
    string JSON(List<T> list){
        stringstream ss;
        ss << '[';
        for(int i=0; i<list.length; i++){
            if(i)
                ss << ',';
            ss << JSON(list[i]);
        }
        ss << ']';
        return ss.str();
    }

    template <class T>
    string JSON(vector<T> list){
        stringstream ss;
        ss << '[';
        for(int i=0; i<list.size(); i++){
            if(i)
                ss << ',';
            ss << JSON(list[i]);
        }
        ss << ']';
        return ss.str();
    }

}