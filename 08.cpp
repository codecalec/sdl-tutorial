#include <SDL.h>
#include <stdio.h>

#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

enum KeyPressSurfaces {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

bool init();

bool loadMedia();

void close();

// window
SDL_Window *gWindow = NULL;

// window renderer
SDL_Renderer *gRenderer = NULL;

bool init() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    } else {
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                   SCREEN_HEIGHT, 0);

        if (gWindow == NULL) {
            printf("Window could not be created! SDL_Error: %s\n",
                   SDL_GetError());
            success = false;
        } else {
            gRenderer =
                SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

            if (gRenderer == NULL) {
                printf("Renderer could not be created. SDL Error: %s\n",
                       SDL_GetError());
                success = false;
            }
        }
    }

    return success;
}

bool loadMedia() {
    bool success = true;

    return success;
}

void close() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    SDL_Quit();
}

int main() {
    if (!init())
        printf("Failed to init!\n");
    else {
        if (!loadMedia())
            printf("Failed to load media!\n");
        else {
            bool quit = false;
            SDL_Event e;

            while (!quit) {
                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) quit = true;
                }

                // clear screen
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);

                // render red filled quad
                SDL_Rect fillRect = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4,
                                     SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
                SDL_RenderFillRect(gRenderer, &fillRect);

                // render green outlined quad
                SDL_Rect outlineRect = {SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6,
                                        SCREEN_WIDTH * 2 / 3,
                                        SCREEN_HEIGHT * 2 / 3};
                SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
                SDL_RenderDrawRect(gRenderer, &outlineRect);

                // render blue line
                SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
                SDL_RenderDrawLine(gRenderer, 0, SCREEN_HEIGHT / 2,
                                   SCREEN_WIDTH, SCREEN_HEIGHT / 2);

                // render yellow dots
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
                for (int i = 0; i < SCREEN_HEIGHT; i += 4) {
                    SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH / 2, i);
                }

                for (float i = 0; i < 1; i += 0.1) {
                    SDL_RenderDrawPoint(gRenderer, int(i * SCREEN_WIDTH),
                                        int(i * SCREEN_HEIGHT));
                }

                SDL_RenderPresent(gRenderer);
            }
        }
    }

    close();

    return 0;
}
