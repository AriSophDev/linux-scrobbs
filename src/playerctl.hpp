#pragma once
#include <string>
#include "metadata.hpp"

using namespace std;

string run_command(const char* cmd);

metadata parse_metadata(const string& info);

metadata get_current_metadata();

double get_current_position();
