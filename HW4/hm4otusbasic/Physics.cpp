#include "Physics.hpp"
#include <cmath>


double dot(const Point& lhs, const Point& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

Physics::Physics(double timePerTick) : timePerTick{timePerTick} {}

void Physics::setWorldBox(const Point& topL, const Point& bottomR) {
    this->topLeft = topL;
    this->bottomRight = bottomR;
}

void Physics::update(std::vector<Ball>& balls, std::forward_list<Dust>& dust, const size_t ticks) const {

    for (size_t i = 0; i < ticks; ++i) {
        move(balls, dust);
        collideWithBox(balls, dust);
        collideBalls(balls, dust);
    }
}

void Physics::collideBalls(std::vector<Ball>& balls, std::forward_list<Dust>& dust) const {
    for (auto a = balls.begin(); a != balls.end(); ++a) {
        if(!a->iscolidable()){
            continue;
        }
        for (auto b = std::next(a); b != balls.end(); ++b) {
            if(!b->iscolidable()){
                continue;
            }
            const double distanceBetweenCenters2 =
                distance2(a->getCenter(), b->getCenter());
            const double collisionDistance = a->getRadius() + b->getRadius();
            const double collisionDistance2 =
                collisionDistance * collisionDistance;

            if (distanceBetweenCenters2 < collisionDistance2) {
                processCollision(*a, *b, distanceBetweenCenters2);
                srand(time(NULL));
                Velocity vel;
                vel.setVector(a->getVelocity().vector());
                double mass = M_PI * pow(DUST_MASS, 3) * 4. / 3.;
                Point center{a->getCenter()};
                createDust(std::move(vel), std::move(center), mass, dust);
            }
        }
    }
}

void Physics::collideWithBox(std::vector<Ball>& balls, std::forward_list<Dust>& dust) const {
    for (Ball& ball : balls) {
         if(!ball.iscolidable()){
            continue;
        }
        const Point p = ball.getCenter();
        const double r = ball.getRadius();
        // определяет, находится ли v в диапазоне (lo, hi) (не включая границы)
        auto isOutOfRange = [](double v, double lo, double hi) {
            return v < lo || v > hi;
        };

        if (isOutOfRange(p.x, topLeft.x + r, bottomRight.x - r)) {
            Point vector = ball.getVelocity().vector();
            vector.x = -vector.x;
            ball.setVelocity(vector);
            Velocity vel;
            vel.setVector(ball.getVelocity().vector());
            double mass = M_PI * pow(DUST_MASS, 3) * 4. / 3.;
            Point center{ball.getCenter()};
            createDust(std::move(vel), std::move(center), mass, dust);

        } else if (isOutOfRange(p.y, topLeft.y + r, bottomRight.y - r)) {
            Point vector = ball.getVelocity().vector();
            vector.y = -vector.y;
            ball.setVelocity(vector);
            Velocity vel;
            vel.setVector(ball.getVelocity().vector());
            double mass = M_PI * pow(DUST_MASS, 3) * 4. / 3.;
            Point center{ball.getCenter()};
            createDust(std::move(vel), std::move(center), mass, dust);
        }
    }
}

void Physics::move(std::vector<Ball>& balls, std::forward_list<Dust>& dust) const {
    for (Ball& ball : balls) {
        Point newPos =
            ball.getCenter() + ball.getVelocity().vector() * timePerTick;
        ball.setCenter(newPos);
    }
    for(Dust& d: dust) {
        Point newPos = d.getCenter() + d.getVelocity().vector() * timePerTick;
        d.setCenter(newPos);
    }
}

void Physics::processCollision(Ball& a, Ball& b,
                               double distanceBetweenCenters2) const {
    // нормированный вектор столкновения
    const Point normal =
        (b.getCenter() - a.getCenter()) / std::sqrt(distanceBetweenCenters2);

    // получаем скорость в векторном виде
    const Point aV = a.getVelocity().vector();
    const Point bV = b.getVelocity().vector();

    // коэффициент p учитывает скорость обоих мячей
    const double p =
        2 * (dot(aV, normal) - dot(bV, normal)) / (a.getMass() + b.getMass());

    // задаем новые скорости мячей после столкновения
    a.setVelocity(Velocity(aV - normal * p * a.getMass()));
    b.setVelocity(Velocity(bV + normal * p * b.getMass()));
}


void Physics::createDust(Velocity&& vel, Point&& center,  double mass, std::forward_list<Dust>& dust_arr) const
{   
    srand(time(NULL));
     for(size_t i{0}; i < 3; i++){
        vel.setVector(vel.vector() * ((rand() % 3) + 1 ));
        // vel.setVector(a->getVelocity().vector() * (a->getMass() / mass) * (rand() % 10));
        Dust temp(vel, center, Color(255,0,0), 10, mass);
        dust_arr.push_front(temp);
    }
     for(size_t i{0}; i < 3; i++){
        vel.setVector(vel.vector() * ((rand() % 3) + 1 ));
        // vel.setVector(a->getVelocity().vector() * (a->getMass() / mass) * (rand() % 10));
        Dust temp(vel, center, Color(0,0,255), 10, mass);
        dust_arr.push_front(temp);
    }
}
