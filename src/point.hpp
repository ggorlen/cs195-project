#ifndef __POINT_HPP__
#define __POINT_HPP__

class Point {
public:
    int x;
    int y;

    Point(unsigned int x_coord, unsigned int y_coord) {
        x = x_coord;
        y = y_coord;
    }

    bool equal(Point p) {
        return x == p.x && y == p.y;
    }
};

#endif