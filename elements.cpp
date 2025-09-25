#include "elements.h"
#include "stats.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>
#include <vector>

using namespace std;

Element colored_text(Stats *stats) {
  string before_text = "";
  if (stats->line > 0) {
    before_text = stats->lines[stats->line - 1];
  }
  Element before = hbox({
      text(before_text) | color(Color::GrayDark),
  });

  Element after = hbox({
      text(stats->lines[stats->line + 1]) | color(Color::GrayDark),
  });

  int typed_correct_amount =
      longest_common(stats->typed_text, stats->lines[stats->line]);
  string typed_correct =
      stats->lines[stats->line].substr(0, typed_correct_amount);
  string typed_wrong = stats->lines[stats->line].substr(
      typed_correct_amount, stats->typed_text.length() - typed_correct_amount);
  string not_typed =
      stats->lines[stats->line].substr(stats->typed_text.length());
  Element current = hbox({
      text(typed_correct) | color(Color::White),
      text(typed_wrong) | color(Color::Red),
      text(not_typed) | color(Color::GrayLight),
      filler(),
      text(to_string(stats->timeleft)) | color(Color::RedLight),
  });

  return vbox({
      before,
      current,
      after,
  });
}

Element keyboard(Stats *stats) {
  vector<Element> rows;

  auto render_row = [&](vector<string> row_keys) {
    vector<Element> row;
    for (string key : row_keys) {
      bool is_active =
          (stats->last_key == key[0] || stats->last_key == tolower(key[0]));
      row.push_back(text(key) | border |
                    (is_active ? bgcolor(Color::Blue) : nothing));
    }
    return hbox(row);
  };

  vector<vector<string>> keys = {{"Q", "W", "E", "R", "T", "Y", "U", "I", "O"},
                                 {"P", "A", "S", "D", "F", "G", "H", "J", "K"},
                                 {"L", "Z", "X", "C", "V", "B", "N", "M"}};

  rows.push_back(render_row(keys[0]));
  rows.push_back(render_row(keys[1]));
  rows.push_back(render_row(keys[2]));

  return vbox(rows);
}

Element popup(Stats *stats, Component *popup_buttons) {
  return window(text("Game Over") | bold,
                vbox({
                    text("Score: " + to_string(stats->score)),
                    separator(),
                    (*popup_buttons)->Render(),
                }) | border |
                    bgcolor(Color::GrayDark));
}

Element main_uii(Element *ttt, Stats *stats) {
  return vbox({
             *ttt | border,
             separator(),
             keyboard(stats),
         }) |
         border | flex;
}
