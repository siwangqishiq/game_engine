#include <gtest/gtest.h>
#include "json.h"

TEST(PurpleJsonTest, JsonObject_init) {
    using namespace purple;

    auto json = JsonObject::create();
    EXPECT_EQ(L"{}", json->toJsonString());
}

TEST(PurpleJsonTest, JsonObject_set_int) {
    using namespace purple;

    auto json = JsonObject::create();
    json->put("key1" , 1);
    json->put("key2" , 2);
    json->put("key3" , 303);

    EXPECT_EQ(1 , json->getInt("key1"));
    EXPECT_EQ(2 , json->getInt("key2"));
    EXPECT_EQ(303 , json->getInt("key3"));
}

TEST(PurpleJsonTest, JsonObject_set_float) {
    using namespace purple;

    auto json = JsonObject::create();
    json->put("key1" , 1.0f);
    json->put("key2" , 2.0f);
    json->put("key3" , 3.0f);

    EXPECT_FLOAT_EQ(1.0f , json->getFloat("key1"));
    EXPECT_FLOAT_EQ(2.0f , json->getFloat("key2"));
    EXPECT_FLOAT_EQ(3.0f , json->getFloat("key3"));
}

TEST(PurpleJsonTest, JsonObject_set_string) {
    using namespace purple;

    auto json = JsonObject::create();

    json->put("key1" , L"key1_value");
    json->put("key2" , L"key2_value");
    json->put("key3" , L"key3_值");

    EXPECT_EQ(L"key1_value" , json->getString("key1"));
    EXPECT_EQ(L"key2_value" , json->getString("key2"));
    EXPECT_EQ(L"key3_值" , json->getString("key3"));
}

TEST(PurpleJsonTest, JsonObject_array){
    using namespace purple;
    auto jsonArray = JsonArray::create();
    EXPECT_EQ(L"[]" , jsonArray->toJsonString());
}

TEST(PurpleJsonTest, JsonObject_array_putint){
    using namespace purple;
    auto jsonArray = JsonArray::create();
    jsonArray->pushInt(1);
    jsonArray->pushInt(2);
    jsonArray->pushInt(3);

    EXPECT_EQ(L"[1,2,3]" , jsonArray->toJsonString());
}

TEST(PurpleJsonTest, JsonObject_array_string){
    using namespace purple;
    auto jsonArray = JsonArray::create();
    jsonArray->push(L"你好");
    jsonArray->push(L"世界");
    jsonArray->push(L"Hello");
    jsonArray->push(L"World");

    EXPECT_EQ(L"[\"你好\",\"世界\",\"Hello\",\"World\"]" , jsonArray->toJsonString());
}

TEST(PurpleJsonTest, JsonObject_parse){
    using namespace purple;
    std::wstring jsonString = L"{  \"name\" : \"maolilan\" ,  \"age\":17  , \"count\": 123.333 ,\"desc\":\"xxxxyyyyyzzzzz\"}";

    JsonParser parser;
    auto json = parser.parseJsonObject(jsonString);

    EXPECT_EQ(17 , json->getInt("age"));
    EXPECT_FLOAT_EQ(123.333f , json->getFloat("count"));
    EXPECT_EQ(L"maolilan" , json->getString("name"));
}

TEST(PurpleJsonTest, JsonObject_parse2){
    using namespace purple;
    auto subJson = JsonObject::create();
    subJson->put("name" , L"毛利兰");
    subJson->put("age" , 17);
    subJson->put("desc" , L"头上有犄角");

    EXPECT_EQ(L"头上有犄角" , subJson->getString("desc"));

    auto jsonStr = subJson->toJsonString();

    JsonParser parser;
    auto result = parser.parseJsonObject(jsonStr);
    EXPECT_EQ(L"头上有犄角" , result->getString("desc"));
    EXPECT_EQ(L"毛利兰" , result->getString("name"));
    EXPECT_EQ(17 , result->getInt("age"));
}

