#pragma once

#include "stats.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

using namespace std;
using namespace ftxui;

#include "logic.h"
#include "stats.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace ftxui;

Element text_previous_next(vector<string> &lines, int i);
Element text_current(vector<string> &lines, int i, string typed);
Element text_timer(int time_left);
Element text_field(vector<string> &lines, int i, string typed, int time_left);
Element keyboard_key(char last_key, char key);
Element keyboard(char last_key);
Component popup_buttons(Stats &stats, ScreenInteractive &screen);
Element popup(int score, Stats &stats, ScreenInteractive &screen);
Element main_uii(vector<string> &lines, int i, string typed, int time_left,
                 char last_char);
