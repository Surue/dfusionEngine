#include "engine.h"

#include <iostream>
#include <log.h>

namespace dfe {
Engine::Engine(EngineInitSettings initSettings) : _gameloop() { }
void Engine::Run() {
  _gameloop.Init();
  _graphicsEngine.Init();

  _gameloop.Update(&_graphicsEngine);
}
}  // namespace dfe