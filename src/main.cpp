#include "src/logic.h"
#include "src/status.h"
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
  (void)argc;

  string file = argv[1];
  int time = 3;
  Status status(file, time);
  render(status);
}
