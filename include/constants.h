//
// Created by silvair on 25.12.18.
//

#ifndef CZOLGI_CONSTANTS_H
#define CZOLGI_CONSTANTS_H

#include <vector>
#include "wall.h"

const int WINDOW_WIDTH = 1080;
const int WINDOW_HEIGHT = 720;

const std::vector<Vector3D> WALLS_POSITIONS{
        Vector3D{1, 0, 0} * Wall::SIZE,
        Vector3D{1, 1, 0} * Wall::SIZE,
        Vector3D{1, 2, 0} * Wall::SIZE,
        Vector3D{1, 3, 0} * Wall::SIZE,
        Vector3D{2, 3, 0} * Wall::SIZE
};

#endif //CZOLGI_CONSTANTS_H
