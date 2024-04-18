#pragma once 
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"
#include <chrono>


class Dust {
public:
    inline Dust(const Velocity& vel, const Point& cent, const Color& col, double rad, double m):velocity(vel), center(cent), color(col), radius(rad), mass(m), time(std::chrono::system_clock::now()){};
    inline Velocity getVelocity() const{
        return velocity;
    }
    void draw(Painter& painter) const{
        painter.draw(center, radius, color);
    }
    inline Point getCenter() const{
        return center;
    }
    inline double getRadius() const{
        return radius;
    }
    inline double getMass() const{
        return mass;
    }
    inline std::chrono::system_clock::time_point getTime() const{
        return time;
    } 
    inline double getRestTime() const{
        return restTime;
    }
    inline void setRestTime(double t){
        restTime = t;
    }
    inline void setCenter(const Point& cen){
        center = cen;
    }
private: 
    Velocity velocity;
    Point center;
    Color color;
    const double radius;
    const double mass;
    const std::chrono::system_clock::time_point time;
    double restTime = 3.;
};
