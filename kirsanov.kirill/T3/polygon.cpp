#include "polygon.h"
#include <cmath>
#include <algorithm>
#include <numeric>
#include <cstddef>

namespace kirsanov
{
    // Сравнение двух точек по координатам
    bool Point::operator==(const Point& other) const
    {
        return x == other.x && y == other.y;
    }

    bool Point::operator!=(const Point& other) const
    {
        return !(*this == other);
    }

    // Сравнение двух многоугольников (вершины должны идти в том же порядке)
    bool Polygon::operator==(const Polygon& other) const
    {
        if (points.size() != other.points.size())
            return false;
        return points == other.points;
    }

    bool Polygon::operator!=(const Polygon& other) const
    {
        return !(*this == other);
    }

    // Возвращает количество вершин
    size_t Polygon::vertexCount() const
    {
        return points.size();
    }

    // Площадь по формуле Гаусса (метод шнурков)
    double Polygon::area() const
    {
        if (points.size() < 3)
            return 0.0;

        // Создаём вектор индексов [0, 1, 2, ..., size-1]
        std::vector<size_t> indices(points.size());
        std::iota(indices.begin(), indices.end(), 0);

        // Вычисляем сумму через accumulate
        double s = std::accumulate(indices.begin(), indices.end(), 0.0,
            [this](double sum, size_t i) {
                const Point& p1 = points[i];
                const Point& p2 = points[(i + 1) % points.size()];  // замыкание на первую
                return sum + static_cast<double>(p1.x * p2.y - p2.x * p1.y);
            });

        return std::abs(s) / 2.0;
    }

    // Проверка, является ли другой многоугольник перестановкой текущего
    bool Polygon::isPermutationOf(const Polygon& other) const
    {
        if (points.size() != other.points.size())
            return false;

        return std::is_permutation(points.begin(), points.end(),
            other.points.begin(), other.points.end());
    }

    // Проверка наличия хотя бы одного прямого угла
    bool Polygon::hasRightAngle() const
    {
        if (points.size() < 3)
            return false;

        // Создаём вектор индексов
        std::vector<size_t> indices(points.size());
        std::iota(indices.begin(), indices.end(), 0);

        // any_of проверяет, существует ли хотя бы один прямой угол
        return std::any_of(indices.begin(), indices.end(),
            [this](size_t i) {
                const Point& a = points[i];                     // предыдущая вершина
                const Point& b = points[(i + 1) % points.size()]; // вершина угла
                const Point& c = points[(i + 2) % points.size()]; // следующая вершина

                // Векторы ab и bc
                int dx1 = b.x - a.x;
                int dy1 = b.y - a.y;
                int dx2 = c.x - b.x;
                int dy2 = c.y - b.y;

                // Скалярное произведение == 0 означает прямой угол
                return (dx1 * dx2 + dy1 * dy2 == 0);
            });
    }
}
