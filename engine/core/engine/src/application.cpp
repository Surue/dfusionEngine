#include "application.h"

namespace dfe {
Application::Application(const ApplicationInitSettings& initSettings)
    : _engine(initSettings.engineInitSettings) {}
void Application::Run() { _engine.Run(); }
}  // namespace dfe