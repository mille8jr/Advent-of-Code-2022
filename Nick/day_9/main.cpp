#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <tuple>
#include <cmath>

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

std::tuple<int, int, std::pair<int, int>> gridSize(const std::vector<std::string>& lines) {
    int x_min = 0;
    int x_max = 0;
    int y_min = 0;
    int y_max = 0;
    int x = 0;
    int y = 0;
    int width;
    int height;
    int num_steps;
    char direction;
    std::pair<int, int> starting_point;

    for(const auto& line : lines) {
        std::istringstream ss(line);
        ss >> direction >> num_steps;
        if (direction == 'L' || direction == 'D') {
            num_steps *= -1;
        }
        if (direction == 'L' || direction == 'R') {
            x += num_steps;
            if (x < x_min)
                x_min = x;
            if (x > x_max)
                x_max = x;
        }
        else if (direction == 'U' || direction == 'D') {
            y += num_steps;
            if (y < y_min)
                y_min = y;
            if (y > y_max)
                y_max = y;
        }
        else
            throw std::invalid_argument("received invalid input");
    }
    width = x_max - x_min;
    height = y_max - y_min;
    x = width - x_max;
    y = height - y_max;
    starting_point = std::make_pair(x, y);
    return std::make_tuple(width, height, starting_point);

}

void moveTail(const std::pair<int, int>& head, std::pair<int, int>& tail) {
    int delta_x = abs(head.first - tail.first);
    int delta_y = abs(head.second - tail.second);
    if (delta_x > 1 || delta_y > 1) {
        if (delta_x == 2) {
            tail.first += (head.first - tail.first) / 2;
            if (delta_y == 1) {
                tail.second = head.second;   
            }
        }
        if (delta_y == 2) {
            tail.second += (head.second - tail.second) / 2;
            if (delta_x == 1) {
                tail.first = head.first;
            }
        }
    }
}

int moveKnots(std::vector<std::vector<std::string>> grid, 
              const std::vector<std::string>& lines, 
              const std::pair<int, int>& starting_point, 
              const int& num_knots) 
{
    char direction;
    int num_steps;
    int delta_x = 0;
    int delta_y = 0;
    int tail_count = 1;
    std::vector<std::pair<int, int>> knots;

    for (int i = 0; i < num_knots; i++) {
        knots.push_back(starting_point);
    }

    for (const auto& line : lines) {
        std::istringstream ss(line);
        ss >> direction >> num_steps;
        for (int i = 0; i < num_steps; i++) {
            // move head
            switch (direction) {
                case 'L':
                    knots[0].first--;
                    break;
                case 'R':
                    knots[0].first++;
                    break;
                case 'U':
                    knots[0].second++;
                    break;
                case 'D':
                    knots[0].second--;
                    break;
                default:
                    throw std::invalid_argument("received invalid input");
            }
            
            for (int j = 1; j < num_knots; j++) {
                moveTail(knots[j-1], knots[j]);
                if (j == num_knots - 1 && grid[knots[j].first][knots[j].second] != "#") {
                    grid[knots[j].first][knots[j].second] = "#";
                    tail_count++;
                }
            }
            
        }
    }
    return tail_count;
}

int main() {
    int width, height;
    std::pair<int, int> starting_point;
    std::vector<std::vector<std::string>> grid;
    
    auto lines = readFile("input.txt");
    std::tie(width, height, starting_point) = gridSize(lines);

    for (int i = 0; i <= width; i++) {
        std::vector<std::string> temp;
        for (int j = 0; j <= height; j++) {
            temp.push_back(".");
        }
        grid.push_back(temp);
    }

    grid[starting_point.first][starting_point.second] = "#";

    std::cout << "With 2 knots, There are " 
              << moveKnots(grid, lines, starting_point, 2) 
              << " positions the tail visited at least once.\n\n";

    std::cout << "With 10 knots, There are " 
              << moveKnots(grid, lines, starting_point, 10) 
              << " positions the tail visited at least once.\n\n";

    return 0;
}