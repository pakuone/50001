#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H
#include <string>
#include <iostream>

struct DataStruct
{
    double key1; // DBL LIT
    unsigned long long key2; // ULL HEX
    std::string key3;
};

struct DelimiterIO {
    char exp;
};

struct DblLitIO {
    double& ref;
};

struct UllHexIO {
    unsigned long long& ref;
};

struct StringIO {
    std::string& ref;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
std::istream& operator>>(std::istream& in, DblLitIO&& dest);
std::istream& operator>>(std::istream& in, UllHexIO&& dest);
std::istream& operator>>(std::istream& in, StringIO&& dest);
std::istream& operator>>(std::istream& in, DataStruct& dest);
std::ostream& operator<<(std::ostream& out, const DataStruct& dest);

bool comp(const DataStruct& s1, const DataStruct& s2);

#endif
