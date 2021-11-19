#include <gameloop.h>
#include <log.h>

#include <chrono>
#include <string>
#include <thread>
#include <vector>

namespace dfe {
Gameloop::Gameloop() : _elapsedTime(0), _isRunning(false), _deltaTime(0.0) {}
void Gameloop::Init() {}
void Gameloop::Update(GraphicsEngine* graphicsEnigne, Inputs* inputs) {
  _isRunning = true;

  _graphicsEngine = graphicsEnigne;
  _inputs = inputs;

  auto startChrono = std::chrono::high_resolution_clock::now();
  std::chrono::high_resolution_clock::time_point startFrame;
  
  while (_isRunning) {
    // Time start frame
    startFrame = std::chrono::high_resolution_clock::now();

    // Update inputs
    _inputs->Update();

    // TODO Update
    if (_inputs->IsKeyDown(KeyCode::A)) {
      Debug::Log("Key A is Down");
    }

    if (_inputs->IsKeyHeld(KeyCode::A)) {
      Debug::Log("Key A is Held");
    }

    if (_inputs->IsKeyUp(KeyCode::A)) {
      Debug::Log("Key A is Up");
    }

    // Render
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