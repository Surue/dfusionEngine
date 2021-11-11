#pragma once

namespace dfe {
struct EngineInitSettings {

};

class Engine {
 public:
  Engine(EngineInitSettings initSettings);
  ~Engine() = default;

 private:
  int _value = 10;
  bool _myBool;
};
}  // namespace dfe