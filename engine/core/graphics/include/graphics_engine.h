#pragma once

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include <core_system.h>

namespace dfe {
class GraphicsEngine: public IRenderable {
 public:
  GraphicsEngine() = default;

  void Init() {
    SDL_Init(SDL_INIT_VIDEO);

    _window = SDL_CreateWindow("SDL2Test", SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_SOFTWARE);
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(_renderer);
    SDL_RenderPresent(_renderer);
  }

  void Render() {
    static int tmp = 0;
    tmp++;

    if (tmp == 1000) {
      SDL_DestroyRenderer(_renderer);
      SDL_DestroyWindow(_window);
      SDL_Quit();
    }
  }

 private:
  SDL_Window *_window;
  SDL_Renderer *_renderer;
};
}  // namespace dfe