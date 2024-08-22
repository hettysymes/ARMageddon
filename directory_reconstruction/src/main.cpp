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
    // Regex patterns for identifying commands, files, and directories
    static const std::regex CD_PATTERN(R"(\$ cd (.*))");
    static const std::regex LS_PATTERN(R"(\$ ls)");
    static const std::regex FILE_PATTERN(R"((\d+) (.*))");
    static const std::regex DIR_PATTERN(R"(dir (.*))");

    std::string path_to_file = get_input(argc, argv);

    // FileTree object representing the file system
    FileTree *ft = new FileTree();

    std::string line;
    std::smatch match;

    std::ifstream history_file;
    history_file.open(path_to_file);

    while (getline(history_file, line))
    {   
        // match the input line to a pattern
        if (std::regex_match(line, CD_PATTERN))
        { // cd into a directory
            std::string dir_name = line.substr(5);
            ft->cd(dir_name);
        }
        else if (std::regex_match(line, LS_PATTERN))
        { // no action needed on ls
        }
        else if (std::regex_match(line, match, DIR_PATTERN))
        { // add directory to the file tree
            std::string name = match.str(1);
            ft->add_directory(name);
        }
        else if (std::regex_match(line, match, FILE_PATTERN))
        { // add file to the file tree
            long filesize = std::stol(match.str(1));
            std::string name = match.str(2);
            ft->add_file(name);
        }
    }

    // report statistics
    int total_file_count = ft->get_file_count();
    cout << total_file_count << ",\"" << ft->get_deepest_path() << "\"," << round(100.0 * (double)ft->get_total_depth() / total_file_count)/100.0 << endl;

    history_file.close();
}