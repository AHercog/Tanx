//
// Created by silvair on 25.12.18.
//

#include <enemies/basic_enemy_tank.h>
#include <GL/gl.h>
#include <GL/freeglut.h>

#include "enemies/basic_enemy_tank.h"

BasicEnemyTank::BasicEnemyTank(const Vector3D &position) : EnemyLike(), position(position) {
}

void BasicEnemyTank::run(float delta, const std::list<Wall> &wallList) {
    Vector3D preTranslationPosition = this->position;
    this->position += this->lowerPartDirection * this->SPEED * delta;

    if (this->isColliding(wallList))
        this->position = preTranslationPosition;
}

void BasicEnemyTank::render() const {
    glColor3f(1, 0, 0);

    glPushMatrix();
    glTranslatef(this->position.getX(), this->position.getY(), this->position.getZ() + this->SIZE / 2.0f);
    glRotatef(this->lowerPartDirection.getAngleAlongZ(), 0, 0, 1);
    glutSolidCube(this->SIZE);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(this->position.getX(), this->position.getY(), this->position.getZ() + this->SIZE / 4.0f);
    glRotatef(this->upperPartDirection.getAngleAlongZ(), 0, 0, 1);
    glTranslatef(10, 0, 0);
    glutSolidCube(this->SIZE / 2.0f);
    glPopMatrix();
}

bool BasicEnemyTank::isColliding(const std::list<Wall> &wallList) {
    for (const Wall &wall : wallList) {
        const Vector3D &differenceVector = wall.getPosition() - this->position;
        const auto minimalPossibleDistance = this->SIZE / 2.0f + wall.getSize() / 2.0f;

        if (differenceVector.length() <= minimalPossibleDistance)
            return true;
    }

    return false;
}
