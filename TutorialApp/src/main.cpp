#include <Engine.h>

int main() {
  Engine e;
  if (!e.initialize("demo", 800, 600))
    return -1;

  e.run();

  return 0;
}
