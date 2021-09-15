#include "bresenham.h"
#include "math.h"
#include <stdio.h>
//Detects in which octant a line is situated
int getOctant(BresenhamLine line) {

	int deltaY = (line.endY - line.startY);
	int deltaX = (line.endX - line.startX);

	//Slope		
	float m = abs(deltaY) / (float)abs(deltaX);
	printf("%f %f %f\n", m, abs(deltaX), abs(deltaY));

	if ((m < 1) && (deltaX > 0) && (deltaY <= 0)) //first octant
		return 1;
	else if ((m >= 1) && (deltaX > 0) && (deltaY <= 0)) //2
		return 2;
	else if ((m >= 1) && (deltaX < 0) && (deltaY <= 0)) //3
		return 3;
	else if ((m < 1) && (deltaX < 0) && (deltaY <= 0)) //4
		return 4;
	else if ((m < 1) && (deltaX < 0) && (deltaY >= 0)) //5
		return 5;
	else if ((m >= 1) && (deltaX < 0) && (deltaY >= 0)) //6
		return 6;
	else if ((m >= 1) && (deltaX > 0) && (deltaY >= 0)) //7
		return 7;
	else if ((m < 1) && (deltaX > 0) && (deltaY >= 0)) //8
		return 8;
	return 0;
}

