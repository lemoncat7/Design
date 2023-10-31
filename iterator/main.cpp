/*
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-31 08:43:58
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-31 08:55:57
 */
#include "Iterator.hpp"

// 客户端代码
int main() {
  BookShelf* bookShelf = new BookShelf();
  bookShelf->addBook(new DesignPatternsBook());
  bookShelf->addBook(new RefactoringBook());
  Iterator* it = bookShelf->createIterator();
  while (it->hasNext()) {
    Book* book = it->next();
    cout << book->getName() << endl; 
  }
  return 0;
}