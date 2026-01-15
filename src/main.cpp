#include <cstdio>
#include <iostream>
#include <cstdio>
#include <ostream>
#include <string>

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

int main() {
    std::string info = run_command("playerctl metadata");

    std::cout << "salida de playerctl: " << std::endl;
    std::cout << info << std::endl;
    return 0;
}
