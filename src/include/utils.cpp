#include "SDL2/SDL.h"


int setup_display() {



	SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Texture *texture;
        SDL_Event event;

        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, ": Error initializing video subsystem of SDL%s", SDL_GetError());
                return -1;
        }

        window = SDL_CreateWindow("SDL_CreateTexture",
                        SDL_WINDOWPOS_UNDEFINED,
                        SDL_WINDOWPOS_UNDEFINED,
                        1024, 512,
                        SDL_WINDOW_RESIZABLE);


        renderer = SDL_CreateRenderer(window, -1, 0);
        texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 64, 32);


        uint32_t pixels[64*32];




        while (1) {
                SDL_PollEvent(&event);
                if(event.type == SDL_QUIT)
                        break;
                int i = 0;



                while(i <2048) {
                        if(((i/64) + (i%64))%2) {

                                pixels[i] = 0xFFFFFFFF;


                        }
                        else {

                                pixels[i] = 0x00000000;
                        }

                        i++;
                }

                SDL_UpdateTexture(texture,
                                NULL,
                                pixels,
                                sizeof(Uint32)*64);
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, texture, NULL, NULL);
                SDL_RenderPresent(renderer);
                SDL_Delay(10000);


        }
        SDL_DestroyRenderer(renderer);
        SDL_Quit();




}

int setup_keyboard() {




}

int update_display() {





}

