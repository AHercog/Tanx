//
// Created by silvair on 24.12.18.
//

#ifndef CZOLGI_PLAYER_H
#define CZOLGI_PLAYER_H

#include <vector_3d.h>
#include <list>
#include "bullet.h"
#include "wall.h"

class Player {
public:
    explicit Player(const Vector3D &coordinates);

    void run(float delta);

    void render();

    void rotateLeft(float delta);

    void rotateRight(float delta);

    void moveForward(float delta, const std::list<Collidable *> &collidableList);

    void moveBackward(float delta, const std::list<Collidable *> &collidableList);

    Bullet shoot();

    void rotateUpperPart(const Vector3D &direction) { this->upperPartDirection = direction / direction.length(); }

    const Vector3D &getPosition() { return this->position; }

private:
    const int SIZE = 6;
    const int SPEED = 25;
    const int ROTATION_SPEED = 180;

    int hp = 100;
    Vector3D position;
    Vector3D lowerPartDirection{1, 0, 0};
    Vector3D upperPartDirection{1, 0, 0};

    bool isColliding(const std::list<Collidable *> &collidableList);
};


#endif //CZOLGI_PLAYER_H
