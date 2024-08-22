#include "filetree.h"
#include <iostream>

using namespace std;


FileTree::FileTree() {
    this->root = new Directory("/");
    this->current = this->root;
    this->total_files = 0;
}

void FileTree::cd(string name) {
    if (name == "/") {
        this->current = this->root;
    } else if (name == "..") {
        this->current = this->current->get_parent();
    } else {
        this->current = this->current->get_subdirectory(name);
    }
}

void FileTree::add_file(string name) {
    this->current->add_file(name);
    this->total_files++;
}

void FileTree::add_directory(string name) {
    cout << "Making new dir" << endl;
    Directory *new_directory = new Directory(name);
    cout << "made new directory";
    this->current->add_subdirectory(new_directory);
}

int FileTree::file_count() {
    return this->total_files;
}


