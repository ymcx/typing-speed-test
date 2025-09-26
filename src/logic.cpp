#include "src/logic.h"
#include "src/elements.h"
#include "src/status.h"

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

Element render(Status &status) {
  if (status.popup_shown) {
    int score = status.calculate_score();
    return popup(status, score);
  } else {
    return main_ui(status);
  }
}

Component get_child(Status &status) {
  return Renderer([&] { return render(status); });
}

Component get_component(Status &status) {
  Component component = CatchEvent(get_child(status), [&](Event event) {
    return handle_key(status, event);
  });
  return component;
}

void renderi(Status &status) {
  Component component = get_component(status);
  thread refresh_ui([&] { timer_loop(status); });
  status.screen.Loop(component);
  refresh_ui.join();
}
