//
// Created by silvair on 25.12.18.
//

#include <enemies/basic_enemy_tank.h>
#include <GL/gl.h>
#include <GL/freeglut.h>

BasicEnemyTank::BasicEnemyTank(const Vector3D &position) : EnemyLike(), position(position) {
}

void BasicEnemyTank::run(float delta, const std::list<Collidable *> &collidableList) {
    Vector3D preTranslationPosition = this->position;
    this->position += this->lowerPartDirection * this->SPEED * delta;

    if (this->isColliding(collidableList))
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

bool BasicEnemyTank::isColliding(const std::list<Collidable *> &collidableList) {
    for (const auto collidable : collidableList) {
        if (collidable == this)
            continue;

        const Vector3D &differenceVector = collidable->getPosition() - this->position;
        const auto minimalPossibleDistance = this->SIZE / 2.0f + collidable->getSize() / 2.0f;

        if (differenceVector.length() <= minimalPossibleDistance)
            return true;
    }

    return false;
}
