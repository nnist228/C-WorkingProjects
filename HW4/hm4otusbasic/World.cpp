#include "World.hpp"
#include "Painter.hpp"
#include <cmath>
#include <fstream>
#include <chrono>

// Длительность одного тика симуляции.
// Подробнее см. update()
// Изменять не следует
static constexpr double timePerTick = 0.001;

/**
 * Конструирует объект мира для симуляции
 * @param worldFilePath путь к файлу модели мира
 */
World::World(const std::string& worldFilePath) {

    std::ifstream stream(worldFilePath);
    /**
     * TODO: хорошее место для улучшения.
     * Чтение границ мира из модели
     * Обратите внимание, что здесь и далее мы многократно
     * читаем в объект типа Point, последовательно
     * заполняя координаты x и у. Если что-то делаем
     * многократно - хорошо бы вынести это в функцию
     * и не дублировать код...
     */
    stream >> topLeft >> bottomRight;
    physics.setWorldBox(topLeft, bottomRight);

    /**
     * TODO: хорошее место для улучшения.
     * (x, y) и (vx, vy) - составные части объекта, также
     * как и (red, green, blue). Опять же, можно упростить
     * этот код, научившись читать сразу Point, Color...
     */
    // double x;
    // double y;
    // double vx;
    // double vy;
    // double radius;

    // double red;
    // double green;
    // double blue;
    Point center, vel_vec;
    Velocity velocity;
    Color color;
    double mass, radius;
    bool isCollidable;

    // Здесь не хватает обработки ошибок, но на текущем
    // уровне прохождения курса нас это устраивает
    while (stream.peek(), stream.good()) {
        // Читаем координаты центра шара (x, y) и вектор
        // его скорости (vx, vy)
        

        stream >> center >> vel_vec >> color >> radius >> std::boolalpha >> isCollidable;
        mass = M_PI * pow(radius, 3) * 4. / 3.;
        velocity.setVector(vel_vec);
        Ball temp(velocity, center, color, radius, mass, isCollidable);

        balls.push_back(temp);

        // Читаем три составляющие цвета шара
        // stream >> red >> green >> blue;
        // Читаем радиус шара
        // stream >> radius;
        // Читаем свойство шара isCollidable, которое
        // указывает, требуется ли обрабатывать пересечение
        // шаров как столкновение. Если true - требуется.
        // В базовой части задания этот параметр
        // stream >> std::boolalpha >> isCollidable;

        // TODO: место для доработки.
        // Здесь не хватает самого главного - создания
        // объекта класса Ball со свойствами, прочитанными
        // выше, и его помещения в контейнер balls

        // После того как мы каким-то образом
        // сконструируем объект Ball ball;
        // добавьте его в конец контейнера вызовом
        // balls.push_back(ball);
    }
}

/// @brief Отображает состояние мира
void World::show(Painter& painter) const {
    // Рисуем белый прямоугольник, отображающий границу
    // мира
    painter.draw(topLeft, bottomRight, Color(1, 1, 1));
    
    // Вызываем отрисовку каждого шара
    for (const Ball& ball : balls) {
        ball.draw(painter);
    }
    // Вызываем отрисовку каждой частицы
   for (const Dust& d: dust){
        d.draw(painter);
   }
}

/// @brief Обновляет состояние мира
void World::update(double time, const std::chrono::system_clock::time_point& cur_time) {
    /**
     * В реальном мире время течет непрерывно. Однако
     * компьютеры дискретны по своей природе. Поэтому
     * симуляцию взаимодействия шаров выполняем дискретными
     * "тиками". Т.е. если с момента прошлой симуляции
     * прошло time секунд, time / timePerTick раз обновляем
     * состояние мира. Каждое такое обновление - тик -
     * в physics.update() перемещаем шары и обрабатываем
     * коллизии - ситуации, когда в результате перемещения
     * один шар пересекается с другим или с границей мира.
     * В общем случае время не делится нацело на
     * длительность тика, сохраняем остаток в restTime
     * и обрабатываем на следующей итерации.
     */

    // учитываем остаток времени, который мы не "доработали" при прошлом update

    //удаляем частицы пыли(dust), время которых истекло
     for(auto d = dust.begin(), prev = dust.before_begin(); d != dust.end(); d++){
        const double delta =
        std::chrono::duration_cast<std::chrono::duration<double>>(cur_time -
                                                                  d->getTime()).count();
        if(d->getRestTime() - delta <= 0){
            d = prev;
            dust.erase_after(d);
        } else{
            prev = d;
        }
    }
    time += restTime;
    const auto ticks = static_cast<size_t>(std::floor(time / timePerTick));
    restTime = time - double(ticks) * timePerTick;

    physics.update(balls, dust, ticks);
}