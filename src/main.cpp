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

#include <atomic>
#include <chrono>
#include <thread>

atomic<bool> show_popup = false;
atomic<bool> exitt = false;
int timee = 5;
int time_left = 5;
ScreenInteractive screen = ScreenInteractive::Fullscreen();

void timer_loop() {
  while (!exitt) {
    while (!show_popup) {
      std::this_thread::sleep_for(std::chrono::seconds(1));
      if (!decrease_time(time_left)) {
        show_popup = true;
      }
      screen.Post(Event::Custom);
    }
  }
}

int main(int argc, char *argv[]) {
  (void)argc;

  string file = argv[1];
  vector<string> lines2 = read_lines(file);
  if (lines2.size() == 0) {
    return 0;
  }

  shuffle_vector(lines2);
  vector<string> lines = compose_vector(lines2);
  string typed = "";
  // int time = 60;
  int line = 0;
  char last_key = '\0';

  int iteration = 1;
  auto pa = [&] {
    return play_again(lines2, lines, show_popup, line, typed, last_key,
                      time_left, iteration, timee);
  };
  auto cl = [&] { return quit(screen, exitt); };

  Component buttons = popup_buttons(pa, cl);

  Component component =
      CatchEvent(Renderer([&] {
                   if (show_popup) {
                     int score =
                         calculate_score(lines, line, typed, iteration, timee);
                     return popup(score, buttons);
                   } else {
                     return main_ui(lines, line, typed, time_left, last_key);
                   }
                 }),
                 [&](Event event) {
                   return handle_key(buttons, event, screen, lines[line],
                                     show_popup, typed, last_key, line,
                                     lines.size(), iteration, exitt);
                 });

  thread refresh_ui(timer_loop);
  screen.Loop(component);
  refresh_ui.join();
}
