#include <iostream>
#include "lib.h"
#include "Config.h"

int main() {
  std::cout << greet("World") << "\n"
            << "Version: "
            << MyProject_VERSION_MAJOR << "."
            << MyProject_VERSION_MINOR << "."
            << MyProject_VERSION_PATCH
            << std::endl;
  return 0;
}
