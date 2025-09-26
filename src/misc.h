#pragma once

#include <string>
#include <vector>

using namespace std;

void shuffle_vector(vector<string> &vector);
void toupper_str(string &input);
void tolower_str(string &input);
vector<string> read_lines(string path);
int common_prefix_length(string a, string b);
int calculate_score(const vector<string> &lines, int line, string typed,
                    int iteration, int time);
bool decrease_time(int &time_left);
