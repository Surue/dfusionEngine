#include <SDL_vulkan.h>
#include <log.h>
#include <window.h>

namespace dfe {
Window::Window(std::string_view windowName, const int width, const int height)
    : _windowName(windowName),
      _window(nullptr),
      _width(width),
      _height(height) {
  _window = SDL_CreateWindow(
      &_windowName.data()[0], SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      _width, _height,
      SDL_WINDOW_VULKAN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE);
}

void Window::Init() {
  
}

void Window::Destroy() { SDL_DestroyWindow(_window); }

SDL_Renderer* Window::CreateRenderer() {
  return SDL_CreateRenderer(_window, -1, SDL_RENDERER_SOFTWARE);
}

std::vector<const char*> Window::GetVulkanExtensions() const {
  uint32_t extensionCount = 0;
  if (!SDL_Vulkan_GetInstanceExtensions(_window, &extensionCount, nullptr)) {
    Debug::LogError("Could not SDL Vulkan Extensions correctly");
  }

  std::vector<const char*> extensions;
  if (!SDL_Vulkan_GetInstanceExtensions(_window, &extensionCount,
                                        extensions.data())) {
    Debug::LogError("Could not SDL Vulkan Extensions correctly");
  }

  return extensions;
}
}  // namespace dfe