#include <inputs.h>

#include <SDL.h>

namespace dfe {
Inputs::Inputs() {
  _keysSatus.resize(static_cast<int>(KeyCode::KEYBOARD_SIZE),
                    ButtonStatus::NONE);
}

void Inputs::Init() {}

bool Inputs::IsKeyDown(KeyCode key) {
  return _keysSatus[static_cast<int>(key)] == ButtonStatus::DOWN;
}
bool Inputs::IsKeyHeld(KeyCode key) {
  return _keysSatus[static_cast<int>(key)] == ButtonStatus::HELD;
}
bool Inputs::IsKeyUp(KeyCode key) {
  return _keysSatus[static_cast<int>(key)] == ButtonStatus::UP;
}
void Inputs::UpdateInputs() {
  // Update keys's status
  for (int i = 0; i < static_cast<int>(KeyCode::KEYBOARD_SIZE); i++) {
    if (_keysSatus[i] == ButtonStatus::DOWN) {
      _keysSatus[i] = ButtonStatus::HELD;
    }

    if (_keysSatus[i] == ButtonStatus::UP) {
      _keysSatus[i] = ButtonStatus::NONE;
    }
  }

  // Check for new event
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_KEYDOWN:
        _keysSatus[static_cast<int>(event.key.keysym.scancode)] =
            ButtonStatus::DOWN;
        break;
      case SDL_KEYUP:
        _keysSatus[static_cast<int>(event.key.keysym.scancode)] =
            ButtonStatus::UP;
        break;
      case SDL_MOUSEBUTTONDOWN:
        break;
      case SDL_MOUSEBUTTONUP:
        break;
      case SDL_MOUSEMOTION:
        break;
      case SDL_MOUSEWHEEL:
        break;
      case SDL_WINDOWEVENT:
        if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
          _callbackOnWindowResized();
        }

        if (event.window.event == SDL_WINDOWEVENT_MINIMIZED) {
          // Minimize windows
        }

        if (event.window.event == SDL_WINDOWEVENT_MAXIMIZED) {
          // Maximize windows
        }

        if (event.window.event == SDL_WINDOWEVENT_RESTORED) {
          // Restore windows
        }
        break;
      case SDL_QUIT:
        break;
    }
  }
}
void Inputs::ProvideWindowInputsListener(const IWindowInputs& windowsInput) {
  _callbackOnWindowResized = windowsInput.GetCallbackOnWindowsResized();
  _callbackOnWindowMinimized = windowsInput.GetCallbackOnWindowsMinimized();
  _callbackOnWindowMaximized = windowsInput.GetCallbackOnWindowsMaximized();
  _callbackOnWindowRestored = windowsInput.GetCallbackOnWindowsRestored();
}
}  // namespace dfe