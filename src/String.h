#ifndef __STRING_H
#define __STRING_H

class String{
private:
public:
    String();
    String(const char* string);
    ~String();
    const char* string;
    uint16_t length;
    bool equals(String other);
    void append(const char* other);
}

#endif
