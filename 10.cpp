#include <SDL.h>
#include <SDL_image.h>

#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;

class LTexture {
    public:
        LTexture();
        ~LTexture();

        bool loadFromFile(std::string path);

        void free();

        void render(int x, int y);

        int getWidth();
        int getHeight();

    private:
        SDL_Texture* mTexture;
        int mWidth;
        int mHeight;
};

bool init();

bool loadMedia();

SDL_Texture *loadTexture(std::string path);

void close();

// window
SDL_Window *gWindow = NULL;

// window renderer
SDL_Renderer *gRenderer = NULL;

// texture
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

bool loadMedia() {
    bool success = true;

    gTexture = loadTexture("../viewport.png");
    if (gTexture == NULL) {
        success = true;
    }

    return success;
}

SDL_Texture *loadTexture(std::string path){
    SDL_Texture *newTexture = IMG_LoadTexture(gRenderer, path.c_str());
    if (newTexture == NULL) {
        printf("Unable to load texture from %s! SDL Error: %s\n",
               path.c_str(), IMG_GetError());
    }

    return newTexture;
}

void close() {
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    SDL_Quit();
    IMG_Quit();
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

                // top left corner viewport
                SDL_Rect topLeftViewport;
                topLeftViewport.x = 0;
                topLeftViewport.y = 0;
                topLeftViewport.w = SCREEN_WIDTH / 2;
                topLeftViewport.h = SCREEN_HEIGHT / 2;
                SDL_RenderSetViewport(gRenderer, &topLeftViewport);

                // Render texture to screen
                SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

                // top right corner viewport
                SDL_Rect topRightViewport;
                topRightViewport.x = SCREEN_WIDTH / 2;
                topRightViewport.y = 0;
                topRightViewport.w = SCREEN_WIDTH / 2;
                topRightViewport.h = SCREEN_HEIGHT / 2;
                SDL_RenderSetViewport(gRenderer, &topRightViewport);

                // Render texture to screen
                SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

                                //Bottom viewport
                SDL_Rect bottomViewport;
                bottomViewport.x = 0;
                bottomViewport.y = SCREEN_HEIGHT / 2;
                bottomViewport.w = SCREEN_WIDTH;
                bottomViewport.h = SCREEN_HEIGHT / 2;
                SDL_RenderSetViewport( gRenderer, &bottomViewport );
                
                //Render texture to screen
                SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

                //Update screen
                SDL_RenderPresent(gRenderer);
            }
        }
    }

    close();

    return 0;
}
