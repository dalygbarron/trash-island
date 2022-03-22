#include "src/Util.hh"
#include <cmath>

Util::Vec::Vec(int32_t x) {
    this->x = x;
    this->y = x;
}

Util::Vec::Vec(int32_t x, int32_t y) {
    this->x = x;
    this->y = y;
}

Util::Vec Util::Vec::operator+(Vec const &other) const {
    return Util::Vec(x + other.x, y + other.y);
}

Util::Vec Util::Vec::operator-(Vec const &other) const {
    return Util::Vec(x - other.x, y - other.y);
}

Util::Vec Util::Vec::operator*(Vec const &other) const {
    return Util::Vec(x * other.x, y * other.y);
}

Util::Vec Util::Vec::operator*(int other) const {
    return Util::Vec(x * other, y * other);
}

Util::Vec Util::Vec::operator/(Vec const &other) const {
    return Util::Vec(
        (x >= 0) ? x / other.x : (x - other.x + 1) / other.x,
        (y >= 0) ? y / other.y : (y - other.y + 1) / other.y
    );
}

Util::Vec Util::Vec::operator/(int other) const {
    return Util::Vec(
        (x >= 0) ? x / other : (x - other + 1) / other,
        (y >= 0) ? y / other : (y - other + 1) / other
    );
}

Util::Vec &Util::Vec::operator+=(Vec const &other) {
    x += other.x;
    y += other.y;
    return *this;
}

bool Util::Vec::operator==(Vec const &other) const {
    return x == other.x && y == other.y;
}

Util::Vec Util::Vec::sign() const {
    return Util::Vec(Util::sign(x), Util::sign(y));
}

Util::Vec Util::Vec::abs() const {
    return Util::Vec(std::abs(x), std::abs(y));
}

int32_t Util::Vec::min() const {
    return std::min(x, y);
}

int32_t Util::Vec::max() const {
    return std::max(x, y);
}

Vector2 Util::Vec::toVector2() const {
    return (Vector2){(float)x, (float)y};
}

Util::Rect::Rect(int32_t x, int32_t y, int32_t width, int32_t height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

Util::Rect Util::Rect::operator*(Vec const &vec) const {
    return Util::Rect(x * vec.x, y * vec.y, width * vec.x, height * vec.y);
};

Rectangle Util::Rect::toRectangle() const {
    return (Rectangle){(float)x, (float)y, (float)width, (float)height};
}

std::ostream &Util::operator<<(std::ostream &output, Util::Vec const &v) {
    output << "(" << v.x << "," << v.y << ")";
    return output;
}

std::ostream &Util::operator<<(std::ostream &output, Util::Rect const &r) {
    output << "(" << r.x << "," << r.y << "," << r.width <<
        "," << r.height << ")";
    return output;
}

int Util::sign(int x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

Rectangle Util::fit(int width, int height, Rectangle bounds) {
    float hRatio = (float)width / bounds.width;
    float vRatio = (float)height / bounds.height;
    float increase = 1.0f / fmax(hRatio, vRatio);
    Rectangle rect;
    rect.x = bounds.x;
    rect.y = bounds.y;
    rect.width = width * increase;
    rect.height = height * increase;
    rect.x += bounds.width * 0.5 - bounds.width * hRatio * increase * 0.5;
    rect.y += bounds.height * 0.5 - bounds.height * vRatio * increase * 0.5;
    return rect;
}
