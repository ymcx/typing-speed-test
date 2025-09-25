#include "logic.h"
#include "misc.h"
#include <cctype>
#include <ftxui/component/screen_interactive.hpp>

using namespace std;
using namespace ftxui;

void play_again(vector<string> &lines, bool &show_popup, int &line,
                string &typed, char &last_key, int &time_left) {
  line = 0;
  typed = "";
  last_key = '\0';
  time_left = 60;

  shuffle(lines);
  show_popup = false;
}

void quit(ScreenInteractive &screen) { screen.Exit(); }

void delete_char(string &typed, char &last_key) {
  if (!typed.empty())
    typed.pop_back();
  last_key = '\0';
}

void next_line(string line, string &typed, int &line_num, char &last_key) {
  if (line == typed) {
    line_num += 1;
    typed = "";
  }
  last_key = '\0';
}

void add_character(string &typed, char &last_key, Event &event) {
  char c = event.character()[0];
  typed += c;
  last_key = toupper(c);
}

bool handle_key(Component &popup_buttons, Event &event,
                ScreenInteractive &screen, string line, bool show_popup,
                string &typed, char &last_key, int &line_num) {
  if (show_popup) {
    return popup_buttons->OnEvent(event);
  }

  if (event == Event::Backspace) {
    delete_char(typed, last_key);
  } else if (event == Event::Escape) {
    quit(screen);
  } else if (event == Event::Return) {
    next_line(line, typed, line_num, last_key);
  } else if (event.is_character()) {
    add_character(typed, last_key, event);
  } else {
    return false;
  }

  return true;
}
