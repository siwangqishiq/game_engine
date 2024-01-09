#include "purple.h"

int main(){

    purple::Log::i("tag3","hello purple for info");
    purple::Log::w("tag2","hello purple2222");
    purple::Log::e("tag1","hello purple11111");
    purple::Log::log("hello logs");

    int count = 0;
    count++;
    purple::Log::log("count:%d" , count);
    purple::Log::e("test" , "error : %d , %s" , count + 1 , "ha this a test case");
    
    return 0;
}