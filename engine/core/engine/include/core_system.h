#pragma once

namespace dfe {
class IInputeUpdatable {
 public:
  virtual void UpdateInputs() = 0;
};

class IUpdatable {
 public:
  virtual void Update() = 0;
};

class IDrawable {
 public:
  virtual void Draw() = 0;
};

class IRenderable {
 public:
  virtual void Render() = 0;
};
}  // namespace dfe