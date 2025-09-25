#include "logic.h"
#include "misc.h"
#include "stats.h"
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace ftxui;

Component popup_buttons(Stats &stats, ScreenInteractive &screen) {
  Component button1 = Button("Play Again", [&] { play_again(stats); });
  Component button2 = Button("Quit", [&] { quit(screen); });

  return Container::Horizontal({button1, button2});
}

Element popup(int score, Component &buttons) {
  Element game_over_text = text("Game Over");
  Element score_text = text(format("Score: {}", score));

  return vbox(game_over_text, score_text, buttons->Render());
}

Element text_previous_next(vector<string> &lines, int i) {
  string line = "";
  if (0 <= i && i < static_cast<int>(lines.size())) {
    line = lines[i];
  }

  return text(line) | color(Color::GrayDark);
}

Element text_current(vector<string> &lines, int i, string typed) {
  string line = lines[i];

  int correct_amount = common_prefix_length(typed, line);
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
  return text(to_string(time_left)) | color(Color::BlueLight);
}

Element text_field(vector<string> &lines, int i, string typed, int time_left) {
  Element previous = text_previous_next(lines, i - 1);
  Element current = text_current(lines, i, typed);
  Element next = text_previous_next(lines, i + 1);
  Element text = vbox(previous, current, next);
  Element timer = text_timer(time_left);

  return hbox(text, timer);
}

Element keyboard_key(char last_key, char key) {
  Decorator color = (last_key == key) ? bgcolor(Color::BlueLight) : nothing;
  return text(string(1, key)) | border | color;
}

Element keyboard(char last_key) {
  vector<vector<char>> rows = {
      {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P'},
      {'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L'},
      {'Z', 'X', 'C', 'V', 'B', 'N', 'M'}};

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

Element main_ui(vector<string> &lines, int i, string typed, int time_left,
                char last_char) {
  Element top = text_field(lines, i, typed, time_left);
  Element bottom = keyboard(last_char);

  return vbox({
      top | border,
      bottom | border,
  });
}
