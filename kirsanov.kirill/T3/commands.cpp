#include "commands.h"
#include <algorithm>
#include <numeric>
#include <stdexcept>

namespace kirsanov
{
    // Сумма площадей фигур, удовлетворяющих предикату
    // Используем accumulate с лямбдой, которая суммирует только подходящие площади
    double totalArea(const std::vector<Polygon>& polys, std::function<bool(const Polygon&)> pred)
    {
        return std::accumulate(polys.begin(), polys.end(), 0.0,
            [&pred](double sum, const Polygon& p) {
                return sum + (pred(p) ? p.area() : 0.0);
            });
    }

    // Средняя арифметическая площадь
    double meanArea(const std::vector<Polygon>& polys)
    {
        if (polys.empty())
            throw std::runtime_error("No polygons");

        double sum = std::accumulate(polys.begin(), polys.end(), 0.0,
            [](double acc, const Polygon& p) {
                return acc + p.area();
            });
        return sum / polys.size();
    }

    // Максимальная площадь
    double maxArea(const std::vector<Polygon>& polys)
    {
        if (polys.empty())
            throw std::runtime_error("No polygons");

        auto it = std::max_element(polys.begin(), polys.end(),
            [](const Polygon& a, const Polygon& b) {
                return a.area() < b.area();
            });
        return it->area();
    }

    // Максимальное количество вершин
    size_t maxVertexes(const std::vector<Polygon>& polys)
    {
        if (polys.empty())
            throw std::runtime_error("No polygons");

        auto it = std::max_element(polys.begin(), polys.end(),
            [](const Polygon& a, const Polygon& b) {
                return a.vertexCount() < b.vertexCount();
            });
        return it->vertexCount();
    }

    // Минимальная площадь
    double minArea(const std::vector<Polygon>& polys)
    {
        if (polys.empty())
            throw std::runtime_error("No polygons");

        auto it = std::min_element(polys.begin(), polys.end(),
            [](const Polygon& a, const Polygon& b) {
                return a.area() < b.area();
            });
        return it->area();
    }

    // Минимальное количество вершин
    size_t minVertexes(const std::vector<Polygon>& polys)
    {
        if (polys.empty())
            throw std::runtime_error("No polygons");

        auto it = std::min_element(polys.begin(), polys.end(),
            [](const Polygon& a, const Polygon& b) {
                return a.vertexCount() < b.vertexCount();
            });
        return it->vertexCount();
    }

    // Обёртка над std::count_if
    size_t countPolygons(const std::vector<Polygon>& polys, std::function<bool(const Polygon&)> pred)
    {
        return std::count_if(polys.begin(), polys.end(), pred);
    }

    // PERMS: сколько фигур являются перестановкой целевой
    size_t countPerms(const std::vector<Polygon>& polys, const Polygon& target)
    {
        return std::count_if(polys.begin(), polys.end(),
            [&target](const Polygon& p) { return p.isPermutationOf(target); });
    }

    // RIGHTSHAPES: сколько фигур содержат прямой угол
    size_t countRightShapes(const std::vector<Polygon>& polys)
    {
        return std::count_if(polys.begin(), polys.end(),
            [](const Polygon& p) { return p.hasRightAngle(); });
    }
}
