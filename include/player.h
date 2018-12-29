//
// Created by silvair on 24.12.18.
//

#ifndef CZOLGI_PLAYER_H
#define CZOLGI_PLAYER_H

#include <vector_3d.h>
#include <list>
#include "bullet.h"
#include "wall.h"
#include "model_handler.h"
#include "health_bar.h"

class Player : public Collidable {
public:
    explicit Player(const Vector3D &coordinates);

    virtual ~Player();

    void run(float delta);

    void render();

    void rotateLeft(float delta);

    void rotateRight(float delta);

    void moveForward(float delta, const std::list<Collidable *> &collidableList);

    void moveBackward(float delta, const std::list<Collidable *> &collidableList);

    Bullet shoot();

    void rotateUpperPart(const Vector3D &direction) { this->upperPartDirection = direction / direction.length(); }

    const Vector3D &getPosition() const override { return this->position; }

    int getSize() const override { return this->SIZE; }

    void getHit(int hp);

    bool isAlive();

private:
    const int SIZE = 10;
    const int SPEED = 40;
    const int ROTATION_SPEED = 180;

    int hp = 100;
    Vector3D position;
    Vector3D lowerPartDirection{1, 0, 0};
    Vector3D upperPartDirection{1, 0, 0};
    ModelHandler modelHandler{const_cast<char *>("../assets/tank.obj")};
    HealthBar healthBar{this->hp};

    bool isColliding(const std::list<Collidable *> &collidableList);
};


#endif //CZOLGI_PLAYER_H
