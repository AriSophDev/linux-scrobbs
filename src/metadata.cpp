#include "metadata.hpp"
#include <cstdio>

using namespace std;

string format_length(const string& ns_str) {
    if (ns_str.empty()) return "";

    long long ns = stoll(ns_str);
    long long seconds_total = ns / 1'000'000'000;

    int minutes = seconds_total / 60;
    int seconds = seconds_total % 60;

    char buffer[16];
    snprintf(buffer, sizeof(buffer), "%d:%02d", minutes, seconds);

    return string(buffer);
}
