#include <algorithm>
#include <fstream>
#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <random>
#include <string>
#include <vector>

using namespace ftxui;
using namespace std;

vector<string> read_lines(string path) {
  vector<string> lines;
  string line;
  ifstream file(path);

  if (file.is_open()) {
    while (getline(file, line)) {
      lines.push_back(line);
    }
    file.close();
  }

  random_device rd;
  mt19937 g(rd());
  shuffle(lines.begin(), lines.end(), g);

  return lines;
}
struct Stats {
  int keypresses = 0;
  bool show_popup = false;
  vector<string> lines;
  int score = 0;
  int line = 0;
  string typed_text = "";
  char last_key = '\0';
  int timeleft;
  Stats(string arg, int time) : lines(read_lines(arg)), timeleft(time) {}
};

bool handle_key(Stats *stats, Component *popup_buttons, Event *event,
                ScreenInteractive *screen) {
  if (stats->show_popup)
    return (*popup_buttons)->OnEvent(*event);

  if (*event == Event::Backspace) {
    if (!stats->typed_text.empty())
      stats->typed_text.pop_back();
    stats->last_key = '\0';
    return true;
  }
  if (*event == Event::Escape) {
    screen->Exit();
    return true;
  }

  if (*event == Event::Return) {
    if (stats->lines[stats->line] == stats->typed_text) {
      stats->keypresses += stats->lines[stats->line].length();
      stats->line += 1;
      stats->typed_text = "";
    }
    stats->last_key = '\0';
    return true;
  }

  if (event->is_character()) {
    char c = event->character()[0];
    stats->typed_text += c;
    stats->last_key = c;
    return true;
  }

  return false;
}
int longest_common(string a, string b) {

  int longest = 0;
  int len = min(a.length(), b.length());
  for (int i = 0; i < len; ++i) {
    if (a[i] == b[i]) {
      ++longest;
    }
  }
  return longest;
}

Element colored_text(const vector<string> &lines, int line, string typed_text,
                     int timeleft) {
  string before_text = "";
  if (line > 0) {
    before_text = lines[line - 1];
  }
  Element before = hbox({
      text(before_text) | color(Color::GrayDark),
  });

  Element after = hbox({
      text(lines[line + 1]) | color(Color::GrayDark),
  });

  int typed_correct_amount = longest_common(typed_text, lines[line]);
  string typed_correct = lines[line].substr(0, typed_correct_amount);
  string typed_wrong = lines[line].substr(
      typed_correct_amount, typed_text.length() - typed_correct_amount);
  string not_typed = lines[line].substr(typed_text.length());
  Element current = hbox({
      text(typed_correct) | color(Color::White),
      text(typed_wrong) | color(Color::Red),
      text(not_typed) | color(Color::GrayLight),
      filler(),
      text(to_string(timeleft)) | color(Color::BlueLight),
  });

  return vbox({
      before,
      current,
      after,
  });
}

int main(int _, char *argv[]) {
  int time = 10;
  Stats stats(argv[1], time);

  vector<vector<string>> keys = {{"Q", "W", "E", "R", "T", "Y", "U", "I", "O"},
                                 {"P", "A", "S", "D", "F", "G", "H", "J", "K"},
                                 {"L", "Z", "X", "C", "V", "B", "N", "M"}};

  auto screen = ScreenInteractive::Fullscreen();
  auto play_again_button = Button("Play Again", [&] {
    stats.typed_text = "";
    stats.line = 0;
    stats.show_popup = false;
  });
  auto quit_button = Button("Quit", [&] { screen.Exit(); });
  auto popup_buttons = Container::Horizontal({
      play_again_button,
      quit_button,
  });

  auto keyboard_renderer = [&] {
    vector<Element> rows;

    auto render_row = [&](vector<string> row_keys) {
      vector<Element> row;
      for (string key : row_keys) {
        bool is_active =
            (stats.last_key == key[0] || stats.last_key == tolower(key[0]));
        row.push_back(text(key) | border |
                      (is_active ? bgcolor(Color::Blue) : nothing));
      }
      return hbox(row);
    };

    rows.push_back(render_row(keys[0]));
    rows.push_back(render_row(keys[1]));
    rows.push_back(render_row(keys[2]));

    return vbox(rows);
  };

  auto component =
      CatchEvent(Renderer([&] {
                   Element ttt = colored_text(stats.lines, stats.line,
                                              stats.typed_text, stats.timeleft);

                   Element main_ui = vbox({
                                         ttt | border,
                                         separator(),
                                         keyboard_renderer(),
                                     }) |
                                     border | flex;

                   if (stats.show_popup) {
                     Element popup =
                         window(text("Game Over") | bold,
                                vbox({
                                    text("Score: " + to_string(stats.score)),
                                    separator(),
                                    popup_buttons->Render(),
                                }) | border |
                                    bgcolor(Color::GrayDark));
                     return dbox({
                         main_ui,
                         popup,
                     });
                   }

                   return main_ui;
                 }),
                 [&](Event event) {
                   return handle_key(&stats, &popup_buttons, &event, &screen);
                 });

  atomic<bool> refresh_ui_continue = true;
  thread refresh_ui([&] {
    while (refresh_ui_continue) {
      this_thread::sleep_for(1.00s);
      if (stats.timeleft <= 1) {
        stats.keypresses +=
            longest_common(stats.typed_text, stats.lines[stats.line]);

        refresh_ui_continue = false;
        stats.score = 60 * stats.keypresses / time;
        stats.show_popup = true;

        screen.Post(Event::Custom);
      } else {
        screen.Post([&] { stats.timeleft--; });
        screen.Post(Event::Custom);
      }
    }
  });

  screen.Loop(component);
  refresh_ui_continue = false;
  refresh_ui.join();
}
