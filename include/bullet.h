//
// Created by silvair on 25.12.18.
//

#ifndef CZOLGI_BULLET_H
#define CZOLGI_BULLET_H

#include <list>
#include "vector_3d.h"
#include "wall.h"

class Bullet {
public:
    explicit Bullet(const Vector3D &position, const Vector3D &direction);

    void run(float delta);

    void render() const;

    bool shouldBeDestroyed(const std::list<Wall *> &wallList) const;

private:
    const int SPEED = 150;

    Vector3D direction;
    Vector3D position;
};


#endif //CZOLGI_BULLET_H
