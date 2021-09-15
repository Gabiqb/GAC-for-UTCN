//
//  main.cpp
//  SDL_Lab1
//
//  Created by CGIS on 16/02/16.
//  Copyright © 2016 CGIS. All rights reserved.
//

#include <iostream>
#include "include\SDL.h"
#include "transform.h"

using namespace egc;

SDL_Renderer *windowRenderer;
// define rectangle vertices
vec3 P1(200, 100, 1), P2(200, 200, 1),P11(500,100,1),P22(500,200,1);


//define window dimensions
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

SDL_Window *window = NULL;
SDL_Event currentEvent;

SDL_Rect rectangleCoordinates = {100, 100, 200, 200};

bool quit = false;

int mouseX, mouseY;
void drawrectangle()
{
    SDL_RenderDrawLine(windowRenderer, P1.x, P1.y, P2.x, P2.y);
    SDL_RenderDrawLine(windowRenderer, P1.x, P1.y, P11.x, P11.y);
    SDL_RenderDrawLine(windowRenderer, P11.x, P11.y, P22.x, P22.y);
    SDL_RenderDrawLine(windowRenderer, P2.x, P2.y, P22.x, P22.y);
}
bool initWindow()
{
    bool success = true;
    
    //Try to initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL initialization failed" << std::endl;
        success = false;
    }
    else{
        //Try to create the window
        window = SDL_CreateWindow("SDL Hello World Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
        
        if(window == NULL)
        {
            std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
			// Create a renderer for the current window
			windowRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

			if(windowRenderer == NULL)
            {
                std::cout << "Failed to create the renderer: " << SDL_GetError() << std::endl;
                success = false;
            }
            else
            {
                //Set background color
				SDL_SetRenderDrawColor(windowRenderer, 255, 255, 255, 255);
			
                //Apply background color
                SDL_RenderClear(windowRenderer);
            }

        }
    }
    
    return success;
}

void destroyWindow()
{
    //Destroy window
    SDL_DestroyWindow(window);
    window = NULL;
    
    //Quit SDL
    SDL_Quit();
}
void rotaterectangle()
{
    mat3 m,t1,t2;
    m=rotate(10);
    vec2 aux;
    aux.x = (P1.x+P2.x+P11.x+P22.x)/4.0;
    aux.y = (P1.y + P2.y + P11.y + P22.y) / 4.0;
    t2 = translate(aux.x,aux.y);
    t1 = translate(-aux.x,-aux.y);

    P1 = t2 * m * t1 * P1;
    P2 = t2 * m * t1 * P2;
    P11 = t2 * m * t1 * P11;
    P22 = t2 * m * t1 * P22;
 

    printf("%lf %lf\n %lf %lf \n %lf %lf\n %lf %lf \n", P1.x, P1.y, P11.x, P11.y, P2.x, P2.y, P22.x, P22.y);
   
}
void irotaterectangle()
{
    mat3 m, t1, t2;
    m = rotate(-10);
    vec2 aux;
    aux.x = (P1.x + P2.x + P11.x + P22.x) / 4.0;
    aux.y = (P1.y + P2.y + P11.y + P22.y) / 4.0;
    t2 = translate(aux.x, aux.y);
    t1 = translate(-aux.x, -aux.y);

    P1 = t2 * m * t1 * P1;
    P2 = t2 * m * t1 * P2;
    P11 = t2 * m * t1 * P11;
    P22 = t2 * m * t1 * P22;

    printf("%lf %lf\n %lf %lf \n %lf %lf\n %lf %lf \n", P1.x, P1.y, P11.x, P11.y, P2.x, P2.y, P22.x, P22.y);

}

void scalerec()
{
    mat3 m;
    m = translate(P1.x,P1.y)  * scale(1.05,1.05) * translate(-P1.x,-P1.y);
    P1 = m * P1;
    P2 = m * P2;
    P11 = m * P11;
    P22 = m * P22;
    printf("%lf %lf\n %lf %lf \n %lf %lf\n %lf %lf \n", P1.x, P1.y, P11.x, P11.y, P2.x, P2.y, P22.x, P22.y);

}
void iscalerec()
{
    mat3 m;
    m = translate(P1.x, P1.y) * scale(1/1.05, 1/1.05) * translate(-P1.x, -P1.y);
    P1 = m * P1;
    P2 = m * P2;
    P11 = m * P11;
    P22 = m * P22;
    printf("%lf %lf\n %lf %lf \n %lf %lf\n %lf %lf \n", P1.x, P1.y, P11.x, P11.y, P2.x, P2.y, P22.x, P22.y);

}
int main(int argc, char * argv[]) {
    if(!initWindow())
    {
        std::cout << "Failed to initialize" << std::endl;
        return -1;
    }
    
    
    while (!quit) {
        //Handle events on queue
        if(SDL_WaitEvent(&currentEvent) != 0)
        {
            //User requests quit
            if(currentEvent.type == SDL_QUIT)
            {
                quit = true;
            }
            vec3 p(1.0f, 0.0f, 1.0f);
            mat3 t1 = translate(1.0f, 1.0f);
            mat3 t2 = translate(-1.0f, -1.0f);
            mat3 s = scale(2.0f, 2.0f);
            p = t2 * s * t1 * p;
            //Mouse event -> pressed button
            if(currentEvent.type == SDL_MOUSEBUTTONDOWN)
            {
                if(currentEvent.button.button == SDL_BUTTON_LEFT)
                {
                    SDL_GetMouseState(&mouseX, &mouseY);
                    std::cout << "Mouse click => " << "x: " << mouseX << ", y: " << mouseY << std::endl;
                }
            }
            
            //Mouse event -> mouse movement
            if(currentEvent.type == SDL_MOUSEMOTION)
            {
                if(currentEvent.button.button == SDL_BUTTON_LEFT)
                {
                    SDL_GetMouseState(&mouseX, &mouseY);
                    std::cout << "Mouse move => " << "x: " << mouseX << ", y: " << mouseY << std::endl;
                }
            }
            
            //Keyboard event
            if(currentEvent.type == SDL_KEYDOWN)
            {
                switch(currentEvent.key.keysym.sym)
                {
                    case SDLK_UP:
                        scalerec();
                        break;
                    case SDLK_DOWN:
                        iscalerec();
                        break;
                    case SDLK_r:                        
                        break;
                    case SDLK_RIGHT:
                        rotaterectangle();
                        break;
                    case SDLK_LEFT:
                        irotaterectangle();
                        break;
                    default:                        
                        break;
                }
            }
            
			
			SDL_SetRenderDrawColor(windowRenderer, 255, 255, 255, 255);
			SDL_RenderClear(windowRenderer);

			SDL_SetRenderDrawColor(windowRenderer, 0, 0, 255, 255);
            drawrectangle(); //dreptunghi cu coltul dreapta jos P22(400,200,1);
			
			SDL_RenderPresent(windowRenderer);
        }
    }
    
    destroyWindow();
    return 0;
}
