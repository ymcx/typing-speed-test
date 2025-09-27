#pragma once

#include "status.h"
#include <ftxui/component/event.hpp>

using namespace ftxui;

bool handle_key(Status &status, Event &event, Component &buttons);
void timer_loop(Status &status);
void render(Status &status);
