#ifndef COLOR_H
#define COLOR_H

#include "include.h"

class Color {
    public:
        float r, g, b;

        // constructors
        Color() {}
        Color(float r, float g, float b): r(r), g(g), b(b) {}

		char toRGB(bool big_endian = true);

        friend Color operator+(const Color &a, const Color &b);
        friend Color operator/(const Color &a, float n);
        friend Color operator*(const Color &a, const Color &b);
        friend Color operator*(const Color &a, float n);
        friend Color operator*(float n, const Color &a);
        friend ostream& operator<<(ostream& o, const Color &c);

        Color max(Color a, float n);
};

#endif // COLOR_H
