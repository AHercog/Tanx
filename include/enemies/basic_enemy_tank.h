//
// Created by silvair on 25.12.18.
//

#ifndef CZOLGI_BASIC_ENEMY_TANK_H
#define CZOLGI_BASIC_ENEMY_TANK_H

#include <vector_3d.h>
#include <wall.h>
#include <list>
#include "enemy_like.h"

class BasicEnemyTank : public EnemyLike {
public:
    explicit BasicEnemyTank(const Vector3D &position);

    void run(float delta, const std::list<Collidable *> &collidableList) override;

    void render() const override;

    void getHit(int damage) override { this->hp -= damage; }

    bool shouldBeDestroyed() override {return this->hp <= 0;}

    bool detectPlayer(const std::list<Wall *> &wallList, const Player *player) override;

    Bullet shoot() override;

    const Vector3D &getPosition() const override { return this->position; }

    int getSize() const override { return this->SIZE; }

private:
    const int SIZE = 6;
    const int SPEED = 25;
    const float SHOOT_TIMER_LIMIT = 1;
    const float CHANGE_DIRECTION_TIMER_LIMIT = 3;

    float shootTimer = 0;
    float changeDirectionTimer = 0;
    int hp = 50;
    Vector3D position;
    Vector3D lowerPartDirection{1, 0, 0};
    Vector3D upperPartDirection{1, 0, 0};
    ModelHandler modelHandler{const_cast<char *>("../assets/tank.obj")};
    HealthBar healthBar{this->hp};

    bool isColliding(const std::list<Collidable *> &collidableList);
};

#endif //CZOLGI_BASIC_ENEMY_TANK_H
