#include "color.h"

char Color::toRGB(bool big_endian) {
	char r = ((int)this->r) & 0xff;
	char g = ((int)this->g) & 0xff;
	char b = ((int)this->b) & 0xff;

	if(big_endian) {
		r = r << 16; g = g << 8; b = b << 0;
	} else {
		b = b << 16; g = g << 8; r = r << 0;
	}

	return r + g + b;
}

Color operator+(const Color &a, const Color &b) {
    return Color(a.r + b.r, a.g + b.g, a.b + b.b);
}

Color operator*(const Color &a, const Color &b) {
    return Color(a.r * b.r, a.g * b.g, a.b * b.b);
}

Color operator*(const Color &a, float n) {
    return Color(a.r * n, a.g * n, a.b * n);
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
