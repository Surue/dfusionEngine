#include "gameloop.h"

#include <log.h>

#include <chrono>
#include <string>

namespace dfe {
Gameloop::Gameloop() {}
void Gameloop::Init() {}
void Gameloop::Update() {
  _isRunning = true;

  auto startChrono = std::chrono::system_clock::now();

  while (_isRunning) {
    auto startFrame = std::chrono::system_clock::now();
    // Update

    while (std::chrono::duration<double>(std::chrono::system_clock::now() -
                                         startFrame)
               .count() < std::chrono::duration<double>(0.02f).count()) {
    }

    auto time = std::chrono::duration<double>(std::chrono::system_clock::now() -
                                              startChrono)
                    .count();

    Debug::Log(std::to_string(time));

    if (time > 10) {
      _isRunning = false;
    }
  }
}
void Gameloop::Destroy() {}
}  // namespace dfe