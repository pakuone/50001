#include "DataStruct.h"
#include "iofmtguard.h"
#include <iomanip>
#include <cstdlib>

std::istream& operator>>(std::istream& in, DelimiterIO&& dest) {
    std::istream::sentry sentry(in);

    if (!sentry) {
        return in;
    }

    char c = '0';
    in >> c;

    if (in && (c != dest.exp)) {
        in.setstate(std::ios::failbit);
    }

    return in;
}

std::istream& operator>>(std::istream& in, DblLitIO&& dest)
{
    std::istream::sentry sentry(in);

    if (!sentry) {
        return in;
    }

    std::string s;
    char c;

    while (in.get(c) && c != 'd' && c != 'D')
    {
        s += c;
    }

    if (!in || (c != 'd' && c != 'D')) {
        in.setstate(std::ios::failbit);
        return in;
    }

    size_t dotPos = s.find('.');

    if (dotPos == std::string::npos)
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    if (dotPos == 0) {
        in.setstate(std::ios::failbit);
        return in;
    }

    for (size_t i = 0; i < dotPos; ++i) {
        if (!isdigit(s[i])) {
            in.setstate(std::ios::failbit);
            return in;
        }
    }

    if (dotPos + 1 >= s.size()) {
        in.setstate(std::ios::failbit);
        return in;
    }

    for (size_t i = dotPos + 1; i < s.size(); ++i) {
        if (!isdigit(s[i])) {
            in.setstate(std::ios::failbit);
            return in;
        }
    }

    dest.ref = std::stod(s);
    return in;
}

std::istream& operator>>(std::istream& in, UllHexIO&& dest) {
    std::istream::sentry sentry(in);

    if (!sentry)
    {
        return in;
    }

    iofmtguard guard(in);

    char c1 = '0';
    char c2 = '0';
    in >> c1 >> c2;

    if (c1 == '0' && (c2 == 'x' || c2 == 'X')) {
        in >> std::hex >> dest.ref;
    }
    else {
        in.setstate(std::ios::failbit);
    }

    return in;
}

std::istream& operator>>(std::istream& in, StringIO&& dest)
{
    std::istream::sentry sentry(in);

    if (!sentry)
    {
        return in;
    }

    in >> DelimiterIO{ '"' };

    if (in) {
        return std::getline(in, dest.ref, '"');
    }

    return in;
}

std::istream& operator>>(std::istream& in, DataStruct& dest) {
    std::istream::sentry sentry(in);

    if (!sentry) {
        return in;
    }

    using del = DelimiterIO;
    using dbl = DblLitIO;
    using ull = UllHexIO;
    using str = StringIO;

    bool hasKey1 = false;
    bool hasKey2 = false;
    bool hasKey3 = false;

    DataStruct temp;

    in >> del{ '(' } >> del{ ':' };
    if (!in) {
        return in;
    }

    while (in) {

        if (in.peek() == ')') {
            in >> del{ ')' };
            break;
        }

        std::string key;

        in >> key;
        if (!in) {
            break;
        }

        if (key == "key1") {
            in >> dbl{ temp.key1 };
            hasKey1 = true;
        }
        else if (key == "key2") {
            in >> ull{ temp.key2 };
            hasKey2 = true;
        }
        else if (key == "key3") {
            in >> str{ temp.key3 };
            hasKey3 = true;
        }
        else {
            in.setstate(std::ios::failbit);
        }

        if (!in) {
            break;
        }

        in >> del{ ':' };
    }

    if (hasKey1 && hasKey2 && hasKey3) {
        dest = std::move(temp);
    }
    else {
        in.setstate(std::ios::failbit);
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& src) {
    std::ostream::sentry sentry(out);
    if (!sentry) {
        return out;
    }

    iofmtguard guard(out);

    out << "(:key1 " << std::fixed << std::setprecision(1) << src.key1 << "d";
    out << ":key2 0x" << std::hex << std::uppercase << src.key2;
    out << ":key3 \"" << src.key3 << "\":)";

    return out;
}

bool comp(const DataStruct& s1, const DataStruct& s2) {
    if (s1.key1 != s2.key1) {
        return s1.key1 < s2.key1;
    }

    if (s1.key2 != s2.key2) {
        return s1.key2 < s2.key2;
    }

    return s1.key3.length() < s2.key3.length();
}
