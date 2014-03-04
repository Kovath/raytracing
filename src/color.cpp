#include "color.h"

Color operator+(const Color &a, const Color &b) {
    return Color(a.r + b.r, a.g + b.g, a.b + b.b);
}

Color operator/(const Color &a, float n) {
    return Color(a.r/n, a.g/n, a.b/n);
}
