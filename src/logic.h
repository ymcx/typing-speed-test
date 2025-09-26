#pragma once

#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace ftxui;

void play_again(vector<string> &lines2, vector<string> &lines,
                atomic<bool> &show_popup, int &line, string &typed,
                char &last_key, int &time_left, int &iteration, int time);
void quit(ScreenInteractive &screen, atomic<bool> &exitt);
void delete_char(string &typed, char &last_key);
void next_line(string &typed, char &last_key, string line_str, int &line,
               int total_lines, int &iteration);
void add_char(string &typed, char &last_key, int line_len, Event &event);
bool handle_key(Component &popup_buttons, Event &event,
                ScreenInteractive &screen, string line_str,
                atomic<bool> &show_popup, string &typed, char &last_key,
                int &line, int total_lines, int &iteration,
                atomic<bool> &exitt);
