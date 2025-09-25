#pragma once

#include "misc.h"
#include <string>
#include <vector>

using namespace std;

struct Stats {
  bool show_popup = false;
  int line = 0;
  string typed_text = "";
  char last_key = '\0';
  int timeleft;
  int ogtime;

  Stats(int time) : timeleft(time), ogtime(time) {}

  int calculate_score(const vector<string> &lines) {
    int keypresses = 0;
    for (int i = 0; i < line; ++i) {
      keypresses += lines[i].length();
    }
    keypresses += common_prefix_length(typed_text, lines[line]);

    return 60 * keypresses / ogtime;
  }

  void reset() {
    show_popup = false;
    line = 0;
    typed_text = "";
    last_key = '\0';
    timeleft = ogtime;
  }
};
