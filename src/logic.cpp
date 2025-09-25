#include "logic.h"
#include "misc.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace ftxui;

void play_again(vector<string> &lines, bool &show_popup, int &line,
                string &typed, char &last_key, int &time_left) {
  line = 0;
  typed = "";
  last_key = '\0';
  time_left = 60;
  show_popup = false;
  shuffle_vector(lines);
}

void quit(ScreenInteractive &screen) { screen.Exit(); }

void delete_char(string &typed, char &last_key) {
  if (!typed.empty()) {
    typed.pop_back();
  }
  last_key = '\0';
}

void next_line(string &typed, char &last_key, string line_str, int &line) {
  if (line_str == typed) {
    line += 1;
    typed = "";
  }
  last_key = '\0';
}

void add_char(string &typed, char &last_key, Event &event) {
  char c = event.character()[0];
  typed += c;
  last_key = toupper(c);
}

bool handle_key(Component &popup_buttons, Event &event,
                ScreenInteractive &screen, string line_str, bool show_popup,
                string &typed, char &last_key, int &line) {
  if (show_popup) {
    return popup_buttons->OnEvent(event);
  }

  if (event == Event::Backspace) {
    delete_char(typed, last_key);
  } else if (event == Event::Escape) {
    quit(screen);
  } else if (event == Event::Return) {
    next_line(typed, last_key, line_str, line);
  } else if (event.is_character()) {
    add_char(typed, last_key, event);
  } else {
    return false;
  }

  return true;
}
