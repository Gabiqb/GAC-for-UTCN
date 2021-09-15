#include "Bezier.h"
#include "math.h"
#include <vector>
 

//Return the value of P(t), where t is in [0,1]
vec2 getParametricPoint(float t, vec2 p0, vec2 p1) {
	//P(t) = (1 - t)*P0 + t*P1
	vec2 point;
	point = p0*(1-t) + p1*t;
	return point;
}

//Paint the pixels that are on the line P0P1
void drawParametricLinePoints(vec2 p0, vec2 p1, SDL_Renderer* renderer) {
	//Hint: To paint a single pixel, you can use the function: SDL_RenderDrawPoint(renderer, x, y)
	for (float i = 0; i <= 1; i+=0.00001)
	{
		vec2 temp = getParametricPoint(i, p0, p1);
		SDL_RenderDrawPoint(renderer, temp.x, temp.y);
	}
}

//Return the value of B(t), where t is in [0,1]. The value of B(t) is computed by taking into account all the 
//controll points contained within the input vector

vec2 getBezierPoint(std::vector<vec2> controlPoints, float t) {
	vec2 point;
	if (controlPoints.size() == 2)
	{
		point =controlPoints[0] * (1 - t) + controlPoints[1] * t;
		return point;
	}
 
		std::vector<vec2> pn_1;
		std::vector<vec2> pn;
		for (int i = 0; i < controlPoints.size() - 1; i++)
			pn_1.push_back(controlPoints[i]);
		for (int i = 1; i < controlPoints.size(); i++)
			pn.push_back(controlPoints[i]);
		
		point=getBezierPoint(pn_1, t) * (1 - t) + getBezierPoint(pn, t) * t;

 
 
	return point;
}

//Paint the pixels that are on the Bezier curve defined by the given control points
void drawBezierPoints(std::vector<vec2> controlPoints, SDL_Renderer* renderer) {
  
	for (float i = 0; i <= 1; i += 0.0005)
	{
		vec2 temp = getBezierPoint(controlPoints,i);
		SDL_RenderDrawPoint(renderer, temp.x, temp.y);
	}
}
