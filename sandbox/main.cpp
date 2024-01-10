#include "purple.h"
#include "pan.h"

void test_log(){
    purple::Log::i("tag3","hello purple for info");
    purple::Log::w("tag2","hello purple2222");
    purple::Log::e("tag1","hello purple11111");
    purple::Log::log("hello logs");

    int count = 0;
    count++;
    purple::Log::log("count:%d" , count);
    purple::Log::e("test" , "error : %d , %s" , count + 1 , "ha this a test case");

    purple::Log::log("call pan lib:\n %s" , pan::FindPanLibInfo().c_str());
}

int main(){
    purple::Application app;
    return app.execute();
}