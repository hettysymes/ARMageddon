#include <vector>
#include <string>
#include <map>

using namespace std;

// This class represents a single directory
class Directory
{
    Directory *parent; // parent directory object
    string name;
    string path;
    int path_length;

    map<string, Directory *> sub; // maps names to subdirectory objects

    vector<string> files; // stores file names in directory

public:
    Directory(string name);

    ~Directory();

    string get_path();

    void set_parent(Directory *parent_directory);
    Directory *get_parent();

    void add_subdirectory(Directory *other);
    Directory *get_subdirectory(string name);

    void add_file(string filename);

    int get_file_count();

    pair<int, string> get_max_path();

    int get_total_depth();
};