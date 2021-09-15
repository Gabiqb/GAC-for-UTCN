#include "zbuffer.h"
#include "include/SDL.h"
namespace egc {

	void computeAlphaBetaGamma(const std::vector<egc::vec4>& triangleVertices, vec2 pixel, float& alpha, float& beta, float& gamma) {
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
	 
	void drawTriangleInZBuffer(std::vector<egc::vec4> triangle, float depthBuffer[WINDOW_HEIGHT][WINDOW_WIDTH], float& zmin, float& zmax) {

		//TO DO  -  implement the "drawing" of the triangle inside the depth buffer
		//The buffer has the same dimension as the screen - use it to fill in not the pixel color of each pixel in the triangel - but the pixel depth (Z component)
		//So you are going to fill in the Z of each pixel inside the triangle - use the algorithm from last week to access the inside of the triangle

	 	
		float minimX = INT_MAX;
		float minimY = INT_MAX;
		float maximX = INT_MIN;
		float maximY = INT_MIN;

		for (int i = 0; i < triangle.size(); i++) {
			if (triangle.at(i).x < minimX)
				minimX = triangle.at(i).x;
			if (triangle.at(i).x > maximX)
				maximX = triangle.at(i).x;
			if (triangle.at(i).y < minimY)
				minimY = triangle.at(i).y;
			if (triangle.at(i).y > maximY)
				maximY = triangle.at(i).y;
		}

		float alpha, beta, gamma;
		for (int x = minimX; x <= maximX; x++) {
			for (int y = minimY; y <= maximY; y++) {
				vec2 pixel = vec2(x, y);
				computeAlphaBetaGamma(triangle, pixel, alpha, beta, gamma);
				if (alpha >= 0 && alpha <= 1 && beta >= 0 && beta <= 1 && gamma >= 0 && gamma <= 1) {
					float z = triangle.at(0).z * alpha + triangle.at(1).z * beta + triangle.at(2).z * gamma;
					if (zmin < z)
						zmin = z;
					if (zmax > z)
						zmax = z;
					if(z>depthBuffer[x][y])
						depthBuffer[x][y] = z;

				}
			}
		}
		 
		//While you compute the z for each pixel, you can also determine the zmin and zmax values ===> from all the points of the rabbit 
		//zmin and zmax are the minimum and maximum Z values FROM ALL THE VERICES OF THE RABBIT

	}

}
