#pragma once

#include <engine.h>

namespace dfe {
struct ApplicationInitSettings {
  EngineInitSettings engineInitSettings;
};

class Application {
 public:
  Application(const ApplicationInitSettings& initSettings);
  ~Application() = default;

  void Run();

 private:
  Engine _engine;
};
}  // namespace dfe