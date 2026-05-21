#ifndef IOFMTGUARD_H
#define IOFMTGUARD_H

#include <ios>

namespace kirsanov
{
    class iofmtguard
    {
    public:
        explicit iofmtguard(std::basic_ios<char>& s);
        ~iofmtguard();

    private:
        std::basic_ios<char>& s_;
        std::streamsize width_;
        char fill_;
        std::streamsize precision_;
        std::ios::fmtflags fmt_;
    };
}

#endif
