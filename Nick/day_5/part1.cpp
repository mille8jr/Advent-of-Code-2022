#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <string>
#include <sstream>

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
    std::vector<std::deque<char>> pile;
    int i, j, num_crates, source, destination;
    std::stringstream ss;
    std::string temp;


    auto lines = readFile("input.txt");
    for(const auto& line : lines){
        
        if ((line[0] == ' ') || (line[0] == '[') && (line[1] != '1')){
            // Initialize vector if empty
            if (pile.empty()) {
                for (i = 0; i < (line.size() + 1) / 4; i++){
                    std::deque<char> crate;
                    pile.push_back(crate);
                }
            }
            j = 0;
            // Build deques from input
            for (i = 1; i < line.size(); i += 4){
                if (line[i] != ' ') {
                    pile[j].push_back(line[i]);
                }
                j++;
            }
        }
        // rearrange the crates
        else if (line[0] == 'm'){
            ss << line;
            ss >> temp >> num_crates >> temp >> source >> temp >> destination;
            ss.clear();
            source -= 1;
            destination -= 1;

            for(i = 0; i < num_crates; i++){
                pile[destination].push_front(pile[source].front());
                pile[source].pop_front();
            }
        }
        
    }

    for (i = 0; i < pile.size(); i++){
        std::cout << pile[i].front();
    }
    std::cout << "\n\n";
    

    return 0;
}