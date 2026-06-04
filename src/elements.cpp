#include "elements.h"
#include "misc.h"
#include "status.h"
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/terminal.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace ftxui;

const Element hspacer = filler() | size(WIDTH, Constraint::EQUAL, 1);
const Element vspacer = filler() | size(HEIGHT, Constraint::EQUAL, 1);

Component popup_buttons(Status &status) {
  const Component button1 = Button("Play Again", [&] { status.play_again(); });
  const Component button2 = Button("Quit", [&] { status.quit(); });

  return Container::Horizontal({button1, button2});
}

Element popup(Status &status, const Component &buttons) {
  const Element title = text("Game Over");
  const Element content = text(format("Score: {}", status.calculate_score()));
  const Element box = vbox(content, vspacer, buttons->Render()) | center;
  const Element popup = window(title, box) |
                        size(HEIGHT, Constraint::EQUAL, 9) |
                        size(WIDTH, Constraint::EQUAL, 22) | center;

  return popup;
}

Element text_previous_next(Status &status, const int delta) {
  const int lines = status.lines.size();
  const int ln = (status.ln + delta + lines) % lines;
  const string line = status.lines[ln];

  return text(line) | color(Color::GrayDark);
}

Element text_current(Status &status) {
  const string line = status.lines[status.ln];

  const int correct_amount = common_prefix_length(status.typed_string, line);
  const int typed_amount = status.typed_string.length();
  status.set_last_char_correct(typed_amount, correct_amount);

  const string correct = line.substr(0, correct_amount);
  const string wrong =
      line.substr(correct_amount, typed_amount - correct_amount);
  const string future = line.substr(typed_amount);

  const Element text1 = text(correct) | color(Color::White);
  const Element text2 = text(wrong) | color(Color::RedLight);
  const Element text3 = text(future) | color(Color::GrayLight);

  return hbox(text1, text2, text3);
}

Element text_field(Status &status) {
  const Element title = text(to_string(status.time_left)) | color(Color::Cyan);
  const Element prev = text_previous_next(status, -1);
  const Element cur = text_current(status);
  const Element next = text_previous_next(status, 1);
  const Element field = hbox(hspacer, vbox(prev, cur, next), hspacer) |
                        size(WIDTH, Constraint::EQUAL, LINE_WIDTH + 2);

  return window(title, field, BorderStyle::ROUNDED);
}

Element keyboard_key(Status &status, const char key) {
  Decorator color;
  if (status.last_char == key) {
    color = bgcolor(status.last_char_correct ? Color::Cyan : Color::RedLight);
  } else {
    color = nothing;
  }

  return text(string(1, key)) | border | color;
}

Element keyboard(Status &status) {
  const vector<vector<char>> layout_rows = {
      {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P'},
      {'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L'},
      {'Z', 'X', 'C', 'V', 'B', 'N', 'M'}};

  vector<Element> rows;
  for (const vector<char> &layout_row : layout_rows) {
    vector<Element> row;
    for (const char &layout_key : layout_row) {
      const Element key = keyboard_key(status, layout_key);
      row.push_back(key);
    }
    rows.push_back(hbox(row) | center);
  }

  return vbox(rows) | center | border;
}

Element main_ui(Status &status) {
  const Element element1 = text_field(status);
  const Element element2 = keyboard(status);

  return vbox(element1, element2) | center;
}
