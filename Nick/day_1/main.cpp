#include <iostream>
#include <fstream>

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

int main() {
    std::string line;
    int temp;
    int total = 0;
    int elf_count = 1;
    std::vector<std::pair<int, int>> elf_list;
    
    std::ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            if (!line.empty())
            {
                std::istringstream ss(line);
                ss >> temp;
                total += temp;
            }
            else
            {
               elf_list.push_back(std::make_pair(elf_count, total));
               elf_count++;
               total = 0; 
            }
        }
        myfile.close();
        elf_list.push_back(std::make_pair(elf_count, total));
        total = 0;
    }

    sort(elf_list.begin(), elf_list.end(), [](auto &left, auto &right) {
    return left.second > right.second;
    });

    std::cout << "Top 3 elves carrying the most calories:\n\n";

    for (elf_count = 0; elf_count < 3; elf_count++)
    {
        std::cout << elf_list[elf_count].first << ": " << elf_list[elf_count].second << std::endl;
        total += elf_list[elf_count].second;
    }

    std::cout << "\nTotal top 3 elf calorie count: " << total << "\n\n";


    return 0;
}