TEST(PurpleJsonTest, JsonObject_parse_circular){
    using namespace purple;
    auto _subJson = JsonObject::create();
    _subJson->put("name" , L"毛利兰");
    _subJson->put("age" , 17);
    _subJson->put("desc" , L"头上有犄角");
    
    auto _json = JsonObject::create();
    _json->put("friend" , _subJson);
    _json->put("score" , 27);
    _json->put("name" , L"工藤新一");
    _json->put("age" , 18);
    _json->put("score2" , 123456);
    _json->put("my" , L"HelloWorld");


    auto originJson = _json;
    std::wstring jsonStr = originJson->toJsonString();
    WriteStringToFile("out.json" , jsonStr);
    
    JsonParser parser;
    auto json = parser.parseJsonObject(jsonStr);

    auto originWifeJson = originJson->getJsonObject("friend");
    EXPECT_EQ(originWifeJson->getInt("age") , 17);

    auto wifeJson = json->getJsonObject("friend");
    EXPECT_EQ(originWifeJson->getInt("age") , wifeJson->getInt("age"));
    EXPECT_EQ(originWifeJson->getString("desc") , wifeJson->getString("desc"));
    EXPECT_EQ(originWifeJson->getString("name") , wifeJson->getString("name"));


    EXPECT_EQ(originJson->getInt("age") , json->getInt("age"));
    EXPECT_EQ(originJson->getString("name") , json->getString("name"));
}

TEST(PurpleJsonTest, JsonObject_json_from_string){
    using namespace purple;
    std::wstring str = L"{\"age\":18,\"friend\":{   \"age\":17,\"desc\":\"头上有犄角\",\"name\":\"毛利兰\"},\"my\":\"HelloWorld\",\"name\":\"工藤新一\",\"score\":27, \"add\":\"test add!!\",\"score2\":123456}";

    JsonParser parser;
    auto json = parser.parseJsonObject(str);
    EXPECT_EQ(18 , json->getInt("age"));
    EXPECT_EQ(27 , json->getInt("score"));
    EXPECT_EQ(123456 , json->getInt("score2"));
    EXPECT_EQ(L"test add!!" , json->getString("add"));
}

TEST(PurpleJsonTest, JsonObject_parse_circular2){
    using namespace purple;
    auto _subJson = JsonObject::create();
    _subJson->put("name" , L"毛利兰");
    _subJson->put("age" , 17);
    _subJson->put("desc" , L"头上有犄角");
    
    auto _json = JsonObject::create();
    _json->put("wife" , _subJson);
    _json->put("score" , 27);
    _json->put("name" , L"工藤新一");
    _json->put("age" , 18);
    _json->put("score2" , 123456);
    _json->put("my" , L"HelloWorld");


    auto originJson = _json;
    std::wstring jsonStr = originJson->toJsonString();
    WriteStringToFile("out.json" , jsonStr);
    
    JsonParser parser;
    auto json = parser.parseJsonObject(jsonStr);

    auto originWifeJson = originJson->getJsonObject("wife");
    EXPECT_EQ(originWifeJson->getInt("age") , 17);

    auto wifeJson = json->getJsonObject("wife");
    EXPECT_EQ(originWifeJson->getInt("age") , wifeJson->getInt("age"));
    EXPECT_EQ(originWifeJson->getString("desc") , wifeJson->getString("desc"));
    EXPECT_EQ(originWifeJson->getString("name") , wifeJson->getString("name"));
    
    EXPECT_EQ(originJson->getInt("age") , json->getInt("age"));
    EXPECT_EQ(originJson->getString("name") , json->getString("name"));
}

TEST(PurpleJsonTest, JsonObject_parse_circular3){
    using namespace purple;
    auto _subJson1 = JsonObject::create();
    _subJson1->put("name" , L"毛利兰");
    _subJson1->put("age" , 17);
    _subJson1->put("desc" , L"头上有犄角");

    auto _subJson2 = JsonObject::create();
    _subJson2->put("name" , L"毛利兰2");
    _subJson2->put("age" , 17);
    _subJson2->put("desc" , L"头上有犄角2");
    
    auto _json = JsonObject::create();
    _json->put("friend1" , _subJson1);
    _json->put("friend2" , _subJson2);
    _json->put("my" , L"HelloWorld");

    auto originJson = _json;
    std::wstring jsonStr = originJson->toJsonString();
    WriteStringToFile("out.json" , jsonStr);
    
    JsonParser parser;
    auto json = parser.parseJsonObject(jsonStr);

    auto originWifeJson = originJson->getJsonObject("friend2");
    EXPECT_EQ(originWifeJson->getInt("age") , 17);

    auto wifeJson = json->getJsonObject("friend2");
    EXPECT_EQ(originWifeJson->getInt("age") , wifeJson->getInt("age"));
    EXPECT_EQ(originWifeJson->getString("desc") , wifeJson->getString("desc"));
    EXPECT_EQ(originWifeJson->getString("name") , wifeJson->getString("name"));

    EXPECT_EQ(originJson->getInt("age") , json->getInt("age"));
    EXPECT_EQ(originJson->getString("name") , json->getString("name"));
}

