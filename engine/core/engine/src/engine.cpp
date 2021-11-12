#include "engine.h"

#include <iostream>
#include <log.h>

namespace dfe {
Engine::Engine(EngineInitSettings initSettings) : _gameloop() {
  Debug::Log("Init Engine");
  Debug::LogWarning("Warning");
}
inline void Engine::Run() {
  _gameloop.Init();
  _gameloop.Update();
}
}  // namespace dfe