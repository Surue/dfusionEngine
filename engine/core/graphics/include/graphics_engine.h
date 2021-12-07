#pragma once

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <core_system.h>
#include <window.h>
#include <pipeline.h>
#include <devices/instance.h>

#include <string_view>

namespace dfe {

class GraphicsEngine : public IRenderable {
 public:
  GraphicsEngine(std::string_view windowName = "dFusionEngine")
      : _window(windowName), _instance(_window), _renderer(nullptr) {}

  void Init() {
    SDL_Init(SDL_INIT_VIDEO);

    _window.Init();

    _renderer = _window.CreateRenderer();
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(_renderer);
    SDL_RenderPresent(_renderer);
  }

  void Render() {
    static int tmp = 0;
    tmp++;

    if (tmp == 1000) {
      SDL_DestroyRenderer(_renderer);
      _window.Destroy();
      SDL_Quit();
    }
  }

  IWindowInputs& GetWindowInputs() { return _window; }

 private:
  Window _window;
  SDL_Renderer *_renderer;

  Pipeline _pipeline{"../resources/shaders/default.vert", "../resources/shaders/default.frag"};

  // Vulkan specific
  graphics::Instance _instance;
};
}  // namespace dfe