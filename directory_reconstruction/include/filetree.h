#include "directory.h"

using namespace std;

class FileTree
{
    Directory *root;
    Directory *current;

public:
    FileTree();
    void cd(string name);
    void add_file(string name);
    void add_directory(string name);
    int get_file_count();
    string get_deepest_path();
    int get_total_depth();
};