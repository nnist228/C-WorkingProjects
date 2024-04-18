#pragma once
#include <fstream>



class Color {
  public:
    friend std::ifstream& operator>> (std::ifstream&, Color&);
    Color() = default;
    // Color(Color &&);
    Color(double red, double green, double blue);
    double red() const;
    double green() const;
    double blue() const;
    Color& setRed(double);
    Color& setGreen(double);
    Color& setBlue(double);
  private:
    double r{};
    double g{};
    double b{};
};
