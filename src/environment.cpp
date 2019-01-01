//
// Created by silvair on 24.12.18.
//

#include <environment.h>
#include <GL/gl.h>

#include "environment.h"

Environment::Environment() = default;

void Environment::run(float delta) {

}

void Environment::render() {
    this->drawGround();
}

void Environment::drawGround() {
    glColor3f(0.298, 0.686, 0.313);

    glBegin(GL_QUADS);
    glVertex3f(-200, -200, 0);
    glVertex3f(1200, -200, 0);
    glVertex3f(1200, 1200, 0);
    glVertex3f(-200, 1200, 0);
    glEnd();
}
