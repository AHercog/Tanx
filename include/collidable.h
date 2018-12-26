//
// Created by silvair on 25.12.18.
//

#ifndef CZOLGI_COLLIDABLE_H
#define CZOLGI_COLLIDABLE_H

#include "vector_3d.h"

class Collidable {
public:
    virtual const Vector3D &getPosition() const = 0;

    virtual int getSize() const = 0;
};


#endif //CZOLGI_COLLIDABLE_H
