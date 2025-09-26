#pragma once

#include "misc.h"
#include <ftxui/component/screen_interactive.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace ftxui;

struct Status {
  ScreenInteractive screen = ScreenInteractive::Fullscreen();
  vector<string> all_words;
  vector<string> lines;
  string typed_string = "";
  char last_char = '\0';
  int iteration = 1;
  int time_left = 0;
  int original_time = 0;
  int ln = 0;
  bool popup_shown = false;
  bool last_char_correct = true;

  Status(string path, int time) {
    all_words = read_lines(path);
    lines = shuffle_lines();
    original_time = time;
    time_left = time;
  }

  vector<string> shuffle_lines() {
    shuffle_vector(all_words);
    return compose_vector(all_words);
  }

  void set_last_char_correct(int a, int b) { last_char_correct = (a == b); }

  void quit() { screen.Exit(); }

  void refresh() { screen.Post(Event::Custom); }

  void decrease_time() {
    if (time_left > 0) {
      --time_left;
    } else {
      popup_shown = true;
    }
  }

  void play_again() {
    lines = shuffle_lines();
    typed_string = "";
    last_char = '\0';
    iteration = 1;
    time_left = original_time;
    ln = 0;
    popup_shown = false;
    last_char_correct = true;
  }

  int calculate_score() {
    int characters = 0;
    for (int i = 0; i < static_cast<int>(lines.size()); ++i) {
      int len = lines[i].length();
      if (i < ln) {
        characters += len * iteration;
      } else {
        characters += len * (iteration - 1);
      }
    }

    characters += common_prefix_length(typed_string, lines[ln]);
    int score = 60 * characters / original_time;

    return score;
  }

  void add_char(char c) {
    if (typed_string.length() < lines[ln].length()) {
      typed_string += c;
      last_char = toupper(c);
    } else {
      last_char = '\0';
    }
  }

  void next_line() {
    if (lines[ln] == typed_string) {
      if (ln + 1 == static_cast<int>(lines.size())) {
        ++iteration;
      }

      ln = (ln + 1) % lines.size();
      typed_string = "";
    }

    last_char = '\0';
  }

  void delete_char() {
    if (!typed_string.empty()) {
      typed_string.pop_back();
    }

    last_char = '\0';
  }
};
