#include <cstdio>
#include <iostream>
#include <cstdio>
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
};



int main() {
    std::string info = run_command("playerctl metadata");

    std::cout << "salida de playerctl: " << std::endl;
    std::cout << info << std::endl;
    return 0;
}
