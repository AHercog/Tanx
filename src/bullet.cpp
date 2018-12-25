//
// Created by silvair on 25.12.18.
//

#include <bullet.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <cmath>

#include "bullet.h"

Bullet::Bullet(const Vector3D &position, const Vector3D &direction) : position(position),
                                                                      direction(direction) {}

void Bullet::run(float delta) {
    this->position += this->direction * this->SPEED * delta;
}

void Bullet::render() const {
    const auto cubeSize = 1;
    glColor3f(1, 0, 0);

    glPushMatrix();
    glTranslatef(this->position.getX(), this->position.getY(), this->position.getZ() + cubeSize / 2.0f + 2);
    glRotatef(this->direction.getAngleAlongZ(), 0, 0, 1);
    glutSolidCube(cubeSize);
    glPopMatrix();
}

bool Bullet::shouldBeDestroyed(const std::list<Wall *> &wallList) const {
    if (std::fabs(this->position.getX()) > 100 or std::fabs(this->position.getY()) > 100)
        return true;

    for (const auto wall : wallList) {
        auto positionDifference = this->position - wall->getPosition();

        if (positionDifference.length() < wall->getSize() / 2.0f)
            return true;
    }

    return false;
}
