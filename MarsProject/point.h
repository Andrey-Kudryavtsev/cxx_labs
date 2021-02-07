#ifndef MARS_POINT_H
#define MARS_POINT_H

#include <iostream>
#include <cstdint>

namespace mars
{
    struct Point
    {
        int32_t m_x;
        int32_t m_y;

        Point(int32_t x = 0, int32_t y = 0);
        Point(const Point &);
        ~Point() = default;
        Point & operator=(const Point &);
        friend Point operator+(const Point &, const Point &);
        friend Point operator-(const Point &, const Point &);
        friend bool operator==(const Point &, const Point &);
        friend bool operator!=(const Point &, const Point &);
        friend bool operator<(const Point &, const Point &);
        friend std::ostream & operator<<(std::ostream &, const Point &);
        static int32_t manhattanDistance(const Point &, const Point &);
        static Point randomPoint(int32_t, int32_t);
    };
}

#endif //MARS_POINT_H
