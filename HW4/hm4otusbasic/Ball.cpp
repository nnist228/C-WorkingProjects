#include "Ball.hpp"
#include <cmath>

/**
 * Задает скорость объекта
 * @param velocity новое значение скорости
 */
Ball::Ball(const Velocity& vel, const Point& p, const Color& col, double rad, double m, bool Colidable): velocity(vel), center(p), color(col), radius (rad), mass(m), isColidable(Colidable){};


void Ball::setVelocity(const Velocity& vel) {
    this->velocity = vel;
}

/**
 * @return скорость объекта
 */
Velocity Ball::getVelocity() const {
    // TODO: место для доработки
    return velocity;
}

/**
 * @brief Выполняет отрисовку объекта
 * @details объект Ball абстрагирован от конкретного
 * способа отображения пикселей на экране. Он "знаком"
 * лишь с интерфейсом, который предоставляет Painter
 * Рисование выполняется путем вызова painter.draw(...)
 * @param painter контекст отрисовки
 */
void Ball::draw(Painter& painter) const {
    painter.draw(center, radius, color);
}

/**
 * Задает координаты центра объекта
 * @param center новый центр объекта
 */
void Ball::setCenter(const Point& cent) {
    this->center = cent;
}

/**
 * @return центр объекта
 */
Point Ball::getCenter() const {
    // TODO: место для доработки
    return center;
}

/**
 * @brief Возвращает радиус объекта
 * @details обратите внимание, что метод setRadius()
 * не требуется
 */
double Ball::getRadius() const {
    // TODO: место для доработки
    return radius;
}

/**
 * @brief Возвращает массу объекта
 * @details В нашем приложении считаем, что все шары
 * состоят из одинакового материала с фиксированной
 * плотностью. В этом случае масса в условных единицах
 * эквивалентна объему: PI * radius^3 * 4. / 3.
 */
double Ball::getMass() const {
    // TODO: место для доработки
    return mass;
}

Color Ball::getColor() const{
    return color;
}

 bool Ball::iscolidable() const {
    return isColidable;
}

// std::ifstream& operator>>(std::ifstream& input, Ball& ball) {
//     Point cords, vec;
//     Color color;
//     double radius, mass;
//     input >> cords >> vec >> color >> radius >> mass;

// }
