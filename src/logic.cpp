#include "logic.h"
#include "stats.h"
#include <cctype>
#include <ftxui/component/screen_interactive.hpp>

using namespace std;
using namespace ftxui;

bool decrease_time(Stats *stats) {
  if (stats->timeleft > 0) {
    stats->timeleft -= 1;
    return true;
  }

  return false;
}

void play_again(Stats &stats) { stats.reset(); }

void close(ScreenInteractive &screen) { screen.Exit(); }

bool handle_key(Stats &stats, Component &popup_buttons, Event &event,
                ScreenInteractive &screen) {
  if (stats.show_popup)
    return popup_buttons->OnEvent(event);

  if (event == Event::Backspace) {
    if (!stats.typed_text.empty())
      stats.typed_text.pop_back();
    stats.last_key = '\0';
    return true;
  }
  if (event == Event::Escape) {
    close(screen);
    return true;
  }

  if (event == Event::Return) {
    if (stats.lines[stats.line] == stats.typed_text) {
      stats.line += 1;
      stats.typed_text = "";
    }
    stats.last_key = '\0';
    return true;
  }

  if (event.is_character()) {
    char c = event.character()[0];
    stats.typed_text += c;
    stats.last_key = toupper(c);
    return true;
  }

  return false;
}
