#ifndef COLLRECT_H
#define COLLRECT_H

struct CollRect {
    float x, y;       // posición
    float width, height; // dimensiones

    CollRect(float x = 0, float y = 0, float w = 0, float h = 0)
        : x(x), y(y), width(w), height(h) {}

    bool intersects(const CollRect& other) const {
        return !(x + width < other.x || other.x + other.width < x ||
            y + height < other.y || other.y + other.height < y);
    }
};

#endif // COLLRECT_H