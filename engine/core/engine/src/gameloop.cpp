#include "gameloop.h"

#include <log.h>

#include <chrono>
#include <string>
#include <thread>

namespace dfe {
Gameloop::Gameloop() : _elapsedTime(0), _isRunning(false) {}
void Gameloop::Init() {}
void Gameloop::Update() {
  _isRunning = true;

  auto startChrono = std::chrono::system_clock::now();
  std::chrono::system_clock::time_point startFrame;
  while (_isRunning) {
    startFrame = std::chrono::system_clock::now();
    // Update

    Debug::Log(std::to_string(_elapsedTime));

    // Wait time
    //auto t = std::chrono::duration<double>(std ::chrono::system_clock::now() - startFrame).count();
    auto sleepDuration = std::chrono::duration<double>(
        0.02 - std::chrono::duration<double>(std ::chrono::system_clock::now() -
                                             startFrame)
                   .count());

    std::this_thread::sleep_for(sleepDuration);

    // Update timers
    _deltaTime = std::chrono::duration<double>(
                     std::chrono::system_clock::now() - startFrame)
                     .count();

    _elapsedTime += _deltaTime;
  }
}
void Gameloop::Destroy() {}
}  // namespace dfe