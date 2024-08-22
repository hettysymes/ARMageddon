#include "filetree.h"

using namespace std;


FileTree::FileTree() {
    this->root = new Directory("/");
    this->current = this->root;
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
}

void FileTree::add_directory(string name) {
    Directory *new_directory = new Directory(name);
    this->current->add_subdirectory(new_directory);
}

int FileTree::get_file_count() {
    return this->root->get_file_count();
}

string FileTree::get_deepest_path() {
    return this->root->get_max_path().second;
}

int FileTree::get_total_depth() {
    return this->root->get_total_depth();
}


