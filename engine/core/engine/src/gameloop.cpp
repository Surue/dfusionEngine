#include <gameloop.h>
#include <log.h>

#include <chrono>
#include <string>
#include <thread>
#include <vector>

namespace dfe {
Gameloop::Gameloop() : _elapsedTime(0), _isRunning(false), _deltaTime(0.0) {}
void Gameloop::Init() {}
void Gameloop::Update(GraphicsEngine* graphicsEnigne) {
  _isRunning = true;

  _graphicsEngine = graphicsEnigne;

  auto startChrono = std::chrono::high_resolution_clock::now();
  std::chrono::high_resolution_clock::time_point startFrame;
  
  while (_isRunning) {
    // Time start frame
    startFrame = std::chrono::high_resolution_clock::now();

    // Update
    // TODO Inputs

    // TODO Update

    // TODO Render
    _graphicsEngine->Render();

    // Wait time
    while (std::chrono::duration<double>(
               std::chrono::high_resolution_clock::now() - startFrame)
               .count() < 0.02) {
    }

    // Update timers
    _deltaTime = std::chrono::duration<double>(
                     std::chrono::high_resolution_clock::now() - startFrame)
                     .count();

    _elapsedTime += _deltaTime;
  }
}
void Gameloop::Destroy() {}
}  // namespace dfe