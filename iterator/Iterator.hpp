/*
 * @Description: 
 * @version: 
 * @Author: 莫邪
 * @Date: 2023-10-31 08:43:54
 * @LastEditors: 莫邪
 * @LastEditTime: 2023-10-31 08:54:59
 */
#include <iostream>
using namespace std;
class Iterator;
// Book接口
class Book {
public:
  virtual string getName() = 0;
};
// 具体书类
class DesignPatternsBook : public Book {
public:
  string getName() override ;
};
// 具体书类 
class RefactoringBook : public Book {
public:
   string getName() override ;
};
// BookShelf类,实现Aggregate接口
class BookShelf {
private:
  vector<Book*> books;
public:
  vector<Book*>& Books() ;
  void addBook(Book* book) ;
  // 创建迭代器
  Iterator* createIterator() ;
};
// 迭代器接口
class Iterator {
public:
  virtual bool hasNext() = 0;
  virtual Book* next() = 0;
};
// 具体迭代器
class BookShelfIterator : public Iterator {
private:
  BookShelf* bookShelf;
  int index;
public:
  BookShelfIterator(BookShelf* bookShelf) ;
  bool hasNext() override ;
  Book* next() override ;
};

