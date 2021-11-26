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

  SDL_Window* _window;
  std::string_view _windowName;
};
}  // namespace dfe