/*
 * @Description:
 * @version:
 * @Author: 莫邪
 * @Date: 2023-11-02 09:57:43
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-11-02 10:04:36
 */
#include "Memento.hpp"
// 编辑器
void TextEdit::AddText(const std::string &text) { text_ += text; }
const std::string &TextEdit::GetText() { return text_; }
std::shared_ptr<TextMemento> TextEdit::CreateMemento() {
  return std::make_shared<TextMemento>(*this);
}
void TextEdit::RestoreMemento(std::shared_ptr<TextMemento> memento) {
  text_ = memento->GetText();
}
// 备忘录(快照)

TextMemento::TextMemento(TextEdit &textEdit) { text_ = textEdit.GetText(); }
std::string TextMemento::GetText() { return text_; }

// 快照管理

void MementoManager::AddMemento(std::shared_ptr<TextMemento> memento) {
  memento_list_.push_back(memento);
}
std::shared_ptr<TextMemento> MementoManager::GetLastMemento() {
  // if (memento_list_.empty()) return std::make_shared<TextMemento>(TextEdit());
  auto mem = memento_list_.back();
  Undo();
  return mem;
}
void MementoManager::Undo() { memento_list_.pop_back(); }