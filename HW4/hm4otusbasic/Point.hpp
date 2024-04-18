#pragma once
#include <cmath>
#include <fstream>

class Point {
    public:
    Point() = default;
    Point(double x, double y) : x{x}, y{y} {};
    double x{};
    double y{};
};


inline Point operator-(const Point& lhs, const Point& rhs) {
    return {lhs.x - rhs.x, lhs.y - rhs.y};
}

inline Point operator+(const Point& lhs, const Point& rhs) {
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}

inline Point operator*(const Point& p, double scalar) {
    return {p.x * scalar, p.y * scalar};
}

inline Point operator/(const Point& p, double scalar) {
    return {p.x / scalar, p.y / scalar};
}

inline double distance2(const Point& lhs, const Point& rhs) {
    const Point delta = lhs - rhs;
    return delta.x * delta.x + delta.y * delta.y;
}

inline std::ifstream& operator>>(std::ifstream& input, Point& p) {
    double a,b;
    input >> a >> b;
    p.x = a;
    p.y = b;
    return input;
}
