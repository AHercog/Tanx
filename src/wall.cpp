//
// Created by silvair on 25.12.18.
//

#include <GL/gl.h>
#include <GL/freeglut.h>
#include "wall.h"

Wall::Wall(const Vector3D &position) : position(position) {

}

void Wall::render() const {
    glColor3f(0.584, 0.458, 0.803);

    glPushMatrix();
    glTranslatef(this->position.getX(), this->position.getY(), this->position.getZ() + Wall::SIZE / 2.0f);
    glutSolidCube(Wall::SIZE);
    glPopMatrix();
}

const Vector3D &Wall::getPosition() const {
    return this->position;
}
