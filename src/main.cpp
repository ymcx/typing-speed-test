#include "src/logic.h"
#include "status.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>

using namespace ftxui;
using namespace std;

int main(int argc, char *argv[]) {
  (void)argc;

  string file = argv[1];
  int time = 3;
  Status status(file, time);
  renderi(status);
}
