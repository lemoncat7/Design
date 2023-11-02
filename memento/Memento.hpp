/*
 * @Description:
 * @version:
 * @Author: 莫邪
 * @Date: 2023-11-02 09:26:30
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-11-02 10:00:03
 */
#include <memory>

#include "iostream"

class TextMemento;

// 编辑器
class TextEdit {
  std::string text_;
 public:
  void AddText(const std::string &text);
  const std::string& GetText();
  std::shared_ptr<TextMemento> CreateMemento() ;
  void RestoreMemento(std::shared_ptr<TextMemento> memento) ;
};
// 备忘录(快照)
class TextMemento {
  std::string text_;
 public:
  TextMemento(TextEdit &textEdit);
  std::string GetText() ;
};

// 快照管理
class MementoManager {
  std::vector<std::shared_ptr<TextMemento>> memento_list_;
public:
  void AddMemento(std::shared_ptr<TextMemento> memento) ;
  std::shared_ptr<TextMemento> GetLastMemento() ;
  void Undo() ;
};