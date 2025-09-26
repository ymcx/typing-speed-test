#include "src/logic.h"
#include "src/elements.h"
#include "src/status.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>

using namespace ftxui;

bool handle_key(Status &status, Event &event, Component &buttons) {
  if (status.popup_shown) {
    return buttons->OnEvent(event);
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
      this_thread::sleep_for(chrono::seconds(1));
      status.decrease_time();
      status.refresh();
    }
  }
}

void render(Status &status) {
  Component buttons = popup_buttons(status);
  Component ui = CatchEvent(
      Renderer([&] {
        return (status.popup_shown) ? popup(status, buttons) : main_ui(status);
      }),
      [&](Event event) { return handle_key(status, event, buttons); });
  thread refresh_ui([&] { timer_loop(status); });

  status.screen.Loop(ui);
  refresh_ui.join();
}
