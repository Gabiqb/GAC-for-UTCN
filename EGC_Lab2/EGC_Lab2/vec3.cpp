#include "vec3.h"

egc::vec3& egc::vec3::operator=(const vec3& srcVector)
{
    
    this->x = srcVector.x;
    this->y = srcVector.y;
    this->z = srcVector.z;
    return *this;
}

egc::vec3 egc::vec3::operator+(const vec3& srcVector) const
{
    egc::vec3 rez;
    rez.x += this->x+srcVector.x;
    rez.y += this->y+srcVector.y;
    rez.z += this->z+srcVector.z;
    return rez;
}

egc::vec3& egc::vec3::operator+=(const vec3& srcVector)
{
    this->x += srcVector.x;
    this->y += srcVector.y;
    this->z += srcVector.z;
    return (*this);
    // TODO: insert return statement here
}

egc::vec3 egc::vec3::operator*(float scalarValue) const
{
    egc::vec3 rez;
    rez.x *= scalarValue;
    rez.y *= scalarValue;
    rez.z *= scalarValue;
    return rez;
   
}

egc::vec3 egc::vec3::operator-(const vec3& srcVector) const
{
    egc::vec3 rez;
    rez.x  = this->x -srcVector.x;
    rez.y  = this->y -srcVector.y;
    rez.z  = this->z - srcVector.z;
    return rez;
}

egc::vec3& egc::vec3::operator-=(const vec3& srcVector)
{
    this->x -= srcVector.x;
    this->y -= srcVector.y;
    this->z -= srcVector.z;
    return *this;
    // TODO: insert return statement here
}

egc::vec3 egc::vec3::operator-() const
{
    egc::vec3 rez;
    rez.x = -1.0f * this->x;
    rez.y = -1.0f * this->y;
    rez.z = -1.0f * this->z;
    return rez;
}

float egc::vec3::length() const
{
    float rez = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    return rez;
}

egc::vec3& egc::vec3::normalize()
{
    float len = this->length();
    this->x /= len;
    this->y /= len;
    this->z /= len;
    return *this;
    // TODO: insert return statement here
}
