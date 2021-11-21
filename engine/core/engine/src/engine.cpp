#include <engine.h>

#include <iostream>
#include <log.h>

namespace dfe {
Engine::Engine(EngineInitSettings initSettings) : _gameloop() {}
void Engine::Run() {
  _gameloop.Init();
  _coreSystemManager.Init();

  _gameloop.RegisterCoreSystem(_coreSystemManager);

  _gameloop.Update();
}
}  // namespace dfe