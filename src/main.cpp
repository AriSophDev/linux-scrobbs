#include <cstdio>
#include <iostream>
#include <sstream>
#include <ostream>
#include <string>
#include <vector>



std::string run_command(const char* cmd){
    char buffer [256];
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
        if (line.find("xesam:title") != std::string::npos) {
            data.title = line.substr(line.find(":") + 2);
        } else if (line.find("xesam:artist") != std::string::npos) {
            data.artist = line.substr(line.find(":") + 2);
        } else if (line.find("xesam:album") != std::string::npos) {
            data.album = line.substr(line.find(":") + 2);
        } else if (line.find("mpris:length") != std::string::npos) {
            data.length = line.substr(line.find(":") + 2);
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
    std::cout << "Length (ns) " << data.length << std::endl;
    return 0;
}
