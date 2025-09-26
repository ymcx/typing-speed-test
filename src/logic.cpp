#include "logic.h"
#include "misc.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace ftxui;

void play_again(vector<string> &lines, bool &show_popup, int &line,
                string &typed, char &last_key, int &time_left, int &iteration,
                int time) {
  iteration = 1;
  line = 0;
  typed = "";
  last_key = '\0';
  time_left = time;
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

void next_line(string &typed, char &last_key, string line_str, int &line,
               int total_lines, int &iteration) {
  if (line_str == typed) {
    if (line + 1 == total_lines) {
      ++iteration;
    }

    line = (line + 1) % total_lines;
    typed = "";
  }
  last_key = '\0';
}

void add_char(string &typed, char &last_key, int line_len, Event &event) {
  char c = event.character()[0];
  if (static_cast<int>(typed.length()) < line_len) {
    typed += c;
    last_key = toupper(c);
  } else {
    last_key = '\0';
  }
}

bool handle_key(Component &popup_buttons, Event &event,
                ScreenInteractive &screen, string line_str, bool show_popup,
                string &typed, char &last_key, int &line, int total_lines,
                int &iteration) {
  if (show_popup) {
    return popup_buttons->OnEvent(event);
  }

  int line_len = line_str.length();

  if (event == Event::Backspace) {
    delete_char(typed, last_key);
  } else if (event == Event::Escape) {
    quit(screen);
  } else if (event == Event::Return) {
    next_line(typed, last_key, line_str, line, total_lines, iteration);
  } else if (event.is_character()) {
    add_char(typed, last_key, line_len, event);
  } else {
    return false;
  }

  return true;
}
