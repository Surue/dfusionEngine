#pragma once

#include <SDL.h>
#include <inputs.h>

#include <functional>
#include <string>

namespace dfe {
class Window : public IWindowInputs {
 public:
  Window(std::string_view windowName, const int width = 720,
         const int height = 640);
  ~Window() = default;

  void Init();

  void Destroy();

  SDL_Renderer* CreateRenderer();

  const SDL_Window& GetWindow() const { return *_window; }

  std::function<void()> GetCallbackOnWindowsResized() {
    return [&]() { OnWindowResize(); };
  }

  std::function<void()> GetCallbackOnWindowsMinimized() {
    return [&]() { OnWindowMinimized(); };
  }

  std::function<void()> GetCallbackOnWindowsMaximized() {
    return [&]() { OnWindowMaximized(); };
  }

  std::function<void()> GetCallbackOnWindowsRestored() {
    return [&]() { OnWindowRestored(); };
  }

 private:
  void OnWindowResize() const {}
  void OnWindowMinimized() const {}
  void OnWindowMaximized() const {}
  void OnWindowRestored() const {}

  const int _width;
  const int _height;

  SDL_Window* _window;
  std::string_view _windowName;
};
}  // namespace dfe