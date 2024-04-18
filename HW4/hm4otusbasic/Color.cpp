#include "Color.hpp"



// Color::Color(Color&& temp) {
//     this->r = std::move(temp.r);
//     this->g = std::move(temp.g);
//     this->b = std::move(temp.b);
// }

Color::Color(double red, double green, double blue)
    : r{red}, g{green}, b{blue} {}

double Color::red() const {
    return r;
}

double Color::green() const {
    return g;
}

double Color::blue() const {
    return b;
}

Color& Color::setRed(double red) {
    r = red;
    return *this;
}

Color& Color::setGreen(double green) {
    g = green;
    return *this;
}

Color& Color::setBlue(double blue) {
    b = blue;
    return *this;
}


std::ifstream& operator>> (std::ifstream& input, Color& color)
{
    double a,b,c;
    input >> a >> b >> c;
    color.setRed(a).setGreen(b).setBlue(c);
    return input;
}