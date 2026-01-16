#include "playerctl.hpp"
#include "metadata.hpp"
#include <string>
#include <cstdio>
#include <sstream>
#include <vector>

using namespace std;


string run_command(const char* cmd) {
    char buffer[256];
    string result;

    FILE* pipe = popen(cmd, "r");
    if (!pipe) return "ERROR";

    while (!feof(pipe)) {
        if (fgets(buffer, 256, pipe) != NULL)
            result += buffer;
    }
    pclose(pipe);

    return result;
}

vector<string> split_lines(const string& text) {
    vector<string> lines;
    stringstream ss(text);
    string line;

    while (getline(ss, line)) {
        lines.push_back(line);
    }

    return lines;
}

metadata parse_metadata(const string& info) {
    auto lines = split_lines(info);
    metadata data;

    for (const auto& line : lines) {
        size_t separator = line.find("  ");
        if (separator == string::npos) separator = line.find("\t");
        if (separator == string::npos) continue;

        string key = line.substr(0, separator);
        string value = line.substr(separator);

        size_t non_space = value.find_first_not_of(" \t");
        if (non_space != string::npos)
            value = value.substr(non_space);

        // Limpia "spotify xesam:title" → "xesam:title"
        size_t last_space = key.rfind(' ');
        if (last_space != string::npos)
            key = key.substr(last_space + 1);

        if (key == "xesam:title") data.title = value;
        if (key == "xesam:artist") data.artist = value;
        if (key == "xesam:album") data.album = value;
        if (key == "mpris:length") data.length = value;
    }
    return data;
}

metadata get_current_metadata() {
    return parse_metadata(run_command("playerctl metadata"));
}

double get_current_position() {
    std::string out = run_command("playerctl position");
    if (out.empty()) return 0.0;
    return std::stod(out);
}


