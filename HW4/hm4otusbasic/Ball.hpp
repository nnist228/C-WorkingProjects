#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Ball {
public:
    // friend std::ifstream& operator>>(std::ifstream&, Ball&);
    Ball(const Velocity&, const Point&, const Color&, double , double, bool = false);
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    Color getColor() const;
    double getRadius() const;
    double getMass() const;
    bool iscolidable() const;
private: 
    Velocity velocity;
    Point center;
    Color color;
    const double radius;
    const double mass;
    bool isColidable;
};
