/*
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-11-02 09:26:34
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-11-02 09:51:17
 */
#include "Memento.hpp"

int main() {
  TextEdit edit; 
  MementoManager mgr;
  edit.AddText("Hello World!");
  mgr.AddMemento(edit.CreateMemento());
  edit.AddText("bro !?");
  mgr.AddMemento(edit.CreateMemento());
  edit.AddText("I'm fine, thanks!");
  mgr.AddMemento(edit.CreateMemento());
  std::cout << edit.GetText() << std::endl;
  edit.RestoreMemento(mgr.GetLastMemento());
  std::cout << edit.GetText() << std::endl;
  edit.RestoreMemento(mgr.GetLastMemento());
  std::cout << edit.GetText() << std::endl;
  edit.RestoreMemento(mgr.GetLastMemento());
  std::cout << edit.GetText() << std::endl;
  return 0;
}