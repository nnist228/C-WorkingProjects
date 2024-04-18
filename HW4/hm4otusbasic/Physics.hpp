#pragma once
#define _USE_MATH_DEFINES
#define DUST_MASS 10
#include "Ball.hpp"
#include "Dust.hpp"
#include <vector>
#include <forward_list>

class Physics {
  public:
    Physics(double timePerTick = 0.001);
    void setWorldBox(const Point& topLeft, const Point& bottomRight);
    void update(std::vector<Ball>& balls, std::forward_list<Dust>& dust, size_t ticks) const;

  private:
    void collideBalls(std::vector<Ball>& balls, std::forward_list<Dust>& dust) const;
    void collideWithBox(std::vector<Ball>& balls, std::forward_list<Dust>& dust) const;
    void move(std::vector<Ball>& balls, std::forward_list<Dust>& dust) const;
    void processCollision(Ball& a, Ball& b,
                          double distanceBetweenCenters2) const;
    void createDust(Velocity&&, Point&&, double, std::forward_list<Dust>&) const;

  private:
    Point topLeft;
    Point bottomRight;
    double timePerTick;
};
