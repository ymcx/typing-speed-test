#include "elements.h"
#include "logic.h"
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
  Stats stats(file, time);

  ScreenInteractive screen = ScreenInteractive::Fullscreen();

  Component play_again_button =
      Button("Play Again", [&] { play_again(&stats); });
  Component quit_button = Button("Quit", [&] { close(&screen); });
  Component popup_buttons = Container::Horizontal({
      play_again_button,
      quit_button,
  });

  Component component =
      CatchEvent(Renderer([&] {
                   Element ttt = colored_text(&stats);
                   Element main_ui = main_uii(&ttt, &stats);

                   if (stats.show_popup) {
                     return popup(&stats, &popup_buttons);
                   }

                   return main_ui;
                 }),
                 [&](Event event) {
                   return handle_key(&stats, &popup_buttons, &event, &screen);
                 });

  atomic<bool> refresh_ui_continue = true;
  thread refresh_ui([&] {
    while (refresh_ui_continue) {
      this_thread::sleep_for(1.00s);
      if (!decrease_time(&stats)) {
        stats.keypresses +=
            longest_common(stats.typed_text, stats.lines[stats.line]);

        refresh_ui_continue = false;
        stats.score = 60 * stats.keypresses / time;
        stats.show_popup = true;
      }
      screen.Post(Event::Custom);
    }
  });

  screen.Loop(component);
  refresh_ui_continue = false;
  refresh_ui.join();
}
