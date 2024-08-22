#include <vector>
#include <string>
#include <map>

using namespace std;

class Directory {
    Directory *parent;
    string name;
    string path;

    map<string, Directory*> sub;

    vector<string> files;

    public: 
    Directory(string name);
    // Directory &operator=(const Directory &other);

    ~Directory();

    string get_path();

    void set_parent(Directory *parent_directory);
    Directory *get_parent();

    void add_subdirectory(Directory* other);
    Directory *get_subdirectory(string name);

    void add_file(string filename);

    int count_files();
};