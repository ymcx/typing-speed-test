#include "elements.h"
#include "status.h"
#include <chrono>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>
#include <thread>

using namespace ftxui;
using namespace std;

Status status(60);

bool handle_key(Status &status, Component &popup_buttons, Event &event) {
  if (status.popup_shown) {
    return popup_buttons->OnEvent(event);
  }

  if (event == Event::Backspace) {
    status.delete_char();
  } else if (event == Event::Escape) {
    status.quit();
  } else if (event == Event::Return) {
    status.next_line();
  } else if (event.is_character()) {
    status.add_char(event.character()[0]);
  } else {
    return false;
  }

  return true;
}

void timer_loop() {
  while (status.game_on) {
    if (!status.popup_shown) {
      this_thread::sleep_for(std::chrono::seconds(1));
      status.decrease_time();
      status.refresh();
    }
  }
}

int main(int argc, char *argv[]) {
  (void)argc;

  string file = argv[1];
  status.set_file(file);

  Component buttons = popup_buttons(status);

  Component component = CatchEvent(
      Renderer([&] {
        if (status.popup_shown) {
          int score = status.calculate_score();
          return popup(score, buttons);
        } else {
          return main_ui(status);
        }
      }),
      [&](Event event) { return handle_key(status, buttons, event); });

  thread refresh_ui(timer_loop);
  status.screen.Loop(component);
  refresh_ui.join();
}
