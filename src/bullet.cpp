//
// Created by silvair on 25.12.18.
//

#include <bullet.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <cmath>
#include <enemies/enemy_like.h>

Bullet::Bullet(const Vector3D &position, const Vector3D &direction, bool isGood) : position(position),
                                                                                   direction(direction),
                                                                                   isGood(isGood) {}

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

bool Bullet::shouldBeDestroyed(const std::list<Collidable *> &collidableList) const {
    for (const auto collidable : collidableList) {
        auto positionDifference = this->position - collidable->getPosition();

        if (positionDifference.length() < collidable->getSize() / 2.0f) {
            auto enemy = dynamic_cast<EnemyLike *>(collidable);

            if (enemy and this->isGood)
                enemy->getHit(10);

            auto player = dynamic_cast<Player *>(collidable);

            if (player and !this->isGood)
                player->getHit(10);

            return true;
        }
    }

    return false;
}
