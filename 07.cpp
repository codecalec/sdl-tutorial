#include <SDL.h>
#include <SDL_image.h>
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

// Loads Individual image as texture
SDL_Texture *loadTexture(std::string path);

void close();

// window
SDL_Window *gWindow = NULL;

// window renderer
SDL_Renderer *gRenderer = NULL;

// current texture
SDL_Texture *gTexture = NULL;

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
            } else {
                // init renderer colour
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // init PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    printf("SDL_image could not init! SDL_image Error: %s\n",
                           IMG_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}

SDL_Texture *loadTexture(std::string path) {
    SDL_Texture *newTexture = NULL;

    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to laod image %s! SDL_image Error: %s\n", path.c_str(),
               IMG_GetError());
    } else {
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n",
                   path.c_str(), SDL_GetError());
        }

        // free old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

bool loadMedia() {
    bool success = true;
    gTexture = loadTexture("../texture.png");
    if (gTexture == NULL) {
        success = true;
    }
    return success;
}

void close() {
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char *args[]) {
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
                SDL_RenderClear(gRenderer);

                // render texture to screen
                SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

                // update screen
                SDL_RenderPresent(gRenderer);
            }
        }
    }

    close();

    return 0;
}
