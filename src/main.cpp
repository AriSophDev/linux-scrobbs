#include <iostream>
#include <thread>
#include <chrono>
#include "playerctl.hpp"
#include "metadata.hpp"

using namespace std;


int main() {
    while (true) {
        metadata m = get_current_metadata();
        double pos = get_current_position();

        cout << "Cancion " << m.title << " - " << m.artist << "\n";
        cout << " Pos: " << pos << "s / " << format_length(m.length) << "\n\n";

       this_thread::sleep_for(std::chrono::seconds(1));
    }
}
