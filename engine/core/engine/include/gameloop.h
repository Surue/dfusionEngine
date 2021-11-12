#pragma once

namespace dfe {
struct GameloopInitSettings {
  float updateTime = 0.2f;
};

class Gameloop {
 public:
  Gameloop();
  ~Gameloop() = default;
  void Init();
  void Update();
  void Destroy();

 private:
  bool _isRunning;
};
}  // namespace dfe