#include "application.h"

namespace dfe {
Application::Application(const ApplicationInitSettings& initSettings)
    : _engine(initSettings.engineInitSettings) {}
}  // namespace dfe