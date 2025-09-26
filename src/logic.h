#pragma once

#include "src/status.h"
#include <ftxui/component/event.hpp>

using namespace ftxui;

bool handle_key(Status &status, Event &event);
void timer_loop(Status &status);
void render(Status &status);