TEST(PurpleJsonTest, JsonArray_parse){
    using namespace purple;
    auto _jsonArray = JsonArray::create();
    _jsonArray->push(L"AAA");
    _jsonArray->push(L"BBB");
    _jsonArray->push(L"CCC");

    std::wstring arrayStr = _jsonArray->toJsonString();

    JsonParser parser;
    auto jsonArray = parser.parseJsonArray(arrayStr);

    EXPECT_EQ(L"AAA" , jsonArray->getString(0));
    EXPECT_EQ(L"BBB" , jsonArray->getString(1));
    EXPECT_EQ(L"CCC" , jsonArray->getString(2));
}

TEST(PurpleJsonTest, JsonArray_parse2){
    using namespace purple;
     auto _jsonArray = JsonArray::create();
    _jsonArray->push(L"你好");
    _jsonArray->push(L"世界");
    _jsonArray->push(L"毛利兰");
    _jsonArray->push(L"工藤新一");

    std::wstring arrayStr = _jsonArray->toJsonString();
    // std::wcout << arrayStr << std::endl;

    JsonParser parser;
    auto jsonArray = parser.parseJsonArray(arrayStr);

    EXPECT_EQ(L"你好" , jsonArray->getString(0));
    EXPECT_EQ(L"世界" , jsonArray->getString(1));
    EXPECT_EQ(L"工藤新一" , jsonArray->getString(3));
    EXPECT_EQ(L"毛利兰" , jsonArray->getString(2));
}

TEST(PurpleJsonTest, JsonArray_parse_init_array){
    using namespace purple;
    std::wstring str = L"  [ 1,  -2,33,4, 5, 6,  7] ";
    JsonParser parser;
    auto jsonArray = parser.parseJsonArray(str);

    EXPECT_EQ(7 , jsonArray->size());
    
    EXPECT_EQ(1 , jsonArray->getInt(0));
    EXPECT_EQ(-2 , jsonArray->getInt(1));
    EXPECT_EQ(33 , jsonArray->getInt(2));
    EXPECT_EQ(4 , jsonArray->getInt(3));
    EXPECT_EQ(5 , jsonArray->getInt(4));
    EXPECT_EQ(6 , jsonArray->getInt(5));
    EXPECT_EQ(7 , jsonArray->getInt(6));
}

TEST(PurpleJsonTest, JsonArray_parse_float_value){
    using namespace purple;
    auto _json = JsonArray::create();
    for(int i = 1 ; i <= 200 ; i++){
        _json->push(i + 0.33f);
    }//end for i

    JsonParser parser;
    auto str = _json->toJsonString();
    auto json = parser.parseJsonArray(str);

    for(int i = 0; i < json->size() ; i++){
        EXPECT_EQ(_json->getFloat(i) , json->getFloat(i));
    }//end for i
}

TEST(PurpleJsonTest, JsonArray_parse_jsonobject){
    using namespace purple;
    auto _json1 = JsonObject::create();
    _json1->put("name" , L"maolilan");
    _json1->put("age" , 17);
    auto _json2 = JsonObject::create();
    _json2->put("name" , L"xinyi");
    _json2->put("age" , 18);
    auto _json3 = JsonObject::create();
    _json3->put("name" , L"huiyuanai");
    _json3->put("age" , 19);

    std::shared_ptr<JsonArray> _jsonArray = JsonArray::create();
    _jsonArray->push(_json1);
    _jsonArray->push(_json2);
    _jsonArray->push(_json3);

    std::wstring str = _jsonArray->toJsonString();
    JsonParser parser;
    auto jsonArray = parser.parseJsonArray(str);

    EXPECT_EQ(3 , jsonArray->size());
    auto json1 = jsonArray->getJsonObject(0);
    auto json2 = jsonArray->getJsonObject(1);
    auto json3 = jsonArray->getJsonObject(2);

    EXPECT_EQ(_json1->getInt("age") , json1->getInt("age"));
    EXPECT_EQ(_json2->getInt("age") , json2->getInt("age"));
    EXPECT_EQ(_json3->getInt("age") , json3->getInt("age"));
    EXPECT_EQ(_json1->getString("name") , json1->getString("name"));
    EXPECT_EQ(_json2->getString("name") , json2->getString("name"));
    EXPECT_EQ(_json3->getString("name") , json3->getString("name"));
}

