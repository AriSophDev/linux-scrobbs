#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::string run_command(const char* cmd) {
    char buffer[256];
    std::string result;

    FILE* pipe = popen(cmd, "r");
    if (!pipe) return "";

    while (fgets(buffer, sizeof(buffer), pipe)) {
        result += buffer;
    }

    pclose(pipe);
    return result;
}

std::vector<std::string> split_lines(const std::string& text) {
    std::vector<std::string> lines;
    std::stringstream ss(text);
    std::string line;

    while (std::getline(ss, line)) {
        lines.push_back(line);
    }

    return lines;
}

struct metadata {
    std::string title;
    std::string artist;
    std::string album;
    std::string length;
};

metadata parse_metadata(const std::string& info) {
    std::vector<std::string> lines = split_lines(info);
    metadata data;

    for (const auto& line : lines) {
        size_t separator_pos = line.find("  ");
        if (separator_pos == std::string::npos) {
            separator_pos = line.find("\t");
        }

        if (separator_pos == std::string::npos) {
            continue;
        }


        std::string key = line.substr(0, separator_pos);
        std::string value = line.substr(separator_pos);


        size_t first_non_space = value.find_first_not_of(" \t");
        if (first_non_space != std::string::npos) {
            value = value.substr(first_non_space);
        }


        size_t potify_pos = key.find("potify ");
        if (potify_pos != std::string::npos) {
            key = key.substr(potify_pos + 7);
        }


        if (key.find("xesam:title") != std::string::npos) {
            data.title = value;
        } else if (key.find("xesam:artist") != std::string::npos) {
            data.artist = value;
        } else if (key.find("xesam:album") != std::string::npos) {
            data.album = value;
        } else if (key.find("mpris:length") != std::string::npos) {
            data.length = value;
        }
    }

    return data;
}

int main() {
    std::string info = run_command("playerctl metadata");
    metadata data = parse_metadata(info);
    std::cout << "Title: " << data.title << std::endl;
    std::cout << "Artist: " << data.artist << std::endl;
    std::cout << "Album: " << data.album << std::endl;
    std::cout << "Length (ns): " << data.length << std::endl;
    return 0;
}
