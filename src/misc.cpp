#include "misc.h"
#include <fstream>
#include <random>
#include <string>
#include <vector>

using namespace std;

void shuffle_vector(vector<string> &input) {
  random_device rd;
  mt19937 g(rd());
  shuffle(input.begin(), input.end(), g);
}

vector<string> compose_vector(const vector<string> &input) {
  vector<string> output;
  string part;

  for (string new_part : input) {
    if (part.length() + new_part.length() > 80) {
      part.pop_back();
      output.push_back(part);
      part = "";
    }
    part += new_part;
    part += ' ';
  }

  return output;
}

void toupper_str(string &input) {
  transform(input.begin(), input.end(), input.begin(),
            [](unsigned char c) { return toupper(c); });
}

void tolower_str(string &input) {
  transform(input.begin(), input.end(), input.begin(),
            [](unsigned char c) { return tolower(c); });
}

vector<string> read_lines(string path) {
  vector<string> lines;
  string line;
  ifstream file(path);

  if (file.is_open()) {
    while (getline(file, line)) {
      tolower_str(line);
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
    if (a[i] != b[i]) {
      break;
    }
    ++length;
  }

  return length;
}
