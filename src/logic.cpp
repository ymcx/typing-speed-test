#include "src/logic.h"
#include "src/elements.h"
#include "src/status.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>

using namespace ftxui;

bool handle_key(Status &status, Event &event) {
  if (status.popup_shown) {
    return popup_buttons(status)->OnEvent(event);
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

void timer_loop(Status &status) {
  while (true) {
    if (!status.popup_shown) {
      this_thread::sleep_for(std::chrono::seconds(1));
      status.decrease_time();
      status.refresh();
    }
  }
}

void render(Status &status) {
  Component component =
      CatchEvent(Renderer([&] { return main_screen(status); }),
                 [&](Event event) { return handle_key(status, event); });
  thread refresh_ui([&] { timer_loop(status); });
  status.screen.Loop(component);
  refresh_ui.join();
}
