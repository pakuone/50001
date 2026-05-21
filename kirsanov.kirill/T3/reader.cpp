#include "reader.h"
#include "iotypes.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstddef>

namespace kirsanov
{
    std::vector<Polygon> readPolygons(const std::string& filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
            throw std::runtime_error("Cannot open file");

        std::vector<Polygon> polygons;
        std::string line;

        // Читаем файл построчно
        while (std::getline(file, line))
        {
            if (line.empty())
                continue;  // пропускаем пустые строки

            std::istringstream iss(line);
            int n;
            iss >> n;  // читаем количество вершин

            //проверка на то, удалось ли чтение
            if (iss.fail() || n < 3)
                continue;

            Polygon poly;
            bool valid = true;

            // Читаем n точек, используя обёртку PointIO
            for (int i = 0; i < n; ++i)
            {
                Point p;
                iss >> PointIO{ p };  // читаем точку в формате (x;y)
                if (iss.fail())
                {
                    valid = false;
                    break;
                }
                poly.points.push_back(p);
            }

            // Если все точки прочитаны и нет лишних символов — добавляем фигуру
            if (valid && poly.points.size() == static_cast<size_t>(n))
            {
                char leftover;
                if (!(iss >> leftover))
                {
                    polygons.push_back(poly);
                }
            }
        }

        return polygons;
    }
}
