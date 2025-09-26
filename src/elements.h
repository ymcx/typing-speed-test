#pragma once

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace ftxui;

Component popup_buttons(function<void()> play_again, function<void()> quit);
Element popup(int score, const Component &buttons);
Element text_previous_next(const vector<string> &lines, int i);
Element text_current(const vector<string> &lines, int i, string typed,
                     bool &last_key_correct);
Element text_timer(int time_left);
Element text_field(const vector<string> &lines, int i, string typed,
                   int time_left, bool &last_key_correct);
Element keyboard_key(char last_key, char key, bool last_key_correct);
Element keyboard(char last_key, bool last_key_correct);
Element main_ui(const vector<string> &lines, int i, string typed, int time_left,
                char last_key);
