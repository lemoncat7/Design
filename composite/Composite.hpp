/*
 * @Description:
 * @version:
 * @Author: 莫邪
 * @Date: 2023-10-20 10:16:58
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-20 11:11:15
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Entry {
  string name;
  int size;

 public:
  Entry(string name) { this->name = name; }
  void setSize(int size) { this->size = size; }
  string getName() { return name; }
  int getSize() { return size; }
  virtual void read(std::string space = " ") = 0;
};
class File : public Entry {
  string content;

 public:
  File(string name, string content) : Entry(name) {
    this->content = content;
    setSize(content.size());
  }
  void read(std::string space = " ") override {
    std::cout << space;
    std::cout << "File : " << getName() << " size [" << getSize()
              << "] content[" << content << "]" << std::endl;
  }
};
class Folder : public Entry {
  vector<std::shared_ptr<Entry>> children;

 public:
  Folder(string name) : Entry(name) { setSize(0); }
  void addEntry(std::shared_ptr<Entry> entry) {
    children.push_back(entry);
    setSize(getSize() + entry->getSize());
  }
  void read(std::string space = " ") override {
    std::cout << space;
    std::cout << "Folder : " << getName() << " size[" << getSize() << "]"
              << std::endl;
    for (auto child : children) {
      child->read(space + " ");
    }
  }
};