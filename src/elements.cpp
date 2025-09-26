#include "elements.h"
#include "misc.h"
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace ftxui;

Component popup_buttons(function<void()> play_again, function<void()> quit) {
  Component button1 = Button("Play Again", play_again);
  Component button2 = Button("Quit", quit);

  return Container::Horizontal({button1, button2});
}

Element popup(int score, const Component &buttons) {
  Element text1 = text("Game Over");
  Element text2 = text(format("Score: {}", score));

  return vbox(text1, text2, buttons->Render());
}

Element text_previous_next(const vector<string> &lines, int i) {
  int total_lines = lines.size();
  string line = lines[(i + total_lines) % total_lines];

  return text(line) | color(Color::GrayDark);
}

Element text_current(const vector<string> &lines, int i, string typed,
                     bool &last_key_correct) {
  string line = lines[i];

  int correct_amount = common_prefix_length(typed, line);
  int typed_amount = typed.length();

  string correct = line.substr(0, correct_amount);
  string wrong = line.substr(correct_amount, typed_amount - correct_amount);
  string future = line.substr(typed_amount);

  Element text1 = text(correct) | color(Color::White);
  Element text2 = text(wrong) | color(Color::Red);
  Element text3 = text(future) | color(Color::GrayLight);

  last_key_correct = (typed_amount == correct_amount);

  return hbox(text1, text2, text3);
}

Element text_timer(int time_left) {
  return text(to_string(time_left)) | color(Color::Blue);
}

Element text_field(const vector<string> &lines, int i, string typed,
                   int time_left, bool &last_key_correct) {
  Element previous = text_previous_next(lines, i - 1);
  Element current = text_current(lines, i, typed, last_key_correct);
  Element next = text_previous_next(lines, i + 1);
  Element text = vbox(previous, current, next);
  Element timer = text_timer(time_left);

  return hbox(text, timer);
}

Element keyboard_key(char last_key, char key, bool last_key_correct) {
  Decorator color = nothing;
  if (last_key == key) {
    if (last_key_correct) {
      color = bgcolor(Color::Blue);
    } else {
      color = bgcolor(Color::Red);
    }
  }

  return text(string(1, key)) | border | color;
}

Element keyboard(char last_key, bool last_key_correct) {
  vector<vector<char>> rows = {
      {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P'},
      {'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L'},
      {'Z', 'X', 'C', 'V', 'B', 'N', 'M'}};

  vector<Element> rows_element;
  for (vector<char> row : rows) {
    vector<Element> row_element;
    for (char key : row) {
      row_element.push_back(keyboard_key(last_key, key, last_key_correct));
    }
    rows_element.push_back(hbox(row_element));
  }

  return vbox(rows_element);
}

Element main_ui(const vector<string> &lines, int i, string typed, int time_left,
                char last_key) {
  bool last_key_correct = true;

  Element element1 = text_field(lines, i, typed, time_left, last_key_correct);
  Element element2 = keyboard(last_key, last_key_correct);

  return vbox({
      element1 | border,
      element2 | border,
  });
}
