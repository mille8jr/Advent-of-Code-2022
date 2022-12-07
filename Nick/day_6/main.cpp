#include <fstream>
#include <iostream>
#include <vector>

std::vector<std::string> readFile(std::string file_name) {
    std::string              line{""};
    std::vector<std::string> lines{};
    std::ifstream            file{file_name};

    if (file.is_open()) {
        while (file) {
            getline(file, line);
            lines.push_back(line);
        }
    }
    else {
        return {};
    }

    lines.pop_back(); // Remove the last element, which is an empty string.
    return lines;
}

bool checkDuplicates(std::string marker) {
    for (int i = 0; i < marker.size(); i++){
        for (int j = i + 1; j < marker.size(); j++) {
            if (marker[i] == marker[j]) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    std::string input, marker, message;
    int i;
    int found_marker = -1;
    int found_message = -1;

    auto lines = readFile("input.txt");
    if (lines.size() > 1) {
        throw std::invalid_argument("This program only supports inputs of one line");
    }
    for (const auto& line : lines){
        input = line;
    }

    for (i = 3; i < input.size(); i++) {
        marker = input.substr(i - 3, 4);
        if (!checkDuplicates(marker)){
            found_marker = i;
            break;
        }
    }
    for (i = found_marker + 10; i < input.size(); i++) {
        message = input.substr(i - 13, 14);
        if (!checkDuplicates(message)){
            found_message = i;
            break;
        }
    }

    if (found_marker >= 0) {
        std::cout << "First marker after character " << found_marker + 1 << "\n";
    }
    else {
        std::cout << "First marker not found\n";
    }

    if (found_message >= 0) {
        std::cout << "First message after character " << found_message + 1 << "\n\n";
    }
    else {
        std::cout << "First message not found\n";
    }
    return 0;
}