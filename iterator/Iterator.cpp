/*
 * @Description:
 * @version:
 * @Author: 莫邪
 * @Date: 2023-10-31 08:52:47
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-31 08:54:26
 */
#include "Iterator.hpp"
// 具体书类
string DesignPatternsBook::getName() { return "Design Patterns"; }
// 具体书类
string RefactoringBook::getName() { return "Refactoring"; }
// BookShelf类,实现Aggregate接口

vector<Book*>& BookShelf::Books() { return books; }
void BookShelf::addBook(Book* book) { books.push_back(book); }
// 创建迭代器
Iterator* BookShelf::createIterator() { return new BookShelfIterator(this); }
// 具体迭代器
BookShelfIterator::BookShelfIterator(BookShelf* bookShelf) {
  this->bookShelf = bookShelf;
  this->index = 0;
}
bool BookShelfIterator::hasNext() {
  if (index < bookShelf->Books().size()) {
    return true;
  }
  return false;
}
Book* BookShelfIterator::next() {
  Book* book = bookShelf->Books()[index];
  index++;
  return book;
}
