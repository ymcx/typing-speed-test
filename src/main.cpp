#include "elements.h"
#include "logic.h"
#include "src/misc.h"
#include "stats.h"
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
  int time = 10;
  vector<string> lines = read_lines(file);
  shuffle(lines);
  Stats stats(time);

  ScreenInteractive screen = ScreenInteractive::Fullscreen();
  Component popup_buttonsa = popup_buttons(stats, screen);

  Component component =
      CatchEvent(Renderer([&] {
                   if (stats.show_popup) {
                     return popup(stats.calculate_score(lines), popup_buttonsa);
                   } else {
                     return main_ui(lines, stats.line, stats.typed_text,
                                    stats.timeleft, stats.last_key);
                   }
                 }),
                 [&](Event event) {
                   return handle_key(stats, popup_buttonsa, event, screen, lines[stats.line]);
                 });

  atomic<bool> refresh_ui_continue = true;
  thread refresh_ui([&] {
    while (refresh_ui_continue) {
      this_thread::sleep_for(1.00s);
      if (!decrease_time(&stats)) {
        refresh_ui_continue = false;
        stats.show_popup = true;
      }
      screen.Post(Event::Custom);
    }
  });

  screen.Loop(component);
  refresh_ui_continue = false;
  refresh_ui.join();
}
