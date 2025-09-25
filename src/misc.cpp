#include "misc.h"
#include <fstream>
#include <random>
#include <string>
#include <vector>

using namespace std;

void shuffle(vector<string> &vector) {
  random_device rd;
  mt19937 g(rd());
  shuffle(vector.begin(), vector.end(), g);
}

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

  return lines;
}

int common_prefix_length(string a, string b) {
  int length = 0;
  int length_max = min(a.length(), b.length());
  for (int i = 0; i < length_max; ++i) {
    if (a[i] == b[i]) {
      ++length;
    } else {
      return length;
    }
  }

  return length;
}

int calculate_score(const vector<string> &lines, int line, string typed) {
  int keypresses = 0;
  for (int i = 0; i < line; ++i) {
    keypresses += lines[i].length();
  }
  keypresses += common_prefix_length(typed, lines[line]);

  return keypresses;
}

bool decrease_time(int &time_left) {
  if (time_left > 0) {
    --time_left;
    return true;
  }

  return false;
}
