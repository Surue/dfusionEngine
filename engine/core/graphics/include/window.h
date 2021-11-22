#pragma once

#include <inputs.h>

#include <string>
#include <functional>

#include <SDL.h>

namespace dfe {
class Window : public IWindowInputs {
 public:
  Window(std::string_view windowName);
  ~Window() = default;

  void Init();

  void Destroy();

  SDL_Renderer* CreateRenderer();

  const SDL_Window& GetWindow() const { return *_window; }

  std::function<void()> GetCallbackOnWindowsResized() const {
    return [&]() { OnWindowResize(); };
  }

  std::function<void()> GetCallbackOnWindowsMinimized() const {
    return [&]() { OnWindowMinimized(); };
  }

  std::function<void()> GetCallbackOnWindowsMaximized() const {
    return [&]() { OnWindowMaximized(); };
  }

  std::function<void()> GetCallbackOnWindowsRestored() const {
    return [&]() { OnWindowRestored(); };
  }

 private:
  void OnWindowResize() const {}
  void OnWindowMinimized() const {}
  void OnWindowMaximized() const {}
  void OnWindowRestored() const {}

  SDL_Window* _window;
  std::string_view _windowName;
};
}  // namespace dfe