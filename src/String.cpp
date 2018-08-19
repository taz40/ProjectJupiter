#include "String.h"

String::String(){
    
}

String::String(const char* other){
    for(int i = 0; other[i] != '\0'; i++){
        string[i] = other[i];
        length = i+1;
    }
}

String::~String(){
    
}

bool String::equals(String* other){
    if(length != other->length){
        return false;
    }
    
    for(int i = 0; i < length; i++){
        if(string[i] != other->string[i]){
            return false;
        }
    }
    return true;
}

void String::append(const char* other){
    for(int i = 0; other[i] != '\0'; i++){
        string[length] = other[i];
        length++;
    }
}

void String::remove(int numchars){
    length -= numchars;
}
