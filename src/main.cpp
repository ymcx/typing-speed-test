#include "elements.h"
#include "logic.h"
#include "src/misc.h"
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
  bool show_popup = false;

  string file = argv[1];
  vector<string> lines = read_lines(file);
  if (lines.size() == 0) {
    return 0;
  }

  shuffle_vector(lines);
  string typed = "";
  int time = 60;
  int time_left = time;
  int line = 0;
  char last_key = '\0';

  ScreenInteractive screen = ScreenInteractive::Fullscreen();

  int iteration = 1;
  auto pa = [&] {
    return play_again(lines, show_popup, line, typed, last_key, time_left,
                      iteration, time);
  };
  auto cl = [&] { return quit(screen); };

  Component buttons = popup_buttons(pa, cl);

  Component component = CatchEvent(
      Renderer([&] {
        if (show_popup) {
          int score = calculate_score(lines, line, typed, iteration, time);
          return popup(score, buttons);
        } else {
          return main_ui(lines, line, typed, time_left, last_key);
        }
      }),
      [&](Event event) {
        return handle_key(buttons, event, screen, lines[line], show_popup,
                          typed, last_key, line, lines.size(), iteration);
      });

  thread refresh_ui([&] {
    while (true) {
      while (!show_popup) {
        this_thread::sleep_for(1.00s);
        if (!decrease_time(time_left)) {
          show_popup = true;
        }
        screen.Post(Event::Custom);
      }
      this_thread::sleep_for(1.00s);
    }
  });

  screen.Loop(component);
  refresh_ui.join();
}
