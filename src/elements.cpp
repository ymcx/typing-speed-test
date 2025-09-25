#include "logic.h"
#include "stats.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace ftxui;

Element text_previous_next(vector<string> &lines, int i) {
  string line = "";
  if (0 <= i && i < static_cast<int>(lines.size())) {
    line = lines[i];
  }

  return text(line) | color(Color::GrayDark);
}

Element text_current(vector<string> &lines, int i, string typed) {
  string line = lines[i];

  int correct_amount = longest_common(typed, line);
  int typed_amount = typed.length();

  string correct = line.substr(0, correct_amount);
  string wrong = line.substr(correct_amount, typed_amount - correct_amount);
  string future = line.substr(typed_amount);

  Element p1 = text(correct) | color(Color::White);
  Element p2 = text(wrong) | color(Color::Red);
  Element p3 = text(future) | color(Color::GrayLight);

  return hbox(p1, p2, p3);
}

Element text_timer(int time_left) {
  string time_left_str = to_string(time_left);
  return text(time_left_str) | color(Color::YellowLight);
}

Element text_field(vector<string> &lines, int i, string typed, int time_left) {
  Element previous = text_previous_next(lines, i - 1);
  Element current = text_current(lines, i, typed);
  Element next = text_previous_next(lines, i + 1);
  Element timer = text_timer(time_left);

  Element text = vbox(previous, current, next);
  Element text_and_timer = hbox(text, timer);

  return text_and_timer;
}

Element keyboard_key(char last_key, char key) {
  Decorator color = (last_key == key) ? bgcolor(Color::Blue) : nothing;
  return text(string(1, key)) | border | color;
}

Element keyboard(char last_key) {
  vector<vector<char>> rows = {{'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O'},
                               {'P', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K'},
                               {'L', 'Z', 'X', 'C', 'V', 'B', 'N', 'M'}};

  vector<Element> rows_element;
  for (vector<char> row : rows) {
    vector<Element> row_element;
    for (char key : row) {
      row_element.push_back(keyboard_key(last_key, key));
    }
    rows_element.push_back(hbox(row_element));
  }

  return vbox(rows_element);
}

Component popup_buttons(Stats &stats, ScreenInteractive &screen) {
  Component play_again_button =
      Button("Play Again", [&] { play_again(stats); });
  Component quit_button = Button("Quit", [&] { close(screen); });

  return Container::Horizontal({
      play_again_button,
      quit_button,
  });
}

Element popup(int score, Stats &stats, ScreenInteractive &screen) {
  Element game_over_text = text("Game over");
  Element score_text = text(format("Score: {}", score));
  Component buttons = popup_buttons(stats, screen);

  return hbox(game_over_text, score_text, buttons->Render());
}

Element main_uii(vector<string> &lines, int i, string typed, int time_left,
                 char last_char) {
  Element top = text_field(lines, i, typed, time_left);
  Element bottom = keyboard(last_char);

  return vbox({
      top | border,
      separator(),
      bottom,
  });
}
