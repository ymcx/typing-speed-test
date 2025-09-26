#include "src/elements.h"
#include "src/misc.h"
#include "src/status.h"
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

Element popup(Status &status, Component &buttons) {
  Element text1 = text("Game Over");
  Element text2 = text(format("Score: {}", status.calculate_score()));

  Element hspacer = filler() | size(HEIGHT, EQUAL, 1);
  Element wspacer = filler() | size(WIDTH, EQUAL, 1);
  Element box = vbox(hspacer, text1, text2, buttons->Render());
  Element window = hbox(wspacer, box) | border;

  return window | size(HEIGHT, EQUAL, 7) | size(WIDTH, EQUAL, 20);
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
  return text(to_string(status.time_left)) | color(Color::BlueLight);
}

Element text_field(Status &status) {
  Element previous = text_previous_next(status, -1);
  Element current = text_current(status);
  Element next = text_previous_next(status, 1);
  Element text = vbox(previous, current, next);

  Element timer_not_centered = text_timer(status);
  Element timer = vbox(filler(), timer_not_centered, filler());

  Element spacer = filler() | size(WIDTH, EQUAL, 1);
  Element field = hbox(spacer, text, filler(), separator(), spacer, timer);

  return field | size(WIDTH, EQUAL, 44);
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
  for (vector<char> layout_row : layout_rows) {
    vector<Element> row;
    for (char layout_key : layout_row) {
      row.push_back(keyboard_key(status, layout_key));
    }
    rows.push_back(hbox(row));
  }

  return vbox(rows);
}

Element main_ui(Status &status) {
  Element element1 = text_field(status);
  Element element2 = keyboard(status);

  return vbox({
      element1 | border,
      element2 | border,
  });
}
