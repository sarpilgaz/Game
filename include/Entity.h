#ifndef ENTITY_H
#define ENTITY_H

class Entity {
protected:
    int x, y;
    int vx, vy;

public:
    Entity() : x(0), y(0), vx(0), vy(0) {}

    int getX() const { return x; }
    int getY() const { return y; }
    int getVx() const { return vx; }
    int getVy() const { return vy; }

    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }
    void setVx(int newVx) { vx = newVx; }
    void setVy(int newVy) { vy = newVy; }
};

#endif // ENTITY_H