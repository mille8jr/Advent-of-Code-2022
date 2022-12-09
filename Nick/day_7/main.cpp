#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

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

struct directory {
    std::vector<std::string> directories;
    std::vector<std::pair<std::string, int>> files;
    std::string name;
    int size;
};

// recursive function to calculate directory size
int calculateDirSize(std::map<std::string, directory>& filesystem,
                               const std::string& dirName = "/") {
    int size = 0;
    for (const auto& dir : filesystem[dirName].directories) {
        size += calculateDirSize(filesystem, dir);
    }
    for (const auto& file : filesystem[dirName].files) {
        size += file.second;
    }
    filesystem[dirName].size = size;
    return size;
}

// recursive function to print the filesystem
void printDirectory(std::map<std::string, directory>& filesystem, 
                    const std::string& dirName = "/", std::string leading_spaces = "") {
    std::cout << leading_spaces << "- " << filesystem[dirName].name << " (dir)\n";
    leading_spaces = leading_spaces + "  ";
    for (const auto& dir : filesystem[dirName].directories) {
        printDirectory(filesystem, dir, leading_spaces);
    }
    for (const auto& file : filesystem[dirName].files) {
        std::cout << leading_spaces << "- " << file.first << " (file, size=" << file.second << ")\n";
    }
}

int main() {
    std::map<std::string, directory> filesystem;
    std::vector<std::string> current_directory;
    std::vector<std::pair<std::string, int>> large_dirs;
    std::string filepath;
    std::string delimiter = " ";
    size_t pos;
    int size;
    int total = 0;
    int total_disk_size = 70000000;
    int update_size = 30000000;
    int disk_used;

    auto lines = readFile("input.txt");
    for(auto line : lines) {
        //split line by spaces and add to command vector
        std::vector<std::string> command; 
        while ((pos = line.find(delimiter)) != std::string::npos) {
            command.push_back(line.substr(0, pos));
            line.erase(0, pos + delimiter.length());
        }
        command.push_back(line);
        // store current filepath in a vector called current_directory
        // push and pop as you move down or up a directory
        if (command[0] == "$") {
            if (command[1] == "cd") {
                if (command[2] == "..") {
                    current_directory.pop_back();
                }
                // store directory data in directory struct and add to filepath map
                else {
                    directory d;
                    if (command[2] == "/")
                        current_directory.push_back(command[2]);
                    else
                        current_directory.push_back(command[2] + "/");
                    filepath = "";
                    for (const auto& dir : current_directory) {
                        filepath += dir;
                    }
                    d.name = command[2];
                    filesystem.insert({filepath, d});
                }
            }
        }
        // add to list of directories within directory struct
        else if (command[0] == "dir") {
            filesystem[filepath].directories.push_back(filepath + command[1] + "/");
        }
        // add to list of files within directory struct
        else {
            filesystem[filepath].files.push_back(std::make_pair(command[1], stoll(command[0])));
        }
    }

    calculateDirSize(filesystem);
    printDirectory(filesystem);

    disk_used = filesystem["/"].size;

    for ( auto it = filesystem.begin(); it != filesystem.end(); ++it  )
    {
        size = it->second.size;
        if (size <= 100000)
            total += size;
        else if (size >= 30000000 - (total_disk_size - disk_used))
            large_dirs.push_back(std::make_pair(it->second.name, size));
    }

    // reverse sort large_dirs by second value
    std::sort(large_dirs.begin(), large_dirs.end(), [](auto &left, auto &right) {
    return left.second < right.second;
    });  

    std::cout << "\nSum of directory sizes of 100000 or less: " << total << "\n\n";

    std::cout << "The smallest directory that would free up enough space\n";
    std::cout << "is directory " << large_dirs[0].first << " with a size of ";
    std::cout << large_dirs[0].second << "\n\n";

    return 0;
}