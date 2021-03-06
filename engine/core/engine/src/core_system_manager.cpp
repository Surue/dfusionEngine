#include <core_system_manager.h>

namespace dfe {
void CoreSystemManager::Init() {
  _inputs.Init();
  _graphicsEngine.Init();

  _inputs.ProvideWindowInputsListener(&_graphicsEngine.GetWindowInputs());
}

std::vector<IUpdatable*> CoreSystemManager::GetUpdatables() const {
  return std::vector<IUpdatable*>{};
}

std::vector<IInputeUpdatable*> CoreSystemManager::GetInputUpdatables() const {
  return std::vector<IInputeUpdatable*>{
      (IInputeUpdatable*)(&_inputs)};  // TODO What's the casting?
}

std::vector<IRenderable*> CoreSystemManager::GetRenderable() const {
  return std::vector<IRenderable*>{
      (IRenderable*)(&_graphicsEngine)};  // TODO What's the casting?
}
void CoreSystemManager::ProvideWindowQuitInputsListener(
    IQuitInputs* quitInput) {
  _inputs.ProvideWindowQuitInputsListener(quitInput);
}
}  // namespace dfe