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
    std::string alphabet = "0abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i = 0;
    int total = 0;

    auto lines = readFile("input.txt");
    while (i < lines.size()) {
      for (const auto& letter : lines[i]) {
        if (lines[i+1].find(letter) != std::string::npos) {
          if (lines[i+2].find(letter) != std::string::npos) {
            total += alphabet.find(letter);
            break;
          }
        }
      }
      i += 3;
    }
        
    std::cout << "Sum of priorities: " << total << "\n\n";

    return 0;
}