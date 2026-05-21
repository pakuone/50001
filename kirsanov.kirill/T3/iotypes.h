#ifndef IOTYPES_H
#define IOTYPES_H

#include "iofmtguard.h"
#include "polygon.h"
#include <iostream>

namespace kirsanov
{
    // Обёртка для чтения точки из потока в формате (x;y)
    struct PointIO
    {
        Point& ref;  // ссылка на объект для записи
    };

    // Обёртка для чтения многоугольника из потока
    struct PolygonIO
    {
        Polygon& ref;
    };

    std::istream& operator>>(std::istream& in, PointIO&& dest);
    std::istream& operator>>(std::istream& in, PolygonIO&& dest);
}

#endif
