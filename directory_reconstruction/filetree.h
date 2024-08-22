#include "directory.h"

using namespace std;

class FileTree
{
    Directory *root;
    Directory *current;
    int total_files;

public:
    FileTree();
    void cd(string name);
    void add_file(string name);
    void add_directory(string name);
    int file_count();
};