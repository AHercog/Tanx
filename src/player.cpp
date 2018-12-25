//
// Created by silvair on 24.12.18.
//

#include <vector_3d.h>
#include <player.h>
#include <GL/freeglut.h>
#include <cmath>

Player::Player(const Vector3D &coordinates) : position(coordinates) {
}

void Player::run(float delta) {
}

void Player::render() {
    glColor3f(0, 1, 0);

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

void Player::rotateLeft(float delta) {
    this->lowerPartDirection.rotateAlongZ(this->ROTATION_SPEED * delta);
}

void Player::rotateRight(float delta) {
    this->lowerPartDirection.rotateAlongZ(-this->ROTATION_SPEED * delta);
}

void Player::moveForward(float delta, const std::list<Wall *> &wallList) {
    Vector3D preTranslationPosition = this->position;
    this->position += this->lowerPartDirection * this->SPEED * delta;

    if (this->isColliding(wallList))
        this->position = preTranslationPosition;
}

void Player::moveBackward(float delta, const std::list<Wall *> &wallList) {
    Vector3D preTranslationPosition = this->position;
    this->position -= this->lowerPartDirection * this->SPEED * delta;

    if (this->isColliding(wallList))
        this->position = preTranslationPosition;
}

bool Player::isColliding(const std::list<Wall *> &wallList) {
    for (const auto wall : wallList) {
        const Vector3D &differenceVector = wall->getPosition() - this->position;
        const auto minimalPossibleDistance = this->SIZE / 2.0f + wall->getSize() / 2.0f;

        if (differenceVector.length() <= minimalPossibleDistance)
            return true;
    }

    return false;
}

void Player::rotateUpperPart(const Vector3D &direction) {
    this->upperPartDirection = direction / direction.length();
}

const Vector3D &Player::getPosition() {
    return this->position;
}

Bullet Player::shoot() {
    return Bullet{this->position + this->upperPartDirection * 10, this->upperPartDirection};
}

