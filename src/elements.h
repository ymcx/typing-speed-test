#pragma once

#include "stats.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

using namespace std;
using namespace ftxui;

Element colored_text(Stats *stats);

Element keyboard(Stats *stats);

Element popup(Stats *stats, Component *popup_buttons);

Element main_uii(Element *ttt, Stats *stats);
