#ifndef NIVEL_H
#define NIVEL_H

class Nivel {
public:
    virtual ~Nivel() = default;

    virtual bool init() = 0;
    virtual void update(float dt) = 0;
    virtual void draw() = 0;
    virtual void unload() = 0;

    virtual bool isFinished() const = 0;
    virtual int nextLevel() const = 0;
};

#endif // NIVEL_H