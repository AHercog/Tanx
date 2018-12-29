//
// Created by silvair on 25.12.18.
//

#include <enemies/basic_enemy_tank.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <random>
#include <effolkronium/random.hpp>
#include <iostream>

using Random = effolkronium::random_static;

BasicEnemyTank::BasicEnemyTank(const Vector3D &position) : EnemyLike(), position(position) {
}

void BasicEnemyTank::run(float delta, const std::list<Collidable *> &collidableList) {
    this->changeDirectionTimer += delta;

    if (this->changeDirectionTimer >= this->CHANGE_DIRECTION_TIMER_LIMIT) {
        this->changeDirectionTimer = 0;

        auto randomVector = Vector3D{Random::get(-1.0f, 1.0f), Random::get(-1.0f, 1.0f), 0};
        randomVector /= randomVector.length();

        this->lowerPartDirection = randomVector;
        this->upperPartDirection = randomVector;
    }

    if (this->shootTimer >= this->SHOOT_TIMER_LIMIT)
        this->shootTimer = 0;

    this->shootTimer += delta;

    Vector3D preTranslationPosition = this->position;
    this->position += this->lowerPartDirection * this->SPEED * delta;

    if (this->isColliding(collidableList))
        this->position = preTranslationPosition;

    this->healthBar.setHp(this->hp);
}

void BasicEnemyTank::render() const {
    glColor3f(0.956, 0.262, 0.211);
    glPushMatrix();
    glTranslatef(this->position.getX(), this->position.getY(), 0);
    glRotatef(this->lowerPartDirection.getAngleAlongZ(), 0, 0, 1);
    this->modelHandler.drawModel(1);
    glPopMatrix();

    glColor3f(0.376, 0.490, 0.545);
    glPushMatrix();
    glTranslatef(this->position.getX(), this->position.getY(), 0);
    glRotatef(this->upperPartDirection.getAngleAlongZ(), 0, 0, 1);
    this->modelHandler.drawModel(0);
    glPopMatrix();

    this->healthBar.render(this->position.getX(), this->position.getY());
}

bool BasicEnemyTank::isColliding(const std::list<Collidable *> &collidableList) {
    for (const auto collidable : collidableList) {
        if (collidable == this)
            continue;

        const Vector3D &differenceVector = collidable->getPosition() - this->position;
        const auto minimalPossibleDistance = this->SIZE / 2.0f + collidable->getSize() / 2.0f;

        if (differenceVector.length() <= minimalPossibleDistance) {
            auto randomVector = Vector3D{Random::get(-1.0f, 1.0f), Random::get(-1.0f, 1.0f), 0};
            randomVector /= randomVector.length();

            this->lowerPartDirection = randomVector;
            this->upperPartDirection = randomVector;
            return true;
        }
    }

    return false;
}

bool BasicEnemyTank::detectPlayer(const std::list<Wall *> &wallList, const Player *const player) {
    auto differenceVector = player->getPosition() - this->position;
    differenceVector /= differenceVector.length();
    this->upperPartDirection = differenceVector;

    const auto isShootLimitExtended = this->shootTimer >= this->SHOOT_TIMER_LIMIT;
    return isShootLimitExtended;
}

Bullet BasicEnemyTank::shoot() {
    return Bullet(this->position + this->upperPartDirection * 10, this->upperPartDirection, false);
}
