#ifndef COLLRECT_H
#define COLLRECT_H

struct CollRect {
    //ATRIBUTOS A USAR:
    float x, y;       // posición
    float width, height; // dimensiones

    //CONTRSTRUCTORES:
    CollRect(float x = 0, float y = 0, float w = 0, float h = 0)
        : x(x), y(y), width(w), height(h) {}

    //SET Y GET:

    //METODOS:
    bool intersects(const CollRect& other) const {
        return !(x + width < other.x || other.x + other.width < x ||
            y + height < other.y || other.y + other.height < y);
    }

    bool contains(float px, float py) const {
        return px >= x && px <= x + width &&
            py >= y && py <= y + height;
    }

    // Solapamiento estricto: tocar el borde NO cuenta como choque.
    bool overlaps(const CollRect& o) const {
        return x < o.x + o.width && x + width  > o.x &&
            y < o.y + o.height && y + height > o.y;
    }
};

#endif // COLLRECT_H