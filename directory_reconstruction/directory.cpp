#include <vector>
#include <string>
#include <iostream>
#include "directory.h"

using namespace std;


Directory::Directory(string name) {
    cout << "running constructor" << endl;
    this->name = name;
    this->path = "";
    cout << "constructed directory " << name << endl;
}

// Directory &Directory::operator=(const Directory &other) {

// }

Directory::~Directory() {
    for (map<string, Directory*>::iterator itr = this->sub.begin(); itr != this->sub.end(); itr++) {
        delete itr->second;
    }
}

string Directory::get_path() {
    return this->path;
}

void Directory::set_parent(Directory *parent_directory) {
    this->parent = parent_directory;
    this->path = parent_directory->path + "/" + this->name;
}

Directory *Directory::get_parent() {
    return this->parent;
}

void Directory::add_subdirectory(Directory* other) {
    this->sub.insert(pair<string, Directory*>(other->name, other));
    other->set_parent(this);
}

Directory* Directory::get_subdirectory(string name) {
    return this->sub.find(name)->second;
}

void Directory::add_file(string filename) {
    this->files.push_back(filename);
}

int Directory::count_files() {
    return this->files.size();
}
