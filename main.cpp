#include <iostream>

#include <application.h>

int main() {
  dfe::ApplicationInitSettings initSettings{};
  dfe::Application app(initSettings);

  app.Run();

  return EXIT_SUCCESS;
}