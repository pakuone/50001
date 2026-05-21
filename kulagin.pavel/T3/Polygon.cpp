#include "Polygon.h"
#include <cmath>

bool Point::operator==(const Point& other) const {
    return (other.x_ == x_) && (other.y_ == y_);
}

double area(const Polygon& polygon) {
    if (polygon.points_.size() < 3) {
        return 0.0;
    }

    double area = 0.0;

    for (int i = 0; i < polygon.points_.size(); i++) {
        const Point& p1 = polygon.points_[i];
        const Point& p2 = polygon.points_[(i + 1) % polygon.points_.size()];

        area += (p1.x_ * p2.y_) - (p1.y_ * p2.x_);
    }

    return std::abs(area) / 2.0;
}