TEST(PurpleJsonTest, JsonArray_parse_contain_jsonarray){
    using namespace purple;
    auto _json1 = JsonObject::create();
    _json1->put("name" , L"maolilan");
    _json1->put("age" , 17);
    auto _json2 = JsonObject::create();
    _json2->put("name" , L"xinyi");
    _json2->put("age" , 18);
    auto _json3 = JsonObject::create();
    _json3->put("name" , L"huiyuanai");
    _json3->put("age" , 19);

    std::shared_ptr<JsonArray> _jsonArray = JsonArray::create();
    _jsonArray->push(_json1);
    _jsonArray->push(_json2);
    _jsonArray->push(_json3);

    auto _json = JsonObject::create();
    _json->putString("name" , L"Hello");
    _json->putInt("id" , 1001);
    _json->putJsonArray("friends" , _jsonArray);

    WriteStringToFile("out.json" , _json->toJsonString());
    JsonParser parser;
    auto str = _json->toJsonString();
    auto json = parser.parseJsonObject(str);

    EXPECT_EQ(_json->getString("name") , json->getString("name"));
    EXPECT_EQ(_json->getInt("age") , json->getInt("age"));

    std::shared_ptr<JsonArray> friendJsonArray = json->getJsonArray("friends");
    EXPECT_EQ(_jsonArray->size() , friendJsonArray->size());

    auto json1 = friendJsonArray->getJsonObject(0);
    auto json2 = friendJsonArray->getJsonObject(1);
    auto json3 = friendJsonArray->getJsonObject(2);

    EXPECT_EQ(_json1->getInt("age") , json1->getInt("age"));
    EXPECT_EQ(_json2->getInt("age") , json2->getInt("age"));
    EXPECT_EQ(_json3->getInt("age") , json3->getInt("age"));
    EXPECT_EQ(_json1->getString("name") , json1->getString("name"));
    EXPECT_EQ(_json2->getString("name") , json2->getString("name"));
    EXPECT_EQ(_json3->getString("name") , json3->getString("name"));
}

TEST(PurpleJsonTest, JsonArray_parse_contain_list1){
    using namespace purple;
    auto _obj = JsonObject::create();
    auto _list = JsonArray::create();
    _obj->putJsonArray("list" , _list);

    for(int i = 0; i < 5 ;i++){
        auto _item = JsonObject::create();
        _item->putString("value" , L"X");
        _item->putInt("width" , 100);
        _item->putInt("height" , 200);
        _item->putString("texture" , L"test.png");

        _list->pushJsonObject(_item);
    }//end for i

    std::wstring str = _obj->toJsonString();

    WriteStringToFile("out.json" , str);

    JsonParser parser;
    auto json = parser.parseJsonObject(str);
    auto array = json->getJsonArray("list");
    EXPECT_EQ(5 , array->size());
}

TEST(PurpleJsonTest, JsonArray_parse_contain_list2){
    using namespace purple;
    auto _obj = JsonObject::create();
    auto _list = JsonArray::create();
    _obj->putJsonArray("list" , _list);

    int len = 4;
    for(int i = 0; i < len ;i++){
        auto _item = JsonObject::create();
        _item->putString("value" , L"X");
        _item->putInt("width" , 100);
        _item->putInt("height" , 200);
        _item->putString("texture" , L"test.png");
        
        auto _arr = JsonArray::create();
        _arr->pushFloat(1.0f);
        _arr->pushFloat(2.0f);
        _arr->pushFloat(3.0f);
        _arr->pushFloat(4.0f);
        
        _item->putJsonArray("texCoords" , _arr);

        _list->pushJsonObject(_item);
    }//end for i

    std::wstring str = _obj->toJsonString();

    WriteStringToFile("out2.json" , str);

    JsonParser parser;
    auto json = parser.parseJsonObject(str);
    auto array = json->getJsonArray("list");
    EXPECT_EQ(len , array->size());
}

//
// TEST(PurpleJsonTest, JsonObject_long_json_string){
//     using namespace purple;
//     std::wstring str = ReadTextFileAsWstring("../../assets/text/font1/char_config.json");
//     JsonParser parser;
//     auto json = parser.parseJsonObject(str);
//     auto jsonList = json->getJsonArray("list");
//     for(int i = 0 ; i < jsonList->size();i++){
//         auto itemJson = jsonList->getJsonObject(i);
//         EXPECT_TRUE(itemJson->getString("texture").find(L"font_texture_") == 0);
//     }//end for i
// }

