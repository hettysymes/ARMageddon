#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <regex>

#include "filetree.h"

std::string get_input(int argc, char **argv)
{
    std::string input = "";
    if (argc == 1 || argv[0] == NULL)
    {
        input = "sample.txt";
    }
    else
    {
        input = argv[1];
    }

    return input;
}

int main(int argc, char **argv)
{
    static const std::regex CD_PATTERN(R"(\$ cd (.*))");
    static const std::regex LS_PATTERN(R"(\$ ls)");
    static const std::regex FILE_PATTERN(R"((\d+) (.*))");
    static const std::regex DIR_PATTERN(R"(dir (.*))");

    std::string path_to_file = get_input(argc, argv);

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
        }
        else if (std::regex_match(line, LS_PATTERN))
        {
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

    int total_file_count = ft->get_file_count();
    cout << total_file_count << ",\"" << ft->get_deepest_path() << "\"," << (double)ft->get_total_depth() / total_file_count << endl;

    history_file.close();
}