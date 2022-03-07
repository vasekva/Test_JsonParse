#include <iostream>
#include <string>
#include <fstream>

int main() {
    std::string line;
    std::ifstream file;

    file.open("hui.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            std::cout << line << '\n';
        }
        file.close();
    } else
        std::cout << "Unable to open file" << std::endl;
}