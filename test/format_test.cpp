#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

// template<typename T>
// std::string FormatString(const T& fmt){
//     std::stringstream ss;
//     ss << fmt;
//     return ss.str();
// }

// template<typename T , typename... Args>
// std::string FormatString(const T& fmt , Args... args){
//     std::stringstream ss;
//     ss << fmt;
//     return ss.str() + FormatString(args...);
// }

// template<typename T, typename... Args>
// std::string _FormatString(std::vector<std::string> &splitStringList, 
//     int index, 
//     T subStr, 
//     Args ... args){
//     std::stringstream ss;
//     if(splitStringList.size() <= index){
//         std::stringstream ss;
//         ss << subStr;
//         std::cout << "final =" << ss.str() << std::endl; 
//         return ss.str();
//     }else{
//         ss << subStr;
//         ss << splitStringList[index];
//         // ss << subStr;
//         std::cout << "subStr =" << ss.str() << std::endl; 
//         return _FormatString(splitStringList ,index + 1 , ss.str(),args...);
//     }
// }

// // template<typename T ,typename... Args>
// // std::string _FormatString(std::vector<std::string> &splitStringList, 
// //     int index,
// //     T subStr){
// //     std::stringstream ss;
// //     ss << subStr;
// //     std::cout << "final =" << ss.str() << std::endl; 
// //     return ss.str();
// // }

// std::vector<std::string> SplitFormatString(std::string &formatStr){
//     std::vector<std::string> splitList;
//     bool isEat = true;
//     std::string subStr = "";
//     for(int i = 0 ; i < formatStr.size() ;i++){
//         auto ch = formatStr[i];
//         if(ch == '{'){
//             if(isEat){
//                 isEat = false;

//                 if(!subStr.empty()){
//                     splitList.emplace_back(subStr);
//                     subStr = "";
//                 }
//             }
//         }else if(ch == '}'){
//             if(!isEat){
//                 isEat = true;
//             }
//         }else{
//             if(isEat){
//                 subStr += ch;
//             }
//         }
//     }//end for i
//     if(!subStr.empty()){
//         splitList.emplace_back(subStr);
//         subStr = "";
//     }

//     return splitList;
// }

// template<typename... Args>
// std::string FormatString(std::string formatStr, Args ... args){
//     std::vector<std::string> splitStringList = SplitFormatString(formatStr);
//     std::string result;
//     return _FormatString(splitStringList , 0 , result, args...);
// }

// template<typename T , typename... Args>
// std::string _FormatString(std::string &formatStr , int start){
//     std::cout << "final :::::" << std::endl;
//     std::stringstream ss;
//     // ss << sub;
//     return ss.str();
// }

// template<typename T , typename... Args>
// std::string _FormatString(std::string &formatStr , int start ,T sub, Args... args){
//     int index =  start;
//     bool eatMode = true;
//     std::stringstream ss;
//     // ss << sub;
//     for(;index < formatStr.size();index++){
//         auto ch = formatStr[index];
//         if(ch == '{'){
//             eatMode = false;
//         }else if(ch == '}'){
//             if(!eatMode){
//                 // ss << args;
//                 std::cout << sub << std::endl;
//                 ss << sub;
//                 ss << _FormatString(formatStr , index + 1, ss.str() , args...);
//                 return ss.str();
//             }
//         } else {
//             if(eatMode){
//                 ss << ch;
//             }
//         }
//     }//end for index;
//     return ss.str();
// }

// template<typename... Args>
// std::string FormatString(std::string formatStr, Args... args){
//     // std::vector<std::string> splitStringList = SplitFormatString(formatStr);
//     std::string result;
//     return _FormatString(formatStr , 0 , result, args...);
// }


// template<typename... Args>
// std::string FormatString(const std::string format, Args ... args){
//     std::stringstream ss;
//     size_t argIndex = 0;
//     const size_t len = format.length();
    
//     for(size_t i = 0; i < len; i++) {
//         if (format[i] == '{' && i + 1 < len && format[i + 1] != '}') {
//             size_t end = format.find('}', i + 1);
//             if (end != std::string::npos) {
//                 // ss << format.substr(i + 1, end - i - 1);
//                 ss << FormatString(ss.str() , args...);
//                 i = end;
//             } else {
//                 // throw std::invalid_argument("Invalid format string: missing '}'");
//                 std::cerr << "Invalid format string: missing '}'" << std::endl;
//             }
//         } else {
//             ss << format[i];
//         }
//     }//end for i
//     return ss.str();
// }

template<typename... Args>
std::string FormatString(std::string format , Args... args){
    int lenStr = std::snprintf(nullptr, 0, format.c_str(), args...);
    if(lenStr <= 0){
        return "";
    }

    lenStr++;
    auto pstrOut =new char[lenStr];
    std::snprintf(pstrOut, lenStr, format.c_str(), args...);
    std::string str(pstrOut);

    delete[] pstrOut;
    return str;
}

int main(){
    auto str = FormatString("hello this %d ,200 %d, 300 %s,hahaha?" , 1 , 2,"test for string");
    std::cout <<"format result:" << str << std::endl;
    // std::cout << "\033[31;4mRed Underline Text\033[0m" << std::endl;
    // printf("\033[4;31;42m color!!! \033[m Hello \n");
    return 0;
}