//Draws a new raster line using Bresenham's algorithm
void BresenhamDraw(BresenhamLine line, SDL_Renderer* renderer) {
	int tmpStartX = 0;
	int tmpStartY = 0;
	int tmpEndX = 0;
	int tmpEndY = 0;
	int tmpCurrentX = 0;
	int tmpCurrentY = 0;

	int dy = abs(line.endY - line.startY);
	int dx = abs(line.endX - line.startX);

	int d, inc1, inc2;

	int octant = getOctant(line);

	switch (octant)
	{
	case 1:
		tmpStartX = tmpCurrentX = line.startX;
		tmpEndX = line.endX;
		tmpStartY = tmpCurrentY = line.startY;
		tmpEndY = line.endY;

		d = 2 * dy - dx;
		inc1 = 2 * dy;
		inc2 = 2 * (dy - dx);

		while (tmpCurrentX < tmpEndX)
		{
			//Draw current point
			SDL_RenderDrawPoint(renderer, tmpCurrentX, tmpCurrentY);
			++tmpCurrentX;

			if (d < 0)
				d += inc1;
			else
			{
				d += inc2;
				--tmpCurrentY;
			}
			printf("1");
		}
		break;
	case 2:
		tmpStartX = tmpCurrentX = line.startX;
		tmpEndX = line.endX;
		tmpStartY = tmpCurrentY = line.startY;
		tmpEndY = line.endY;

		d = 2 * dx - dy;
		inc1 = 2 * dx;
		inc2 = 2 * (dx - dy);

		while (tmpCurrentY > tmpEndY)
		{
			//Draw current point
			SDL_RenderDrawPoint(renderer, tmpCurrentX, tmpCurrentY);
			--tmpCurrentY;

			if (d < 0)
				d += inc1;
			else
			{
				d += inc2;
				tmpCurrentX++;
			}
			printf("2");
		}
	
		break;
	case 3:
		tmpStartX = tmpCurrentX = line.startX;
		tmpEndX = line.endX;
		tmpStartY = tmpCurrentY = line.startY;
		tmpEndY = line.endY;

		d = 2 * dx - dy;
		inc1 = 2 * dx;
		inc2 = 2 * (dx - dy);

		while (tmpCurrentY > tmpEndY)
		{
			//Draw current point
			SDL_RenderDrawPoint(renderer, tmpCurrentX, tmpCurrentY);
			--tmpCurrentY;

			if (d < 0)
				d += inc1;
			else
			{
				d += inc2;
				tmpCurrentX--;
			}
			printf("3");
		}
		break;
	case 4:
		tmpStartX = tmpCurrentX = line.startX;
		tmpEndX = line.endX;
		tmpStartY = tmpCurrentY = line.startY;
		tmpEndY = line.endY;

		d = 2 * dy - dx;
		inc1 = 2 * dy;
		inc2 = 2 * (dy - dx);

		while (tmpCurrentX > tmpEndX)
		{
			//Draw current point
			SDL_RenderDrawPoint(renderer, tmpCurrentX, tmpCurrentY);
			--tmpCurrentX;

			if (d < 0)
				d += inc1;
			else
			{
				d += inc2;
				--tmpCurrentY;
			}
			printf("4");
		}
		break;
	case 5:
		tmpStartX = tmpCurrentX = line.startX;
		tmpEndX = line.endX;
		tmpStartY = tmpCurrentY = line.startY;
		tmpEndY = line.endY;

		d = 2 * dy - dx;
		inc1 = 2 * dy;
		inc2 = 2 * (dy - dx);

		while (tmpCurrentX > tmpEndX)
		{
			//Draw current point
			SDL_RenderDrawPoint(renderer, tmpCurrentX, tmpCurrentY);
			--tmpCurrentX;

			if (d < 0)
				d += inc1;
			else
			{
				d += inc2;
				++tmpCurrentY;
			}
			printf("5");
		}
		break;
	case 6:
		tmpStartX = tmpCurrentX = line.startX;
		tmpEndX = line.endX;
		tmpStartY = tmpCurrentY = line.startY;
		tmpEndY = line.endY;

		d  = 2 * dx - dy;
		inc1 = 2 * dx;
		inc2 = 2 * (dx - dy);

		while (tmpCurrentY < tmpEndY)
		{
			//Draw current point
			SDL_RenderDrawPoint(renderer, tmpCurrentX, tmpCurrentY);
			++tmpCurrentY;

			if (d < 0)
				d += inc1;
			else
			{
				d += inc2;
				tmpCurrentX--;
			}
			printf("6");
		}
		break;
	case 7:
		tmpStartX = tmpCurrentX = line.startX;
		tmpEndX = line.endX;
		tmpStartY = tmpCurrentY = line.startY;
		tmpEndY = line.endY;

		d = 2 * dx - dy;
		inc1 = 2 * dx;
		inc2 = 2 * (dx - dy);

		while (tmpCurrentY < tmpEndY)
		{
			//Draw current point
			SDL_RenderDrawPoint(renderer, tmpCurrentX, tmpCurrentY);
			++tmpCurrentY;

			if (d < 0)
				d += inc1;
			else
			{
				d += inc2;
				tmpCurrentX++;
			}
			printf("7");
		}
		break;
	case 8:
		tmpStartX = tmpCurrentX = line.startX;
		tmpEndX = line.endX;
		tmpStartY = tmpCurrentY = line.startY;
		tmpEndY = line.endY;

		d = 2 * dy - dx;
		inc1 = 2 * dy;
		inc2 = 2 * (dy - dx);

		while (tmpCurrentX < tmpEndX)
		{
			//Draw current point
			SDL_RenderDrawPoint(renderer, tmpCurrentX, tmpCurrentY);
			++tmpCurrentX;

			if (d < 0)
				d += inc1;
			else
			{
				d += inc2;
				++tmpCurrentY;
			}
			printf("8");
		}
		break;

	default:
		break;
	}
}
void plot_points(SDL_Renderer* renderer, float x, float y,float cX,float cY)
{
	SDL_RenderDrawPoint(renderer, x+cX, y+cY);
	SDL_RenderDrawPoint(renderer, x + cX, -y + cY);
	SDL_RenderDrawPoint(renderer, -x + cX, y + cY);
	SDL_RenderDrawPoint(renderer, -x + cX, -y + cY);
	SDL_RenderDrawPoint(renderer, y + cX , x + cY);
	SDL_RenderDrawPoint(renderer, -y + cX, x + cY);
	SDL_RenderDrawPoint(renderer, y + cX, -x + cY);
	SDL_RenderDrawPoint(renderer, -y + cX, -x + cY);
}
//Draws a new raster circle using Bresenham's algorithm
void BresenhamDraw(BresenhamCircle circle, SDL_Renderer* renderer) {
	float R = circle.radius;
	float xC = circle.centerX;
	float yC = circle.centerY;
	float currentY = R;
	float d = 1.0 / 4 - R;
	for (float currentX = 0.0; currentX < ceil(R / sqrt(2)); currentX++)
	{
		plot_points(renderer, currentX, currentY, xC, yC);
		d += 2 * currentX + 1;
		if (d > 0)
		{
			d += 2 - 2 * currentY;
			--currentY;
		}
	}

}