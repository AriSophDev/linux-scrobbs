#pragma once
#include <string>

using namespace std;

struct metadata {
    string title;
    string artist;
    string album;
    string length;
};

string format_length(const std::string& ns_str);
