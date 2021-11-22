#pragma once
#include <core_system.h>

#include <vector>

namespace dfe {
// Prototypes
class CoreSystemManager;
// Prototypes

struct GameloopInitSettings {
  float updateTime = 0.2f;
};

class Gameloop {
 public:
  Gameloop();
  ~Gameloop() = default;

  void RegisterCoreSystem(const CoreSystemManager& coreSystemManager);
  void Init();
  void Update();
  void Destroy();

 private:
  bool _isRunning;
  double _elapsedTime;
  double _deltaTime;

  std::vector<IUpdatable*> _updatables;
  std::vector<IInputeUpdatable*> _inputsUpdatables;
  std::vector<IDrawable*> _drawables;
  std::vector<IRenderable*> _renderables;
};
}  // namespace dfe