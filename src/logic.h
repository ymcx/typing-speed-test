#pragma once

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

using namespace std;
using namespace ftxui;

void play_again(vector<string> &lines, bool &show_popup, int &line,
                string &typed, char &last_key, int &time_left);
void quit(ScreenInteractive &screen);
void delete_char(string &typed, char &last_key);
void next_line(string line, string &typed, int &line_num, char &last_key);
void add_character(string &typed, char &last_key, Event &event);
bool handle_key(Component &popup_buttons, Event &event,
                ScreenInteractive &screen, string line, bool show_popup,
                string &typed, char &last_key, int &line_num);
