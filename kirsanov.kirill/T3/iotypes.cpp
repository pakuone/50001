#include "iotypes.h"

namespace kirsanov
{
    // Чтение точки: (x;y)
    std::istream& operator>>(std::istream& in, PointIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
            return in;

        char c1, c2, c3;
        int x, y;
        in >> c1 >> x >> c2 >> y >> c3;

        if (in.fail())
        {
            return in;
        }

        if (c1 != '(' || c2 != ';' || c3 != ')')
        {
            in.setstate(std::ios::failbit);
            return in;
        }

        dest.ref = { x, y };
        return in;
    }

    std::istream& operator>>(std::istream& in, PolygonIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
            return in;

        int n;
        in >> n;
        if (in.fail() || n < 3)
        {
            in.setstate(std::ios::failbit);
            return in;
        }

        Polygon poly;
        for (int i = 0; i < n; ++i)
        {
            Point p;
            in >> PointIO{ p };  // рекурсивно читаем точку
            if (in.fail())
            {
                in.setstate(std::ios::failbit);
                return in;
            }
            poly.points.push_back(p);
        }

        dest.ref = std::move(poly);
        return in;
    }
}
