#include "rasterization.h"

namespace egc {


	void computeAlphaBetaGamma(const std::vector<egc::vec4>& triangleVertices, vec2 pixel, float& alpha, float& beta, float& gamma){
		
		vec4 vertex1 = triangleVertices.at(0);
		vec4 vertex2 = triangleVertices.at(1);
		vec4 vertex3 = triangleVertices.at(2);

		float Fbc = (vertex2.y - vertex3.y) * pixel.x + (vertex3.x - vertex2.x) * pixel.y + vertex2.x * vertex3.y - vertex3.x * vertex2.y;
		float Fbcxy = (vertex2.y - vertex3.y) * vertex1.x + (vertex3.x - vertex2.x) * vertex1.y + vertex2.x * vertex3.y - vertex3.x * vertex2.y;
		float Fac = (vertex1.y - vertex3.y) * pixel.x + (vertex3.x - vertex1.x) * pixel.y + vertex1.x * vertex3.y - vertex3.x * vertex1.y;
		float Facxy = (vertex1.y - vertex3.y) * vertex2.x + (vertex3.x - vertex1.x) * vertex2.y + vertex1.x * vertex3.y - vertex3.x * vertex1.y;

		alpha = Fbc / Fbcxy;
		beta = Fac / Facxy;
		gamma = 1 - alpha - beta;
	}

	void rasterizeTriangle(SDL_Renderer* renderer, const std::vector<egc::vec4>& triangleVertices, const std::vector<egc::vec4>& triangleColors) {
		
		float minimX = INT_MAX;
		float minimY = INT_MAX;
		float maximX = INT_MIN;
		float maximY = INT_MIN;

		for (int i = 0; i < triangleVertices.size(); i++) {
			if (triangleVertices.at(i).x < minimX)
				minimX = triangleVertices.at(i).x;
			if (triangleVertices.at(i).x > maximX)
				maximX = triangleVertices.at(i).x;
			if (triangleVertices.at(i).y < minimY)
				minimY = triangleVertices.at(i).y;
			if (triangleVertices.at(i).y > maximY)
				maximY = triangleVertices.at(i).y;
		}

		float alpha, beta, gamma;

		for (int x = minimX; x <= maximX; x++) {
			for (int y = minimY; y <= maximY; y++) {
				vec2 pixel = vec2(x, y);
				computeAlphaBetaGamma(triangleVertices, pixel, alpha, beta, gamma);
				if (alpha >= 0 && alpha <= 1 && beta >= 0 && beta <= 1 && gamma >= 0 && gamma <= 1) {
					vec4 color = triangleColors.at(0) * alpha + triangleColors.at(1) * beta + triangleColors.at(2) * gamma;
					SDL_SetRenderDrawColor(renderer, color.x, color.y, color.z, color.w);
					SDL_RenderDrawPoint(renderer, x, y);
				}
			}
		}
	}

}
