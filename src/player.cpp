//
// Created by silvair on 24.12.18.
//

#include <vector_3d.h>
#include <player.h>
#include <GL/freeglut.h>
#include <iostream>

Player::Player(const Vector3D &coordinates) : position(coordinates) {
}

Player::~Player() = default;

void Player::run(float delta) {
    this->healthBar.setHp(this->hp);
}

void Player::render() {
    glColor3f(0.011, 0.662, 0.956);
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

void Player::rotateLeft(float delta) {
    this->lowerPartDirection.rotateAlongZ(this->ROTATION_SPEED * delta);
}

void Player::rotateRight(float delta) {
    this->lowerPartDirection.rotateAlongZ(-this->ROTATION_SPEED * delta);
}

void Player::moveForward(float delta, const std::list<Collidable *> &collidableList) {
    Vector3D preTranslationPosition = this->position;
    this->position += this->lowerPartDirection * this->SPEED * delta;

    if (this->isColliding(collidableList))
        this->position = preTranslationPosition;
}

void Player::moveBackward(float delta, const std::list<Collidable *> &collidableList) {
    Vector3D preTranslationPosition = this->position;
    this->position -= this->lowerPartDirection * this->SPEED * delta * 0.5;

    if (this->isColliding(collidableList))
        this->position = preTranslationPosition;
}

bool Player::isColliding(const std::list<Collidable *> &collidableList) {
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

Bullet Player::shoot() {
    return Bullet{this->position + this->upperPartDirection * 10, this->upperPartDirection, true};
}

void Player::getHit(int hp) {
    this->hp -= hp;
}

bool Player::isAlive() {
    return this->hp > 0;
}

