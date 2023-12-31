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

// Loads Individual image
SDL_Surface *loadSurface(std::string path);

void close();

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;
SDL_Surface *gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface *gCurrentSurface = NULL;

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
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      success = false;
    } else {
      gScreenSurface = SDL_GetWindowSurface(gWindow);
    }
  }

  return success;
}

bool loadMedia() {
  bool success = true;

  gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("../press.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
    printf("Failed to load default image!\n");
    success = false;
  }

  gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("../up.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL) {
    printf("Failed to load up image!\n");
    success = false;
  }

  gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("../down.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL) {
    printf("Failed to load down image!\n");
    success = false;
  }

  gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("../left.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL) {
    printf("Failed to load left image!\n");
    success = false;
  }

  gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("../right.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL) {
    printf("Failed to load right image!\n");
    success = false;
  }

  return success;
}

SDL_Surface *loadSurface(std::string path) {
    
  SDL_Surface* optimizedSurface = NULL;

  SDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str());
  if (loadedSurface == NULL) {
    printf("unable to laod image %s! SDL Error: %s\n", path.c_str(),
           SDL_GetError());
  } else {
      optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
      if (optimizedSurface == NULL) {
          printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
      }

      SDL_FreeSurface(loadedSurface);
  }
  return optimizedSurface;
}

void close() {
  for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++) {
    SDL_FreeSurface(gKeyPressSurfaces[i]);
    gKeyPressSurfaces[i] = NULL;
  }

  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  SDL_Quit();
}

int main(int argc, char *args[]) {
  if (!init())
    printf("Failed to init!\n");
  else {
    if (!loadMedia())
      printf("Failed to load media!\n");
    else {
      SDL_UpdateWindowSurface(gWindow);

      bool quit = false;
      SDL_Event e;

      gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

      while (!quit) {
        while (SDL_PollEvent(&e)) {
          if (e.type == SDL_QUIT)
            quit = true;

          else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
              case SDLK_UP:
                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
                break;

              case SDLK_DOWN:
                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                break;

              case SDLK_LEFT:
                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                break;

              case SDLK_RIGHT:
                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                break;

              default:
                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                break;
            }
          }

          SDL_Rect stretchRect;
          stretchRect.x = 0;
          stretchRect.y = 0;
          stretchRect.w = SCREEN_WIDTH / 2;
          stretchRect.h = SCREEN_HEIGHT / 2;
          SDL_BlitScaled(gCurrentSurface, NULL, gScreenSurface, &stretchRect);
          SDL_UpdateWindowSurface(gWindow);
        }
      }
    }
  }

  close();

  return 0;
}
