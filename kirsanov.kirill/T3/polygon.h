#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <cstddef>

namespace kirsanov
{

    struct Point
    {
        int x, y;
        bool operator==(const Point& other) const;  // сравнение точек
        bool operator!=(const Point& other) const;
    };

    struct Polygon
    {
        std::vector<Point> points;  // вектор вершин

        // Операторы сравнения (полное совпадение последовательности)
        bool operator==(const Polygon& other) const;
        bool operator!=(const Polygon& other) const;

        size_t vertexCount() const;                    // количество вершин
        double area() const;                           // площадь (формула Гаусса)
        bool isPermutationOf(const Polygon& other) const;  // перестановка (PERMS)
        bool hasRightAngle() const;                    // есть ли прямой угол (RIGHTSHAPES)
    };
}

#endif
