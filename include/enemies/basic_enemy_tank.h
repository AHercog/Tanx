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

    void run(float delta, const std::list<Wall> &wallList) override;

    void render() const override;

private:
    const int SIZE = 6;
    const int SPEED = 25;

    Vector3D position;
    Vector3D lowerPartDirection{1, 0, 0};
    Vector3D upperPartDirection{1, 0, 0};

    bool isColliding(const std::list<Wall> &wallList);
};

#endif //CZOLGI_BASIC_ENEMY_TANK_H
