#include "misc.h"
#include <fstream>
#include <random>
#include <string>
#include <vector>

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
