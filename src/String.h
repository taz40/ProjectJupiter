#ifndef __STRING_H
#define __STRING_H

#include "types.h"

class String{
private:
public:
    String();
    String(const char* string);
    ~String();
    char* string;
    uint16_t length;
    bool equals(String* other);
    void append(const char* other);
    void remove(int numchars);
};

#endif
