#pragma once

#include "misc.h"
#include <string>
#include <vector>

using namespace std;

struct Stats {
  int keypresses = 0;
  bool show_popup = false;
  vector<string> lines;
  int score = 0;
  int line = 0;
  string typed_text = "";
  char last_key = '\0';
  int timeleft;
  int ogtime;
  Stats(string arg, int time)
      : lines(read_lines(arg)), timeleft(time), ogtime(time) {}

  void reset() {
    keypresses = 0;
    show_popup = false;
    score = 0;
    line = 0;
    typed_text = "";
    last_key = '\0';
    timeleft = ogtime;
  }
};
