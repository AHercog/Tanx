//
// Created by silvair on 24.12.18.
//

#ifndef CZOLGI_COORDINATES_H
#define CZOLGI_COORDINATES_H


class Vector3D {
public:
    Vector3D(float x, float y, float z);

    void rotateAlongZ(float degrees);

    Vector3D operator+(const Vector3D &otherCoordinates) const;

    Vector3D operator-(const Vector3D &otherCoordinates) const;

    Vector3D operator*(float multiplier) const;

    Vector3D operator/(float multiplier) const;

    void operator+=(const Vector3D &otherCoordinates);

    void operator-=(const Vector3D &otherCoordinates);

    void operator*=(float multiplier);

    void operator/=(float multiplier);

    float getX() const;

    float getY() const;

    float getZ() const;

    float getAngleAlongZ() const;

    float length() const;

private:
    float x, y, z;
};


#endif //CZOLGI_COORDINATES_H
