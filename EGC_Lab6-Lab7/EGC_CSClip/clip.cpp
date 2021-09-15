#include "clip.h"
#include <algorithm>
#include "vec2.h"
using namespace std;

namespace egc {
	float min(float x1, float x2, float x3, float x4)
	{
		float min = 2147483647;
		if (x1 < min)
			min = x1;
		if (x2 < min)
			min = x2;
		if (x3 < min)
			min = x3;
		if (x4 < min)
			min = x4;
		return min;
	}
	float max(float x1, float x2, float x3, float x4)
	{
		float max = -1;
		if (x1 > max)
			max = x1;
		if (x2 > max)
			max = x2;
		if (x3 > max)
			max = x3;
		if (x4 > max)
			max = x4;
		return max;
	}
	std::vector<int> computeCSCode(std::vector<vec3> clipWindow, const vec3 p) {
		std::vector<int> code;
		code = { 0,0,0,0 };
		float ymin = min(clipWindow[0].y, clipWindow[1].y, clipWindow[2].y, clipWindow[3].y);
		float xmin = min(clipWindow[0].x, clipWindow[1].x, clipWindow[2].x, clipWindow[3].x);
		float ymax = max(clipWindow[0].y, clipWindow[1].y, clipWindow[2].y, clipWindow[3].y);
		float xmax = max(clipWindow[0].x, clipWindow[1].x, clipWindow[2].x, clipWindow[3].x);
		//TO DO - compute the code for the point given as argument
		if (p.x < xmin)
			code[3] = 1;
		if (p.x > xmax)
			code[2] = 1;
		if (p.y > ymax)
			code[1] = 1;
		if (p.y < ymin)
			code[0] = 1;

		   
		return code;
	}

	bool simpleRejection(std::vector<int> cod1, std::vector<int> cod2) {
		//TO DO - write the code to determine if the two input codes represent 
		//points in the SIMPLE REJECTION case
		for (int i = 0; i < 4; i++)
			if (cod1[i] == 1 && cod2[i]==1)
				return true;

		return false;
	}

	bool simpleAcceptance(std::vector<int> cod1, std::vector<int> cod2) {
		//TO DO - write the code to determine if the two input codes represent 
		//points in the SIMPLE ACCEPTANCE case
		for (int i = 0; i < 4; i++)
			if (cod1[i] == 1 || cod2[i] == 1)
				return false;
		return true;
	}
	void invert(vec3 *p1, vec3 *p2,std::vector<int> *cod1,std::vector<int> *cod2)
	{
		vec3 p3 = *p1;
		*p1 = *p2;
		*p2 = p3;

		std::vector<int> cod3 = *cod1;
		*cod1 = *cod2;
		*cod2 = cod3;
	}
	bool insideArea(std::vector<int> cod)
	{
		for (int i = 0; i < 4; i++)
			if (cod[i] == 1)
				return false;
		return true;
	}
	
	//function returns -1 if the line segment cannot be clipped
	int lineClip_CohenSutherland(std::vector<vec3> clipWindow, vec3& p1, vec3& p2) {
		//TO DO - implement the Cohen-Sutherland line clipping algorithm - consult the laboratory work
		bool finished = false;
		bool respins = false;
		bool display = false;
		float ymin=min(clipWindow[0].y, clipWindow[1].y,clipWindow[2].y,clipWindow[3].y);
		float xmin=min(clipWindow[0].x, clipWindow[1].x, clipWindow[2].x, clipWindow[3].x);
		float ymax=max(clipWindow[0].y, clipWindow[1].y, clipWindow[2].y, clipWindow[3].y);
		float xmax=max(clipWindow[0].x, clipWindow[1].x, clipWindow[2].x, clipWindow[3].x);
		do
		{
			std::vector <int> cod1 = computeCSCode(clipWindow,p1);
			std::vector <int> cod2 = computeCSCode(clipWindow,p2);
			 respins = simpleRejection(cod1, cod2);
			if (respins == true)
				finished = true;
			else
			{
				 display = simpleAcceptance(cod1, cod2);
				if (display == true)
					finished = true;
				else
				{
					if(insideArea(cod1))
					   invert(&p1, &p2,&cod1,&cod2);
					if (cod1[0] == 1 && p2.y != p1.y)
					{
						 
						p1.x = p1.x + (p2.x - p1.x) * (ymin - p1.y) / (p2.y - p1.y);
						p1.y = ymin;

					}
					else if (cod1[1] == 1 && p2.y != p1.y)
					{
						p1.x = p1.x + (p2.x - p1.x) * (ymax - p1.y) / (p2.y - p1.y);
						p1.y = ymax;
					}
					else if (cod1[2] == 1 && p2.x != p1.x)
					{
						p1.y = p1.y + (p2.y - p1.y) * (xmax - p1.x) / (p2.x - p1.x);
						p1.x = xmax;
					}
					else if (cod1[3] == 1 && p2.x != p1.x)
					{
						 
						p1.y = p1.y + (p2.y - p1.y) * (xmin - p1.x) / (p2.x - p1.x);
						p1.x = xmin;	
					}
				}
			}
		}while (!finished);
		if (respins == true)
			return -1;
		else
			return 0;
	
	}
	std::vector<vec3> normali(std::vector<vec3>clipWindow)
	{
		std::vector<vec3> N;
		
		return N;
	}
	 
	float maxi(float a1, float a2)
	{
		float max = a1;
		if (a2 > max)
			max = a2;
		return max;
	}
	float mini(float a1, float a2)
	{
		float min= a1;
		if (a2 < min)
			min = a2;
		return min;
	}
	int lineClip_CyrusBeck(std::vector<vec3> clipWindow, vec3& p1, vec3& p2) {
		std::vector<vec3> Ni;
	 
		vec3 aux;
		for (int i = 0; i < clipWindow.size(); i++)
		{
			aux = clipWindow[(i + 1)%clipWindow.size()] - clipWindow[i%clipWindow.size()];
			Ni.push_back(vec3(aux.y,-aux.x,0));
		}
	 
		if (p1 == p2)
		{
		  for(int i=0;i<clipWindow.size();i++)
			if (dotProduct(Ni[i], (p1 - clipWindow[i])) > 0)
				return -1;
		}
		else
		{
			float te = 0.0;
			float tl = 1.0;
			vec3 D = p2 - p1;
	    	for (int i = 0; i < clipWindow.size(); i++)
			{
				float t=1.0;
				float produs = dotProduct(Ni[i], D);
				if (produs !=0)
				{
					t = dotProduct(Ni[i], (p1 - clipWindow[i])) / (-produs);
					if (produs < 0)
						te = maxi(te, t);
					else
						tl = mini(tl, t);
				}
				else
				{
					if (dotProduct(Ni[i], (p1 - clipWindow[i])) > 0)
						return -1;
				 
				}
			}		
			if (te > tl)
			{
				return -1;
			}
			else
			{	
				vec3 aux = p1;
				p1 = p1 + (p2 - p1) * te;
				p2 = aux + (p2 - aux) * tl;		
				std::cout << p1 << " " << p2<<endl;
			}
		}

 	}
	 
	 
}

