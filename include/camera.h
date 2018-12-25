//
// Created by silvair on 25.12.18.
//

#ifndef CZOLGI_CAMERA_H
#define CZOLGI_CAMERA_H


#include "vector_3d.h"

class Camera {
public:
    explicit Camera(const Vector3D &playerPosition);

    void run();

    Vector3D getMouseRelativeCoordinates();

    void setMousePosition(const Vector3D &mousePosition);

private:
    Vector3D mousePosition;
    const Vector3D &playerPosition;
    const int CAMERA_HEIGHT = 50;
};


#endif //CZOLGI_CAMERA_H
