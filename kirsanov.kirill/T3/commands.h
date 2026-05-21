#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "polygon.h"
#include <vector>
#include <functional>
#include <cstddef>

namespace kirsanov
{
    // Базовая сумма площадей по предикату
    double totalArea(const std::vector<Polygon>& polys, std::function<bool(const Polygon&)> pred);

    // Средняя арифметическая площадь
    double meanArea(const std::vector<Polygon>& polys);

    // Максимальная площадь и количество вершин
    double maxArea(const std::vector<Polygon>& polys);
    size_t maxVertexes(const std::vector<Polygon>& polys);

    // Минимальная площадь и количество вершин
    double minArea(const std::vector<Polygon>& polys);
    size_t minVertexes(const std::vector<Polygon>& polys);

    // Подсчёт фигур по предикату
    size_t countPolygons(const std::vector<Polygon>& polys, std::function<bool(const Polygon&)> pred);

    // PERMS: количество перестановок
    size_t countPerms(const std::vector<Polygon>& polys, const Polygon& target);

    // RIGHTSHAPES: количество фигур с прямыми углами
    size_t countRightShapes(const std::vector<Polygon>& polys);
}

#endif
