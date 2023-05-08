#include "vector3.hpp"
#include <cmath>
#include <algorithm>

const Vector3 Vector3::UP(0, 1, 0);
const Vector3 Vector3::DOWN(0, -1, 0);
const Vector3 Vector3::LEFT(-1, 0, 0);
const Vector3 Vector3::RIGHT(1, 0, 0);
const Vector3 Vector3::FORWARD(0, 0, 1);
const Vector3 Vector3::BACK(0, 0, -1);
const Vector3 Vector3::ONE(1, 1, 1);
const Vector3 Vector3::ZERO(0, 0, 0);

Vector3::Vector3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

float Vector3::Length() const
{
    return sqrtf(x * x + y * y + z * z);
}

float Vector3::LengthSq() const
{
    return x * x + y * y + z * z;
}

float Vector3::Dot(const Vector3& v) const
{
    return x * v.x + y * v.y + z * v.z;
}

float Vector3::Max() const
{
    return std::max(x, std::max(y, z));
}

Vector3 Vector3::Cross(const Vector3& v) const
{
    return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

Vector3 Vector3::Reflect(const Vector3& n) const
{
    return *this - n * (2 * Dot(n));
}

Vector3 Vector3::Refract(const Vector3& n, float factor) const
{
    float c = -n.Dot(*this);
    Vector3 r_out_perp =  (*this + n * c) * factor;
    Vector3 r_out_parallel = n * -sqrt(fabs(1.0 - r_out_perp.LengthSq()));
    return r_out_perp + r_out_parallel;
}

Vector3& Vector3::Normalize()
{
    const float l = Length();
    x /= l;
    y /= l;
    z /= l;
    return *this;
}

Vector3 Vector3::Normalized() const
{
    const float l = Length();
    return Vector3(x / l, y / l, z / l);
}

Vector3 Vector3::Lerp(const Vector3& dest, float factor) const
{
    return (dest - *this) * factor + *this; 
}

float Vector3::operator[](int i) const
{
    return ((float*)this)[i];
}

float& Vector3::operator[](int i)
{
    return ((float*)this)[i];
}

Vector3& Vector3::operator+=(const Vector3& r)
{
    x += r.x;
    y += r.y;
    z += r.z;
    return *this;
}

Vector3& Vector3::operator-=(const Vector3& r)
{
    x -= r.x;
    y -= r.y;
    z -= r.z;
    return *this;
}

Vector3& Vector3::operator*=(float f)
{
    x *= f;
    y *= f;
    z *= f;
    return *this;
}

Vector3& Vector3::operator/=(float f)
{
    x /= f;
    y /= f;
    z /= f;
    return *this;
}

Vector3& Vector3::operator*=(const Vector3& v)
{
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
}

Vector3& Vector3::operator/=(const Vector3& v)
{
    x /= v.x;
    y /= v.y;
    z /= v.z;
    return *this;
}

Vector3 Vector3::operator+(const Vector3& r) const 
{
    return Vector3(x + r.x, y + r.y, z + r.z);
}

Vector3 Vector3::operator-(const Vector3& r) const 
{
    return Vector3(x - r.x, y - r.y, z - r.z);
}

Vector3 Vector3::operator*(float f) const
{
    return Vector3(x * f, y * f, z * f);
}

Vector3 Vector3::operator/(float f) const 
{
    return Vector3(x / f, y / f, z / f);
}

Vector3 Vector3::operator*(const Vector3& v) const
{
    return Vector3(x * v.x, y * v.y, z * v.z);
}

Vector3 Vector3::operator/(const Vector3& v) const
{
    return Vector3(x / v.x, y / v.y, z / v.z);
}

bool Vector3::operator==(const Vector3& r) const
{
    return x == r.x && y == r.y && z == r.z;
}

bool Vector3::operator!=(const Vector3& r) const
{
    return x != r.x || y != r.y || z != r.z;
}
