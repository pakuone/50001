#include <iostream>
#include "DataStruct.h"
#include <vector>
#include <limits>
#include <algorithm>
#include <iterator>

int main() {
    std::vector<DataStruct> data;

    while (true) {
        std::copy(
            std::istream_iterator<DataStruct>(std::cin),
            std::istream_iterator<DataStruct>(),
            std::back_inserter(data)
        );

        if (std::cin.eof()) {
            break;
        }

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            break;
        }
    }

    std::sort(data.begin(), data.end(), comp);

    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );

    return 0;
}
