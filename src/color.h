#ifndef COLOR_H
#define COLOR_H

class Color {
    public:
        float r, g, b;

        // constructors
        Color() {}
        Color(float r, float g, float b): r(r), g(g), b(b) {}

        friend Color operator+(const Color &a, const Color &b);
        friend Color operator/(const Color &a, float n);
};

#endif // COLOR_H
