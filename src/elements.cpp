#include "elements.h"
#include "misc.h"
#include "status.h"
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace ftxui;

Component popup_buttons(Status &status) {
  Component button1 = Button("Play Again", [&] { status.play_again(); });
  Component button2 = Button("Quit", [&] { status.quit(); });

  return Container::Horizontal({button1, button2});
}

Element popup(Status &status, int score) {
  Element text1 = text("Game Over");
  Element text2 = text(format("Score: {}", score));

  return vbox(text1, text2, popup_buttons(status)->Render());
}

Element text_previous_next(Status &status, int delta) {
  int total_lines = status.lines.size();
  string line = status.lines[(status.ln + delta + total_lines) % total_lines];

  return text(line) | color(Color::GrayDark);
}

Element text_current(Status &status) {
  string line = status.lines[status.ln];

  int correct_amount = common_prefix_length(status.typed_string, line);
  int typed_amount = status.typed_string.length();

  string correct = line.substr(0, correct_amount);
  string wrong = line.substr(correct_amount, typed_amount - correct_amount);
  string future = line.substr(typed_amount);

  Element text1 = text(correct) | color(Color::White);
  Element text2 = text(wrong) | color(Color::Red);
  Element text3 = text(future) | color(Color::GrayLight);

  status.set_last_char_correct(typed_amount, correct_amount);

  return hbox(text1, text2, text3);
}

Element text_timer(Status &status) {
  return text(to_string(status.time_left)) | color(Color::Blue);
}

Element text_field(Status &status) {
  Element previous = text_previous_next(status, -1);
  Element current = text_current(status);
  Element next = text_previous_next(status, 1);
  Element text = vbox(previous, current, next);
  Element timer = text_timer(status);

  return hbox(text, timer);
}

Element keyboard_key(Status &status, char key) {
  Decorator color = nothing;
  if (status.last_char == key) {
    if (status.last_char_correct) {
      color = bgcolor(Color::Blue);
    } else {
      color = bgcolor(Color::Red);
    }
  }

  return text(string(1, key)) | border | color;
}

Element keyboard(Status &status) {
  vector<vector<char>> rows = {
      {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P'},
      {'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L'},
      {'Z', 'X', 'C', 'V', 'B', 'N', 'M'}};

  vector<Element> rows_element;
  for (vector<char> row : rows) {
    vector<Element> row_element;
    for (char key : row) {
      row_element.push_back(keyboard_key(status, key));
    }
    rows_element.push_back(hbox(row_element));
  }

  return vbox(rows_element);
}

Element main_ui(Status &status) {
  Element element1 = text_field(status);
  Element element2 = keyboard(status);

  return vbox({
      element1 | border,
      element2 | border,
  });
}
