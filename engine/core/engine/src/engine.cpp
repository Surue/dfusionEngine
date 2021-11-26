#include <engine.h>

#include <iostream>
#include <log.h>

namespace dfe {
Engine::Engine(EngineInitSettings initSettings) : _gameloop() {}
void Engine::Run() {
  _gameloop.Init();
  _coreSystemManager.Init();

  _coreSystemManager.ProvideWindowQuitInputsListener(this);

  _gameloop.RegisterCoreSystem(_coreSystemManager);

  _gameloop.Update();

  Destroy();
}
void Engine::Stop() { _gameloop.Stop(); }
void Engine::Destroy() {
  _coreSystemManager.Destroy();
  _gameloop.Destroy();
}
std::function<void()> Engine::GetCallbackOnWindowQuitInputs() {
  return [&]() { Stop(); };
}
}  // namespace dfe