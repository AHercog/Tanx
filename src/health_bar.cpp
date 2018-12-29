//
// Created by xaaq on 29.12.18.
//

#include <health_bar.h>
#include <GL/gl.h>
#include <GL/freeglut.h>

#include "health_bar.h"

HealthBar::HealthBar(int maxHp) : maxHp(maxHp), hp(maxHp) {}

void HealthBar::render(float x, float y) const {
    glColor3f(0.007, 0.466, 0.741);

    glPushMatrix();
    glTranslatef(x, y, 10);

    for (int i = 0; i < 10; ++i) {
        if (i / 10.0f >= static_cast<float>(this->hp) / this->maxHp)
            continue;

        glPushMatrix();
        glTranslatef(static_cast<GLfloat>((i * 0.5) - 2.5), 0, 0);
        glutSolidCube(0.5);
        glPopMatrix();
    }

    glPopMatrix();
}


