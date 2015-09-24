//
// Created by haohanwang on 9/23/15.
//

#ifndef SOCKETSERVER_JSONENCODER_H
#define SOCKETSERVER_JSONENCODER_H

#include<vector>

using namespace std;

#include "json/json.h"

template<typename T>
class JsonEncoder {
public:
    JsonEncoder *jsonEncoder;

    static std::string typeOf(T){
        std::string Type="unknown";
        if(std::is_same<T,int>::value) Type="int";
        if(std::is_same<T,std::string>::value) Type="string";
        if(std::is_same<T,float>::value) Type="float";
        return Type;}

    static string encode(vector<T> input) {
        Json::Value value;
        for (int i = 0; i < input.size(); i++) {
            value[to_string(i)] = to_string(input[i]);
        }
        Json::Value root;
        root["class"] = "vector";
        root["type"] = typeOf(input[0]);
        root["size"] = to_string(input.size());
        root["value"] = value;
        Json::StyledWriter writer;
        return writer.write(root);
    }

    static string encode(T input){
        Json::Value root;
        root["class"] = "single_value";
        root["type"] = typeOf(input);
        root["size"] = 1;
        root["value"] = to_string(input);
        Json::StyledWriter writer;
        return writer.write(root);
    }

    static T decode_single_value(Json::Value root){
        if (root["type"] == "int")
            return stoi(root["value"].asString());
        if (root["type"] == "float")
            return stof(root["value"].asString());
        if (root["type"] == "string")
            return root["value"].asString();
        return 0;
    }

    static vector<T> decode_vector(Json::Value root){
        vector<T> result;
        int s = stoi(root["size"].asString());
        if (root["type"] == "int")
            vector<int> result(s);
        else if (root["type"] == "float"){
            vector<float> result(s);
            Json::Value value = root["value"];
            for (int i=0; i<s; i++){
                result[i] = stof(value[to_string(i)].asString());
            }
            return result;
        }

        else if (root["type"] == "string")
            vector<string> result(s);

        return result;
    }

    static vector<T> decode_vector_main(char buffer []){
        Json::Value root;
        Json::Reader reader;
        bool parsedSuccess = reader.parse(buffer, root, false);
        if (parsedSuccess < 0) throw std::runtime_error( "Parsing Json String Error" );
        return decode_vector(root);
    }

    static T decode_single_value_main(char buffer []){
        Json::Value root;
        Json::Reader reader;
        bool parsedSuccess = reader.parse(buffer, root, false);
        if (parsedSuccess < 0) throw std::runtime_error( "Parsing Json String Error" );
            return decode_single_value(root);
    }

private:
    JsonEncoder() { };
};


#endif //SOCKETSERVER_JSONENCODER_H
