//
//  main.cpp
//  SDL_Lab1
//
//  Created by CGIS on 16/02/16.
//  Copyright © 2016 CGIS. All rights reserved.
//

#include <iostream>
#include "include\SDL.h"
#include "stdafx.h"
#include <algorithm>
 
//define window dimensions
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

SDL_Window *window = NULL;
SDL_Surface *windowSurface = NULL;
SDL_Event currentEvent;

SDL_Rect rectangleCoordinates = {220, 90, 150, 150};
Uint32 rectagleColor;

bool quit = false;

int mouseX, mouseY;

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
            //Try to get the window surface
            windowSurface = SDL_GetWindowSurface(window);
            
            if(windowSurface == NULL)
            {
                std::cout << "Failed to get the window surface: " << SDL_GetError() << std::endl;
                success = false;
            }
            else
            {
                //Initialize surface color
                SDL_FillRect(windowSurface, NULL, SDL_MapRGB(windowSurface->format, 255, 255, 255));
                
                //Update the surface
                SDL_UpdateWindowSurface(window);
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
enum color  { RED = 1,GREEN = 2,BLUE = 3 };
int main(int argc, char * argv[]) {
    Uint32 red = 0;
    Uint32 green = 0;
    Uint32 blue = 0;
    int currentcolor[4] = { 0,0,0 };
    color ccol = RED;
    int  my=0;
    int  mx=0;
    if(!initWindow())
    {
        std::cout << "Failed to initialize" << std::endl;
        return -1;
    }
    
    rectagleColor = SDL_MapRGB(windowSurface->format, 0, 0, 255);
    
    while (!quit) {
        //Handle events on queue
        if(SDL_WaitEvent(&currentEvent) != 0)
        {
            //User requests quit
            if(currentEvent.type == SDL_QUIT)
            {
                quit = true;
            }
            
            //Mouse event -> pressed button
            if(currentEvent.type == SDL_MOUSEBUTTONDOWN)
            {
                if(currentEvent.button.button == SDL_BUTTON_LEFT)
                {
                    SDL_GetMouseState(&mouseX, &mouseY);
                    rectangleCoordinates = { mouseX, mouseY, 0, 0 }; 
                    rectagleColor = SDL_MapRGB(windowSurface->format,0, 0, 255);
                    SDL_FillRect(windowSurface, &rectangleCoordinates, rectagleColor);

                    std::cout << "Mouse click => " << "x: " << mouseX << ", y: " << mouseY << std::endl;
                }
            }
            
            //Mouse event -> mouse movement
            if(currentEvent.type == SDL_MOUSEMOTION)
            {
                if(currentEvent.button.button == SDL_BUTTON_LEFT)
                {
                  
                  SDL_GetMouseState(&mx, &my);
                  int mx2 = (int)fmin(mouseX, mx);
                  int my2 = (int)fmin(mouseY, my);
                  rectangleCoordinates = { mx2 ,my2 ,abs(mx2-mx),abs(my2-my) };
              
                  rectagleColor = SDL_MapRGB(windowSurface->format, 0, 0, 255);
                  SDL_FillRect(windowSurface, &rectangleCoordinates, rectagleColor);
                  std::cout << "Mouse move => " << "x: " << mouseX << ", y: " << mouseY << std::endl;
                }
  
            }
            
            //Keyboard event
            if(currentEvent.type == SDL_KEYDOWN)
            {
                switch(currentEvent.key.keysym.sym)
                {

                    case SDLK_UP:
                        if (currentcolor[ccol] > 255)
                            currentcolor[ccol] = 0;
                        currentcolor[ccol]++;
                        break;
                        
                    case SDLK_DOWN:
                        if(currentcolor[ccol]<0)
                            currentcolor[ccol]=255;
                        currentcolor[ccol]--;
                        break;
                    case SDLK_r:
                        ccol = RED;
                        
                        break;
                    case SDLK_g:
                        ccol = GREEN;
                       
                        break;
                    case SDLK_b:
                        ccol = BLUE;
                        
                        break;
                    case SDLK_c:
                        rectangleCoordinates = { SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480 };
                        rectagleColor = SDL_MapRGB(windowSurface->format, 255,255, 255);
                     
                        break;
                    default:
                        //rectagleColor = SDL_MapRGB(windowSurface->format, 31, 34, 42);
                        break;

                }
                
            }  
            rectangleCoordinates = { 220, 90, 150, 150 };
            rectagleColor = SDL_MapRGB(windowSurface->format, currentcolor[1],currentcolor[2],currentcolor[3]);
            SDL_FillRect(windowSurface, &rectangleCoordinates, rectagleColor);
            SDL_UpdateWindowSurface(window);
        }
    }
    
    destroyWindow();
    return 0;
}
