//
// Created by silvair on 25.12.18.
//

#include <camera.h>
#include <GL/glu.h>
#include <constants.h>


Camera::Camera(const Vector3D &playerPosition) : playerPosition(playerPosition),
                                                 mousePosition(Vector3D{0, 0, 0}) {

}

void Camera::run() {
    gluLookAt(this->playerPosition.getX(), this->playerPosition.getY() - CAMERA_HEIGHT / 2, this->CAMERA_HEIGHT,
              this->playerPosition.getX(), this->playerPosition.getY(), 0.0,
              0.0, 1.0, 0.0);
}

Vector3D Camera::getMouseRelativeCoordinates() {
    return Vector3D{this->mousePosition.getX() - static_cast<float>(WINDOW_WIDTH) / 2,
                    -(this->mousePosition.getY() - static_cast<float>(WINDOW_HEIGHT) / 2),
                    0};
}

void Camera::setMousePosition(const Vector3D &mousePosition) {
    this->mousePosition = mousePosition;
}
