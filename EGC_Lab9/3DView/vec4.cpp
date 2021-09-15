#include "vec4.h"

egc::vec4& egc::vec4::operator=(const vec4& srcVector)
{
    this->x = srcVector.x;
    this->y = srcVector.y;
    this->z = srcVector.z;
    this->w = srcVector.w;
    return *this;
    // TODO: insert return statement here
}

egc::vec4 egc::vec4::operator+(const vec4& srcVector) const
{
    egc::vec4 rez;
    rez.w = this->w + srcVector.w;
    rez.x = this->x + srcVector.x;
    rez.y = this->y + srcVector.y;
    rez.z = this->z + srcVector.z;
    return rez;
}

egc::vec4& egc::vec4::operator+=(const vec4& srcVector)
{
    this->w += srcVector.w;
    this->x += srcVector.x;
    this->y += srcVector.y;
    this->z += srcVector.z;
    return *this;
    // TODO: insert return statement here
}

egc::vec4 egc::vec4::operator*(float scalarValue) const
{
    egc::vec4 rez;
    rez.w = this->w * scalarValue;
    rez.x = this->x * scalarValue;
    rez.y = this->y * scalarValue;
    rez.z = this->z * scalarValue;
    return rez;
    return vec4();
}

egc::vec4 egc::vec4::operator-(const vec4& srcVector) const
{
    egc::vec4 rez;
    rez.w = this->w - srcVector.w;
    rez.x = this->x - srcVector.x;
    rez.y = this->y - srcVector.y;
    rez.z = this->z - srcVector.z;
    return rez;
    
}

egc::vec4& egc::vec4::operator-=(const vec4& srcVector)
{
    this->w -= srcVector.w;
    this->x -= srcVector.x;
    this->y -= srcVector.y;
    this->z -= srcVector.z;
    return *this;
    // TODO: insert return statement here
}

egc::vec4 egc::vec4::operator-() const
{
    egc::vec4 rez;
    rez.w=this->w * -1.0f;
    rez.x=this->x * -1.0f;
    rez.y=this->y * -1.0f;
    rez.z=this->z * -1.0f;
    return rez;
}

float egc::vec4::length() const
{
    return (float)sqrt(this->w * this->w + this->x * this->x + this->y * this->y + this->z * this->z);
}

egc::vec4& egc::vec4::normalize()
{
    float len = this->length();
    this->w /= len;
    this->x /= len;
    this->y /= len;
    this->z /= len;
    return *this;
    // TODO: insert return statement here
}
