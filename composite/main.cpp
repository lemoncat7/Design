/*
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-20 10:16:52
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-20 11:12:19
 */
#include "Composite.hpp"


int main() {
  std::shared_ptr<Folder> root = std::make_shared<Folder>("root");
  std::shared_ptr<Folder> second = std::make_shared<Folder>("sec");
  second->addEntry(std::make_shared<File>("sex.md", "this is a girl"));
  root->addEntry(std::make_shared<File>("readme.md", "for test"));
  root->addEntry(second);
  root->addEntry(std::make_shared<File>("readme2.md", "for test2"));
  root->read();
  return 0;
}