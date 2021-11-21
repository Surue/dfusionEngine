#include <gameloop.h>
#include <core_system_manager.h>
#include <inputs.h>
#include <log.h>

#include <chrono>
#include <string>
#include <thread>
#include <vector>

namespace dfe {
Gameloop::Gameloop() : _elapsedTime(0), _isRunning(false), _deltaTime(0.0) {}
void Gameloop::RegisterCoreSystem(const CoreSystemManager& coreSystemManager) {
  auto updatables = coreSystemManager.GetUpdatables();
  for (int i = 0; i < updatables.size(); i++) {
    _updatables.push_back(updatables[i]);
  }

  auto inputUpdatables = coreSystemManager.GetInputUpdatables();
  for (int i = 0; i < inputUpdatables.size(); i++) {
    _inputsUpdatables.push_back(inputUpdatables[i]);
  }

  auto rendarable = coreSystemManager.GetRenderable();
  for (int i = 0; i < rendarable.size(); i++) {
    _renderables.push_back(rendarable[i]);
  }
}
void Gameloop::Init() {}
void Gameloop::Update() {
  _isRunning = true;

  auto startChrono = std::chrono::high_resolution_clock::now();
  std::chrono::high_resolution_clock::time_point startFrame;

  while (_isRunning) {
    // Time start frame
    startFrame = std::chrono::high_resolution_clock::now();

    // Update inputs
    for (size_t i = 0; i < _inputsUpdatables.size(); i++) {
      _inputsUpdatables[i]->UpdateInputs();
    }

    // Update

    // Draw

    // Render
    for (size_t i = 0; i < _renderables.size(); i++) {
      _renderables[i]->Render();
    }

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