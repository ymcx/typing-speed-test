#include "elements.h"
#include "misc.h"
#include "status.h"
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ranges>
#include <string>
#include <vector>

using namespace std;
using namespace ftxui;

const Element hspacer = filler() | size(WIDTH, EQUAL, 1);
const Element vspacer = filler() | size(HEIGHT, EQUAL, 1);

Component popup_buttons(Status &status) {
  Component button1 = Button("Play Again", [&] { status.play_again(); });
  Component button2 = Button("Quit", [&] { status.quit(); });

  return Container::Horizontal({button1, button2});
}

Element popup(Status &status, Component &buttons) {
  Element text1 = text("Game Over");
  Element text2 = text(format("Score: {}", status.calculate_score()));

  Element box = vbox(vspacer, text1, text2, vspacer, buttons->Render());
  Element window = hbox(hspacer, box) | border;

  return window | size(HEIGHT, EQUAL, 8) | size(WIDTH, EQUAL, 20);
}

Element text_previous_next(Status &status, int delta) {
  int lines = status.lines.size();
  int ln = (status.ln + delta + lines) % lines;
  string line = status.lines[ln];

  return text(line) | color(Color::GrayDark);
}

Element text_current(Status &status) {
  string line = status.lines[status.ln];

  int correct_amount = common_prefix_length(status.typed_string, line);
  int typed_amount = status.typed_string.length();
  status.set_last_char_correct(typed_amount, correct_amount);

  string correct = line.substr(0, correct_amount);
  string wrong = line.substr(correct_amount, typed_amount - correct_amount);
  string future = line.substr(typed_amount);

  Element text1 = text(correct) | color(Color::White);
  Element text2 = text(wrong) | color(Color::Red);
  Element text3 = text(future) | color(Color::GrayLight);

  return hbox(text1, text2, text3);
}

Element text_timer(Status &status) {
  string time_left = to_string(status.time_left + 1);
  Element timer = text(time_left) | color(Color::BlueLight);

  timer = vbox(vspacer, timer, vspacer);
  timer = hbox(hspacer, timer, hspacer);

  return timer | border;
}

Element text_field(Status &status) {
  Element previous = text_previous_next(status, -1);
  Element text = text_current(status);
  Element next = text_previous_next(status, 1);

  text = vbox(previous, text, next);
  text = hbox(hspacer, text, hspacer);

  return text | border;
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
  vector<vector<char>> layout_rows = {
      {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P'},
      {'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L'},
      {'Z', 'X', 'C', 'V', 'B', 'N', 'M'}};

  vector<Element> rows;
  for (auto [i, layout_row] : views::enumerate(layout_rows)) {
    vector<Element> row;
    for (char layout_key : layout_row) {
      row.push_back(keyboard_key(status, layout_key));
    }
    rows.push_back(hbox(row) | center);
  }

  Element keyboard = hbox(hspacer, vbox(rows), hspacer);
  return keyboard | border | size(WIDTH, EQUAL, 32);
}

Element main_ui(Status &status) {
  Element element1 = text_field(status);
  Element element2 = text_timer(status);
  Element element3 = keyboard(status);

  return vbox(hbox(element1, element2), element3);
}
