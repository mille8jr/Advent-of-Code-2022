#include <iostream>
#include <fstream>
#include <vector>
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
    std::stringstream ss;
    char ch;
    int temp;
    int sections[4];
    int contained = 0;
    int overlap = 0;
    int i;

    auto lines = readFile("input.txt");
    for(const auto& line : lines){
        ss << line;
        
        // create an array of 4 ints
        for (i = 0; i < 4; i++) {
            if (i == 0) {
                ss >> temp;
                sections[i] = temp;
            }
            else {
                ss >> ch >> temp;
                sections[i] = temp;
            }
        }
        ss.clear();

        // check for overlap
        if (((sections[2] >= sections[0]) && (sections[2] <= sections[1])) ||
            ((sections[0] >= sections[2]) && (sections[0] <= sections[3])))     
        {    
            overlap++;

                // check for containment
                if ((sections[0] <= sections[2] && sections[1] >= sections[3]) ||
                    (sections[2] <= sections[0] && sections[3] >= sections[1])) 
                {
                    contained++;
                }
            
        }
    }
    std::cout << "Total pairs with overlap: " << overlap << std::endl;
    std::cout << "Total pairs with full containment: " << contained << "\n\n";

    return 0;
}