#pragma once

#include "stats.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

using namespace std;
using namespace ftxui;

bool decrease_time(Stats *stats);

void play_again(Stats &stats);

void close(ScreenInteractive &screen);

bool handle_key(Stats &stats, Component &popup_buttons, Event &event,
                ScreenInteractive &screen);
