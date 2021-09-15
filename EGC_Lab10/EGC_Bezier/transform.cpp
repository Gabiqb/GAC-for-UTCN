#include "mat3.h"
#include "vec2.h"
#include "transform.h"

namespace egc {
	mat3 translate(const vec2 translateArray)
	{
		mat3 T;
		T.at(0, 2) = translateArray.x;
		T.at(1, 2) = translateArray.y;
		return T;

	}

	mat3 translate(float tx, float ty)
	{
		mat3 T;
		T.at(0, 2) = tx;
		T.at(1, 2) = ty;
		return T;
	}

	mat3 scale(const vec2 scaleArray)
	{
		mat3 S;
		S.at(0, 0) = scaleArray.x;
		S.at(1, 1) = scaleArray.y;
		return S;
	}

	mat3 scale(float sx, float sy)
	{
		mat3 S;
		S.at(0, 0) = sx;
		S.at(1, 1) = sy;
		return S;
	}

	mat3 rotate(float angle)
	{
		mat3 R;
		const float rad = angle * PI / 180;
		R.at(0, 0) = cos(rad);
		R.at(0, 1) = -sin(rad);
		R.at(1, 0) = sin(rad);
		R.at(1, 1) = cos(rad);
		return R;
	}

	mat4 translate(const vec3 translateArray)
	{
		mat4 T;
		T.at(0, 3) = translateArray.x;
		T.at(1, 3) = translateArray.y;
		T.at(2, 3) = translateArray.z;
		return T;
	}

	mat4 translate(float tx, float ty, float tz)
	{
		mat4 T;
		T.at(0, 3) = tx;
		T.at(1, 3) = ty;
		T.at(2, 3) = tz;
		return T;
	}

	mat4 scale(const vec3 scaleArray)
	{
		mat4 S;
		S.at(0, 0) = scaleArray.x;
		S.at(1, 1) = scaleArray.y;
		S.at(2, 2) = scaleArray.z;
		return S;
	}

	mat4 scale(float sx, float sy, float sz)
	{
		mat4 S;
		S.at(0, 0) = sx;
		S.at(1, 1) = sy;
		S.at(2, 2) = sz;
		return S;
	}

	mat4 rotateX(float angle)
	{
		mat4 R;
		const float rad = angle * PI / 180;
		R.at(1, 1) = cos(rad);
		R.at(2, 1) = sin(rad);
		R.at(1, 2) = -sin(rad);
		R.at(2, 2) = cos(rad);
		return R;
	}

	mat4 rotateY(float angle)
	{
		mat4 R;
		const float rad = angle * PI / 180;
		R.at(0, 0) = cos(rad);
		R.at(0, 2) = sin(rad);
		R.at(2, 0) = -sin(rad);
		R.at(2, 2) = cos(rad);
		return R;
	}

	mat4 rotateZ(float angle)
	{
		mat4 R;
		const float rad = angle * PI / 180;
		R.at(0, 0) = cos(rad);
		R.at(1, 0) = sin(rad);
		R.at(0, 1) = -sin(rad);
		R.at(1, 1) = cos(rad);
		return R;
	}







}