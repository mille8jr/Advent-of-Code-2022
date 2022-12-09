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

int getScenicScore(const std::vector<std::vector<int>> trees, int row, int col) {
    int i;
    int tree_count = 0;
    int scenic_score;
    // return 0 if tree is on perimeter of grid
    if ((row == 0) || (col == 0)) {
        return 0;
    }
    else {
        // check left of tree
        for (i = 0; i < col; i++) {
            if (trees[row][i] >= trees[row][col]) {
                tree_count = 0;
            }
            tree_count++;
        }
        scenic_score = tree_count;
        tree_count = 0;
        // check right of tree
        for (i = col + 1; i < trees[row].size(); i++) {
            if (trees[row][i] >= trees[row][col]) {
                tree_count++;
                break;
            }
            tree_count++;
        }
        scenic_score *= tree_count;
        tree_count = 0;
        // check above tree
        for (i = 0; i < row; i++) {
            if(trees[i][col] >= trees[row][col]) {
                tree_count = 0;
            }
            tree_count++;
        }
        scenic_score *= tree_count;
        tree_count = 0;
        // check below tree
        for (i = row + 1; i < trees.size(); i++) {
            if(trees[i][col] >= trees[row][col]) {
                tree_count++;
                break;
            }
            tree_count++;
        }
        scenic_score *= tree_count;
        return scenic_score;
    }

}

int main() {
    auto lines = readFile("input.txt");
    std::vector<std::vector<int>> trees(lines.size());
    int i = 0;
    int scenic_score = 0;

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
            int temp = getScenicScore(trees, i, j);
            if (temp > scenic_score) {
               scenic_score = temp;
            }
        }
    }

    std::cout << "Highest scenic score: " << scenic_score << "\n\n";

    return 0;
}