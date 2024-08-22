#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <regex>

#include "filetree.h"

int main()
{
    static const std::regex CD_PATTERN(R"(\$ cd (.*))");
    static const std::regex LS_PATTERN(R"(\$ ls)");
    static const std::regex FILE_PATTERN(R"((\d+) (.*))");
    static const std::regex DIR_PATTERN(R"(dir (.*))");

    std::string path_to_file = "sample.txt";

    FileTree *ft = new FileTree();

    std::string line;
    std::smatch match;

    std::ifstream history_file;
    history_file.open(path_to_file);

    while (getline(history_file, line))
    {
        char cmd = line[2];
        if (std::regex_match(line, CD_PATTERN))
        {
            std::string dir_name = line.substr(5);
            ft->cd(dir_name);
            cout << "cd to " << dir_name << endl;
        }
        else if (std::regex_match(line, LS_PATTERN))
        {
            cout << "ls used" << endl;
        }
        else if (std::regex_match(line, match, DIR_PATTERN))
        {
            std::string name = match.str(1);
            ft->add_directory(name);
        }
        else if (std::regex_match(line, match, FILE_PATTERN))
        {
            long filesize = std::stol(match.str(1));
            std::string name = match.str(2);
            ft->add_file(name);
        }
    }
    cout << ft->file_count() << "\n";

    history_file.close();
}