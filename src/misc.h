#pragma once

#include <string>
#include <vector>

using namespace std;

constexpr int LINE_WIDTH = 50;

void shuffle_vector(vector<string> &input);
vector<string> compose_vector(const vector<string> &input);
void toupper_str(string &input);
void tolower_str(string &input);
vector<string> read_lines(string path);
int common_prefix_length(string a, string b);
