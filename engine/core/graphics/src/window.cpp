#include <window.h>

namespace dfe {
Window::Window(std::string_view windowName)
    : _windowName(windowName), _window(nullptr) {}

void Window::Init() {
  _window = SDL_CreateWindow(&_windowName.data()[0], SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE );
}

void Window::Destroy() { SDL_DestroyWindow(_window); }

SDL_Renderer* Window::CreateRenderer() {
  return SDL_CreateRenderer(_window, -1, SDL_RENDERER_SOFTWARE);
}
}  // namespace dfe