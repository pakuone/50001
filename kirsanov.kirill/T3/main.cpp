#include "polygon.h"
#include "reader.h"
#include "commands.h"
#include "iofmtguard.h"
#include "constants.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <cstddef>

using namespace kirsanov;

// Обработка AREA <EVEN|ODD|MEAN|num>
void processAreaCommand(const std::vector<Polygon>& polygons, std::istream& in)
{
    std::string param;
    in >> param;
    try
    {
        iofmtguard guard(std::cout);               // сохраняем формат
        std::cout << std::fixed << std::setprecision(1);  // один знак после запятой

        if (param == PARAM_EVEN)
        {
            std::cout << totalArea(polygons, [](const Polygon& p) {
                return p.vertexCount() % 2 == 0;
                }) << "\n";
        }
        else if (param == PARAM_ODD)
        {
            std::cout << totalArea(polygons, [](const Polygon& p) {
                return p.vertexCount() % 2 != 0;
                }) << "\n";
        }
        else if (param == PARAM_MEAN)
        {
            std::cout << meanArea(polygons) << "\n";
        }
        else
        {
            int n = std::stoi(param);
            if (n < 3)
            {
                std::cout << INVALID_COMMAND << "\n";
            }
            else
            {
                std::cout << totalArea(polygons, [n](const Polygon& p) {
                    return p.vertexCount() == static_cast<size_t>(n);
                    }) << "\n";
            }
        }
    }
    catch (...)
    {
        std::cout << INVALID_COMMAND << "\n";
    }
}

// Обработка MAX <AREA|VERTEXES>
void processMaxCommand(const std::vector<Polygon>& polygons, std::istream& in)
{
    std::string param;
    in >> param;
    try
    {
        if (param == PARAM_AREA)
        {
            iofmtguard guard(std::cout);
            std::cout << std::fixed << std::setprecision(1) << maxArea(polygons) << "\n";
        }
        else if (param == PARAM_VERTEXES)
        {
            std::cout << maxVertexes(polygons) << "\n";
        }
        else
        {
            std::cout << INVALID_COMMAND << "\n";
        }
    }
    catch (...)
    {
        std::cout << INVALID_COMMAND << "\n";
    }
}

// Обработка MIN <AREA|VERTEXES>
void processMinCommand(const std::vector<Polygon>& polygons, std::istream& in)
{
    std::string param;
    in >> param;
    try
    {
        if (param == PARAM_AREA)
        {
            iofmtguard guard(std::cout);
            std::cout << std::fixed << std::setprecision(1) << minArea(polygons) << "\n";
        }
        else if (param == PARAM_VERTEXES)
        {
            std::cout << minVertexes(polygons) << "\n";
        }
        else
        {
            std::cout << INVALID_COMMAND << "\n";
        }
    }
    catch (...)
    {
        std::cout << INVALID_COMMAND << "\n";
    }
}

// Обработка COUNT <EVEN|ODD|num>
void processCountCommand(const std::vector<Polygon>& polygons, std::istream& in)
{
    std::string param;
    in >> param;
    try
    {
        if (param == PARAM_EVEN)
        {
            std::cout << countPolygons(polygons, [](const Polygon& p) {
                return p.vertexCount() % 2 == 0;
                }) << "\n";
        }
        else if (param == PARAM_ODD)
        {
            std::cout << countPolygons(polygons, [](const Polygon& p) {
                return p.vertexCount() % 2 != 0;
                }) << "\n";
        }
        else
        {
            int n = std::stoi(param);
            if (n < 3)
            {
                std::cout << INVALID_COMMAND << "\n";
            }
            else
            {
                std::cout << countPolygons(polygons, [n](const Polygon& p) {
                    return p.vertexCount() == static_cast<size_t>(n);
                    }) << "\n";
            }
        }
    }
    catch (...)
    {
        std::cout << INVALID_COMMAND << "\n";
    }
}

// Обработка PERMS <Polygon>
void processPermsCommand(const std::vector<Polygon>& polygons, std::istream& in)
{
    int n;
    if (!(in >> n))
    {
        std::cout << INVALID_COMMAND << "\n";
        return;
    }

    if (n < 3)
    {
        // Очищаем всю оставшуюся строку, чтобы не засорять следующий ввод
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << INVALID_COMMAND << "\n";
        return;
    }

    Polygon target;
    for (int i = 0; i < n; ++i)
    {
        char c1, c2, c3;
        int x, y;
        if (!(in >> c1 >> x >> c2 >> y >> c3) || c1 != '(' || c2 != ';' || c3 != ')')
        {
            std::cout << INVALID_COMMAND << "\n";
            return;
        }
        target.points.push_back({ x, y });
    }

    if (target.points.size() != static_cast<size_t>(n))
    {
        std::cout << INVALID_COMMAND << "\n";
        return;
    }

    std::cout << countPerms(polygons, target) << "\n";
}

// Обработка RIGHTSHAPES
void processRightShapesCommand(const std::vector<Polygon>& polygons)
{
    std::cout << countRightShapes(polygons) << "\n";
}

int main(int argc, char* argv[])
{
    // Проверка аргументов командной строки
    if (argc != 2)
    {
        std::cerr << USAGE << argv[0] << " filename\n";
        return 1;
    }

    // Чтение фигур из файла
    std::vector<Polygon> polygons;
    try
    {
        polygons = readPolygons(argv[1]);
    }
    catch (const std::exception& e)
    {
        std::cerr << ERROR_PREFIX << e.what() << "\n";
        return 1;
    }

    // Основной цикл обработки команд
    std::string cmd;
    while (std::cin >> cmd)  // завершается по EOF (Ctrl+Z)
    {
        if (cmd == CMD_AREA)
        {
            processAreaCommand(polygons, std::cin);
        }
        else if (cmd == CMD_MAX)
        {
            processMaxCommand(polygons, std::cin);
        }
        else if (cmd == CMD_MIN)
        {
            processMinCommand(polygons, std::cin);
        }
        else if (cmd == CMD_COUNT)
        {
            processCountCommand(polygons, std::cin);
        }
        else if (cmd == CMD_PERMS)
        {
            processPermsCommand(polygons, std::cin);
        }
        else if (cmd == CMD_RIGHTSHAPES)
        {
            processRightShapesCommand(polygons);
        }
        else
        {
            std::cout << INVALID_COMMAND << "\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    return 0;
}
