#include <ctime>
#include "point.h"

namespace mars
{
    Point::Point(int32_t x, int32_t y) : m_x(x), m_y(y)
    {

    }

    Point::Point(const Point &other) : m_x(other.m_x), m_y(other.m_y)
    {

    }

    Point & Point::operator=(const Point &other)
    {
        if (this == &other)
        {
            return *this;
        }
        m_x = other.m_x;
        m_y = other.m_y;
        return *this;
    }

    Point operator+(const Point &a, const Point &b)
    {
        Point res(a.m_x + b.m_x, a.m_y + b.m_y);
        return res;
    }

    Point operator-(const Point &a, const Point &b)
    {
        Point res(a.m_x - b.m_x, a.m_y - b.m_y);
        return res;
    }

    bool operator==(const Point &a, const Point &b)
    {
        return (a.m_x == b.m_x && a.m_y == b.m_y);
    }

    bool operator!=(const Point &a, const Point &b)
    {
        return (a.m_x != b.m_x || a.m_y != b.m_y);
    }

    bool operator<(const Point &a, const Point &b)
    {
        return ((a.m_x < b.m_x) || (a.m_x == b.m_x && a.m_y < b.m_y));
    }

    std::ostream & operator<<(std::ostream &out, const Point &p)
    {
        out << "(" << p.m_x << ", " << p.m_y << ")";
        return out;
    }

    int32_t Point::manhattanDistance(const Point &a, const Point &b)
    {
        return abs(a.m_x - b.m_x) + abs(a.m_y - b.m_y);
    }

    Point Point::randomPoint(int32_t upBorderX, int32_t upBorderY)
    {
        srand(time(nullptr));
        int32_t x = rand() % (upBorderX);
        int32_t y = rand() % (upBorderY);
        Point p(x, y);
        return p;
    }
}
