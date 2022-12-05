#include <iostream>
#include <fstream>
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

int main() {
    std::string compartment1, compartment2;
    std::string alphabet = "0abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int total = 0;

    auto lines = readFile("input.txt");
    for(const auto& line : lines){
        compartment1 = line.substr(0, line.length() / 2);
        compartment2 = line.substr(line.length() / 2, line.length());
        for(const auto& letter : compartment1)
            if (compartment2.find(letter) != std::string::npos){
                total += alphabet.find(letter);
                break;
            }
    }
    std::cout << "Sum of priorities: " << total << "\n\n";

    return 0;
}