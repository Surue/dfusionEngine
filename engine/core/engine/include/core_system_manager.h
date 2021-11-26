#pragma once
#include <inputs.h>
#include <core_system.h>
#include <graphics_engine.h>

namespace dfe {

class CoreSystemManager {
 public:
  CoreSystemManager() = default;
  ~CoreSystemManager() = default;

  void Init();
  
  void Destroy() {
      
  }

  std::vector<IUpdatable*> GetUpdatables() const;

  std::vector<IInputeUpdatable*> GetInputUpdatables() const;

  std::vector<IRenderable*> GetRenderable() const;

  void ProvideWindowQuitInputsListener(IQuitInputs* quitInput);

 private:
  Inputs _inputs;
  GraphicsEngine _graphicsEngine;
};
}  // namespace dfe