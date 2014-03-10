#include "color.h"

Color::Color() {}
Color::Color(float r, float g, float b): r(r), g(g), b(b) {}

Color operator+(const Color &a, const Color &b) {
    return Color(a.r + b.r, a.g + b.g, a.b + b.b);
}

Color Color::operator+=(const Color&a) {
    this->r += a.r;
    this->b += a.b;
    this->g += a.g;
    return *this;
}

Color operator*(const Color &a, const Color &b) {
    return Color(a.r * b.r, a.g * b.g, a.b * b.b);
}

Color operator*(const Color &a, float n) {
    return Color(a.r * n, a.g * n, a.b * n);
}

Color Color::operator*=(const Color&a) {
    this->r *= a.r;
    this->b *= a.b;
    this->g *= a.g;
    return *this;
}

Color Color::operator/=(const Color&a) {
    this->r /= a.r;
    this->b /= a.b;
    this->g /= a.g;
    return *this;
}
Color Color::operator/=(int n) {
    this->r /= n;
    this->b /= n;
    this->g /= n;
    return *this;
}

Color operator*(float n, const Color &a) {
    return a*n;
}

Color operator/(const Color &a, float n) {
    return Color(a.r/n, a.g/n, a.b/n);
}

ostream& operator<<(ostream& o, const Color &c) {
    return o << "Color(" << c.r << ", " << c.g << ", " << c.b << ")";
}

Color max(Color color, float n) {
    if (color.r < 0) color.r = 0;
    if (color.g < 0) color.g = 0;
    if (color.b < 0) color.b = 0;
    return color;
}
