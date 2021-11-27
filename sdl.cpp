#include <SDL.h>
#include <stdio.h>
#include "sdl.h"
#include <iostream>
using namespace std;


//SDL_Surface* old_screen = NULL;
SDL_Surface* old_screen = SDL_CreateRGBSurface(0, RESX, RESY, 32,
	0x00FF0000,
	0x0000FF00,
	0x000000FF,
	0xFF000000);


SDL_Window* screen;
SDL_Renderer* renderer;


/// try to create a frame window with the given dimensions
bool initGraphics(int frameWidth, int frameHeight)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Cannot initialize SDL: %s\n", SDL_GetError());
		return false;
	}
	//screen = SDL_SetVideoMode(frameWidth, frameHeight, 32, 0);
	//screen = SDL_CreateWindow("My VFB Window",
 //                               SDL_WINDOWPOS_UNDEFINED,
 //                               SDL_WINDOWPOS_UNDEFINED,
 //                               frameWidth, frameHeight,
 //                               SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	
    SDL_CreateWindowAndRenderer(frameWidth, frameHeight, SDL_WINDOW_SHOWN, &screen, &renderer );
	SDL_SetWindowTitle(screen, "My VFB");



	if (!screen) {
		printf("Cannot set video mode %dx%d - %s\n", frameWidth, frameHeight, SDL_GetError());
		return false;
	}
	return true;
}

/// closes SDL graphics
void closeGraphics(void)
{
	SDL_Quit();
}

 //displays a VFB (virtual frame buffer) to the real framebuffer, with the necessary color clipping
void displayVFB(Color vfb[VFB_MAX_SIZE][VFB_MAX_SIZE])
{

	int rs = old_screen->format->Rshift;
	int gs = old_screen->format->Gshift;
	int bs = old_screen->format->Bshift;
	for (int y = 0; y < old_screen->h; y++) {
		Uint32 *row = (Uint32*) ((Uint8*)old_screen->pixels + y * old_screen->pitch);
		for (int x = 0; x < old_screen->w; x++)
			row[x] = vfb[y][x].toRGB32(rs, gs, bs);
	}

	SDL_Texture* sdlTexture = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		640, 480);

	SDL_UpdateTexture(sdlTexture, NULL, old_screen->pixels, old_screen->pitch);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, sdlTexture, NULL, NULL);
	SDL_RenderPresent(renderer);

	//SDL_Flip(old_screen);
}


/// waits the user to indicate he wants to close the application (by either clicking on the "X" of the window,
/// or by pressing ESC)
void waitForUserExit(void)
{
	SDL_Event ev;
	while (1) {
		while (SDL_WaitEvent(&ev)) {
			switch (ev.type) {
				case SDL_QUIT:
					return;
				case SDL_KEYDOWN:
				{
					switch (ev.key.keysym.sym) {
						case SDLK_ESCAPE:
							return;
						default:
							break;
					}
				}
				default:
					break;
			}
		}
	}
}


// returns the frame width
int frameWidth(void)
{
	if (screen) return SDL_GetWindowSurface(screen)->w;
	return 0;
}

//int frameHeight(void)
int frameHeight(void)
{
	if (screen) return SDL_GetWindowSurface(screen)->h;
	return 0;
}



//int main(int argv, char** args)
//{
//    initGraphics(200, 400);
//    cout << "Hello World!";
//    cout << "I am learning C++";
//    cout << "\n" << frameWidth() << " " << frameHeight() << "\n";
//    return 0;
//}
