
//
// Created by silvair on 24.12.18.
//

#include <vector_3d.h>
#include <cmath>


Vector3D::Vector3D(float x, float y, float z) : x(x), y(y), z(z) {}

void Vector3D::rotateAlongZ(float degrees) {
    auto newAngle = std::atan2(this->y, this->x) + degrees * M_PI / 180;
    auto distance = std::hypot(this->x, this->y);

    this->x = static_cast<float>(std::cos(newAngle) * distance);
    this->y = static_cast<float>(std::sin(newAngle) * distance);
}

Vector3D Vector3D::operator+(const Vector3D &otherCoordinates) const {
    return Vector3D(this->x + otherCoordinates.x,
                    this->y + otherCoordinates.y,
                    this->z + otherCoordinates.z);
}

Vector3D Vector3D::operator-(const Vector3D &otherCoordinates) const {
    return Vector3D(this->x - otherCoordinates.x,
                    this->y - otherCoordinates.y,
                    this->z - otherCoordinates.z);

}

Vector3D Vector3D::operator*(float multiplier) const {
    return Vector3D(this->x * multiplier,
                    this->y * multiplier,
                    this->z * multiplier);
}

Vector3D Vector3D::operator/(float multiplier) const {
    return Vector3D(this->x / multiplier,
                    this->y / multiplier,
                    this->z / multiplier);
}

void Vector3D::operator+=(const Vector3D &otherCoordinates) {
    this->x += otherCoordinates.x;
    this->y += otherCoordinates.y;
    this->z += otherCoordinates.z;
}

void Vector3D::operator-=(const Vector3D &otherCoordinates) {
    this->x -= otherCoordinates.x;
    this->y -= otherCoordinates.y;
    this->z -= otherCoordinates.z;
}

void Vector3D::operator*=(float multiplier) {
    this->x *= multiplier;
    this->y *= multiplier;
    this->z *= multiplier;
}

void Vector3D::operator/=(float multiplier) {
    this->x /= multiplier;
    this->y /= multiplier;
    this->z /= multiplier;
}

float Vector3D::getX() const {
    return this->x;
}

float Vector3D::getY() const {
    return this->y;
}

float Vector3D::getZ() const {
    return this->z;
}

float Vector3D::getAngleAlongZ() const {
    const auto angle = std::atan2(this->y, this->x) * 180 / M_PI;
    return static_cast<float>(angle);
}

float Vector3D::length() const {
    const auto distanceSqrt = sqrt(pow(this->getX(), 2) + pow(this->getY(), 2) + pow(this->getZ(), 2));
    return static_cast<float>(distanceSqrt);
}
