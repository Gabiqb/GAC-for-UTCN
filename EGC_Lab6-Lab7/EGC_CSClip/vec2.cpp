#include "vec2.h"

egc::vec2& egc::vec2::operator=(const vec2& srcVector)
{
	this->x = srcVector.x;
	this->y = srcVector.y;
	return *this;
}

egc::vec2 egc::vec2::operator+(const vec2& srcVector) const
{
	egc::vec2 rez;
	rez.x = this->x + srcVector.x;
	rez.y = this->y + srcVector.y;

	return rez;
}

egc::vec2& egc::vec2::operator+=(const vec2& srcVector)
{
	this->x += srcVector.x;
	this->y += srcVector.y;
	return *this;
	// TODO: insert return statement here
}

egc::vec2 egc::vec2::operator*(float scalarValue) const
{
	egc::vec2 rez;
	rez.x = this->x * scalarValue;
	rez.y = this->y * scalarValue;
	return rez;
}

egc::vec2 egc::vec2::operator-(const vec2& srcVector) const
{
	egc::vec2 rez;
	 
	rez.x = this->x - srcVector.x;
	rez.y = this->y - srcVector.y;

	return rez;
}

egc::vec2& egc::vec2::operator-=(const vec2& srcVector)
{
	this->x -= srcVector.x;
	this->y -= srcVector.y;
	return *this;
}

egc::vec2 egc::vec2::operator-() const
{
	egc::vec2 rez;
	rez.x = -1.0f * this->x;
	rez.y = -1.0f* this->y;
	return rez;
}

float egc::vec2::length() const
{
	float rez = sqrt(this->x * this->x + this->y * this->y);
	return rez;
}

egc::vec2& egc::vec2::normalize()
{
	float len = (*this).length();
	this->x = this->x / len;
	this->y = this->y / len;
	return *this;
}
