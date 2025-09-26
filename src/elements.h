#pragma once

#include "src/status.h"
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

Component popup_buttons(Status &status);
Element popup(Status &status, Component &buttons);
Element text_previous_next(Status &status, int delta);
Element text_current(Status &status);
Element text_timer(Status &status);
Element text_field(Status &status);
Element keyboard_key(Status &status, char key);
Element keyboard(Status &status);
Element main_ui(Status &status);
