#pragma once

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace ftxui;

Component popup_buttons(function<void()> pa, function<void()> cl);
Element popup(int score, Component &buttons);
Element text_previous_next(vector<string> &lines, int i);
Element text_current(vector<string> &lines, int i, string typed);
Element text_timer(int time_left);
Element text_field(vector<string> &lines, int i, string typed, int time_left);
Element keyboard_key(char last_key, char key);
Element keyboard(char last_key);
Element main_ui(vector<string> &lines, int i, string typed, int time_left,
                char last_char);
