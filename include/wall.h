//
// Created by silvair on 25.12.18.
//

#ifndef CZOLGI_WALL_H
#define CZOLGI_WALL_H

#include <vector_3d.h>
#include "collidable.h"

class Wall : public Collidable {
public:
    static const int SIZE = 10;

    explicit Wall(const Vector3D &position);

    void render() const;

    const Vector3D &getPosition() const override;

    int getSize() const override { return Wall::SIZE; };

private:

    Vector3D position;
};

#endif //CZOLGI_WALL_H
