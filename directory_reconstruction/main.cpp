#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "filetree.h"

using namespace std;

int main() {
    string path_to_file = "sample.txt";

    FileTree* ft = new FileTree();
    delete ft;

    string line;

    ifstream history_file;
    history_file.open(path_to_file);

    getline(history_file, line);

    while (true) {
        char cmd = line[2]; 
        if (cmd == 'c') { // cd
            string dir_name = line.substr(5);
            ft->cd(dir_name);
            cout << "cd to " << dir_name << endl;
            getline(history_file, line);
        } else { // ls
            cout << "ls used" << endl;
            getline(history_file, line);
            while (line[0] != '$') {
                string name = line.substr(line.find(" ")+1);
                if (line[0] == 'd') { // directory
                    cout << "add directory " << name << endl;
                    ft->add_directory(name);
                } else { // file
                    cout << "add file " << name << "." << endl;
                    ft->add_file(name);
                }
                getline(history_file, line);
            }
        }
    }
    cout << ft->file_count() << "\n";

    history_file.close();
}