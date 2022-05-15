#pragma once 

#include <string>

#define ____WINDOWS_8____ 0
void findAndReplaceAll(std::string & data, std::string toSearch, std::string replaceStr){
    // Get the first occurrence
    size_t pos = data.find(toSearch);
    // Repeat till end is reached
    while( pos != std::string::npos){
        // Replace this occurrence of Sub String
        data.replace(pos, toSearch.size(), replaceStr);
        // Get the next occurrence from the current position
        pos = data.find(toSearch, pos + replaceStr.size());
    }
}

void normalizePathToWindows8(std::string& path){
#if ____WINDOWS_8____
    findAndReplaceAll(path,"/","\\");
    path.insert(0,"..\\",3);
#endif
}

std::string normalizePathToWindows8(const std::string& path){
#if ____WINDOWS_8____
        std::string copy(path);
        findAndReplaceAll(copy,"/","\\");
        copy.insert(0,"..\\",3);
        return copy ;
#else 
        return path ;
#endif
}