#ifndef READER_H
#define READER_H

#include "polygon.h"
#include <vector>
#include <string>

namespace kirsanov
{
    std::vector<Polygon> readPolygons(const std::string& filename);
}

#endif
