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

int chtoi(char ch) {
    return (int(ch) - 48);
}

bool checkVisibility(const std::vector<std::vector<int>> trees, int row, int col) {
    int i;
    int invisibleCount = 0;
    // return true if tree is on perimeter of grid
    if ((row == 0) || (col == 0)) {
        return true;
    }
    else {
        // check left of tree
        for (i = 0; i < col; i++) {
            if (trees[row][i] >= trees[row][col]) {
                invisibleCount++;
                break;
            }
        }
        if (invisibleCount < 1) {
            return true;
        }
        // check right of tree
        for (i = col + 1; i < trees[row].size(); i++) {
            if (trees[row][i] >= trees[row][col]) {
                invisibleCount++;
                break;
            }
        }
        if (invisibleCount < 2) {
            return true;
        }
        // check above tree
        for (i = 0; i < row; i++) {
            if(trees[i][col] >= trees[row][col]) {
                invisibleCount++;
                break;
            }
        }
        if (invisibleCount < 3) {
            return true;
        }
        // check below tree
        for (i = row + 1; i < trees.size(); i++) {
            if(trees[i][col] >= trees[row][col]) {
                invisibleCount++;
                break;
            }
        }
        if (invisibleCount < 4) {
            return true;
        }
        else {
            return false;
        }
    }

}

int main() {
    auto lines = readFile("input.txt");
    std::vector<std::vector<int>> trees(lines.size());
    int i = 0;
    int visCount = 0;

    // build tree grid
    for(const auto& line : lines) {
        for (const auto& tree : line) {
            trees[i].push_back(chtoi(tree));
        }
        i++;
    }

    // count each visible tree
    for(i = 0; i < trees.size(); i++) {
        for (int j = 0; j < trees[0].size(); j++) {
            if (checkVisibility(trees, i, j)) {
               visCount++;
            }
        }
    }

    std::cout << "Total number of visible trees: " << visCount << "\n\n";

    return 0;
}