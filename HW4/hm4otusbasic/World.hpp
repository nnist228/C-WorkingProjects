#pragma once
#define _USE_MATH_DEFINES
#include "Ball.hpp"
#include "Dust.hpp"
#include "Physics.hpp"
#include <string>
#include <vector>
#include <forward_list>

class Painter;



class World {
  public:
    World(const std::string& worldFilePath);
    void show(Painter& painter) const;
    void update(double time, const std::chrono::system_clock::time_point&);

  private:
    // Границы мира заданы углами прямоугольника
    Point topLeft;
    Point bottomRight;
    // Объект физического движка
    Physics physics;
    // Контейнер с шарами
    std::vector<Ball> balls;
    std::forward_list<Dust> dust;
    // Длина отрезка времени, который не был
    // учтен при прошлой симуляции. См. реализацию update
    double restTime = 0.;
};
