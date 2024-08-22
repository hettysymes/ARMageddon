#include <vector>
#include <string>
#include "directory.h"

using namespace std;


Directory::Directory(string name) {
    this->name = name;
    this->path = "";
    this->path_length = 0;
}

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
    this->path_length = parent_directory->path_length+1;
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

int Directory::get_file_count() {
    int total = 0;
    for (map<string, Directory*>::iterator itr = this->sub.begin(); itr != this->sub.end(); itr++) {
        total += itr->second->get_file_count();
    }
    total +=  this->files.size();
    return total;
}

pair<int, string> Directory::get_max_path() {
    pair<int, string> best = pair<int, string>(this->path_length, this->path + "/" + this->files[0]);
    for (map<string, Directory*>::iterator itr = this->sub.begin(); itr != this->sub.end(); itr++) {
        pair<int, string> sub_max_length = itr->second->get_max_path();
        if (sub_max_length.first >= best.first) {
            best = sub_max_length;
        }
    }
    return best;
}

int Directory::get_total_depth() {
    int total = 0;
    for (map<string, Directory*>::iterator itr = this->sub.begin(); itr != this->sub.end(); itr++) {
        total += itr->second->get_total_depth();
    }
    total +=  this->files.size() * this->path_length;
    return total;
}

