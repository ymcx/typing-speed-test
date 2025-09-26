#pragma once

#include "src/status.h"
#include <ftxui/dom/node.hpp>

bool handle_key(Status &status, Event &event);
void timer_loop(Status &status);
Element render(Status &status);
Component get_child(Status &status);
Component get_component(Status &status);
void renderi(Status &status);
